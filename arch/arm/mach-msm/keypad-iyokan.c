/* arch/arm/mach-msm/keypad-iyokan.c
 *
 * Copyright (C) [2010] Sony Ericsson Mobile Communications AB.
 * Adapted for SEMC 2011 devices by Michael Bestas (mikeioannina@gmail.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 */

#include <linux/mfd/pmic8058.h>
#include "keypad-semc.h"
/* iyokan GPIO slider - start */
#include <linux/gpio_event.h>
#include <linux/platform_device.h>
/* iyokan GPIO slider - end */

static const unsigned int pm8xxx_keymap[] = {
	KEY(0, 0, KEY_BACK),		/* BACK */
	KEY(0, 1, KEY_HOME),		/* HOME */
	KEY(0, 2, KEY_MENU),		/* MENU */
	KEY(0, 3, KEY_LEFTSHIFT),	/* SHIFT_LEFT */
	KEY(0, 7, KEY_W),		/* W */

	KEY(1, 0, KEY_CAMERA_FOCUS),	/* FOCUS */
	KEY(1, 1, KEY_CAMERA),		/* CAMERA */
	KEY(1, 2, KEY_VOLUMEDOWN),	/* VOLUME_DOWN */
	KEY(1, 3, KEY_VOLUMEUP),	/* VOLUME_UP */
	KEY(1, 4, KEY_Q),		/* Q */
	KEY(1, 5, KEY_G),		/* G */
	KEY(1, 6, KEY_U),		/* U */
	KEY(1, 7, KEY_S),		/* S */

	KEY(2, 0, KEY_LANGUAGE),	/* LANGUAGE_SWITCH */
	KEY(2, 3, KEY_F),		/* F */
	KEY(2, 5, KEY_LEFTBRACE),	/* AT */
	KEY(2, 6, KEY_N),		/* N */
	KEY(2, 7, KEY_O),		/* O */

	KEY(3, 0, KEY_SPACE),		/* SPACE */
	KEY(3, 1, KEY_A),		/* A */
	KEY(3, 2, KEY_B),		/* B */
	KEY(3, 3, KEY_RIGHTBRACE),	/* GRAVE */
	KEY(3, 4, KEY_R),		/* R */
	KEY(3, 6, KEY_J),		/* J */

	KEY(4, 0, KEY_ENTER),		/* ENTER */
	KEY(4, 1, KEY_D),		/* D */
	KEY(4, 3, KEY_Z),		/* Z */
	KEY(4, 4, KEY_C),		/* C */
	KEY(4, 5, KEY_Y),		/* Y */
	KEY(4, 7, KEY_L),		/* L */

	KEY(5, 0, KEY_DOT),		/* PERIOD */
	KEY(5, 1, KEY_APOSTROPHE),	/* APOSTROPHE */
	KEY(5, 2, KEY_COMMA),		/* COMMA */
	KEY(5, 3, KEY_E),		/* E */
	KEY(5, 4, KEY_T),		/* T */
	KEY(5, 5, KEY_H),		/* H */
	KEY(5, 6, KEY_I),		/* I */

	KEY(6, 0, KEY_UP),		/* DPAD_UP */
	KEY(6, 1, KEY_DOWN),		/* DPAD_DOWN */
	KEY(6, 4, KEY_LEFTALT),		/* ALT_LEFT */
	KEY(6, 5, KEY_COMPOSE),		/* PICTSYMBOLS */
	KEY(6, 6, KEY_K),		/* K */
	KEY(6, 7, KEY_BACKSPACE),	/* DEL */

	KEY(7, 2, KEY_RIGHT),		/* DPAD_RIGHT */
	KEY(7, 3, KEY_LEFT),		/* DPAD_LEFT */
	KEY(7, 4, KEY_V),		/* V */
	KEY(7, 5, KEY_X),		/* X */
	KEY(7, 6, KEY_M),		/* M */
	KEY(7, 7, KEY_P),		/* P */
};

static struct matrix_keymap_data pm8xxx_keymap_data = {
	.keymap_size	= ARRAY_SIZE(pm8xxx_keymap),
	.keymap		= pm8xxx_keymap,
};

struct pm8xxx_keypad_platform_data pm8xxx_keypad_data = {
	.input_name		= "pm8xxx-keypad",
	.input_phys_device	= "pm8xxx-keypad/input0",
	.num_rows		= 8,
	.num_cols		= 8,
	.rows_gpio_start	= PM8058_GPIO_PM_TO_SYS(8),
	.cols_gpio_start	= PM8058_GPIO_PM_TO_SYS(0),
	.debounce_ms		= 10,
	.scan_delay_ms		= 2,
	.row_hold_ns		= 122000,
	.wakeup			= 1,
	.keymap_data		= &pm8xxx_keymap_data,
};

/* iyokan GPIO slider - start */
#define SLIDE_CLOSED_N_GPIO	180

static struct gpio_event_direct_entry gpio_switch_map[] = {
	{SLIDE_CLOSED_N_GPIO, SW_LID},
};

static struct gpio_event_input_info gpio_switch_info = {
	.info.func = gpio_event_input_func,
	.flags = 0,
	.type = EV_SW,
	.keymap = gpio_switch_map,
	.keymap_size = ARRAY_SIZE(gpio_switch_map),
	.info.no_suspend = true,
};

static struct gpio_event_info *slider_info[] = {
	&gpio_switch_info.info,
};

static struct gpio_event_platform_data gpio_slider_data = {
	.name		= "gpio-slider",
	.info		= slider_info,
	.info_count	= ARRAY_SIZE(slider_info),
};

struct platform_device gpio_slider_device = {
	.name	= GPIO_EVENT_DEV_NAME,
	.id	= -1,
	.dev	= {
		.platform_data	= &gpio_slider_data,
	},
};

static int __init gpio_slider_device_init(void)
{
	return platform_device_register(&gpio_slider_device);
}

static void __exit gpio_slider_device_exit(void)
{
	platform_device_unregister(&gpio_slider_device);
}

module_init(gpio_slider_device_init);
module_exit(gpio_slider_device_exit);
/* iyokan GPIO slider - end */
