#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include "../include/emu4380.h"

using namespace std;

//unsigned int max_size = 131072;

int main(int argc, char *argv[]){
	//argv validation
	//unsigned int max = 131072;
	if(argc == 1){
		cout << "Error: Expecting command line arguments (min 1, max 2)." << endl;
		return 1;
	}else if(argc == 3){
		max_size = stoi(argv[2]);
	}else if(argc > 3){
		cout << "Command line arguments after argv[2] ignored." << endl;
		max_size = stoi(argv[2]);
	};

	//Open file, validation that file is open
	string file_name;
	file_name = argv[1];
	ifstream file(file_name, ios::binary);
	//ifstream file(file_name);
	if(!file.is_open()){
		cout << "Error: Could not open file." << endl;
		return 2;
	};

	//To get file size to test if max is enough
	file.seekg(0, ios::end);
	streamsize file_size = file.tellg();
	file.seekg(0, ios::beg);
	if(max_size < file_size){
		cout << "Error: Insufficiant memory for file." << endl;
		file.close();
		return 2;
	};
	//Mock way to make a binary file.
	/*ofstream tester("tester.dat", ifstream::binary);
	unsigned int value = 0;
	while(file >> value){
		tester.write((char*)&value, 1);
	};*/

	//Checking if prog_mem initialization succeeds
	if(!init_mem(max_size)){
		cout << "Error initiating memory." << endl;
		file.close();
		return 2;
	};
	file.read(reinterpret_cast<char*>(prog_mem),file_size);
	// *((unsigned int*)(&prog_mem[59]));
	file.close();
	//tester.close();
	reg_file[PC] =*((unsigned int*)(&prog_mem[0]));
	reg_file[SL] = 0;
	reg_file[SB] =max_size;
	
	//cout <<*((unsigned int*)(&prog_mem[0])) << endl;
	int j = 0;
	while(true){
		if(!fetch()){
			cout << "INVALID INSTRUCTION AT (fetch): " << addr << endl;
			return 1;
		};
		if(!decode()){
			cout << "INVALID INSTRUCTION AT (decode): " << addr << endl;
			return 1;
		};
		if(!execute()){
			cout << "INVALID INSTRUCTION AT (ex): " << addr << endl;
			return 1;
		};
		/*if(j > 40){
			break;
		};
		j++;*/
	};

	return 0;
};
