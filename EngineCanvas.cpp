#include <Windows.h>
#include <iostream>
#include <intrin.h>
#include "Memory.h"
#include "OffSet.h"
#include "GameData.h"
#include "SpoofCall.h"
#include "EngineCanvas.h"
#include "obfuscation.h"
//#include "EngineSDK.hpp"

ULONG_PTR Canvas::DebugCanvas = 0;
ULONG_PTR Canvas::Font_Roboto = 0;
ULONG_PTR Canvas::Font_TSLFont = 0;

K2_DrawText Canvas::Func_K2_DrawText;

ULONG_PTR Canvas::Canvas_ConstDrawTextCall1;
ULONG_PTR Canvas::Canvas_ConstDrawTextCall2;
ULONG_PTR Canvas::Canvas_ConstDrawTextCall3;
ULONG_PTR Canvas::Canvas_ConstDrawTextCall4;

ULONG_PTR Canvas::Canvas_ConstDrawLineAdds;

ULONG_PTR Canvas::Canvas_ConstDrawRectAdds;
ULONG_PTR Canvas::Canvas_ConstDrawRectCall;

ULONG_PTR Canvas::Canvas_ConstDrawCall; //底层HOOK 


//这个位置初始化底层UI

void Canvas::InsAddress()
{	
	Canvas_ConstDrawTextCall1 = GameData::TslGameBase + 0x25E4AC0;//	//75 08 E8 ?? ?? ?? ?? 48 8B D8 48 8B D7 48 8D 4C 24 ??
	Canvas_ConstDrawTextCall2 = GameData::TslGameBase + 0x1A0C720;//	//48 8B D6 48 8D 8D F0 04 00 00 E8 ?? ?? ?? ?? 90 41 8B CE
	Canvas_ConstDrawTextCall3 = GameData::TslGameBase + 0x25D2280;//	//E8 ?? ?? ?? ?? 90 45 33 ED 45 8B F5 8B
	Canvas_ConstDrawTextCall4 = GameData::TslGameBase + 0x20BE7B0;//	//E8 ?? ?? ?? ?? 8B C3 48 8B 8D 28 01 00 00 48 33 CC
	Canvas_ConstDrawLineAdds = GameData::TslGameBase + 0x59C8C08;//	//48 8D 05 ?? ?? ?? ?? 48 89 45 90 C7 45 E0 00 00 00 00
	Canvas_ConstDrawRectAdds = GameData::TslGameBase + 0x72FA5B8;//	//48 8B 1D ?? ?? ?? ?? 48 8B 5B 30 48 89 5C 24 78
	Canvas_ConstDrawRectCall = GameData::TslGameBase + 0x3947AC0;//	//48 8D 54 24 38 48 8D 4C 24 50 E8 ?? ?? ?? ?? 90 C7 44 24
	Canvas_ConstDrawCall = GameData::TslGameBase + 0x3951F10;//	//E8 ?? ?? ?? ?? 90 4C 8D 9C 24 C0 00 00 00 41 0F 28 73 F0
}
//获取引擎地址
FLinearColor Canvas::DXCOLORTOUE4(DWORD Color) {
	FLinearColor color;
	color.A = (float)(((Color >> 24) & 0xFF) / 255.f);//0.f;//
	color.R = (float)((Color & 0xFF) / 255.f);
	color.G = (float)(((Color >> 8) & 0xFF) / 255.f);
	color.B = (float)(((Color >> 16) & 0xFF) / 255.f);
	return color;
}
//画圆
void Canvas::UCanvas_DrawCircle(ULONG64 DebugUCanvas,float x0, float y0, float radius, float thickness, const struct FLinearColor& RectColor)
{
	float x = radius, y = 0;
	float radiusError = 1 - x;
	while (x >= y)
	{
		//void UCanvas_DrawRect(ULONG_PTR UCanvas, const struct FLinearColor& RectColor, float ScreenX, float ScreenY, float ScreenW, float ScreenH);
		
		
		UCanvas_DrawRect(DebugUCanvas, RectColor,x + x0, y + y0, thickness, thickness);
		UCanvas_DrawRect(DebugUCanvas, RectColor,y + x0, x + y0, thickness, thickness);
		UCanvas_DrawRect(DebugUCanvas, RectColor,-x + x0, y + y0, thickness, thickness);
		UCanvas_DrawRect(DebugUCanvas, RectColor, -y + x0, x + y0, thickness, thickness);
		UCanvas_DrawRect(DebugUCanvas, RectColor, -x + x0, -y + y0, thickness, thickness);
		UCanvas_DrawRect(DebugUCanvas, RectColor, -y + x0, -x + y0, thickness, thickness);
		UCanvas_DrawRect(DebugUCanvas, RectColor, x + x0, -y + y0, thickness, thickness);
		UCanvas_DrawRect(DebugUCanvas, RectColor, y + x0, -x + y0, thickness, thickness);
		y++;
		if (radiusError < 0)
		{
			radiusError += 2 * y + 1;
		}
		else {
			x--;
			radiusError += 2 * (y - x + 1);
		}
	}
}
//绘制方框
void Canvas::UCanvas_DrawBox(ULONG64 UObject, float ScreenX, float ScreenY, float ScreenW, float ScreenH, const struct FLinearColor& RectColor, float LineThickness) {
	UCanvas_DrawLine(UObject, ScreenX, ScreenY, ScreenX, ScreenY + ScreenH, RectColor, LineThickness);
	UCanvas_DrawLine(UObject, ScreenX, ScreenY, ScreenX + ScreenW, ScreenY, RectColor, LineThickness);
	UCanvas_DrawLine(UObject, ScreenX + ScreenW, ScreenY, ScreenX + ScreenW, ScreenY + ScreenH, RectColor, LineThickness);
	UCanvas_DrawLine(UObject, ScreenX, ScreenY + ScreenH, ScreenX + ScreenW, ScreenY + ScreenH, RectColor, LineThickness);
}
void Canvas::ShortKey() 
{

	if (Mem::NtUserGetAsyncKeyState(VK_F1) & 1)
	{
		GameData::Switch_Radar = GameData::Switch_Radar ? FALSE : TRUE;
	}
	if (Mem::NtUserGetAsyncKeyState(VK_F2) & 1)
	{
		GameData::Switch_Player = GameData::Switch_Player ? FALSE : TRUE;
		
	}
	if (Mem::NtUserGetAsyncKeyState(VK_F3) & 1)
	{
		GameData::Switch_Item = GameData::Switch_Item ? FALSE : TRUE;
		
	}
	if (Mem::NtUserGetAsyncKeyState(VK_F4) & 1)
	{
		GameData::Switch_Vehicle = GameData::Switch_Vehicle ? FALSE : TRUE;
		
	}
	if (Mem::NtUserGetAsyncKeyState(VK_F6) & 1)
	{
		GameData::Switch_AimBot = GameData::Switch_AimBot ? FALSE : TRUE;
	}
	if (Mem::NtUserGetAsyncKeyState(VK_F7) & 1)
	{
		GameData::Switch_chuanqiang = GameData::Switch_chuanqiang ? FALSE : TRUE;
	}
	if (Mem::NtUserGetAsyncKeyState(VK_F8) & 1)
	{
		GameData::Switch_BoxSupport = GameData::Switch_BoxSupport ? FALSE : TRUE;
	}
	if (Mem::NtUserGetAsyncKeyState(VK_F9) & 1)
	{
		GameData::jiasu = GameData::jiasu ? FALSE : TRUE;
	}
	if (Mem::NtUserGetAsyncKeyState(VK_F10) & 1)
	{
		GameData::shouchi = GameData::shouchi ? FALSE : TRUE;
	}

	if (Mem::NtUserGetAsyncKeyState(VK_UP) & 1)
	{
		GameData::ESPDistance = GameData::ESPDistance + 100.f;
		if (GameData::ESPDistance > 1000.f)
		{
			GameData::ESPDistance = 1000.f;
		}
	}
	if (Mem::NtUserGetAsyncKeyState(VK_DOWN) & 1)
	{
		GameData::ESPDistance = GameData::ESPDistance - 100.f;
		if (GameData::ESPDistance < 100.f)
		{
			GameData::ESPDistance = 100.f;
		}
	}
	if (Mem::NtUserGetAsyncKeyState(VK_OEM_3) & 1)
	{
		GameData::Switch_Battle = GameData::Switch_Battle ? FALSE : TRUE;
	}
	if (Mem::NtUserGetAsyncKeyState(VK_HOME) & 1)
	{
		GameData::Switch_Menu = GameData::Switch_Menu ? FALSE : TRUE;
	}

}
void Canvas::ShowMenu(ULONG64 UCanvas) {
	if (GameData::Switch_Menu) {
		FLinearColor OFFColor = DXCOLORTOUE4(0xFFDAB9FF);
		FLinearColor NOColor = DXCOLORTOUE4(0xFF0000FF);
		float _Top = 300.f;
		float _Lift = 10.f;
		UCanvas_Text(UCanvas, _Lift+30, _Top + 3, DXCOLORTOUE4(0xFFFFFFFF), XorStringW(L" Home显示/隐藏菜单"));
		_Top += 25.f;
		UCanvas_Text(UCanvas, _Lift, _Top, OFFColor, XorStringW(L" ━━━━━━━━━━━━━━━━━━━━━━━"));
		_Top += 25.f;
		UCanvas_Text(UCanvas, _Lift, _Top, OFFColor, XorStringW(L"科技本是逆天之行，请谨慎操作"));
		_Top += 25.f;
		UCanvas_Text(UCanvas, _Lift, _Top, GameData::Switch_Radar ? NOColor : OFFColor, XorStringW(L" F1 地图雷达"));
		UCanvas_Text(UCanvas, _Lift+100, _Top, GameData::Switch_Player ? NOColor : OFFColor, XorStringW(L" F2 显示人物"));
		_Top += 25.f;
		UCanvas_Text(UCanvas, _Lift, _Top, GameData::Switch_Item ? NOColor : OFFColor, XorStringW(L" F3 显示物资"));
		UCanvas_Text(UCanvas, _Lift + 100, _Top, GameData::Switch_Vehicle ? NOColor : OFFColor, XorStringW(L" F4 显示载具"));
		_Top += 25.f;
		UCanvas_Text(UCanvas, _Lift, _Top, GameData::Switch_AimBot ? NOColor : OFFColor, XorStringW(L" F6 自动瞄准"));
		UCanvas_Text(UCanvas, _Lift + 100, _Top, GameData::Switch_chuanqiang ? NOColor : OFFColor, XorStringW(L" F7 子弹追踪【高危】"));
		_Top += 25.f;
		UCanvas_Text(UCanvas, _Lift, _Top, GameData::Switch_BoxSupport ? NOColor : OFFColor, XorStringW(L" F8 显示盒子"));
		UCanvas_Text(UCanvas, _Lift+100, _Top, GameData::jiasu ? NOColor : OFFColor, XorStringW(L" F9 人物加速【高危】"));
		_Top += 25.f;
		UCanvas_Text(UCanvas, _Lift , _Top, GameData::shouchi ? NOColor : OFFColor, XorStringW(L" F10 手持武器"));
		UCanvas_Text(UCanvas, _Lift + 100, _Top, GameData::Switch_Battle ? NOColor : OFFColor, XorStringW(L" ~ 战斗模式"));
		_Top += 25.f;
		UCanvas_Text(UCanvas, _Lift, _Top + 3, DXCOLORTOUE4(0xFFFFFFFF), XorStringW(L" 智能漏打默认开启，且不能关闭"));
		_Top += 25.f;
		UCanvas_Text(UCanvas, _Lift, _Top + 3, DXCOLORTOUE4(0xFFFFFFFF), XorStringW(L" ↑/↓调节透视距离"));
		_Top += 25.f;
		UCanvas_Text(UCanvas, _Lift+25, _Top + 3, DXCOLORTOUE4(0xFFFFFFFF), XorStringW(L" 【S H I F T】锁头"));

	}	

}

ULONG64 Canvas::EngineImmediDraw(ULONG64 Rcx, ULONG64 Rdx) {
	void* RetAddress = _ReturnAddress();
	DWORD Eax = Mem::Ram<DWORD>(Rcx + 0xB8);
	Mem::Wam<DWORD>(Rdx, Eax);
	Eax = Mem::Ram<DWORD>(Rcx + 0xBC);
	Mem::Wam<DWORD>(Rdx + 0x4, Eax);
	if (GameData::TslGameBase + OffSet::HookRetAddress == (ULONG_PTR)RetAddress)
	{
		ULONG64 DebugUCanvas = GetUCanvcs();//UI底层绘制
		//ULONG64 DebugUCanvas = GetDebugUCanvcs();//UI顶层绘制
		if (DebugUCanvas > 0)
		{

			GameData::ScreenCenterX = (float)(Mem::Ram<int>(DebugUCanvas + 0x48) / 2);
			GameData::ScreenCenterY = (float)(Mem::Ram<int>(DebugUCanvas + 0x4C) / 2);
			/*GameData::ScreenCenterX = (float)(Mem::Ram<int>(DebugUCanvas + 0x40) / 2);
			GameData::ScreenCenterY = (float)(Mem::Ram<int>(DebugUCanvas + 0x44) / 2);*/


			InsAddress();
			////清除绘制数据
			GameData::DrawClear();


		
			//枚举绘制对象
			GameData::RefreshGameData();
			
			//菜单
			ShowMenu(DebugUCanvas);
			//热键
			ShortKey();
		


			


			

			for (int i = 0; i < GameData::DrawInfo.Count; i++)
			{
				if (GameData::DrawInfo.info[i].Type == 1)
				{
					UCanvas_Text1(DebugUCanvas,
						GameData::DrawInfo.info[i].nX,
						GameData::DrawInfo.info[i].nY,
						DXCOLORTOUE4(GameData::DrawInfo.info[i].Color),
						GameData::DrawInfo.info[i].Text);
				}
				if (GameData::DrawInfo.info[i].Type == 2)//绘制线条
				{

					UCanvas_DrawLine(
						DebugUCanvas,
						GameData::DrawInfo.info[i].nX,
						GameData::DrawInfo.info[i].nY,
						GameData::DrawInfo.info[i].cX,
						GameData::DrawInfo.info[i].cY,
						DXCOLORTOUE4(GameData::DrawInfo.info[i].Color),
						GameData::DrawInfo.info[i].xW);
				}
				if (GameData::DrawInfo.info[i].Type == 3)//绘制填充
				{
					UCanvas_DrawRect(
						DebugUCanvas,
						DXCOLORTOUE4(GameData::DrawInfo.info[i].Color),
						GameData::DrawInfo.info[i].nX,
						GameData::DrawInfo.info[i].nY,
						GameData::DrawInfo.info[i].cX,
						GameData::DrawInfo.info[i].cY);
				}

				if (GameData::DrawInfo.info[i].Type == 4)//绘制方框
				{

					UCanvas_DrawBox(
						DebugUCanvas,
						GameData::DrawInfo.info[i].nX,
						GameData::DrawInfo.info[i].nY,
						GameData::DrawInfo.info[i].cX,
						GameData::DrawInfo.info[i].cY,
						DXCOLORTOUE4(GameData::DrawInfo.info[i].Color), GameData::DrawInfo.info[i].xW);
				}
				if (GameData::DrawInfo.info[i].Type == 5)//绘制文本
				{
					UCanvas_Text(DebugUCanvas,
						GameData::DrawInfo.info[i].nX,
						GameData::DrawInfo.info[i].nY,
						DXCOLORTOUE4(GameData::DrawInfo.info[i].Color),
						GameData::DrawInfo.info[i].Text);

				}
				if (GameData::DrawInfo.info[i].Type == 6)//绘制文本
				{
					UCanvas_DrawText(DebugUCanvas, 
						GameData::DrawInfo.info[i].Text,
						DXCOLORTOUE4(GameData::DrawInfo.info[i].Color),
						GameData::DrawInfo.info[i].nX,
						GameData::DrawInfo.info[i].nY,
						Font_TSLFont,
						1, true);
				}

				if (GameData::DrawInfo.info[i].Type == 7)//绘制圆形
				{
					UCanvas_DrawCircle(DebugUCanvas, GameData::DrawInfo.info[i].nX, GameData::DrawInfo.info[i].nY, GameData::DrawInfo.info[i].cX, GameData::DrawInfo.info[i].xW, DXCOLORTOUE4(GameData::DrawInfo.info[i].Color));
				}				
			}

		}
		



	}
	return Rdx;
}
//
ULONG64 Canvas::GetUCanvcs() {
	ULONG64 YID = (ULONG64)OffSet::CanvasObject;
	typedef ULONG64(__fastcall* GetUCavcs_t)(ULONG_PTR UCavcsId);
	GetUCavcs_t GetUCavcsFn = GetUCavcs_t(GameData::TslGameBase + OffSet::GetUCanvcsCall);
	return spoof_call(GameData::SpoofBytes, GetUCavcsFn, YID);
}
ULONG64 Canvas::GetDebugUCanvcs() {
	ULONG64 YID = (ULONG64)OffSet::DebugCanvasObject;
	typedef ULONG64(__fastcall* GetUCavcs_t)(ULONG_PTR UCavcsId);
	GetUCavcs_t GetUCavcsFn = GetUCavcs_t(GameData::TslGameBase + OffSet::GetUCanvcsCall);
	return spoof_call(GameData::SpoofBytes, GetUCavcsFn, YID);
}
void Canvas::UCanvas_Text1(ULONG64 UCanvas, int x, int y, FLinearColor Color, const wchar_t* szText)
{
	UCanvas_DrawText(UCanvas, szText, Color, x, y, Font_Roboto, 1, true);
	
}
void Canvas::UCanvas_Text(ULONG64 UCanvas, int x, int y, FLinearColor Color, const wchar_t* szText)
{
	//UCanvas_DrawText(UCanvas, szText, Color, x, y, Font_Roboto, 1, true);
	Func_K2_DrawText(UCanvas, Font_Roboto, FString(szText), FVector2D(x, y), Color, 1.0f, FLinearColor(0.f, 0.f, 0.f, 1.f), FVector2D(), false, false, true, FLinearColor(0.f, 0.f, 0.f, 1.0f));
}
ULONG_PTR Canvas::FindObjectClass(const char* lpClassName) {//LobbyHUD_Default_C
	ULONG64 GObjectsTArray = GameData::Dec_UObject(Mem::Ram<ULONG64>(GameData::TslGameBase + OffSet::UObject));
	if (GObjectsTArray > 0) {
		for (size_t i = 0; i < 1000000; i++) {
			ULONG64 GObjects = Mem::Ram<ULONG64>(GObjectsTArray + 0x18 * i);
			ULONG FontId = GameData::Xenuine_DecryptID(GObjects);
			if (FontId > 0 && FontId < 1000000) {
				std::string Name = GameData::GetNames(FontId);
				if (Name != ("NULL") && strcmp(Name.c_str(), lpClassName) == 0)
				{
					return GObjects;
				}
			}
		}
	}
	return 0;
}


