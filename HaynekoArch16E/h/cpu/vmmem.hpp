#ifndef HA32S_H_VMMEM_
#define HA32S_H_VMMEM_
#include <string>

#include "general.hpp"

class VMMem {
public:
	VMMem( const VMMem &other ) = delete;
	VMMem &operator=( const VMMem &other ) = delete;

	VMMem( dword mem_size );

	~VMMem();

	void writeq( addr address, qword data );
	void writed( addr address, dword data );
	void writew( addr address, word data );
	void writeb( addr address, byte data );

	qword readq( addr address );
	dword readd( addr address );
	word readw( addr address );
	byte readb( addr address );

protected:
	byte *mem_ptr;
	dword mem_size;
};

#endif // HA32S_H_VMMEM_