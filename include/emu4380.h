#pragma once
#ifndef EMU_4380_H
#define EMU_4380_H

extern unsigned int reg_file[22];
extern unsigned char* prog_mem;
extern unsigned int  cntrl_regs[5];
extern unsigned int data_regs[2];
//Added vars for utility
extern unsigned int max_size;
extern unsigned int addr;

enum RegNames{R0=0, R1=1, R2=2, R3=3, R4=4, R5=5, R6=6, R7=7, R8=8, R9=9, R10=10, R11=11, R12=12, R13=13, R14=14, R15=15, PC=16, SL=17, SB=18, SP=19, FP=20, HP=21};
enum CntrlRegNames{OPERATION=0, OPERAND_1=1, OPERAND_2=2, OPERAND_3, IMMEDIATE=4};
enum DataRegNames{REG_VAL_1=0, REG_VAL_2};

bool fetch();
bool decode();
bool execute();
bool init_mem(unsigned int size);

#endif
