/*
 * Locator.c
 *
 *  Created on: 10 Aug 2012
 *      Author: k_beckma
 */

#include "Locator.h"
#include "LocatorDB.h"
#include "sdds_types.h"
#include "Log.h"

rc_t
Locator_addToList(Locator_t* head, Locator_t* newL) {

    if (head == NULL || newL == NULL) {
        return SDDS_RT_BAD_PARAMETER;
    }

    Locator_t* tmp = head;

    while (head != NULL) {
        // locator is allready in the list
        if (Locator_isEqual(head, newL) == true) {
            // up ref of loc in list
            Locator_upRef(head);
            // down ref of locator to insert
            Locator_downRef(newL);
            return SDDS_RT_OK;
        }
        tmp = head;
        head = head->next;
    }
    // add to the end
    tmp->next = newL;
    // take care its the end
    newL->next = NULL;

    Locator_upRef(newL);

    return SDDS_RT_OK;
}

rc_t
Locator_removeFromList(Locator_t* head, Locator_t* toDel) {

    if (head == NULL || toDel == NULL) {
        return SDDS_RT_BAD_PARAMETER;
    }

    Locator_t* tmp = NULL;
    Locator_t* prev = head;

    while (head != NULL) {
        // found it
        if (Locator_isEqual(head, toDel) == true) {
            tmp = head;
            break;
        }
        prev = head;
        head = head->next;
    }

    // nothing found
    if (tmp == NULL) {
        return SDDS_RT_FAIL;
    }

    // chain out
    prev->next = tmp->next;

    tmp->next = NULL;

    // check if they are the same or just equal
    // if just equal we downref both of them
    if (toDel != tmp) {
        Locator_downRef(toDel);
        toDel->next = NULL;
    }
    Locator_downRef(tmp);

    return SDDS_RT_OK;
}

rc_t
Locator_contains(List_t* list, Locator_t* l) {

    if ((list == NULL) || (l == NULL)) {
        return SDDS_RT_BAD_PARAMETER;
    }

    Locator_t* data = (Locator_t*) list->first_fn(list);

    while (data != NULL) {
        // locator is allready in the list
        if (Locator_isEqual(data, l) == true) {
            return SDDS_RT_OK;
        }
        data = list->next_fn(list);
    }

    return SDDS_RT_FAIL;
}

void
Locator_print(Locator_t* loc) {
    char addr[NI_MAXHOST];
    Locator_getAddress(loc, addr);
    Log_debug("Locator {%s}\n", addr);
}
