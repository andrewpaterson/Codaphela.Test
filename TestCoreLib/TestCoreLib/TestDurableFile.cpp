#include "TestLib/Assert.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "CoreLib/DurableFile.h"
#include "CoreLib/DurableFileController.h"
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

	CDurableFile			cDurable;
	CFileUtil				cFileUtil;
	CDurableFileController	cController;

	cFileUtil.RemoveDir("Durable1");
	cFileUtil.MakeDir("Durable1");

	cController.Init("Durable1", "Durable1", TRUE);

	cDurable.Init(&cController, "Durable1\\TestFile.txt", "Durable1\\_TestFile.txt");
	cDurable.Open();

	cDurable.Begin();
	cDurable.End();

	cDurable.Close();
	cDurable.Kill();

	cController.Kill();

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

	CFileUtil				cFileUtil;
	CDurableFile			cDurable;
	filePos					iResult;
	CTextFile				cTextFile;
	CDurableFileController	cController;

	char			sz1[] = "In the age of chaos";
	char			sz2[] = " two factions battled";
	char			sz3[] = "undys";
	char			sz4[] = "In the age of undys two factions battled";

	cFileUtil.RemoveDir("Durable2");
	cFileUtil.MakeDir("Durable2");

	cController.Init("Durable2", "Durable2", TRUE);

	cDurable.Init(&cController, "Durable2\\WrittenFile.txt", "Durable2\\_WrittenFile.txt");
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

	cController.Kill();

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
void TestDurableFileComplex(void)
{
	FastFunctionsInit();
	TypeConverterInit();

	CFileUtil				cFileUtil;
	CDurableFile			cDurable;
	filePos					iResult;
	CTextFile				cTextFile;
	CDurableFileController	cController;

	char			szA[] = "AAAA";
	char			szB[] = "BBBB";
	char			szC[] = "CCDD";
	char			szE[] = "EEEE";
	char			szF[] = "FFFF";

	char			szDest[5];
	char			szAll[18];

	cFileUtil.RemoveDir("Durable3");
	cFileUtil.MakeDir("Durable3");

	cController.Init("Durable3", "Durable3", TRUE);

	cDurable.Init(&cController, "Durable3\\WrittenFile.txt", "Durable3\\_WrittenFile.txt");
	cDurable.Open();

	cDurable.Begin();

	iResult = cDurable.Write(4, szB, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertLongLongInt(8, cDurable.miPosition);
	AssertLongLongInt(8, cDurable.miLength);

	iResult = cDurable.Write(10, szC, 2, 2);
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

	iResult = cDurable.Write(12, szE, 1, 4);
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
	cDurable.Rewrite();

	cDurable.Begin();
	AssertLongLongInt(16, cDurable.miPosition);
	AssertLongLongInt(16, cDurable.miLength);

	iResult = cDurable.Write(0, szA, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertLongLongInt(4, cDurable.miPosition);
	iResult = cDurable.Write(8, szC, 2, 1);

	memset(szAll, 0, 18);
	iResult = cDurable.Read(0, szAll, 4, 4);
	AssertLongLongInt(4, iResult);
	AssertString("AAAABBBBCCCCEEEE", szAll);

	memset(szAll, 0, 18);
	iResult = cDurable.Read(11, szAll, 3, 2);
	AssertLongLongInt(1, iResult);
	AssertString("CEEEE", szAll);

	memset(szAll, 0, 18);
	iResult = cDurable.Write(16, szF, 1, 1);
	iResult = cDurable.Read(11, szAll, 3, 2);
	AssertLongLongInt(2, iResult);
	AssertString("CEEEEF", szAll);

	cDurable.End();
	cDurable.Rewrite();

	cDurable.Close();
	cDurable.Kill();

	cController.Kill();

	cTextFile.Init();
	cTextFile.Read("Durable3\\WrittenFile.txt");
	AssertString("AAAABBBBCCCCEEEEF", cTextFile.Text());
	cTextFile.Kill();

	cTextFile.Init();
	cTextFile.Read("Durable3\\_WrittenFile.txt");
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
	TestDurableFileComplex();

	TestStatistics();
}

