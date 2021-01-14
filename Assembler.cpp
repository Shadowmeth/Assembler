#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <vector>

/*
mov <reg> #<mem>
mov <mem> <reg>

#<mem> is dereferencing the memory address
cmp #<mem> <val>
cmp <reg> <val>
cmp #<mem> <reg>
// ALWAYS SETS ZERO FLAG TO TRUE IF THE SECOND OPERAND IS GREATER THAN OPCODE and FALSE OTHERWISE
// IF THE VALUES ARE SAME EQUAL IS SET

Add/Sub value to memory/register content and store it back there
add #<mem> <val>
add <reg> <val>

sub #<mem> <val>
sub <reg> <val>

info simply prints the contents of registers
halt command exists the program

*/

#define MOV (1LL << 32)
#define CMP (1LL << 33)
#define ADD (1LL << 34)
#define SUB (1LL << 35)
#define INFO (1LL << 36)
#define HALT (1LL << 37)
#define COMMENT (1LL << 38)

class Assembler
{
private:
    using Memory = long long;
    std::ifstream ifile;
    std::vector<std::string> source;
    Memory memory[4096];
    long long RA, RB, RC, RD, RE, RF; // general purpose register
    size_t IP; // Instruction Pointer
    bool overflow, zero, index, equal; // status registers
    std::string current_inst{""};
    
public:
    Assembler(std::string f_name) {
	ifile.open(f_name);
	RA = RB = RC = RD = RE = RF = 0; // we want to keep the compiler happy
	overflow = zero = index = equal = false;
	IP = 0;
    }

    void toLower(std::string& str) {
	for (size_t i = 0; i < str.length(); i++) {
	    if (str[i] >= 'A' && str[i] <= 'Z') {
		str[i] = str[i] + 32;
	    }
	}
    }
    
    void readSource() {
	if (!ifile.is_open()) {
	    std::cerr << "Error opening file (check if it exists or you have appropriate permissions)" << std::endl;
	    return;
	}

	std::string line;

	while (std::getline(ifile, line)) {
	    source.push_back(line);
	}
    }

    void printSource() {
	for (size_t i = 0; i < source.size(); i++) {
	    std::cout << source[i] << std::endl;
	}
    }

    void regInfo() const {
	// displays all the registers contents (for debugging and testing purposes)
	// theres also a special instruction, called info that prints the registers information
	std::cout << "\nGENERAL PURPOSE REGISTERS\n";
	std::cout << "RA = " << RA << '\n';
	std::cout << "RB = " << RB << '\n';
	std::cout << "RC = " << RC << '\n';
	std::cout << "RD = " << RD << '\n';
	std::cout << "RE = " << RE << '\n';
	std::cout << "RF = " << RF << '\n';
	
	std::cout << "\nSPECIAL REGISTERS\n";
	std::cout << "IP       = " << IP << '\n';
	std::cout << std::boolalpha << "overflow = " << overflow << '\n';
	std::cout << std::boolalpha << "zero     = " << zero << '\n';
	std::cout << std::boolalpha << "index    = " << index << '\n';
	std::cout << std::boolalpha << "equal    = " << equal << '\n';
    }

    // fetch the next instruction to be executed
    void fetch() {
	// for now assume the syntax is always right
	// simply return the instruction pointed to by IP and increment IP
	current_inst = source[IP++];
    }

    long long decode () {
	// inst is the instruction we want to decode
	std::string s{""};
	for (size_t i = 0; i < current_inst.length(); i++) {
	    if (current_inst[i] == ' ') {
		break;
	    } else if (current_inst[i] == '/' && (i + 1) != current_inst.length() && current_inst[i + 1] == '/') {
		// The condition relies on some short circuiting magic to not read past string buffer
		return COMMENT;
	    }
	    s += current_inst[i];
	}
	
	toLower(s);
	
	if (s == "mov")
	    return MOV;
	else if (s == "cmp")
	    return CMP;
	else if (s == "add")
	    return ADD;
	else if (s == "sub")
	    return SUB;
	else if (s == "info")
	    return INFO;
	else if (s == "halt")
	    return HALT;

	return -1; // Some invalid instruction was found
    }
    
    void run() {
	// actual bytecode excution happens here
	// von neumann architecture:
	// fetch instruction
	// decode instruction
	// execute instruction
	
	while (true) {
	    fetch();
	    long long inst = decode();

	switch (inst) {
	case HALT: {
	    // halt instruction found, simply break the loop
	    break;
	}

	case MOV: {
	    
	}    
	    
	}
	    
	}
	
    }
	


};

int main()
{
    // We want 8 byte long memory
    // 4 byte opcode and 4 byte operand
    // This is extremely inefficient for memory as no one needs 2**32 opcodes but for easier implementation
    // we are going with this
    assert(sizeof(long long) == 8 && "BUS Size is incompatible for the architecture");
    
    Assembler *as = new Assembler("lmao.source");
    as->readSource();
    as->run();
    
}
