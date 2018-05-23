#ifndef TH06_H
#define TH06_H

#include <stdint.h>

//    extern uint8_t NRF_TWI_MNGR_BUFFER_LOC_IND th06_write_user_reg1;


   /******************************************************************************************
                                            DEFINES
    ******************************************************************************************/

    #define THO6_I2C_ADDRESS (0x80U>>1)
    #define TH06_RSVD_MASK   0b00111010 // bit mask for the temperature user register 1


    /******************************************************************************************
                                        TYPE DEFINITIONs
    ******************************************************************************************/

    /* TH06 Registers */
    typedef enum
    {
        TH06_MEASURE_HUMIDITY_HOLD_MASTER           = 0xE5,
        TH06_MEASURE_HUMIDITY_NO_HOLD_MASTER        = 0xF5,
        TH06_MEASURE_TEMPERATURE_HOLD_MASTER        = 0xE3,
        TH06_MEASURE_TEMPERATURE_NO_HOLD_MASTER     = 0xF3,
        TH06_MEASURE_TEMPERATURE_PREVIOUS           = 0xE0,
        TH06_RESET                                  = 0xFE,
        TH06_WRITE_USER_REG1                        = 0xE6,
        TH06_READ_USER_REG1                         = 0xE7,
        TH06_FIRMWARE_REV                           = 0x84
    }TH06_I2C_COMMANDS;

    typedef enum 
    {
        RES_MASK        = 0b10000001U,   //  mask for bits 7 and 0
        RES_RH12_Temp14 = 0b00000000U,   //  22.8ms MAX conversion time
        RES_RH8_Temp12  = 0b00000001U,   //  6.9ms
        RES_RH10_Temp13 = 0b10000000U,   //  23.0ms
        RES_RH11_Temp11 = 0b10000001U    //  9.4ms
    }TEMP_RESOLUTION;


    /* Heater enumeration to enable or disable the heater on initialisation. */
    typedef enum 
    {
        HEATER_ON  = 0x04U,
        HEATER_OFF = 0x00U
    }HEATERe;

    typedef enum 
    {
        TH06_INIT,
        TH06_WRITE_SETTINGS,
        TH06_IDLE,
        TH06_CONVERSION_START,
        TH06_WAIT_FOR_CONVERSION_COMPLETE,
        TH06_READ_HUMIDITY,
        TH06_READ_TEMPERATURE,
        TH06_COMPLETE,
        TH06_ERROR
    }TH06_STATEMACHINE;


    /* Structure for the temperature and humidity results. */
    typedef struct
    {
        TH06_STATEMACHINE   State;
        double              Temperature;
        double              Humidity;
        unsigned int        Timeout;
    }TH06_DATA;


    /*
     *  FUNCTION PROTOTYPES
     */
    
#endif