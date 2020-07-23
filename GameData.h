#pragma once
#include <iostream>
#include <xstring>
using namespace std;
#define M_PI	3.14159265358979323846264338327950288419716939937510

#define D3DCOLOR_ARGB(a,r,g,b) \
    ((DWORD)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define ServerSetControlRotationCallAddr 0x24DCF70
#define SwitchColor(Color,alpha)(D3DCOLOR_ARGB(alpha,(Color >> 16) & 0xFF,(Color >> 8) & 0xFF,Color & 0xFF))
//typedef void(__fastcall* ServerSetControlRotation_t)(ULONG64 PlayerControll, struct Vector3 Rotation);
//ServerSetControlRotation_t Moe_ServerSetControlRotation = (ServerSetControlRotation_t)((uintptr_t)GetModuleHandleA(NULL) + ServerSetControlRotationCallAddr);
int AimBot_API(int 瞄准X, int 瞄准Y);

typedef struct _D3DMATRIX2 {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float m[4][4];
	};
} D3DMATRIX2;

class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	float x;
	float y;
	float z;

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}
	inline float Length()
	{
		return sqrtf(x * x + y * y + z * z);
	}
	inline Vector3& operator+=(const Vector3& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	inline Vector3& operator-=(const Vector3& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	inline Vector3& operator*=(const Vector3& v) {
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	inline Vector3& operator/=(const Vector3& v) {
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	inline Vector3& operator+=(float v) {
		x += v; y += v; z += v; return *this;
	}

	inline Vector3& operator-=(float v) {
		x -= v; y -= v; z -= v; return *this;
	}

	inline Vector3& operator*=(float v) {
		x *= v; y *= v; z *= v; return *this;
	}

	inline Vector3& operator/=(float v) {
		x /= v; y /= v; z /= v; return *this;
	}

	inline Vector3 operator-() const {
		return Vector3(-x, -y, -z);
	}

	inline Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	inline Vector3 operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline Vector3 operator*(const Vector3& v) const {
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	inline Vector3 operator/(const Vector3& v) const {
		return Vector3(x / v.x, y / v.y, z / v.z);
	}

	inline Vector3 operator+(float v) const {
		return Vector3(x + v, y + v, z + v);
	}

	inline Vector3 operator-(float v) const {
		return Vector3(x - v, y - v, z - v);
	}

	inline Vector3 operator*(float v) const {
		return Vector3(x * v, y * v, z * v);
	}

	inline Vector3 operator/(float v) const {
		return Vector3(x / v, y / v, z / v);
	}
};

class Vector4
{
public:
	Vector4() : x(0.f), y(0.f), w(0.f), h(0.f)
	{

	}

	Vector4(float _x, float _y, float _w, float _h) : x(_x), y(_y), w(_w), h(_h)
	{

	}
	~Vector4()
	{

	}

	float x;
	float y;
	float w;
	float h;

	inline float Dot(Vector4 v)
	{
		return x * v.x + y * v.y + w * v.w + h * v.h;
	}

	inline float Distance(Vector4 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.w - w, 2.0) + powf(v.h - h, 2.0)));
	}
	inline float Length()
	{
		return sqrtf(x * x + y * y + w * w + h * h);
	}
	Vector4 operator+(Vector4 v)
	{
		return Vector4(x + v.x, y + v.y, w + v.w, h + v.h);
	}

	Vector4 operator-(Vector4 v)
	{
		return Vector4(x - v.x, y - v.y, w - v.w, h - v.h);
	}
};
class FRotator
{
public:
	FRotator() :Pitch(0.f), Yaw(0.f), Roll(0.f) {

	}
	FRotator(float _Pitch, float _Yaw, float _Roll) : Pitch(_Pitch), Yaw(_Yaw), Roll(_Roll)
	{

	}
	~FRotator()
	{

	}
	float Pitch;
	float Yaw;
	float Roll;
	inline FRotator Clamp() {

		if (Pitch > 180)
		{
			Pitch -= 360;
		}
		else
		{
			if (Pitch < -180)
			{
				Pitch += 360;
			}
		}
		if (Yaw > 180)
		{
			Yaw -= 360;
		}
		else {
			if (Yaw < -180)
			{
				Yaw += 360;
			}
		}
		if (Pitch > 89)
		{
			Pitch = 89;
		}
		if (Pitch < -89)
		{
			Pitch = -89;
		}
		while (Yaw < 180)
		{
			Yaw += 360;
		}
		while (Yaw > 180)
		{
			Yaw -= 360;
		}
		Roll = 0;
		return FRotator(Pitch, Yaw, Roll);
	}
	inline float Length()
	{
		return sqrtf(Pitch * Pitch + Yaw * Yaw + Roll * Roll);
	}
	FRotator operator+(FRotator v) {
		return FRotator(Pitch + v.Pitch, Yaw + v.Yaw, Roll + v.Roll);
	}
	FRotator operator-(FRotator v) {
		return FRotator(Pitch - v.Pitch, Yaw - v.Yaw, Roll - v.Roll);
	}
};

struct FWeaponTrajectoryConfig
{
	float                                              InitialSpeed;
	unsigned long long								   BallisticCurve;
	float                                              RangeModifier;
	float                                              ReferenceDistance;
	float                                              TravelDistanceMax;
	float                                              SimulationSubstepTime;
	float                                              VDragCoefficient;
	float                                              BDS;
};

struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};

struct FTransform
{
	FQuat rot;
	Vector3 translation;
	char pad[4];
	Vector3 scale;
	char pad1[4];
	D3DMATRIX2 ToMatrixWithScale()
	{
		D3DMATRIX2 m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};
// Enum Engine.ETraceTypeQuery
enum ETraceTypeQuery
{
	TraceTypeQuery1 = 0,
	TraceTypeQuery2 = 1,
	TraceTypeQuery3 = 2,
	TraceTypeQuery4 = 3,
	TraceTypeQuery5 = 4,
	TraceTypeQuery6 = 5,
	TraceTypeQuery7 = 6,
	TraceTypeQuery8 = 7,
	TraceTypeQuery9 = 8,
	TraceTypeQuery10 = 9,
	TraceTypeQuery11 = 10,
	TraceTypeQuery12 = 11,
	TraceTypeQuery13 = 12,
	TraceTypeQuery14 = 13,
	TraceTypeQuery15 = 14,
	TraceTypeQuery16 = 15,
	TraceTypeQuery17 = 16,
	TraceTypeQuery18 = 17,
	TraceTypeQuery19 = 18,
	TraceTypeQuery20 = 19,
	TraceTypeQuery21 = 20,
	TraceTypeQuery22 = 21,
	TraceTypeQuery23 = 22,
	TraceTypeQuery24 = 23,
	TraceTypeQuery25 = 24,
	TraceTypeQuery26 = 25,
	TraceTypeQuery27 = 26,
	TraceTypeQuery28 = 27,
	TraceTypeQuery29 = 28,
	TraceTypeQuery30 = 29,
	TraceTypeQuery31 = 30,
	TraceTypeQuery32 = 31,
	TraceTypeQuery_MAX = 32,
	ETraceTypeQuery_MAX = 33
};

// 我搞完了给你发来 你直接填里面 
//设置大小参数



//贴图 设置纹理









//贴图

// Enum Engine.EDrawDebugTrace
enum EDrawDebugTrace
{
	EDrawDebugTrace__None = 0,
	EDrawDebugTrace__ForOneFrame = 1,
	EDrawDebugTrace__ForDuration = 2,
	EDrawDebugTrace__Persistent = 3,
	EDrawDebugTrace__EDrawDebugTrace_MAX = 4
};
struct FHitResult
{
	unsigned char                                      _0x000000[0x88];                                   		// 0x000000 (0x0088)
};
typedef struct _ObjectIdInfo
{
	ULONG Type;				//类型
	ULONG ObjId;			//对象ID
	DWORD Color;			//颜色
	ULONG_PTR imageid;			//图片ID


	wchar_t Alias[64];			//别名
}ObjectIdInfo;

typedef struct _DrawInformation {
	UINT Type;
	float nX;
	float nY;
	float cX;
	float cY;
	float xW;
	DWORD Color;
	DWORD iColor;
	ULONG_PTR imageid;			//图片ID

	wchar_t Text[128];
}DrawInformation;
typedef struct DrawIndex
{
	int Count;
	DrawInformation info[2000];
};

typedef struct ObjIdInfo
{
	int Count;
	ObjectIdInfo info[500];
};
typedef struct 绘制颜色结构 {
	DWORD 玩家可视颜色;
	DWORD 玩家不可视颜色;
	DWORD 倒地玩家颜色;
	DWORD 信息颜色;
	DWORD 信息颜色不可视颜色;
	DWORD 血条框颜色;
	DWORD 血条填充颜色;
	DWORD 低血量颜色;
	DWORD 雷达颜色;
	DWORD 雷达不可视颜色;
}绘制颜色结构;
typedef struct StringA
{
	char buffer[64];
};
struct 预判数据
{
	int 抬枪量1;
	int 抬枪量2;
	int 抬枪量3;
	int 抬枪量4;
	int 抬枪量5;
	int 抬枪量6;
	int 距离1;
	int 距离2;
	int 距离3;
	int 距离4;
	int 距离5;
	int 距离6;
	int 子弹速度;
};


EXTERN_C BYTE Aimbot_sw;
EXTERN_C FLOAT Aimbot_x;
EXTERN_C FLOAT Aimbot_y;
EXTERN_C FLOAT Aimbot_z;
EXTERN_C ULONG_PTR HookSilenceAimBotReturn;
EXTERN_C ULONG_PTR HookTurnBulletReturn;
EXTERN_C  ULONG_PTR HookAtanfReturn;
EXTERN_C  ULONG_PTR JmpAtanfAddress;
EXTERN_C void SilenceAimBot2();


namespace GameData {
	extern void* SpoofBytes;

	extern ULONG_PTR TslGameBase;
	extern ULONG_PTR BEBase;
	extern ULONG_PTR win32u;
	extern float ScreenCenterX, ScreenCenterY;

	//数据变量
	extern ULONG64 g_Uworld, g_Levels, g_Actor, g_ObjectList, g_Gameinsts, g_LocalPlayers, g_PlayerControllers, g_Camera, g_Localactor, g_Games, g_PlayerControllers2;

	extern bool Switch_Menu, Switch_Battle, Switch_Player, Switch_AimBot, Switch_Vehicle, Switch_BoxSupport, Switch_Item, Switch_Expose, Switch_Radar, Switch_InsHit, Switch_NoRecoil, Switch_Hp, Switch_Name, Switch_chuanqiang,
		ItemShow_YaoPin, ItemShow_ZhuangBei, shouchi,jiasu, anti_aim, ItemShow_Juji, HUANFU, ItemShow_BuQiang, ItemShow_PeiJian,xueliang,jisha,yaqiang,shift, Switch_Audience;

	extern bool IsLock;//是否锁定目标
	extern float TargeNear, TargetLen, AimbotRange, ESPDistance, EnemyLatelyDistance;
	extern ULONG64 Aimbot;

	extern float 集_自身坐标x, 集_自身坐标y, 集_地图比例, 全_雷达半径, 全_雷达中心x, 全_雷达中心y;

	extern int BoneInfo[6][8];
	extern int AimBotBone[28];

	extern DrawIndex DrawInfo;
	extern ObjIdInfo ObjeId;
	extern 绘制颜色结构 ColorInfo;

	
	//地址解密
	EXTERN_C ULONG64 Dec_Uworld(ULONG64 a1);
	EXTERN_C ULONG64 Dec_Level(ULONG64 a1);
	EXTERN_C ULONG64 Dec_Actor(ULONG64 a1);
	EXTERN_C ULONG64 Dec_Gameinst(ULONG64 a1);
	EXTERN_C ULONG64 Dec_LocalPlayers(ULONG64 a1);
	EXTERN_C ULONG64 Dec_PlayerControllers(ULONG64 a1);
	EXTERN_C ULONG64 Dec_Localactor(ULONG64 a1);
	
	EXTERN_C ULONG64 Dec_Games1(ULONG64 a1);
	EXTERN_C ULONG64 Dec_Games2(ULONG64 a1);
	EXTERN_C ULONG64 Dec_Bullets(ULONG64 a1);
	EXTERN_C ULONG64 Dec_UObject(ULONG64 a1);
	EXTERN_C BYTE Moel_Hqwq(LONG64);
	EXTERN_C ULONG64 Dec_Overall(ULONG64 a1);



	bool LineTraceSingle(ULONG64 Entitys, Vector3 StartPos, Vector3 EndPos);


	std::string GetNames(DWORD ID);
	void DrawClear();



	void RefreshGameData();
	uint32_t Xenuine_DecryptID(uint64_t Obj);
	BOOL GetCanvasObj();
	BOOL Getskinid();
	


	VOID LockAim(Vector3 TargetCenterOfMass);
	void 自动瞄准(Vector3 TargetCenterOfMass, ULONG CameraManager);
	BOOL WorldToScreen_Aim(ULONG64 CameraManager, ULONG64 LocalMesh, Vector3 WorldLocation, Vector3* pOut, float* DeltaInMeters);
	float CalcBulletArriveTime(float ObjLen, float InitialSpeed); 

	Vector3 Prejudgement(Vector3 TargetCenter, int Distance, ULONG64 本人数组 );
	bool DrawBone(ULONG64 entity, ULONG64 pCamera, ULONG64 Mesh, DWORD Color, DWORD Color2, float px, Vector4* Rect, bool exaly);

	void DrawHealth(float x, float y, float w, float h, DWORD Color, float Health, int len, int Kill, ULONG Team, const wchar_t* pName);

	VOID GetBoneIndex(ULONG64 Mesh, Vector3* Result, ULONG Id);
	FRotator GetAim(Vector3 TargetCenterOfMass);
	FRotator Vector3ToFRotator(Vector3 v);

	BOOL WorldToScreen(ULONG64 CameraManager, Vector3 WorldLocation, Vector3* pOut, float* DeltaInMeters);

	BOOL WorldToScreen2(ULONG64 CameraManager, Vector3 WorldLocation, Vector3* pOut, float* DeltaInMeters, Vector3 Breath);

	Vector3 CalcAngle(Vector3 src, Vector3 dst);

	float GetDistance(Vector3 point1, Vector3 point2);

	预判数据 取预判初始数据(char* 参_武器名称);

	void 设置预判数据(预判数据* 参_预判数据, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, int v9, int v10, int v11, int v12, int v13);

	Vector3 取预判坐标(Vector3 参_对象坐标, float 参_对象距离, Vector3 参_对象速度, float 参_重力, 预判数据 参_预判数据, float mgravity);

	VOID 初始雷达参数();

	BOOL 雷达坐标转换(float 参_方向, float 参_敌人坐标x, float 参_敌人坐标y, float* 参_返回坐标x, float* 参_返回坐标y);

	VOID 设置雷达坐标(float 参_自身坐标x, float 参_自身坐标y);

	Vector3 旋转(Vector3 参_圆心, Vector3 参_坐标, float 参_角度);

	Vector3 求圆角度坐标(Vector3 参_中心, int 参_半径, int 参_角度);

	VOID 刷新雷达();

	char* GetUNames(ULONG ObjId);

	BOOL IsObjectId(ULONG id, ObjectIdInfo* ObjIdInfo);

	VOID AddDrawInfo(UINT Type, float nX, float nY, float cX, float cY, float xW, DWORD Color, DWORD iColor, ULONG_PTR imageid, const wchar_t* wlpText);

	int EnumObgectNames();

	float CalculateAngle(float x1, float y1, float x2, float y2);

	D3DMATRIX2 Matrix2(Vector3 rot, Vector3 origin = Vector3(0, 0, 0));

	D3DMATRIX2 MatrixMultiplication(D3DMATRIX2 pM1, D3DMATRIX2 pM2);

	EXTERN_C ULONG64 Dec_PUBG(ULONG64 Type, ULONG_PTR DecVal, ULONG_PTR CallAddress);



}