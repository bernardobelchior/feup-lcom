#include "test7.h"

int ser_test_conf(unsigned short base_addr) {

	char st, ier;

	//CHECK LCR

	if(serial_get_conf(base_addr,&st) != OK)
		return -1;


	printf("\tLCR :%d %d %d %d %d %d %d %d\n\n",(st & BIT(7)) >> 7,(st & BIT(6)) >> 6,(st & BIT(5)) >> 5,(st & BIT(4)) >> 4
			,(st & BIT(3)) >> 3,(st & BIT(2)) >> 2,(st & BIT(1)) >> 1,
			(st & BIT(0)));

	unsigned char word_length_select = (st & BIT(1)) | (st & BIT (0));

	printf("\tWord length: ");
	switch(word_length_select){
	case 0:
		printf("5");
		break;
	case 1:
		printf("6");
		break;
	case 2:
		printf("7");
		break;
	case 3:
		printf("8");
		break;
	}

	printf("\t\tNo. of stop bits: ");

	unsigned char stop_bits = (st & BIT(2)) >> 2;

	if(stop_bits == 0)
		printf("1\n");
	else if(stop_bits == 1)
		printf("2\n");


	unsigned char parity = ((st & BIT(5)) | (st & BIT(4)) | ((st & BIT(3)))) >> 3;

	printf("\tParity: ");

	if((parity & BIT(0)) == 0)
		printf("None");

	else if(parity == 1)
		printf("Odd");

	else if(parity == 3)
		printf("Even");

	else if(parity == 5)
		printf("1");

	else if(parity == 7)
		printf("0");

	unsigned char set_break_enable = ((st & BIT(6)) >> 6);

	printf("\t\tSet Break Enable :%d\n",set_break_enable);

	unsigned char dlab = ((st & BIT(7)) >> 7);

	printf("\tDLAB: ");
	if(dlab)
		printf("DL\n");

	else printf("Data\n");

	//CHECK DL

	if(!serial_check_dlab(base_addr))
		serial_toggle_dlab(base_addr);
	char dll, dlm;
	unsigned short dl;

	if(serial_get_dll(base_addr,&dll) != OK)
		return 1;

	if(serial_get_dlm(base_addr,&dlm) != OK)
		return 1;


	dl = (unsigned short)(dlm << 8) |(unsigned short)(dll);

	unsigned short bitrate = UART_FREQ/dl;
	printf("\tDLL: 0x%.2x\t",dll);
	printf("\tDLM: 0x%.2x\n",dlm);
	printf("\tDL: 0x%.4x",dl);
	printf("\t\tBitrate = %d bps\n",bitrate);

	//CHECK IER

	if(serial_get_ier(base_addr,&ier))
		return 1;

	printf("\n\n\tIER :%d %d %d %d %d %d %d %d",(ier & BIT(7)) >> 7,(ier & BIT(6)) >> 6,(ier & BIT(5)) >> 5,(ier & BIT(4)) >> 4
			,(ier & BIT(3)) >> 3,(ier & BIT(2)) >> 2,(ier & BIT(1)) >> 1,
			(ier & BIT(0)));
	if(ier & IER_ENABLE_RX)
		printf("\tRX enabled.");
	else
		printf("\tRX disabled.");

	if ((ier & IER_ENABLE_RX)>>1)
		printf("\tTX enabled.\n");
	else
		printf("\tTX disabled.\n");


	return 0;

}

int ser_test_set(unsigned short base_addr, unsigned long bits, unsigned long stop, 
		long parity, unsigned long rate) {

	unsigned long new_conf = 0;
	unsigned long divider_latch;
	char dll, dlm;


	//Set the word length
	switch (bits){
	case 6:
		new_conf |= BIT(0);
		break;
	case 7:
		new_conf |= BIT(1);
		break;
	case 8:
		new_conf |= (BIT(1) | BIT(0));
		break;
	default:
		break;
	}

	if (stop == 2)
		new_conf |= BIT(2);

	switch(parity){
	case 0:
		break;
	case 1:
		new_conf |= BIT(3);
		break;
	case 2:
		new_conf |= (BIT(3) | BIT(2));
		break;
	default:
		break;
	}

	printf("\nnova conf %d\n",new_conf);

	serial_set_conf(base_addr,new_conf);
	divider_latch = UART_FREQ / rate;

	dll = (unsigned char) divider_latch;
	dlm = (unsigned char) (divider_latch >> 8);

	printf("%d\n",divider_latch);
	serial_set_dll(base_addr, dll);
	serial_set_dlm(base_addr, dlm);

	return 0;

}

int ser_test_poll(unsigned short base_addr, unsigned char tx, unsigned long bits, 
		unsigned long stop, long parity, unsigned long rate,
		int stringc, char *strings[]) {
	/* To be completed */
}

int ser_test_int(/* details to be provided */) { 
	/* To be completed */
}

int ser_test_fifo(/* details to be provided */) {
	/* To be completed */
}
