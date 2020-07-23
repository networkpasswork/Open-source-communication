#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <intrin.h>
#include <vector>
#include "Memory.h"
#include "OffSet.h"
#include "GameData.h"
#include "obfuscation.h"
#include "SpoofCall.h"
#include "EngineSDK.hpp"

using namespace std;
Vector3 calFOV(Vector3 D, Vector3 W);
Vector3 Clamp1(Vector3 Ver);
ULONG jugement(const char* 参_武器名称);
vector<FVector2D> TempItemOverlayArr;
//void ZZHOOK()
//{
//	uint64_t user32DLL = (uint64_t)GetModuleHandle(XorStringW(L"USER32.dll"));
//	BYTE XIU[] = { 0x1 };
//	Mem::WriteMemory(user32DLL + 0x3, XIU, sizeof(XIU));
//
//}
//
//void DELETEHOOK()
//{
//	uint64_t user32DLL = (uint64_t)GetModuleHandle(XorStringW(L"USER32.dll"));
//	BYTE XIU[] = { 0x2 };
//	Mem::WriteMemory(user32DLL + 0x3, XIU, sizeof(XIU));
//
//}
bool IsRange(int CurrentValue, int Min, int Max)
{
	return CurrentValue > Min&& CurrentValue < Max;
}
void IsOverlay(FVector2D& D2D)
{
	for (int i = 0; i < TempItemOverlayArr.size(); i++)
	{
		if (IsRange(D2D.X, TempItemOverlayArr[i].X - 80, TempItemOverlayArr[i].X + 80) && IsRange(D2D.Y, TempItemOverlayArr[i].Y - 16, TempItemOverlayArr[i].Y + 16))
		{
			D2D = TempItemOverlayArr[i];
			D2D.Y = D2D.Y - 16 * 0.8;
		}
	}
}
void* MalloAddress = nullptr;
typedef __int64(__fastcall* ObjID_Decrypt_)(void* MemoryAddress, int value1, int value2, uint64_t Obj);
ObjID_Decrypt_ Xenuine_DecryptaID = NULL;
std::string GameData::GetNames(DWORD ID)
{
	std::string emp = "duiaudsakjkow";
	if (ID <= 0 || ID > 400000)
		return emp;
	auto gnames = GameData::Dec_Games1(Mem::Ram<uint64_t>(GameData::TslGameBase + OffSet::GNames - 0x20));
	gnames = GameData::Dec_Games2(Mem::Ram<uint64_t>(gnames));
	char Name[64] = { 0 };
	uint32_t IdDiv = ID / OffSet::NameCont;
	uint32_t Idtemp = ID % OffSet::NameCont;
	uint64_t Serial = Mem::Ram<uint64_t>(gnames + IdDiv * 0x8);
	if (!Serial || Serial < 0x100000)
		return emp;
	uint64_t pName = Mem::Ram<uint64_t>(Serial + 0x8 * Idtemp);
	if (!pName || pName < 0x100000)
		return emp;
	StringA names = Mem::Ram<StringA>(pName + 0x10);
	char te[64];
	memset(&te, 0, 64);
	if (memcmp(names.buffer, te, 64) == 0)
		return emp;
	std::string str(names.buffer);
	return str;
}
BOOL GameData::Getskinid()
{
	bool IsFind = false;
	bool IsFind2 = false;
	for (size_t i = 0; i < 400000; i++)
	{
		std::string Name = GetNames(i);
		if (Name == "M24_CartelGold_01")
		{
			IsFind = true;
			OffSet::M24_CartelGold_01 = i;
			continue;
		}
		if (Name == "AWM_Perl_01")
		{
			IsFind = true;
			OffSet::AWM_Perl_01 = i;
			continue;
		}
		if (Name == "Kar98k_Casual_01")
		{
			IsFind = true;
			OffSet::Kar98k_Casual_01 = i;
			continue;
		}
		if (Name == "Mini14_Dust_01")
		{
			IsFind = true;
			OffSet::Mini14_Dust_01 = i;
			continue;
		}
		if (Name == "QBU88_CartelGold_01")
		{
			IsFind = true;
			OffSet::QBU88_CartelGold_01 = i;
			continue;
		}
		if (Name == "FNFAL_BStat_01")
		{
			IsFind = true;
			OffSet::FNFAL_BStat_01 = i;
			continue;
		}
		if (Name == "SKS_BStat_01")
		{
			IsFind = true;
			OffSet::SKS_BStat_01 = i;
			continue;
		}
		if (Name == "HK416_3rd_01")
		{
			IsFind = true;
			OffSet::HK416_3rd_01 = i;
			continue;
		}
		if (Name == "AKM_CartelPink_01")
		{
			IsFind = true;
			OffSet::AKM_CartelPink_01 = i;
			continue;
		}
		if (Name == "Groza_CartelGold_01")
		{
			IsFind = true;
			OffSet::Groza_CartelGold_01 = i;
			continue;
		}
		if (Name == "QBZ95_Diamond_01")
		{
			IsFind = true;
			OffSet::QBZ95_Diamond_01 = i;
			continue;
		}
		if (Name == "Scar-L_1st_01")
		{
			IsFind = true;
			OffSet::ScarL_1st_01 = i;
			continue;
		}
		if (Name == "M16A4_Henna_01")
		{
			IsFind = true;
			OffSet::M16A4_Henna_01 = i;
			continue;
		}		
		if (IsFind && IsFind2)
		{
			return TRUE;
		}
	}
	return FALSE;
}
BOOL GameData::GetCanvasObj()
{
	bool IsFind = false;
	bool IsFind2 = false;
	for (size_t i = 0; i < 400000; i++)
	{
		std::string Name = GetNames(i);
		if (Name == "CanvasObject")
		{
			IsFind = true;
			OffSet::CanvasObject = i;
			continue;
		}
		else if (Name == "DebugCanvasObject")
		{
			IsFind2 = true;
			OffSet::DebugCanvasObject = i;
			continue;
		}
		if (IsFind && IsFind2)
		{
			return TRUE;
		}
	}
	return FALSE;
}
uint32_t GameData::Xenuine_DecryptID(uint64_t Obj)//解密ID
{
	if (Xenuine_DecryptaID == NULL)
		Xenuine_DecryptaID = (ObjID_Decrypt_)(GameData::TslGameBase + OffSet::XXXID);

	if (MalloAddress == nullptr)
		MalloAddress = malloc(300);
	if (!Obj || !Xenuine_DecryptaID)
		return 0;
	uint64_t temp = Mem::Ram<uint64_t>(Obj);
	if (temp < GameData::TslGameBase || temp > GameData::TslGameBase + 0x10000000)
		return 0;
	Xenuine_DecryptaID(MalloAddress, 0, 0, Obj);
	spoof_call(SpoofBytes, Xenuine_DecryptaID, MalloAddress, 0, 0, Obj);
	return  Mem::Ram<uint32_t>(uint64_t(MalloAddress) + 8);
}
ULONG jugement(const char* 参_武器名称) {
	ULONG ID;
	if (参_武器名称 != NULL)
	{
		if (strcmp("WeapAK47_C", 参_武器名称) == 0)//248053
		{
			ID = OffSet::AKM_CartelPink_01;
			goto _RetOut;
		}
		if (strcmp("WeapQBZ95_C", 参_武器名称) == 0)//248082
		{
			ID = OffSet::QBZ95_Diamond_01;
			goto _RetOut;
		}
		if (strcmp("WeapKar98k_C", 参_武器名称) == 0)//248069
		{
			ID = OffSet::Kar98k_Casual_01;
			goto _RetOut;
		}
		if (strcmp("WeapM24_C", 参_武器名称) == 0)//248072
		{
			ID = OffSet::M24_CartelGold_01;
			goto _RetOut;
		}
		if (strcmp("WeapSKS_C", 参_武器名称) == 0)//248087
		{
			ID = OffSet::SKS_BStat_01;
			goto _RetOut;
		}
		if (strcmp("WeapSCAR-L_C", 参_武器名称) == 0)//248086
		{
			ID = OffSet::ScarL_1st_01;
			goto _RetOut;
		}
		if (strcmp("WeapHK416_C", 参_武器名称) == 0) //248067
		{
			ID = OffSet::HK416_3rd_01;
			goto _RetOut;
		}
		if (strcmp("WeapM16A4_C", 参_武器名称) == 0)//248070
		{
			ID = OffSet::M16A4_Henna_01;
			goto _RetOut;
		}
		if (strcmp("WeapAWM_C", 参_武器名称) == 0)//248055
		{
			ID = OffSet::AWM_Perl_01;
			goto _RetOut;
		}
		if (strcmp("WeapMini14_C", 参_武器名称) == 0)//248075
		{
			ID = OffSet::Mini14_Dust_01;
			goto _RetOut;
		}
		if (strcmp("WeapGroza_C", 参_武器名称) == 0)//248066
		{
			ID = OffSet::Groza_CartelGold_01;
			goto _RetOut;
		}
		if (strcmp("WeapQBU88_C", 参_武器名称) == 0)//248081
		{
			ID = OffSet::QBU88_CartelGold_01;
			goto _RetOut;
		}
		if (strcmp("WeapFNFal_C", 参_武器名称) == 0)//248063
		{
			ID = OffSet::FNFAL_BStat_01;
			goto _RetOut;
		}


	}

_RetOut:
	return ID;


}
wchar_t* char20wchar(const char* cchar)
{
	wchar_t* m_wchar;
	int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
	m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
	m_wchar[len] = '\0';
	return m_wchar;
}
//内存无后
BOOL GameData::WorldToScreen_Aim(ULONG64 CameraManager, ULONG64 LocalMesh, Vector3 WorldLocation, Vector3* pOut, float* DeltaInMeters) //内存压枪NB 修复了掉落物品 即使你把物品丢掉也会显示 训练场物品显示 那是怎么弄得 你弄了新的便宜吗 不是 换了个指针行吧  不过那俩物品显示  咋回事 哪个？你下面俩物品显示 一个是正常物品 一个是掉落物品 也就是训练场 那为啥我弄完  物品都飞天上去了呢 你坐标不对昨晚我也是你哪个效果额 我知道了 自己改改东西 别和我的一样 我要吃市场了 我这边压到3 额 我们现在都没多少量 保底2000把你能不呢分我点 我还等你给我分呢我要是行还至于现在这样吗 慢慢来 我大概做半个月就把代理丢你好累 稳妥老哥 加鸡腿 下了 我这边一堆破事 有个傻逼买了个我无后 自己加不来 我去给他远程去了哈哈 去吧
{
	ULONG64 Ptr1 = Mem::Ram<ULONG64>(LocalMesh + OffSet::UAnimInstance);
	Vector3 Rotation = Mem::Ram<Vector3>(Ptr1 + OffSet::ControlRotation_CP) + Mem::Ram<Vector3>(Ptr1 + OffSet::RecoilADSRotation_CP);
	D3DMATRIX2 tempMatrix = Matrix2(Rotation);//CameraInfo.Rotation
	Vector3 vAxisX, vAxisY, vAxisZ;
	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
	Vector3 Location = Mem::Ram<Vector3>(CameraManager + OffSet::CameraPos);
	Vector3 vDelta = WorldLocation - Location;// CameraInfo.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;
	if (DeltaInMeters != NULL) {
		*DeltaInMeters = vTransformed.z / 100;
	}
	float FovAngle = Mem::Ram<float>(CameraManager + OffSet::CameraFov); //CameraInfo.FOV;//
																 //float ScreenCenterX = GameWindowWidth / 2.0f;
																 //float ScreenCenterY = GameWindowHeight / 2.0f;


	pOut->x = ScreenCenterX + vTransformed.x * ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f) / vTransformed.z;
	pOut->y = ScreenCenterY - vTransformed.y * ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f) / vTransformed.z;
	pOut->z = 0;

	if (pOut->x < 0) {
		pOut->x = 0;
	}
	if (pOut->y < 0) {
		pOut->y = 0;
	}
	if (pOut->x > 0 && pOut->y > 0) {
		if (pOut->x <= ScreenCenterX * 2.0f && pOut->y <= ScreenCenterY * 2.0f) { //画骨骼 2.0f
			return TRUE;
		}
	}

	return FALSE;
}
void* GameData::SpoofBytes = NULL;
ULONG_PTR GameData::TslGameBase = 0;
ULONG_PTR GameData::BEBase=0;
ULONG_PTR GameData::win32u=0 ;
float GameData::ScreenCenterX = 0, GameData::ScreenCenterY = 0;
ULONG64 GameData::g_Uworld, GameData::g_Levels, GameData::g_Actor, GameData::g_ObjectList, GameData::g_Gameinsts, GameData::g_LocalPlayers, GameData::g_PlayerControllers, GameData::g_Camera, GameData::g_Localactor, GameData::g_Games, GameData::g_PlayerControllers2;

bool GameData::Switch_Menu = true, GameData::Switch_Battle = false, GameData::Switch_Player = true, GameData::Switch_AimBot = true, GameData::Switch_Vehicle = true, GameData::Switch_BoxSupport = true,
GameData::Switch_Radar = false, GameData::Switch_Item = true, GameData::Switch_Expose = true, GameData::Switch_InsHit = false, GameData::Switch_NoRecoil = true, GameData::Switch_Hp = true, GameData::Switch_Name = true,
GameData::ItemShow_YaoPin = true, GameData::ItemShow_ZhuangBei = true, GameData::anti_aim = false, GameData::HUANFU = true, GameData::shouchi = true, GameData::jiasu = false, GameData::shift=true, GameData::jisha=false, GameData::xueliang=true, GameData::ItemShow_Juji = true, GameData::ItemShow_BuQiang = true, GameData::ItemShow_PeiJian = true, GameData::Switch_chuanqiang= false,GameData::Switch_Audience = true;

bool GameData::IsLock = false;//是否锁定目标
float GameData::TargeNear = 0.f, GameData::TargetLen = 0.f, GameData::AimbotRange = 200.f, GameData::ESPDistance = 600.f, GameData::EnemyLatelyDistance = 0.f;
ULONG64 GameData::Aimbot = 0;

float GameData::集_自身坐标x, GameData::集_自身坐标y, GameData::集_地图比例, GameData::全_雷达半径, GameData::全_雷达中心x, GameData::全_雷达中心y;



BYTE Aimbot_sw = 0;
FLOAT Aimbot_x = 0.f;
FLOAT Aimbot_y = 0.f;
FLOAT Aimbot_z = 0.f;
ULONG_PTR HookTurnBulletReturn = 0;
ULONG_PTR HookSilenceAimBotReturn = 0;
ULONG_PTR HookAtanfReturn = 0;
ULONG_PTR JmpAtanfAddress = 0;
int64_t AimTarget = 0;
int64_t CameraManagerAddress = 0; //设置相机数组
int GameData::BoneInfo[6][8] = 
{
	{ Bones::forehead, Bones::face_root,Bones::Head ,Bones::neck_01,Bones::spine_03, Bones::spine_02, Bones::spine_01, Bones::pelvis },
	{ Bones::neck_01, Bones::upperarm_r, Bones::lowerarm_r, Bones::hand_r ,Bones::index_01_r,-1,-1,-1},
	{ Bones::neck_01, Bones::upperarm_l, Bones::lowerarm_l, Bones::hand_l ,Bones::index_01_l,-1,-1,-1},
	{ Bones::pelvis, Bones::thigh_r, Bones::thigh_twist_01_r, Bones::calf_r,Bones::calf_twist_01_r, Bones::foot_r , Bones::ball_r, -1} ,
	{ Bones::pelvis, Bones::thigh_l, Bones::thigh_twist_01_l, Bones::calf_l, Bones::calf_twist_01_l, Bones::foot_l, Bones::ball_l, -1 } };

int GameData::AimBotBone[28] = {
	Bones::spine_03, Bones::forehead ,Bones::face_root,Bones::Head ,Bones::neck_01,Bones::spine_02, Bones::spine_01, Bones::pelvis,
	Bones::upperarm_r, Bones::lowerarm_r, Bones::hand_r ,Bones::index_01_r,
	Bones::upperarm_l, Bones::lowerarm_l, Bones::hand_l ,Bones::index_01_l,
	Bones::thigh_r, Bones::thigh_twist_01_r, Bones::calf_r,Bones::calf_twist_01_r, Bones::foot_r , Bones::ball_r,
	Bones::thigh_l, Bones::thigh_twist_01_l, Bones::calf_l, Bones::calf_twist_01_l, Bones::foot_l, Bones::ball_l };

typedef uint64_t(__fastcall* DecFunction3)(uint64_t key, uint64_t base);
DecFunction3 pDecFunction = NULL;
DrawIndex GameData::DrawInfo;
ObjIdInfo GameData::ObjeId;
绘制颜色结构 GameData::ColorInfo;
ULONG64 DecFunction(ULONG64 Data)//通用解密
{
	if (pDecFunction == NULL)
	{
		pDecFunction = reinterpret_cast<DecFunction3>(Mem::Ram<uint64_t>(GameData::TslGameBase + OffSet::DecCall));
	}
	if (Data == NULL)
	{
		return NULL;
	}
	return pDecFunction(0, Data);
}
ULONG64 GameData::Dec_Uworld(ULONG64 a1)
{
	return Dec_PUBG((ULONG_PTR)OffSet::Dec_UWorld, a1, GameData::TslGameBase + OffSet::DecCall);
}

ULONG64 GameData::Dec_Level(ULONG64 a1)
{
	return Dec_PUBG((ULONG_PTR)OffSet::Dec_level, a1, GameData::TslGameBase + OffSet::DecCall);
}

ULONG64 GameData::Dec_Actor(ULONG64 a1)
{
	return Dec_PUBG((ULONG_PTR)OffSet::Dec_Actor, a1, GameData::TslGameBase + OffSet::DecCall);
}

ULONG64 GameData::Dec_Gameinst(ULONG64 a1)
{
	return Dec_PUBG((ULONG_PTR)OffSet::Dec_GameInst, a1, GameData::TslGameBase + OffSet::DecCall);
}

ULONG64 GameData::Dec_LocalPlayers(ULONG64 a1)
{
	return Dec_PUBG((ULONG_PTR)OffSet::Dec_LocalPlayer, a1, GameData::TslGameBase + OffSet::DecCall);
}

ULONG64 GameData::Dec_PlayerControllers(ULONG64 a1)
{
	return Dec_PUBG((ULONG_PTR)OffSet::Dec_PlayerControllers, a1, GameData::TslGameBase + OffSet::DecCall);
}

ULONG64 GameData::Dec_Localactor(ULONG64 a1)
{
	return Dec_PUBG((ULONG_PTR)OffSet::Dec_Localactor, a1, GameData::TslGameBase + OffSet::DecCall);
}

ULONG64 GameData::Dec_Games1(ULONG64 a1)
{
	return Dec_PUBG((ULONG_PTR)OffSet::Dec_GNames1, a1, GameData::TslGameBase + OffSet::DecCall);
}

ULONG64 GameData::Dec_Games2(ULONG64 a1)
{
	return Dec_PUBG((ULONG_PTR)OffSet::Dec_GNames2, a1, GameData::TslGameBase + OffSet::DecCall);
}

ULONG64 GameData::Dec_Bullets(ULONG64 a1)
{
	return Dec_PUBG((ULONG_PTR)OffSet::Dec_BulletTable, a1, GameData::TslGameBase + OffSet::DecCall);
}

ULONG64 GameData::Dec_UObject(ULONG64 a1)
{
	return Dec_PUBG((ULONG_PTR)OffSet::Dec_UObject, a1, GameData::TslGameBase + OffSet::DecCall);
}
ULONG64 GameData::Dec_Overall(ULONG64 a1)
{
	return Dec_PUBG((ULONG_PTR)OffSet::Dec_Overall, a1, GameData::TslGameBase + OffSet::DecCall);
}
bool GameData::LineTraceSingle(ULONG64 Entitys, Vector3 StartPos, Vector3 EndPos) {

	typedef bool(__fastcall* fnLineTraceSingle)(void* Uworld,
		Vector3 Start,
		Vector3 End,
		ETraceTypeQuery TraceChannel,
		bool bTraceComplex,
		void* ActorsToIgnore,
		EDrawDebugTrace DrawDebugType,
		FHitResult* Outhit,
		bool bIgnoreSelf,
		FLinearColor TraceColor,
		FLinearColor TraceHitColor,
		float DrawTime);
	fnLineTraceSingle pfnLineTraceSingle = fnLineTraceSingle(TslGameBase + OffSet::LineTraceSingle);

	FHitResult OutHit;

	return !spoof_call(SpoofBytes,
		pfnLineTraceSingle,
		(void*)g_Uworld,
		StartPos,
		EndPos,
		TraceTypeQuery1,
		true,
		(void*)g_Actor,
		EDrawDebugTrace__None,
		&OutHit,
		true,
		FLinearColor(),
		FLinearColor(),
		0.f);
}


void GameData::DrawClear() {
	DrawInfo.Count = 0;
	Mem::Asm_ZeroMemory(&DrawInfo, sizeof(DrawInfo));
}
void GameData::RefreshGameData(){
	
	
	
	g_PlayerControllers2 = 0;
	TargetLen = 0.f;
	TargeNear = 0.f;
	EnemyLatelyDistance = 1000.f;
	bool Is_Health = false;
	float Distance = 0.f;
	float len = 0.f;
	Vector3 Pos = Vector3(0.f, 0.f, 0.f), MyPos = Vector3(0.f, 0.f, 0.f), Head = Vector3(0.f, 0.f, 0.f);
	Vector3 Foot = Vector3(0.f, 0.f, 0.f);

	g_Uworld = Mem::Ram<ULONG64>(TslGameBase + OffSet::UWorld); if (g_Uworld <= 0) { g_PlayerControllers = 0; return; }
	g_Uworld = Dec_Uworld(g_Uworld);
	g_Levels = Mem::Ram<ULONG64>(g_Uworld + OffSet::level); if (g_Levels <= 0) { g_PlayerControllers = 0; return; }
	g_Levels = Dec_Level(g_Levels);
	g_Actor = Mem::Ram<ULONG64>(g_Levels + OffSet::Actor); if (g_Actor <= 0) { g_PlayerControllers = 0; return; }
	g_Actor = Dec_Actor(g_Actor);
	g_ObjectList = Mem::Ram<ULONG64>(g_Actor);
	ULONG ListCount = Mem::Ram<ULONG>(g_Actor + 8);
	if (g_ObjectList > 0 && ListCount > 30 && ListCount < 20000) {
		g_Gameinsts = Mem::Ram<ULONG64>(g_Uworld + OffSet::GameInst); if (g_Gameinsts <= 0) { g_PlayerControllers = 0; return; }
		g_Gameinsts = Dec_Gameinst(g_Gameinsts);
		g_LocalPlayers = Mem::Ram<ULONG64>(g_Gameinsts + OffSet::LocalPlayer); if (g_LocalPlayers <= 0) { return; }
		g_LocalPlayers = Dec_LocalPlayers(Mem::Ram<ULONG64>(g_LocalPlayers));
		g_PlayerControllers = Dec_PlayerControllers(Mem::Ram<ULONG64>(g_LocalPlayers + OffSet::PlayerControllers)); if (g_PlayerControllers <= 0) { return; }
		g_Camera = Mem::Ram<ULONG64>(g_PlayerControllers + OffSet::Camera); if (g_Camera <= 0) { return; }
		g_Localactor = Mem::Ram<ULONG64>(g_PlayerControllers + OffSet::Localactor);
		g_Localactor = Dec_Localactor(g_Localactor);
		uint32_t FWRS = 0;
		/*ULONG64 WU1 = Mem::Ram<ULONG64>(GameData::TslGameBase + 0x6FD8E80);
		ULONG64 WU = Mem::Ram<ULONG64>(WU1 + 0x238);*/
	
	/*	auto LocalMesh = Mem::Ram<ULONG64>(g_Localactor + OffSet::Mesh);
		auto AdditiveRot_Increase = Mem::Ram<ULONG64>(LocalMesh + 0xC78);
		printf("AdditiveRot_Increase:%lld",AdditiveRot_Increase);


		auto AdditiveRot_Increase1 = Mem::Ram<ULONG64>(LocalMesh + 0xC68);
		printf("AdditiveRot_Increase1:%lld", AdditiveRot_Increase1);


		auto AdditiveRot_Increase2 = Mem::Ram<ULONG64>(LocalMesh + 0xC88);
		printf("AdditiveRot_Increase2:%lld", AdditiveRot_Increase2);


		auto AdditiveRot_Increase3 = Mem::Ram<ULONG64>(LocalMesh + 0xC98);
		printf("AdditiveRot_Increase3:%lld", AdditiveRot_Increase3);*/






	/*	wchar_t buffinfo2[64];
		swprintf(buffinfo2, XorStringW(L"%f"), ben2);
		AddDrawInfo(5, 120.F, 130.F, 0, 0, 5.f, 0xFF0000FF, 0xFF000000, 0, buffinfo2);
		float ben3 = Mem::Ram<float>(g_Localactor + 0x9C0+8);
		wchar_t buffinfo3[64];
		swprintf(buffinfo3, XorStringW(L"%f"), ben3);
		AddDrawInfo(5, 130.F, 140.F, 0, 0, 5.f, 0xFF0000FF, 0xFF000000, 0, buffinfo3);
		float ben4 = Mem::Ram<float>(g_Localactor + 0x9C0 + 12);
		wchar_t buffinfo4[64];
		swprintf(buffinfo4, XorStringW(L"%f"), ben4);
		AddDrawInfo(5, 140.F, 150.F, 0, 0, 5.f, 0xFF0000FF, 0xFF000000, 0, buffinfo4);
		float ben5 = Mem::Ram<float>(g_Localactor + 0x9C0 + 16);
		wchar_t buffinfo5[64];
		swprintf(buffinfo5, XorStringW(L"%f"), ben5);
		AddDrawInfo(5, 150.F, 160.F, 0, 0, 5.f, 0xFF0000FF, 0xFF000000, 0, buffinfo5);
		float ben6 = Mem::Ram<float>(g_Localactor + 0x9C0 + 20);
		wchar_t buffinfo6[64];
		swprintf(buffinfo6, XorStringW(L"%f"), ben6);
		AddDrawInfo(5, 160.F, 170.F, 0, 0, 5.f, 0xFF0000FF, 0xFF000000, 0, buffinfo6);
		float ben7 = Mem::Ram<float>(g_Localactor + 0x9C0 + 24);
		wchar_t buffinfo7[64];
		swprintf(buffinfo7, XorStringW(L"%f"), ben7);
		AddDrawInfo(5, 170.F, 180.F, 0, 0, 5.f, 0xFF0000FF, 0xFF000000, 0, buffinfo7);
		float ben8 = Mem::Ram<float>(g_Localactor + 0x9C0 + 28);
		wchar_t buffinfo8[64];
		swprintf(buffinfo8, XorStringW(L"%f"), ben8);
		AddDrawInfo(5, 180.F, 190.F, 0, 0, 5.f, 0xFF0000FF, 0xFF000000, 0, buffinfo8);*/
		
		
		int longName = 0;
		g_PlayerControllers2 = g_PlayerControllers;
		if (Switch_Radar) {
			初始雷达参数();
			刷新雷达();
		}
		TempItemOverlayArr.clear();
		for (size_t i = 0; i < ListCount; i++)
		{
			ULONG64 pObject = Mem::Ram<ULONG64>(g_ObjectList + i * 8);
			if (pObject > 0 && pObject != g_Localactor) {
				ULONG ObjectId = Xenuine_DecryptID(pObject);
				ObjectIdInfo ObjIdInfo;

				if (IsObjectId(ObjectId, &ObjIdInfo)) {

					if ((ObjIdInfo.Type == 1 || ObjIdInfo.Type == 2) && Switch_Player) {
						//MessageBox(0, L"1", 0, 0);
						auto Health = Mem::Ram<float>(pObject + OffSet::Health);
						auto Health_Die = Mem::Ram<float>(pObject + OffSet::Health_Die);
						if (((Health > 0) && (Health <= 100)) || ((Health_Die > 0) && (Health_Die <= 100))) {
							auto ObjectMesh = Mem::Ram<ULONG64>(pObject + OffSet::Mesh);
							auto LocalMesh = Mem::Ram<ULONG64>(g_Localactor + OffSet::Mesh);
							ULONG Team = Mem::Ram<ULONG>(pObject + OffSet::TeamNumber);//队伍编号TeamNumber
							ULONG64 MyTame = Dec_Localactor(Mem::Ram<ULONG64>(pObject + OffSet::MyTeam));
							if (MyTame != 0) { continue; }
							GetBoneIndex(ObjectMesh, &Pos, 15);
							GetBoneIndex(LocalMesh, &MyPos, 15);
							Vector3 ppp = Mem::Ram<Vector3>(g_PlayerControllers + OffSet::PItchX);
							Vector3 Location = Mem::Ram<Vector3>(g_Camera + OffSet::CameraPos);

							BOOL Easy = LineTraceSingle(pObject, Location, Pos);
							if (Switch_Radar) {
								float 局_雷达2D坐标x, 局_雷达2D坐标y;
								设置雷达坐标(Location.x, Location.y);
								if (雷达坐标转换(ppp.y, Pos.x, Pos.y, &局_雷达2D坐标x, &局_雷达2D坐标y)) {
									AddDrawInfo(3, 局_雷达2D坐标x - 3, 局_雷达2D坐标y - 3, 6, 6, 0, Easy ? ColorInfo.雷达颜色 : ColorInfo.雷达不可视颜色, 0, 0, NULL);
								}
							}
							Distance = (MyPos - Pos).Length() / 100;
							uint32_t DistanceFW = (uint32_t)(MyPos - Pos).Length() / 100.0f;
							if (DistanceFW <= GameData::ESPDistance)
							{
								FWRS++;


							}
							if (EnemyLatelyDistance > Distance && Distance < 300.f) {
								EnemyLatelyDistance = Distance;
							}
							ULONG64 pName = Mem::Ram<ULONG64>(pObject + OffSet::PlayerName);

							//MessageBox(0, L"4", 0, 0);
							if (WorldToScreen(g_Camera, Pos, &Head, &len)) {

								if (len > 0.f && len < ESPDistance)
								{
									auto PlayerState = Dec_Localactor(Mem::Ram<ULONG64>(pObject + OffSet::PlayerState));
									auto PlayerSatisitc = 0;
									if (PlayerState > 0) 
									{
										PlayerSatisitc = Mem::Ram<ULONG>(PlayerState + OffSet::PlayerSatisitc);
									}
								
									//判断对象状态设置颜色
									DWORD BoneColor = 0, InfoColor = 0;
									if (Health_Die > 0 && Health_Die <= 100 && Health == 0) {
										BoneColor = ColorInfo.倒地玩家颜色;
										InfoColor = ColorInfo.倒地玩家颜色;
										Is_Health = true;
									}
									else {
										Is_Health = false;
									}
									Vector4 RectAng;
									//DrawBoneESP(g_Camera, ObjectMesh, BoneColor, &RectAng, 1.0f, 6, true);这颜色。。。能不呢发我个完整的
									//GetBoneRect(g_Camera, ObjectMesh, &RectAng);
									//DrawBone(pObject, g_Camera, ObjectMesh, Easy ? ColorInfo.玩家可视颜色 : ColorInfo.玩家不可视颜色,0 , 1,&RectAng);
									TargetLen = CalculateAngle(ScreenCenterX, ScreenCenterY, Head.x, Head.y);
									if (TargetLen <= 150.f && Switch_Expose) { 
#if (HUD004 || HUD003)
										DrawBone(pObject, g_Camera, ObjectMesh, ColorInfo.玩家可视颜色, ColorInfo.玩家不可视颜色, 1.f, &RectAng, true);
#else
										DrawBone(pObject, g_Camera, ObjectMesh, ColorInfo.玩家可视颜色, ColorInfo.玩家不可视颜色, 1.f, &RectAng, true);
#endif // HUD004

									}
									else {
#if (HUD004 || HUD003)
										DrawBone(pObject, g_Camera, ObjectMesh, Easy ? ColorInfo.玩家可视颜色 : ColorInfo.玩家不可视颜色, 0, 1.f, &RectAng, false);
#else
										DrawBone(pObject, g_Camera, ObjectMesh, Easy ? ColorInfo.玩家可视颜色 : ColorInfo.玩家不可视颜色, 0, 1.f, &RectAng, false);
#endif // HUD004
									}
									char PlayerName[64];
									if (Mem::ReadMemory(pName, PlayerName, 64))
									{
										InfoColor = Easy ? ColorInfo.信息颜色 : ColorInfo.信息颜色不可视颜色;
										
										
											DrawHealth(RectAng.x, RectAng.y, RectAng.w, RectAng.h, InfoColor, Health, (int)len, PlayerSatisitc, Team,(wchar_t*)pName);
										
									}
									if (anti_aim)
									{
										Vector3 AimFov;
										Vector3 AmiMz;
										int AimX;
										int AimY;
										Vector3 AimBots;
										Vector3 LocalPos, ObjePos, Breath = Vector3(0.f, 0.f, 0.f);
										Vector3 自身坐标 = Mem::Ram<Vector3>(LocalMesh + OffSet::PosiTion);
										Vector3 敌人坐标 = Mem::Ram<Vector3>(ObjectMesh + OffSet::PosiTion);
										AimFov = calFOV(敌人坐标, 自身坐标);
										AmiMz = Mem::Ram<Vector3>(pObject + OffSet::antiaim);
										AmiMz = Clamp1(AmiMz);//
										AimX = fabs(AimFov.x - AmiMz.y);
										AimY = fabs(AimFov.y - AmiMz.x);
										//printf("AimX:%d,AimY:%d\n", AimX, AimY);
										GetBoneIndex(ObjectMesh, &ObjePos, 15);
										if (AimX <= 3 && AimY <= 3)
										{
											//longName++;
											if (WorldToScreen(g_Camera, ObjePos, &Foot, &len))
											{

												longName++;
												wchar_t buffinfo[64];
												swprintf(buffinfo, XorStringW(L"警报!警报!%s正在在瞄准你！"), (wchar_t*)pName);
												AddDrawInfo(5, ScreenCenterX - 100, ScreenCenterY * 2 - 1000 + longName * 13, 0, 0, 15.f, 0xFF0000FF, 0xFF000000, 0, buffinfo);
												AddDrawInfo(2, Foot.x, Foot.y, ScreenCenterX, ScreenCenterY * 2 - 1000 + longName * 13, 1, 0xFF0000FF, 0, 0, NULL);
											}


										}
									}
									if (shouchi)//名字 也定义错了  
									{
										auto WeaponProcessor = Mem::Ram<ULONG64>(pObject + OffSet::WeaponProcessor);
										auto EquippedWeapons = Mem::Ram<ULONG64>(WeaponProcessor + OffSet::EquippedWeapons);
										auto CurrentWeaponIndex = Mem::Ram<BYTE>(WeaponProcessor + OffSet::CurrentWeaponIndex);
										if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex <= 4)
										{
											auto pWeap = Mem::Ram<ULONG64>(EquippedWeapons + CurrentWeaponIndex * 0x8);
											if (pWeap > 0)
											{
												uint32_t WeaponID = Xenuine_DecryptID(pWeap);
												string WeaponName = GetNames(WeaponID);
												WeaponName = WeaponName.substr(4, WeaponName.size());
												WeaponName = WeaponName.substr(0, WeaponName.size() - 2);
												float X = RectAng.x + (RectAng.w / 2) - 25.f;
												float Y = RectAng.y - 10;
												AddDrawInfo(5, X - 20, Y - 20 + 5 - 15, 0, 0, 15.f, ColorInfo.信息颜色, 0xFF000000, 0, char20wchar(WeaponName.c_str()));


											}
										}
									}
									if (HUANFU)
									{
										auto 武器指针 = Mem::Ram<ULONG64>(g_Localactor + OffSet::WeaponProcessor);
										auto 武器位置 = Mem::Ram<BYTE>(武器指针 + OffSet::CurrentWeaponIndex);
										auto 武器基址A = Mem::Ram<ULONG64>(武器指针 + OffSet::EquippedWeapons);
										auto 当前武器A = Mem::Ram<ULONG64>(武器基址A + 武器位置 * 8);
										if (武器位置 >= 0 && 武器位置 <= 4)
										{
											if (当前武器A > 0)
											{
												uint32_t WeaponID = Xenuine_DecryptID(当前武器A);
												std::string Name = GameData::GetNames(WeaponID);
												uint32_t skinid = jugement(Name.c_str());
												uint64_t 皮肤指针 = DecFunction(Mem::Ram<uint64_t>(当前武器A + OffSet::WeaponMesh));					
												if ((Mem::NtUserGetAsyncKeyState(VK_ADD) != 0))
												{
													Mem::Wam<ULONG>(皮肤指针 + OffSet::SkinId - 8, 0x3);
													Mem::Wam<ULONG>(皮肤指针 + OffSet::SkinId, skinid);
												}


											}
										}

									}
									//设置自瞄目标
									if ((IsLock == FALSE))
									{
										if (Is_Health) 
										{ 
											continue; 
										}
										TargetLen = CalculateAngle(ScreenCenterX, ScreenCenterY, Head.x, Head.y);
										if (TargetLen < AimbotRange)
										{
											if (TargeNear == 0.f) 
											{
												TargeNear = TargetLen;
												Aimbot = pObject;
											}
											else 
											{
												if (TargetLen < TargeNear) 
												{
													TargeNear = TargetLen;
													Aimbot = pObject;
												}
											}
										}
									}
								}
							}

						}
					}//显示载具
					if (ObjIdInfo.Type == 3 && Switch_Vehicle) {
						auto DroppedItemGroup = Mem::Ram<ULONG64>(pObject + OffSet::DroppedItemGroup);
						if (DroppedItemGroup <= 0) { continue; }
						DroppedItemGroup = Mem::Ram<ULONG64>(DroppedItemGroup);
						if (DroppedItemGroup <= 0) { continue; }
						Vector3 Position = Mem::Ram<Vector3>(DroppedItemGroup + OffSet::PosiTion);
						if (WorldToScreen(g_Camera, Position, &Foot, &len)) {
							wchar_t ShowText[64];

							swprintf(ShowText, L"%s[%dm]", ObjIdInfo.Alias, (int)len);

							AddDrawInfo(5, Foot.x, Foot.y, 0, 0, 10, ObjIdInfo.Color, 0xFF000000, 0, ShowText);
						}
					}//空头 战利品
					
					if ((ObjIdInfo.Type == 4 || ObjIdInfo.Type == 5) && Switch_Battle ==false &&Switch_BoxSupport)//
					{
						auto DroppedItemGroup = Mem::Ram<ULONG64>(pObject + OffSet::DroppedItemGroup); if (DroppedItemGroup <= 0) { continue; }
						DroppedItemGroup = Mem::Ram<ULONG64>(DroppedItemGroup); if (DroppedItemGroup <= 0) { continue; }
						Vector3 Position = Mem::Ram<Vector3>(DroppedItemGroup + OffSet::PosiTion);
						float len = 0.f;
						if (WorldToScreen(g_Camera, Position, &Foot, &len))
						{
							DWORD_PTR PackList = Mem::Ram<DWORD_PTR>(pObject + OffSet::Package - 8); if (PackList == 0) { continue; }
							auto PackCount = Mem::Ram<ULONG>(pObject + OffSet::Package);
							int longName = 0;
							for (ULONG i = 0; i < PackCount; i++)
							{
								auto PackObject = Mem::Ram<DWORD_PTR>(PackList + i * 8);
								if (PackObject > 0) 
								{
									auto PackId =Mem::Ram<ULONG>(PackObject + OffSet::WPItemId);
									ObjectIdInfo objinfo;
									if (IsObjectId(PackId, &objinfo))
									{
										longName++;
										wchar_t ShowText[64];
										swprintf(ShowText, XorStringW(L" %s"), objinfo.Alias);
										AddDrawInfo(1, Foot.x, Foot.y - 13 * longName, 0, 0, 9, objinfo.Color, 0xFF000000, 0, ShowText);
									}
								}
							}
							

							wchar_t ShowText[64];
							swprintf(ShowText, XorStringW(L"%s[%dm]"), ObjIdInfo.Alias, (int)len);
							AddDrawInfo(5, Foot.x + 4, Foot.y, 0, 0, 9, ObjIdInfo.Color, 0xFF000000, 0, ShowText);//- wcslen(ObjIdInfo.Alias) * 6 / 2
						}
					}//绘制物品
					if (ObjIdInfo.Type == 6 && Switch_Battle == false && Switch_Item == true)
					{
						ULONG64 ItemList = Mem::Ram<ULONG64>(pObject + OffSet::DroppedItemGroup);
						ULONG Itemcount = Mem::Ram<ULONG>(pObject + OffSet::DroppedItemGroup + 0x8);
						if (ItemList > 0 && Itemcount < 50 && Itemcount > 0)
						{
							int longName = 0;
							for (ULONG i = 0; i < Itemcount; i++)
							{
								ULONG64 pItem = Mem::Ram<ULONG64>(ItemList + i * 0x10);
								if (pItem > 0)
								{
									ULONG64 pItemIns = Mem::Ram<ULONG64>(pItem + OffSet::DroppedItemGroup_UItem);
									if (pItemIns > 0)
									{
										ULONG ItemId = Mem::Ram<ULONG>(pItemIns + OffSet::WPItemId);
										if (ItemId > 0)
										{
											//ItemId = Dec_ObjectId(ItemId);//现在这个版本不需要再用解密ID直接读 即可

											ObjectIdInfo objinfo;
											if (IsObjectId(ItemId, &objinfo)) {
												if (ItemShow_YaoPin == false && objinfo.Type == 7) { continue; }
												if (ItemShow_ZhuangBei == false && objinfo.Type == 8) { continue; }
												if (ItemShow_Juji == false && objinfo.Type == 9) { continue; }
												if (ItemShow_BuQiang == false && objinfo.Type == 10) { continue; }
												if (ItemShow_PeiJian == false && objinfo.Type == 11) { continue; }
												Vector3 Position = Mem::Ram<Vector3>(pItem + OffSet::PosiTion);
												if (WorldToScreen(g_Camera, Position, &Foot, &len))
												{
													if (len <= 120.f)
													{
														FVector2D D2D = { Foot.x,Foot.y };
														IsOverlay(D2D);
														TempItemOverlayArr.push_back(D2D);
														wchar_t ShowText[128];
														swprintf(ShowText, L"%s[%dm]", objinfo.Alias, (int)len);
														AddDrawInfo(1, D2D.X - (float)wcslen(objinfo.Alias), D2D.Y, 0, 0, 9, objinfo.Color, 0xFF000000, 0, ShowText);
													}
												}
											}
										}
									}
								}
							}
						}
					}
					//判断结束
				}
			}
		}
		if (g_Localactor > 0) //
		{
			ULONG Audience = Mem::Ram<ULONG>(g_Localactor + OffSet::Audience);
			if (Audience < 0 || Audience > 20)
			{
				Audience = 0;
			}
			if (Audience > 0 || EnemyLatelyDistance < 300.f)
			{
				wchar_t AudienceText[128];
				wchar_t AudienceText1[128];
				swprintf(AudienceText1, XorStringW(L"观战人数:%d人"), Audience);
				swprintf(AudienceText, XorStringW(L"%dM内敌人个数:%d  最近敌人:%dM"), (int)GameData::ESPDistance, FWRS,(int)EnemyLatelyDistance);
				AddDrawInfo(6, 10, 20, 0, 0, 0.9f, 0xFFFFFFFF, 0xFF000000, 0, AudienceText1);


				AddDrawInfo(6, ScreenCenterX - 150, ScreenCenterY * 2 - 200, 0, 0, 0.9f, 0xFF0000FF, 0xFF000000, 0, AudienceText);
			//	AddDrawInfo(6, 1.f, 1.f, 0, 0, 0.9f, 0xFF0000FF, 0xFF000000, 0, AudienceText1);
			}
		}
		if (Switch_chuanqiang)
		{
			if ((Mem::NtUserGetAsyncKeyState(VK_RBUTTON) != 0))
			{
				if (Aimbot > 0)
				{
					IsLock = TRUE;
					Vector3 AimBots;
					bool IsBoneShow = false;
					Vector3 LocalPos, ObjePos, Breath = Vector3(0.f, 0.f, 0.f);
					auto ObjectMesh = Mem::Ram<ULONG64>(Aimbot + OffSet::Mesh);
					auto LocalMesh = Mem::Ram<ULONG64>(g_Localactor + OffSet::Mesh);
					LocalPos = Mem::Ram<Vector3>(g_Camera + OffSet::CameraPos);
					if (Mem::NtUserGetAsyncKeyState(VK_SHIFT) != 0)
					{
						GetBoneIndex(ObjectMesh, &ObjePos, 15);
						IsBoneShow = true;
					}
					else
					{						
							GetBoneIndex(ObjectMesh, &ObjePos, 4);
							IsBoneShow = true;
						
					}


					if (IsBoneShow && WorldToScreen(g_Camera, ObjePos, &AimBots, &len))
					{
						AddDrawInfo(5, AimBots.x - 3, AimBots.y - 3, 0, 0, 14, 0xFF00FF00, 0xFF000000, 0, L"已追踪");
						auto WeaponProcessor = Mem::Ram<ULONG64>(g_Localactor + OffSet::WeaponProcessor);
						auto EquippedWeapons = Mem::Ram<ULONG64>(WeaponProcessor + OffSet::EquippedWeapons);
						auto CurrentWeaponIndex = Mem::Ram<BYTE>(WeaponProcessor + OffSet::CurrentWeaponIndex);
						if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex < 3)
						{
							auto pWeap = Mem::Ram<ULONG64>(EquippedWeapons + CurrentWeaponIndex * 8);
							if (pWeap > 0)
							{
								ULONG64 ulSpeedAddr = Mem::Ram<ULONG64>(pWeap + OffSet::WeaponTrajectoryData);
								float InitialSpeed = Mem::Ram<float>(ulSpeedAddr + OffSet::TrajectoryConfig);
								float HitTime = CalcBulletArriveTime((LocalPos - ObjePos).Length() / 100.f, InitialSpeed);
								ULONG64 pBulletTable = Dec_Bullets(Mem::Ram<ULONG64>(pWeap + OffSet::BulletTable));
								ULONG64 BulletTable = Mem::Ram<ULONG64>(pBulletTable);
								ULONG BulletTable_Count = Mem::Ram<ULONG>(pBulletTable + 8);
								if (BulletTable_Count > 0)
								{
									for (ULONG i = 0; i < BulletTable_Count; i++)//216  36  76数组：0xE0  0xA4  0xB0

									{
										ULONG64 pBullet = BulletTable + i * OffSet::ShuZu;
										float StopTime = Mem::Ram<float>(pBullet + OffSet::ShiJian);
										if (StopTime > HitTime)
										{

											if (pBullet > (int)GameData::ESPDistance)
											{

												//DELETEHOOK();
												Mem::Wam<Vector3>(pBullet + OffSet::ZuoBiao, ObjePos);
											}
											else
											{


												Mem::Wam<float>(pBullet + OffSet::ZuoBiao, 0);
											}


										}
									}
								}
							}
						}
					}




				}
			}
			else
			{
			//	ZZHOOK();
				Aimbot = 0;
				Aimbot_sw = 0;
				IsLock = FALSE;
			}
		}
		if (Switch_AimBot)
		{
			if ((Mem::NtUserGetAsyncKeyState(VK_RBUTTON) != 0))
			{
				if (Aimbot > 0)
				{
					IsLock = TRUE;
					Vector3 AimBots;
					bool IsBoneShow = false;
					Vector3 LocalPos, ObjePos, Breath = Vector3(0.f, 0.f, 0.f);
					auto ObjectMesh = Mem::Ram<ULONG64>(Aimbot + OffSet::Mesh);
					auto LocalMesh = Mem::Ram<ULONG64>(g_Localactor + OffSet::Mesh);//0x510
					LocalPos = Mem::Ram<Vector3>(g_Camera + OffSet::CameraPos);
					if (Mem::NtUserGetAsyncKeyState(VK_SHIFT) != 0)
					{
						GetBoneIndex(ObjectMesh, &ObjePos, 15);
						IsBoneShow = true;
					}
					else {
						if (Switch_Expose)
						{
							for (int i = 0; i < 28; i++)
							{
								GetBoneIndex(ObjectMesh, &ObjePos, AimBotBone[i]);
								if (LineTraceSingle(Aimbot, LocalPos, ObjePos))
								{
									IsBoneShow = true;
									break;
								}
							}
						}
						else
						{
							GetBoneIndex(ObjectMesh, &ObjePos, 4);
							IsBoneShow = true;
						}
					}
					if (IsBoneShow && WorldToScreen_Aim(g_Camera, LocalMesh, ObjePos, &AimBots, &len))
					{
						
						auto WeaponProcessor = Mem::Ram<ULONG64>(g_Localactor + OffSet::WeaponProcessor);
						auto EquippedWeapons = Mem::Ram<ULONG64>(WeaponProcessor + OffSet::EquippedWeapons);
						auto CurrentWeaponIndex = Mem::Ram<BYTE>(WeaponProcessor + OffSet::CurrentWeaponIndex);
						if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex < 3)
						{
							auto pWeap = Mem::Ram<ULONG64>(EquippedWeapons + CurrentWeaponIndex * 8);
							if (pWeap > 0)
							{

								auto WeaponProcessor = Mem::Ram<ULONG64>(g_Localactor + OffSet::WeaponProcessor);
								auto EquippedWeapons = Mem::Ram<ULONG64>(WeaponProcessor + OffSet::EquippedWeapons);
								auto CurrentWeaponIndex = Mem::Ram<BYTE>(WeaponProcessor + OffSet::CurrentWeaponIndex);
								if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex < 3)
								{
									auto pWeap = Mem::Ram<ULONG64>(EquippedWeapons + CurrentWeaponIndex * 8);
									if (pWeap > 0)
									{

										


										ULONG64 ulSpeedAddr = Mem::Ram<ULONG64>(pWeap + OffSet::WeaponTrajectoryData);
										float InitialSpeed = Mem::Ram<float>(ulSpeedAddr + OffSet::TrajectoryConfig);
										auto m_gravity = Mem::Ram<float>(ulSpeedAddr + OffSet::TrajectoryConfig + 24);
										预判数据 局_预判数据 = 取预判初始数据(GetUNames(Xenuine_DecryptID(pWeap)));


										if (局_预判数据.子弹速度 <= 0)
										{
											局_预判数据.子弹速度 = (int)InitialSpeed;
										}
										float len = (LocalPos - ObjePos).Length() / 100.f;
										auto actorRootComponent = GameData::Dec_Localactor(Mem::Ram<ULONG64>(Aimbot + OffSet::ActorRootComp));
										auto TargetSpeed = Mem::Ram<Vector3>(actorRootComponent + OffSet::Veloctity);
										ObjePos = 取预判坐标(ObjePos, len, TargetSpeed, 9.8f, 局_预判数据, m_gravity);
										if (WorldToScreen_Aim(g_Camera, LocalMesh, ObjePos, &AimBots, &len))
										{

											AddDrawInfo(5, AimBots.x - 3, AimBots.y - 3, 0, 0, 14, 0xFF0000FF, 0xFF000000, 0, L"已瞄准");
											AimBots.x = (AimBots.x - ScreenCenterX) * 0.01 * 100;
											AimBots.y = (AimBots.y - ScreenCenterY) * 0.01 * 100;
											AimBot_API(AimBots.x, AimBots.y);

										}
									}
								}
							}
						}
					}
				}
			}
			else
			{

				Aimbot = 0;
				Aimbot_sw = 0;
				IsLock = FALSE;
			}
		}

		ULONG64 puad = Dec_Localactor(Mem::Ram<ULONG64>(g_Localactor + 0x490));
		if (jiasu)
		{
			if (Mem::NtUserGetAsyncKeyState(VK_SHIFT) != 0)
			{
				Mem::Wam<float>(puad + 0x2F8, 100000);
				Mem::Wam<float>(puad + 0x20C, -1700);
			}
			else
			{
				Mem::Wam<float>(puad + 0x2F8, 700);
			}
		}
		/*if (Switch_chuanqiang)
		{
			if ((Mem::NtUserGetAsyncKeyState(VK_RBUTTON) != 0))
			{
				if (Aimbot > 0)
				{
					IsLock = TRUE;
					Vector3 AimBots;
					bool IsBoneShow = false;
					Vector3 LocalPos, ObjePos, Breath = Vector3(0.f, 0.f, 0.f);
					auto ObjectMesh = Mem::Ram<ULONG64>(Aimbot + OffSet::Mesh);
					auto LocalMesh = Mem::Ram<ULONG64>(g_Localactor + OffSet::Mesh);
					LocalPos = Mem::Ram<Vector3>(g_Camera + OffSet::CameraPos);
					if (Mem::NtUserGetAsyncKeyState(VK_SHIFT) != 0)
					{
						GetBoneIndex(ObjectMesh, &ObjePos, 15);
						IsBoneShow = true;
					}
					else
					{
						if (Switch_Expose)
						{
							for (int i = 0; i < 28; i++)
							{
								GetBoneIndex(ObjectMesh, &ObjePos, AimBotBone[i]);
								if (LineTraceSingle(Aimbot, LocalPos, ObjePos))
								{
									IsBoneShow = true;
									break;
								}
							}
						}
						else
						{
							GetBoneIndex(ObjectMesh, &ObjePos, 4);
							IsBoneShow = true;
						}
					}
					if (IsBoneShow && WorldToScreen(g_Camera, ObjePos, &AimBots, &len))
					{
						AddDrawInfo(5, AimBots.x - 3, AimBots.y - 3, 0, 0, 14, 0xFF0000FF, 0xFF000000, 0, L"已追踪");
						auto WeaponProcessor = Mem::Ram<ULONG64>(g_Localactor + OffSet::WeaponProcessor);
						auto EquippedWeapons = Mem::Ram<ULONG64>(WeaponProcessor + OffSet::EquippedWeapons);
						auto CurrentWeaponIndex = Mem::Ram<BYTE>(WeaponProcessor + OffSet::CurrentWeaponIndex);
						if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex < 3)
						{
							auto pWeap = Mem::Ram<ULONG64>(EquippedWeapons + CurrentWeaponIndex * 8);
							if (pWeap > 0)
							{
								ULONG64 ulSpeedAddr = Mem::Ram<ULONG64>(pWeap + OffSet::WeaponTrajectoryData);
								float InitialSpeed = Mem::Ram<float>(ulSpeedAddr + OffSet::TrajectoryConfig);
								float HitTime = CalcBulletArriveTime((LocalPos - ObjePos).Length() / 100.f, InitialSpeed);
								ULONG64 pBulletTable = Dec_Bullets(Mem::Ram<ULONG64>(pWeap + OffSet::BulletTable));
								ULONG64 BulletTable = Mem::Ram<ULONG64>(pBulletTable);
								ULONG BulletTable_Count = Mem::Ram<ULONG>(pBulletTable + 8);
								if (BulletTable_Count > 0)
								{
									for (ULONG i = 0; i < BulletTable_Count; i++)

									{
										ULONG64 pBullet = BulletTable + i * OffSet::ShuZu;
										float StopTime = Mem::Ram<float>(pBullet + OffSet::ShiJian);
										if (StopTime > HitTime)
										{

											if (pBullet > (int)GameData::ESPDistance)
											{
												ZZHOOK();
												Mem::Wam<Vector3>(pBullet + OffSet::ZuoBiao, ObjePos);

											}
											else
											{
												Mem::Wam<float>(pBullet + OffSet::ZuoBiao, 0);
											}
										}
									}
								}
							}
						}
					}
				}
			}
			else
			{
				DELETEHOOK();
				Aimbot = 0;
				Aimbot_sw = 0;
				IsLock = FALSE;
			}
		}*/
		//if ((Mem::NtUserGetAsyncKeyState(VK_RBUTTON) != 0) && Switch_chuanqiang)
		//{
		//	if (Aimbot > 0) 
		//	{
		//		IsLock = TRUE;
		//		Vector3 AimBots;
		//		bool IsBoneShow = false;
		//		Vector3 LocalPos, ObjePos, Breath = Vector3(0.f, 0.f, 0.f);
		//		auto ObjectMesh = Mem::Ram<ULONG64>(Aimbot + OffSet::Mesh);
		//		auto LocalMesh = Mem::Ram<ULONG64>(g_Localactor + OffSet::Mesh);
		//		LocalPos = Mem::Ram<Vector3>(g_Camera + OffSet::CameraPos);
		//		if (Mem::NtUserGetAsyncKeyState(VK_SHIFT) != 0)
		//		{
		//			GetBoneIndex(ObjectMesh, &ObjePos, 15);
		//			IsBoneShow = true;
		//		}
		//		else {
		//			if (Switch_Expose) {
		//				for (int i = 0; i < 28; i++)
		//				{
		//					GetBoneIndex(ObjectMesh, &ObjePos, AimBotBone[i]);
		//					if (LineTraceSingle(Aimbot, LocalPos, ObjePos))
		//					{
		//						IsBoneShow = true;
		//						break;
		//					}
		//				}
		//			}
		//			else
		//			{
		//				GetBoneIndex(ObjectMesh, &ObjePos, 4);
		//				IsBoneShow = true;
		//			}
		//		}
		//		if (IsBoneShow && WorldToScreen(g_Camera, ObjePos, &AimBots, &len))
		//		{

		//			AddDrawInfo(5, AimBots.x - 3, AimBots.y - 3, 0, 0, 14, 0xFF0000FF, 0xFF000000, 0, L"已追踪");
		//			auto WeaponProcessor = Mem::Ram<ULONG64>(g_Localactor + OffSet::WeaponProcessor);
		//			BYTE 静默追踪还原数据 = Mem::Ram<BYTE>(GameData::TslGameBase + OffSet::MagicBullet);
		//			auto EquippedWeapons = Mem::Ram<ULONG64>(WeaponProcessor + OffSet::EquippedWeapons);
		//			auto CurrentWeaponIndex = Mem::Ram<BYTE>(WeaponProcessor + OffSet::CurrentWeaponIndex);
		//			if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex < 3)
		//			{
		//				auto pWeap = Mem::Ram<ULONG64>(EquippedWeapons + CurrentWeaponIndex * 8);
		//				if (pWeap > 0)
		//				{
		//					ULONG64 ulSpeedAddr = Mem::Ram<ULONG64>(pWeap + OffSet::WeaponTrajectoryData);
		//					float InitialSpeed = Mem::Ram<float>(ulSpeedAddr + OffSet::TrajectoryConfig);
		//					auto m_gravity = Mem::Ram<float>(ulSpeedAddr + OffSet::TrajectoryConfig + 24);
		//					预判数据 局_预判数据 = 取预判初始数据(GetUNames(Xenuine_DecryptID(pWeap)));
		//					if (局_预判数据.子弹速度 <= 0)
		//					{
		//						局_预判数据.子弹速度 = (int)InitialSpeed;
		//					}
		//					float len = (LocalPos - ObjePos).Length() / 100.f;
		//					auto actorRootComponent = GameData::Dec_Localactor(Mem::Ram<ULONG64>(Aimbot + OffSet::ActorRootComp));
		//					auto TargetSpeed = Mem::Ram<Vector3>(actorRootComponent + OffSet::Veloctity);
		//					ObjePos = 取预判坐标(ObjePos, len, TargetSpeed, 9.8f, 局_预判数据, m_gravity);
		//					if (Mem::Ram<BYTE>(TslGameBase + OffSet::XeCrc) == (BYTE)0x44) //CRC用MagicBullet = 1B0C76F ;
		//					{
		//						//Xenuine::SetCrcPass(TslGameBase + OffSet::XeCrc, TslGameBase + OffSet::XeCrc + 13, 13);//C7 44 24 ?? FF FF FF FF C7 44 24 ?? FF FF FF FF 49 8B 9D ???????? 8B D7 48 8B CB E8 ???????? 85 FF
		//						HookSilenceAimBotReturn = GameData::TslGameBase + OffSet::MagicBullet + 14;
		//						BYTE outAimbot[] = { 0xFF,0x25,0x00,0x00 ,0x00,0x00 ,0x00,0x00 ,0x00,0x00 ,0x00,0x00 ,0x00,0x00 };
		//						*(ULONG64*)(outAimbot + 6) = (ULONG64)SilenceAimBot2;
		//						Mem::DriverWrite(GameData::TslGameBase + OffSet::MagicBullet, outAimbot, 14);
		//						Mem::DriverWrite(GameData::TslGameBase + OffSet::MagicBullet, (BYTE*)静默追踪还原数据, 14);
		//					}
		//					LockAim(ObjePos);
		//				}
		//			}
		//		}
		//	}
		//	else
		//	{
		//		BYTE 静默追踪还原数据 = Mem::Ram<BYTE>(GameData::TslGameBase + OffSet::MagicBullet);
		//		if (Mem::Ram<BYTE>(TslGameBase + OffSet::XeCrc) == (BYTE)0x50)
		//		{
		//			BYTE OLGCODE[14] = { 0x49,0x8B,0xCC,0xE8,0xD0,0x20,0x9A,0xFF,0x0F,0xB6,0xD0,0x49,0x8B,0xCC };
		//			Mem::DriverWrite(GameData::TslGameBase + OffSet::MagicBullet, OLGCODE, 14);
		//			Mem::DriverWrite(GameData::TslGameBase + OffSet::MagicBullet, (BYTE*)静默追踪还原数据, 14);
		//		//	Xenuine::UnCrcPass(TslGameBase + OffSet::XeCrc);
		//		}
		//		Aimbot_sw = 0;
		//		IsLock = FALSE;
		//	}
		//}	
	}
}
		
				

Vector3 calFOV(Vector3 D, Vector3 W) {
	float 坐标X差 = W.x - D.x;
	float 坐标Y差 = W.y - D.y;
	float 坐标Z差 = W.z - D.z;
	Vector3 角度;
	角度.x = (atan2(坐标Y差, 坐标X差)) * 180 / M_PI;
	角度.y = (atan2(坐标Z差, sqrt(坐标X差 * 坐标X差 + 坐标Y差 * 坐标Y差))) * 180 / M_PI;
	return 角度;
}
Vector3 Clamp1(Vector3 Ver) {
	Vector3 Result = Ver;
	if (Result.x > 180)
	{
		Result.x -= 360;
	}
	else
	{
		if (Result.x < -180)
		{
			Result.x += 360;
		}
	}
	if (Result.y > 180)
	{
		Result.y -= 360;
	}
	else {
		if (Result.y < -180)
		{
			Result.y += 360;
		}
	}
	if (Result.x > 89)
	{
		Result.x = 89;
	}
	if (Result.x < -89)
	{
		Result.x = -89;
	}
	while (Result.y < 180)
	{
		Result.y += 360;
	}
	while (Result.y > 180)
	{
		Result.y -= 360;
	}
	Result.z = 0;
	return Result;
}

int AimBot_API(int 瞄准X, int 瞄准Y)
{
	INPUT Input;
	int iPosX = 瞄准X;
	int iPosY = 瞄准Y;
	Input.type = 0;
	Input.mi.dx = iPosX;
	Input.mi.dy = iPosY;
	Input.mi.dwFlags = 1;
	return Mem::NtUserSendInput(1, &Input, sizeof(Input));
}
VOID GameData::LockAim(Vector3 TargetCenterOfMass)
{
	FRotator AngLocalAngles = Mem::Ram<FRotator>(g_PlayerControllers + OffSet::PItchX);
	Vector3 Delta = Mem::Ram<Vector3>(g_Camera + OffSet::CameraPos);
	FRotator AngDelta = (Vector3ToFRotator(TargetCenterOfMass - Delta) - AngLocalAngles).Clamp();//
	AngLocalAngles = AngLocalAngles + AngDelta;
	Aimbot_x = AngLocalAngles.Pitch;
	Aimbot_y = AngLocalAngles.Yaw;
	Aimbot_sw = 1;
}
float GameData::CalcBulletArriveTime(float ObjLen, float InitialSpeed) {
	float Attenuation = 0.f;
	if (ObjLen <= 100.f) {
		Attenuation = 1.11f;
	}else if (ObjLen <= 150.f) {
		Attenuation = 1.165f;
	}else if (ObjLen <= 200.f) {
		Attenuation = 1.22f;
	}else if(ObjLen <= 250.f) {
		Attenuation = 1.275f;
	}else if (ObjLen <= 300.f) {
		Attenuation = 1.33f;
	}else if (ObjLen <= 350.f) {
		Attenuation = 1.385f;
	}else if (ObjLen <= 400.f) {
		Attenuation = 1.44f;
	}else if (ObjLen <= 450.f) {
		Attenuation = 1.495f;
	}else if (ObjLen <= 500.f) {
		Attenuation = 1.55f;
	}else if (ObjLen <= 550.f) {
		Attenuation = 1.605f;
	}else if(ObjLen <= 600.f) {
		Attenuation = 1.66f;
	}else if (ObjLen <= 650.f) { //
		Attenuation = 1.715f;
	}else if (ObjLen <= 700.f) {
		Attenuation = 1.77f;
	}else if (ObjLen <= 750.f) {
		Attenuation = 1.825f;
	}else if (ObjLen <= 800.f) {
		Attenuation = 1.88f;
	}else if(ObjLen <= 850.f) {
		Attenuation = 1.935f;
	}else if (ObjLen <= 900.f) {
		Attenuation = 1.99f;
	}else if (ObjLen <= 950.f) {
		Attenuation = 2.045f;
	}else if (ObjLen <= 1000.f) {
		Attenuation = 2.1f;
	}else{
		Attenuation = 2.155f;
	}
	return (ObjLen / InitialSpeed) * Attenuation;
}
FRotator GameData::GetAim(Vector3 TargetCenterOfMass)
{
	FRotator AngLocalAngles = Mem::Ram<FRotator>(g_PlayerControllers + OffSet::PItchX);
	Vector3 Delta = Mem::Ram<Vector3>(g_Camera + OffSet::CameraPos);
	FRotator AngDelta = (Vector3ToFRotator(TargetCenterOfMass - Delta) - AngLocalAngles).Clamp();//
	AngLocalAngles = AngLocalAngles + AngDelta;
	Aimbot_x = AngLocalAngles.Pitch;
	Aimbot_y = AngLocalAngles.Yaw;
	Aimbot_sw = 1;
	return AngLocalAngles;

}
bool GameData::DrawBone(ULONG64 entity, ULONG64 pCamera, ULONG64 Mesh, DWORD Color, DWORD Color2, float px, Vector4* Rect, bool exaly) {
	Vector3 localeye = Mem::Ram<Vector3>(pCamera + OffSet::CameraPos);
	Vector3 neckpos, pelvispos, previous, current, p1, c1;
	Vector3 lefttop = Vector3(0.f, 0.f, 0.f), rightbottom = Vector3(0.f, 0.f, 0.f);
	GetBoneIndex(Mesh, &neckpos, Bones::neck_01);
	GetBoneIndex(Mesh, &pelvispos, Bones::pelvis);
	bool previousvis = false, currentvis = false, retbool = false;
	for (int i = 0; i < 6; i++)
	{
		previous = Vector3(0, 0, 0);
		for (int x = 0; x < 8; x++)
		{
			if (BoneInfo[i][x] == -1) {
				continue;
			}
			Vector3 aipos;
			GetBoneIndex(Mesh, &aipos, BoneInfo[i][x]);
			current = BoneInfo[i][x] == Bones::neck_01 ? neckpos : (BoneInfo[i][x] == Bones::pelvis ? pelvispos : aipos);
			//currentvis = ;
			//if (currentvis) {
			//	retbool = true;
			//}
			if (previous.x == 0.f)
			{
				//previousvis = currentvis;
				previous = current;
				continue;
			}
			if (WorldToScreen(pCamera, previous, &p1, NULL) && WorldToScreen(pCamera, current, &c1, NULL))
			{
				if (exaly) {
					if (LineTraceSingle(entity, localeye, previous) || LineTraceSingle(entity, localeye, current)) {
						AddDrawInfo(2, p1.x, p1.y, c1.x, c1.y, px, Color, NULL, 0, NULL);
					}
					else {
						AddDrawInfo(2, p1.x, p1.y, c1.x, c1.y, px, Color2, NULL, 0, NULL);
					}
				}
				else {
					AddDrawInfo(2, p1.x, p1.y, c1.x, c1.y, px, Color, NULL, 0, NULL);
				}

				if (lefttop.x == 0.f || lefttop.x > p1.x)
					lefttop.x = p1.x;
				if (lefttop.y == 0.f || lefttop.y > p1.y)
					lefttop.y = p1.y;
				if (rightbottom.x == 0.f || rightbottom.x < p1.x)
					rightbottom.x = p1.x;
				if (rightbottom.y == 0.f || rightbottom.y < p1.y)
					rightbottom.y = p1.y;
				if (lefttop.x == 0.f || lefttop.x > c1.x)
					lefttop.x = c1.x;
				if (lefttop.y == 0.f || lefttop.y > c1.y)
					lefttop.y = c1.y;
				if (rightbottom.x == 0.f || rightbottom.x < c1.x)
					rightbottom.x = c1.x;
				if (rightbottom.y == 0.f || rightbottom.y < c1.y)
					rightbottom.y = c1.y;
			}
			previous = current;
			//previousvis = currentvis;
		}
	}
	lefttop.x = lefttop.x - (rightbottom.x - lefttop.x) / 40.f;
	lefttop.y = lefttop.y - (rightbottom.y - lefttop.y) / 10.f;
	rightbottom.x = rightbottom.x + (rightbottom.x - lefttop.x) / 40.f;
	rightbottom.y = rightbottom.y + (rightbottom.y - lefttop.y) / 11.f;
	Rect->x = lefttop.x;
	Rect->y = lefttop.y;
	Rect->w = rightbottom.x - lefttop.x;
	Rect->h = rightbottom.y - lefttop.y;
	return retbool;
}
void GameData::DrawHealth(float x, float y, float w, float h, DWORD Color, float Health, int len, int Kill, ULONG Team, const wchar_t* pName)
{
	float X = x + (w / 2) - 27.f;
	float Y = y - 10;

	AddDrawInfo(3, X, Y, Health / 100.f * 110, 4.f, 0.f, Health > 40 ? ColorInfo.血条填充颜色 : ColorInfo.低血量颜色, NULL, 0, NULL);
	AddDrawInfo(4, X, Y, 110, 4.f, 1.f, ColorInfo.血条框颜色, NULL, 0, NULL);
	if (Team > 100000 || Team == 100000)
	{

		Team = Team - 100000;
	}
	
		wchar_t buffinfo[64];
		swprintf(buffinfo, XorStringW(L"[距离:%dM  队编:%d]"), len, Team);
		AddDrawInfo(5, X, Y - 20, 0, 0, 15.f, Color, 0xFF000000, 0, buffinfo);

		swprintf(buffinfo, XorStringW(L"[杀敌:%d]"), Kill);
		AddDrawInfo(5, X - 20 + 80 + 3, Y - 20 + 5 - 15 - 3, 0, 0, 15.f, Color, 0xFF000000, 0, buffinfo);



		swprintf(buffinfo, XorStringW(L"%s"), pName);
		AddDrawInfo(5, x + (w / 2) - (wcslen(buffinfo) * 6 / 2), y + h, 0, 0, 9, Color, 0xFF0000FF, 0, buffinfo);


		







}
//取骨骼坐标
VOID GameData::GetBoneIndex(ULONG64 Mesh, Vector3* Result, ULONG Id) {

	FTransform Bone = Mem::Ram<FTransform>(Mem::Ram<ULONG64>(Mesh + OffSet::Bone) + Id * 0x30);
	FTransform ComponentToWorld = Mem::Ram<FTransform>(Mesh + OffSet::BoneArry);
	D3DMATRIX2 Matrix;
	Matrix = MatrixMultiplication(Bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
	Result->x = Matrix._41;
	Result->y = Matrix._42;
	Result->z = Matrix._43;

}
FRotator GameData::Vector3ToFRotator(Vector3 v) {

	float RADPI = (float)(180 / M_PI);
	float Yaw = atan2f(v.y, v.x) * RADPI;
	float Pitch = atan2f(v.z, sqrtf((v.x * v.x) + (v.y * v.y))) * RADPI;
	float Roll = 0;
	return FRotator(Pitch, Yaw, Roll);
}
//转换世界坐标
BOOL GameData::WorldToScreen(ULONG64 CameraManager, Vector3 WorldLocation, Vector3* pOut, float* DeltaInMeters) {

	Vector3 Rotation = Mem::Ram<Vector3>(CameraManager + OffSet::CameraRot);
	D3DMATRIX2 tempMatrix = Matrix2(Rotation);//CameraInfo.Rotation
	Vector3 vAxisX, vAxisY, vAxisZ;
	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
	Vector3 Location = Mem::Ram<Vector3>(CameraManager + OffSet::CameraPos);
	Vector3 vDelta = WorldLocation - Location;// CameraInfo.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;
	if (DeltaInMeters != NULL) {
		*DeltaInMeters = vTransformed.z / 100;
	}
	float FovAngle = Mem::Ram<float>(CameraManager + OffSet::CameraFov); //CameraInfo.FOV;//
																 //float ScreenCenterX = GameWindowWidth / 2.0f;
																 //float ScreenCenterY = GameWindowHeight / 2.0f;


	pOut->x = ScreenCenterX + vTransformed.x * ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f) / vTransformed.z;
	pOut->y = ScreenCenterY - vTransformed.y * ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f) / vTransformed.z;
	pOut->z = 0;

	if (pOut->x < 0) {
		pOut->x = 0;
	}
	if (pOut->y < 0) {
		pOut->y = 0;
	}
	if (pOut->x > 0 && pOut->y > 0) {
		if (pOut->x <= ScreenCenterX * 2.0f && pOut->y <= ScreenCenterY * 2.0f) {
			return TRUE;
		}
	}

	return FALSE;
}
//转换世界坐标
BOOL GameData::WorldToScreen2(ULONG64 CameraManager, Vector3 WorldLocation, Vector3* pOut, float* DeltaInMeters, Vector3 Breath) {

	Vector3 Rotation = Mem::Ram<Vector3>(CameraManager + OffSet::CameraRot);
	D3DMATRIX2 tempMatrix = Matrix2(Rotation);//CameraInfo.Rotation
	Vector3 vAxisX, vAxisY, vAxisZ;
	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	if (Breath.x != 0 || Breath.y != 0 || Breath.y != 0)
	{
		tempMatrix = Matrix2(Breath);//CameraInfo.Rotation
		vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
	}

	Vector3 Location = Mem::Ram<Vector3>(CameraManager + OffSet::CameraPos);
	Vector3 vDelta = WorldLocation - Location;// CameraInfo.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
	//Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY2), vDelta.Dot(vAxisZ2), vDelta.Dot(vAxisX2));
	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;
	if (DeltaInMeters != NULL) {
		*DeltaInMeters = vTransformed.z / 100;
	}
	float FovAngle = Mem::Ram<float>(CameraManager + OffSet::CameraFov); //CameraInfo.FOV;//
																 //float ScreenCenterX = GameWindowWidth / 2.0f;
																 //float ScreenCenterY = GameWindowHeight / 2.0f;
																 //vTransformed.x += Breath.x;
																 //vTransformed.y += Breath.y;
																 //vTransformed.z += Breath.z;

	pOut->x = ScreenCenterX + vTransformed.x * ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f) / vTransformed.z;
	pOut->y = ScreenCenterY - vTransformed.y * ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f) / vTransformed.z;
	pOut->z = 0;

	if (pOut->x < 0) {
		pOut->x = 0;
	}
	if (pOut->y < 0) {
		pOut->y = 0;
	}
	if (pOut->x > 0 && pOut->y > 0) {
		if (pOut->x <= ScreenCenterX * 2.0f && pOut->y <= ScreenCenterY * 2.0f) {
			return TRUE;
		}
	}

	return FALSE;
}
Vector3 GameData::CalcAngle(Vector3 src, Vector3 dst)
{
	Vector3 delta = dst - src;
	float yaw = atan2(delta.y, delta.x) * 180.f / M_PI;
	float pitch = -((acos(delta.z / GetDistance(src, dst)) * 180.f / M_PI) - 90.f);
	return Vector3(pitch, yaw, 0.f);
}
float GameData::GetDistance(Vector3 point1, Vector3 point2) {
	Vector3 heading = point2 - point1;
	float distanceSquared;
	float distance;
	distanceSquared = heading.x * heading.x + heading.y * heading.y + heading.z * heading.z;
	distance = sqrt(distanceSquared);
	return distance;
}

预判数据 GameData::取预判初始数据(char* 参_武器名称) {
	预判数据 局_预判数据;
	设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 0);
	if (参_武器名称 != NULL)
	{
		if (strcmp(XorString("WeapAK47_C"), 参_武器名称) == 0)//248053
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 715);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapQBZ95_C"), 参_武器名称) == 0)//248082
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 870);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapKar98k_C"), 参_武器名称) == 0)//248069
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 760);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapM24_C"), 参_武器名称) == 0)//248072
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 790);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapSKS_C"), 参_武器名称) == 0)//248087
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 800);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapSCAR-L_C"), 参_武器名称) == 0)//248086
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 870);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapHK416_C"), 参_武器名称) == 0) //248067
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 880);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapM16A4_C"), 参_武器名称) == 0)//248070
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 900);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapAWM_C"), 参_武器名称) == 0)//248055
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 945);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapMini14_C"), 参_武器名称) == 0)//248075
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 990);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapGroza_C"), 参_武器名称) == 0)//248066
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 715);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapMk14_C"), 参_武器名称) == 0)
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 853);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapM249_C"), 参_武器名称) == 0)
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 915);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapMk47Mutant_C"), 参_武器名称) == 0)
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 780);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapBerylM762_C"), 参_武器名称) == 0) //248057
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 715);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapAUG_C"), 参_武器名称) == 0)//248054
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 940);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapQBU88_C"), 参_武器名称) == 0)//248081
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 945);
			goto _RetOut;
		}
		if (strcmp(XorString("WeapFNFal_C"), 参_武器名称) == 0)//248063
		{
			设置预判数据(&局_预判数据, 0, 6, 12, 15, 25, 30, 100, 200, 300, 400, 500, 600, 840);
			goto _RetOut;
		}
	}
_RetOut:
	return 局_预判数据;

}
void GameData::设置预判数据(预判数据* 参_预判数据, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, int v9, int v10, int v11, int v12, int v13) {
	参_预判数据->抬枪量1 = v1;
	参_预判数据->抬枪量2 = v2;
	参_预判数据->抬枪量3 = v3;
	参_预判数据->抬枪量4 = v4;
	参_预判数据->抬枪量5 = v5;
	参_预判数据->抬枪量6 = v6;

	参_预判数据->距离1 = v7;
	参_预判数据->距离2 = v8;
	参_预判数据->距离3 = v9;
	参_预判数据->距离4 = v10;
	参_预判数据->距离6 = v11;
	参_预判数据->距离6 = v12;

	参_预判数据->子弹速度 = v13;
}
Vector3 GameData::取预判坐标(Vector3 参_对象坐标, float 参_对象距离, Vector3 参_对象速度, float 参_重力, 预判数据 参_预判数据, float mgravity)
{
	float 局_子弹飞行时间 = 0, 局_临时变量 = 0;
	int 局_抬枪量 = 0;
	Vector3 局_预判坐标;
	if (参_对象距离 <= 参_预判数据.距离1) {
		局_抬枪量 = 参_预判数据.抬枪量1;
	}
	else if (参_对象距离 <= 参_预判数据.距离2) {
		局_抬枪量 = 参_预判数据.抬枪量2;
	}
	else if (参_对象距离 <= 参_预判数据.距离3) {
		局_抬枪量 = 参_预判数据.抬枪量3;
	}
	else if (参_对象距离 <= 参_预判数据.距离4) {
		局_抬枪量 = 参_预判数据.抬枪量4;
	}
	else if (参_对象距离 <= 参_预判数据.距离5) {
		局_抬枪量 = 参_预判数据.抬枪量5;
	}
	else if (参_对象距离 <= 参_预判数据.距离6) {
		局_抬枪量 = 参_预判数据.抬枪量6;
	}
	else {
		局_抬枪量 = 30;
	}
	局_子弹飞行时间 = 参_对象距离 / 参_预判数据.子弹速度;
	局_子弹飞行时间 = 局_子弹飞行时间 * 1.33;
	局_预判坐标.x = 参_对象坐标.x + 参_对象速度.x * 局_子弹飞行时间;
	局_预判坐标.y = 参_对象坐标.y + 参_对象速度.y * 局_子弹飞行时间;

	float gravity = (参_对象距离 * mgravity);
	局_预判坐标.z = 参_对象坐标.z + (0.5 * gravity * powf(局_子弹飞行时间, 2));

	return 局_预判坐标;
}
VOID GameData::初始雷达参数()
{
	//全_雷达中心x = ScreenCenterX * 2.f - 500.f;
	//全_雷达中心x = ScreenCenterX * 2.f * 0.75f;
	全_雷达中心x = ScreenCenterX * 0.5f;

	全_雷达中心y = ScreenCenterY * 2.f - 170.f;

	全_雷达半径 = 130;
	集_地图比例 = 全_雷达半径 / 20000.f;

}

BOOL GameData::雷达坐标转换(float 参_方向, float 参_敌人坐标x, float 参_敌人坐标y, float* 参_返回坐标x, float* 参_返回坐标y)
{
	float 局_临时半径 = 全_雷达半径 - 4;
	Vector3 局_相对坐标, 局_目标坐标, 局_地图中心;
	局_地图中心 = Vector3(全_雷达中心x, 全_雷达中心y, 0.f);
	局_相对坐标.x = 参_敌人坐标x - 集_自身坐标x;
	局_相对坐标.y = 参_敌人坐标y - 集_自身坐标y;
	局_目标坐标.x = 局_地图中心.x + 局_相对坐标.x * 集_地图比例;
	局_目标坐标.y = 局_地图中心.y + 局_相对坐标.y * 集_地图比例;
	局_目标坐标.x = 局_目标坐标.x - 局_地图中心.x;
	局_目标坐标.y = 局_目标坐标.y - 局_地图中心.y;
	if (参_方向 < 0) {
		参_方向 = 270.f - 参_方向 + 180.f;
	}
	else {
		参_方向 = 270.f - 参_方向 - 180.f;
	}
	局_目标坐标 = 旋转(局_地图中心, 局_目标坐标, 参_方向);
	if (局_目标坐标.x < 全_雷达中心x - 局_临时半径) {
		局_目标坐标.x = 全_雷达中心x - 局_临时半径;
	}
	if (局_目标坐标.x > 全_雷达中心x + 局_临时半径) {
		局_目标坐标.x = 全_雷达中心x + 局_临时半径;
	}
	if (局_目标坐标.y < 全_雷达中心y - 局_临时半径) {
		局_目标坐标.y = 全_雷达中心y - 局_临时半径;
	}
	if (局_目标坐标.y > 全_雷达中心y + 局_临时半径) {
		局_目标坐标.y = 全_雷达中心y + 局_临时半径;
	}
	*参_返回坐标x = 局_目标坐标.x;
	*参_返回坐标y = 局_目标坐标.y;
	return true;
}

VOID GameData::设置雷达坐标(float 参_自身坐标x, float 参_自身坐标y)
{
	集_自身坐标x = 参_自身坐标x;
	集_自身坐标y = 参_自身坐标y;
}

Vector3 GameData::旋转(Vector3 参_圆心, Vector3 参_坐标, float 参_角度)
{
	Vector3 局_返回坐标;
	float 局_临时 = 参_角度 * (float)M_PI / 180;
	局_返回坐标.x = 参_圆心.x - (参_坐标.x * cosf(局_临时) - 参_坐标.y * sinf(局_临时));
	局_返回坐标.y = 参_圆心.y - (参_坐标.x * sinf(局_临时) + 参_坐标.y * cosf(局_临时));
	return 局_返回坐标;
}

Vector3 GameData::求圆角度坐标(Vector3 参_中心, int 参_半径, int 参_角度)
{
	Vector3 局_返回坐标;
	局_返回坐标.x = 参_中心.x + 参_半径 * cosf(参_角度 * M_PI / 180);
	局_返回坐标.y = 参_中心.y + 参_半径 * sinf(参_角度 * M_PI / 180);
	return 局_返回坐标;
}

VOID GameData::刷新雷达() 
{

	Vector3 局_临时坐标;//雷达要不要   要   呆呆那份圆形的 你有吗一会你看看吧
	float FovAngle = Mem::Ram<float>(g_Camera + OffSet::CameraFov);
	AddDrawInfo(3, 全_雷达中心x - 全_雷达半径, 全_雷达中心y - 全_雷达半径, 全_雷达半径 * 2, 全_雷达半径 * 2, 1, 0x64000000, 0, 0, NULL);
	AddDrawInfo(7, 全_雷达中心x, 全_雷达中心y, 130, 3.f, 1, 0xFFFFFFFF, 0, 0, NULL);
	AddDrawInfo(7, 全_雷达中心x, 全_雷达中心y, 100, 3.f, 1, 0xFFFFFFFF, 0, 0, NULL);
	AddDrawInfo(7, 全_雷达中心x, 全_雷达中心y, 70, 3.f, 1, 0xFFFFFFFF, 0, 0, NULL);
	AddDrawInfo(7, 全_雷达中心x, 全_雷达中心y, 40, 3.f, 1, 0xFFFFFFFF, 0, 0, NULL);
	AddDrawInfo(4, 全_雷达中心x - 全_雷达半径, 全_雷达中心y - 全_雷达半径, 全_雷达半径 * 2, 全_雷达半径 * 2, 1, 0x000000, 0, 0, NULL);
	AddDrawInfo(2, 全_雷达中心x - 全_雷达半径, 全_雷达中心y, 全_雷达中心x + 全_雷达半径, 全_雷达中心y, 1, SwitchColor(0xFFFFFFFF, 255), 0, 0, NULL);
	AddDrawInfo(2, 全_雷达中心x, 全_雷达中心y - 全_雷达半径, 全_雷达中心x, 全_雷达中心y + 全_雷达半径, 1, SwitchColor(0xFFFFFFFF, 255), 0, 0, NULL);
	局_临时坐标 = 求圆角度坐标(Vector3(全_雷达中心x, 全_雷达中心y, 0.f), 全_雷达半径, FovAngle / 1.2 - 90);
	AddDrawInfo(2, 全_雷达中心x, 全_雷达中心y, 局_临时坐标.x, 局_临时坐标.y, 1, SwitchColor(0xFFFF80FF, 255), 0, 0, NULL);
	局_临时坐标 = 求圆角度坐标(Vector3(全_雷达中心x, 全_雷达中心y, 0.f), 全_雷达半径, 270 - FovAngle / 1.2);
	AddDrawInfo(2, 全_雷达中心x, 全_雷达中心y, 局_临时坐标.x, 局_临时坐标.y, 1, SwitchColor(0xFFFF80FF, 255), 0, 0, NULL);
	/*AddDrawInfo(3, 全_雷达中心x - 全_雷达半径 + 1, 全_雷达中心y - 全_雷达半径 + 1, 全_雷达半径 * 2 - 2, 全_雷达半径 * 2 - 2, 1, 0x64000000, 0, 0, NULL);
	AddDrawInfo(7, 全_雷达中心x, 全_雷达中心y , 全_雷达半径 * 1.2, NULL, 2, 0xFFFFFFFF, 0, 0, NULL);*/


}
char* GameData::GetUNames(ULONG ObjId)
{
	auto gnames = Dec_Games1(Mem::Ram<ULONG_PTR>(TslGameBase + OffSet::GNames - 0x20));
	gnames = Dec_Games2(Mem::Ram<ULONG_PTR>(gnames));
	if (gnames > 0)
	{
		ULONG IdDiv = ObjId / OffSet::NameCont;
		ULONG Idtemp = ObjId % OffSet::NameCont;
		ULONG64 Serial = Mem::Ram<ULONG_PTR>(gnames + IdDiv * 0x8);
		if (Serial > 0)
		{
			ULONG64 pName = Mem::Ram<ULONG_PTR>(Serial + 0x8 * Idtemp);
			if (pName > 0) {
				/*if (Mem::Asm_IsReadPtr((char*)(pName + 0x10), 64) == 0)
				{*/
					return (char*)(pName + 0x10);
			//	}
			}
		}
	}
	return nullptr;
}
//判断ID是否在缓存中
BOOL GameData::IsObjectId(ULONG id, ObjectIdInfo* ObjIdInfo)
{

	for (int i = 0; i < ObjeId.Count; i++)
	{
		if (ObjeId.info[i].ObjId == id)
		{
			//*ObjIdInfo = (ObjectIdInfo*)((ULONG64)ObjeId.info + sizeof(ObjectIdInfo) * i);
			ObjIdInfo->Type = ObjeId.info[i].Type;
			ObjIdInfo->ObjId = ObjeId.info[i].ObjId;
			ObjIdInfo->Color = ObjeId.info[i].Color;
			ObjIdInfo->imageid = ObjeId.info[i].imageid;
			swprintf(ObjIdInfo->Alias, 64, XorStringW(L"%s"), ObjeId.info[i].Alias);
			return TRUE;
		}
	}
	return FALSE;
}
//添加绘制信息
VOID GameData::AddDrawInfo(UINT Type, float nX, float nY, float cX, float cY, float xW, DWORD Color, DWORD iColor, ULONG_PTR imageid, const wchar_t* wlpText) {

	DrawInfo.info[DrawInfo.Count].Type = Type;
	DrawInfo.info[DrawInfo.Count].nX = nX;
	DrawInfo.info[DrawInfo.Count].nY = nY;
	DrawInfo.info[DrawInfo.Count].cX = cX;
	DrawInfo.info[DrawInfo.Count].cY = cY;
	DrawInfo.info[DrawInfo.Count].xW = xW;
	DrawInfo.info[DrawInfo.Count].Color = Color;
	DrawInfo.info[DrawInfo.Count].iColor = iColor;
	DrawInfo.info[DrawInfo.Count].imageid = imageid;
	if (wlpText != NULL)
	{
		swprintf(DrawInfo.info[DrawInfo.Count].Text, 128, XorStringW(L"%s"), wlpText);
	}
	DrawInfo.Count++;
}
int GameData::EnumObgectNames()
{
	
	srand(GetTickCount());

	//初始化CRC
	//Xenuine::CrcClear(TslGameBase + OffSet::XeCrc);
	//Xenuine::AddCrcPassAddress(TslGameBase + OffSet::XeCrc, TslGameBase + OffSet::XeCrc + 13);	//0x2614EE0
	//Xenuine::AddCrcPassAddress(GameData::TslGameBase + 0x343266C, GameData::TslGameBase + 0x343266C + 4);//WU + 0x370
	//Xenuine::AddCrcPassAddress(GameData::TslGameBase + WU + 0x370, GameData::TslGameBase + WU + 0x370 + 5);
	


	ColorInfo.玩家可视颜色 = 0xFF0000FF;
	ColorInfo.玩家不可视颜色 = 0xFFFFFFFF;
	ColorInfo.倒地玩家颜色 = 0xFFFFA8FF;
	ColorInfo.信息颜色 = 0xFFFFFFFF;
	ColorInfo.信息颜色不可视颜色 = 0xFF00FF00;
	ColorInfo.血条框颜色 = 0xFF000000;
	ColorInfo.血条填充颜色 = 0xFF0080FF;
	ColorInfo.低血量颜色 = 0xFF0000FF;
	ColorInfo.雷达颜色 = 0xFF0000FF;
	ColorInfo.雷达不可视颜色 = 0xFF00FF00;

	ObjeId.Count = 0;
	auto gnames = GameData::Dec_Games1(Mem::Ram<ULONG_PTR>(TslGameBase + OffSet::GNames - 0x20)); //是注入崩溃？不是 玩会游戏崩溃
	gnames = GameData::Dec_Games2(Mem::Ram<ULONG_PTR>(gnames));
	for (int i = 0; i < 30; i++) 
	{
		ULONG64 chunk = Mem::Ram<ULONG64>(gnames + i * 8); if (chunk <= 0) { continue; }
		for (int x = 0; x < OffSet::NameCont; x++) {
			ULONG64 fName = Mem::Ram<ULONG64>(chunk + x * 8);
			if (fName > 0) {
				/*if (Mem::Asm_IsReadPtr((char*)fName + 0x10, 64) == 0)
				{*/
					if (strcmp(XorString("PlayerMale_A"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 1;
						ObjeId.info[ObjeId.Count].Color = 0xFFfffffe;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorString("Male"));
						ObjeId.Count++;
						continue;

					}
					if (strcmp(XorString("PlayerMale_A_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 1;
						ObjeId.info[ObjeId.Count].Color = 0xFFfffffe;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,L"%s", XorString("Male"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("PlayerFemale_A"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 2;
						ObjeId.info[ObjeId.Count].Color = 0xFFfffffe;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorString("Female"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("PlayerFemale_A_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 2;
						ObjeId.info[ObjeId.Count].Color = 0xFFfffffe;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorString("Female"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Uaz_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("Uaz_A_01"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Uaz_A_01_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("Uaz_B_01"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Uaz_B_01_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("Uaz_C_01"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Uaz_C_01_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"吉普"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Dacia_A_01"), (char*)fName + 0x10) == 0 || strcmp(XorString("Dacia_A_01_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Dacia_A_02"), (char*)fName + 0x10) == 0 || strcmp(XorString("Dacia_A_02_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Dacia_A_03"), (char*)fName + 0x10) == 0 || strcmp(XorString("Dacia_A_03_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Dacia_A_04"), (char*)fName + 0x10) == 0 || strcmp(XorString("Dacia_A_04_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Dacia_A_01_v2"), (char*)fName + 0x10) == 0 || strcmp(XorString("Dacia_A_03_v2_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Dacia_A_04_v2"), (char*)fName + 0x10) == 0 || strcmp(XorString("Dacia_A_04_v2_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"轿车"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("ABP_Motorbike_03"), (char*)fName + 0x10) == 0 || strcmp(XorString("ABP_Motorbike_03_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("ABP_Motorbike_04"), (char*)fName + 0x10) == 0 || strcmp(XorString("ABP_Motorbike_04_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("ABP_Motorbike_04_Sidecar"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Motorbike_03_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_Motorbike_04"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Motorbike_04_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_Motorbike_04_Desert"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Motorbike_04_Desert_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_Motorbike_04_SideCar_Desert"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Motorbike_04_SideCar_Desert_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"摩托"));
						ObjeId.Count++;
						continue;
					}				
					if (strcmp(XorString("BP_Niva_01_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Niva_02_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Niva_03_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Niva_04_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_Niva_05_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Niva_06_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"雪地越野"));//
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Buggy_A_01"), (char*)fName + 0x10) == 0 || strcmp(XorString("Buggy_A_01_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Buggy_A_02"), (char*)fName + 0x10) == 0 || strcmp(XorString("Buggy_A_02_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Buggy_A_03"), (char*)fName + 0x10) == 0 || strcmp(XorString("Buggy_A_03_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Buggy_A_04"), (char*)fName + 0x10) == 0 || strcmp(XorString("Buggy_A_04_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Buggy_A_05"), (char*)fName + 0x10) == 0 || strcmp(XorString("Buggy_A_05_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("Buggy_A_06"), (char*)fName + 0x10) == 0 || strcmp(XorString("Buggy_A_06_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"山蹦子"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Boat_PG117_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("PG117_A_01_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"船"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("BP_PickupTruck_A_01_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_PickupTruck_A_02_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_PickupTruck_A_03_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_PickupTruck_A_04_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_PickupTruck_A_05_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"越野"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("BP_PickupTruck_B_01_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_PickupTruck_B_02_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_PickupTruck_B_03_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_PickupTruck_B_04_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"皮卡"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("AquaRail_A_01_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("AquaRail_A_01"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("AquaRail_C"), (char*)fName + 0x10) == 0 || strcmp(XorString(""), (char*)fName + 0x10) == 0 ||
						strcmp(XorString(""), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"摩托艇"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("BP_Van_A_01"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Van_A_01_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_Van_A_02"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Van_A_02_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_Van_A_03"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Van_A_03_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString(""), (char*)fName + 0x10) == 0 || strcmp(XorString(""), (char*)fName + 0x10) == 0 ||
						strcmp(XorString(""), (char*)fName + 0x10) == 0 || strcmp(XorString(""), (char*)fName + 0x10) == 0 ||
						strcmp(XorString(""), (char*)fName + 0x10) == 0 || strcmp(XorString(""), (char*)fName + 0x10) == 0 ||
						strcmp(XorString(""), (char*)fName + 0x10) == 0 || strcmp(XorString(""), (char*)fName + 0x10) == 0 ||
						strcmp(XorString(""), (char*)fName + 0x10) == 0 || strcmp(XorString(""), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"小巴车"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("BP_Mirado_Open_03_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Mirado_A_02_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_Mirado_Open_04_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_M_Rony_A_01_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"跑车"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("BP_M_Rony_A_01_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_M_Rony_A_02_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_M_Rony_A_03_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"小货车"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("BP_Scooter_01_A_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Scooter_02_A_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_Scooter_03_A_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Scooter_04_A_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"小摩托"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("BP_TukTukTuk_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_TukTukTuk_A_01_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_TukTukTuk_A_02_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_TukTukTuk_A_03_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"三轮车"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("BP_Snowmobile_01_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("BP_Snowmobile_02_C"), (char*)fName + 0x10) == 0 ||
						strcmp(XorString("BP_Snowmobile_03_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"雪地摩托"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("BP_Motorglider_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"滑翔机"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("RedZoneBomb_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"轰炸点"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Carapackage_RedBox_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 4;
						ObjeId.info[ObjeId.Count].Color = 0xFFFF0090;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"空投"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("DeathDropItemPackage_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 5;
						ObjeId.info[ObjeId.Count].Color = 0xFFFF0090;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"骨灰盒"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("DroppedItemGroup"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 6;
						ObjeId.info[ObjeId.Count].Color = 0xFFfffffe;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"Item"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Heal_FirstAid_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 7;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FF00;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"急救包"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Heal_MedKit_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 7;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FF00;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"医疗箱"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Boost_EnergyDrink_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 7;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FF00;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"能量饮料"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Boost_PainKiller_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 7;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FF00;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"止痛药"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Boost_AdrenalineSyringe_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FF00;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"肾上腺素"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_FlareGun_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 8;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"信号枪"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_Pan_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 8;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"平底锅"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_Grenade_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 8;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"手雷"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Weapon_StickyGrenade_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 8;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"炸弹"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_JerryCan_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 8;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"汽油桶"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Armor_D_01_Lv2_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 8;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFF00;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"二级甲"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Armor_C_01_Lv3_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 8;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"三级甲"));
						ObjeId.Count++;
					}
					if (strcmp(XorString("Item_Head_F_02_Lv2_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("Item_Head_F_01_Lv2_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 8;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFF00;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"二级头"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Head_G_01_Lv3_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 8;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"三级头"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Back_F_01_Lv2_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("Item_Back_F_02_Lv2_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 8;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFFF00;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"二级包"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Back_C_01_Lv3_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("Item_Back_C_02_Lv3_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 8;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"三级包"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_M24_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 9;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"M24"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_SKS_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 9;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"SKS"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_Kar98k_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 9;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"Kar98k"));//Item_Weapon_Mosin_C
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_Mosin_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 9;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"莫辛纳甘步枪"));//Item_Weapon_Mosin_C
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_Mini14_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 9;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"Mini14"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_FNFal_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 9;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"FNFal"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_AWM_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 9;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"AWM"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_Mk14_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 9;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"Mk14"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_AK47_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"AKM"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_HK416_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("Item_Weapon_HK416"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"M416"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_M16A4_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"M16A4"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_SCAR-L_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"SCAR-L"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_QBU88_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"QBU"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_Mk47Mutant_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"Mk47"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_BerylM762_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"M762"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_G36C_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"G36C"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_Groza_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"Groza"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_AUG_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"AUG"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_M249_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"M249"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_DP28_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"DP28"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Weapon_QBZ95_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0080FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"QBZ"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Ghillie_01_C"), (char*)fName + 0x10) == 0 || strcmp(XorString("Item_Ghillie_02_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 10;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"吉利服"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Large_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFA8FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"步枪快扩"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_SniperRifle_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFA8FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"狙击快扩"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Muzzle_Suppressor_Large_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"步枪消音"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Muzzle_Suppressor_SniperRifle_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFF0000FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"狙击消音"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Magazine_Extended_Large_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFA8FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"步枪扩容"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Magazine_Extended_SniperRifle_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFA8FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"狙击扩容"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Muzzle_Compensator_Large_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFA8FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"步枪补偿"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Stock_SniperRifle_CheekPad_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFA8FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"托腮板"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Lower_Foregrip_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFA8FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"垂直握把"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Upper_DotSight_01_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFA8FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"红点"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Upper_Holosight_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFFFFA8FF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"全息"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Upper_Scope3x_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"3倍镜"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Upper_ACOG_01_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"4倍镜"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Upper_Scope6x_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"6倍镜"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Upper_CQBSS_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"8倍镜"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("Item_Attach_Weapon_Upper_PM2_01_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 11;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"15倍镜"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("ProjGrenade_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"手雷"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("ProjFlashBang_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias,  L"%s", XorStringW(L"闪光"));
						ObjeId.Count++;
						continue;
					}
					if (strcmp(XorString("ProjMolotov_C"), (char*)fName + 0x10) == 0) {
						ObjeId.info[ObjeId.Count].Type = 3;
						ObjeId.info[ObjeId.Count].Color = 0xFF00FFFF;
						ObjeId.info[ObjeId.Count].ObjId = x + OffSet::NameCont * i;
						swprintf(ObjeId.info[ObjeId.Count].Alias, L"%s", XorStringW(L"燃烧瓶"));
						ObjeId.Count++;
						continue;
					}
				//}
			}
		}
	}
	return ObjeId.Count;
}
//计算距离
float GameData::CalculateAngle(float x1, float y1, float x2, float y2) {
	float cx, cy;
	cx = x1 - x2;
	cy = y1 - y2;
	return sqrtf(cx * cx + cy * cy);;
}
D3DMATRIX2 GameData::Matrix2(Vector3 rot, Vector3 origin) {

	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX2 matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

D3DMATRIX2 GameData::MatrixMultiplication(D3DMATRIX2 pM1, D3DMATRIX2 pM2) {

	D3DMATRIX2 pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}




