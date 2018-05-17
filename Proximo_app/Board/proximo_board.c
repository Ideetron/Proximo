/*
*/
#include "nrf_gpio.h"
#include "sdk_config.h"
//#if NRF_MODULE_ENABLED(BUTTON)
//#include "app_button.h"
//#include "app_timer.h"
//#include "app_error.h"
//#include "nrf_drv_gpiote.h"
//#include "nrf_assert.h"
#include "proximo_board.h"


void proximo_io_init(void)
{
  //  Input pin for the vibration sensor SQ-MIN-200
  nrf_gpio_cfg_input(VIBRATION_PIN, NRF_GPIO_PIN_NOPULL);

  //  LDR Supply Pin
  nrf_gpio_cfg_output(LDR_VCC_PIN);
  nrf_gpio_pin_write(LDR_VCC_PIN, 0);

  //  LDR input pin
  nrf_gpio_cfg_input(LDR_OUT_PIN, NRF_GPIO_PIN_NOPULL);

  //  DATA IN pin for the SK6812 mini RGB LED
  nrf_gpio_cfg_output(SK6812_DIN_PIN);
  nrf_gpio_pin_write(SK6812_DIN_PIN, 0);

  //  Buzzer pin
  nrf_gpio_cfg_output(BUZZER_PIN);
  nrf_gpio_pin_write(BUZZER_PIN, 1);

  //  Alarm output pin
  nrf_gpio_cfg_output(ALARM_OUT_PIN);
  nrf_gpio_pin_write(ALARM_OUT_PIN, 1);

  //  Boost converter enable pin
  nrf_gpio_cfg_output(TPS_EN_PIN);
  nrf_gpio_pin_write(TPS_EN_PIN, 0);
}