/*
*************************************************************************
* Ralink Technology Corporation
* 5F., No. 5, Taiyuan 1st St., Jhubei City,
* Hsinchu County 302,
* Taiwan, R.O.C.
*
* (c) Copyright 2012, Ralink Technology Corporation
*
* This program is free software; you can redistribute it and/or modify  *
* it under the terms of the GNU General Public License as published by  *
* the Free Software Foundation; either version 2 of the License, or     *
* (at your option) any later version.                                   *
*                                                                       *
* This program is distributed in the hope that it will be useful,       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of        *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
* GNU General Public License for more details.                          *
*                                                                       *
* You should have received a copy of the GNU General Public License     *
* along with this program; if not, write to the                         *
* Free Software Foundation, Inc.,                                       *
* 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
*                                                                       *
*************************************************************************/

#include "include/rtbth_dbg.h"
#include "rtbt_ctrl.h"
#include "rtbt_osabl.h"
#include "rtbth_3298.h"
#include <linux/device.h>
#include <linux/device/class.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/module.h>

#define VERSION "4.0.0"

MODULE_AUTHOR("Ralink Tech & Ry.");
MODULE_DESCRIPTION("Support for Ralink Bluetooth RT3290 Cards");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);

static struct class *deviceClass;
static dev_t mainDevice = 0;

static struct rtbt_dev_entry *rtbt_pci_dev_list = NULL;


#if LINUX_VERSION_CODE < KERNEL_VERSION(6, 2, 0)
#define KClassCreate(x) class_create(THIS_MODULE, x)
#else
#define KClassCreate class_create
#endif


static int __init rtbth_init(void)
{
	struct rtbt_dev_entry *ent;

	DebugPrint(TRACE, DBG_INIT, "--->%s()\n", __FUNCTION__);
	

#ifdef RT3298
	ent = rtbt_3298_init();
#endif // RT3298 //

	if (ent) {
		rtbt_pci_dev_list = ent;
		ral_os_register(rtbt_pci_dev_list);
	}

	
	mainDevice = MKDEV(192, 0);
	register_chrdev_region(mainDevice, 1, "rtBth");

	deviceClass = KClassCreate("RtClass");
	if (IS_ERR(deviceClass)) {
		pr_err("Unable to allocate class for module");
		goto byeClass;
	}

	if (IS_ERR(device_create(deviceClass, NULL, mainDevice, NULL,
				 "rtbth"))) {
		pr_err("Unable to create rtbth device!");
		goto byeDevice;
	}
	
	DebugPrint(TRACE, DBG_INIT, "<---%s()\n", __FUNCTION__);
	return 0;
byeDevice:
	class_destroy(deviceClass);
byeClass:
	unregister_chrdev_region(mainDevice, 1);
	return -1;
}

static void __exit rtbth_exit(void)
{
	DebugPrint(TRACE, DBG_INIT, "--->%s()\n", __FUNCTION__);
	if (rtbt_pci_dev_list)
		ral_os_unregister(rtbt_pci_dev_list);
#ifdef RT3298
	rtbt_3298_exit();
#endif // RT3298 //
	device_destroy(deviceClass, mainDevice);
	class_destroy(deviceClass);
	unregister_chrdev_region(mainDevice, 1);

	DebugPrint(TRACE, DBG_INIT, "<---%s()\n", __FUNCTION__);
}

module_init(rtbth_init);
module_exit(rtbth_exit);
