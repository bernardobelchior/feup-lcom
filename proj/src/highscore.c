#include "highscore.h"

void highscore_init(){
	highscore_menu = (menu*) malloc(sizeof(menu));
	highscore_menu = create_menu("spaceinvader_font_transparent.bmp");
	menu_add_button(highscore_menu, create_button(512, 675, 200, 75, ALIGN_CENTER, &highscore_back_on_click, "Back" ,rgb(0x00FFFFFF), ALIGN_CENTER));
}

void highscore_load(){
	FILE* file;
	file = fopen(highscore_path, "r");

	highscore_size = 0;
	highscores = (score**) malloc(MAX_NUMBER_OF_SCORES*sizeof(score*));

	if(file == NULL)
		return;

	fscanf(file, "//MINIX INVADERS HIGHSCORES//\n");

	unsigned char i = 0;

	score* sc = (score*) malloc(sizeof(score));
	while(((sc = highscore_read(file)) != NULL) && i < MAX_NUMBER_OF_SCORES){
		highscores[i] = (score*) malloc(sizeof(score));
		*highscores[i] = *sc;
		i++;
	}

	highscore_size = i;
	fclose(file);
}

score* highscore_read(FILE* file){
	if(feof(file))
		return NULL;

	char buf;

	score* sc = (score*) malloc(sizeof(score));
	sc->name = (char*) malloc(20*sizeof(char));
	unsigned char length;

	fgets(sc->name, 20, file);
	length = strlen(sc->name);

	sc->name[length-1] = '\0';
	length--;

	sc->name = (char*) realloc(sc->name, length*sizeof(char));

	sc->date = (Date*) malloc(sizeof(Date));
	fscanf(file, "%u/%u/%u\n", &(sc->date->day), &(sc->date->month), &(sc->date->year));

	fscanf(file, "%u\n", &(sc->points));

	return sc;
}

int highscore_add(char* name, Date* date, unsigned int points){
	score* sc = (score*) malloc(sizeof(score));
	sc->name = name;
	sc->date = date;
	sc->points = points;

	unsigned char i;
	for(i = 0; i < highscore_size && i < MAX_NUMBER_OF_SCORES; i++){
		if(points > highscores[i]->points)
			break;
	}

	if(i == MAX_NUMBER_OF_SCORES)
		return 0;


	unsigned char j;
	if(highscore_size < MAX_NUMBER_OF_SCORES){
		j = highscore_size;
		highscore_size++;
	} else
		j = MAX_NUMBER_OF_SCORES;

	for(; j > i; j--){
		highscores[j] = highscores[j-1];
	}
	highscores[i] = sc;

	return 1;
}

int is_on_highscores(unsigned int points){
	unsigned int i;
	for(i = 0; i < highscore_size && i < MAX_NUMBER_OF_SCORES; i++){
		if(points > highscores[i]->points)
			return 1;
	}

	if(i == MAX_NUMBER_OF_SCORES)
		return 0;

	return 1;
}

int highscore_write(FILE* file, score* sc){
	fprintf(file, "\n%s\n%u/%u/%u\n%u", sc->name, sc->date->day, sc->date->month, sc->date->year, sc->points);
	return 0;
}

void highscore_tick(){
	//Title
	font_draw_string(space_invaders_font, get_h_res()/2, get_v_res()/40, "Highscores", ALIGN_CENTER);

	//Draws menu
	menu_draw(highscore_menu);

	//Draws table header
	font_draw_string(space_invaders_font, 200, 95, "Name", ALIGN_CENTER);
	font_draw_string(space_invaders_font, 525, 95, "Date", ALIGN_CENTER);
	font_draw_string(space_invaders_font, 850, 95, "Score", ALIGN_CENTER);

	//Draws highscores
	char* date_str = (char*) malloc(20*sizeof(char));
	unsigned char i;
	for(i = 0; i < highscore_size; i++){
		font_draw_string(space_invaders_font, 200, 155+50*i, highscores[i]->name, ALIGN_CENTER);
		sprintf(date_str, "%u/%u/%u", highscores[i]->date->day, highscores[i]->date->month, highscores[i]->date->year);
		font_draw_string(space_invaders_font, 525, 155+50*i, date_str, ALIGN_CENTER);
		font_draw_int(space_invaders_font, 850, 155+50*i, (int) highscores[i]->points, ALIGN_CENTER);
	}
	free(date_str);

	//Draws guidelines
#ifdef DEBUG
	vg_draw_frame(50, 90, 900, 561, rgb(0xFFFFFF));

	//Vertical lines
	vg_draw_line(350, 90, 350, 650, rgb(0xFFFFFF));
	vg_draw_line(750, 90, 750, 650, rgb(0xFFFFFF));

	//Horizontal lines
	vg_draw_line(50, 145, 950, 145, rgb(0xFFFFFF));
	vg_draw_line(50, 150, 950, 150, rgb(0xFFFFFF));

	for(i = 1; i < 10; i++){
		vg_draw_line(50, 150+50*i, 950, 150+50*i, rgb(0xFFFFFF));
	}
#endif
}

void highscore_back_on_click(){
	change_state(main_menu);
}

void highscore_save(){
	FILE* file;
	file = fopen(highscore_path, "w");

	fprintf(file, "//MINIX INVADERS HIGHSCORES//");

	unsigned char i;

	if(file != NULL){
		for(i = 0; i < highscore_size && i < MAX_NUMBER_OF_SCORES; i++){
			highscore_write(file, highscores[i]);
		}
		fclose(file);
	}

	for(i = 0; i < highscore_size && i < MAX_NUMBER_OF_SCORES; i++){
		free(highscores[i]->date);
		free(highscores[i]);
	}

	free(highscores);
	highscore_size = 0;
}

void highscore_destruct(){
	delete_menu(highscore_menu);
}
