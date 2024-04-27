#include "BaseLib/GlobalMemory.h"
#include "BaseLib/ChunkFile.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/ChunkFileFile.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileSimple(void)
{
	CChunkFile	cChunkFile;
	CFileUtil	cFileUtil;
	int			iChunkNum;
	
	cFileUtil.MakeDir("Output");
	cFileUtil.Delete("Output/ChunkFile.bin");
	cChunkFile.Init(DiskFile("Output/ChunkFile.bin"));
	AssertFalse(cChunkFile.IsOpen());
	AssertTrue(cChunkFile.WriteOpen());
	AssertTrue(cChunkFile.IsOpen());
	AssertTrue(cChunkFile.WriteChunkBegin());
	AssertTrue(cChunkFile.WriteChunkEnd("ThisChunk"));
	AssertTrue(cChunkFile.WriteClose());
	AssertFalse(cChunkFile.IsOpen());
	cChunkFile.Kill();

	cChunkFile.Init(DiskFile("Output/ChunkFile.bin"));
	AssertFalse(cChunkFile.IsOpen());
	AssertTrue(cChunkFile.ReadOpen());
	Pass();
	AssertTrue(cChunkFile.IsOpen());
	iChunkNum = cChunkFile.FindFirstChunkWithName("ThisChunk");
	AssertInt(0, iChunkNum);
	AssertTrue(cChunkFile.ReadChunkBegin(iChunkNum));
	Pass();
	AssertTrue(cChunkFile.ReadClose());
	Pass();
	AssertFalse(cChunkFile.IsOpen());
	cChunkFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileMD5ing(void)
{
	char			szFox[] = "The quick brown fox jumps over the lazy dog";
	uint8	ucFoxMD5[] = {0x9e, 0x10, 0x7d, 0x9d, 0x37, 0x2b, 0xb6, 0x82, 0x6b, 0xd8, 0x1d, 0x35, 0x42, 0xa4, 0x19, 0xd6};
	int				iFoxLen;
	char			szLorem[] = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
	uint8	ucLoremMD5[] = {0xfa, 0x5c, 0x89, 0xf3, 0xc8, 0x8b, 0x81, 0xbf, 0xd5, 0xe8, 0x21, 0xb0, 0x31, 0x65, 0x69, 0xaf};
	int				iLoremLen;
	CChunkFile		cChunkFile;

	iFoxLen = (int)strlen(szFox);
	iLoremLen = (int)strlen(szLorem);

	cChunkFile.Init(MemoryFile());
	AssertTrue(cChunkFile.WriteOpen());
	AssertTrue(cChunkFile.WriteChunkBegin());
	AssertTrue(cChunkFile.Write(szFox, 1, iFoxLen) > 0);
	AssertTrue(cChunkFile.WriteChunkEnd("ChunkName"));
	AssertTrue(cChunkFile.Write(szLorem, 1, iLoremLen) > 0);
	AssertTrue(cChunkFile.WriteClose());

	AssertTrue(cChunkFile.ReadOpen());
	AssertMD5(ucLoremMD5, (uint8 *)cChunkFile.GetMD5Hash());
	AssertTrue(cChunkFile.ReadChunkBegin(0));
	AssertMD5(ucFoxMD5, (uint8 *)cChunkFile.GetMD5Hash());
	AssertTrue(cChunkFile.ReadChunkEnd());
	AssertTrue(cChunkFile.ReadClose());

	cChunkFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFilenameing(void)
{
	CChunkFile		cChunkFile;
	int				iChunkNum;
	char			acTwentyOne[] =   {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
	char			acTwentyTwo[] =   {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19};
	char			acTwentyThree[] = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29};
	char			acActual[10];

	cChunkFile.Init(MemoryFile());
	AssertTrue(cChunkFile.WriteOpen());
	AssertTrue(cChunkFile.WriteChunkBegin());
	AssertLongLongInt(1, cChunkFile.Write(acTwentyOne, 10, 1));
	AssertTrue(cChunkFile.WriteChunkBegin());
	AssertLongLongInt(1, cChunkFile.Write(acTwentyTwo, 10, 1));
	AssertTrue(cChunkFile.WriteChunkEnd("Floopy"));
	AssertTrue(cChunkFile.WriteChunkBegin());
	AssertLongLongInt(1, cChunkFile.Write(acTwentyThree, 10, 1));
	AssertTrue(cChunkFile.WriteChunkEnd("Floopy"));
	AssertTrue(cChunkFile.WriteChunkEnd("Rise"));
	AssertTrue(cChunkFile.WriteClose());

	AssertTrue(cChunkFile.ReadOpen());
	iChunkNum = cChunkFile.FindFirstChunkWithName("Rise");
	AssertInt(0, iChunkNum);
	AssertTrue(cChunkFile.ReadChunkBegin(iChunkNum));
	AssertLongLongInt(1, cChunkFile.Read(acActual, 10, 1));
	AssertMemory(acTwentyOne, acActual, 10);

	iChunkNum = cChunkFile.FindFirstChunkWithName("Floopy");
	AssertInt(0, iChunkNum);
	AssertTrue(cChunkFile.ReadChunkBegin(iChunkNum));
	AssertLongLongInt(1, cChunkFile.Read(acActual, 10, 1));
	AssertMemory(acTwentyTwo, acActual, 10);
	AssertTrue(cChunkFile.ReadChunkEnd());

	iChunkNum = cChunkFile.FindNextChunkWithName();
	AssertInt(1, iChunkNum);
	AssertTrue(cChunkFile.ReadChunkBegin(iChunkNum));
	AssertLongLongInt(1, cChunkFile.Read(acActual, 10, 1));
	AssertMemory(acTwentyThree, acActual, 10);
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkEnd());
	AssertTrue(cChunkFile.ReadClose());

	cChunkFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileFileBasic(void)
{
	CChunkFile		cChunkFile;
	CChunkFileFile	cChunkFileFile1;
	CChunkFileFile	cChunkFileFile2;
	CFileBasic		cFileBasic1;
	CFileBasic		cFileBasic2;
	int				iResult;
	char			szResult[256];

	cChunkFile.Init(MemoryFile());
	AssertTrue(cChunkFile.WriteOpen());

	AssertTrue(cChunkFile.WriteChunkBegin());
	cChunkFileFile1.Init(&cChunkFile);
	cFileBasic1.Init(&cChunkFileFile1);
	AssertTrue(cFileBasic1.Open(EFM_Write_Create));
	AssertTrue(cFileBasic1.WriteInt(12345678));
	AssertTrue(cFileBasic1.WriteInt(0x7fffffff));
	AssertTrue(cFileBasic1.Close());
	AssertTrue(cChunkFile.WriteChunkEnd("2 Ints"));
	cFileBasic1.Kill();

	AssertTrue(cChunkFile.WriteChunkBegin());
	cChunkFileFile1.Init(&cChunkFile);
	cFileBasic2.Init(&cChunkFileFile1);
	AssertTrue(cFileBasic2.Open(EFM_Write_Create));
	AssertTrue(cFileBasic2.WriteString("Hello"));
	AssertTrue(cFileBasic2.WriteString("World"));
	AssertTrue(cFileBasic2.Close());
	AssertTrue(cChunkFile.WriteChunkEnd("The Usual"));
	cFileBasic2.Kill();

	AssertTrue(cChunkFile.WriteClose());

	AssertTrue(cChunkFile.ReadOpen());
	AssertTrue(cChunkFile.ReadChunkBegin("2 Ints"));
	cChunkFileFile1.Init(&cChunkFile);
	cFileBasic1.Init(&cChunkFileFile1);
	AssertTrue(cFileBasic1.Open(EFM_Read));
	AssertTrue(cFileBasic1.ReadInt(&iResult));
	AssertInt(12345678, iResult);
	AssertTrue(cFileBasic1.ReadInt(&iResult));
	AssertInt(0x7fffffff, iResult);
	AssertTrue(cFileBasic1.Close());
	AssertTrue(cChunkFile.ReadChunkEnd());
	cFileBasic1.Kill();

	AssertTrue(cChunkFile.ReadChunkBegin("The Usual"));
	cChunkFileFile1.Init(&cChunkFile);
	cFileBasic2.Init(&cChunkFileFile1);
	AssertTrue(cFileBasic2.Open(EFM_Read));
	AssertTrue(cFileBasic2.ReadString(szResult, 256));
	AssertString("Hello", szResult);
	AssertTrue(cFileBasic2.ReadString(szResult, 256));
	AssertString("World", szResult);
	AssertTrue(cFileBasic2.Close());
	AssertTrue(cChunkFile.ReadChunkEnd());
	cFileBasic2.Kill();

	cChunkFile.ReadClose();
	cChunkFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFile(void)
{
	BeginTests();
	FastFunctionsInit();
	MemoryInit();
	
	TestChunkFileSimple();
	TestChunkFileMD5ing();
	TestChunkFilenameing();
	TestChunkFileFileBasic();

	MemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

