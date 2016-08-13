/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : PWR_Manager.h
**     Project     : HEXIWEAR_OLED
**     Processor   : MK64FN1M0VDC12
**     Component   : fsl_power_manager
**     Version     : Component 1.2.0, Driver 01.00, CPU db: 3.00.000
**     Repository  : KSDK 1.2.0
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-11-27, 13:18, # CodeGen: 19
**     Contents    :
**         POWER_SYS_Init                           - power_manager_error_code_t POWER_SYS_Init(power_manager_user_config_t const...
**         POWER_SYS_Deinit                         - power_manager_error_code_t POWER_SYS_Deinit(void);
**         POWER_SYS_SetMode                        - power_manager_error_code_t POWER_SYS_SetMode(uint8_t...
**         POWER_SYS_GetLastMode                    - power_manager_error_code_t POWER_SYS_GetLastMode(uint8_t * powerModeIndexPtr);
**         POWER_SYS_GetLastModeConfig              - power_manager_error_code_t POWER_SYS_Ge...
**         POWER_SYS_GetCurrentMode                 - power_manager_modes_t POWER_SYS_GetCurrentMode(void);
**         POWER_SYS_GetErrorCallbackIndex          - uint8_t POWER_SYS_GetErrorCallbackIndex(void);
**         POWER_SYS_GetErrorCallback               - power_manager_callback_user_config_t* POWER_SYS_GetErrorCallback(void);
**         POWER_SYS_GetVeryLowPowerModeStatus      - bool POWER_SYS_GetVeryLowPowerModeStatus(void);
**         POWER_SYS_GetLowLeakageWakeupResetStatus - bool POWER_SYS_GetLowLeakageWakeupResetStatus(void);
**         POWER_SYS_GetAckIsolation                - bool POWER_SYS_GetAckIsolation(void);
**         POWER_SYS_ClearAckIsolation              - void POWER_SYS_ClearAckIsolation(void);
**         POWER_SYS_SetWakeupModule                - void POWER_SYS_SetWakeupModule(power_wakeup_module_t module,bool enable);
**         POWER_SYS_GetWakeupModuleFlag            - bool POWER_SYS_GetWakeupModuleFlag(power_wakeup_module_t module);
**         POWER_SYS_SetWakeupPin                   - void POWER_SYS_SetWakeupPin(power_wakeup_pin_t pin,llwu_external_pin_modes_t...
**         POWER_SYS_GetWakeupPinFlag               - bool POWER_SYS_GetWakeupPinFlag(power_wakeup_pin_t pin);
**         POWER_SYS_ClearWakeupPinFlag             - void POWER_SYS_ClearWakeupPinFlag(power_wakeup_pin_t pin);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file PWR_Manager.h
** @version 01.00
*/         
/*!
**  @addtogroup PWR_Manager_module PWR_Manager module documentation
**  @{
*/         
#ifndef __PWR_Manager_H
#define __PWR_Manager_H
/* MODULE PWR_Manager. */
/* Include inherited beans */
#include "GPIO.h"
#include "osa1.h"
#include "Cpu.h"
#include "fsl_power_manager.h"

/*! @brief Power manager configuration declaration */
extern const power_manager_user_config_t PWR_CFG_Run;
extern const power_manager_user_config_t PWR_CFG_Sleep;
    

/*! @brief Array of pointers to User configuration structures */
extern power_manager_user_config_t const * powerConfigsArr[];



/*! @brief Array of pointers to User defined static Callbacks configuration structures */
extern power_manager_callback_user_config_t * powerStaticCallbacksConfigsArr[];

  
#endif
/* ifndef __PWR_Manager_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

