#ifndef HA32S_H_VMREG_
#define HA32S_H_VMREG_

#include "general.hpp"

class Register {
public:

protected:

private:
};

class FloatPtRegister {
public:

protected:

private:
};

class IP: public Register {
public:
	IP();
	IP( addr ip_addr );

	void modIp( addr ip_addr );
	addr getIp() const;

protected:
	volatile regd ip;
};

class alignas( 32 ) GPR: public Register {
public:
	GPR();

	void writeReg( byte reg_num, dword data );
	dword readReg( byte reg_num ) const;

protected:
	regd regs[32];
};

class CR: public Register {
public:
	CR();

	void writeCtrlReg( byte reg_num, dword data );
	dword readCtrlReg( byte reg_num ) const;

protected:
	regd crs[4];
};

#endif // HA32S_H_VMREG_