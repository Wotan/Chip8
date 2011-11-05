
#include <SDL/SDL.h>
#include <stdlib.h>
#include "emulator.h"
#include "op.h"

int	Emulator::op_0NNN(WORD opcode)
{
  printf("Op 0NNN not implementated\n");
  opcode = opcode;
  return 0;
}

int	Emulator::op_00E0(WORD opcode)
{
  graphics->Clear();
  opcode = opcode;
  return 0;
}

int	Emulator::op_00EE(WORD opcode)
{
  CHECK_STACK(stack_ptr);
  PC = stack[stack_ptr];
  stack_ptr--;
  opcode = opcode;
  return 0;
}

int	Emulator::op_1NNN(WORD opcode)
{
  PC = opcode & 0x0FFF;
  return 0;
}

int	Emulator::op_2NNN(WORD opcode)
{
  stack_ptr++;
  CHECK_STACK(stack_ptr);
  stack[stack_ptr] = PC;
  printf("Jump : current adress %X\n", stack[stack_ptr]);
  PC = opcode & 0x0FFF;
  return 0;
}

int	Emulator::op_3XNN(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  printf("op_3XNN VX:%X register\n", cpu_register[1]);
  if (cpu_register[VX] == (opcode & 0x00FF))
    PC += 2;
  return 0;
}

int	Emulator::op_4XNN(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  if (cpu_register[VX] != (opcode & 0x00FF))
    PC += 2;
  return 0;
}

int	Emulator::op_5XY0(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  if (cpu_register[VX] == cpu_register[VY])
    PC += 2;
  return 0;
}

int	Emulator::op_6XNN(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  cpu_register[VX] = (opcode & 0x00FF);
  printf("Set reg%X to %X\n", VX, cpu_register[VX]);
  return 0;
}

int	Emulator::op_7XNN(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  cpu_register[VX] += (opcode & 0x00FF);
  return 0;
}
