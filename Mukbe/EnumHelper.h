#pragma once
template<size_t N>
struct Bit
{
	static constexpr int value = 1 << N;
};
#define BitEnum(n) Bit<n>::value,

enum RenderLayer : int
{
	Layer_None			= Bit<0>::value,
	Layer_BackGround	= Bit<1>::value,
	Layer_Terrain		= Bit<2>::value,
	Layer_GameText		= Bit<3>::value,
	Layer_Object 		= Bit<4>::value,
	Layer_Light 		= Bit<5>::value,
	Layer_UI	 		= Bit<6>::value,
	Layer_UIText 		= Bit<7>::value,
	Layer_Imgui 		= Bit<8>::value,
};

enum Pivot
{
	LEFT_TOP, CENTER, BOTTOM, TOP
};
enum RigidType : short
{
	Dynamic = 0, Static, RigidType_End
};
