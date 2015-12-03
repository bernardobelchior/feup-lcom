#include "highscore.h"

int highscore_init(){
	FILE* file;
	if((file = fopen(highscore_path, "r")) == NULL)
		return 1;

	highscores = (score**) malloc(MAX_NUMBER_OF_SCORES*sizeof(score*));
	score* sc;

	fscanf(file, "//MINIX INVADERS HIGHSCORES//\n");

	unsigned char i = 0;

	while((sc = highscore_read(file)) != NULL){
		highscores[i] = sc;
		i++;
	}

	highscore_size = i;
	fclose(file);
	return 0;
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

	fscanf(file, "%u\n", &(sc->points));

	return sc;
}

int highscore_add(char* name, unsigned int points){
	score* sc = (score*) malloc(sizeof(score));
	sc->name = name;
	sc->points = points;

	unsigned char i;
	for(i = 0; i < highscore_size; i++){
		if(points > highscores[i]->points)
			break;
	}

	highscore_size++;
	highscores = (score**) realloc(highscores, highscore_size*sizeof(score*));

	unsigned char j;
	for(j = highscore_size; j > i; j--){
		highscores[j] = highscores[j-1];
	}
	highscores[i] = sc;

	return 0;
}

int highscore_write(FILE* file, score* sc){
	fprintf(file, "\n%s\n%u", sc->name, sc->points);
	return 0;
}

int highscore_destruct(){
	FILE* file;
	if((file = fopen(highscore_path, "w")) == NULL)
		return 1;

	printf("size: %d\n", highscore_size);

	fprintf(file, "//MINIX INVADERS HIGHSCORES//");

	unsigned char i;
	for(i = 0; i < highscore_size && i < MAX_NUMBER_OF_SCORES; i++){
		printf("Name: %s\tScore: %u\n", highscores[i]->name, highscores[i]->points);
		highscore_write(file, highscores[i]);
		free(highscores[i]);
	}

	free(highscores);
	fclose(file);
	highscore_size = 0;

	return 0;
}
