#include <Windows.h> 
#include "Memory.h"
#include "OffSet.h"
#include "GameData.h"
#include "EngineCanvas.h"
#include "obfuscation.h"
#include <iostream>//
#include "DriverIO.h"
#include "UserAPI.h"

ULONG_PTR VtableFack[1000];

DWORD NTAPI ExceptionHandler(EXCEPTION_POINTERS* ExceptionInfo) {
	UNREFERENCED_PARAMETER(ExceptionInfo);
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
	{
		byte* p = (byte*)ExceptionInfo->ExceptionRecord->ExceptionAddress;
		if ((*p == 0xF3) && (*(p + 1) == 0xA4) && (*(p + 7) == 0xEB))
		{
			ExceptionInfo->ContextRecord->Rip = ExceptionInfo->ContextRecord->Rip + 9;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		if ((*p == 0x8A) && (*(p + 1) == 0x07) && (*(p + 4) == 0xC6))
		{
			ExceptionInfo->ContextRecord->Rip = ExceptionInfo->ContextRecord->Rip + 0xE;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

BOOL SuperHackScreenBykaka()
{

	HWND hWindow;

	DWORD_PTR FuncAddress = (DWORD_PTR)GetProcAddress(GetModuleHandleA(XorString("win32u.dll")), XorString("NtUserSetWindowDisplayAffinity"));
	Mem::NtUserSetWindowDisplayAffinityIndex = *(DWORD*)(FuncAddress + 0x4);


	while (!IsWindow(hWindow)) { hWindow = FindWindowA("UnrealWindow", NULL); }
	Mem::NtUserSetWindowDisplayAffinity(hWindow, 1);



	DWORD old;
	void* hookGetDcAddr = nullptr;
	if (GetModuleHandle(L"win32u.dll"))
		hookGetDcAddr = (void*)GetProcAddress(GetModuleHandle(L"win32u.dll"), "NtUserGetDC");
	else
		hookGetDcAddr = (void*)GetProcAddress(GetModuleHandle(L"user32.dll"), "GetDC");
	if (hookGetDcAddr)
	{
		BYTE GetDcShell[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
		VirtualProtectEx(GetCurrentProcess(), hookGetDcAddr, 6, PAGE_EXECUTE_READWRITE, &old);
		memcpy(hookGetDcAddr, GetDcShell, sizeof(GetDcShell));
		VirtualProtectEx(GetCurrentProcess(), hookGetDcAddr, 6, old, &old);

	}

	void* HookCreateDc = nullptr;
	if (GetModuleHandle(L"win32u.dll"))
		HookCreateDc = (void*)GetProcAddress(GetModuleHandle(L"win32u.dll"), "NtGdiCreateCompatibleDC");
	else
		HookCreateDc = (void*)GetProcAddress(GetModuleHandle(L"GDI32.dll"), "CreateCompatibleDC");
	if (HookCreateDc)
	{
		BYTE CreateDcShell[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
		VirtualProtectEx(GetCurrentProcess(), HookCreateDc, sizeof(CreateDcShell), PAGE_EXECUTE_READWRITE, &old);
		memcpy(HookCreateDc, CreateDcShell, sizeof(CreateDcShell));
		VirtualProtectEx(GetCurrentProcess(), HookCreateDc, sizeof(CreateDcShell), old, &old);


	}



	void* HookGetDisplay = nullptr;
	if (GetModuleHandle(L"win32u.dll"))
		HookGetDisplay = (void*)GetProcAddress(GetModuleHandle(L"win32u.dll"), "NtUserGetWindowDisplayAffinity");
	else
		HookGetDisplay = (void*)GetProcAddress(GetModuleHandle(L"user32.dll"), "GetWindowDisplayAffinity");
	if (HookGetDisplay)
	{
		BYTE GetDisplayShell[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
		VirtualProtectEx(GetCurrentProcess(), HookGetDisplay, 6, PAGE_EXECUTE_READWRITE, &old);
		memcpy(HookGetDisplay, GetDisplayShell, sizeof(GetDisplayShell));
		VirtualProtectEx(GetCurrentProcess(), HookGetDisplay, 6, old, &old);

	}




	void* HookBit = nullptr;
	if (GetModuleHandle(L"win32u.dll"))
		HookBit = (void*)GetProcAddress(GetModuleHandle(L"win32u.dll"), "NtGdiBitBlt");
	else
		HookBit = (void*)GetProcAddress(GetModuleHandle(L"GDI32.dll"), "BitBlt");
	if (HookBit)
	{
		BYTE BitbleShell[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
		VirtualProtectEx(GetCurrentProcess(), HookBit, 6, PAGE_EXECUTE_READWRITE, &old);
		memcpy(HookBit, BitbleShell, sizeof(BitbleShell));
		VirtualProtectEx(GetCurrentProcess(), HookBit, 6, old, &old);

	}


	void* HookCreatebitmap = nullptr;
	if (GetModuleHandle(L"win32u.dll"))
		HookCreatebitmap = (void*)GetProcAddress(GetModuleHandle(L"win32u.dll"), "NtGdiCreateCompatibleBitmap");
	else
		HookCreatebitmap = (void*)GetProcAddress(GetModuleHandle(L"GDI32.dll"), "CreateCompatibleBitmap");
	if (HookCreatebitmap)
	{
		BYTE BitMapShell[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
		VirtualProtectEx(GetCurrentProcess(), HookCreatebitmap, 6, PAGE_EXECUTE_READWRITE, &old);
		memcpy(HookCreatebitmap, BitMapShell, sizeof(BitMapShell));
		VirtualProtectEx(GetCurrentProcess(), HookCreatebitmap, 6, old, &old);
	}


	void* hookselectobj = nullptr;
	if (GetModuleHandle(L"win32u.dll"))
		hookselectobj = (void*)GetProcAddress(GetModuleHandle(L"win32u.dll"), "NtGdiSelectBitmap");
	else
		hookselectobj = (void*)GetProcAddress(GetModuleHandle(L"GDI32.dll"), "SelectObject");
	if (hookselectobj)
	{
		BYTE selectobj[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
		VirtualProtectEx(GetCurrentProcess(), hookselectobj, 6, PAGE_EXECUTE_READWRITE, &old);
		memcpy(hookselectobj, selectobj, sizeof(selectobj));
		VirtualProtectEx(GetCurrentProcess(), hookselectobj, 6, old, &old);


	}
	else
	{
		hookselectobj = (void*)GetProcAddress(GetModuleHandle(L"GDI32.dll"), "SelectObject");
		BYTE selectobj[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
		VirtualProtectEx(GetCurrentProcess(), hookselectobj, 6, PAGE_EXECUTE_READWRITE, &old);
		memcpy(hookselectobj, selectobj, sizeof(selectobj));
		VirtualProtectEx(GetCurrentProcess(), hookselectobj, 6, old, &old);
	}


	void* hookDCW = nullptr;
	if (GetModuleHandle(L"win32u.dll"))
		hookDCW = (void*)GetProcAddress(GetModuleHandle(L"win32u.dll"), "NtGdiOpenDCW");
	else
		hookDCW = (void*)GetProcAddress(GetModuleHandle(L"GDI32.dll"), "CreateDCW");
	if (hookDCW)
	{
		BYTE DCWS[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
		VirtualProtectEx(GetCurrentProcess(), hookDCW, 6, PAGE_EXECUTE_READWRITE, &old);
		memcpy(hookDCW, DCWS, sizeof(DCWS));
		VirtualProtectEx(GetCurrentProcess(), hookDCW, 6, old, &old);


	}

	HMODULE uxtheme = LoadLibraryA("uxtheme.dll");
	if (uxtheme)
	{
		uint64_t GetBitmap = (uint64_t)GetProcAddress(uxtheme, "GetThemeBitmap");
		if (GetBitmap > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetBitmap, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)GetBitmap, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetBitmap, 6, old, &old);


		}
		uint64_t GetBufferedPaintDC = (uint64_t)GetProcAddress(uxtheme, "GetBufferedPaintDC");
		if (GetBufferedPaintDC > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetBufferedPaintDC, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)GetBufferedPaintDC, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetBufferedPaintDC, 6, old, &old);
		}
		uint64_t GetBufferedPaintTargetDC = (uint64_t)GetProcAddress(uxtheme, "GetBufferedPaintTargetDC");
		if (GetBufferedPaintTargetDC > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetBufferedPaintTargetDC, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)GetBufferedPaintTargetDC, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetBufferedPaintTargetDC, 6, old, &old);

		}
		uint64_t GetBufferedPaintBits = (uint64_t)GetProcAddress(uxtheme, "GetBufferedPaintBits");
		if (GetBufferedPaintBits > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetBufferedPaintBits, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)GetBufferedPaintBits, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetBufferedPaintBits, 6, old, &old);
		}
		uint64_t GetThemeBackgroundContentRect = (uint64_t)GetProcAddress(uxtheme, "GetThemeBackgroundContentRect");
		if (GetThemeBackgroundContentRect > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetThemeBackgroundContentRect, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)GetThemeBackgroundContentRect, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetThemeBackgroundContentRect, 6, old, &old);
		}
		uint64_t GetThemeMargins = (uint64_t)GetProcAddress(uxtheme, "GetThemeMargins");
		if (GetThemeMargins > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetThemeMargins, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)GetThemeMargins, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetThemeMargins, 6, old, &old);
		}
	}
	HMODULE gdi32full = LoadLibraryA("gdi32full.dll");
	if (gdi32full)
	{
		uint64_t GetBitmapBits = (uint64_t)GetProcAddress(gdi32full, "GetBitmapBits");
		if (GetBitmapBits > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetBitmapBits, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)GetBitmapBits, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetBitmapBits, 6, old, &old);

		}
		uint64_t CreateCompatibleBitmap = (uint64_t)GetProcAddress(gdi32full, "CreateCompatibleBitmap");
		if (CreateCompatibleBitmap > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)CreateCompatibleBitmap, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)CreateCompatibleBitmap, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)CreateCompatibleBitmap, 6, old, &old);

		}
		uint64_t CreateDIBitmap = (uint64_t)GetProcAddress(gdi32full, "CreateDIBitmap");
		if (CreateDIBitmap > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)CreateDIBitmap, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)CreateDIBitmap, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)CreateDIBitmap, 6, old, &old);

		}
		uint64_t GetDIBits = (uint64_t)GetProcAddress(gdi32full, "GetDIBits");
		if (GetDIBits > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetDIBits, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)GetDIBits, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GetDIBits, 6, old, &old);

		}
		uint64_t CreateCompatibleDC = (uint64_t)GetProcAddress(gdi32full, "CreateCompatibleDC");
		if (CreateCompatibleDC > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)CreateCompatibleDC, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)CreateCompatibleDC, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)CreateCompatibleDC, 6, old, &old);

		}
		uint64_t BitBlt = (uint64_t)GetProcAddress(gdi32full, "BitBlt");
		if (BitBlt > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)BitBlt, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)BitBlt, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)BitBlt, 6, old, &old);

		}
		uint64_t hdcCreateDCW = (uint64_t)GetProcAddress(gdi32full, "hdcCreateDCW");
		if (hdcCreateDCW > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)hdcCreateDCW, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)hdcCreateDCW, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)hdcCreateDCW, 6, old, &old);

		}
		uint64_t GdiGetDC = (uint64_t)GetProcAddress(gdi32full, "GdiGetDC");
		if (GdiGetDC > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GdiGetDC, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)GdiGetDC, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)GdiGetDC, 6, old, &old);

		}
		uint64_t CreateDCExW = (uint64_t)GetProcAddress(gdi32full, "CreateDCExW");
		if (CreateDCExW > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)CreateDCExW, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)CreateDCExW, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)CreateDCExW, 6, old, &old);

		}
		uint64_t CreateDCA = (uint64_t)GetProcAddress(gdi32full, "CreateDCA");
		if (CreateDCA > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)CreateDCA, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)CreateDCA, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)CreateDCA, 6, old, &old);

		}
		uint64_t NtGdiBitblt = (uint64_t)GetProcAddress(gdi32full, "NtGdiBitBlt");
		if (NtGdiBitblt > 0x1000)
		{
			BYTE Nop[] = { 0x33,0xc0,0xc3,0x90,0x90,0x90 };
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)NtGdiBitblt, 6, PAGE_EXECUTE_READWRITE, &old);
			memcpy((BYTE*)NtGdiBitblt, Nop, sizeof(Nop));
			VirtualProtectEx(GetCurrentProcess(), (LPVOID)NtGdiBitblt, 6, old, &old);

		}
	}
	return TRUE;
}

void StartFunc()
{
	GameData::TslGameBase = (ULONG_PTR)GetModuleHandle(NULL);
	OffSet::SearchOffSet();


	GameData::SpoofBytes = (void*)(GameData::TslGameBase + OffSet::SpoofAddress);//FF 23
	Canvas::Font_Roboto = Canvas::FindObjectClass("Roboto");
	Canvas::Font_TSLFont = Canvas::FindObjectClass("TSLFont");
	Canvas::Func_K2_DrawText = (K2_DrawText)(GameData::TslGameBase + OffSet::K2_DrawText);

	//Canvas::Func_K2_DrawLine = (K2_DrawLine_t)(GameData::TslGameBase + OffSet::K2_DrawLine);//K2画线


	GameData::GetCanvasObj();
	GameData::Getskinid();



	DWORD_PTR FD = (DWORD_PTR)GetProcAddress(GetModuleHandle(XorStringW(L"Ntdll.dll")), XorString("ZwWriteVirtualMemory"));//内核写内存函数 走syscall调用
	Mem::NtWriteVirtualMemoryIndex = *(DWORD*)(FD + 0x4);


	HMODULE user32 = GetModuleHandle(XorStringW(L"win32u.dll"));
	if (user32)
	{
		DWORD_PTR FuncAddress = (DWORD_PTR)GetProcAddress(user32, XorString("NtUserGetAsyncKeyState"));
		Mem::NtUserGetAsyncKeyStateIndex = *(ULONG*)(FuncAddress + 0x4);
		FuncAddress = (DWORD_PTR)GetProcAddress(user32, XorString("NtUserSendInput"));
		Mem::NtUserSendInputIndex = *(DWORD*)(FuncAddress + 0x4);
	}
	else
	{
		Mem::NtUserGetAsyncKeyStateIndex = 0x1044;
		Mem::NtUserSendInputIndex = 0x1082;
	}

	GameData::EnumObgectNames();
	ULONG64 Overall = Mem::Ram<ULONG64>(GameData::TslGameBase + OffSet::GlobalAddress);
	ULONG64 Overall2 = Mem::Ram<ULONG64>(Overall + OffSet::GlobalOffSet);
	ULONG64 Overall3 = GameData::Dec_Overall(Mem::Ram<ULONG64>(Overall2 + OffSet::Overall));
	ULONG64 Overall4 = Mem::Ram<ULONG64>(Overall3);
	Mem::ReadMemory(Overall4, VtableFack, sizeof(VtableFack));
	VtableFack[3] = (ULONG64)Canvas::EngineImmediDraw;
	Mem::Wam<ULONG64>(Overall3, (ULONG64)VtableFack);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{

#ifdef CONSOLETEST

#endif  CONSOLETEST

		AddVectoredExceptionHandler(1, (PVECTORED_EXCEPTION_HANDLER)ExceptionHandler);

		/*UserAPI::GetInstance()->Initialize(myxorstrw("34537"), myxorstrw("584076308"), myxorstrw("135696"));
		UserAPI::GetInstance()->CardLogin("54740BE641E7412DA45A65C01CD8DA9F");
		ULONG64 ExpireTime = UserAPI::GetInstance()->GetRestTime();*/
		/*if (ExpireTime > 0)
		{
			UserAPI::GetInstance()->Exit();*/
			StartFunc();
			SuperHackScreenBykaka();

		//}
		//else
		//{
		//	AllocConsole();
		//	freopen("CONOUT$", "w", stdout);//。。。。
		//	printf("您所使用的是盗版辅助！请下载正版辅助！");
		//	MessageBoxA(NULL, "您使用了盗版！", "请使用正版辅助!", NULL);
		//}
		break;
	}
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}