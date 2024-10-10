import sys

#Error in sub line when processing instructions

#label is always 4 bytes aka uses 4 spots in list

#operand_list = []
#Later change byte_list[0] to be Start of Instructions
byte_list = [[0,0,0,0]]
#byte_list at start of input, is the address ie byte_list[12] = 12 for address
#initialize first 4 bytes as 0, first byte is start of instructions

#populate byte_list as we go
symbolsTable = {}
#store label, and then label index aka address
#use symbol_table to fill byte_list values 

def processData(line,lineNum):
	#Handles blank lines, comment lines, and directive lines
	#Process each line in file, until instruction
	#directive begins with .
	#label must begin with alphanumeric
	#running = True
	state = "Start"
	#Start of line
	label = ""
	directive = ""
	int_val = ""
	byt_val = ""
	#Iterator
	i = 0
	while(True):
		char = line[i]
		match state:
			case "Start":
				if char == ";":
					return 0
				elif char ==" " or char == "\t":
					state = "Saw Whitespace"
				elif char == "\n":
					return 0
				elif char.isalnum():
					state = "Label"
					label += char
				else:
					#Error, mainly checked for _ and $
					return 1
			case "Saw Whitespace":
				if char == " " or char == "\t":
					pass
				elif char == ";" or char == "\n":
					return 0
				elif char == ".":
					state = "Directive"
				elif char.isalpha():
					#Start of instructions
					state = "Instruction Start"
					#return -1
			case "Label":
				if char.isalnum() or char == "_" or char == "$":
					label += char
				elif char == " " or char == "\t":
					symbolsTable[label] = lineNum
					state = "Label Done"
				else:
					#Including \n as this would be an error
					return 1

			case "Label Done":
				if char == " " or char == "\t":
					pass
				elif char == ".":
					state = "Directive"
				elif char.isalpha():
					#Start of instructions
					state = "Instruction Start"
				else:
					return 1

			case "Directive":
				if char == " " or char == "\t":
					if directive.lower() == "byt":
						state = "Directive Byt"
					elif directive.lower() == "int":
						state = "Directive Int"
					else:
						return 1
				elif char == "\n" or char ==";":
					if directive.lower() == "byt":
						#Add implementation to store values
						#Might not be able to be a blank byt, check this
						state = "Byte Zero"
					elif directive.lower() == "int":
						#Initialize int as 0's
						state ="Int Zero"
					else:
						#Error, improper directive
						return 1
				elif char.isalpha():
					directive += char
				else:
					#Error, expecting alpha, whitespace, \n or ;
					return 1
			case "Directive Int":
				if char == " " or char == "\t":
					pass
				elif char =="#":
					state = "Int Start"
				elif char.isalnum():
					int_val += char
					state = "Int Start"
				else:
					state = "Int Zero"
			case "Int Start":
				if char.isalnum() or char == "-":
					int_val += char
				elif char == " " or char == "\t" or char == "\n" or char == ";":
					if(len(int_val) <= 1):
						byte_list.append([ord(int_val),0,0,0])
						#print(byte_list)
					else:
						byte_list.append([int(int_val),0,0,0])
						#print(byte_list)
					return 0
				else:
					return 1
			case "Int Zero":
				byte_list.append([0,0,0,0])
				#print(byte_list)
				return 0
			case "Directive Byt":
				if char == " " or char == "\t":
					pass
				elif char.isalnum() or char == "\\":
					byt_val += char
					state = "Byte Start"
				elif char == "#" or char == "'":
					state = "Byte Start"
			case "Byte Start":
				#if char==" " or char=="\t" or char=="\n" or char==";":
				if char == "'":
					#print(byt_val)
					if len(byt_val) == 1:
						byte_list.append([ord(byt_val)])
					elif byt_val == r"\t":
						byte_list.append([ord("\t")])
					elif byt_val == r"\\":
						#Not 100% sure this works
						byte_list.append([ord("\\")])
					elif byt_val == r"\n":
						byte_list.append([ord("\n")])
					elif byt_val == r"\'":
						byte_list.append([ord("\'")])
					elif byt_val == r"\"":
						byte_list.append([ord("\"")])
					elif byt_val == r"\r":
						byte_list.append([ord("\r")])
					elif byt_val == r"\b":
						byte_list.append([ord("\b")])
					else:
						byte_list.append([int(byt_val)])
					#print(byte_list)
					return 0

				else:
					byt_val += char
			case "Byte Zero":
				byte_list.append([0])
				#print(byte_list)
				return 0
			case "Instruction Start":
				#First instruction, set first byte
				index = 0
				for byte in byte_list:
					for val in byte:
						index += 1
				#print(index)
				byte_list[0][0] = index
				return -1
		#Move iterator up
		i += 1
		if i == len(line):
			#Temp error check, might keep
			return 1

	return 1
	#If end of file is hit in this function, is an error
	#expecting at least 1 instruction

def validateVal(val):
	if len(val) == 0:
		return 0
	elif val.lower().startswith("r") and val[1:].isdigit():
		return int(val[1:])
	elif val.isdigit() or val[1:].isdigit():
		return int(val)
	elif len(val) == 1 and symbolsTable.get(val) == None:
		return ord(val)
	else:
		return val

def processInstruction(line, lineNum):
	state = "Start"
	#Only used for Special Case
	prevState = ""
	currentOperand = 1

	label = ""
	instruction = ""
	value = None
	operand1 = ""
	operand2 = ""
	operand3 = ""
	immediate = ""

	#Iterator 
	i = 0
	while(True):
		char = line[i]
		match state:
			case "Start":
				if char.isalpha():
					state = "Label Start"
					label += char
				elif char == " " or char == "\t":
					state = "Instruction Start"
				elif char == "\n" or char == ";":
					return 0
				else:
					return 1
			case "Label Start":
				if char.isalnum() or char == "$" or char == "_":
					label += char
				elif char == " " or char == "\t":
					state = "Instruction Start"
					symbolsTable[label] = lineNum
					#print(symbolsTable)
				else:
					#\n, ;, anything else
					return 1
			case "Instruction Start":
				if char.isalpha():
					instruction += char
				elif char == " " or char == "\t":
					#print(instruction)
					if instruction.lower() == "jmp":
						value = 1
						state = "Immediate"
					elif instruction.lower() == "mov":
						value = 7
						state = "Operand 1"
					elif instruction.lower() == "movi":
						value = 8
						state = "Operand 1"
					elif instruction.lower() == "lda":
						value = 9
						state = "Operand 1"
					elif instruction.lower() == "str":
						value = 10
						state = "Operand 1"
					elif instruction.lower() == "ldr":
						value = 11
						state = "Operand 1"
					elif instruction.lower() == "stb":
						value = 12
						state = "Operand 1"
					elif instruction.lower() == "ldb":
						value = 13
						state = "Operand 1"
					elif instruction.lower() == "add":
						value = 18
						state = "Operand 1"
					elif instruction.lower() == "addi":
						value = 19
						state = "Operand 1"
					elif instruction.lower() == "sub":
						value = 20
						state = "Operand 1"
					elif instruction.lower() == "subi":
						value = 21
						state = "Operand 1"
					elif instruction.lower() == "mul":
						value = 22
						state = "Operand 1"
					elif instruction.lower() == "muli":
						value = 23
						state = "Operand 1"
					elif instruction.lower() == "div":
						value = 24
						state = "Operand 1"
					elif instruction.lower() == "sdiv":
						value = 25
						state = "Operand 1"
					elif instruction.lower() == "divi":
						value = 26
						state = "Operand 1"
					elif instruction.lower() == "trp":
						value = 31
						state = "Immediate"
					else:
						#Invalid Instruction
						return 1

			case "Immediate":
				if char == " " or char == "\t" or char == "#":
					pass
				elif char == "'":
					prevState = "Immediate"
					currentOperand = 4
					state = "Special Case"
				elif char.isalnum():
					immediate += char
				elif char == "\n" or char == ";":
					state = "Push Values"
					i -= 1
				else:
					return 1
			case "Operand 1":
				if char == ",":
					if value >= 8 and value <= 13:
						state = "Immediate"
					else:
						state = "Operand 2"
				elif char == " " or char == "\t":
					pass
				elif char == "\n" or char == ";":
					state = "Push Values"
					i -= 1
				elif char == "#":
					pass
				elif char == "'":
					prevState = "Operand 1"
					currentOperand = 1
					state = "Special Case"
				else:
					operand1 += char
			case "Operand 2":
				if char == ",":
					#print(operand2)
					if value == 19 or value == 21 or value == 23 or value == 26:
						state = "Immediate"
					else:
						state = "Operand 3"
				elif char == " " or char == "\t":
					pass
				elif char == "\n" or char == ";":
					state = "Push Values"
					i -= 1
				elif char == "#":
					pass
				elif char == "'":
					prevState = "Operand 2"
					currentOperand = 2
					state = "Special Case"
				else:
					operand2 += char
			case "Operand 3":
				if char == ",":
					state = "Immediate"
				elif char == " " or char == "\t":
					pass
				elif char == "\n" or char == ";":
					state = "Push Values"
					i -= 1
				elif char == "#":
					pass
				elif char == "'":
					prevState = "Operand 3"
					currentOperand = 3
					state = "Special Case"
				else:
					operand3 += char
			case "Special Case":
				if char == "'":
					state = prevState
				else:
					if currentOperand == 1:
						operand1 += char
					elif currentOperand == 2:
						operand2 += char
					elif currentOperand == 3:
						operand3 += char
					elif currentOperand == 4:
						immediate += char
			case "Push Values":
				values = []
				values.append(value)
				#print(operand1,operand2,operand3,immediate)
				values.append(validateVal(operand1))
				values.append(validateVal(operand2))
				values.append(validateVal(operand3))
				values.append(validateVal(immediate))
				values.append(0)
				values.append(0)
				values.append(0)
				#print(values)
				byte_list.append(values)
				return 0

		#Temp error check
		if i == len(line):
			return 1
		i += 1
	return 1
def link():
	byteNum = 0
	for byte in byte_list:
		valNum = 0
		for val in byte:
			if type(val) == str:
				labelLineNum = symbolsTable[val]
				bytesToValue = byte_list[:labelLineNum]
				index = 0
				for i in bytesToValue:
					index += len(i)
				#print(index,"\n") 
				byte_list[byteNum][valNum] = index
				#print(byte_list[labelLineNum],"\n")
			valNum += 1
		byteNum += 1
	#Ensuring all labels are processed, else error
	for byte in byte_list:
		for val in byte:
			if type(val) == str:
				return 1
	return 0

def output(outputFileName):
	with open(outputFileName,"wb") as binary_file:
		for byte in byte_list:
			for val in byte:
				someBytes = val.to_bytes(1,"little")
				binary_file.write(someBytes)
	binary_file.close()

def main():
	#Validate argv[1] is a asm file
	if(len(sys.argv) < 2 or sys.argv[1].endswith(".asm") != True):
		print("USAGE: python3 asm4380.py inputFile.asm")
		return
	fileName = sys.argv[1]
	f = open(fileName,'r')
	#Retrieve all lines in file
	lines = []
	for line in f:
		lines.append(line)
	f.close()
	lineNum = 1

	#Start of processData
	while(True):
		if lineNum == len(lines) + 1:
			#Might want better message here
			print("Assembler error: Expecting at least 1 instruction!")
			return 2
		valid = processData(lines[lineNum-1],lineNum)
		if valid > 0:
			print("Assembler error encountered on line {}!".format(lineNum))
			return 2
		elif valid < 0:
			#Will return -1 if start of instructions
			break
		lineNum += 1

	#Start of processInstructions
	while(True):
		if lineNum == len(lines) + 1:
			break
		valid = processInstruction(lines[lineNum-1],lineNum)
		if valid > 0:
			print("Assembler error encountered on line {}!".format(lineNum))
			return 2

		lineNum += 1

	#Replace Lables with Values
	valid = link()
	if valid != 0:
			#Will be 1 if there is a remaining "label" in the byte_list after initial run
			print("Assembler error encoutered on line {}".format(lineNum))
			return 2

	#Process Output
	outputFileName = fileName[:-3] + "bin"
	output(outputFileName)
	return 0

if __name__ == "__main__":
	main()
