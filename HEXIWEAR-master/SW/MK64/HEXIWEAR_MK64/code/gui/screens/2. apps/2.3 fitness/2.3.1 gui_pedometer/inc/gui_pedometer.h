/**
 * \file gui_pedometer.h
 * \version 1.00
 * \brief this file contains pedometer app public objects
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#pragma once

#include "gui_driver.h"

typedef enum
{
    GUI_PEDOMETER_STATUS_SUCCESS,
    GUI_PEDOMETER_STATUS_ERROR

} gui_pedometer_status_t;

extern guiScreen_t
	pedometerScreen;

/**
 * initialize pedometer app GUI
 * @param param optional parameter
 */
void gui_pedometer_Init( void* param );

/**
 * create the pedometer GUI app tasks
 * @param param optional parameter
 */
void gui_pedometer_CreateTasks( void* param );

/**
 * destroy the pedometer GUI app tasks
 * @param param optional parameter
 */
void gui_pedometer_DestroyTasks( void* param );

/**
 * put the packet into pedometer app GUI queue
 * @param  packet data to be put into the queue
 * @return        status flag
 */
gui_pedometer_status_t gui_pedometer_QueueMsgPut( uint32_t* packet );
