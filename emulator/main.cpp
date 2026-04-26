/*
 * Making an emulator for the 6502
 * Using https://www.youtube.com/playlist?list=PLLwK93hM93Z13TRzPx9JqTIn33feefl37
 * http://www.obelisk.me.uk/6502/
*/

#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Mem {
	static constexpr u32 MAX_MEM = 2034 * 64;
	Byte Data[MAX_MEM];

	void Initialize () {
		for ( u32 i = 0; i < MAX_MEM; i++ ) {
			Data[i] = 0;
		}
	}

	Byte operator [] ( u32 Address ) const {
		return Data [Address];
	}
};

struct CPU {

	Word PC;	// Program Counter
	Word SP;	// Stack Pointer
	
	Byte A, X, Y;	// registers
	
	Byte C : 1;	// Carry Flag
	Byte Z : 1;	// Zero Flag
	Byte I : 1;	// Interrupt Disable
	Byte D : 1;	// Decimal Mode
	Byte B : 1;	// Break Command
	Byte V : 1;	// Overflow Flag
	Byte N : 1;	// Negative Flag

	void Reset(Mem& memory) {
		PC = 0xFFFC;
		SP = 0x00FF;
		C = Z = I = D = B = V = N = 0;
		A = X = Y = 0;

		memory.Initialize();
	}

	Byte Fetch ( u32& cycles, Mem& memory ) {
		Byte Data = memory[PC];
		PC++;
		cycles --;

		return Data;
	}
	
	// Immediate LDA Instruction
	static constexpr Byte
		INS_LDA_IM = 0xA9;
	
	void Execute ( u32 cycles, Mem& memory ) {
		while ( cycles > 0 ) {
			Byte Ins = Fetch ( cycles, memory );
			switch (Ins) {
				case INS_LDA_IM : {
							  Byte Value = Fetch (cycles, memory);
							  A = Value;
							  Z = A == 0 ? 1 : 0;
							  N = (A & 0b10000000) > 0;
						  } break;
				default:
						  printf("Instruction not handled %d", Ins);
						  break;
			}
		}
	}

};

int main() {
	Mem mem;
	CPU cpu;
	cpu.Reset(mem);
	mem[0xFFC] = CPU::INS_LDA_IM;
	mem[0xFFD] = 0x42;
	cpu.Execute ( 2, mem );
	 
	return 0;
}
