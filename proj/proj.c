#include <minix/drivers.h>
#include "proj.h"
#include "events.h"
#include "timer.h"
#include "mouse.h"
#include "keyboard.h"
#include "vbe.h"
#include "video_gr.h"
#include "singleplayer.h"
#include "i8042.h"
#include <stdlib.h>

extern enum game_state state;
extern menu* start_menu;

int main(int argc, char **argv) {
	sef_startup();
	vg_exit();//TODO ELIMINAR
	start();
	leave();
	return 0;
}

int start() {
	unsigned short character = 0x00;
	int ipc_status;
	message msg;
	int irq_set_kb = kb_subscribe_int();
	int irq_set_timer = timer_subscribe_int();
	int irq_set_mouse = mouse_subscribe_int();
	int r;
	unsigned char packet[3];
	unsigned short counter = 0;

	controller = keyboard;
	mouse_init();
	start_menu_init();
	vg_init(VBE_VIDEO_MODE);

	while (1) { //TODO change condition
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_kb) { /* keyboard interrupt */
					character = kb_int_handler();
					if (character != KB_2BYTE_SCODE)
						kb_event_handler(character);
				}
				if (msg.NOTIFY_ARG & irq_set_mouse){ /* mouse interrupt */
					mouse_int_handler(counter, packet);
					if(packet[0] != MOUSE_ACK && (packet[0] & BIT(3)))
						counter++;
					if(counter == 3){
						counter = 0;
						mouse_event_handler(packet);
					}

				}
				if (msg.NOTIFY_ARG & irq_set_timer){ /* timer interrupt */
					timer_int_handler();
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		}
		else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	return 0;
}

void test_function(){//TODO delete this funcion
	vg_draw_frame(0, 0, 50, 50, 2);
}

void start_menu_init(){
	state = main_menu;
	start_menu = create_menu();

	button* singleplayer = create_button(300, 100, 200, 90, &singleplayer_init, 2);
	menu_add_button(start_menu, singleplayer);
	button* multiplayer = create_button(300, 200, 200, 90, &test_function, 2);
	menu_add_button(start_menu, multiplayer);
	button* highscore = create_button(300, 300, 200, 90, &test_function, 2);
	menu_add_button(start_menu, highscore);
	button* options = create_button(300, 400, 200, 90, &test_function, 2);
	menu_add_button(start_menu, options);
	button* exit = create_button(300, 500, 200, 90, &leave, 2);
	menu_add_button(start_menu, exit);
}

void start_menu_destruct(){
	delete_menu(start_menu);
}

void leave(){
	timer_unsubscribe_int();
	kb_unsubscribe_int();
	mouse_unsubscribe_int();
	empty_out_buf();
	start_menu_destruct();
	vg_exit();
	exit(0);
}
