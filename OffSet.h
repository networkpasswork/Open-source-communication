#pragma once

#define INRANGE(x,a,b)    (x >= a && x <= b)
#define GetBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xA) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GetByte( x )    (GetBits(x[0]) << 4 | GetBits(x[1]))

namespace OffSet {

	extern DWORD GlobalAddress;
	extern DWORD GlobalOffSet;
	extern DWORD UObject;
	extern DWORD Dec_UObject;
	extern DWORD UWorld;
	extern DWORD Dec_UWorld;
	extern DWORD GNames;
	extern DWORD Dec_GNames1;
	extern DWORD Dec_GNames2;
	extern DWORD level;
	extern DWORD Dec_level;
	extern DWORD Actor;
	extern DWORD Dec_Actor;
	extern DWORD GameInst;
	extern DWORD Dec_GameInst;
	extern DWORD LocalPlayer;
	extern DWORD Dec_LocalPlayer;
	extern DWORD PlayerControllers;
	extern DWORD Dec_PlayerControllers;
	extern DWORD Localactor;
	extern DWORD Dec_Localactor;
	extern DWORD Overall;
	extern DWORD Dec_Overall;
	extern DWORD Camera;
	extern DWORD MyTeam;

	extern DWORD SpoofAddress;
	extern DWORD MagicBullet;
	extern DWORD LineTraceSingle;
	extern DWORD IDD;
	extern DWORD UCanvcsId;
	extern DWORD DebugUCanvcsId;
	extern DWORD GetUCanvcsCall;


	extern DWORD XeCrc;
	extern DWORD TsCrc;
	extern DWORD TsCrc2;
	extern DWORD DecCall;

	extern DWORD ProcessEventHook;
	extern DWORD HookRetAddress;
	extern DWORD K2_DrawText;
	extern DWORD K2_DrawLine;
	extern DWORD Ahud_DrawText;
	extern DWORD Ahud_DrawLine;
	extern DWORD Ahud_DrawRect;

	extern DWORD ObjId;
	extern DWORD NameCont;
	extern DWORD PItchX;
	extern DWORD Audience;
	extern DWORD PlayerName;
	extern DWORD PlayerState;
	extern DWORD PlayerSatisitc;
	extern DWORD Health;
	extern DWORD Health_Die;
	extern DWORD Mesh;
	extern DWORD Easy;
	extern DWORD CameraRot;
	extern DWORD CameraPos;
	extern DWORD CameraFov;
	extern DWORD Bone;
	extern DWORD BoneArry;
	extern DWORD PosiTion;
	extern DWORD DroppedItemGroup;
	extern DWORD DroppedItemGroup_UItem;
	extern DWORD Package;
	extern DWORD WeaponProcessor;
	extern DWORD CurrentWeaponIndex;
	extern DWORD EquippedWeapons;
	extern DWORD ActorRootComp;
	extern DWORD Veloctity;


	extern DWORD CanvasObject;
	extern DWORD DebugCanvasObject;
	extern DWORD AHUDuobject;

	extern DWORD IsScope;
	extern DWORD ScopeCarmera;
	extern DWORD ScopeCarmera_Breath;
	extern DWORD K2_Draw_pictures;
	extern DWORD BulletTable;
	extern DWORD Dec_BulletTable;
	extern DWORD BulletTimeMax;
	extern DWORD WeaponTrajectoryData;
	extern DWORD TrajectoryConfig;
	extern DWORD ShuZu;//子弹数组  /lletArrays
	extern DWORD ShiJian;//子弹时间  /lletTime
	extern DWORD ZuoBiao;//子弹坐标  /lletPos

	extern DWORD WPItemId; //ItemID
	extern DWORD ArrayBreath; //屏息
	extern DWORD SXDD; //上下抖动 未调用 无需更新
	extern DWORD ZYDD; //左右抖动 未调用 无需更新
	extern DWORD BeiBaoDiZhi;//背包地址
	extern DWORD TeamNumber;//队伍编号

	extern DWORD DroppedItem;//训练场物品

	extern DWORD UAnimInstance;//压枪
	extern DWORD ControlRotation_CP;//压枪
	extern DWORD RecoilADSRotation_CP;//压枪antiaim
	extern DWORD antiaim;
	extern DWORD WeaponMesh;
	extern DWORD SkinId;
	extern DWORD XXXID;


	extern DWORD M24_CartelGold_01;
	extern DWORD AWM_Perl_01;
	extern DWORD Kar98k_Casual_01;
	extern DWORD Mini14_Dust_01;
	extern DWORD QBU88_CartelGold_01;
	extern DWORD FNFAL_BStat_01;
	extern DWORD SKS_BStat_01;
	extern DWORD HK416_3rd_01;
	extern DWORD AKM_CartelPink_01;
	extern DWORD Groza_CartelGold_01;
	extern DWORD QBZ95_Diamond_01;
	extern DWORD ScarL_1st_01;
	extern DWORD M16A4_Henna_01;



	void SearchOffSet();

}

struct FName
{
	union
	{
		struct
		{
			int ComparisonIndex;
			int Number;
		};

		unsigned long long CompositeComparisonValue;
	};

	inline FName()
		: ComparisonIndex(0),
		Number(0)
	{
	};

	inline FName(int i)
		: ComparisonIndex(i),
		Number(0)
	{
	};

	FName(const char* nameToFind)
		: ComparisonIndex(0),
		Number(0)
	{
	}


};
struct FKey
{
	struct FName                                       KeyName;                                                  // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	uintptr_t Unknow;
	uintptr_t CallBack;

};
#define Color_Black 0x0			//黑色
#define Color_Red 0xFF			//红色
#define Color_NavyBlue 0x800000 //藏青
#define Color_Green 0xFF00
#define Color_White 0xFFFFFF
#define Color_Violet 0xFF0090
#define Color_Skyblue 0xFF8800
#define Color_YanQing 0xFFFF00
#define Color_Fuchsin 0xFF00FF
#define Color_Orange 0x80FF
#define Color_Yellow 0xFFFF//这些都用不了啊
#define Color_DarkGrey 0x606060
#define Color_DarkGreen 0x80E000
#define Color_PurplishRed 0x800080
#define Color_Pink 0x8050FF
#define Color_VividGreen 0xE080
#define Color_Pink2 0xFFA8FF
#define Color_AliceBlue 0x80A080
#define Color_FuHong 0xC080FF
#define Color_DanZiSe 0xFF8080

enum Bones : int
{
	Root = 0,
	pelvis,
	spine_01,
	spine_02,
	spine_03,
	neck_01,
	Head,
	face_root,
	eyebrows_pos_root,
	eyebrows_root,
	eyebrows_r,
	eyebrows_l,
	eyebrow_l,
	eyebrow_r,
	forehead_root,
	forehead,
	jaw_pos_root = 26,
	jaw_root,
	jaw,
	mouth_down_pos_root,
	mouth_down_root,
	lip_bm_01,
	lip_bm_02,
	lip_br,
	lip_bl,
	jaw_01,
	jaw_02,
	cheek_pos_root,
	cheek_root,
	cheek_r,
	cheek_l,
	nose_sIDe_root,
	nose_sIDe_r_01,
	nose_sIDe_r_02,
	nose_sIDe_l_01,
	nose_sIDe_l_02,
	eye_pos_r_root,
	eye_r_root,
	eye_rot_r_root,
	eye_lID_u_r,// 39,
	eye_r,// 40,
	eye_lID_b_r,// 41,
	eye_pos_l_root,// 42,
	eye_l_root,// 43,
	eye_rot_l_root,// 44,
	eye_lID_u_l,// 45,
	eye_l,// 46,
	eye_lID_b_l,// 47,
	nose_pos_root,// 48,
	nose,// 49,
	mouth_up_pos_root,// 50,
	mouth_up_root,// 51,
	lip_ul,// 52,
	lip_um_01,// 53,
	lip_um_02,// 54,
	lip_ur,// 55,
	lip_l,// 56,
	lip_r,// 57,
	hair_root,// 58,
	hair_b_01,// 59,
	hair_b_02,// 60,
	hair_l_01,// 61,
	hair_l_02,// 62,
	hair_r_01,// 63,
	hair_r_02,// 64,
	hair_f_02,// 65,
	hair_f_01,// 66,
	hair_b_pt_01,// 67,
	hair_b_pt_02,// 68,
	hair_b_pt_03,// 69,
	hair_b_pt_04,// 70,
	hair_b_pt_05,// 71,
	camera_fpp,// 72,
	GunReferencePoint,// 73,
	GunRef,// 74,
	breast_l,// 75,
	breast_r,// 76,
	clavicle_l,// 77,
	upperarm_l,// 78,
	lowerarm_l,// 79,
	hand_l,// 80,
	thumb_01_l,// 81,
	thumb_02_l,// 82,
	thumb_03_l,// 83,
	thumb_04_l_MBONLY,// 84,
	index_01_l,// 85,
	index_02_l,// 86,
	index_03_l,// 87,
	index_04_l_MBONLY,// 88,
	mIDdle_01_l,// 89,
	mIDdle_02_l,// 90,
	mIDdle_03_l,// 91,
	mIDdle_04_l_MBONLY,// 92,
	ring_01_l,// 93,
	ring_02_l,// 94,
	ring_03_l,// 95,
	ring_04_l_MBONLY,// 96,
	pinky_01_l,// 97,
	pinky_02_l,// 98,
	pinky_03_l,// 99,
	pinky_04_l_MBONLY,// 100,
	item_l,// 101,
	lowerarm_twist_01_l,// 102,
	upperarm_twist_01_l,// 103,
	clavicle_r,// 104,
	upperarm_r,// 105,
	lowerarm_r,// 106,
	hand_r,// 107,
	thumb_01_r,// 108,
	thumb_02_r,// 109,
	thumb_03_r,// 110,
	thumb_04_r_MBONLY,// 111,
	index_01_r,// 112,
	index_02_r,// 113,
	index_03_r,// 114,
	index_04_r_MBONLY,// 115,
	mIDdle_01_r,// 116,
	mIDdle_02_r,// 117,
	mIDdle_03_r,// 118,
	mIDdle_04_r_MBONLY,// 119,
	ring_01_r,// 120,
	ring_02_r,// 121,
	ring_03_r,// 122,
	ring_04_r_MBONLY,// 123,
	pinky_01_r,// 124,
	pinky_02_r,// 125,
	pinky_03_r,// 126,
	pinky_04_r_MBONLY,// 127,
	item_r,// 128,
	lowerarm_twist_01_r,// 129,
	upperarm_twist_01_r,// 130,
	BackPack,// 131,
	backpack_01,// 132,
	backpack_02,// 133,
	Slot_Primary,// 134,
	Slot_Secondary,// 135,
	Slot_Melee,// 136,
	slot_throwable,// 137,
	coat_l_01,// 138,
	coat_l_02,// 139,
	coat_l_03,// 140,
	coat_l_04,// 141,
	coat_fl_01,// 142,
	coat_fl_02,// 143,
	coat_fl_03,// 144,
	coat_fl_04,// 145,
	coat_b_01,// 146,
	coat_b_02,// 147,
	coat_b_03,// 148,
	coat_b_04,// 149,
	coat_r_01,// 150,
	coat_r_02,// 151,
	coat_r_03,// 152,
	coat_r_04,// 153,
	coat_fr_01,// 154,
	coat_fr_02,// 155,
	coat_fr_03,// 156,
	coat_fr_04,// 157,
	thigh_l,// 158,
	calf_l,// 159,
	foot_l,// 160,
	ball_l,// 161,
	calf_twist_01_l,// 162,
	thigh_twist_01_l,// 163,
	thigh_r,// 164,
	calf_r,// 165,
	foot_r,// 166,
	ball_r,// 167,
	calf_twist_01_r,// 168,
	thigh_twist_01_r,// 169,
	Slot_SIDeArm,// 170,
	skirt_l_01,// 171,
	skirt_l_02,// 172,
	skirt_l_03,// 173,
	skirt_f_01,// 174,
	skirt_f_02,// 175,
	skirt_f_03,// 176,
	skirt_b_01,// 177,
	skirt_b_02,// 178,
	skirt_b_03,// 179,
	skirt_r_01,// 180,
	skirt_r_02,
	skirt_r_03,
	ik_hand_root,
	ik_hand_gun,
	ik_hand_r,
	ik_hand_l,
	ik_aim_root,
	ik_aim_l,
	ik_aim_r,
	ik_foot_root,
	ik_foot_l,
	ik_foot_r,
	camera_tpp,
	ik_target_root,
	ik_target_l,
	ik_target_r,
	VB_spine_03_spine_03,
	VB_upperarm_r_lowerarm_r
};