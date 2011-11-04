/*
** op.h for  in /home/wotan/projets/chip8
** 
** Made by geoffroy aubey
** Login   <aubey_g@epitech.net>
** 
** Started on  Thu Nov  3 13:33:44 2011 geoffroy aubey
** Last update Thu Nov  3 13:33:44 2011 geoffroy aubey
*/

#ifndef OP_H_
# define OP_H_

int	op_0NNN(WORD opcode, t_emulator *emu);
int	op_00E0(WORD opcode, t_emulator *emu);
int	op_00EE(WORD opcode, t_emulator *emu);
int	op_1NNN(WORD opcode, t_emulator *emu);
int	op_2NNN(WORD opcode, t_emulator *emu);
int	op_3XNN(WORD opcode, t_emulator *emu);
int	op_4XNN(WORD opcode, t_emulator *emu);
int	op_5XY0(WORD opcode, t_emulator *emu);
int	op_6XNN(WORD opcode, t_emulator *emu);
int	op_7XNN(WORD opcode, t_emulator *emu);
int	op_8XY0(WORD opcode, t_emulator *emu);
int	op_8XY1(WORD opcode, t_emulator *emu);
int	op_8XY2(WORD opcode, t_emulator *emu);
int	op_8XY3(WORD opcode, t_emulator *emu);
int	op_8XY4(WORD opcode, t_emulator *emu);
int	op_8XY5(WORD opcode, t_emulator *emu);
int	op_8XY6(WORD opcode, t_emulator *emu);
int	op_8XY7(WORD opcode, t_emulator *emu);
int	op_8XYE(WORD opcode, t_emulator *emu);
int	op_9XY0(WORD opcode, t_emulator *emu);
int	op_ANNN(WORD opcode, t_emulator *emu);
int	op_BNNN(WORD opcode, t_emulator *emu);
int	op_CXNN(WORD opcode, t_emulator *emu);
int	op_DXYN(WORD opcode, t_emulator *emu);
int	op_EX9E(WORD opcode, t_emulator *emu);
int	op_EXA1(WORD opcode, t_emulator *emu);
int	op_FX07(WORD opcode, t_emulator *emu);
int	op_FX0A(WORD opcode, t_emulator *emu);
int	op_FX15(WORD opcode, t_emulator *emu);
int	op_FX18(WORD opcode, t_emulator *emu);
int	op_FX1E(WORD opcode, t_emulator *emu);
int	op_FX29(WORD opcode, t_emulator *emu);
int	op_FX33(WORD opcode, t_emulator *emu);
int	op_FX55(WORD opcode, t_emulator *emu);
int	op_FX65(WORD opcode, t_emulator *emu);

#endif /* !OP_H_ */
