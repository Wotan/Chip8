#include <stdlib.h>
#include <stdio.h>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include "emulator.h"
#include "op.h"

WORD		Emulator::GetWord(int addr) const
{
  WORD		opcode = 0;

  opcode = memory[addr];
  opcode <<= 8;
  opcode |= memory[addr + 1];
  return opcode;
}

int		Emulator::DoCycle()
{
  WORD opcode;

  opcode = GetWord(PC);
  PC += 2;
  if (timer > 0)
    timer--;
  printf("opcode = %04x\n", opcode);
  switch (opcode & 0xF000)
    {
    case 0x0000:
      switch (opcode & 0x00FF)
	{
	case 0xE0:
	  op_00E0(opcode);
	  break;
	case 0xEE:
	    op_00EE(opcode);
	    break;
	default:
	  printf("Unknown opcode\n");
	}
      break ;

    case 0x1000:
      op_1NNN(opcode);
      break ;
    case 0x2000:
      op_2NNN(opcode);
      break ;
    case 0x3000:
      op_3XNN(opcode);
      break ;
    case 0x4000:
      op_4XNN(opcode);
      break ;
    case 0x5000:
      op_5XY0(opcode);
      break ;
    case 0x6000:
      op_6XNN(opcode);
      break ;
    case 0x7000:
      op_7XNN(opcode);
      break ;

    case 0x8000:
      switch (opcode & 0x000F)
	{
	case 0x0:
	  op_8XY0(opcode);
	  break;
	case 0x1:
	  op_8XY1(opcode);
	  break;
	case 0x2:
	  op_8XY2(opcode);
	  break;
	case 0x3:
	  op_8XY3(opcode);
	  break;
	case 0x4:
	  op_8XY4(opcode);
	  break;
	case 0x5:
	  op_8XY5(opcode);
	  break;
	case 0x6:
	  op_8XY6(opcode);
	  break;
	case 0x7:
	  op_8XY7(opcode);
	  break;
	case 0xE:
	  op_8XYE(opcode);
	  break;
	default:
	  printf("Unknown opcode\n");
	}
      break ;

    case 0x9000:
      op_9XY0(opcode);
      break ;
    case 0xA000:
      op_ANNN(opcode);
      break ;
    case 0xB000:
      op_BNNN(opcode);
      break ;
    case 0xC000:
      op_CXNN(opcode);
      break ;
    case 0xD000:
      op_DXYN(opcode);
      break ;

    case 0xE000:
      switch (opcode & 0x00FF)
	{
	case 0x9E:
	  op_EX9E(opcode);
	  break ;
	case 0xA1:
	  op_EXA1(opcode);
	  break ;
	default:
	  printf("Unknown opcode\n");
	}
      break ;

    case 0xF000:
      switch (opcode & 0x00FF)
	{
	case 0x0007:
	  op_FX07(opcode);
	  break ;
	case 0x000A:
	  op_FX0A(opcode);
	  break ;
	case 0x0015:
	  op_FX15(opcode);
	  break ;
	case 0x0018:
	  op_FX18(opcode);
	  break ;

	case 0x001E:
	  op_FX1E(opcode);
	  break ;
	case 0x0029:
	  op_FX29(opcode);
	  break ;
	case 0x0033:
	  op_FX33(opcode);
	  break ;
	case 0x0055:
	  op_FX55(opcode);
	  break ;
	case 0x0065:
	  op_FX65(opcode);
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

Emulator::Emulator()
{
  QString	fileName;

  stack_ptr = -1;
  PC = 0x200;
  I = 0;
  timer = 0;
  sound_timer = 0;
  for (int i = 0; i < 16; i++)
    cpu_register[i] = 0;
  LoadFont();
}

bool	Emulator::Open(QString &fileName)
{
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly))
    return false;
  file.read((char *)&memory[0x200], MEMORY_SIZE);
  file.close();
  return true;
}

void	Emulator::SetGraphics(Graphics *new_graphics)
{
  graphics = new_graphics;
}

int	Emulator::LoadFont()
{
  memory[0]=0xF0; memory[1]=0x90; memory[2]=0x90;
  memory[3]=0x90; memory[4]=0xF0;
  memory[5]=0x20; memory[6]=0x60; memory[7]=0x20;
  memory[8]=0x20; memory[9]=0x70;
  memory[10]=0xF0;memory[11]=0x10;memory[12]=0xF0;
  memory[13]=0x80;memory[14]=0xF0;
  memory[15]=0xF0;memory[16]=0x10;memory[17]=0xF0;
  memory[18]=0x10;memory[19]=0xF0;
  memory[20]=0x90;memory[21]=0x90;memory[22]=0xF0;
  memory[23]=0x10;memory[24]=0x10;
  memory[25]=0xF0;memory[26]=0x80;memory[27]=0xF0;
  memory[28]=0x10;memory[29]=0xF0;
  memory[30]=0xF0;memory[31]=0x80;memory[32]=0xF0;
  memory[33]=0x90;memory[34]=0xF0;
  memory[35]=0xF0;memory[36]=0x10;memory[37]=0x20;
  memory[38]=0x40;memory[39]=0x40;
  memory[40]=0xF0;memory[41]=0x90;memory[42]=0xF0;
  memory[43]=0x90;memory[44]=0xF0;
  memory[45]=0xF0;memory[46]=0x90;memory[47]=0xF0;
  memory[48]=0x10;memory[49]=0xF0;
  memory[50]=0xF0;memory[51]=0x90;memory[52]=0xF0;
  memory[53]=0x90;memory[54]=0x90;
  memory[55]=0xE0;memory[56]=0x90;memory[57]=0xE0;
  memory[58]=0x90;memory[59]=0xE0;
  memory[60]=0xF0;memory[61]=0x80;memory[62]=0x80;
  memory[63]=0x80;memory[64]=0xF0;
  memory[65]=0xE0;memory[66]=0x90;memory[67]=0x90;
  memory[68]=0x90;memory[69]=0xE0;
  memory[70]=0xF0;memory[71]=0x80;memory[72]=0xF0;
  memory[73]=0x80;memory[74]=0xF0;
  memory[75]=0xF0;memory[76]=0x80;memory[77]=0xF0;
  memory[78]=0x80;memory[79]=0x80;
  return 0;
}
