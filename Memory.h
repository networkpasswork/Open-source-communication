#pragma once


EXTERN_C int FuncIndex;
EXTERN_C DWORD Asm_SysCall(...);

namespace Mem {
	extern ULONG NtReadVirtualMemoryIndex,
		NtWriteVirtualMemoryIndex,
		NtUserCreateFile,
		NtProtectVirtualMemoryIndex,
		NtUserSendInputIndex,
		NtUserGetAsyncKeyStateIndex,
		NtUserSetWindowDisplayAffinityIndex;
	EXTERN_C bool Asm_CopyMemory(void* _Dst, void const* _Src, size_t _Size);
	//EXTERN_C bool Asm_IsReadPtr(void const* _Dst, size_t _Size);
	EXTERN_C bool Asm_ZeroMemory(void const* _Dst, size_t _Size);

	template <class T> T Ram(__int64 ptr);
	template <class T> void Wam(__int64 ptr, T Val);
	//template <class T> void WVM(__int64 ptr, T Val);
	bool ReadMemory(__int64 ptr, void* buff, size_t size);
	//bool WriteMemory(__int64 ptr, void* buff, size_t size);
	BOOL DriverWrite(ULONG64 BaseAddress, PVOID buffer, ULONG size);

	BOOL NtUserSetWindowDisplayAffinity(HWND hWnd, DWORD dwAffinity);

	SHORT NtUserGetAsyncKeyState(DWORD key);

	DWORD NtUserSendInput(UINT cInputs, LPINPUT pInputs, int cbSize);

	template<class T>
	T Ram(__int64 ptr)
	{
		T buff;
		ReadMemory(ptr, &buff, sizeof(T));
		return buff;
	}
	/*template<class T>
	void Wam(__int64 ptr, T Val)
	{
		WriteMemory(ptr, &Val, sizeof(T));
	}*/


	template<class T>
	void Wam(__int64 ptr, T Val)
	{
		T readMe = Val;
		ULONG oldp;
		FuncIndex = NtWriteVirtualMemoryIndex;
		Asm_SysCall((HANDLE)-1, ptr, &readMe, sizeof(T), &oldp);
	}








}