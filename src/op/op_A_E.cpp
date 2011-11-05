#include <time.h>
#include "emulator.h"
#include "op.h"

int	Emulator::op_ANNN(WORD opcode)
{
  I = opcode & 0x0FFF;
  return 0;
}

int	Emulator::op_BNNN(WORD opcode)
{
  PC = (opcode & 0x0FFF) + cpu_register[0];
  return 0;
}

int	Emulator::op_CXNN(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;

  CHECK_REGISTER(VX);

  srand(time(NULL));
  cpu_register[VX] = rand() % ((opcode & 0x0FFF) + 1);

  return 0;
}

int	Emulator::op_DXYN(WORD opcode)
{
  int	height = opcode & 0x000F;
  int	i, j;
  int	x, y;
  bool	isSet;
  WORD  VX = (opcode & 0x0F00) >> 8;
  WORD  VY = (opcode & 0x00F0) >> 4;

  CHECK_REGISTER(VX);
  CHECK_REGISTER(VY);
  cpu_register[0xF] = 0;
  printf("Dessin\n");
  printf("Coordonate : X %i Y %i\n", cpu_register[VX],
	 cpu_register[VY]);

  x = cpu_register[VX];
  y = cpu_register[VY];
  for (j = 0; j < height; j++)
    {
      for (i = 0; i < 8; i++)
	{
	  if (memory[I + j] & (1 << (7 - i)))
	    {
	      isSet = graphics->IsPixelSet(x + i, y + j);
	      if (isSet)
		cpu_register[0xF] = 1;
	      graphics->SetPixel(x + i, y + j, !isSet);
	    }
	}
    }
  graphics->Flip();
  return 0;
}

int	Emulator::op_EX9E(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  unsigned int	key;

  key = cpu_register[VX];

  if (graphics->IsKeyUp(key))
    PC += 2;
  return 0;
}

int	Emulator::op_EXA1(WORD opcode)
{
  WORD  VX = (opcode & 0x0F00) >> 8;
  int	key;

  key = cpu_register[VX];
  if (!graphics->IsKeyUp(key))
    PC += 2;
  return 0;
}
