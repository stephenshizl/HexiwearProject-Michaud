/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include "board.h"
#include "host_mcu_interface.h"
#include "fsl_interrupt_manager.h"

#include "HEXIWEAR_info.h"

#include "fsl_uart_driver.h"
#include "uartCom1.h"

#if defined( HEXIWEAR_DEBUG )
#include "uartCom2.h"
#endif

#include "host_mcu_interface_types.h"

#include "error.h"

/*! *********************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

static hostInterface_packet_t
  hostInterface_rxPacket;

static msg_queue_handler_t
  hostInterface_rxQueueHnd;

static hostInterface_rxState_t
  hostInterface_rxState = hostInterface_rxState_idle;

/**
 * message queues
 */
MSG_QUEUE_DECLARE( hostInterface_rxQueue, gHostInterface_msgNum, sizeof(hostInterface_packet_t) );

/**
 * tasks
 */
OSA_TASK_DEFINE( HostInterface_RxTask, gHostInterfaceRxTaskStackSize_c );

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

static void packetHandler(hostInterface_packet_t * pHostInterface_packet);
osa_status_t HostInterface_RxQueueMsgPut(hostInterface_packet_t * pHostInterface_packet);
static osa_status_t HostInterface_RxQueueMsgGet(hostInterface_packet_t * pHostInterface_packet);
static void HostInterface_RxTask(task_param_t param);
static void HostInterface_RxCallback(uint32_t instance, void *uartState);

/**
 * this function handle packet which is arrived through the comm interface
 */
static void packetHandler (
                            hostInterface_packet_t* self
                          )
{
  switch( self->type )
  {
    // buttons
    case packetType_button_1:
    case packetType_button_2:
    case packetType_button_3:
    case packetType_button_4:
    case packetType_slide:    {break;}

    // alert service
    case packetType_alertIn:  {break;}

    default: {}
  }
}

/**
 * initialize RX tasks and queues
 * @return  task initialization status
 */
osa_status_t HostInterface_RxInit()
{
  osa_status_t
    status;

  /**
   * set the interrupt priority levels
   */

  UART_DRV_InstallRxCallback( gHostInterface_instance, HostInterface_RxCallback, (uint8_t*)&hostInterface_rxPacket, NULL, true);
  NVIC_SetPriority( gHostInterface_irqn, gHostInterfaceIRQPriority_c );

#if defined( HEXIWEAR_DEBUG )
  NVIC_SetPriority( HEXIWEAR_DEBUG_IRQn , HEXIWEAR_DEBUG_PRIO );
#endif

  // Create Rx Message Queue
  hostInterface_rxQueueHnd = OSA_MsgQCreate (
                                              hostInterface_rxQueue,
                                              gHostInterface_msgNum,
                                              sizeof(hostInterface_packet_t) / sizeof(uint32_t)
                                            );

  if ( NULL == hostInterface_rxQueueHnd )
  {
    catch(3);
  }

#if defined( HEXIWEAR_DEBUG )
  vQueueAddToRegistry( hostInterface_rxQueueHnd, (signed char*)"RxQueue" );
#endif

  // Create Rx Task
  status = OSA_TaskCreate (
                            HostInterface_RxTask,
                            (uint8_t*)"HostInterface_RxTask",
                            gHostInterfaceRxTaskStackSize_c,
                            HostInterface_RxTask_stack,
                            gHostInterfaceRxPriority_c,
                            (task_param_t)NULL,
                            false,
                            &HostInterface_RxTask_task_handler
                          );

  if  ( kStatus_OSA_Success != status )
  {
    catch(3);
  }

  return (osa_status_t)status;
}


/**
 * interface state machine for UART callback
 */
static void HostInterface_RxCallback(
                                      uint32_t instance,
                                         void* uartState
                                    )
{
  static uint8_t
    byteCount;

  uart_state_t*
    state = (uart_state_t*)uartState;

  switch ( hostInterface_rxState )
  {
    case hostInterface_rxState_idle:  {
                                        if ( gHostInterface_startByte1 == hostInterface_rxPacket.start1 )
                                        {
                                            hostInterface_rxState++;
                                            state->rxBuff++;
                                        }

                                        break;
                                      }

    case hostInterface_rxState_headerReceived:  {
                                                  if  (
                                                               ( gHostInterface_startByte1 != hostInterface_rxPacket.start1 )
                                                        ||     ( gHostInterface_startByte2 != hostInterface_rxPacket.start2 )
                                                        || ( hostInterface_rxPacket.length >  gHostInterface_dataSize )
                                                      )
                                                  {
                                                    // return to idle state
                                                    hostInterface_rxState = hostInterface_rxState_idle;
                                                    // reset the RX buffer pointer
                                                    state->rxBuff         = (uint8_t*) &hostInterface_rxPacket;
                                                  }

                                                  else
                                                  {
                                                    // advance the buffer pointer
                                                    state->rxBuff++;

                                                    if ( 0 == hostInterface_rxPacket.length )
                                                    {
                                                      // advance to "wait-trailer-bit" state
                                                      hostInterface_rxState = hostInterface_rxState_trailerWait;
                                                    }

                                                    else
                                                    {
                                                      byteCount = 0;
                                                      // advance to "data-wait" state
                                                      hostInterface_rxState = hostInterface_rxState_dataWait;
                                                    }
                                                  }

                                                  break;
                                                }

      case hostInterface_rxState_dataWait:  {
                                              byteCount++;
                                              (state->rxBuff)++;

                                              // if we reached the byte-count
                                              if  ( hostInterface_rxPacket.length == byteCount )
                                              {
                                                // advance to "wait-trailer-bit" state
                                                hostInterface_rxState = hostInterface_rxState_trailerWait;
                                              }

                                              break;
                                            }

      case hostInterface_rxState_trailerWait: {
                                                if ( gHostInterface_trailerByte == *(state->rxBuff) )
                                                {

#if defined (gHostInterface_RxConfirmationEnable)

                                                  if ( packetType_OK == hostInterface_rxPacket.type )
                                                  {
                                                    // announce that OK packet is received successfully
                                                    HostInterface_EventConfirmPacketSet();
                                                  }

                                                  else

#endif

                                                  {
                                                    // else, put the packet into the RX queue
                                                    HostInterface_RxQueueMsgPut((hostInterface_packet_t *)&hostInterface_rxPacket);
                                                  }
                                                }

                                                // go back to the idle state
                                                hostInterface_rxState = hostInterface_rxState_idle;
                                                // reset the RX buffer pointer
                                                state->rxBuff = (uint8_t *) &hostInterface_rxPacket;
                                                break;
                                              }

      default:  {
                  hostInterface_rxState++;
                  state->rxBuff++;
                }
  }
}

/**
 *    This function puts a message to the end of the Tx message queue.
 *
 *    @param    pHostInterface_packet   Packet that will be placed into Tx message queue.
 *
 *    @return                          kStatus_OSA_Success  Message successfully put into the queue.
 *                                     kStatus_OSA_Error    Process fail.
 */

osa_status_t HostInterface_RxQueueMsgPut(
                                          hostInterface_packet_t* pHostInterface_packet
                                        )
{
  osa_status_t
    status = OSA_MsgQPut(hostInterface_rxQueueHnd, (hostInterface_packet_t *)pHostInterface_packet);

  if ( kStatus_OSA_Error == status )
  {
    catch(2);
  }
  return (osa_status_t)status;
}

/**
 *    This function gets a message from the head of the Tx message queue.
 *
 *    @param    pHostInterface_packet   Pointer to a memory to save the packet.
 *
 *    @return                          kStatus_OSA_Success  Message successfully obtained from the queue.
 *                                     kStatus_OSA_Error    Process fail.
 */

static osa_status_t HostInterface_RxQueueMsgGet (
                                                  hostInterface_packet_t* pHostInterface_packet
                                                )
{
  osa_status_t
    status = OSA_MsgQGet(hostInterface_rxQueueHnd, (hostInterface_packet_t *)pHostInterface_packet, gHostInterface_waitTimeout);

  if ( kStatus_OSA_Error == status )
  {
    catch(2);
  }
  return (osa_status_t)status;
}

/**
 *    Host MCU Interface Tx task
 *
 *    @param   param   initialData
 */
static void HostInterface_RxTask(
                                  task_param_t param
                                )
{
  hostInterface_packet_t
    tmpPkt;

  while (1)
  {
    osa_status_t
      status = HostInterface_RxQueueMsgGet( &tmpPkt );

    if ( kStatus_OSA_Success == status )
    {
#ifdef gHostInterface_TxConfirmationEnable
      // acknowledge the packet reception
      HostInterface_EventSendOkPacketSet();
#endif

      // handle the packet's content
      packetHandler(&tmpPkt);
    }
  }
}
