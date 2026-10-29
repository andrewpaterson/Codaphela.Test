typedef signed char int8_t;
typedef short int16_t;
typedef long int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int_least8_t;
typedef short int_least16_t;
typedef long int_least32_t;
typedef long long int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned long uint_least32_t;
typedef unsigned long long uint_least64_t;
typedef int int_fast8_t;
typedef int int_fast16_t;
typedef long int_fast32_t;
typedef long long int_fast64_t;
typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned long uint_fast32_t;
typedef unsigned long long uint_fast64_t;
typedef long intptr_t;
typedef unsigned long uintptr_t;
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
extern "C"
{
int HostOpen(const char* szPath, int iMode);
int HostClose(int iHandle);
uint32_t HostRead(int iHandle, void* pvBuffer, uint32_t uiBytes);
uint32_t HostWrite(int iHandle, const void* pvBuffer, uint32_t uiBytes);
int HostSeek(int iHandle, long long llOffset, int iOrigin);
long long HostTell(int iHandle);
long long HostSize(int iHandle);
int HostTruncate(int iHandle, long long llSize);
int HostFlush(int iHandle);
int HostDelete(const char* szPath);
int HostRename(const char* szOld, const char* szNew);
int HostExists(const char* szPath);
long long HostFileSize(const char* szPath);
int HostMakeDir(const char* szPath);
int HostRemoveDir(const char* szPath);
int HostIsDirectory(const char* szPath);
int HostTouch(const char* szPath);
int HostCurrentDirectory(char* szDest, uint32_t uiSize);
int HostFindFile(const char* szDirectory, uint32_t uiIndex, char* szName, uint32_t uiSize);
}
static uint32_t Command(int iCommand)
{
(*(volatile unsigned char*)(0x00FF0200 + 0x18)) = (unsigned char)iCommand;
return (*(volatile uint32_t*)(0x00FF0200 + 0x10));
}
static long long CommandLong(int iCommand)
{
uint32_t uiLow;
uint32_t uiHigh;
(*(volatile unsigned char*)(0x00FF0200 + 0x18)) = (unsigned char)iCommand;
uiLow = (*(volatile uint32_t*)(0x00FF0200 + 0x10));
uiHigh = (*(volatile uint32_t*)(0x00FF0200 + 0x14));
return (long long)(((unsigned long long)uiHigh << 32) | uiLow);
}
static uint32_t PathCommand(int iCommand, const char* szPath)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)szPath;
return Command(iCommand);
}
int HostOpen(const char* szPath, int iMode)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)szPath;
(*(volatile uint32_t*)(0x00FF0200 + 0x04)) = (uint32_t)iMode;
return (int)Command(1);
}
int HostClose(int iHandle)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)iHandle;
return (int)Command(2);
}
uint32_t HostRead(int iHandle, void* pvBuffer, uint32_t uiBytes)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)iHandle;
(*(volatile uint32_t*)(0x00FF0200 + 0x04)) = (uint32_t)pvBuffer;
(*(volatile uint32_t*)(0x00FF0200 + 0x08)) = uiBytes;
return Command(3);
}
uint32_t HostWrite(int iHandle, const void* pvBuffer, uint32_t uiBytes)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)iHandle;
(*(volatile uint32_t*)(0x00FF0200 + 0x04)) = (uint32_t)pvBuffer;
(*(volatile uint32_t*)(0x00FF0200 + 0x08)) = uiBytes;
return Command(4);
}
int HostSeek(int iHandle, long long llOffset, int iOrigin)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)iHandle;
(*(volatile uint32_t*)(0x00FF0200 + 0x04)) = (uint32_t)llOffset;
(*(volatile uint32_t*)(0x00FF0200 + 0x08)) = (uint32_t)((unsigned long long)llOffset >> 32);
(*(volatile uint32_t*)(0x00FF0200 + 0x0C)) = (uint32_t)iOrigin;
return (int)Command(5);
}
long long HostTell(int iHandle)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)iHandle;
return CommandLong(6);
}
long long HostSize(int iHandle)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)iHandle;
return CommandLong(7);
}
int HostTruncate(int iHandle, long long llSize)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)iHandle;
(*(volatile uint32_t*)(0x00FF0200 + 0x04)) = (uint32_t)llSize;
(*(volatile uint32_t*)(0x00FF0200 + 0x08)) = (uint32_t)((unsigned long long)llSize >> 32);
return (int)Command(8);
}
int HostFlush(int iHandle)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)iHandle;
return (int)Command(9);
}
int HostDelete(const char* szPath)
{
return (int)PathCommand(10, szPath);
}
int HostRename(const char* szOld, const char* szNew)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)szOld;
(*(volatile uint32_t*)(0x00FF0200 + 0x04)) = (uint32_t)szNew;
return (int)Command(19);
}
int HostExists(const char* szPath)
{
return (int)PathCommand(11, szPath);
}
long long HostFileSize(const char* szPath)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)szPath;
return CommandLong(12);
}
int HostMakeDir(const char* szPath)
{
return (int)PathCommand(13, szPath);
}
int HostRemoveDir(const char* szPath)
{
return (int)PathCommand(14, szPath);
}
int HostIsDirectory(const char* szPath)
{
return (int)PathCommand(15, szPath);
}
int HostTouch(const char* szPath)
{
return (int)PathCommand(16, szPath);
}
int HostCurrentDirectory(char* szDest, uint32_t uiSize)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)szDest;
(*(volatile uint32_t*)(0x00FF0200 + 0x04)) = uiSize;
return (int)Command(17);
}
int HostFindFile(const char* szDirectory, uint32_t uiIndex, char* szName, uint32_t uiSize)
{
(*(volatile uint32_t*)(0x00FF0200 + 0x00)) = (uint32_t)szDirectory;
(*(volatile uint32_t*)(0x00FF0200 + 0x04)) = uiIndex;
(*(volatile uint32_t*)(0x00FF0200 + 0x08)) = (uint32_t)szName;
(*(volatile uint32_t*)(0x00FF0200 + 0x0C)) = uiSize;
return (int)Command(18);
}
