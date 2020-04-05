#include "lvgl/lvgl.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_CK_OS_BATTERY_020
#define LV_ATTRIBUTE_IMG_CK_OS_BATTERY_020
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG_CK_OS_BATTERY_020 uint8_t ck_os_battery_020_map[] = {
  0x04, 0x02, 0xcc, 0xff, 	/*Color of index 0*/
  0x6c, 0xfe, 0x6c, 0xff, 	/*Color of index 1*/
  0xe4, 0xe6, 0xe4, 0xff, 	/*Color of index 2*/
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 3*/

  0x55, 0x5a, 0xaa, 0xaa, 0xa5, 0x55, 
  0x55, 0x6a, 0xaa, 0xaa, 0xa9, 0x55, 
  0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 
  0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 
  0xaa, 0xaa, 0x55, 0x55, 0xaa, 0xaa, 
  0xaa, 0xaa, 0x55, 0x55, 0xaa, 0xaa, 
  0xaa, 0xaa, 0x55, 0x55, 0xaa, 0xaa, 
  0xaa, 0xaa, 0x55, 0x55, 0xaa, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x50, 0x00, 0x00, 0x05, 0xaa, 
  0xaa, 0x50, 0x00, 0x00, 0x05, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 
};

const lv_img_dsc_t ck_os_battery_020 = {
  .header.always_zero = 0,
  .header.w = 24,
  .header.h = 32,
  .data_size = 208,
  .header.cf = LV_IMG_CF_INDEXED_2BIT,
  .data = ck_os_battery_020_map,
};
