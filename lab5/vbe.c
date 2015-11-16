#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>

#include "vbe.h"
#include "lmlib.h"

#define LINEAR_MODEL_BIT 14

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)

int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {

	struct reg86u reg86;
	phys_bytes buf = vmi_p;

	reg86.u.b.intno = BIOS_VIDEO_INT;

	reg86.u.w.ax = VBE_MODE_INFO;
	reg86.u.w.cx = mode;

	reg86.u.w.es = PB2BASE(buf);
	reg86.u.w.di = PB2OFF(buf);

	if (sys_int86(&reg86) != OK) {
		printf("\tvg_init(): vbe_get_mode_info(): sys_int86() failed. \n");
		return 1;
	}

	return 0;

	return 1;
}

