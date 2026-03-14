#ifndef HA32S_H_VMREG_
#define HA32S_H_VMREG_

#include "general.hpp"

// register counts
constexpr byte VM_GPR_COUNT = 32;
constexpr byte VM_FPR_COUNT = 16;
constexpr byte VM_CR_COUNT  = 4;

class alignas( 32 ) VMGPR {
public:
	VMGPR();

	enum TYPE: regid {
		X0, RA, RB, RC, RD, RI, BP, SP,
		R8, R9, R10, R11, R12, R13, R14, R15,
		R16, R17, R18, R19, R20, R21, R22, R23,
		T0, T1, T2, T3, T4, T5, T6, T7
	};

	void writeReg( regid reg_num, dword data );
	dword readReg( regid reg_num ) const;

protected:
	regd regs[32];
};

class VMFloatReg {
public:
	VMFloatReg();

	void writeReg( regid reg_num, float data );
	float readReg( regid reg_num ) const;
protected:
	float regs[16];

private:
};

class VMDoubleReg {
public:
	VMDoubleReg();

	void writeReg( regid reg_num, double data );
	double readReg( regid reg_num ) const;
protected:
	double regs[16];

private:
};

class VMIP {
public:
	VMIP();
	VMIP( addr ip_addr );

	void modIp( addr ip_addr );
	addr getIp() const;

protected:
	volatile regd ip;
};


class VMCR {
public:
	VMCR();

	void writeCtrlReg( regid reg_num, dword data );
	dword readCtrlReg( regid reg_num ) const;

protected:
	regd crs[4];
};

#endif // HA32S_H_VMREG_