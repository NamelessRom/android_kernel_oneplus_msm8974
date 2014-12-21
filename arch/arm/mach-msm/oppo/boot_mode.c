/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <asm/setup.h>

#include <linux/export.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/string.h>

#include <linux/boot_mode.h>

static int ftm_mode = MSM_BOOT_MODE__NORMAL;

int get_boot_mode(void)
{
	return ftm_mode;
}
EXPORT_SYMBOL(get_boot_mode);

static char boot_mode[16];
static int __init boot_mode_init(char *str)
{
	strcpy(boot_mode, str);

	pr_debug("%s: parse boot_mode is %s\n", __func__, boot_mode);

	if (!strcmp(boot_mode, "normal"))
		ftm_mode = MSM_BOOT_MODE__NORMAL;
	else if (!strcmp(boot_mode, "factory"))
		ftm_mode = MSM_BOOT_MODE__FACTORY;
	else if (!strcmp(boot_mode, "recovery"))
		ftm_mode = MSM_BOOT_MODE__RECOVERY;
	else if (!strcmp(boot_mode, "charger"))
		ftm_mode = MSM_BOOT_MODE__CHARGE;
	else
		ftm_mode = MSM_BOOT_MODE__NORMAL;

	printk(KERN_INFO "%s: parse ftm_mode is %d\n", __func__, ftm_mode);

	return 1;
}
__setup("androidboot.mode=", boot_mode_init);

char *get_boot_mode_str(void)
{
	return boot_mode;
}
EXPORT_SYMBOL(get_boot_mode_str);

static char pwron_event[16];
static int __init start_reason_init(char *str)
{
	strcpy(pwron_event, str);

	pr_debug("%s: parse poweron reason %s\n", __func__, pwron_event);

	return 1;
}
__setup("androidboot.startupmode=", start_reason_init);

char *get_start_reason(void)
{
	return pwron_event;
}
EXPORT_SYMBOL(get_start_reason);

