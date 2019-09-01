#include "epicardium.h"

#include "py/obj.h"
#include "py/objint.h"
#include "py/objstr.h"
#include "py/runtime.h"

#include <stdio.h>

union disp_framebuffer fb;

static const uint8_t hackaday[1220] = {
    1, 224, 0, 0, 0, 0, 0, 240, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 248, 0, 0, 0, 0, 3, 240, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 126, 0, 0, 0, 0, 7, 224,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0,
    0, 15, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    31, 0, 0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 31, 128, 0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 63, 128, 0, 0, 0, 63, 128, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 127, 128, 0,
    0, 0, 63, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    192, 127, 128, 0, 0, 0, 63, 224, 96, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 224, 255, 128, 0, 0, 0, 63, 240,
    224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 241, 255, 192,
    0, 0, 0, 127, 249, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 123, 255, 224, 0, 0, 0, 255, 255, 224, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 127, 255, 240, 0, 0, 1, 255, 255,
    192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 63, 255, 248, 0,
    0, 3, 255, 255, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    63, 255, 252, 7, 252, 7, 255, 255, 128, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 15, 255, 254, 31, 255, 143, 255, 254,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 255, 254, 127,
    255, 207, 255, 252, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 15, 252, 255, 255, 231, 254, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 7, 249, 255, 255, 243, 252, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 243, 255,
    255, 249, 248, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 231, 255, 255, 252, 240, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 111, 255, 255, 254, 64, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 255, 255, 254,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 255,
    255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 31, 255, 255, 255, 1, 192, 224, 120, 7, 240, 225, 224,
    248, 63, 224, 31, 30, 14, 0, 0, 31, 255, 255, 255, 129,
    192, 224, 252, 15, 248, 227, 193, 248, 63, 248, 63, 14,
    30, 0, 0, 63, 255, 255, 255, 129, 192, 224, 252, 31, 124,
    231, 129, 248, 63, 252, 63, 15, 60, 0, 0, 63, 135, 252,
    31, 129, 192, 224, 254, 60, 24, 239, 1, 252, 60, 60, 63,
    135, 184, 0, 0, 62, 3, 248, 15, 129, 225, 225, 222, 56,
    0, 238, 3, 220, 60, 30, 123, 131, 248, 0, 0, 62, 1, 240,
    15, 129, 255, 225, 206, 56, 0, 254, 3, 158, 60, 30, 123,
    195, 240, 0, 0, 60, 1, 240, 7, 193, 255, 227, 207, 56,
    0, 254, 7, 158, 60, 30, 115, 193, 224, 0, 0, 60, 3, 248,
    7, 193, 225, 227, 207, 56, 0, 254, 7, 158, 60, 30, 241,
    193, 224, 0, 0, 60, 7, 252, 7, 193, 192, 227, 255, 60,
    16, 247, 7, 255, 60, 28, 255, 224, 224, 0, 0, 60, 31, 255,
    7, 129, 192, 231, 255, 158, 60, 231, 143, 255, 60, 124,
    255, 224, 224, 0, 0, 62, 63, 255, 199, 129, 192, 231, 255,
    159, 252, 227, 207, 255, 63, 249, 255, 240, 224, 0, 0, 62,
    127, 255, 207, 129, 192, 239, 3, 207, 248, 227, 238, 7,
    191, 241, 192, 240, 224, 0, 0, 63, 255, 191, 255, 129,
    192, 239, 3, 195, 224, 225, 254, 7, 191, 193, 192, 240,
    224, 0, 0, 31, 255, 159, 255, 128, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 31, 255, 31, 255, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 223, 255, 31, 255, 96,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 207, 255,
    95, 254, 112, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 239, 255, 255, 254, 248, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 7, 231, 255, 255, 252, 252, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 243, 255, 255, 249,
    254, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 255, 249,
    255, 255, 243, 255, 252, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 15, 255, 252, 255, 255, 231, 255, 255, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 31, 255, 252, 255, 255, 231, 255, 255,
    128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 63, 255, 248, 255,
    255, 227, 255, 255, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    127, 255, 240, 253, 255, 225, 255, 255, 192, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 123, 255, 224, 125, 243, 192, 255,
    251, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 241, 255, 192,
    48, 97, 128, 63, 241, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 224, 255, 128, 0, 0, 0, 63, 224, 224, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 192, 127, 128, 0, 0, 0, 63, 224, 96,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 128, 0, 0, 0,
    63, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 128,
    0, 0, 0, 63, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    31, 128, 0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 31, 0, 0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 62, 0, 0, 0, 0, 15, 128, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 126, 0, 0, 0, 0, 7, 224, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 248, 0, 0, 0, 0, 3, 240,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 224, 0, 0, 0, 0,
    0, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static const char binbands[72][2] = {
    {224, 0}, {224, 160}, {225, 64}, {225, 224},
    {226, 160}, {227, 64}, {227, 224}, {228, 128},
    {229, 64}, {229, 224}, {230, 128}, {231, 32},
    {231, 32}, {207, 32}, {191, 32}, {167, 32},
    {151, 32}, {127, 32}, {103, 32}, {87, 32},
    {63, 32}, {47, 32}, {23, 32}, {7, 32},
    {7, 32}, {7, 34}, {7, 37}, {7, 39},
    {7, 42}, {7, 44}, {7, 47}, {7, 50},
    {7, 52}, {7, 55}, {7, 57}, {7, 60},
    {7, 60}, {6, 156}, {5, 252}, {5, 92},
    {4, 156}, {3, 252}, {3, 92}, {2, 188},
    {1, 252}, {1, 92}, {0, 188}, {0, 28},
    {0, 28}, {16, 28}, {40, 28}, {56, 28},
    {80, 28}, {96, 28}, {120, 28}, {144, 28},
    {160, 28}, {184, 28}, {200, 28}, {224, 28},
    {224, 28}, {224, 25}, {224, 23}, {224, 20},
    {224, 18}, {224, 15}, {224, 12}, {224, 10},
    {224, 7}, {224, 5}, {224, 2}, {224, 0}
    };


static mp_obj_t mp_displaybuffer_setbuff(size_t n_args, const mp_obj_t *args)
{ 
	uint16_t x   = mp_obj_get_int(args[0]);
	uint16_t y   = mp_obj_get_int(args[1]);
	uint16_t msb = mp_obj_get_int(args[2]);
	uint16_t lsb = mp_obj_get_int(args[3]);

	if (x > 159 || x < 0) {
		mp_raise_ValueError("X-Coords have to be 0 < x < 160");
	}

	if (y > 79 || y < 0) {
		mp_raise_ValueError("Y-Coords have to be 0 < y < 80");
	}

  fb.fb[y][x][0] = msb;
  fb.fb[y][x][1] = lsb;     

	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(
	displaybuffer_setbuff_obj, 4, 4, mp_displaybuffer_setbuff
);

static mp_obj_t mp_displaybuffer_rainbowbuff(size_t n_args, const mp_obj_t *args)
{
	uint16_t offset = mp_obj_get_int(args[0]);
	if (offset > 71 || offset < 0) {
		mp_raise_ValueError("Offset must be 0 < offset < 72");
	}
  for (int y = 0; y < DISP_HEIGHT; y++) {
    for (int x = 0; x < DISP_WIDTH; x++) {
      fb.fb[y][x][0] = binbands[(x+offset)%72][0];
      fb.fb[y][x][1] = binbands[(x+offset)%72][1];     
    }
  }
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(
	displaybuffer_rainbowbuff_obj, 1, 1, mp_displaybuffer_rainbowbuff
);

static mp_obj_t mp_displaybuffer_clrbuff()
{ 
  for (int y = 0; y < DISP_HEIGHT; y++) {
    for (int x = 0; x < DISP_WIDTH; x++) {
      fb.fb[y][x][0] = 0x00;
      fb.fb[y][x][1] = 0x00;     
    }
  }
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(displaybuffer_clrbuff_obj, mp_displaybuffer_clrbuff);

static mp_obj_t mp_displaybuffer_showbuff()
{
  int res = epic_disp_framebuffer(&fb);
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(displaybuffer_showbuff_obj, mp_displaybuffer_showbuff);



#define ROW_OFFSET 9
static mp_obj_t mp_displaybuffer_wrencher()
{
  for (int y = 0; y < 61; y++) {
    for (int x = 0; x < DISP_WIDTH; x++) {
      int unpackBitCount = (y*160) + x;
      int unpackIdx = unpackBitCount / 8;
      int unpackBit = unpackBitCount % 8;
      if (hackaday[1219-unpackIdx] & 1<<unpackBit) {
        fb.fb[y+ROW_OFFSET][x][0] = 0xFF;
        fb.fb[y+ROW_OFFSET][x][1] = 0xFF;
      }
    }
  }
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(displaybuffer_wrencher_obj, mp_displaybuffer_wrencher);

static mp_obj_t mp_displaybuffer_open()
{
	int res = epic_disp_open();
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(displaybuffer_open_obj, mp_displaybuffer_open);

static mp_obj_t mp_displaybuffer_close()
{
	int res = epic_disp_close();
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(displaybuffer_close_obj, mp_displaybuffer_close);

/* The globals table for this module */
static const mp_rom_map_elem_t displaybuffer_module_globals_table[] = {
	{ MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_sys_displaybuffer) },
	{ MP_ROM_QSTR(MP_QSTR_open), MP_ROM_PTR(&displaybuffer_open_obj) },
	{ MP_ROM_QSTR(MP_QSTR_close), MP_ROM_PTR(&displaybuffer_close_obj) },
  { MP_ROM_QSTR(MP_QSTR_setbuff), MP_ROM_PTR(&displaybuffer_setbuff_obj) },
  { MP_ROM_QSTR(MP_QSTR_rainbowbuff), MP_ROM_PTR(&displaybuffer_rainbowbuff_obj) },
  { MP_ROM_QSTR(MP_QSTR_clrbuff), MP_ROM_PTR(&displaybuffer_clrbuff_obj) },
  { MP_ROM_QSTR(MP_QSTR_showbuff), MP_ROM_PTR(&displaybuffer_showbuff_obj) },
  { MP_ROM_QSTR(MP_QSTR_wrencher), MP_ROM_PTR(&displaybuffer_wrencher_obj) },
};
static MP_DEFINE_CONST_DICT(
	displaybuffer_module_globals, displaybuffer_module_globals_table
);

const mp_obj_module_t displaybuffer_module = {
	.base    = { &mp_type_module },
	.globals = (mp_obj_dict_t *)&displaybuffer_module_globals,
};

/* clang-format off */
MP_REGISTER_MODULE(MP_QSTR_sys_displaybuffer, displaybuffer_module, MODULE_DISPLAYBUFFER_ENABLED);
