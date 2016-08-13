#pragma once

#include <stdint.h>
#include "gui_driver.h"

extern guiLabel_t
  bootloader_labelLoad;

extern guiLabel_t
	bootloader_labelTitle;

extern const uint8_t
  otap_coverScreen_bmp[ OLED_GRAM_SIZE+6 ],
  otap_mainScreen_bmp[ OLED_GRAM_SIZE+6 ],

  otap_select_kw40_bmp[4806],
  otap_select_mk64_bmp[4806],

  bootloader_failure_bmp[18438],
  bootloader_success_bmp[18438],

  bootloader_loadWhite_bmp[6278],
  bootloader_loadBlue_bmp[6278];

#define LOAD_IMG_NUM ( 2 )

extern guiImage_t
  bootloader_selectMK64,
  bootloader_selectKW40,

  bootloader_loadImg_white,
  bootloader_loadImg_blue,

  bootloader_success,
  bootloader_failure;

#define BOOT_IMAGE_FLAGS_ADDRESS ( 0xF0000 )
#define FLASH_WRITE_ALIGN ( 1 )

typedef struct __attribute__ ((__packed__))
{
  uint8_t  newBootImageAvailable[ FLASH_WRITE_ALIGN ];
  uint8_t  bootProcessCompleted[ FLASH_WRITE_ALIGN ];
  uint8_t  bootVersion[2];
  uint8_t  padding[4];

} bootInfo_t;
