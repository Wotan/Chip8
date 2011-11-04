/*
** emulator.c for  in /home/wotan/projets/chip8
** 
** Made by geoffroy aubey
** Login   <aubey_g@epitech.net>
** 
** Started on  Thu Nov  3 00:15:16 2011 geoffroy aubey
** Last update Thu Nov  3 00:15:16 2011 geoffroy aubey
*/

#ifndef EMULATOR_H_
# define EMULATOR_H_

# include "graphics.h"
# define NB_REGISTER 16
# define STACK_SIZE 16
# define MEMORY_SIZE 0xFFF
# define FREQUENCE 100 /* Hertz */
# define CHECK_STACK(x) if (!(((x) >= 0 && (x) < STACK_SIZE)))\
    {printf("Error, stack overflow or no adress on stack\n"); return 1;}
# define CHECK_REGISTER(x) if (!((x) < NB_REGISTER))\
    {printf("Error, register adress is out of range\n"); return 1;}

typedef unsigned char BYTE;
typedef unsigned short WORD;


typedef struct s_emulator
{

  BYTE		memory[0xFFF];
  BYTE		cpu_register[16]; /* F is carry */
  WORD		stack[STACK_SIZE];
  int		stack_ptr;
  WORD		I;
  int		PC;
  t_graphics	*graphics;
  BYTE		timer;
  BYTE		sound_timer;
}		t_emulator;

void		sync_CPU();
t_emulator	*init_emulator(char *file_name);
int		do_cycle(t_emulator *emu);
WORD		get_word(t_emulator *emu, int addr);
int		load_font(t_emulator *emu);
int		handle_events(t_emulator *emu, t_graphics *graphics, int *pause);

#endif /* EMULATOR_H_ */
