#include "highscore.h"

int highscore_init(){
	FILE* file;
	if((file = fopen(highscore_path, "r")) == NULL)
		return 1;

	highscores = (score**) malloc(MAX_NUMBER_OF_SCORES*sizeof(score*));
	score* sc;

	unsigned char i = 0;
	while((sc = highscore_read(file)) != NULL){
		highscores[i] = sc;
		i++;
	}

	highscore_size = i;

	return 0;
}

score* highscore_read(FILE* file){
	score* sc = (score*) malloc(sizeof(score));
	sc->name = (char*) malloc(20*sizeof(char));

	unsigned char i = 0, character_read;
	while((character_read = fgetc(file)) != EOF && character_read != '\n' && i < 20){
		sc->name[i] = character_read;
		i++;
	}

	if(i >= 20){
		while((character_read = fgetc(file)) != EOF && character_read != '\n');
	} else if(character_read == EOF)
		return NULL;

	fscanf(file, "%d", sc->points);

	return sc;
}

int highscore_destruct(){
	unsigned char i;
	for(i = 0; i < highscore_size; i++){
		printf("Name: %s\tScore: %d", highscores[i]->name, highscores[i]->points);
		free(highscores[i]);
	}
	free(highscores);

	return 0;
}
