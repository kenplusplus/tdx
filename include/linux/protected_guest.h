/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Protected Guest (and Host) Capability checks
 *
 * Copyright (C) 2021 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 */

#ifndef _PROTECTED_GUEST_H
#define _PROTECTED_GUEST_H

#ifndef __ASSEMBLY__

#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/device.h>

#define PATTR_MEM_ENCRYPT		0	/* Encrypted memory */
#define PATTR_HOST_MEM_ENCRYPT		1	/* Host encrypted memory */
#define PATTR_GUEST_MEM_ENCRYPT		2	/* Guest encrypted memory */
#define PATTR_GUEST_PROT_STATE		3	/* Guest encrypted state */
#define PATTR_GUEST_UNROLL_STRING_IO	4	/* Unrolled string IO */
#define PATTR_GUEST_SHARED_MAPPING_INIT	5	/* Late shared mapping init*/
#define PATTR_GUEST_DEVICE_FILTER	6	/* Guest Device filter */
#define PATTR_GUEST_SECURE_TIME		7	/* Guest Secure Time */
#define PATTR_GUEST_CPUID_FILTER	8	/* Guest CPUID Filter */
#define PATTR_GUEST_RAND_LOOP		9	/* Hardware RNG must succeed */

/* 0x800 - 0x8ff reserved for AMD */
#define PATTR_SME			0x800
#define PATTR_SEV			0x801
#define PATTR_SEV_ES			0x802

/* 0x900 - 0x9ff reserved for Intel */
#define PATTR_GUEST_TDX			0x900

#ifdef CONFIG_ARCH_HAS_PROTECTED_GUEST

#include <asm/protected_guest.h>

#else	/* !CONFIG_ARCH_HAS_PROTECTED_GUEST */

static inline bool prot_guest_has(unsigned int attr) { return false; }

/*
 * prot_guest_authorized() - Used to get ARCH specific authorized status of
 *			     given device.
 * @dev - device structure
 * @dev_str - device search string (for PCI bus it is vendor:device, other
 *	      bus device may use dev_name(dev))
 *
 * Return True to allow the device or False to deny it.
 *
 */
static inline bool prot_guest_authorized(struct device *dev, char *dev_str)
{
	return dev->authorized;
}

#endif	/* CONFIG_ARCH_HAS_PROTECTED_GUEST */

#endif	/* __ASSEMBLY__ */

#endif	/* _PROTECTED_GUEST_H */
