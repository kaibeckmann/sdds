#ifndef EXTERN_LCD_CMD_H
#define EXTERN_LCD_CMD_H

// Raven
void lcd_symb_raven_on(void);
void lcd_symb_raven_off(void);
// Audio
void lcd_symb_bell_on(void);
void lcd_symb_bell_off(void);
void lcd_symb_tone_on(void);
void lcd_symb_tone_off(void);
void lcd_symb_mic_on(void);
void lcd_symb_mic_off(void);
void lcd_symb_speaker_on(void);
void lcd_symb_speaker_off(void);
// Status
void lcd_symb_key_on(void);
void lcd_symb_key_off(void);
void lcd_symb_att_on(void);
void lcd_symb_att_off(void);
// Time
void lcd_symb_space_sun(void);
void lcd_symb_space_moon(void);
void lcd_symb_space_off(void);
void lcd_symb_clock_am(void);
void lcd_symb_clock_pm(void);
void lcd_symb_clock_off(void);
// Radio commuication status
void lcd_symb_trx_rx(void);
void lcd_symb_trx_tx(void);
void lcd_symb_trx_off(void);
void lcd_symb_ip_on(void);
void lcd_symb_ip_off(void);
void lcd_symb_pan_on(void);
void lcd_symb_pan_off(void);
void lcd_symb_zlink_on(void);
void lcd_symb_zlink_off(void);
void lcd_symb_zigbee_on(void);
void lcd_symb_zigbee_off(void);
// Antenna status
void lcd_symb_antenna_level_0(void);
void lcd_symb_antenna_level_1(void);
void lcd_symb_antenna_level_2(void);
void lcd_symb_antenna_off(void);
// Battery status - Controlled by ATMega3290p
// Envelope status
void lcd_symb_env_open(void);
void lcd_symb_env_close(void);
void lcd_symb_env_off(void);
// Temperature
void lcd_symb_temp_celsius(void);
void lcd_symb_temp_fahrenheit(void);
void lcd_symb_temp_off(void);
// Numeric
void lcd_symb_minus_on(void);
void lcd_symb_minus_off(void);
void lcd_symb_dot_on(void);
void lcd_symb_dot_off(void);
void lcd_symb_col_on(void);
void lcd_symb_col_off(void);
// Led
void lcd_led_on(void);
void lcd_led_toggle(void);
void lcd_led_off(void);
// Messages
void lcd_print_msg(const char* s);
void lcd_print_nmbr(const char* s);

void cmd_queue_read(SipcAnswerId_t id);

#define LCD_CMD_LIST \
{\
  {lcd_symb_raven_on},\
  {lcd_symb_raven_off},\
  {lcd_symb_bell_on},\
  {lcd_symb_bell_off},\
  {lcd_symb_tone_on},\
  {lcd_symb_tone_off},\
  {lcd_symb_mic_on},\
  {lcd_symb_mic_off},\
  {lcd_symb_speaker_on},\
  {lcd_symb_speaker_off},\
  {lcd_symb_key_on},\
  {lcd_symb_key_off},\
  {lcd_symb_att_on},\
  {lcd_symb_att_off},\
  {lcd_symb_space_sun},\
  {lcd_symb_space_moon},\
\
  {lcd_symb_space_off},\
  {lcd_symb_clock_am},\
  {lcd_symb_clock_pm},\
  {lcd_symb_clock_off},\
  {lcd_symb_trx_rx},\
  {lcd_symb_trx_tx},\
  {lcd_symb_trx_off},\
  {lcd_symb_ip_on},\
  {lcd_symb_ip_off},\
  {lcd_symb_pan_on},\
  {lcd_symb_pan_off},\
  {lcd_symb_zlink_on},\
  {lcd_symb_zlink_off},\
  {lcd_symb_zigbee_on},\
  {lcd_symb_zigbee_off},\
  {lcd_symb_antenna_level_0},\
\
  {lcd_symb_antenna_level_1},\
  {lcd_symb_antenna_level_2},\
  {lcd_symb_antenna_off},\
  {lcd_symb_env_open},\
  {lcd_symb_env_close},\
  {lcd_symb_env_off},\
  {lcd_symb_temp_celsius},\
  {lcd_symb_temp_fahrenheit},\
  {lcd_symb_temp_off},\
  {lcd_symb_minus_on},\
  {lcd_symb_minus_off},\
  {lcd_symb_dot_on},\
  {lcd_symb_dot_off},\
  {lcd_symb_col_on},\
  {lcd_symb_col_off},\
  {lcd_led_on},\
\
  {lcd_led_toggle},\
  {lcd_led_off},\
\
}

typedef struct
{
  void (*func)(void);
} CmdFunc_t;

extern const CmdFunc_t lcd_func_ptrs[];

#endif // EXTERN_LCD_CMD_H
