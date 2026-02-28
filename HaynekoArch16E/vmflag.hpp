#pragma once

#include "general.hpp"

class Flag {
public:
	enum TYPE : byte{
		Z, C, O, N,
		FLZ, FLO, FLV,
		IF,
		U0, U1, U2,
		BE, AC,
		U3, U4,
		XTE, BME, CIE,
		U5, U6, U7, U8, U9,
		VIE,
		U10, U11, U12, U13, U14, U15, U16, U17
	};

	static constexpr dword Z_MASK   = 1 << 0;
	static constexpr dword C_MASK   = 1 << 1;
	static constexpr dword O_MASK   = 1 << 2;
	static constexpr dword N_MASK   = 1 << 3;

	static constexpr dword FLZ_MASK = 1 << 4;
	static constexpr dword FLO_MASK = 1 << 5;
	static constexpr dword FLV_MASK = 1 << 6;

	static constexpr dword IF_MASK  = 1 << 7;

	static constexpr dword U0_MASK  = 1 << 8;
	static constexpr dword U1_MASK  = 1 << 9;
	static constexpr dword U2_MASK  = 1 << 10;

	static constexpr dword BE_MASK  = 1 << 11;
	static constexpr dword AC_MASK  = 1 << 12;

	static constexpr dword U3_MASK  = 1 << 13;
	static constexpr dword U4_MASK  = 1 << 14;

	static constexpr dword XTE_MASK = 1 << 15;
	static constexpr dword BME_MASK = 1 << 16;
	static constexpr dword CIE_MASK = 1 << 17;

	static constexpr dword U5_MASK  = 1 << 18;
	static constexpr dword U6_MASK  = 1 << 19;
	static constexpr dword U7_MASK  = 1 << 20;
	static constexpr dword U8_MASK  = 1 << 21;
	static constexpr dword U9_MASK  = 1 << 22;

	static constexpr dword VIE_MASK = 1 << 23;

	static constexpr dword U10_MASK = 1 << 24;
	static constexpr dword U11_MASK = 1 << 25;
	static constexpr dword U12_MASK = 1 << 26;
	static constexpr dword U13_MASK = 1 << 27;
	static constexpr dword U14_MASK = 1 << 28;
	static constexpr dword U15_MASK = 1 << 29;
	static constexpr dword U16_MASK = 1 << 30;
	static constexpr dword U17_MASK = 1 << 31;

private:
	dword flag;

public:
	Flag() : flag(0) {}

	void set( TYPE flag );
	void clear( TYPE flag );
	bool get( TYPE flag ) const;

};