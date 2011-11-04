#include "emulator.h"
#include "op.h"

int	op_FX07(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  emu->cpu_register[VX] = emu->timer;
  return 0;
}

int	op_FX0A(WORD opcode, t_emulator *emu)
{
  printf("Not implemented yet\n");
  return 0;
}

int	op_FX15(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  emu->timer = emu->cpu_register[VX];
  return 0;
}

int	op_FX18(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  emu->sound_timer = emu->cpu_register[VX];
  return 0;
}

int	op_FX1E(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);

  if (emu->I + emu->cpu_register[VX] > 0xFFF)
    emu->cpu_register[0xF] = 1;
  else
    emu->cpu_register[0xF] = 0;
  emu->I += emu->cpu_register[VX];
  return 0;
}

int	op_FX29(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);
  emu->I = 5 * emu->cpu_register[VX];
  return 0;
}

int	op_FX33(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  BYTE	tmp;

  CHECK_REGISTER(VX);
  tmp = emu->cpu_register[VX];
  emu->memory[emu->I] = tmp / 100;
  emu->memory[emu->I + 1] = (tmp / 10) % 10;
  emu->memory[emu->I + 2] = tmp % 10;
  return 0;
}

int	op_FX55(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  unsigned int i;

  CHECK_REGISTER(VX);

  for (i = 0; i <= VX; i++)
    {
      emu->memory[emu->I + i] = emu->cpu_register[i];
    }
  return 0;
}

int	op_FX65(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) / 0x100;
  unsigned int i;

  CHECK_REGISTER(VX);

  for (i = 0; i <= VX; i++)
    {
      emu->cpu_register[i] = emu->memory[emu->I + i];
    }
  return 0;
}

