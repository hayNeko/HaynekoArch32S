#include "h/vm.hpp"

VM::VM() : registers(), float_registers(), double_registers(), ports(), control_registers(), memory(65536), instruction_pointer(), flags() {
    // default constructor: memory size default 64KiB (adjustable)
}

VM::~VM() {
}

regd VM::readRegister(regid id) const {
    return registers.readReg(id);
}

void VM::writeRegister(regid id, dword value) {
    registers.writeReg(id, value);
}

void VM::writeRegister(regid id, word value) {
    registers.writeReg(id, static_cast<dword>(value));
}

void VM::writeRegister(regid id, byte value) {
    registers.writeReg(id, static_cast<dword>(value));
}

ctrlreg VM::readControlRegister(crid id) const {
    return control_registers.readCtrlReg(id);
}

void VM::writeControlRegister(crid id, dword value) {
    control_registers.writeCtrlReg(id, value);
}

addr VM::getIP() const {
    return instruction_pointer.getIp();
}

void VM::setIP(addr value) {
    instruction_pointer.modIp(value);
}

qword VM::readMemory(addr address, qword) const {
    return memory.readq(address);
}

dword VM::readMemory(addr address) const {
    return memory.readd(address);
}

word VM::readMemory(addr address, word) const {
    return memory.readw(address);
}

byte VM::readMemory(addr address, byte) const {
    return memory.readb(address);
}

void VM::writeMemory(addr address, qword value) {
    memory.writeq(address, value);
}

void VM::writeMemory(addr address, dword value) {
    memory.writed(address, value);
}

void VM::writeMemory(addr address, word value) {
    memory.writew(address, value);
}

void VM::writeMemory(addr address, byte value) {
    memory.writeb(address, value);
}

dword VM::stpop() {
    // pop a dword from stack (assumes 32-bit stack)
    regd sp = registers.readReg(VMGPR::SP);
    dword val = memory.readd(sp);
    registers.writeReg(VMGPR::SP, sp + 4);
    return val;
}

void VM::stpop3() {
    // pop three registers (not implemented fully; placeholder)
    (void)0;
}

void VM::stpush(regid reg) {
    regd sp = registers.readReg(VMGPR::SP);
    sp -= 4;
    memory.writed(sp, registers.readReg(reg));
    registers.writeReg(VMGPR::SP, sp);
}

void VM::stpush3(regid reg, regid reg2, regid reg3) {
    stpush(reg3);
    stpush(reg2);
    stpush(reg);
}

void VM::stpush(immd imm, dword) {
    regd sp = registers.readReg(VMGPR::SP);
    sp -= 4;
    memory.writed(sp, imm);
    registers.writeReg(VMGPR::SP, sp);
}

void VM::stpush(addr addr_val) {
    regd sp = registers.readReg(VMGPR::SP);
    sp -= 4;
    memory.writed(sp, addr_val);
    registers.writeReg(VMGPR::SP, sp);
}

void VM::interrupt(byte vector) {
    // placeholder: set some flag or handle interrupt
    (void)vector;
}

void VM::syscall() {
    // placeholder
}

void VM::sysret() {
    // placeholder
}

int VM::halt() {
    return VM_PROCESS_EXIT_CODE_SUCCESS;
}

dword VM::in(portid port) const {
    return ports.readPort(port);
}

void VM::out(portid port, dword value) {
    ports.writePort(port, value);
}
