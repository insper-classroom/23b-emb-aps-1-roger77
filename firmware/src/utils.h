/*
 * utils.h
 *
 * Created: 12/09/2023 14:30:15
 *  Author: Gabriel
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#include "music.h"

#define BUZZER_PIO PIOD
#define BUZZER_PIO_ID ID_PIOD
#define BUZZER_PIO_IDX 27
#define BUZZER_PIO_IDX_MASK (1u << BUZZER_PIO_IDX)

#define BUT1_PIO PIOD
#define BUT1_PIO_ID ID_PIOD
#define BUT1_PIO_IDX 28
#define BUT1_PIO_IDX_MASK (1u << BUT1_PIO_IDX)

#define BUT2_PIO				PIOC
#define BUT2_PIO_ID				ID_PIOC
#define BUT2_PIO_IDX		    31
#define BUT2_PIO_IDX_MASK		(1u << BUT2_PIO_IDX)

#define BUT3_PIO PIOA
#define BUT3_PIO_ID ID_PIOA
#define BUT3_PIO_IDX 19
#define BUT3_PIO_IDX_MASK (1u<< BUT3_PIO_IDX)

#define LED_PIO           PIOC
#define LED_PIO_ID        ID_PIOC
#define LED_PIO_IDX       8
#define LED_PIO_IDX_MASK  (1 << LED_PIO_IDX)

#define LED1_PIO   PIOA
#define LED1_PIO_ID ID_PIOA
#define LED1_PIO_IDX     0
#define LED1_PIO_IDX_MASK  (1<<LED1_PIO_IDX)

#define LED2_PIO   PIOC
#define LED2_PIO_ID ID_PIOC
#define LED2_PIO_IDX     30
#define LED2_PIO_IDX_MASK  (1<<LED2_PIO_IDX)

#define LED3_PIO   PIOB
#define LED3_PIO_ID ID_PIOB
#define LED3_PIO_IDX     2
#define LED3_PIO_IDX_MASK  (1<<LED3_PIO_IDX)

extern volatile char but1_flag;
extern volatile char but2_flag;
extern volatile char but3_flag;
extern volatile char display_flag;
extern volatile char pause_display_flag;

extern void but1_callback(void);
extern void but2_callback(void);
extern void but3_callback(void);

void set_buzzer(void);

void clear_buzzer(void);

void buzzer_test(int freq);

void init(void);

void tone(int freq, int time);

void loop_musica(int tamanho, int id_musica, int tempo, int wholenote, int divider, int noteDuration, Musica musicaAtual, Musica musicas[]);

#endif /* UTILS_H_ */