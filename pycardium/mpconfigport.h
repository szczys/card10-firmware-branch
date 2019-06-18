/* Hardware Name */
#define MICROPY_HW_BOARD_NAME "card10"
#define MICROPY_HW_MCU_NAME "max32665"

/* MicroPython Config Options */

/*
 * Right now, we do not support importing external modules
 * though this might change in the future.
 */
#define MICROPY_ENABLE_EXTERNAL_IMPORT  (0)

#define MICROPY_ENABLE_DOC_STRING           (1)
#define MICROPY_ENABLE_GC                   (1)
#define MICROPY_FLOAT_IMPL                  (MICROPY_FLOAT_IMPL_FLOAT)
#define MICROPY_HELPER_REPL                 (1)
#define MICROPY_LONGINT_IMPL                (MICROPY_LONGINT_IMPL_LONGLONG)
#define MICROPY_PY_BUILTINS_HELP            (1)
#define MICROPY_PY_BUILTINS_HELP_MODULES    (1)
#define MICROPY_PY_UTIME_MP_HAL             (1)

/* Modules */
#define MODULE_UTIME_ENABLED                (1)

/*
 * This port is intended to be 32-bit, but unfortunately, int32_t for
 * different targets may be defined in different ways - either as int
 * or as long. This requires different printf formatting specifiers
 * to print such value. So, we avoid int32_t and use int directly.
 */
#define UINT_FMT "%u"
#define INT_FMT "%d"
typedef int mp_int_t;       /* must be pointer size */
typedef unsigned mp_uint_t; /* must be pointer size */

typedef long mp_off_t;

/*
 * Make a pointer to RAM callable (eg set lower bit for Thumb code)
 * (This scheme won't work if we want to mix Thumb and normal ARM code.)
 */
#define MICROPY_MAKE_POINTER_CALLABLE(p) ((void*)((mp_uint_t)(p) | 1))

/* We need to provide a declaration/definition of alloca() */
#include <alloca.h>

/* TODO: Document this */
#define MP_STATE_PORT MP_STATE_VM

/* For some reason, we need to define readline history manually */
#define MICROPY_PORT_ROOT_POINTERS \
    const char *readline_hist[16];
