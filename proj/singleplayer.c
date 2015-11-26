#include "singleplayer.h"
#include "proj.h"

extern enum singleplayer_controller controller;
extern enum game_state state;

void singleplayer_init() {
	if(state == main_menu)
		start_menu_destruct();

	singleplayer_game.num_projectiles = 0;

	if((singleplayer_game.aliens = (alien**) malloc(ALIENS_PER_ROW * ALIEN_ROWS * sizeof(alien*))) == NULL)
		return;

	if((singleplayer_game.shields = (shield**) malloc(NUMBER_OF_SHIELDS * sizeof(shield*))) == NULL)
		return;

	if((singleplayer_game.projectiles = (projectile**) malloc(20*sizeof(projectile*))) == NULL)
		return;

	singleplayer_game.score = 0;

	if( (singleplayer_game.play = player_init()) == NULL)
		return;

	state = singleplayer;
}

void singleplayer_tick(){
	if(controller == mouse)
		player_set_x_pos(singleplayer_game.play, mouse_info.x);
	player_draw(singleplayer_game.play);
	singleplayer_check_projectiles_state();
}

void singleplayer_check_projectiles_state(){
	unsigned char i;
	for(i = 0; i < singleplayer_game.num_projectiles; i++){
		if(projectile_reached_end(singleplayer_game.projectiles[i])){
			singleplayer_delete_projectile(i);
		}
		//else if(singleplayer_projectile_collision(singleplayer_game.projectiles[i]))
			//singleplayer_delete_projectile(i);
		else{
			projectile_move(singleplayer_game.projectiles[i]);
			projectile_draw(singleplayer_game.projectiles[i]);
		}
	}
}

int singleplayer_delete_projectile(unsigned int proj_index){
	if(proj_index >= singleplayer_game.num_projectiles)
		return 1;

	free(singleplayer_game.projectiles[proj_index]);
	unsigned char i;
	for(i = proj_index; i < singleplayer_game.num_projectiles - 1; i++){
		singleplayer_game.projectiles[i] = singleplayer_game.projectiles[i+1];
	}

	singleplayer_game.num_projectiles--;
	//singleplayer_game.projectiles = (projectile**) realloc(singleplayer_game.projectiles, singleplayer_game.num_projectiles);
	return 0;
}

int singleplayer_projectile_collision(projectile* proj){
	if(player_check_collision(singleplayer_game.play, proj->x, proj->y)){
		player_hit(singleplayer_game.play);
		return 1;
	}


	unsigned char i;
	//for(i = 0; i < ALIENS_PER_ROW*ALIEN_ROWS; i++){
	for(i = 0; i < 0; i++){
		//TODO check alien collision
	}

	//for(i = 0; i < NUMBER_OF_SHIELDS; i++){
	for(i = 0; i < 0; i++){
		//TODO check shield collision
	}
}

int singleplayer_move(short x){
	return player_move(singleplayer_game.play, x);
}

int singleplayer_fire(){//TODO crashes when projectiles are more than 4 or 9, depending on the code
	singleplayer_game.num_projectiles++;
	singleplayer_game.projectiles = (projectile**) realloc(singleplayer_game.projectiles, singleplayer_game.num_projectiles);
	if((*(singleplayer_game.projectiles + singleplayer_game.num_projectiles - 1) = player_fire(singleplayer_game.play)) == NULL){
		singleplayer_game.num_projectiles--;
		singleplayer_game.projectiles = (projectile**) realloc(singleplayer_game.projectiles, singleplayer_game.num_projectiles);
		return 1;
	}
	return 0;
}

void singleplayer_destruct() {//TODO proper free
	unsigned char i;

	//for...
	free(singleplayer_game.aliens);

	//for...
	free(singleplayer_game.shields);

	for(i = 0; i < singleplayer_game.num_projectiles; i++)
		free(singleplayer_game.projectiles[i]);
	free(singleplayer_game.projectiles);

	player_destruct(singleplayer_game.play);
}

