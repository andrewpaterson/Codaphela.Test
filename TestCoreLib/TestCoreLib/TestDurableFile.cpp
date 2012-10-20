#include "TestLib/Assert.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "CoreLib/DurableFile.h"
#include "BaseLib/FileBasic.h"
#include "BaseLib/PointerRemapper.h"
#include "BaseLib/TextFile.h"
#include "CoreLib/TypeConverter.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileInit(void)
{
	FastFunctionsInit();
	TypeConverterInit();

	CDurableFile	cDurable;
	CFileUtil		cFileUtil;

	cFileUtil.RemoveDir("Durable1");
	cFileUtil.MakeDir("Durable1");

	cDurable.Init(TRUE, "Durable1\\TestFile.txt", "Durable1\\_TestFile.txt");
	cDurable.Open();

	cDurable.Begin();
	cDurable.End();

	cDurable.Close();
	cDurable.Kill();

	FastFunctionsKill();
	TypeConverterKill();

	cFileUtil.RemoveDir("Durable1");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileWrite(void)
{
	FastFunctionsInit();
	TypeConverterInit();

	CFileUtil		cFileUtil;
	CDurableFile	cDurable;
	filePos			iResult;
	CTextFile		cTextFile;

	char			sz1[] = "In the age of chaos";
	char			sz2[] = " two factions battled";
	char			sz3[] = "undys";
	char			sz4[] = "In the age of undys two factions battled";

	cFileUtil.RemoveDir("Durable2");
	cFileUtil.MakeDir("Durable2");

	cDurable.Init(TRUE, "Durable2\\WrittenFile.txt", "Durable2\\_WrittenFile.txt");
	cDurable.Open();
	AssertLongLongInt(0, cDurable.miPosition);
	AssertLongLongInt(0, cDurable.miLength);

	cDurable.Begin();
	iResult = cDurable.Write(sz1, (int)strlen(sz1), 1);
	AssertLongLongInt(1, iResult);
	AssertLongLongInt(19, cDurable.miPosition);
	AssertLongLongInt(19, cDurable.miLength);
	AssertInt(1, cDurable.mcWrites.NumElements());

	iResult = cDurable.Write(sz2, (int)strlen(sz2)+1, 1);
	AssertLongLongInt(1, iResult);
	AssertLongLongInt(41, cDurable.miPosition);
	AssertLongLongInt(41, cDurable.miLength);
	AssertInt(1, cDurable.mcWrites.NumElements());

	iResult = cDurable.Write(14, sz3, (int)strlen(sz3), 1);
	AssertLongLongInt(1, iResult);
	AssertLongLongInt(19, cDurable.miPosition);
	AssertLongLongInt(41, cDurable.miLength);
	AssertInt(1, cDurable.mcWrites.NumElements());
	AssertString(sz4, (char*)RemapSinglePointer(cDurable.mcWrites.Get(0), sizeof(SDurableFileCommandWrite)));

	cDurable.End();

	cDurable.Close();
	cDurable.Kill();

	cTextFile.Init();
	cTextFile.Read("Durable2\\WrittenFile.txt");
	AssertString(sz4, cTextFile.Text());
	cTextFile.Kill();

	FastFunctionsKill();
	TypeConverterKill();

	cFileUtil.RemoveDir("Durable2");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestComplexDurableFile(void)
{
	FastFunctionsInit();
	TypeConverterInit();

	CFileUtil		cFileUtil;
	CDurableFile	cDurable;
	filePos				iResult;
	CTextFile		cTextFile;

	char			sz1[] = "BBBB";
	char			sz2[] = "CCDD";
	char			sz3[] = "EEEE";
	char			sz4[] = "AAAA";
	char			sz5[] = "FFFF";

	char			szDest[5];
	char			szAll[17];

	cFileUtil.RemoveDir("Durable3");
	cFileUtil.MakeDir("Durable3");

	cDurable.Init(TRUE, "Durable3\\WrittenFile.txt", "Durable3\\_WrittenFile.txt");
	cDurable.Open();

	cDurable.Begin();

	iResult = cDurable.Write(4, sz1, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertLongLongInt(8, cDurable.miPosition);
	AssertLongLongInt(8, cDurable.miLength);

	iResult = cDurable.Write(10, sz2, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertLongLongInt(14, cDurable.miPosition);
	AssertLongLongInt(14, cDurable.miLength);

	memset(szDest, 0, 5);
	iResult = cDurable.Read(8, szDest, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertLongLongInt(12, cDurable.miPosition);
	AssertLongLongInt(14, cDurable.miLength);
	AssertString("", szDest);
	AssertString("CC", &szDest[2]);

	iResult = cDurable.Write(12, sz3, 1, 4);
	AssertLongLongInt(4, iResult);
	AssertLongLongInt(16, cDurable.miPosition);
	AssertLongLongInt(16, cDurable.miLength);

	memset(szDest, 0, 5);
	iResult = cDurable.Read(14, szDest, 2, 2);
	AssertLongLongInt(1, iResult);
	AssertLongLongInt(16, cDurable.miPosition);
	AssertLongLongInt(16, cDurable.miLength);
	AssertString("EE", szDest);
	cDurable.End();

	cDurable.Begin();
	AssertLongLongInt(16, cDurable.miPosition);
	AssertLongLongInt(16, cDurable.miLength);

	iResult = cDurable.Write(0, sz4, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertLongLongInt(4, cDurable.miPosition);
	iResult = cDurable.Write(8, sz2, 2, 1);

	memset(szAll, 0, 17);
	iResult = cDurable.Read(0, szAll, 4, 4);
	AssertLongLongInt(4, iResult);
	AssertString("AAAABBBBCCCCEEEE", szAll);

	iResult = cDurable.Read(11, szAll, 3, 2);
	AssertLongLongInt(1, iResult);

	iResult = cDurable.Write(16, sz5, 1, 1);
	memset(szAll, 0, 17);
	iResult = cDurable.Read(11, szAll, 3, 2);
	AssertLongLongInt(2, iResult);
	AssertString("CEEEEF", szAll);

	cDurable.End();

	cDurable.Close();
	cDurable.Kill();

	cTextFile.Init();
	cTextFile.Read("Durable3\\WrittenFile.txt");
	AssertString("AAAABBBBCCCCEEEEF", cTextFile.Text());
	cTextFile.Kill();

	FastFunctionsKill();
	TypeConverterKill();

	cFileUtil.RemoveDir("Durable3");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFile(void)
{
	BeginTests();

	TestDurableFileInit();
	TestDurableFileWrite();
	TestComplexDurableFile();

	TestStatistics();
}


