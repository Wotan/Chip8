#include <stdlib.h>
#include <stdio.h>
#include "emulator.h"
#include "op.h"

WORD		get_word(t_emulator *emu, int addr)
{
  WORD		opcode = 0;

  opcode = emu->memory[addr];
  opcode <<= 8;
  opcode |= emu->memory[addr + 1];
  return opcode;
}

int		do_cycle(t_emulator *emu)
{
  WORD opcode;

  opcode = get_word(emu, emu->PC);
  emu->PC += 2;
  if (emu->timer > 0)
    emu->timer--;
  printf("opcode = %04x\n", opcode);
  switch (opcode & 0xF000)
    {
    case 0x0000:
      switch (opcode & 0x00FF)
	{
	case 0xE0:
	  op_00E0(opcode, emu);
	  break;
	case 0xEE:
	    op_00EE(opcode, emu);
	    break;
	default:
	  printf("Unknown opcode\n");
	}
      break ;

    case 0x1000:
      op_1NNN(opcode, emu);
      break ;
    case 0x2000:
      op_2NNN(opcode, emu);
      break ;
    case 0x3000:
      op_3XNN(opcode, emu);
      break ;
    case 0x4000:
      op_4XNN(opcode, emu);
      break ;
    case 0x5000:
      op_5XY0(opcode, emu);
      break ;
    case 0x6000:
      op_6XNN(opcode, emu);
      break ;
    case 0x7000:
      op_7XNN(opcode, emu);
      break ;

    case 0x8000:
      switch (opcode & 0x000F)
	{
	case 0x0:
	  op_8XY0(opcode, emu);
	  break;
	case 0x1:
	  op_8XY1(opcode, emu);
	  break;
	case 0x2:
	  op_8XY2(opcode, emu);
	  break;
	case 0x3:
	  op_8XY3(opcode, emu);
	  break;
	case 0x4:
	  op_8XY4(opcode, emu);
	  break;
	case 0x5:
	  op_8XY5(opcode, emu);
	  break;
	case 0x6:
	  op_8XY6(opcode, emu);
	  break;
	case 0x7:
	  op_8XY7(opcode, emu);
	  break;
	case 0xE:
	  op_8XYE(opcode, emu);
	  break;
	default:
	  printf("Unknown opcode\n");
	}
      break ;

    case 0x9000:
      op_9XY0(opcode, emu);
      break ;
    case 0xA000:
      op_ANNN(opcode, emu);
      break ;
    case 0xB000:
      op_BNNN(opcode, emu);
      break ;
    case 0xC000:
      op_CXNN(opcode, emu);
      break ;
    case 0xD000:
      op_DXYN(opcode, emu);
      break ;

    case 0xE000:
      switch (opcode & 0x00FF)
	{
	case 0x9E:
	  op_EX9E(opcode, emu);
	  break ;
	case 0xA1:
	  op_EXA1(opcode, emu);
	  break ;
	default:
	  printf("Unknown opcode\n");
	}
      break ;

    case 0xF000:
      switch (opcode & 0x00FF)
	{
	case 0x0007:
	  op_FX07(opcode, emu);
	  break ;
	case 0x000A:
	  op_FX0A(opcode, emu);
	  break ;
	case 0x0015:
	  op_FX15(opcode, emu);
	  break ;
	case 0x0018:
	  op_FX18(opcode, emu);
	  break ;

	case 0x001E:
	  op_FX1E(opcode, emu);
	  break ;
	case 0x0029:
	  op_FX29(opcode, emu);
	  break ;
	case 0x0033:
	  op_FX33(opcode, emu);
	  break ;
	case 0x0055:
	  op_FX55(opcode, emu);
	  break ;
	case 0x0065:
	  op_FX65(opcode, emu);
	  break ;
	default:
	  printf("Unknown opcode\n");
	}
      break ;
    default:
      printf("Unknown opcode\n");
    }
  return 0;
}

t_emulator	*init_emulator(char *file_name)
{
  FILE	*file;
  t_emulator *emu;
  int	i;

  emu = malloc(sizeof(*emu));
  if ((file = fopen(file_name, "r")) == NULL)
    return NULL;

  fread(&emu->memory[0x200], 1, MEMORY_SIZE, file);
  fclose(file);

  emu->stack_ptr = -1;
  emu->PC = 0x200;
  emu->I = 0;
  emu->timer = 0;
  emu->sound_timer = 0;
  for (i = 0; i < 16; i++)
    emu->cpu_register[i] = 0;
  load_font(emu);
  return emu;
}

int	load_font(t_emulator *emu)
{
  emu->memory[0]=0xF0; emu->memory[1]=0x90; emu->memory[2]=0x90;
  emu->memory[3]=0x90; emu->memory[4]=0xF0;
  emu->memory[5]=0x20; emu->memory[6]=0x60; emu->memory[7]=0x20;
  emu->memory[8]=0x20; emu->memory[9]=0x70;
  emu->memory[10]=0xF0;emu->memory[11]=0x10;emu->memory[12]=0xF0;
  emu->memory[13]=0x80;emu->memory[14]=0xF0;
  emu->memory[15]=0xF0;emu->memory[16]=0x10;emu->memory[17]=0xF0;
  emu->memory[18]=0x10;emu->memory[19]=0xF0;
  emu->memory[20]=0x90;emu->memory[21]=0x90;emu->memory[22]=0xF0;
  emu->memory[23]=0x10;emu->memory[24]=0x10;
  emu->memory[25]=0xF0;emu->memory[26]=0x80;emu->memory[27]=0xF0;
  emu->memory[28]=0x10;emu->memory[29]=0xF0;
  emu->memory[30]=0xF0;emu->memory[31]=0x80;emu->memory[32]=0xF0;
  emu->memory[33]=0x90;emu->memory[34]=0xF0;
  emu->memory[35]=0xF0;emu->memory[36]=0x10;emu->memory[37]=0x20;
  emu->memory[38]=0x40;emu->memory[39]=0x40;
  emu->memory[40]=0xF0;emu->memory[41]=0x90;emu->memory[42]=0xF0;
  emu->memory[43]=0x90;emu->memory[44]=0xF0;
  emu->memory[45]=0xF0;emu->memory[46]=0x90;emu->memory[47]=0xF0;
  emu->memory[48]=0x10;emu->memory[49]=0xF0;
  emu->memory[50]=0xF0;emu->memory[51]=0x90;emu->memory[52]=0xF0;
  emu->memory[53]=0x90;emu->memory[54]=0x90;
  emu->memory[55]=0xE0;emu->memory[56]=0x90;emu->memory[57]=0xE0;
  emu->memory[58]=0x90;emu->memory[59]=0xE0;
  emu->memory[60]=0xF0;emu->memory[61]=0x80;emu->memory[62]=0x80;
  emu->memory[63]=0x80;emu->memory[64]=0xF0;
  emu->memory[65]=0xE0;emu->memory[66]=0x90;emu->memory[67]=0x90;
  emu->memory[68]=0x90;emu->memory[69]=0xE0;
  emu->memory[70]=0xF0;emu->memory[71]=0x80;emu->memory[72]=0xF0;
  emu->memory[73]=0x80;emu->memory[74]=0xF0;
  emu->memory[75]=0xF0;emu->memory[76]=0x80;emu->memory[77]=0xF0;
  emu->memory[78]=0x80;emu->memory[79]=0x80;
  return 0;
}
