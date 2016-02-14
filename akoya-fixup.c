/*
 * HID driver for Medion Akoya P2214T Notebooks
 * Copyright (c) 2015-2016 Hendrik Schumann <github@schumann.pw>
 * Heavily inspired by various other HID drivers that adjust the report
 * descriptor.
*/

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include <linux/hid.h>
#include <linux/module.h>
#include <linux/usb.h>

#include "hid-ids.h"

/*
 * The report descriptor of some Elan based keyboard devices specifies an
 * excessively large number of consumer usages (2^16), which is more than
 * HID_MAX_USAGES. This prevents proper parsing of the report descriptor,
 * and the keyboard is unusable as a result.
 *
 * This driver fixes the report descriptor for:
 * - USB ID 04F3:0400, Elan Touchpad / ITE Tech. Inc. ITE Device(8910)
 */

static __u8 *akoya_keyboard_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);

	if (intf->cur_altsetting->desc.bInterfaceNumber == 0) {
		/*
		 * Change usage maximum and logical maximum from 0xffff to
		 * 0x2fff, so they don't exceed HID_MAX_USAGES
		 * Hopefully this won't break other devices (tm)
		*/
		switch (hdev->product) {
		case USB_DEVICE_ID_ELAN_AKOYA_0400:
			if (*rsize >= 188
					&& rdesc[151] == 0xff && rdesc[152] == 0xff
					&& rdesc[156] == 0xff && rdesc[157] == 0xff) {
				rdesc[152] = rdesc[157] = 0x2f;
				hid_info(hdev, "fixing Medion Akoya USB keyboard report descriptor\n");
			}
			break;
		}
	}
	return rdesc;
}

static const struct hid_device_id akoya_keyboard_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_ELAN,
			USB_DEVICE_ID_ELAN_AKOYA_0400) },
	{ }
};
MODULE_DEVICE_TABLE(hid, akoya_keyboard_devices);

static struct hid_driver akoya_keyboard_driver = {
	.name = "akoya_keyboard",
	.id_table = akoya_keyboard_devices,
	.report_fixup = akoya_keyboard_report_fixup,
};

module_hid_driver(akoya_keyboard_driver);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hendrik Schumann");
MODULE_DESCRIPTION("Keyboard fixup module for Medion Akoya P2214T notebooks");
