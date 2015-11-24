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
	mmap_t map;

	if (lm_alloc(sizeof(vbe_mode_info_t), &map) == NULL) {
		printf("\tvg_init(): lm_alloc() failed \n");
		return 1;
	}

	reg86.u.b.intno = BIOS_VIDEO_INT;

	reg86.u.w.ax = VBE_MODE_INFO;
	reg86.u.w.cx = mode;

	reg86.u.w.es = PB2BASE(map.phys);
	reg86.u.w.di = PB2OFF(map.phys);

	if (sys_int86(&reg86) != OK) {
		printf("\tvbe_get_mode_info(): sys_int86() failed. \n");
		return 1;
	}

	switch (reg86.u.w.ax) {
	case VBE_FUNC_CALL_FAILED:
		printf("\tvg_init(): sys_int86() function call failed.\n");
		return 1;
		break;
	case VBE_FUNC_NOT_SUPPORTED:
		printf("\tvg_init(): sys_int86() function not supported.\n");
		return 2;
		break;
	case VBE_FUNC_INVALID_CUR_MODE:
		printf(
				"\tvg_init(): sys_int86() function invalid in current video mode.\n");
		return 3;
		break;
	}

	*vmi_p = *((vbe_mode_info_t *) map.virtual);

	lm_free(&map);

	return 0;
}

int vbe_get_controller_info() {
	vbe_controller_info_t * info;// = (vbe_controller_info_t *) malloc(sizeof(vbe_controller_info_t ));
	struct reg86u reg86;
	mmap_t map;

	if ((info = lm_alloc(sizeof(vbe_controller_info_t), &map)) == NULL) {
		printf("\tvbe_get_controller_info(): lm_alloc() failed \n");
		return 1;
	}

	info->VbeSignature[0] = 'V';
	info->VbeSignature[1] = 'B';
	info->VbeSignature[2] = 'E';
	info->VbeSignature[3] = '2';

	reg86.u.b.intno = BIOS_VIDEO_INT;

	reg86.u.w.ax = VBE_CTRL_INFO;

	reg86.u.w.es = PB2BASE(map.phys);
	reg86.u.w.di = PB2OFF(map.phys);

	if (sys_int86(&reg86) != OK) {
		printf("\tvbe_get_controller_info(): sys_int86() failed. \n");
		return 1;
	}

	switch (reg86.u.w.ax) {
	case VBE_FUNC_CALL_FAILED:
		printf(
				"\tvbe_get_controller_info(): sys_int86() function call failed.\n");
		return 1;
		break;
	case VBE_FUNC_NOT_SUPPORTED:
		printf(
				"\tvbe_get_controller_info(): sys_int86()  function not supported.\n");
		return 2;
		break;
	case VBE_FUNC_INVALID_CUR_MODE:
		printf(
				"\tvbe_get_controller_info():  sys_int86() function invalid in current video mode.\n");
		return 3;
		break;
	}


	printf("\tCapabilities:\n");

	if(info->Capabilities[0] & BIT(0))
		printf("\t\tDAC width is switchable to 8 bits per primary color.\n");

	else
		printf("\t\tDAC is fixed width, with 6 bits per primary color.\n");


	if(info->Capabilities[0] & BIT(1))
		printf("\t\tController is not VGA compatible.\n");

	else
		printf("\t\tController is VGA compatible.\n");


	if(info->Capabilities[0] & BIT(2))
		printf("\t\tWhen programming large blocks of information to the RAMDAC, use the blank bit in Function 09h.\n");

	else
		printf("\t\tNormal RAMDAC operation.\n");


	printf("\n");

	/*unsigned long *p =  << 16;
	unsigned short i = 0;
	while(*((short *)info.VideoModePtr + i) != -1){
		printf("0x%x\n", *((short *)info.VideoModePtr + i));
		i++;
	}*/

	printf("\t\tTotal memory: %dKB\n", info->TotalMemory*64);

	lm_free(&map);

	return 0;
}

