#pragma once
#pragma comment (lib,"Advapi32.lib")
#include <Windows.h>
#include <winternl.h>
#include "obfuscation.h"
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t; /*Unsigned*/
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;



typedef struct _IO_Struct
{
	uint32_t PID;
	uint64_t Addr;
	uint32_t Size;
	PVOID	Buffer;
} IO_Struct, * PIO_Struct;

#define IOCTL_READ CTL_CODE(FILE_DEVICE_UNKNOWN, 0x795139, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_WRITE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x219315, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ALLOC CTL_CODE(FILE_DEVICE_UNKNOWN, 0x193276, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_FREE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x829143, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_CloseHandle CTL_CODE(FILE_DEVICE_UNKNOWN, 0x253714, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_GetHandle CTL_CODE(FILE_DEVICE_UNKNOWN, 0x356294, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
typedef long(__fastcall* RtlInitUnicodeStringFn)(
	OUT PUNICODE_STRING DestinationString,
	IN PCWSTR SourceString
	);


typedef long(__fastcall* ZwCreateFileFn)(
	_Out_     PHANDLE FileHandle,
	_In_      ACCESS_MASK DesiredAccess,
	_In_      POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_     PIO_STATUS_BLOCK IoStatusBlock,
	_In_opt_  PLARGE_INTEGER AllocationSize,
	_In_      ULONG FileAttributes,
	_In_      ULONG ShareAccess,
	_In_      ULONG CreateDisposition,
	_In_      ULONG CreateOptions,
	_In_opt_  PVOID EaBuffer,
	_In_      ULONG EaLength
	);



typedef long(__fastcall* NtOpenFileFn)(OUT PHANDLE FileHandle,
	IN ACCESS_MASK DesiredAccess,
	IN POBJECT_ATTRIBUTES ObjectAttributes,
	OUT PIO_STATUS_BLOCK IoStatusBlock,
	IN ULONG ShareAccess,
	IN ULONG OpenOptions);


typedef long(__fastcall* NtDeviceIoControlFileFn)(IN HANDLE FileHandle,
	IN HANDLE Event OPTIONAL,
	IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
	IN PVOID ApcContext OPTIONAL,
	OUT PIO_STATUS_BLOCK IoStatusBlock,
	IN ULONG IoControlCode,
	IN PVOID InputBuffer OPTIONAL,
	IN ULONG InputBufferLength,
	OUT PVOID OutputBuffer OPTIONAL,
	IN ULONG OutputBufferLength);
typedef long(__fastcall* NtDeviceIoControlFileFnf)(IN HANDLE FileHandle,
	IN HANDLE Event OPTIONAL,
	IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
	IN PVOID ApcContext OPTIONAL,
	OUT PIO_STATUS_BLOCK IoStatusBlock,
	IN ULONG IoControlCode,
	IN PVOID InputBuffer OPTIONAL,
	IN ULONG InputBufferLength,
	OUT float OutputBuffer OPTIONAL,
	IN ULONG OutputBufferLength);
typedef long(__fastcall* NtCloseFn)(
	IN HANDLE Handle);


namespace FIO
{
	static HANDLE Drv; static uint32_t PID;
	__forceinline void SecureIO(uint32_t Code, IO_Struct Data)
	{
		IO_STATUS_BLOCK IO;
		auto Ntdll = GetModuleHandleA(XorString("Ntdll.dll"));
		NtDeviceIoControlFileFn pNtDeviceIoControlFile = (NtDeviceIoControlFileFn)GetProcAddress(Ntdll, XorString("NtDeviceIoControlFile"));
		pNtDeviceIoControlFile(Drv, 0, 0, 0, &IO, Code, &Data, sizeof(IO_Struct), 0, 0);
	}



	static bool CheckDrvStatus()
	{
		auto Ntdll = GetModuleHandleA("Ntdll.dll");
		RtlInitUnicodeStringFn PRtlInitUnicodeStringFn = (RtlInitUnicodeStringFn)GetProcAddress(Ntdll, "RtlInitUnicodeString");
		UNICODE_STRING FileName;
		PRtlInitUnicodeStringFn(&FileName, L"\\??\\NDIS");
		OBJECT_ATTRIBUTES Params; IO_STATUS_BLOCK IO;
		InitializeObjectAttributes(&Params, &FileName, OBJ_CASE_INSENSITIVE, nullptr, nullptr);
		NtOpenFileFn pNtOpenFile = (NtOpenFileFn)GetProcAddress(Ntdll, "NtOpenFile");
		pNtOpenFile(&Drv, GENERIC_READ, &Params, &IO, 0x7, FILE_NON_DIRECTORY_FILE);
		if (Drv != 0)
		{
			return true;
		}
	}
	static void CloseDrv()
	{
		auto Ntdll = GetModuleHandleA(XorString("Ntdll.dll"));
		NtCloseFn pNtClose = (NtCloseFn)GetProcAddress(Ntdll, XorString("NtClose"));
		pNtClose(Drv);
	}
	static void Write(uint64_t Addr, void* Buff, uint32_t Size)
	{
		if (!Addr || !Size) return;
		IO_Struct Data = { PID, Addr ,Size, Buff };
		SecureIO(IOCTL_WRITE, Data);
	}
	/*static void Read(uint64_t Addr, void* Buff, uint32_t Size)
	{
		void* Buf;
		if (!Addr || !Size) return;
		D_IO_Struct Data = { PID, Size, Addr };
		RSecureIO(IOCTL_READ, Data, Buff, Size);
	}*/
}