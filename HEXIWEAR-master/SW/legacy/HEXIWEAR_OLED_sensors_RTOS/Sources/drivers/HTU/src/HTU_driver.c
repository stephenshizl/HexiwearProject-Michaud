/**
 * HTU driver functions
 * Project HEXIWEAR, 2015
 */

#include "HTU_driver.h"
#include "HTU_info.h"

#include "FS_I2C.h"
#include "generic_i2c_driver.h"

#include "HEXIWEAR_types.h"
#include "HEXIWEAR_info.h"
#include <string.h>

#include "error.h"

/**
 * intern variables
 */

static handleHTU_t
  self;
static settingsHTU_t
  settings;

/**
 * measurement time for temperature and humidity
 */
static uint16_t
  temp_meas_time,
  humidity_meas_time;

/**
 * intern functions
 */

/**
 * visible functions
 */

/**
 * initialize i2c interface to HTU21D sensor and reset the module
 * @return status flag
 */
htu_status_t HTU_Init(
                        handleHTU_t* htuHandle,
                      settingsHTU_t* htuSettings
                    )
{
  /**
   * initialize the intern structures,
   * which will be used from now on
   */

  memcpy( (void*)&self,     (void*)htuHandle,   sizeof(self) );
  memcpy( (void*)&settings, (void*)htuSettings, sizeof(settings) );

  statusI2C_t
    status = I2C_Init( &(self.protocol), settings.address, settings.baudRate_kbps );

  if ( STATUS_I2C_SUCCESS != status )
  {
    return STATUS_HTU_INIT_ERROR;
  }

  else
  {
    // reset device
    htu_status_t
      devStatus = STATUS_HTU_SUCCESS;

    devStatus |= HTU_SoftReset();
    devStatus |= HTU_SetUserRegister();

    if ( STATUS_HTU_SUCCESS != devStatus )
    {
      catch(9);
      return STATUS_HTU_ERROR;
    }

    else
    {
      return STATUS_HTU_SUCCESS;
    }
  }
}

/**
 * initialize i2c interface to HTU21D sensor and reset the module
 * @return status flag
 */
htu_status_t HTU_Deinit()
{
  statusI2C_t
    status = I2C_Deinit( &(self.protocol) );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(9);
    return STATUS_HTU_PROTOCOL_ERROR;
  }

  else
  {
    return STATUS_HTU_SUCCESS;
  }
}

/**
 * reset the sensor
 */
htu_status_t HTU_SoftReset()
{
  genericI2cHandle_t
    i2cProtocol = self.protocol;

  uint8_t
    cmd[1] = { HTU21D_SOFT_RESET };

  i2c_status_t
    status = I2C_DRV_MasterSendDataBlocking (
                                              i2cProtocol.instance,
                                              &(i2cProtocol.device),

                                              NULL,
                                              0,

                                              &(cmd[0]),
                                              1,

                                              i2cProtocol.timeout
                                            );

  if ( kStatus_I2C_Success != status )
  {
    catch(9);
    return STATUS_HTU_PROTOCOL_ERROR;
  }
  else
  {
    return STATUS_HTU_SUCCESS;
  }
}

/**
 * configure the measurement resolution
 */
htu_status_t HTU_SetUserRegister()
{
  uint8_t
    txBuff;

  uint8_t
    rxBuff[1];

  // set byte to be written to user register,
  // also set the corresponding measurement time

  switch ( settings.bitRes )
  {
      // RH: 12bit, TEMP: 14bit
      case BITRES_HTU_RH_12_TEMP14: {
                                      txBuff             = 0x2;
                                      temp_meas_time     = 50;
                                      humidity_meas_time = 16;

                                      break;
                                    }

      // RH: 8bit, TEMP: 12bit
      case BITRES_HTU_RH_8_TEMP12: {
                                      txBuff             = 0x3;
                                      temp_meas_time     = 13;
                                      humidity_meas_time = 3;

                                      break;
                                    }

      // RH: 10bit, TEMP: 13bit
      case BITRES_HTU_RH_10_TEMP13: {
                                      txBuff             = 0x82;
                                      temp_meas_time     = 25;
                                      humidity_meas_time = 5;

                                      break;
                                    }

      // RH: 11bit, TEMP: 11bit
      case BITRES_HTU_RH_11_TEMP11: {
                                      txBuff             = 0x83;
                                      temp_meas_time     = 7;
                                      humidity_meas_time = 8;

                                      break;
                                    }
      default: {}
  }


  statusI2C_t
    status = I2C_WriteReg( &(self.protocol), HTU21D_WRITE_USER_REG, txBuff );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(9);
    return STATUS_HTU_PROTOCOL_ERROR;
  }

  else
  {
    return STATUS_HTU_SUCCESS;
  }
}

/**
 * retrieve temperature data
 * @param  tempData  data to be filled
 * @return           status flag
 */
htu_status_t HTU_GetTemp( int16_t* tempData )
{
  genericI2cHandle_t
    i2cProtocol = self.protocol;

  uint8_t
    cmd[1] = { HTU21D_TRIGGER_TEMP_NOHOLD };

  uint8_t
//    rxBuff[3];
    rxBuff[2];

  *tempData = -1;

  i2c_status_t
    status = I2C_DRV_MasterSendDataBlocking (
                                              i2cProtocol.instance,
                                              &(i2cProtocol.device),

                                              NULL,
                                              0,

                                              &(cmd[0]),
                                              1,

                                              i2cProtocol.timeout
                                            );

  if ( kStatus_I2C_Success != status )
  {
    return STATUS_HTU_PROTOCOL_ERROR;
  }

  else
  {
    // wait corresponding time
//    OSA_TimeDelay(temp_meas_time);

    // read temperature data
    while (1)
    {
      status = I2C_DRV_MasterReceiveDataBlocking(
                                                  i2cProtocol.instance,
                                                  &(i2cProtocol.device),

                                                  NULL,
                                                  0,

                                                  &(rxBuff[0]),
												  ArraySize( rxBuff ),

                                                  i2cProtocol.timeout
                                                );

      if ( kStatus_I2C_Success == status )
      {
        break;
      }
    }

    /**
     * convert to final value
     * discard the third received byte (checksum)
     */
    *tempData = ( rxBuff[0] << 8 ) | ( rxBuff[1] & 0xFC );

    return STATUS_HTU_SUCCESS;
  }
}

/**
 * retrieve humidity data
 * @param  humData  data to be filled
 * @return          status flag
 */
htu_status_t HTU_GetHum( int16_t* humData )
{
  genericI2cHandle_t
    i2cProtocol = self.protocol;

  uint8_t
    cmd[1] = { HTU21D_TRIGGER_HUMD_NOHOLD };

  uint8_t
    rxBuff[3];

  i2c_status_t
    status = I2C_DRV_MasterSendDataBlocking (
                                              i2cProtocol.instance,
                                              &(i2cProtocol.device),

                                              NULL,
                                              0,

                                              &(cmd[0]),
                                              1,

                                              i2cProtocol.timeout
                                            );

  if ( kStatus_I2C_Success != status )
  {
    return STATUS_HTU_PROTOCOL_ERROR;
  }

  else
  {
    // wait corresponding time
//    OSA_TimeDelay( humidity_meas_time );

    // read humidity data
    while (1)
    {
      status = I2C_DRV_MasterReceiveDataBlocking(
                                                  i2cProtocol.instance,
                                                  &(i2cProtocol.device),

                                                  NULL,
                                                  0,

                                                  &(rxBuff[0]),
                                                  3,

                                                  i2cProtocol.timeout
                                                );

      if ( kStatus_I2C_Success == status )
      {
        break;
      }
    }

    /**
     * convert to final value
     * discard the third received byte (checksum)
     */
    *humData = ( rxBuff[0] << 8 ) | ( rxBuff[1] & 0xFC );

    return STATUS_HTU_SUCCESS;
  }
}

/**
 * retrieve temperature and humidity data
 */
htu_status_t HTU_ReadRawData(
						    	int16_t* temperature,
								int16_t* humidity
                            )
{
  htu_status_t
    status = STATUS_HTU_SUCCESS;

  status |= HTU_GetTemp( temperature );
  status |= HTU_GetHum ( humidity );

  return status;
}

/**
 * check if I2C bus needs to be recovered
 * @return status flag
 */
htu_status_t HTU_RecoverI2C()
{
	statusI2C_t
		recoverStatus = I2C_Recover( &(self.protocol) );

	if ( STATUS_I2C_SUCCESS != recoverStatus )
	{
		catch( CATCH_WEATHER );
		return STATUS_HTU_ERROR;
	}
	else
	{
		return STATUS_HTU_SUCCESS;
	}
}

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void hum_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      )
{
  /**
   * helper pointers
   */
  int16_t*
    input = (int16_t*)src;
  float*
    output = (float*)dst;

  // convert data
  output[idx] = -6 + 125 * ( (float)input[idx] / 0x10000 );

  if( output[idx] > 100 )
  {
    output[idx] = 100;
  }
  else if ( output[idx] < 0 )
  {
    output[idx] = 0;
  }
}

/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void hum_fmtDef2Me (
                      const void* src,
                            void* dst,
                         uint32_t idx
                    )
{
  /**
   * helper pointers
   */
  uint16_t*
    input = (uint16_t*)src;
  mE_t*
    output = (mE_t*)dst;

  // convert data
  float
    foo = -6 + 125 * ( (float)input[idx] / 0x10000 );

  if( foo > 100 )
  {
    foo = 100;
  }
  else if ( foo < 0 )
  {
    foo = 0;
  }

  output[idx] = (mE_t)( foo * 100 );
}

/**
 * format raw to byte - currently unimplemented
 */
void hum_fmtDef2Byte(
						const void* src,
							  void* dst,
						   uint32_t idx
					)
{}

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void temp_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      )
{
  /**
   * helper pointers
   */
  int16_t*
    input = (int16_t*)src;
  float*
    output = (float*)dst;

  // convert data
  output[idx] = (float)( ( ( 175.72 * (float)input[idx] ) / 65536.0 ) - 46.85 );
}

/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void temp_fmtDef2Me (
                      const void* src,
                            void* dst,
                         uint32_t idx
                    )
{
    /**
     * helper pointers
     */
    uint16_t*
        input = (uint16_t*)src;
    mE_t*
        output = (mE_t*)dst;

    // convert data
    float
        foo = (float)( ( ( 175.72 * (float)input[idx] ) / 65536.0 ) - 46.85 );

    uint8_t
        calibConst;

    if ( foo < 16 )
    {
        calibConst = HTU_TEMP_CALIB_OFFSET_0;
    }
    else if ( foo < 32 )
    {
        calibConst = HTU_TEMP_CALIB_OFFSET_1;
    }
    else
    {
        calibConst = HTU_TEMP_CALIB_OFFSET_2;
    }

    output[idx] = (mE_t)( (foo - calibConst ) * 100 );
}

/**
 * format raw to byte - currently unimplemented
 */
void temp_fmtDef2Byte(
						const void* src,
							  void* dst,
						   uint32_t idx
					)
{}
