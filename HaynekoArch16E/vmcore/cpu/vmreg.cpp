#include <stdexcept>

#include "h/general.hpp"
#include "cpu/vmreg.hpp"

VMIP::VMIP() {
	this->ip = 0xFFFFFFFA; // JMP .program_entry  3E XX XX XX XX
}

VMIP::VMIP( addr ip_addr ) {
	this->ip = ip_addr;
}

void VMIP::modIp( addr ip_addr ) {
	this->ip = ip_addr;
}
addr VMIP::getIp() const {
	return this->ip;
}

VMGPR::VMGPR() {
    for ( int i = 0; i < VM_GPR_COUNT; ++i ) regs[i] = 0;
}
void VMGPR::writeReg( regid reg_num, dword data ) {
    if ( reg_num >= VM_GPR_COUNT )
        throw std::out_of_range( "Invalid register number" );

    this->regs[reg_num] = data;
}

dword VMGPR::readReg( regid reg_num ) const {
    if ( reg_num >= VM_GPR_COUNT )
        throw std::out_of_range( "Invalid register number" );

    return this->regs[reg_num];
}

VMCR::VMCR() {
    for ( int i = 0; i < VM_CR_COUNT; ++i ) crs[i] = 0;
}

void VMCR::writeCtrlReg( regid reg_num, dword data ) {
    if ( reg_num >= VM_CR_COUNT )
        throw std::out_of_range( "Invalid register number" );

    this->crs[reg_num] = data;
}

dword VMCR::readCtrlReg( regid reg_num ) const {
    if ( reg_num >= VM_CR_COUNT )
        throw std::out_of_range( "Invalid register number" );

    return this->crs[reg_num];
}

// Floating point register implementation
VMFloatReg::VMFloatReg() {
    for ( int i = 0; i < VM_FPR_COUNT; ++i ) regs[i] = 0.0f;
}

void VMFloatReg::writeReg( regid reg_num, float data ) {
    if ( reg_num >= VM_FPR_COUNT )
        throw std::out_of_range( "Invalid register number" );

    this->regs[reg_num] = data;
}

float VMFloatReg::readReg( regid reg_num ) const {
    if ( reg_num >= VM_FPR_COUNT )
        throw std::out_of_range( "Invalid register number" );

    return this->regs[reg_num];
}

// Double precision floating point register implementation
VMDoubleReg::VMDoubleReg() {
    for ( int i = 0; i < VM_FPR_COUNT; ++i ) regs[i] = 0.0;
}

void VMDoubleReg::writeReg( regid reg_num, double data ) {
    if ( reg_num >= VM_FPR_COUNT )
        throw std::out_of_range( "Invalid register number" );

    this->regs[reg_num] = data;
}

double VMDoubleReg::readReg( regid reg_num ) const {
    if ( reg_num >= VM_FPR_COUNT )
        throw std::out_of_range( "Invalid register number" );

    return this->regs[reg_num];
}
