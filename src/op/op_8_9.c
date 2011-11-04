#include "emulator.h"
#include "op.h"

int	op_8XY0(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  emu->cpu_register[VX] = emu->cpu_register[VY];
  return 0;
}

int	op_8XY1(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  emu->cpu_register[VX] |= emu->cpu_register[VY];
  return 0;
}

int	op_8XY2(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  emu->cpu_register[VX] &= emu->cpu_register[VY];
  return 0;
}

int	op_8XY3(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  emu->cpu_register[VX] ^= emu->cpu_register[VY];
  return 0;
}

int	op_8XY4(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);

  if ((emu->cpu_register[VX] + emu->cpu_register[VY]) > 0xFF)
    emu->cpu_register[0xF] = 1;
  else
    emu->cpu_register[0xF] = 0;

  emu->cpu_register[VX] += emu->cpu_register[VY];
  return 0;
}

int	op_8XY5(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  if (emu->cpu_register[VY] > emu->cpu_register[VX])
    emu->cpu_register[0xF] = 1;
  else
    emu->cpu_register[0xF] = 0;
  emu->cpu_register[VX] -= emu->cpu_register[VY];
  return 0;
}

int	op_8XY6(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) / 0x100;

  CHECK_REGISTER(VX);
  emu->cpu_register[0xF] = (emu->cpu_register[VX] & 1) ? 1 : 0;
  emu->cpu_register[VX] >>= 1;
  return 0;
}

int	op_8XY7(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  if (emu->cpu_register[VY] > emu->cpu_register[VX])
    emu->cpu_register[0xF] = 1;
  else
    emu->cpu_register[0xF] = 0;
  emu->cpu_register[VX] = emu->cpu_register[VY] - emu->cpu_register[VX];
  return 0;
}

int	op_8XYE(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  emu->cpu_register[0xF] = (emu->cpu_register[VX] & 1 << 7) ? 1 : 0;
  emu->cpu_register[VX] <<= 1;
  return 0;
}

int	op_9XY0(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  if (emu->cpu_register[VX] != emu->cpu_register[VY])
    emu->PC += 2;
  return 0;
}

