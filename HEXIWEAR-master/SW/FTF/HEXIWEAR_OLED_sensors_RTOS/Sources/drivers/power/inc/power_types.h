/**
 * Power management, related data types
 * Project HEXIWEAR, 2015
 */

#ifndef HG_POWER_TYPES
#define HG_POWER_TYPES

#include <stdint.h>

typedef enum
{
  POWER_OLED,
  POWER_MCU,
  POWER_HTU_TSL,
  POWER_MAXIM,
  POWER_BATTERY

} power_peripheral_t;

typedef enum
{
  POWER_STATUS_SUCCESS,    // success
  POWER_STATUS_INIT_ERROR, // error prior to function being executed
  POWER_STATUS_ERROR       // fail

} power_status_t;

typedef enum
{
    POWER_WAKE_SRC_NONE,
    POWER_WAKE_SRC_USER,
    POWER_WAKE_SRC_SENSOR_TIMER

} power_wake_src_t;

typedef enum
{
    POWER_SLEEP_SRC_NONE,
	POWER_SLEEP_SRC_SENSOR_TAG,
   	POWER_SLEEP_SRC_RTC

} power_sleep_src_t;

typedef enum
{
    POWER_CURRENT_MODE_NORMAL,
    POWER_CURRENT_MODE_SLEEP_SHALLOW,   /**< only OLED */
    POWER_CURRENT_MODE_SLEEP_TOTAL,     /**< everything: OLED + non-freescale sensors + MCU */
    POWER_CURRENT_MODE_SLEEP_SENSOR_TAG /**< only MCU */

} power_current_mode_t;

typedef enum
{
    POWER_SLEEP_MODE_SHALLOW,   /**< only OLED */
    POWER_SLEEP_MODE_TOTAL,     /**< everything: OLED + non-freescale sensors + MCU */
    POWER_SLEEP_MODE_SENSOR_TAG /**< only MCU */

} power_sleep_mode_t;

typedef enum
{
    POWER_SLEEP_STATE_ON,
    POWER_SLEEP_STATE_OFF

} power_sleepState_t;

#endif
