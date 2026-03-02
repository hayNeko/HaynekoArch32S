#include "general.hpp"

// TODO: use void (*instFunc) (Inst inst, VM& vm, Reg &dst_reg, Reg &src_reg1, Reg &src_reg2,
//                             immd imm, addr addr, dispd disp) to call each instruction.

class VM;
class Reg;

struct alignas( 8 ) InstPrefix {
	byte ISL;
	bool BRH_H;
	bool LOCK;
	byte REX;
	union {
		bool XTU;
		bool BMU;
	};
	union {
		bool DBI;
		bool TBI;
	};

	byte OPCODE;
	byte SBOPCODE;
};
