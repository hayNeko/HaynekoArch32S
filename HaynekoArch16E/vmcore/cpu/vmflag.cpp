#include <stdexcept>

#include "h/general.hpp"
#include "cpu/vmflag.hpp"

void VMFlag::set( VMFlag::TYPE flag ) {
	#ifndef VMCPU_DISABLE_PROTECTION_MODE
	if ( flag >= 16 ) throw std::invalid_argument( "Invalid flag" );
	#endif
	setBit( this->flag, flag );
}

void VMFlag::clear( VMFlag::TYPE flag ) {
	#ifndef VMCPU_DISABLE_PROTECTION_MODE
	if ( flag >= 16 ) throw std::invalid_argument( "Invalid flag" );
	#endif
	clearBit( this->flag, flag );
}

bool VMFlag::get( VMFlag::TYPE flag ) const {
	#ifndef VMCPU_DISABLE_PROTECTION_MODE
	if ( flag >= 16 ) throw std::invalid_argument( "Invalid flag" );
	#endif
	return isBitSet( this->flag, flag );
}