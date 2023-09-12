/*
 * music.h
 *
 * Created: 12/09/2023 14:46:16
 *  Author: Gabriel
 */ 


#ifndef MUSIC_H_
#define MUSIC_H_

typedef struct {
	char* nome;
	int* notasEDuracoes;
	int tamanho;
	int tempo;
} Musica;

#endif /* MUSIC_H_ */