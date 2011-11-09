#include <stdio.h>
#include "emulator.h"
#include "op.h"
#include "graphics.h"

int	Emulator::op_FX07(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  cpu_register[VX] = timer;
  return 0;
}

int	Emulator::op_FX0A(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  printf("Waiting event\n");
  mRegToSet = VX;
  mWaitingKey = true;
  return 0;
}

int	Emulator::op_FX15(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  timer = cpu_register[VX];
  return 0;
}

int	Emulator::op_FX18(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  sound_timer = cpu_register[VX];
  return 0;
}

int	Emulator::op_FX1E(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);

  if (I + cpu_register[VX] > 0xFFF)
    cpu_register[0xF] = 1;
  else
    cpu_register[0xF] = 0;
  I += cpu_register[VX];
  return 0;
}

int	Emulator::op_FX29(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  I = 5 * cpu_register[VX];
  return 0;
}

int	Emulator::op_FX33(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  BYTE	tmp;

  CHECK_REGISTER(VX);
  tmp = cpu_register[VX];
  memory[I] = tmp / 100;
  memory[I + 1] = (tmp / 10) % 10;
  memory[I + 2] = tmp % 10;
  return 0;
}

int	Emulator::op_FX55(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  unsigned int i;

  CHECK_REGISTER(VX);

  for (i = 0; i <= VX; i++)
    {
      memory[I + i] = cpu_register[i];
    }
  return 0;
}

int	Emulator::op_FX65(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  unsigned int i;

  CHECK_REGISTER(VX);

  for (i = 0; i <= VX; i++)
    {
      cpu_register[i] = memory[I + i];
    }
  return 0;
}

