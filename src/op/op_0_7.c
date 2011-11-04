
#include <SDL/SDL.h>
#include <stdlib.h>
#include "emulator.h"
#include "op.h"

int	op_0NNN(WORD opcode, t_emulator *emu)
{
  printf("Op 0NNN not implementated\n");
  opcode = opcode;
  emu = emu;
  return 0;
}

int	op_00E0(WORD opcode, t_emulator *emu)
{
  SDL_FillRect(emu->graphics->screen, NULL,
	       SDL_MapRGB(emu->graphics->screen->format, 0, 0, 0));
  opcode = opcode;
  return 0;
}

int	op_00EE(WORD opcode, t_emulator *emu)
{
  CHECK_STACK(emu->stack_ptr);
  emu->PC = emu->stack[emu->stack_ptr];
  emu->stack_ptr--;
  opcode = opcode;
  return 0;
}

int	op_1NNN(WORD opcode, t_emulator *emu)
{
  emu->PC = opcode & 0x0FFF;
  return 0;
}

int	op_2NNN(WORD opcode, t_emulator *emu)
{
  emu->stack_ptr++;
  CHECK_STACK(emu->stack_ptr);
  emu->stack[emu->stack_ptr] = emu->PC;
  printf("Jump : current adress %X\n", emu->stack[emu->stack_ptr]);
  emu->PC = opcode & 0x0FFF;
  return 0;
}

int	op_3XNN(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  printf("op_3XNN VX:%X register\n", emu->cpu_register[1]);
  if (emu->cpu_register[VX] == (opcode & 0x00FF))
    emu->PC += 2;
  return 0;
}

int	op_4XNN(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  if (emu->cpu_register[VX] != (opcode & 0x00FF))
    emu->PC += 2;
  return 0;
}

int	op_5XY0(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  if (emu->cpu_register[VX] == emu->cpu_register[VY])
    emu->PC += 2;
  return 0;
}

int	op_6XNN(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  emu->cpu_register[VX] = (opcode & 0x00FF);
  printf("Set reg%X to %X\n", VX, emu->cpu_register[VX]);
  return 0;
}

int	op_7XNN(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  emu->cpu_register[VX] += (opcode & 0x00FF);
  return 0;
}
