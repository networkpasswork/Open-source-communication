#pragma once
#include "EngineSDK.hpp"
//
//0x2D366A0
typedef void(__fastcall* K2_DrawText) (ULONG_PTR UCanvas, ULONG_PTR RenderFont, class FString RenderText, struct FVector2D ScreenPosition, struct FLinearColor RenderColor, float Kerning, struct FLinearColor ShadowColor, struct FVector2D ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, struct FLinearColor OutlineColor);

namespace Canvas {
	extern ULONG_PTR DebugCanvas;//
	extern ULONG_PTR Font_Roboto;//字体
	extern ULONG_PTR Font_TSLFont;//字体

	extern K2_DrawText Func_K2_DrawText;

	EXTERN_C ULONG_PTR Canvas_ConstDrawTextCall1;
	EXTERN_C ULONG_PTR Canvas_ConstDrawTextCall2;
	EXTERN_C ULONG_PTR Canvas_ConstDrawTextCall3;
	EXTERN_C ULONG_PTR Canvas_ConstDrawTextCall4;

	EXTERN_C ULONG_PTR Canvas_ConstDrawLineAdds;

	EXTERN_C ULONG_PTR Canvas_ConstDrawRectAdds;
	EXTERN_C ULONG_PTR Canvas_ConstDrawRectCall;

	EXTERN_C ULONG_PTR Canvas_ConstDrawCall;

	EXTERN_C void UCanvas_DrawText(ULONG_PTR UCanvas, const class FString& Text, const struct FLinearColor& TextColor, float ScreenX, float ScreenY, ULONG_PTR Font, float Scale, bool bScalePosition);
	EXTERN_C void UCanvas_DrawLine(ULONG_PTR UCanvas, float StartScreenX, float StartScreenY, float EndScreenX, float EndScreenY, const struct FLinearColor& LineColor, float LineThickness);
	EXTERN_C void UCanvas_DrawRect(ULONG_PTR UCanvas, const struct FLinearColor& RectColor, float ScreenX, float ScreenY, float ScreenW, float ScreenH);
	EXTERN_C void UCanvas_DrawCircle(ULONG64 DebugUCanvas, float x0, float y0, float radius, float thickness, const struct FLinearColor& RectColor);

	void InsAddress();

	FLinearColor DXCOLORTOUE4(DWORD Color);

	void UCanvas_DrawBox(ULONG64 UObject, float ScreenX, float ScreenY, float ScreenW, float ScreenH, const FLinearColor& RectColor, float LineThickness);

	void ShortKey();

	void ShowMenu(ULONG64 UCanvas);

	ULONG64 EngineImmediDraw(ULONG64 Rcx, ULONG64 Rdx);

	ULONG64 GetUCanvcs();

	ULONG64 GetDebugUCanvcs();


	void UCanvas_Text(ULONG64 UCanvas, int x, int y, FLinearColor Color, const wchar_t* szText);
	void UCanvas_Text1(ULONG64 UCanvas, int x, int y, FLinearColor Color, const wchar_t* szText);
	ULONG_PTR FindObjectClass(const char* lpClassName);

	void GetKeyId();

}


