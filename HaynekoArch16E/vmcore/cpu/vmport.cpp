#include <stdexcept>

#include "h/general.hpp"
#include "cpu/vmport.hpp"

Port::Port() {
	for ( byte i = 0; i <= 7; ++i )
		this->port[i] = 0;
}

dword Port::readPort( portid port ) const {
	if ( port >= 8 || port < 0 )
		// throw expection, or just return -1.
		throw std::out_of_range( "Invalid port number" );
	return this->port[port];
}

void Port::writePort( portid port, dword value ) {
	if ( port >= 8 || port < 0 )
		throw std::out_of_range( "Invalid port number" );
	this->port[port] = value;
}