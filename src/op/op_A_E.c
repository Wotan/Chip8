#include <time.h>
#include "emulator.h"
#include "op.h"

int	op_ANNN(WORD opcode, t_emulator *emu)
{
  emu->I = opcode & 0x0FFF;
  return 0;
}

int	op_BNNN(WORD opcode, t_emulator *emu)
{
  emu->PC = (opcode & 0x0FFF) + emu->cpu_register[0];
  return 0;
}

int	op_CXNN(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);

  srand(time(NULL));
  emu->cpu_register[VX] = rand() % ((opcode & 0x0FFF) + 1);

  return 0;
}

int	op_DXYN(WORD opcode, t_emulator *emu)
{
  int	height = opcode & 0x000F;
  int	i, j;
  int	x, y;
  int	tmp;
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  emu->cpu_register[0xF] = 0;
  printf("Dessin\n");
  printf("Coordonate : X %i Y %i\n", emu->cpu_register[VX],
	 emu->cpu_register[VY]);

  x = emu->cpu_register[VX];
  y = emu->cpu_register[VY];
  for (j = 0; j < height; j++)
    {
      for (i = 0; i < 8; i++)
	{
	  if (emu->memory[emu->I + j] & (1 << (7 - i)))
	    {
	      tmp = is_pixel_set(emu->graphics, x + i, y + j);
	      if (tmp)
		emu->cpu_register[0xF] = 1;
	      set_pixel(emu->graphics, x + i, y + j, !tmp);
	    }
	}
    }
  SDL_Flip(emu->graphics->screen);
  return 0;
}

int	op_EX9E(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  unsigned int	key;

  key = emu->cpu_register[VX];

  if (emu->graphics->key[key])
    emu->PC += 2;
  return 0;
}

int	op_EXA1(WORD opcode, t_emulator *emu)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  unsigned int	key;

  key = emu->cpu_register[VX];

  if (!emu->graphics->key[key])
    emu->PC += 2;
  return 0;
}
