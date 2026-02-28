#include <iostream>

#include "general.hpp"

//#include "vmcore.hpp"
//#include "vmcpu.hpp"
#include "vmflag.hpp"
//#include "vminst.hpp"
#include "vminstphsr.hpp"
#include "vmmem.hpp"
//#include "vmport.hpp"
#include "vmreg.hpp"

//#undef ALPHA

int main() {
	#ifdef ALPHA
	std::cout << "This is Alpha version." << std::endl;
	#endif


	return 0;
}