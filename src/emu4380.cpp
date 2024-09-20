#include <iostream>
#include <cstring>
#include <typeinfo>
#include "../include/emu4380.h"

using namespace std;

unsigned int reg_file[22] = {0};
unsigned char* prog_mem = nullptr;
unsigned int cntrl_regs[5] = {0};
unsigned int data_regs[2] = {0};
unsigned int max_size = 131072;
unsigned int addr = 0;

bool fetch(){ 
	if(reg_file[PC] + 8 > max_size){
		return false;
	};
	addr = reg_file[PC];
	cntrl_regs[OPERATION] =*((unsigned char*)(&prog_mem[addr]));
	cntrl_regs[OPERAND_1] =*((unsigned char*)(&prog_mem[addr+1]));
	cntrl_regs[OPERAND_2] =*((unsigned char*)(&prog_mem[addr+2]));
	cntrl_regs[OPERAND_3] =*((unsigned char*)(&prog_mem[addr+3]));
	cntrl_regs[IMMEDIATE] =*((unsigned char*)(&prog_mem[addr+4]));
	reg_file[PC] += 8;
	return true;
};

bool decode(){
	if(cntrl_regs[OPERATION] == 1){
	//JMP
		if(cntrl_regs[IMMEDIATE] > max_size){
			return false;
		};
		return true;

	}else if(cntrl_regs[OPERATION] == 7){
	//MOV
		if(cntrl_regs[OPERAND_1] > 15){
			return false;
		}else if(cntrl_regs[OPERAND_2] > 15){
			return false;
		};
		data_regs[REG_VAL_1] = cntrl_regs[OPERAND_1];
		data_regs[REG_VAL_2] = cntrl_regs[OPERAND_2];
		return true;

	}else if(cntrl_regs[OPERATION] == 8){
	//MOVI
		if(cntrl_regs[OPERAND_1] > 15){
			return false;
		};
		data_regs[REG_VAL_1] = cntrl_regs[OPERAND_1];
		return true;

	}else if(cntrl_regs[OPERATION] == 9){
	//LDA
		if(cntrl_regs[OPERAND_1] > 15){
			return false;
		};
		if(cntrl_regs[IMMEDIATE] > max_size){
			return false;
		};
		data_regs[REG_VAL_1] = cntrl_regs[OPERAND_1];
		return true;

	}else if(cntrl_regs[OPERATION] == 10){
	//STR
		if(cntrl_regs[OPERAND_1] > 15){
			return false;
		};
		if(cntrl_regs[IMMEDIATE] > max_size){
			return false;
		};
		data_regs[REG_VAL_1] = cntrl_regs[OPERAND_1];
		return true;

	}else if(cntrl_regs[OPERATION] == 11){
	//LDR
		if(cntrl_regs[OPERAND_1] > 15){
			return false;
		};
		if(cntrl_regs[IMMEDIATE] > max_size){
			return false;
		};
		data_regs[REG_VAL_1] = cntrl_regs[OPERAND_1];
		return true;

	}else if(cntrl_regs[OPERATION] == 12){
	//STB
		if(cntrl_regs[OPERAND_1] > 15){
			return false;
		};
		if(cntrl_regs[IMMEDIATE] > max_size){
			return false;
		};
		data_regs[REG_VAL_1] = cntrl_regs[OPERAND_1];
		return true;

	}else if(cntrl_regs[OPERATION] == 13){
	//LDB
		if(cntrl_regs[OPERAND_1] > 15){
			return false;
		};
		if(cntrl_regs[IMMEDIATE] > max_size){
			return false;
		};
		data_regs[REG_VAL_1] = cntrl_regs[OPERAND_1];
		return true;

	}else if(cntrl_regs[OPERATION] == 18){
	//ADD
		if(cntrl_regs[OPERAND_1] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_2] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_3] > 15){
                        return false;
                };
                data_regs[REG_VAL_1] = reg_file[cntrl_regs[OPERAND_2]];
                data_regs[REG_VAL_2] = reg_file[cntrl_regs[OPERAND_3]];
		return true;

	}else if(cntrl_regs[OPERATION] == 19){
	//ADDI
		if(cntrl_regs[OPERAND_1] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_2] > 15){
                        return false;
                };
                data_regs[REG_VAL_1] = reg_file[cntrl_regs[OPERAND_2]];
		return true;
	}else if(cntrl_regs[OPERATION] == 20){
	//SUB
		if(cntrl_regs[OPERAND_1] > 15){
			return false;
		};
		if(cntrl_regs[OPERAND_2] > 15){
			return false;
		};
		if(cntrl_regs[OPERAND_3] > 15){
			return false;
		};
		data_regs[REG_VAL_1] = reg_file[cntrl_regs[OPERAND_2]];
		data_regs[REG_VAL_2] = reg_file[cntrl_regs[OPERAND_3]];
		return true;

	}else if(cntrl_regs[OPERATION] == 21){
	//SUBI
		if(cntrl_regs[OPERAND_1] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_2] > 15){
                        return false;
                };
                data_regs[REG_VAL_1] = reg_file[cntrl_regs[OPERAND_2]];
		return true;

	}else if(cntrl_regs[OPERATION] == 22){
	//MUL
		if(cntrl_regs[OPERAND_1] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_2] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_3] > 15){
                        return false;
                };
                data_regs[REG_VAL_1] = reg_file[cntrl_regs[OPERAND_2]];
                data_regs[REG_VAL_2] = reg_file[cntrl_regs[OPERAND_3]];
		return true;

	}else if(cntrl_regs[OPERATION] == 23){
	//MULI
		if(cntrl_regs[OPERAND_1] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_2] > 15){
                        return false;
                };
                data_regs[REG_VAL_1] = reg_file[cntrl_regs[OPERAND_2]];
		return true;

	}else if(cntrl_regs[OPERATION] == 24){
	//DIV
		if(cntrl_regs[OPERAND_1] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_2] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_3] > 15){
                        return false;
                };
                data_regs[REG_VAL_1] = reg_file[cntrl_regs[OPERAND_2]];
                data_regs[REG_VAL_2] = reg_file[cntrl_regs[OPERAND_3]];
		return true;

	}else if(cntrl_regs[OPERATION] == 25){
	//SDIV
		if(cntrl_regs[OPERAND_1] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_2] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_3] > 15){
                        return false;
                };
                data_regs[REG_VAL_1] = reg_file[cntrl_regs[OPERAND_2]];
                data_regs[REG_VAL_2] = reg_file[cntrl_regs[OPERAND_3]];
		return true;

	}else if(cntrl_regs[OPERATION] == 26){
	//DIVI
		if(cntrl_regs[OPERAND_1] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_2] > 15){
                        return false;
                };
                if(cntrl_regs[OPERAND_3] > 15){
                        return false;
                };
                data_regs[REG_VAL_1] = reg_file[cntrl_regs[OPERAND_2]];
                data_regs[REG_VAL_2] = reg_file[cntrl_regs[OPERAND_3]];
		return true;

	}else if(cntrl_regs[OPERATION] == 31){
	//TRP
		//Tried a != or statement here, wasn't working so I gave up
		if(cntrl_regs[IMMEDIATE] == 0){
			return true;
		}else if(cntrl_regs[IMMEDIATE] == 1){
			return true;
		}else if(cntrl_regs[IMMEDIATE] == 2){
                        return true;
                }else if(cntrl_regs[IMMEDIATE] == 3){
                        return true;
                }else if(cntrl_regs[IMMEDIATE] == 4){
                        return true;
                }else if(cntrl_regs[IMMEDIATE] == 98){
                        return true;
                };
		return false;
	};

	return false;
};

bool execute(){
	if(cntrl_regs[OPERATION] == 1){
	//JMP
		reg_file[PC] = cntrl_regs[IMMEDIATE];
		return true;
	}else if(cntrl_regs[OPERATION] == 7){
	//MOV
		reg_file[data_regs[REG_VAL_1]] = reg_file[data_regs[REG_VAL_2]];
		return true;
	}else if(cntrl_regs[OPERATION] == 8){
	//MOVI
		reg_file[data_regs[REG_VAL_1]] = cntrl_regs[IMMEDIATE];
		//cout << "MOVI" <<reg_file[data_regs[REG_VAL_1]] << endl;
		return true;
	}else if(cntrl_regs[OPERATION] == 9){
	//LDA
		reg_file[data_regs[REG_VAL_1]] = cntrl_regs[IMMEDIATE];
		return true;
	}else if(cntrl_regs[OPERATION] == 10){
	//STR
		prog_mem[cntrl_regs[IMMEDIATE]] = data_regs[REG_VAL_1];
		return true;
	}else if(cntrl_regs[OPERATION] == 11){
	//LDR
		reg_file[data_regs[REG_VAL_1]] = *((unsigned char*)(&prog_mem[cntrl_regs[IMMEDIATE]]));
		return true;
	}else if(cntrl_regs[OPERATION] == 12){
	//STB
		prog_mem[cntrl_regs[IMMEDIATE]] = data_regs[REG_VAL_1];
		return true;
	}else if(cntrl_regs[OPERATION] == 13){
	//LDB
		reg_file[data_regs[REG_VAL_1]] = *((unsigned char*)(&prog_mem[cntrl_regs[IMMEDIATE]]));
		return true;
	}else if(cntrl_regs[OPERATION] == 18){
	//ADD
		reg_file[cntrl_regs[OPERAND_1]] = (data_regs[REG_VAL_1] + data_regs[REG_VAL_2]);
		return true;
	}else if(cntrl_regs[OPERATION] == 19){
	//ADDI
		reg_file[cntrl_regs[OPERAND_1]] = (data_regs[REG_VAL_1] + cntrl_regs[IMMEDIATE]);
		return true;
	}else if(cntrl_regs[OPERATION] == 20){
	//SUB
		//cout << "First: " << data_regs[REG_VAL_1] << " Second: " << data_regs[REG_VAL_2] << endl;
		reg_file[cntrl_regs[OPERAND_1]] = (data_regs[REG_VAL_1] - data_regs[REG_VAL_2]);
		//cout << "SUB" << reg_file[cntrl_regs[OPERAND_1]] << endl;
		return true;
	}else if(cntrl_regs[OPERATION] == 21){
	//SUBI
		reg_file[cntrl_regs[OPERAND_1]] = (data_regs[REG_VAL_1] - cntrl_regs[IMMEDIATE]); 
		return true;
	}else if(cntrl_regs[OPERATION] == 22){
	//MUL
		reg_file[cntrl_regs[OPERAND_1]] = (data_regs[REG_VAL_1] * data_regs[REG_VAL_2]);
		return true;
	}else if(cntrl_regs[OPERATION] == 23){
	//MULI
		reg_file[cntrl_regs[OPERAND_1]] = (data_regs[REG_VAL_1] * cntrl_regs[IMMEDIATE]);
		return true;
	}else if(cntrl_regs[OPERATION] == 24){
	//DIV
	//Ask about  all these divisions
		reg_file[cntrl_regs[OPERAND_1]] = (data_regs[REG_VAL_1] / data_regs[REG_VAL_2]);
		return true;
	}else if(cntrl_regs[OPERATION] == 25){
	//SDIV
		reg_file[cntrl_regs[OPERAND_1]] = (data_regs[REG_VAL_1] / data_regs[REG_VAL_2]);
		return true;
	}else if(cntrl_regs[OPERATION] == 26){
	//DIVI
		reg_file[cntrl_regs[OPERAND_1]] = (data_regs[REG_VAL_1] / cntrl_regs[IMMEDIATE]);
		return true;
	}else if(cntrl_regs[OPERATION] == 31){
		if(cntrl_regs[IMMEDIATE] == 0){
			exit(0);
		}else if(cntrl_regs[IMMEDIATE] == 1){
			cout << reg_file[R3];
			return true;
		}else if(cntrl_regs[IMMEDIATE] == 2){
			cin >> reg_file[R3];
			return true;
		}else if(cntrl_regs[IMMEDIATE] == 3){
			cout << char(reg_file[R3]);
			return true;
		}else if(cntrl_regs[IMMEDIATE] == 4){
			cin >> reg_file[R3];
			return true;
		}else if(cntrl_regs[IMMEDIATE] == 98){
			cout << "R0	" << reg_file[R0] << endl;
			cout << "R1     " << reg_file[R1] << endl;
			cout << "R2     " << reg_file[R2] << endl;
			cout << "R3     " << reg_file[R3] << endl;
			cout << "R4     " << reg_file[R4] << endl;
			cout << "R5     " << reg_file[R5] << endl;
			cout << "R6     " << reg_file[R6] << endl;
			cout << "R7     " << reg_file[R7] << endl;
			cout << "R8     " << reg_file[R8] << endl;
			cout << "R9     " << reg_file[R9] << endl;
			cout << "R10     " << reg_file[R10] << endl;
			cout << "R11     " << reg_file[R11] << endl;
			cout << "R12     " << reg_file[R12] << endl;
			cout << "R13     " << reg_file[R13] << endl;
			cout << "R14     " << reg_file[R14] << endl;
			cout << "R15     " << reg_file[R15] << endl;
			cout << "PC     " << reg_file[PC] << endl;
			cout << "SL     " << reg_file[SL] << endl;
			cout << "SB     " << reg_file[SB] << endl;
			cout << "SP     " << reg_file[SP] << endl;
			cout << "FP     " << reg_file[FP] << endl;
			cout << "HP     " << reg_file[HP] << endl;
			return true;
		};
		return false;
	};
	return false;
};

bool init_mem(unsigned int size){
	prog_mem = new unsigned char[size];
	if(!prog_mem){
		return false;
	};
	memset(prog_mem, 0, size);
	return true;
};
