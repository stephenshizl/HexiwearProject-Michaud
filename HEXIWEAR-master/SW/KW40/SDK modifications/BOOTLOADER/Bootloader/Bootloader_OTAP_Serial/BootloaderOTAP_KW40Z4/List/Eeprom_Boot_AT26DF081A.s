///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       12/Jan/2016  08:59:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\eeprom\Eeprom_Boot_AT26DF081A.c
//    Command line =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\eeprom\Eeprom_Boot_AT26DF081A.c
//        -D MCU_MKW40Z160 -D gEepromType_d=gEepromDevice_M25P80_c
//        --preprocess=cl
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\
//        -lC
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\
//        -lA
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\
//        --diag_suppress Pa039 -o
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\Obj\
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M0+ -e --fpu=None -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\OtapSerialBootloader\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\spi\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\eeprom\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\flash\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\include\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\include\cfg\
//        -On --c89
//    List file    =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\Eeprom_Boot_AT26DF081A.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__SystemLibrary", "DLib"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1


        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\eeprom\Eeprom_Boot_AT26DF081A.c
//    1 /*!
//    2 * Copyright (c) 2015, Freescale Semiconductor, Inc.
//    3 * All rights reserved.
//    4 *
//    5 * \file Eeprom_AT26DF081A.c
//    6 * This is the Source file for the AT26DF081A FLASH driver
//    7 *
//    8 * Redistribution and use in source and binary forms, with or without modification,
//    9 * are permitted provided that the following conditions are met:
//   10 *
//   11 * o Redistributions of source code must retain the above copyright notice, this list
//   12 *   of conditions and the following disclaimer.
//   13 *
//   14 * o Redistributions in binary form must reproduce the above copyright notice, this
//   15 *   list of conditions and the following disclaimer in the documentation and/or
//   16 *   other materials provided with the distribution.
//   17 *
//   18 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
//   19 *   contributors may be used to endorse or promote products derived from this
//   20 *   software without specific prior written permission.
//   21 *
//   22 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//   23 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//   24 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//   25 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
//   26 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//   27 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//   28 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//   29 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//   30 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//   31 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//   32 */
//   33 
//   34 
//   35 /*! *********************************************************************************
//   36 *************************************************************************************
//   37 * Include
//   38 *************************************************************************************
//   39 ********************************************************************************** */
//   40 #include "Eeprom_Boot.h"
//   41 
//   42 #if gEepromType_d == gEepromDevice_AT26DF081A_c
//   43 
//   44 #include "SPI.h"
//   45 
//   46 /*! *********************************************************************************
//   47 *************************************************************************************
//   48 * Private macros
//   49 *************************************************************************************
//   50 ********************************************************************************** */
//   51 
//   52 #define  EEPROM_WRSR            0x01
//   53 #define  EEPROM_RDSR            0x05
//   54 #define  EEPROM_READ            0x03
//   55 #define  EEPROM_READ_HF         0x0B
//   56 
//   57 #define  EEPROM_ERASE_4K        0x20
//   58 #define  EEPROM_ERASE_32K       0x52
//   59 #define  EEPROM_ERASE_64K       0xD8
//   60 #define  EEPROM_ERASE_ALL       0xC7
//   61 
//   62 #define  EEPROM_WRITE_ENABLE    0x06
//   63 #define  EEPROM_WRITE_DISABLE   0x04
//   64 #define  EEPROM_WRITE_BYTES     0x02
//   65 #define  EEPROM_WRITE_SEQ       0xAD
//   66 
//   67 #define  EEPROM_UNPROTECT       0x39
//   68 #define  EEPROM_READ_PROT_SECT  0x3C
//   69 
//   70 #define  EEPROM_POWER_DOWN      0xB9
//   71 #define  EEPROM_WAKE_UP         0xAB
//   72 
//   73 #define  EEPROM_BUSY_FLAG_MASK  0x01
//   74 #define  EEPROM_SPM_FLAG_MASK   0x40
//   75 
//   76 /* adress mask */
//   77 #define  ADDRESS_MASK 0x000000FF
//   78 
//   79 
//   80 /****************************** SPI MACROS ***********************************/
//   81 #define mEepromSpiInstance_c 0
//   82 
//   83 /******************************************************************************
//   84 *******************************************************************************
//   85 * Private Prototypes
//   86 *******************************************************************************
//   87 ******************************************************************************/
//   88 #if gEepromWriteWnable_d
//   89 static ee_err_t EEPROM_WriteSR(uint8_t status);
//   90 static ee_err_t EEPROM_PrepareForWrite(uint32_t NoOfBytes, uint32_t Addr);
//   91 static ee_err_t EEPROM_WritePage(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf);
//   92 #endif
//   93 static ee_err_t EEPROM_WaitForReady(void);
//   94 static uint8_t  EEPROM_ReadStatusReq(void);
//   95 static void     EEPROM_Command(uint8_t opCode, uint32_t Addr);
//   96 
//   97 
//   98 /*! *********************************************************************************
//   99 *************************************************************************************
//  100 * Private Memory Declarations
//  101 *************************************************************************************
//  102 ********************************************************************************** */
//  103 #if gEepromWriteWnable_d
//  104 static uint8_t mEepromEraseBitmap[32];
//  105 #endif
//  106 
//  107 
//  108 /*! *********************************************************************************
//  109 *************************************************************************************
//  110 * Public Functions
//  111 *************************************************************************************
//  112 ********************************************************************************** */
//  113 
//  114 /*****************************************************************************
//  115 *  EEPROM_Init
//  116 *
//  117 *  Initializes the EEPROM peripheral
//  118 *
//  119 *****************************************************************************/
//  120 ee_err_t EEPROM_Init(void)
//  121 {
//  122     ee_err_t retval;
//  123     spi_user_config_t config;
//  124 #if gEepromWriteWnable_d
//  125     uint32_t i;
//  126     
//  127     // Mark Flash as Unerased
//  128     for(i = 0; i < 32; i++)
//  129         mEepromEraseBitmap[i] = 0;
//  130 #endif
//  131     
//  132     config.busFrequencyKHz = 8000;
//  133     config.direction = kSpiMsbFirst;
//  134     config.phase = kSpiClockPhase_FirstEdge;
//  135     config.polarity = kSpiClockPolarity_ActiveHigh;
//  136     
//  137     spi_master_init(mEepromSpiInstance_c);
//  138     spi_master_configure_bus(mEepromSpiInstance_c, &config);
//  139     retval = EEPROM_WaitForReady();
//  140     if (retval != ee_ok)
//  141         return retval;
//  142 #if gEepromWriteWnable_d
//  143     /* Unprotect all sectors */
//  144     retval = EEPROM_WriteSR(0);
//  145 #endif
//  146     return retval;
//  147 }
//  148 
//  149 /*****************************************************************************
//  150 *  EEPROM_ChipErase
//  151 *
//  152 *  Erase all memory to 0xFF
//  153 *
//  154 *****************************************************************************/
//  155 ee_err_t EEPROM_ChipErase(void)
//  156 {
//  157     uint8_t cmd;
//  158     
//  159     while (EEPROM_isBusy());
//  160     
//  161     assert_cs();
//  162     cmd = EEPROM_WRITE_ENABLE;
//  163     spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
//  164     deassert_cs();
//  165     
//  166     assert_cs();
//  167     cmd = EEPROM_ERASE_ALL;
//  168     spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
//  169     deassert_cs();
//  170     
//  171     return ee_ok;
//  172 }
//  173 
//  174 /*****************************************************************************
//  175 *  EEPROM_EraseBlock
//  176 *
//  177 *  Erase a block of memory to 0xFF
//  178 *
//  179 *****************************************************************************/
//  180 ee_err_t EEPROM_EraseBlock(uint32_t Addr, uint32_t size)
//  181 {
//  182     uint8_t cmd[4];
//  183     
//  184     while (EEPROM_isBusy());
//  185     
//  186     switch (size)
//  187     {
//  188     case (4*1024):
//  189         cmd[0] = EEPROM_ERASE_4K;
//  190         break;
//  191     case (32*1024):
//  192         cmd[0] = EEPROM_ERASE_32K;
//  193         break;
//  194     case (64*1024):
//  195         cmd[0] = EEPROM_ERASE_64K;
//  196         break;
//  197     default:
//  198         return ee_error;
//  199     }
//  200     
//  201     cmd[1] = (Addr >> 16) & ADDRESS_MASK;
//  202     cmd[2] = (Addr >>  8) & ADDRESS_MASK;
//  203     cmd[3] = (Addr >>  0) & ADDRESS_MASK;
//  204     
//  205     assert_cs();
//  206     spi_master_transfer(mEepromSpiInstance_c, cmd, NULL, sizeof(cmd));
//  207     deassert_cs();
//  208 
//  209     return ee_ok;
//  210 }
//  211 
//  212 
//  213 /*****************************************************************************
//  214 *  EEPROM_WriteData_Seq
//  215 *
//  216 *  Writes a data buffer into EEPROM, one byte at a time.
//  217 *  No address is needed because the internal address counter will be used.
//  218 *
//  219 *  EEPROM_StartWriteData_Seq must be called before using this function.
//  220 *****************************************************************************/
//  221 #if gEepromWriteWnable_d
//  222 ee_err_t EEPROM_WriteData_Seq(uint32_t NoOfBytes, uint8_t *Outbuf)
//  223 {
//  224     
//  225     if (!(EEPROM_ReadStatusReq() & EEPROM_SPM_FLAG_MASK))
//  226         return ee_error;
//  227     
//  228     assert_cs();
//  229     spi_master_transfer(mEepromSpiInstance_c, Outbuf, NULL, NoOfBytes);
//  230     deassert_cs();
//  231 
//  232     return ee_ok;
//  233 }
//  234 #endif
//  235 
//  236 /*****************************************************************************
//  237 *  EEPROM_StartWriteData_Seq
//  238 *
//  239 *  Writes a data buffer into EEPROM, at a given address, one byte at a time
//  240 *  This function will set the SPM bit in the EEPROM's Status Register
//  241 *
//  242 *****************************************************************************/
//  243 #if gEepromWriteWnable_d
//  244 ee_err_t EEPROM_StartWriteData_Seq(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
//  245 {
//  246     ee_err_t retval;
//  247     
//  248     if (NoOfBytes == 0)
//  249         return ee_ok;
//  250     
//  251     while (EEPROM_isBusy());
//  252     
//  253     SPI_Send_byte(EEPROM_WRITE_ENABLE,DEASSERT_CS);
//  254     
//  255     EEPROM_Command(EEPROM_WRITE_SEQ,Addr);
//  256     SPI_Send_byte((uint8_t)(*Outbuf++),DEASSERT_CS);
//  257     
//  258     NoOfBytes--;
//  259     
//  260     retval = EEPROM_WriteData_Seq(NoOfBytes, Outbuf);
//  261     
//  262     SPI_Send_byte(EEPROM_WRITE_DISABLE,DEASSERT_CS);
//  263     return retval;
//  264 }
//  265 #endif
//  266 
//  267 /*****************************************************************************
//  268 *  EEPROM_WriteData
//  269 *
//  270 *  Writes a data buffer into EEPROM, at a given address
//  271 *
//  272 *****************************************************************************/
//  273 #if gEepromWriteWnable_d
//  274 ee_err_t EEPROM_WriteData(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
//  275 {
//  276     ee_err_t retval;
//  277     
//  278     if (NoOfBytes == 0)
//  279         return ee_ok;
//  280     
//  281     while (EEPROM_isBusy());
//  282     
//  283     retval = EEPROM_PrepareForWrite(NoOfBytes, Addr);
//  284     if (retval != ee_ok)
//  285         return retval;
//  286     
//  287     while ((Addr & 0xFF) + NoOfBytes > 0xFF)
//  288     {
//  289         uint32_t bytes = 0x100 - (Addr & 0xFF);
//  290         
//  291         retval = EEPROM_WritePage(bytes, Addr, Outbuf);
//  292         NoOfBytes -= bytes;
//  293         Addr += bytes;
//  294         Outbuf += bytes;
//  295         
//  296         if (retval != ee_ok)
//  297             return retval;
//  298     }
//  299     
//  300     retval = EEPROM_WritePage(NoOfBytes, Addr, Outbuf);
//  301     
//  302     return retval;
//  303 }
//  304 #endif
//  305 
//  306 /*****************************************************************************
//  307 *  EEPROM_ReadData
//  308 *
//  309 *  Reads a data buffer from EEPROM, from a given address
//  310 *
//  311 *****************************************************************************/
//  312 ee_err_t EEPROM_ReadData(uint16_t NoOfBytes, uint32_t Addr, uint8_t *inbuf)
//  313 {
//  314     while (EEPROM_isBusy());
//  315 
//  316     EEPROM_Command(EEPROM_READ,Addr);
//  317 
//  318     spi_master_transfer(mEepromSpiInstance_c, NULL, inbuf, NoOfBytes);
//  319     deassert_cs();
//  320 
//  321     return ee_ok;
//  322 }
//  323 
//  324 /*****************************************************************************
//  325 *  EEPROM_ReadStatusReq
//  326 *
//  327 *
//  328 *****************************************************************************/
//  329 uint8_t EEPROM_isBusy(void)
//  330 {
//  331     return (EEPROM_ReadStatusReq() & EEPROM_BUSY_FLAG_MASK);
//  332 }
//  333 
//  334 /*! *********************************************************************************
//  335 *************************************************************************************
//  336 * Private Functions
//  337 *************************************************************************************
//  338 ********************************************************************************** */
//  339 
//  340 /*****************************************************************************
//  341 *  EEPROM_ReadStatusReq
//  342 *
//  343 *
//  344 *****************************************************************************/
//  345 static uint8_t EEPROM_ReadStatusReq(void)
//  346 {
//  347     uint8_t cmd = EEPROM_RDSR;
//  348 
//  349     assert_cs();
//  350     spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
//  351     spi_master_transfer(mEepromSpiInstance_c, NULL, &cmd, sizeof(cmd));
//  352     deassert_cs();
//  353 
//  354     return cmd;
//  355 }
//  356 
//  357 /*****************************************************************************
//  358 *  EEPROM_WriteData
//  359 *
//  360 *  Writes a data buffer into the External Memory, at a given address
//  361 *
//  362 *****************************************************************************/
//  363 #if gEepromWriteWnable_d
//  364 static ee_err_t EEPROM_PrepareForWrite(uint32_t NoOfBytes, uint32_t Addr)
//  365 {
//  366     uint32_t i;
//  367     ee_err_t ret = ee_ok;
//  368     uint32_t startBlk, endBlk;
//  369     
//  370     // Obtain the block number
//  371     startBlk = Addr >> 12;
//  372     endBlk   = (Addr + NoOfBytes) >> 12;
//  373     
//  374     for(i = startBlk; i <= endBlk; i++)
//  375         if ( (mEepromEraseBitmap[i/8] & (1 << (i%8) ) ) == 0)
//  376         {
//  377             ret = EEPROM_EraseBlock(i * 4096, 4096);
//  378             if (ret != ee_ok)
//  379                 return ret;
//  380             
//  381             mEepromEraseBitmap[i/8] |= 1 << (i%8);
//  382             while (EEPROM_isBusy());
//  383         }
//  384     
//  385     return ret;
//  386 }
//  387 #endif
//  388 
//  389 /*****************************************************************************
//  390 *  EEPROM_WritePage
//  391 *
//  392 *  Writes maximum 256 bytes into a EEPROM page
//  393 *
//  394 *****************************************************************************/
//  395 #if gEepromWriteWnable_d
//  396 static ee_err_t EEPROM_WritePage(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
//  397 {
//  398     uint8_t cmd;
//  399 
//  400     if( NoOfBytes == 0 )
//  401         return ee_ok;
//  402     
//  403     while (EEPROM_isBusy());
//  404     
//  405     assert_cs();
//  406     cmd = EEPROM_WRITE_ENABLE;
//  407     spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
//  408     deassert_cs();
//  409 
//  410     assert_cs();
//  411     cmd = EEPROM_WRITE_BYTES;
//  412     spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
//  413     spi_master_transfer(mEepromSpiInstance_c, Outbuf, NULL, NoOfBytes);
//  414     deassert_cs();
//  415 
//  416     return ee_ok;
//  417 }
//  418 #endif
//  419 
//  420 /*****************************************************************************
//  421 *  EEPROM_WaitForReady
//  422 *
//  423 *
//  424 *****************************************************************************/
//  425 static ee_err_t EEPROM_WaitForReady(void)
//  426 {
//  427     volatile uint16_t wait = 0x400; // near 50 ms @ 50 us/cycle
//  428     
//  429     /* Bit   7    6    5    4   3:2   1      0
//  430     *      SPL  SPM  EPE  WPP  SWP  WEL  RDY/BSY
//  431     */
//  432     
//  433     while ((EEPROM_ReadStatusReq() & EEPROM_BUSY_FLAG_MASK) && (wait !=0) )
//  434     {
//  435         wait--;
//  436     }
//  437     
//  438     if(wait != 0)
//  439     {
//  440         return ee_ok;
//  441     }
//  442     return ee_error;
//  443 }
//  444 
//  445 
//  446 /*****************************************************************************
//  447 *  EEPROM_Command
//  448 *
//  449 *
//  450 *****************************************************************************/
//  451 static void EEPROM_Command(uint8_t opCode, uint32_t Addr)
//  452 {
//  453     uint8_t cmd[4];
//  454 
//  455     cmd[0] = opCode;
//  456     cmd[1] = (uint8_t) ((Addr >> 16) & ADDRESS_MASK);
//  457     cmd[2] = (uint8_t) ((Addr >>  8) & ADDRESS_MASK);
//  458     cmd[3] = (uint8_t) ((Addr >>  0) & ADDRESS_MASK);
//  459     assert_cs();
//  460     spi_master_transfer(mEepromSpiInstance_c, cmd, NULL, sizeof(cmd));
//  461     /* CS will remain asserted to be able to send the data */
//  462 }
//  463 
//  464 
//  465 /*****************************************************************************
//  466 *  EEPROM_WriteSR
//  467 *
//  468 *
//  469 *****************************************************************************/
//  470 #if gEepromWriteWnable_d
//  471 static ee_err_t EEPROM_WriteSR(uint8_t status)
//  472 {
//  473     uint8_t cmd;
//  474 
//  475     while (EEPROM_isBusy());
//  476 
//  477     assert_cs();
//  478     cmd = EEPROM_WRITE_ENABLE;
//  479     spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
//  480     deassert_cs();
//  481 
//  482     assert_cs();
//  483     cmd = EEPROM_WRSR;
//  484     spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
//  485     spi_master_transfer(mEepromSpiInstance_c, &status, NULL, sizeof(status));
//  486     deassert_cs();
//  487 
//  488     return ee_ok;
//  489 }
//  490 #endif
//  491 
//  492 #endif /* gEepromDevice_AT26DF081A_c */
// 
//
// 
//
//
//Errors: none
//Warnings: none
