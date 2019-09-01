#include "epicardium.h"

#include "py/obj.h"
#include "py/objint.h"
#include "py/objstr.h"
#include "py/runtime.h"

#include <stdio.h>

union disp_framebuffer fb;

static uint16_t rgb888_to_rgb565(uint8_t *bytes)
{
	return ((bytes[0] & 0b11111000) << 8) | ((bytes[1] & 0b11111100) << 3) |
	       (bytes[2] >> 3);
}

static uint16_t get_color(mp_obj_t color_in)
{
	if (mp_obj_get_int(mp_obj_len(color_in)) < 3) {
		mp_raise_ValueError("color must have 3 elements");
	}

	uint8_t red = mp_obj_get_int(
		mp_obj_subscr(color_in, mp_obj_new_int(0), MP_OBJ_SENTINEL)
	);
	uint8_t green = mp_obj_get_int(
		mp_obj_subscr(color_in, mp_obj_new_int(1), MP_OBJ_SENTINEL)
	);
	uint8_t blue = mp_obj_get_int(
		mp_obj_subscr(color_in, mp_obj_new_int(2), MP_OBJ_SENTINEL)
	);
	uint8_t colors[3] = { red, green, blue };
	return rgb888_to_rgb565(colors);
}

/* print something on the display */
static mp_obj_t mp_display_print(size_t n_args, const mp_obj_t *args)
{
	if (!mp_obj_is_str_or_bytes(args[0])) {
		mp_raise_TypeError("input text must be a string");
	}
	GET_STR_DATA_LEN(args[0], print, print_len);
	uint32_t posx = mp_obj_get_int(args[1]);
	uint32_t posy = mp_obj_get_int(args[2]);
	uint32_t fg   = get_color(args[3]);
	uint32_t bg   = get_color(args[4]);
	int res = epic_disp_print(posx, posy, (const char *)print, fg, bg);
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(
	display_print_obj, 5, 5, mp_display_print
);

/* print something on the display */
static mp_obj_t mp_display_print_adv(size_t n_args, const mp_obj_t *args)
{
	if (!mp_obj_is_str_or_bytes(args[0])) {
		mp_raise_TypeError("input text must be a string");
	}
	GET_STR_DATA_LEN(args[0], print, print_len);
	uint32_t posx    = mp_obj_get_int(args[1]);
	uint32_t posy    = mp_obj_get_int(args[2]);
	uint32_t fg      = get_color(args[3]);
	uint32_t bg      = get_color(args[4]);
	uint8_t fontName = mp_obj_get_int(args[5]);
	int res          = epic_disp_print_adv(
                fontName, posx, posy, (const char *)print, fg, bg
	);
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(
	display_print_adv_obj, 6, 6, mp_display_print_adv
);

/* draw pixel on the display */
static mp_obj_t mp_display_pixel(size_t n_args, const mp_obj_t *args)
{
	uint16_t x   = mp_obj_get_int(args[0]);
	uint16_t y   = mp_obj_get_int(args[1]);
	uint16_t col = get_color(args[2]);

	//TODO: Move sanity checks to epicardium
	if (x > 160 || x < 0) {
		mp_raise_ValueError("X-Coords have to be 0 < x < 160");
	}

	if (y > 80 || y < 0) {
		mp_raise_ValueError("Y-Coords have to be 0 < y < 80");
	}

	int res = epic_disp_pixel(x, y, col);
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(
	display_pixel_obj, 3, 3, mp_display_pixel
);

/* set display backlight brightness */
static mp_obj_t mp_display_backlight(size_t n_args, const mp_obj_t *args)
{
	uint16_t brightness = mp_obj_get_int(args[0]);

	int res = epic_disp_backlight(brightness);
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(
	display_backlight_obj, 1, 1, mp_display_backlight
);

/* draw line on the display */
static mp_obj_t mp_display_line(size_t n_args, const mp_obj_t *args)
{
	uint16_t xs  = mp_obj_get_int(args[0]);
	uint16_t ys  = mp_obj_get_int(args[1]);
	uint16_t xe  = mp_obj_get_int(args[2]);
	uint16_t ye  = mp_obj_get_int(args[3]);
	uint16_t col = get_color(args[4]);
	uint16_t ls  = mp_obj_get_int(args[5]);
	uint16_t ps  = mp_obj_get_int(args[6]);

	//TODO: Move sanity checks to epicardium
	if (xs > 160 || xs < 0 || xe > 160 || xe < 0) {
		mp_raise_ValueError("X-Coords have to be 0 < x < 160");
	}

	if (ys > 80 || ys < 0 || ye > 80 || ye < 0) {
		mp_raise_ValueError("Y-Coords have to be 0 < x < 80");
	}

	if (ls > 1 || ls < 0) {
		mp_raise_ValueError("Line style has to be 0 or 1");
	}

	int res = epic_disp_line(xs, ys, xe, ye, col, ls, ps);
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(
	display_line_obj, 7, 7, mp_display_line
);

/* draw rectangle on the display */
static mp_obj_t mp_display_rect(size_t n_args, const mp_obj_t *args)
{
	uint16_t xs  = mp_obj_get_int(args[0]);
	uint16_t ys  = mp_obj_get_int(args[1]);
	uint16_t xe  = mp_obj_get_int(args[2]);
	uint16_t ye  = mp_obj_get_int(args[3]);
	uint16_t col = get_color(args[4]);
	uint16_t fs  = mp_obj_get_int(args[5]);
	uint16_t ps  = mp_obj_get_int(args[6]);

	//TODO: Move sanity checks to epicardium
	if (xs > 160 || xs < 0 || xe > 160 || xe < 0) {
		mp_raise_ValueError("X-Coords have to be 0 < x < 160");
	}

	if (ys > 80 || ys < 0 || ye > 80 || ye < 0) {
		mp_raise_ValueError("Y-Coords have to be 0 < x < 80");
	}

	if (fs > 1 || fs < 0) {
		mp_raise_ValueError("Fill style has to be 0 or 1");
	}

	int res = epic_disp_rect(xs, ys, xe, ye, col, fs, ps);
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(
	display_rect_obj, 7, 7, mp_display_rect
);

/* draw rectangle on the display */
static mp_obj_t mp_display_circ(size_t n_args, const mp_obj_t *args)
{
	uint16_t x   = mp_obj_get_int(args[0]);
	uint16_t y   = mp_obj_get_int(args[1]);
	uint16_t rad = mp_obj_get_int(args[2]);
	uint16_t col = get_color(args[3]);
	uint16_t fs  = mp_obj_get_int(args[4]);
	uint16_t ps  = mp_obj_get_int(args[5]);

	if (fs > 1 || fs < 0) {
		mp_raise_ValueError("Fill style has to be 0 or 1");
	}

	int res = epic_disp_circ(x, y, rad, col, fs, ps);
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(
	display_circ_obj, 6, 6, mp_display_circ
);

/* clear the display */
static mp_obj_t mp_display_clear(mp_obj_t col)
{
	uint16_t color = get_color(col);
	int res        = epic_disp_clear(color);
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(display_clear_obj, mp_display_clear);

static mp_obj_t mp_display_update()
{
	int res = epic_disp_update();
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(display_update_obj, mp_display_update);

static const uint8_t hackaday[1220] = { 1, 224, 0, 0, 0, 0, 0, 240, 0, 0, 0, 0, 0, 0, 0, 0,
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


static mp_obj_t mp_display_setbuff(size_t n_args, const mp_obj_t *args)
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
	display_setbuff_obj, 4, 4, mp_display_setbuff
);

static mp_obj_t mp_display_rainbowbuff(size_t n_args, const mp_obj_t *args)
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
	display_rainbowbuff_obj, 1, 1, mp_display_rainbowbuff
);

static mp_obj_t mp_display_clrbuff()
{ 
  for (int y = 0; y < DISP_HEIGHT; y++) {
    for (int x = 0; x < DISP_WIDTH; x++) {
      fb.fb[y][x][0] = 0x00;
      fb.fb[y][x][1] = 0x00;     
    }
  }
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(display_clrbuff_obj, mp_display_clrbuff);

static mp_obj_t mp_display_showbuff()
{
  int res = epic_disp_framebuffer(&fb);
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(display_showbuff_obj, mp_display_showbuff);



#define ROW_OFFSET 9
static mp_obj_t mp_display_wrencher()
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
static MP_DEFINE_CONST_FUN_OBJ_0(display_wrencher_obj, mp_display_wrencher);

static mp_obj_t mp_display_open()
{
	int res = epic_disp_open();
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(display_open_obj, mp_display_open);

static mp_obj_t mp_display_close()
{
	int res = epic_disp_close();
	if (res < 0) {
		mp_raise_OSError(-res);
	}
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(display_close_obj, mp_display_close);

/* The globals table for this module */
static const mp_rom_map_elem_t display_module_globals_table[] = {
	{ MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_sys_display) },
	{ MP_ROM_QSTR(MP_QSTR_open), MP_ROM_PTR(&display_open_obj) },
	{ MP_ROM_QSTR(MP_QSTR_close), MP_ROM_PTR(&display_close_obj) },
	{ MP_ROM_QSTR(MP_QSTR_print), MP_ROM_PTR(&display_print_obj) },
	{ MP_ROM_QSTR(MP_QSTR_print_adv), MP_ROM_PTR(&display_print_adv_obj) },
	{ MP_ROM_QSTR(MP_QSTR_pixel), MP_ROM_PTR(&display_pixel_obj) },
	{ MP_ROM_QSTR(MP_QSTR_backlight), MP_ROM_PTR(&display_backlight_obj) },
	{ MP_ROM_QSTR(MP_QSTR_line), MP_ROM_PTR(&display_line_obj) },
	{ MP_ROM_QSTR(MP_QSTR_rect), MP_ROM_PTR(&display_rect_obj) },
	{ MP_ROM_QSTR(MP_QSTR_circ), MP_ROM_PTR(&display_circ_obj) },
	{ MP_ROM_QSTR(MP_QSTR_clear), MP_ROM_PTR(&display_clear_obj) },
	{ MP_ROM_QSTR(MP_QSTR_update), MP_ROM_PTR(&display_update_obj) },
  { MP_ROM_QSTR(MP_QSTR_setbuff), MP_ROM_PTR(&display_setbuff_obj) },
  { MP_ROM_QSTR(MP_QSTR_rainbowbuff), MP_ROM_PTR(&display_rainbowbuff_obj) },
  { MP_ROM_QSTR(MP_QSTR_clrbuff), MP_ROM_PTR(&display_clrbuff_obj) },
  { MP_ROM_QSTR(MP_QSTR_showbuff), MP_ROM_PTR(&display_showbuff_obj) },
  { MP_ROM_QSTR(MP_QSTR_wrencher), MP_ROM_PTR(&display_wrencher_obj) },
};
static MP_DEFINE_CONST_DICT(
	display_module_globals, display_module_globals_table
);

const mp_obj_module_t display_module = {
	.base    = { &mp_type_module },
	.globals = (mp_obj_dict_t *)&display_module_globals,
};

/* clang-format off */
MP_REGISTER_MODULE(MP_QSTR_sys_display, display_module, MODULE_DISPLAY_ENABLED);
