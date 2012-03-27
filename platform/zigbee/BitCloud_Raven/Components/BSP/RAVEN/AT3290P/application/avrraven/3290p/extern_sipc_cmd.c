/*========================= INCLUDES                 =========================*/
#include <sipc.h>
#include <sipcproto.h>

#include <extern_sipc_cmd.h>
#include <lcd.h>
#include <led.h>

#include <temp.h>
#include <battery.h>
/*========================= IMPLEMENTATION           =========================*/
const CmdFunc_t lcd_func_ptrs[SIPC_CMD_ID_LCD_MAX] = LCD_CMD_LIST;

// Raven
void lcd_symb_raven_on(void){lcd_symbol_set(LCD_SYMBOL_RAVEN);}
void lcd_symb_raven_off(void){lcd_symbol_clr(LCD_SYMBOL_RAVEN);}
// Audio
void lcd_symb_bell_on(void){lcd_symbol_set(LCD_SYMBOL_BELL);}
void lcd_symb_bell_off(void){lcd_symbol_clr(LCD_SYMBOL_BELL);}
void lcd_symb_tone_on(void){lcd_symbol_set(LCD_SYMBOL_TONE);}
void lcd_symb_tone_off(void){lcd_symbol_clr(LCD_SYMBOL_TONE);}
void lcd_symb_mic_on(void){lcd_symbol_set(LCD_SYMBOL_MIC);}
void lcd_symb_mic_off(void){lcd_symbol_clr(LCD_SYMBOL_MIC);}
void lcd_symb_speaker_on(void){lcd_symbol_set(LCD_SYMBOL_SPEAKER);}
void lcd_symb_speaker_off(void){lcd_symbol_clr(LCD_SYMBOL_SPEAKER);}
// Status
void lcd_symb_key_on(void){lcd_symbol_set(LCD_SYMBOL_KEY);}
void lcd_symb_key_off(void){lcd_symbol_clr(LCD_SYMBOL_KEY);}
void lcd_symb_att_on(void){lcd_symbol_set(LCD_SYMBOL_ATT);}
void lcd_symb_att_off(void){lcd_symbol_clr(LCD_SYMBOL_ATT);}
// Time
void lcd_symb_space_sun(void){lcd_symbol_clr(LCD_SYMBOL_MOON);lcd_symbol_set(LCD_SYMBOL_SUN);}
void lcd_symb_space_moon(void){lcd_symbol_clr(LCD_SYMBOL_SUN);lcd_symbol_set(LCD_SYMBOL_MOON);}
void lcd_symb_space_off(void){lcd_symbol_clr(LCD_SYMBOL_MOON);lcd_symbol_clr(LCD_SYMBOL_SUN);}
void lcd_symb_clock_am(void){lcd_symbol_clr(LCD_SYMBOL_PM);lcd_symbol_set(LCD_SYMBOL_AM);}
void lcd_symb_clock_pm(void){lcd_symbol_clr(LCD_SYMBOL_AM);lcd_symbol_set(LCD_SYMBOL_PM);}
void lcd_symb_clock_off(void){lcd_symbol_clr(LCD_SYMBOL_AM);lcd_symbol_clr(LCD_SYMBOL_PM);}
// Radio commuication status
void lcd_symb_trx_rx(void){lcd_symbol_clr(LCD_SYMBOL_TX);lcd_symbol_set(LCD_SYMBOL_RX);}
void lcd_symb_trx_tx(void){lcd_symbol_clr(LCD_SYMBOL_RX);lcd_symbol_set(LCD_SYMBOL_TX);}
void lcd_symb_trx_off(void){lcd_symbol_clr(LCD_SYMBOL_TX);lcd_symbol_clr(LCD_SYMBOL_RX);}
void lcd_symb_ip_on(void){lcd_symbol_set(LCD_SYMBOL_IP);}
void lcd_symb_ip_off(void){lcd_symbol_clr(LCD_SYMBOL_IP);}
void lcd_symb_pan_on(void){lcd_symbol_set(LCD_SYMBOL_PAN);}
void lcd_symb_pan_off(void){lcd_symbol_clr(LCD_SYMBOL_PAN);}
void lcd_symb_zlink_on(void){lcd_symbol_set(LCD_SYMBOL_ZLINK);}
void lcd_symb_zlink_off(void){lcd_symbol_clr(LCD_SYMBOL_ZLINK);}
void lcd_symb_zigbee_on(void){lcd_symbol_set(LCD_SYMBOL_ZIGBEE);}
void lcd_symb_zigbee_off(void){lcd_symbol_clr(LCD_SYMBOL_ZIGBEE);}
// Antenna status
void lcd_symb_antenna_level_0(void){lcd_symbol_antenna_signal(LCD_SYMBOL_INDEX_ANT_SIG1); lcd_symbol_set(LCD_SYMBOL_ANT_DIS);}
void lcd_symb_antenna_level_1(void){lcd_symbol_antenna_signal(LCD_SYMBOL_INDEX_ANT_SIG2); lcd_symbol_set(LCD_SYMBOL_ANT_DIS);}
void lcd_symb_antenna_level_2(void){lcd_symbol_antenna_signal(LCD_SYMBOL_INDEX_ANT_SIG3); lcd_symbol_set(LCD_SYMBOL_ANT_DIS);}
void lcd_symb_antenna_off(void){lcd_symbol_antenna_disable();}
// Battery status - Controlled by ATMega3290p
// Envelope status
void lcd_symb_env_open(void){lcd_symbol_set(LCD_SYMBOL_ENV_CL);lcd_symbol_set(LCD_SYMBOL_ENV_OP);lcd_symbol_set(LCD_SYMBOL_ENV_MAIN);}
void lcd_symb_env_close(void){lcd_symbol_clr(LCD_SYMBOL_ENV_OP);lcd_symbol_set(LCD_SYMBOL_ENV_CL);lcd_symbol_set(LCD_SYMBOL_ENV_MAIN);}
void lcd_symb_env_off(void){lcd_symbol_clr(LCD_SYMBOL_ENV_OP);lcd_symbol_clr(LCD_SYMBOL_ENV_CL);lcd_symbol_clr(LCD_SYMBOL_ENV_MAIN);}
// Temperature
void lcd_symb_temp_celsius(void){lcd_symbol_clr(LCD_SYMBOL_F);lcd_symbol_set(LCD_SYMBOL_C);}
void lcd_symb_temp_fahrenheit(void){lcd_symbol_clr(LCD_SYMBOL_C);lcd_symbol_set(LCD_SYMBOL_F);}
void lcd_symb_temp_off(void){lcd_symbol_clr(LCD_SYMBOL_C);lcd_symbol_clr(LCD_SYMBOL_F);}
// Numeric
void lcd_symb_minus_on(void){lcd_symbol_set(LCD_SYMBOL_MINUS);}
void lcd_symb_minus_off(void){lcd_symbol_clr(LCD_SYMBOL_MINUS);}
void lcd_symb_dot_on(void){lcd_symbol_set(LCD_SYMBOL_DOT);}
void lcd_symb_dot_off(void){lcd_symbol_clr(LCD_SYMBOL_DOT);}
void lcd_symb_col_on(void){lcd_symbol_set(LCD_SYMBOL_COL);}
void lcd_symb_col_off(void){lcd_symbol_clr(LCD_SYMBOL_COL);}
// Led
void lcd_led_on(void){led_status_set(LED_ON);}
void lcd_led_toggle(void){led_status_set(LED_TOGGLE);}
void lcd_led_off(void){led_status_set(LED_OFF);}
// Messages
void lcd_print_msg(const char* s){lcd_puts(s);}
void lcd_print_nmbr(const char* s){}

typedef struct {
  uint8_t id;
  int16_t value;
} gen_answer_t ;
static bool temp_read_queued = false;
static bool battery_read_queued = false;

static void dummy_answer(SipcAnswerId_t id)
{
  gen_answer_t da = {id, 0} ;
  sipc_send_frame(sizeof(da), (uint8_t*)&da);
}

static void do_temp_read(void* data)
{
  gen_answer_t packet;

  packet.id = SIPC_ANSWER_ID_TEMPERATURE;
  packet.value = temp_get(TEMP_UNIT_CELCIUS);

  sipc_send_frame(sizeof(packet), (uint8_t*)&packet);
  temp_read_queued = false;
}

static void do_battery_read(void* data)
{
  gen_answer_t packet;

  packet.id = SIPC_ANSWER_ID_BATTERY;
  packet.value = battery_voltage_read();

  sipc_send_frame(sizeof(packet), (uint8_t*)&packet);
  battery_read_queued = false;
}

#define QUEUE_READ(id, flag, handler) \
  do { \
    if(flag) \
      dummy_answer(id); \
    else \
    { \
      flag = true;\
      vrt_post_event(handler, NULL); \
    } \
  }while(0)

void cmd_queue_read(SipcAnswerId_t id)
{
  switch(id)
  {
    case SIPC_ANSWER_ID_TEMPERATURE:
      QUEUE_READ(SIPC_ANSWER_ID_TEMPERATURE, temp_read_queued, do_temp_read);
      break;
    case SIPC_ANSWER_ID_BATTERY:
      QUEUE_READ(SIPC_ANSWER_ID_BATTERY, battery_read_queued, do_battery_read);
      break;
  }
}

#undef QUEUE_READ

// eof extern_lcd_cmd.c
