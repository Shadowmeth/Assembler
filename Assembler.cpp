#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <vector>
using namespace std;

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

*/

#define MOV 1LL << 32 
#define CMP 1LL << 33
#define ADD 1LL << 34
#define SUB 1LL << 35

class Assembler
{
private:
	using Memory = long long;
	ifstream ifile;
	std::vector<string> source;
	Memory memory[4096];
	long long RA, RB, RC, RD, RE, RF; // general purpose register
	long long IP; // Instruction Pointer
	bool overflow, zero, index, equal; // status registers

public:
	Assembler(string f_name)
	{
		ifile.open(f_name);
		RA = RB = RC = RD = RE = RF = IP = 0; // we want to keep the compiler happy
		overflow = zero = index = equal = false;
	}

	void readSource() 
	{
		if (!ifile.is_open()) {
			cerr << "Error opening file" << endl;
			return;
		}

		string line;

		while (getline(ifile, line)) {
			source.push_back(line);
		}
	}

	void printSource() {
		for (int i = 0; i < source.size(); i++) {
			cout << source[i] << endl;
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
	/*
	Assembler *as = new Assembler("lmao.source");
	as->readSource();
	as->printSource();
	*/	
	cout << 125 << endl;
	cout << MOV << endl;
	cout << CMP << endl;

}
