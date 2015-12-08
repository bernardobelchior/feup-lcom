#include "singleplayer.h"

extern enum singleplayer_controller controller;
extern enum game_state state;

void singleplayer_init() {

	singleplayer_game.score = 0;

	if ((singleplayer_game.play = player_init()) == NULL)
		return;

	projectile_list_init();
	alien_list_init();
	shield_list_init();
}

void singleplayer_tick() {
	static unsigned short ticks = 0;
	if (controller == mouse)
		player_set_x_pos(singleplayer_game.play, mouse_info.x);

	if(invaders->head == NULL)
		change_state(main_menu);

	if (ticks % 60 == 0)
		if(aliens_move() == -1)
			change_state(main_menu);

#ifdef DEBUG
	vg_draw_line(PLACEHOLDER_LEFT_BORDER, 0, PLACEHOLDER_LEFT_BORDER, get_v_res(), rgb(0x00FFFFFF));
	vg_draw_line(PLACEHOLDER_RIGHT_BORDER, 0, PLACEHOLDER_RIGHT_BORDER, get_v_res(),rgb(0x00FFFFFF));
	vg_draw_line(0, PLACEHOLDER_SHIELD_LINE, get_h_res(), PLACEHOLDER_SHIELD_LINE,rgb(0x00FFFFFF));
#endif


	ticks++;

	if (invaders->alien_num == 0) {
		change_state(main_menu);
	}

	aliens_draw();
	shields_draw();
	player_draw(singleplayer_game.play);
	singleplayer_check_projectiles_state();
}

void singleplayer_check_projectiles_state() {

	if (projectiles->head == NULL)
		return;

	projectile *iterator = projectiles->head;

	do {
		if (projectile_reached_end(iterator)
				|| singleplayer_projectile_collision(iterator))
			projectile_delete(iterator); //TODO implement on projectile.c
		else {
			projectile_move(iterator);
			projectile_draw(iterator);
		}

		iterator = iterator->next;
	} while (iterator != NULL);
}

int singleplayer_projectile_collision(projectile* proj) {
	//TODO Add shield collision

	return aliens_collision_handler(proj->x, proj->y) | player_collision_handler(singleplayer_game.play, proj->x, proj->y) | shield_collision_handler(proj->x, proj->y);
}

int singleplayer_move(char direction) {
	return player_move(singleplayer_game.play, direction);
}

int singleplayer_fire() {
	return player_fire(singleplayer_game.play);
}

void singleplayer_destruct() { //TODO still need to free shield, after implementing
	aliens_destruct();
	player_destruct(singleplayer_game.play);
	shields_destruct();
}

