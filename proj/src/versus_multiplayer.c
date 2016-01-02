#include "versus_multiplayer.h"

void versus_mp_game_init(){

	if((mp_game.p1 = player_init(1)) == NULL)
		return;

	if((mp_game.p2 = player_init(0)) == NULL)
		return;

	player_mirror_image(mp_game.p2);

	mp_game.reset_ticks = 1;
	projectile_list_init();
	shield_list_init(0);

}

void versus_mp_game_tick(){

	static unsigned int time_limit = DEFAULT_TIME_LIMIT;
	static unsigned int seconds = 0;
	static unsigned int ticks = 0;
	static char game_over = 0;

	if(mp_game.reset_ticks){
		time_limit = DEFAULT_TIME_LIMIT;
		seconds = 0;
		ticks = 0;
		mp_game.reset_ticks = 0;
		game_over = 0;
	}

	if(seconds >= DEFAULT_TIME_LIMIT){
		game_over = 1;
		seconds = 0;
	}

	if(seconds >= GAME_OVER_SCREEN_TIME && game_over)
		change_state(main_menu);

	if(ticks % 60 == 0)
		seconds++;

	if(!game_over){
		//Draws scores

		font_draw_string(space_invaders_font, 0, 0, "P1 Score: ", ALIGN_LEFT);
		font_draw_int(space_invaders_font, strlen("P1 Score: ")*space_invaders_font->letter_width, 0, mp_game.p1->score, ALIGN_LEFT);


		font_draw_string(space_invaders_font, 0, SP_PLAYER_INITIAL_Y_POS+SHIP_HEIGHT, "P2 Score: ", ALIGN_LEFT);
		font_draw_int(space_invaders_font, strlen("P2 Score: ")*space_invaders_font->letter_width, SP_PLAYER_INITIAL_Y_POS+SHIP_HEIGHT, mp_game.p2->score, ALIGN_LEFT);


		//Draws timer

		font_draw_int(space_invaders_font, get_h_res()-3*space_invaders_font->letter_width, MP_PLAYER_1_INITIAL_Y_POS-SHIP_HEIGHT, (DEFAULT_TIME_LIMIT - seconds)/60, ALIGN_RIGHT);
		font_draw_string(space_invaders_font,get_h_res()-2*space_invaders_font->letter_width, MP_PLAYER_1_INITIAL_Y_POS-SHIP_HEIGHT, ":",ALIGN_RIGHT);
		if((DEFAULT_TIME_LIMIT-seconds)%60 < 10)
			font_draw_int(space_invaders_font,get_h_res()-space_invaders_font->letter_width - LETTER_SPACEMENT
					, MP_PLAYER_1_INITIAL_Y_POS-SHIP_HEIGHT,0,ALIGN_RIGHT);
		font_draw_int(space_invaders_font,get_h_res(), MP_PLAYER_1_INITIAL_Y_POS-SHIP_HEIGHT,(DEFAULT_TIME_LIMIT - seconds)%60,ALIGN_RIGHT);


		shields_draw();
		mp_game.p1->num_lives = 5;
		mp_game.p2->num_lives = 5;
		player_tick(mp_game.p1);
		player_tick(mp_game.p2);
		versus_mp_check_projectiles_state();
	}

	else{
		if(mp_game.p1->score < mp_game.p2->score)
			font_draw_string(space_invaders_font,get_h_res()/2, get_v_res()/2, "THE WINNER IS PLAYER 2!!",ALIGN_CENTER);

		else if (mp_game.p1->score > mp_game.p2->score)
			font_draw_string(space_invaders_font,get_h_res()/2, get_v_res()/2, "THE WINNER IS PLAYER 1!!",ALIGN_CENTER);

		else
			font_draw_string(space_invaders_font,get_h_res()/2, get_v_res()/2, "ITS A DRAW!!",ALIGN_CENTER);

	}
	ticks++;

}

int versus_mp_move(char player, char direction){
	if(player == 1)
		return player_move(mp_game.p1,direction);
	else if (player == 2)
		return player_move(mp_game.p2,direction);
	else return -1;
}

int versus_mp_fire(char player){
	if(player == 1)
		return player_fire(mp_game.p1,-1);

	else if(player == 2)
		return player_fire(mp_game.p2, 1);

	else return -1;
}

void versus_mp_check_projectiles_state(){

	if(projectiles->head == NULL)
		return;

	projectile *iterator = projectiles->head;

	do {
		if (projectile_reached_end(iterator)
				|| versus_mp_projectile_collision(iterator))
			projectile_delete(iterator); //TODO implement on projectile.c
		else {
			projectile_move(iterator);
			projectile_draw(iterator);
		}

		iterator = iterator->next;
	} while (iterator != NULL);
}

int versus_mp_projectile_collision(projectile *proj){
	return shield_collision_handler(proj)||player_collision_handler(mp_game.p1, proj)|| player_collision_handler(mp_game.p2, proj);
}

void versus_mp_game_over(){
	player_destruct(mp_game.p1);
	player_destruct(mp_game.p2);
	shields_destruct();
}
void versus_mp_game_destruct(){

}
