#ifndef HA32S_H_VM_
#define HA32S_H_VM_

#include "general.hpp"
#include "cpu/vmreg.hpp"
#include "cpu/vminst.hpp"
#include "cpu/vminstpsr.hpp"
#include "cpu/vminstprefix.hpp"
#include "cpu/vmport.hpp"
#include "cpu/vmmem.hpp"

class VM {
public:
	VM();
	~VM();

	regd readRegister( regid id ) const;

	void writeRegister( regid id, dword value );
	void writeRegister( regid id, word value );
	void writeRegister( regid id, byte value );

	ctrlreg readControlRegister( crid id ) const;

	void writeControlRegister( crid id, dword value );

	addr getIP() const;
	void setIP( addr value );

	qword readMemory( addr addr, qword ) const;
	dword readMemory( addr addr ) const;
	word readMemory( addr addr, word ) const;
	byte readMemory( addr addr, byte ) const;
	void writeMemory( addr addr, qword value );
	void writeMemory( addr addr, dword value );
	void writeMemory( addr addr, word value );
	void writeMemory( addr addr, byte value );

	dword stpop();
	void stpop3(); // Reg *reg1, etc..
	void stpush( regid reg );
	void stpush3( regid reg, regid reg2, regid reg3 );
	void stpush( immd imm, dword );
	void stpush( addr addr );

	void interrupt( byte vector );
	void syscall();
	void sysret();
	int halt();

	dword in( portid port ) const;
	void out( portid port, dword value );


	VMGPR registers;
	VMFloatReg float_registers;
	VMDoubleReg double_registers;
	VMPort ports;
	VMCR control_registers;
	VMMem memory;
	VMIP instruction_pointer;
	VMFlag flags;

	
};

#endif // HA32S_H_VM_