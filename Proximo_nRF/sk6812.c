#include "stdint.h"
#include "sk6812.h"
#include "nrf_log.h"
#include "nrfx_pwm.h"
#include "nrf_drv_pwm.h"
#include "nrf_delay.h"

static bool init = false;

static nrf_drv_pwm_t m_pwm1 = NRF_DRV_PWM_INSTANCE(1);

static void sk6812_handler(nrf_drv_pwm_evt_type_t event_type)
{
    if (event_type == NRF_DRV_PWM_EVT_FINISHED)
    {
        nrf_drv_pwm_uninit(&m_pwm1);
    }
}


void sk6812(uint8_t Green, uint8_t Red, uint8_t Blue)
{
    static uint32_t topvalue;
    uint16_t bit0, bit1, i, offset;
    uint32_t err;

    // Calculate the TOPVALUE and the settings for bit values 0 and 1 with the given duty cycles of 70%=1 and 30%=0.
    topvalue = 16000000UL / 800000UL;
    bit0 = (topvalue * 70UL) / 100UL;
    bit1 = (topvalue * 30UL) / 100UL;

    nrf_drv_pwm_config_t const config1 =
    {
        .output_pins =
        {
            SK6812_DIN_PIN,             // channel 0
            NRF_DRV_PWM_PIN_NOT_USED,   // channel 1
            NRF_DRV_PWM_PIN_NOT_USED,   // channel 2
            NRF_DRV_PWM_PIN_NOT_USED,   // channel 3
        },
        .irq_priority = APP_IRQ_PRIORITY_LOWEST,
        .base_clock   = PWM_PRESCALER_PRESCALER_DIV_1,
        .count_mode   = NRF_PWM_MODE_UP,
        .top_value    = topvalue,
        .load_mode    = NRF_PWM_LOAD_COMMON,
        .step_mode    = NRF_PWM_STEP_AUTO
    };

    if(init == true)
    {
        nrf_drv_pwm_uninit(&m_pwm1);
        init = false;
    }

    err = nrf_drv_pwm_init(&m_pwm1, &config1, sk6812_handler);
    APP_ERROR_CHECK(err);
    init = true;

    // This array cannot be allocated on stack (hence "static") and it must
    // be in RAM (hence no "const", though its content is not changed).
    static uint16_t seq_values[24];

    offset = 0;

    //  Set the bits for the Green byte
    for( i = 0 ; i < 8 ; i++)
    {
      if(Green & (1<<(7-i)))
      {
        seq_values[offset+i] = bit1;
      }
      else
      {
        seq_values[offset+i] = bit0;
      }
    }
    offset += 8;

    //  Set the bits for the Red byte
    for( i = 0 ; i < 8 ; i++)
    {
      if(Red & (1<<(7-i)))
      {
        seq_values[offset+i] = bit1;
      }
      else
      {
        seq_values[offset+i] = bit0;
      }
    }
    offset += 8;

    //  Set the bits for the Blue byte 
    for( i = 0 ; i < 8 ; i++)
    {
      if(Blue & (1<<(7-i)))
      {
        seq_values[offset+i] = bit1;
      }
      else
      {
        seq_values[offset+i] = bit0;
      }
    }

    // Add a little delay at the end of the data transfer to ensure that the data loads correctly  
    seq_values[24] = 0;

    nrf_pwm_sequence_t const seq =
    {
        .values.p_common = seq_values,
        .length          = NRF_PWM_VALUES_LENGTH(seq_values),
        .repeats         = 0,
        .end_delay       = 0
    };

    (void)nrf_drv_pwm_simple_playback(&m_pwm1, &seq, 9, NRF_DRV_PWM_FLAG_STOP);
}