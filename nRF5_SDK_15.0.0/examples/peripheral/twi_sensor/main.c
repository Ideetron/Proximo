/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/** @file
 * @defgroup tw_sensor_example main.c
 * @{
 * @ingroup nrf_twi_example
 * @brief TWI Sensor Example main file.
 *
 * This file contains the source code for a sample application using TWI.
 *
 */

#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"
#include "th06.h"


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


#define TPS_EN_PIN       24 //  Boost converter enable pin
#define I2C_SCL_PIN      11 //  I2C Serial Clock Line  
#define I2C_SDA_PIN      12 //  I2C Serial Data

/* TWI instance ID. */
#define TWI_INSTANCE_ID     0

/* Common addresses definition for temperature sensor. */
#define LM75B_ADDR          (0x90U >> 1)

#define LM75B_REG_TEMP      0x00U
#define LM75B_REG_CONF      0x01U
#define LM75B_REG_THYST     0x02U
#define LM75B_REG_TOS       0x03U

/* Mode for LM75B. */
#define NORMAL_MODE 0U

/* Indicates if operation on TWI has ended. */
static volatile bool m_xfer_done = false;

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/* Buffer for samples read from temperature sensor. */
static uint8_t m_sample;

/**
 * @brief Function for setting active mode on MMA7660 accelerometer.
 */
void LM75B_set_mode(void)
{
    ret_code_t err_code;

    /* Writing to LM75B_REG_CONF "0" set temperature sensor in NORMAL mode. */
    uint8_t reg[2] = {LM75B_REG_CONF, NORMAL_MODE};
    err_code = nrf_drv_twi_tx(&m_twi, LM75B_ADDR, reg, sizeof(reg), false);
    APP_ERROR_CHECK(err_code);
//    while (m_xfer_done == false);

    /* Writing to pointer byte. */
    reg[0] = LM75B_REG_TEMP;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, LM75B_ADDR, reg, 1, false);
    APP_ERROR_CHECK(err_code);
//    while (m_xfer_done == false);
}



/**
 * @brief Function for handling data from temperature sensor.
 *
 * @param[in] temp          Temperature in Celsius degrees read from sensor.
 */
__STATIC_INLINE void data_handler(uint8_t temp)
{
    NRF_LOG_INFO("Temperature: %d Celsius degrees.", temp);
}

/**
 * @brief TWI events handler.
 */
void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            m_xfer_done = true;
            break;
        default:
            break;
    }
}

/**
 * @brief UART initialization.
 */
void twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_lm75b_config = {
       .scl                = I2C_SCL_PIN,
       .sda                = I2C_SDA_PIN,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_lm75b_config, NULL, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}

/**
 * @brief Function for reading data from temperature sensor.
 */
static void read_sensor_data()
{
    m_xfer_done = false;

    /* Read 1 byte from the specified address - skip 3 bits dedicated for fractional part of temperature. */
    ret_code_t err_code = nrf_drv_twi_rx(&m_twi, LM75B_ADDR, &m_sample, sizeof(m_sample));
    APP_ERROR_CHECK(err_code);
}

void th06_init(void)
{
    ret_code_t err_code;
    static uint8_t reg[3] = {0};
    uint8_t statusRegVal;

    /* Read the User register 1 with a repeated start. */
    m_xfer_done = false;
    reg[0] = TH06_READ_USER_REG1;
    err_code = nrf_drv_twi_tx(&m_twi, THO6_I2C_ADDRESS, reg, 1, true);
    APP_ERROR_CHECK(err_code);
//    while (m_xfer_done == false);

    err_code = nrf_drv_twi_rx(&m_twi, THO6_I2C_ADDRESS, &reg[1], 1);
    APP_ERROR_CHECK(err_code);
//    while (m_xfer_done == false);

    //  Mask the reserved bits of the TH06 and configure the TH06 settings.
    statusRegVal = reg[1];
    reg[1] &= TH06_RSVD_MASK;
    reg[1] = RES_RH12_Temp14 | HEATER_OFF;
//    nrf_delay_ms(1);

    /* Write User register 1 with the new setting configuration. */
    m_xfer_done = false;
    reg[0] = TH06_WRITE_USER_REG1;
    err_code = nrf_drv_twi_tx(&m_twi, THO6_I2C_ADDRESS, reg, 2, false);
    NRF_LOG_INFO("Init error code: %X, %d, User Register1: %02X", err_code, err_code, statusRegVal);
    APP_ERROR_CHECK(err_code);
//    while (m_xfer_done == false);
}


static void read_temperature(void)
{
    ret_code_t err_code;
    uint16_t regVal;
    static float temperature, humidity;

    /* Read the User register 1 with a repeated start. */
    uint8_t reg[3];

    m_xfer_done = false;
    reg[0] = TH06_MEASURE_HUMIDITY_HOLD_MASTER;
    err_code = nrf_drv_twi_tx(&m_twi, THO6_I2C_ADDRESS, reg, 1, true);
    APP_ERROR_CHECK(err_code);
//    while (m_xfer_done == false);

    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, THO6_I2C_ADDRESS, reg, 2);
    APP_ERROR_CHECK(err_code);
//    while (m_xfer_done == false);

    regVal = (((uint16_t) reg[0]) << 8) | ((uint16_t)reg[1]);

    // Calculate the humidity
    if(regVal == 0)
    {
        humidity = 0.0;
    }
    else
    {
        humidity = ((125.0 * ((float) regVal)) / 65536.0) - 6.0;
    }

    //  Read the temperature result
    m_xfer_done = false;
    reg[0] = TH06_MEASURE_TEMPERATURE_PREVIOUS;
    err_code = nrf_drv_twi_tx(&m_twi, THO6_I2C_ADDRESS, reg, 1, true);
    APP_ERROR_CHECK(err_code);
//    while (m_xfer_done == false);

    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, THO6_I2C_ADDRESS, &reg[0], 2);
    APP_ERROR_CHECK(err_code);
//    while (m_xfer_done == false);

    regVal = (((uint16_t) reg[0]) << 8) | ((uint16_t)reg[1]);

    // Calculate the temperature
    if(regVal == 0)
    {
        temperature = 0.0;
    }
    else
    {
        temperature = ((175.72 * ((double) regVal)) / 65536.0) - 46.85;
    }

    NRF_LOG_INFO("TH06 measure humidity: %i, Temperature: %i", (int16_t) (humidity * 10.0), (int16_t) (temperature * 10.0));
}


/**
 * @brief Function for main application entry.
 */
int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    //  Boost converter enable pin
    nrf_gpio_cfg_output(TPS_EN_PIN);
    nrf_gpio_pin_write(TPS_EN_PIN, 0);

    NRF_LOG_INFO("TWI sensor example started.");
    NRF_LOG_FLUSH();
    twi_init();
    th06_init();

    while (true)
    {
        nrf_delay_ms(500);

//        do
//        {
//            __WFE();
//        }while (m_xfer_done == false);

        read_temperature();
        NRF_LOG_FLUSH();
    }
}

/** @} */
