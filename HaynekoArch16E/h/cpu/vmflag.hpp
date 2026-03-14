#ifndef HA32S_H_VMFLAG_
#define HA32S_H_VMFLAG_

#include "general.hpp"

class VMFlag {
public:
	enum TYPE: byte {
		Z, C, O, N,
		FLZ, FLO, FLV,
		IF,
		BE = 11, AC,
		PROT = 16
	};

	static constexpr dword Z_MASK = 1 << 0;
	static constexpr dword C_MASK = 1 << 1;
	static constexpr dword O_MASK = 1 << 2;
	static constexpr dword N_MASK = 1 << 3;
	static constexpr dword FLZ_MASK = 1 << 4;
	static constexpr dword FLO_MASK = 1 << 5;
	static constexpr dword FLV_MASK = 1 << 6;
	static constexpr dword IF_MASK = 1 << 7;
	static constexpr dword BE_MASK = 1 << 11;
	static constexpr dword AC_MASK = 1 << 12;
	static constexpr dword PROT_MASK = 1 << 16;

	static constexpr dword Z_SIGN = 0;
	static constexpr dword C_SIGN = 1;
	static constexpr dword O_SIGN = 2;
	static constexpr dword N_SIGN = 3;
	static constexpr dword FLZ_SIGN = 4;
	static constexpr dword FLO_SIGN = 5;
	static constexpr dword FLV_SIGN = 6;
	static constexpr dword IF_SIGN = 7;
	static constexpr dword BE_SIGN = 11;
	static constexpr dword AC_SIGN = 12;
	static constexpr dword PROT_SIGN = 16;


private:
	flag flag;

public:
	VMFlag(): flag( 0 ) {}

	void set( TYPE flag );
	void clear( TYPE flag );
	bool get( TYPE flag ) const;
};

#endif // HA32S_H_VMFLAG_