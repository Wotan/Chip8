/*
** emulator.c for  in /home/wotan/projets/chip8
** 
** Made by geoffroy aubey
** Login   <aubey_g@epitech.net>
** 
** Started on  Thu Nov  3 00:15:16 2011 geoffroy aubey
** Last update Sat Nov  5 22:33:30 2011 geoffroy aubey
*/

#ifndef EMULATOR_H_
# define EMULATOR_H_

# include "graphics.h"
# define NB_REGISTER 16
# define STACK_SIZE 16
# define MEMORY_SIZE 0xFFF
# define FREQUENCE 200 /* Hertz */
# define CHECK_STACK(x) if (!(((x) >= 0 && (x) < STACK_SIZE)))\
    {printf("Error, stack overflow or no adress on stack\n"); return 1;}
# define CHECK_REGISTER(x) if (!((x) < NB_REGISTER))			\
    {printf("Error, register adress is out of range\n"); return 1;}

typedef unsigned char BYTE;
typedef unsigned short WORD;


typedef class Emulator
{
public:
  Emulator(char *file_name);
  int	        DoCycle();
  WORD		GetWord(int addr) const;
  int		LoadFont();
  void		SetGraphics(Graphics *new_graphics);
  int		op_0NNN(WORD opcode);
  int		op_00E0(WORD opcode);
  int		op_00EE(WORD opcode);
  int		op_1NNN(WORD opcode);
  int		op_2NNN(WORD opcode);
  int		op_3XNN(WORD opcode);
  int		op_4XNN(WORD opcode);
  int		op_5XY0(WORD opcode);
  int		op_6XNN(WORD opcode);
  int		op_7XNN(WORD opcode);
  int		op_8XY0(WORD opcode);
  int		op_8XY1(WORD opcode);
  int		op_8XY2(WORD opcode);
  int		op_8XY3(WORD opcode);
  int		op_8XY4(WORD opcode);
  int		op_8XY5(WORD opcode);
  int		op_8XY6(WORD opcode);
  int		op_8XY7(WORD opcode);
  int		op_8XYE(WORD opcode);
  int		op_9XY0(WORD opcode);
  int		op_ANNN(WORD opcode);
  int		op_BNNN(WORD opcode);
  int		op_CXNN(WORD opcode);
  int		op_DXYN(WORD opcode);
  int		op_EX9E(WORD opcode);
  int		op_EXA1(WORD opcode);
  int		op_FX07(WORD opcode);
  int		op_FX0A(WORD opcode);
  int		op_FX15(WORD opcode);
  int		op_FX18(WORD opcode);
  int		op_FX1E(WORD opcode);
  int		op_FX29(WORD opcode);
  int		op_FX33(WORD opcode);
  int		op_FX55(WORD opcode);
  int		op_FX65(WORD opcode);

private:
  BYTE		memory[0xFFF];
  BYTE		cpu_register[16]; /* F is carry */
  WORD		stack[STACK_SIZE];
  int		stack_ptr;
  WORD		I;
  int		PC;
  BYTE		timer;
  BYTE		sound_timer;
  Graphics	*graphics;

}		t_emulator;

void		sync_CPU();
t_emulator	*init_emulator(char *file_name);

#endif /* EMULATOR_H_ */
