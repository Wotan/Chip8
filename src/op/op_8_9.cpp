#include <stdio.h>
#include "emulator.h"
#include "op.h"

int	Emulator::op_8XY0(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  cpu_register[VX] = cpu_register[VY];
  return 0;
}

int	Emulator::op_8XY1(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  cpu_register[VX] |= cpu_register[VY];
  return 0;
}

int	Emulator::op_8XY2(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  cpu_register[VX] &= cpu_register[VY];
  return 0;
}

int	Emulator::op_8XY3(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  cpu_register[VX] ^= cpu_register[VY];
  return 0;
}

int	Emulator::op_8XY4(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);

  if ((cpu_register[VX] + cpu_register[VY]) > 0xFF)
    cpu_register[0xF] = 1;
  else
    cpu_register[0xF] = 0;

  cpu_register[VX] += cpu_register[VY];
  return 0;
}

int	Emulator::op_8XY5(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  if (cpu_register[VY] > cpu_register[VX])
    cpu_register[0xF] = 0;
  else
    cpu_register[0xF] = 1;
  cpu_register[VX] -= cpu_register[VY];
  return 0;
}

int	Emulator::op_8XY6(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) / 0x100;

  CHECK_REGISTER(VX);
  cpu_register[0xF] = (cpu_register[VX] & 1) ? 1 : 0;
  cpu_register[VX] >>= 1;
  return 0;
}

int	Emulator::op_8XY7(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  if (cpu_register[VY] > cpu_register[VX])
    cpu_register[0xF] = 0;
  else
    cpu_register[0xF] = 1;
  cpu_register[VX] = cpu_register[VY] - cpu_register[VX];
  return 0;
}

int	Emulator::op_8XYE(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  cpu_register[0xF] = (cpu_register[VX] & 1 << 7) ? 1 : 0;
  cpu_register[VX] <<= 1;
  return 0;
}

int	Emulator::op_9XY0(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  if (cpu_register[VX] != cpu_register[VY])
    PC += 2;
  return 0;
}

