#include <Log.h>
#include <os-ssal/Task.h>
#include <os-ssal/Memory.h>

#include <string.h>
#include <api_calls.h>
#include <error.h>

#define TASK_MNG_TICK 1000
#define TASK_MNG_TASK_ID 3
#define TASK_MNG_MUL_SEC_TO_NANO_SEC 1000000000ULL
#define TASK_MNG_MUL_USEC_TO_NANO_SEC 1000UL
#define TASK_MNG_PRI 102

struct Task_struct {
    void (* cb)(void* obj);
    void* data;
    timeout_t timeout;
    time_t fireTime;
    SSW_TaskMode_t mode;
    struct Task_struct* next;
    struct Task_struct* prev;
    bool isActive;
};

#define STACK_SIZE 1024
static char stack_task_mng[STACK_SIZE];

static struct Task_struct* taskList;
static struct Task_struct* taskLast;
static bool isTaskListEmpty;

static void
addTask(struct Task_struct* t);
static void
stopTask(struct Task_struct* t);
static inline void
deleteTask(struct Task_struct* t);
static inline void
doMng(void);
static void
checkFireTimes(void);

void*
TaskMngLoop(void* foo) {
    (void)foo;

    for(;; ) {
        doMng();
        sys_sleep(TASK_MNG_TICK);
    }
    return NULL;
}

ssw_rc_t
Task_setData(Task _this, void* data) {
    if (_this == NULL) {
        return SDDS_SSW_RT_FAIL;
    }
    _this->data = data;
    return SDDS_SSW_RT_OK;
}


/**
 * Should be called at the init phase
 */
ssw_rc_t
TaskMng_init(void) {
    taskList = (struct Task_struct*)Memory_alloc(sizeof(struct Task_struct));
    taskLast = taskList;
    isTaskListEmpty = true;
    if(taskList == NULL) {
        return SDDS_SSW_RT_FAIL;
    }
    memset(taskList, 0, sizeof(struct Task_struct));

    unsigned int err;
    err = sys_task_create(TASK_MNG_TASK_ID, TASK_MNG_PRI, TaskMngLoop,
                          &stack_task_mng[STACK_SIZE], NULL, NULL);
    if(err != E_OK) {
        Log_error("can't create Task for TaskMng\n");
        return SDDS_SSW_RT_FAIL;
    }

    return SDDS_SSW_RT_OK;
}

Task
Task_create(void) {
    Task t = Memory_alloc(sizeof(struct Task_struct));
    t->isActive = false;
    return t;
}

/**
 * inits a task with a callback function etc
 */
ssw_rc_t
Task_init(Task _this, void (* callback)(void* obj), void* data) {
    _this->cb = callback;
    _this->data = data;

    return SDDS_SSW_RT_OK;
}

ssw_rc_t
Task_start(Task _this, uint8_t sec, SDDS_usec_t usec, SSW_TaskMode_t mode) {
    if(_this->cb == NULL || _this == NULL) {
        return SDDS_SSW_RT_FAIL;
    }
    time_t systemTime = sys_gettime();
    _this->timeout = (usec * TASK_MNG_MUL_USEC_TO_NANO_SEC) + (sec * TASK_MNG_MUL_SEC_TO_NANO_SEC);
    _this->fireTime = systemTime + _this->timeout;
    _this->mode = mode;
    _this->isActive = true;
    addTask(_this);
    return SDDS_SSW_RT_OK;
}

ssw_rc_t
Task_stop(Task _this) {
    if (_this == NULL) {
        return SDDS_SSW_RT_FAIL;
    }
    if(_this->isActive) {
        stopTask(_this);
        _this->isActive = false;
    }
    return SDDS_SSW_RT_OK;
}

ssw_rc_t
Task_delete(Task _this) {
    if (_this == NULL) {
        return SDDS_SSW_RT_FAIL;
    }
    deleteTask(_this);
    return SDDS_SSW_RT_OK;
}


static void
addTask(struct Task_struct* t) {
    taskLast->next = t;
    t->next = NULL;
    t->prev = taskLast;
    taskLast = t;
    isTaskListEmpty = false;
}

static void
stopTask(struct Task_struct* t) {
    t->prev->next = t->next;
    if(t->next != NULL) {
        t->next->prev = t->prev;
    }
    if(t == taskLast) {
        taskLast = t->prev;
    }
    if(t->prev == taskList && t->next == NULL) {
        isTaskListEmpty = true;
    }
}

static inline void
deleteTask(struct Task_struct* t) {
    stopTask(t);
    Memory_free(t);
}

static inline void
doMng() {
    if(!isTaskListEmpty) {
        checkFireTimes();
    }
}

static void
checkFireTimes() {
    struct Task_struct* itterator;
    itterator = taskList->next;
    time_t systemTime = sys_gettime();
    while(itterator != NULL) {
        if(itterator->fireTime < systemTime) {
            if(itterator->mode == SDDS_SSW_TaskMode_repeat) {
                itterator->fireTime = systemTime + itterator->timeout;
            }
            itterator->cb(itterator->data);
            bool lastElement = itterator->next == NULL;
            if(itterator->mode == SDDS_SSW_TaskMode_single) {
                deleteTask(itterator);
            }
            if(lastElement) {
                break;
            }
        }
        itterator=itterator->next;
    }
}