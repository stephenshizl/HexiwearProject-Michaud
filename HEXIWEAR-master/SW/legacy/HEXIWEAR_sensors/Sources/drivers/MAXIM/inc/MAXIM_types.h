/**
 * MAXIM-related data types
 * Project HEXIWEAR, 2015
 */

#ifndef HG_MAXIM_TYPES
#define HG_MAXIM_TYPES

#include <stdint.h>
#include "generic_i2c_types.h"

typedef struct
{
  /**
   * I2C relevant information
   */
  genericI2cHandle_t protocol;

} handleMAXIM_t;

typedef enum
{
  modeHR        = 0x2,
  modeSPO2      = 0x3,
  modeMultiLED  = 0x7

} modeMAXIM_t;

typedef enum
{
  ledPower_69  = 0x0, // ADC -> 15 bit
  ledPower_118 = 0x1, // ADC -> 16 bit
  ledPower_215 = 0x2, // ADC -> 17 bit
  ledPower_411 = 0x3  // ADC -> 18 bit

} pwMAXIMT_t;

typedef enum
{
  sampleRate_50   = 0x0,
  sampleRate_100  = 0x1,
  sampleRate_200  = 0x2,
  sampleRate_400  = 0x3,
  sampleRate_800  = 0x4,
  sampleRate_1000 = 0x5,
  sampleRate_1600 = 0x6,
  sampleRate_3200 = 0x7

} sampleRateMAXIM_t;

typedef enum
{
  slotRed   =  0x0,
  slotIR    =  0x1,
  slotGreen =  0x2,
  slotNone  =  0x3

} slotMAXIM_t;

typedef enum
{
  STATUS_MAXIM_SUCCESS,        // success
  STATUS_MAXIM_ERROR,          // fail
  STATUS_MAXIM_PROTOCOL_ERROR, // protocol failure
  STATUS_MAXIM_INIT_ERROR,     // initialization error
  STATUS_MAXIM_PARAM_ERROR,    // invalid parameter is given
  STATUS_MAXIM_TIMEOUT         // timeout occured

} statusMAXIM_t;

/**
 * general module settings
 */

typedef struct
{
  // mode (HR, SpO2, or multi-led)
  modeMAXIM_t mode;

  // multi-led time slots
  slotMAXIM_t slot1;
  slotMAXIM_t slot2;
  slotMAXIM_t slot3;
  slotMAXIM_t slot4;

  // timings
  sampleRateMAXIM_t sampleRate;
         pwMAXIMT_t pulseWidth;

  // device I2C address
  uint8_t address;

} settingsMAXIM_t;

#endif
