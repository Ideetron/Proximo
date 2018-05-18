/*
*/
#include "nrf_gpio.h"
#include "sdk_config.h"
#include "proximo_board.h"
#include "nrf_delay.h"


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
  nrf_gpio_pin_write(BUZZER_PIN, 0);

  //  Alarm output pin
  nrf_gpio_cfg_output(ALARM_OUT_PIN);
  nrf_gpio_pin_write(ALARM_OUT_PIN, 0);

  //  Boost converter enable pin
  nrf_gpio_cfg_output(TPS_EN_PIN);
  nrf_gpio_pin_write(TPS_EN_PIN, 0);
}


//__inline void proximo_din_high(void)
//{
//  nrf_gpio_pin_write(SK6812_DIN_PIN, 1);
//}
//
//__inline void proximo_din_low(void)
//{
//  nrf_gpio_pin_write(SK6812_DIN_PIN, 0);
//}
//
//
//__inline void proximo_tps_on(void)
//{
//  nrf_gpio_pin_write(TPS_EN_PIN, 1);
//}
//
//__inline void proximo_tps_off(void)
//{
//  nrf_gpio_pin_write(TPS_EN_PIN, 0);
//}


/*
* Description :     SK6812_WriteBit1
* Brief:            Write a one to the SK6812        
*/
static __inline void SK6812_WriteBit1(void)
{
    // Set the Data pin High
    nrf_gpio_pin_write(SK6812_DIN_PIN, 1);
    
    nrf_delay_us(10);
    
    // Set the Neo Pixel data pin low.
    nrf_gpio_pin_write(SK6812_DIN_PIN, 0);
    
    // Wait
//    Nop();
}

/*
* Description :     SK6812_WriteBit0
* Brief:            Write a zero to the SK6812      
*/
static __inline void SK6812_WriteBit0 (void)
{
    // Set the Data pin High
    nrf_gpio_pin_write(SK6812_DIN_PIN, 1);
    
    // Wait
//    Nop();

    // Set the Neo Pixel data pin low.
    nrf_gpio_pin_write(SK6812_DIN_PIN, 0);
}

