#ifndef HA32S_H_VMPORT_
#define HA32S_H_VMPORT_

#include "h/general.hpp"

class Port {
public:
	Port();

	dword readPort( portid port ) const;
	void writePort( portid port, dword value );
private:
	dword port[8];
};

#endif // HA32S_H_VMPORT_