#ifndef HA32S_H_VMINSTPSR_
#define HA32S_H_VMINSTPSR_

#include "h/general.hpp"
#include "cpu/vmreg.hpp"
#include "cpu/vmflag.hpp"

/* isa list on https://github.com/hayNeko/hayneko_arch32S/blob/main/hayneko_arch32S-v1.json
* this isa need to be updated. (March 6 2026)
*/

// many of instruction is 2-operand instruction ( a = a OP b ) but not 3-operand instruction ( a = b OP c )
class VMInstParser {
public:
};

#endif // HA32S_H_VMINSTPSR_