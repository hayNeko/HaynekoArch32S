#include <stdexcept>

#include "vmflag.hpp"
#include "general.hpp"

void Flag::set( Flag::TYPE flag ) {
	#ifndef VMCPU_DISABLE_PROTECTION_MODE
	if (flag >= 16 ) throw std::invalid_argument( "Invalid flag" );
	#endif
	this->flag |= ( 1 << flag );
}

void Flag::clear( Flag::TYPE flag ) {
	#ifndef VMCPU_DISABLE_PROTECTION_MODE
	if (flag >= 16 ) throw std::invalid_argument( "Invalid flag" );
	#endif
	this->flag &= ~( 1 << flag );
}

bool Flag::get( Flag::TYPE flag ) const {
	#ifndef VMCPU_DISABLE_PROTECTION_MODE
	if (flag >= 16 ) throw std::invalid_argument( "Invalid flag" );
	#endif
	return this->flag & ( 1 << flag );
}