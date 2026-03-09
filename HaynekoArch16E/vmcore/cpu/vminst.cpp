#include "h/general.hpp"

#include "cpu/vminst.hpp"

// TODO: use void (*instFunc) (Inst inst, VM& vm, Reg &dst_reg, Reg &src_reg1, Reg &src_reg2,
//                             immd imm, addr addr, dispd disp) to call each instruction.

struct alignas( 8 ) InstPrefix {
	bool has_prefix;
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
	bool SIG;
};