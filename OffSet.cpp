#include <Windows.h>
#include <iostream>
#include "OffSet.h"


DWORD OffSet::GlobalAddress;
DWORD OffSet::GlobalOffSet;
DWORD OffSet::UObject;
DWORD OffSet::Dec_UObject;
DWORD OffSet::UWorld;
DWORD OffSet::Dec_UWorld;
DWORD OffSet::GNames;
DWORD OffSet::Dec_GNames1;
DWORD OffSet::Dec_GNames2;
DWORD OffSet::level;
DWORD OffSet::Dec_level;
DWORD OffSet::Actor;
DWORD OffSet::Dec_Actor;
DWORD OffSet::GameInst;
DWORD OffSet::Dec_GameInst;
DWORD OffSet::LocalPlayer;
DWORD OffSet::Dec_LocalPlayer;
DWORD OffSet::PlayerControllers;
DWORD OffSet::Dec_PlayerControllers;
DWORD OffSet::Localactor;
DWORD OffSet::Dec_Localactor;
DWORD OffSet::Overall;
DWORD OffSet::Dec_Overall;
DWORD OffSet::Camera;
DWORD OffSet::MyTeam;

DWORD OffSet::SpoofAddress;
DWORD OffSet::LineTraceSingle;

DWORD OffSet::UCanvcsId;
DWORD OffSet::DebugUCanvcsId;
DWORD OffSet::GetUCanvcsCall;


DWORD OffSet::XeCrc;
DWORD OffSet::TsCrc;
DWORD OffSet::TsCrc2;
DWORD OffSet::DecCall;

DWORD OffSet::ProcessEventHook;
DWORD OffSet::HookRetAddress;
DWORD OffSet::K2_DrawText;
DWORD OffSet::K2_DrawLine;
DWORD OffSet::Ahud_DrawText;
DWORD OffSet::Ahud_DrawLine;
DWORD OffSet::Ahud_DrawRect;

DWORD OffSet::ObjId;
DWORD OffSet::NameCont;
DWORD OffSet::PItchX;
DWORD OffSet::Audience;
DWORD OffSet::PlayerName;
DWORD OffSet::PlayerState;
DWORD OffSet::PlayerSatisitc;
DWORD OffSet::Health;
DWORD OffSet::Health_Die;
DWORD OffSet::Mesh;
DWORD OffSet::Easy;
DWORD OffSet::CameraRot;
DWORD OffSet::CameraPos;
DWORD OffSet::CameraFov;
DWORD OffSet::Bone;
DWORD OffSet::BoneArry;
DWORD OffSet::PosiTion;
DWORD OffSet::DroppedItemGroup;
DWORD OffSet::DroppedItemGroup_UItem;
DWORD OffSet::Package;
DWORD OffSet::WeaponProcessor;
DWORD OffSet::CurrentWeaponIndex;
DWORD OffSet::EquippedWeapons;
DWORD OffSet::ActorRootComp;
DWORD OffSet::Veloctity;
DWORD OffSet::AHUDuobject;
DWORD OffSet::CanvasObject;
DWORD OffSet::DebugCanvasObject;
DWORD OffSet::MagicBullet;

DWORD OffSet::IDD;

DWORD OffSet::IsScope;
DWORD OffSet::ScopeCarmera;
DWORD OffSet::ScopeCarmera_Breath;

DWORD OffSet::K2_Draw_pictures;
DWORD OffSet::BulletTable;
DWORD OffSet::Dec_BulletTable;
DWORD OffSet::BulletTimeMax;
DWORD OffSet::WeaponTrajectoryData;
DWORD OffSet::TrajectoryConfig;
DWORD OffSet::ShuZu;//子弹数组  /lletArrays
DWORD OffSet::ShiJian;//子弹时间  /lletTime
DWORD OffSet::ZuoBiao;//子弹坐标  /lletPos

DWORD OffSet::WPItemId; //ItemID
DWORD OffSet::ArrayBreath; //屏息
DWORD OffSet::SXDD; //上下抖动 未调用 无需更新
DWORD OffSet::ZYDD; //左右抖动 未调用 无需更新
DWORD OffSet::BeiBaoDiZhi;//背包地址
DWORD OffSet::TeamNumber;//队伍编号

DWORD OffSet::DroppedItem;//训练场物品

DWORD OffSet::UAnimInstance;//压枪
DWORD OffSet::ControlRotation_CP;//压枪
DWORD OffSet::RecoilADSRotation_CP;//压枪antiaim
DWORD OffSet::antiaim;
DWORD OffSet::WeaponMesh;
DWORD OffSet::SkinId;
DWORD OffSet::XXXID;






DWORD OffSet::M24_CartelGold_01;
DWORD OffSet::AWM_Perl_01;
DWORD OffSet::Kar98k_Casual_01;
DWORD OffSet::Mini14_Dust_01;
DWORD OffSet::QBU88_CartelGold_01;
DWORD OffSet::FNFAL_BStat_01;
DWORD OffSet::SKS_BStat_01;
DWORD OffSet::HK416_3rd_01;
DWORD OffSet::AKM_CartelPink_01;
DWORD OffSet::Groza_CartelGold_01;
DWORD OffSet::QBZ95_Diamond_01;
DWORD OffSet::ScarL_1st_01;
DWORD OffSet::M16A4_Henna_01;












void OffSet::SearchOffSet() 
{
	XXXID = 0x1A62A90;
	Overall = 0x280;//	//Overall 48 8B ?? ?? ?? 00 00 48 85 C9 0F 84 ?? ?? ?? ?? 48 8B 01 FF 90 ?? ?? 00 00 48 8B ?? ?? ?? 00 00  mov rcx,[rax+00000318]
	GlobalAddress = 0x74DDE38;//;	//48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 85 C0 74 0A TslGame.exe+13DD520 - 48 8B 0D 7903FB05     - mov rcx,[TslGame.exe+738D8A0] { (208) }
	GlobalOffSet = 0xC90;//	//48 8B ?? ?? ?? 00 00 48 85 C9 0F 84 ?? ?? ?? ?? 48 8B 01 FF 90 ?? ?? 00 00 48 8B ?? ?? ?? 00 00 TslGame.exe+1D85434 - 48 8B 8F D8040000     - mov rcx,[rdi+000004D8]
	Dec_Overall = 0x8615FF48;//0x483ECF84;//	//48 8B ?? ?? ?? 00 00 48 85 C9 0F 84 ?? ?? ?? ?? 48 8B 01 FF 90 ?? ?? 00 00 48 8B ?? ?? ?? 00 00 倒数第二行  TslGame.exe+1D8546A - B9 4ACB3E48           - mov ecx,483ECB4A { 1212074826 }
	HookRetAddress = 0x3DFE506;//0x3DFE589;//;	//48 8B CE FF 50 18 3B 38  TslGame.exe+1377CB8 - 73 7F    上面一行             
	ProcessEventHook = 0x27967D0;//0x279678F;//	//74 06 E8 ?? ?? ?? ?? 90 48 8B 8C 24 ?? 00 00 00 48 33 CC E8 ?? ?? ?? ?? 48 8B 9C 24 ?? ?? 00 00 0F 28 B4 24 ?? ?? 00 00  mov [rsp+10],rdx      直接地址


	UObject = 0x745A8A8; //字体数组
	Dec_UObject = 0x483ECFA8; //FontsKey
	Dec_UWorld = 0x483ECFAD; //UWorldKey
	Dec_GNames1 = 0x483ECF3C;//0x483ECF6E; //GNamesPositionKey
	Dec_GNames2 = 0x483ECFCE; //GNamesOffsetKey
	Dec_level = 0x483ECF70; //LevelKey
	Dec_Actor = 0x483ECF04; //ActorKey
	Dec_GameInst = 0x483ECFF7; //GameinstKey
	Dec_LocalPlayer = 0x483ECF43; //LocalPlayerKey
	Dec_PlayerControllers = 0x483ECF9F; //PlayerControllerKey
	Dec_Localactor = 0x483ECF4B; //LocalActorKey

	NameCont = 0x400C; //IDD
	Camera = 0x4A8;//CameraManager	//Camera
	DecCall = 0x5020428;//指针地址 a call Nearby Dec_Overall 48 89 4C ?? ?? 57 48 83 EC ?? 48 C7 44 ?? ?? ?? ?? ?? ?? 48 89 5C 24 ?? 48 89 74 ?? ?? 49 8B ?? 48 8B ?? 33 C9
	UWorld = 0x750A668;//UWorld
	GNames = 0x74052A8 + 0x20;//GNames
	level = 0x8B0;//Level
	Actor = 0x190;//Actor
	GameInst = 0x238;//GameInstence	//ComponentToWorld //？？
	LocalPlayer = 0x50;//LocalPlayer
	PlayerControllers = 0x38;//PlayerController
	Localactor = 0x450;	//AcknowledgedPawn //本人数组

	SpoofAddress = 0x1865900;//0x5EA040;//不一样 封号点
	LineTraceSingle = 0x121D430;//E8 ?? ?? ?? ?? 48 8D 54 24 60 49 8B CF 84 C0 直接操作码 TslGame.exe+9B8AEF - E8 BC857202           - call TslGame.exe+30E10B0
	GetUCanvcsCall = 0x3E02460;

	K2_DrawText = 0x3957FA0;//绘制文本
	//K2_DrawLine = 0x38184D0;//TslGame.exe+2D09640 - 4C 8B DC - mov r11,rsp   4C 8B DC 48 81 EC ???????? 49 C7 43 ?????????? 41 0F 29 73 E8 0F 28 F3 4C 89 44 24 ?? 66
	//MagicBullet = 0x64EF90;//F3 0F 10 94 24 ???????? F3 0F 58 D0 F3 0F 11 94 24


	K2_DrawLine = 0x38184D0;//TslGame.exe+2D09640 - 4C 8B DC - mov r11,rsp   4C 8B DC 48 81 EC ???????? 49 C7 43 ?????????? 41 0F 29 73 E8 0F 28 F3 4C 89 44 24 ?? 66
	MagicBullet = 0x64EF90;//F3 0F 10 94 24 ???????? F3 0F 58 D0 F3 0F 11 94 24


	Ahud_DrawText = 0x30ADDD0;
	Ahud_DrawLine = 0x30AD7E0;
	Ahud_DrawRect = 0x30ADD10;







	//偏移区
	ObjId = 0x20;//ObjId
	Mesh = 0x518;//Mesh  48 89 5C 24 08 57 48 83 EC 40 48 8B 99 ?? ?? 00 00 48 8B FA 48 85 DB TslGame.exe+B5A47A - 48 8B 99 18050000     - mov rbx,[rcx+00000518]

	PItchX = 0x3FC;//PItchX
	Audience = 0x1080;//Audience
	PlayerName = 0x10A0;//Playname //PlayName
	PlayerState = 0x420;//PlayerState
	PlayerSatisitc = 0x480;//PlayerSatisitc
	Health = 0xE64;//Health
	Health_Die = 0xEC8;//Health_Die //GroggyHealth
	Easy = 0x764;//Eyes
	CameraPos = 0x1618;//CameraPos
	CameraRot = 0x15F4;//CameraRot
	CameraFov = 0x1604;//CameraFov

	Bone = 0xAC0;//Bone //BoneArray
	BoneArry = 0x240;//BoneArry //ComponentToWorld
	PosiTion = 0x250;//Position
	DroppedItemGroup = 0x2D8;//DroppedItemGroup  4c 8d a1 ???? 0000 8b 91 ???? 0000 2b 91 ???? 0000直接操作码 TslGame.exe+538D51 - 4C 8D A1 A0020000     - lea r12,[rcx+000002A0] | 48 89 b4 24 ???? 0000 48 89 b4 24 ???? 0000 45 33 c0
	DroppedItemGroup_UItem = 0x650;//DroppedItemGroup_UItem 0F B6 F8 48 85 D2 74 13 4C 8B CE 4C 8B C5 49 8B CE
	Package = 0x530; //Packge
	WeaponProcessor = 0xFD8;//WeaponProcessor 48 8B 8B ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 ?? ?? 74 ?? 48 8B 8B ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 ?? ?? 48 ?? ?? ?? E8 ?? ?? ?? ?? 81
	CurrentWeaponIndex = 0x2D9;//CurrentWeaponIndex 48 8B 8B ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 ?? ?? 74 ?? 48 8B 8B ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 ?? ?? 48 ?? ?? ?? E8 ?? ?? ?? ?? 81
	EquippedWeapons = 0x2B8; //EquippedWeapons 48 8B 8B ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 ?? ?? 74 ?? 48 8B 8B ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 ?? ?? 48 ?? ?? ?? E8 ?? ?? ?? ?? 81 -33

	ActorRootComp = 0x4C8;//ActorRootComp	
	Veloctity = 0x3D0;//Velotity
	IsScope = 0x984;//IsScope
	BulletTable = 0xEC8;//BulletTable //BulletTableArray
	Dec_BulletTable = 0x483ECF70;// //BulletTableKey
	WeaponTrajectoryData = 0xF48;//WeapTable //TrajectoryData
	TrajectoryConfig = 0xB8;////InitialSpeed
	ArrayBreath = 0x984;//屏息 //ArrayBreath

	UAnimInstance = 0xC68;//压枪 // FloatProperty TslGame.TslVehicleAnimInstance.AdditiveRot_Increase
	ControlRotation_CP = 0x5F8;//压枪 //StructProperty TslGame.TslAnimInstance.ControlRotation_CP
	RecoilADSRotation_CP = 0xAA0;//压枪 //StructProperty TslGame.TslAnimInstance.RecoilADSRotation_CP	

	DroppedItem = 0x400;//训练场物品 //EncryptedObjectProperty TslGame.DroppedItem.Item
	WPItemId = 0x270; //ItemID //NameProperty TslGame.Item.ItemID
	BeiBaoDiZhi = 0x756343C;//背包地址
	TeamNumber = 0x1B98;//队伍编号
	MyTeam = TeamNumber - 0x10;
	WeaponMesh = 0x658;//[30007] ArrayProperty TslGame.TslWeapon.CompatibleDualWeapons 0x638
	SkinId = 0x11C8;	//0x11C8
	//antiaim = 0x1350;
}











