#include <iostream>

#include "h/general.hpp"
#include "vmboot/vminit.hpp"

//#undef ALPHA

/* arg0: is_protected mode (0: default disable, 1: enable)

*/
int main( int argc, char *argv[] ) {
	#ifdef VER_ALPHA
	println( "This is a alpha version." );
	#endif

	// init vmcore with default values
	// and set vm to protected mode

	return VM_PROCESS_EXIT_CODE_SUCCESS;
}