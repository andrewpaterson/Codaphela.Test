#include "BaseLib/Logger.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/FileBasic.h"
#include "BaseLib/PointerRemapper.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/DurableFile.h"
#include "CoreLib/DurableFileController.h"
#include "TestLib/Assert.h"

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* SetDurable(char* szRewrite, BOOL bDurable)
{
	if (bDurable)
	{
		return szRewrite;
	}
	else
	{
		return NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileInit(BOOL bDurable)
{
	CDurableFile			cDurableFile;
	CFileUtil				cFileUtil;
	CDurableFileController	cController;
	char					szDirectory[] = "Durable1";
	char					szRewrite[] = "_Durable1";

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewrite, NULL);

	cController.Init(szDirectory, SetDurable(szRewrite, bDurable));
	cDurableFile.Init(&cController, "Durable1" _FS_ "TestFile.txt", "_Durable1" _FS_ "_TestFile.txt");
	cController.Begin();

	cController.End();
	cDurableFile.Kill();
	cController.Kill();

	cFileUtil.RemoveDirs(szDirectory, szRewrite, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileWrite(BOOL bDurable)
{
	CFileUtil				cFileUtil;
	CDurableFile			cDurableFile;
	filePos					iResult;
	CDurableFileController	cController;
	char					szDirectory[] = "Durable2";
	char					szRewrite[] = "_Durable2";

	char			sz1[] = "In the age of chaos";
	char			sz2[] = " two factions battled";
	char			sz3[] = "undys";
	char			sz4[] = "In the age of undys two factions battled";

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewrite, NULL);

	cController.Init(szDirectory, SetDurable(szRewrite, bDurable));
	cDurableFile.Init(&cController, "Durable2" _FS_ "WrittenFile.txt", "_Durable2" _FS_ "_WrittenFile.txt");
	cController.Begin();

	AssertTrue(cController.IsBegun());
	AssertBool(bDurable, cController.IsDurable());
	AssertLongLongInt(0, cDurableFile.Tell());
	AssertLongLongInt(0, cDurableFile.Size());
	AssertInt(0, cDurableFile.GetNumWrites());

	iResult = cDurableFile.Write(sz1, (int)strlen(sz1), 1);
	AssertLongLongInt(1, iResult);
	AssertLongLongInt(19, cDurableFile.Tell());
	AssertLongLongInt(19, cDurableFile.Size());
	AssertTrue(cDurableFile.TestGetOpenedSinceBegin());
	AssertInt(1, cDurableFile.GetNumWrites());

	iResult = cDurableFile.Write(sz2, (int)strlen(sz2), 1);
	AssertLongLongInt(1, iResult);
	AssertLongLongInt(40, cDurableFile.Tell());
	AssertLongLongInt(40, cDurableFile.Size());
	AssertInt(1, cDurableFile.GetNumWrites());

	iResult = cDurableFile.Write(14, sz3, (int)strlen(sz3), 1);
	AssertLongLongInt(1, iResult);
	AssertLongLongInt(19, cDurableFile.Tell());
	AssertLongLongInt(40, cDurableFile.Size());
	AssertInt(1, cDurableFile.GetNumWrites());
	AssertMemory(sz4, (char*)cDurableFile.GetWriteData(0), 40);

	cController.End();
	AssertFalse(cDurableFile.TestGetOpenedSinceBegin());
	AssertInt(0, cDurableFile.GetNumWrites());
	AssertFalse(cDurableFile.IsBegun());

	AssertFalse(cDurableFile.IsOpen());

	cDurableFile.Kill();
	cController.Kill();

	AssertFileString("Durable2" _FS_ "WrittenFile.txt", sz4);

	cFileUtil.RemoveDirs(szDirectory, szRewrite, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileCloseOpen(BOOL bDurable)
{
	CFileUtil				cFileUtil;
	CDurableFile			cDurableFile;
	filePos					iResult;
	CDurableFileController	cController;
	char					szDirectory[] = "Durable7";
	char					szRewrite[] = "_Durable7";

	char			szA[] = "AAAA";
	char			szB[] = "BBBB";
	char			szDest[8] = "";

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewrite, NULL);

	cController.Init(szDirectory, SetDurable(szRewrite, bDurable));
	cDurableFile.Init(&cController, "Durable7" _FS_ "WrittenFile.txt", "_Durable7" _FS_ "_WrittenFile.txt");
	cController.Begin();

	iResult = cDurableFile.Write(4, szA, 4, 1);
	AssertLongLongInt(1, iResult);
	AssertLongLongInt(8, cDurableFile.Tell());
	AssertLongLongInt(8, cDurableFile.Size());
	iResult = cDurableFile.Write(0, szB, 4, 1);

	cController.End();
	cDurableFile.Kill();

	cDurableFile.Init(&cController, "Durable7" _FS_ "WrittenFile.txt", "_Durable7" _FS_ "_WrittenFile.txt");
	cController.Begin();

	AssertLongLongInt(8, cDurableFile.Size());
	iResult = cDurableFile.Read(szDest, 4, 2);
	AssertLongLongInt(2, iResult);
	AssertLongLongInt(8, cDurableFile.Tell());

	cController.End();

	cFileUtil.RemoveDirs(szDirectory, szRewrite, NULL);
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileComplex(BOOL bDurable)
{
	CFileUtil				cFileUtil;
	CDurableFile			cDurableFile;
	filePos					iResult;
	CDurableFileController	cController;
	char					szDirectory[] = "Durable3";
	char					szRewrite[] = "_Durable3";

	char			szA[] = "AAAA";
	char			szB[] = "BBBB";
	char			szC[] = "CCDD";
	char			szE[] = "EEEE";
	char			szF[] = "FFFF";

	char			szDest[5];
	char			szAll[18];

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewrite, NULL);

	cController.Init(szDirectory, SetDurable(szRewrite, bDurable));
	cDurableFile.Init(&cController, "Durable3" _FS_ "WrittenFile.txt", "_Durable3" _FS_ "_WrittenFile.txt");
	cController.Begin();

	iResult = cDurableFile.Write(4, szB, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertTrue(cDurableFile.TestGetOpenedSinceBegin());
	AssertLongLongInt(8, cDurableFile.Tell());
	AssertLongLongInt(8, cDurableFile.Size());
	AssertInt(1, cDurableFile.GetNumWrites());

	iResult = cDurableFile.Write(10, szC, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertLongLongInt(14, cDurableFile.Tell());
	AssertLongLongInt(14, cDurableFile.Size());
	AssertInt(2, cDurableFile.GetNumWrites());

	memset(szDest, 0, 5);
	iResult = cDurableFile.Read(8, szDest, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertString("", szDest);
	AssertString("CC", &szDest[2]);
	AssertLongLongInt(12, cDurableFile.Tell());
	AssertLongLongInt(12, cDurableFile.Tell());
	AssertLongLongInt(14, cDurableFile.Size());
	AssertInt(2, cDurableFile.GetNumWrites());
	
	iResult = cDurableFile.Write(12, szE, 1, 4);
	AssertLongLongInt(4, iResult);
	AssertLongLongInt(16, cDurableFile.Tell());
	AssertLongLongInt(16, cDurableFile.Size());
	AssertInt(2, cDurableFile.GetNumWrites());

	memset(szDest, 0, 5);
	iResult = cDurableFile.Read(14, szDest, 2, 2);
	AssertLongLongInt(1, iResult);
	AssertString("EE", szDest);
	AssertLongLongInt(16, cDurableFile.Tell());
	AssertLongLongInt(16, cDurableFile.Tell());
	AssertLongLongInt(16, cDurableFile.Size());
	AssertInt(2, cDurableFile.GetNumWrites());

	AssertInt(1, cController.NumFiles());
	AssertString("Durable3" _FS_ "WrittenFile.txt", cDurableFile.GetFileName());

	cController.End();
	AssertFalse(cDurableFile.TestGetOpenedSinceBegin());
	AssertInt(0, cDurableFile.GetNumWrites());

	AssertInt(0, cController.NumFiles());

	cController.Begin();
	AssertString("Durable3" _FS_ "WrittenFile.txt", cDurableFile.GetFileName());
	AssertLongLongInt(0, cDurableFile.Tell());
	AssertLongLongInt(16, cDurableFile.Size());
	AssertInt(0, cDurableFile.GetNumWrites());
	AssertFalse(cDurableFile.TestGetOpenedSinceBegin());

	AssertLongLongInt(0, cDurableFile.Tell());
	AssertLongLongInt(16, cDurableFile.Size());
	AssertLongLongInt(0, cDurableFile.Tell());
	AssertLongLongInt(16, cDurableFile.Size());

	iResult = cDurableFile.Write(0, szA, 2, 2);
	AssertLongLongInt(2, iResult);
	if (bDurable) AssertLongLongInt(4, cDurableFile.Tell());
	iResult = cDurableFile.Write(8, szC, 2, 1);

	memset(szAll, 0, 18);
	iResult = cDurableFile.Read(0, szAll, 4, 4);
	AssertLongLongInt(4, iResult);
	AssertString("AAAABBBBCCCCEEEE", szAll);

	memset(szAll, 0, 18);
	iResult = cDurableFile.Read(11, szAll, 3, 2);
	AssertLongLongInt(1, iResult);
	AssertString("CEEEE", szAll);

	memset(szAll, 0, 18);
	iResult = cDurableFile.Write(16, szF, 1, 1);
	iResult = cDurableFile.Read(11, szAll, 3, 2);
	AssertLongLongInt(2, iResult);
	AssertString("CEEEEF", szAll);

	cController.End();
	cDurableFile.Kill();
	cController.Kill();

	AssertFileString("Durable3" _FS_ "WrittenFile.txt", "AAAABBBBCCCCEEEEF");

	if (bDurable) AssertFileString("_Durable3" _FS_ "_WrittenFile.txt", "AAAABBBBCCCCEEEEF");

	cFileUtil.RemoveDirs(szDirectory, szRewrite, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileRead(BOOL bDurable)
{
	CFileUtil				cFileUtil;
	CDurableFile			cDurableFile;
	filePos					iResult;
	CDurableFileController	cController;
	CTextFile				cTextFile;
	char					szDirectory[] = "Durable4";
	char					szRewrite[] = "_Durable4";
	char					szDest[2048];

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewrite, NULL);

	cTextFile.Init("Sea lions, like CLions of the holy see");
	cTextFile.Write("Durable4" _FS_ "ReadFile.txt");
	cTextFile.Write("Durable4" _FS_ "_ReadFile.txt");
	cTextFile.Kill();

	cController.Init(szDirectory, SetDurable(szRewrite, bDurable));
	cDurableFile.Init(&cController, "Durable4" _FS_ "ReadFile.txt", "_Durable4" _FS_ "_ReadFile.txt");
	cController.Begin();
	AssertFalse(cDurableFile.TestGetOpenedSinceBegin());
	AssertInt(0, cController.NumFiles());

	memset(szDest, 0, 10);
	iResult = cDurableFile.Read(szDest, 9, 1);
	AssertLongLongInt(1, iResult);
	AssertTrue(cDurableFile.TestGetOpenedSinceBegin());
	AssertInt(0, cDurableFile.GetNumWrites());
	AssertInt(1, cController.NumFiles());
	AssertString("Sea lions", szDest);
	AssertLongLongInt(9, cDurableFile.Tell());
	AssertLongLongInt(38, cDurableFile.Size());

	memset(szDest, 0, 2);
	iResult = cDurableFile.Read(szDest, 1, 1);
	AssertLongLongInt(1, iResult);
	AssertString(",", szDest);
	AssertLongLongInt(10, cDurableFile.Tell());
	AssertLongLongInt(38, cDurableFile.Size());

	memset(szDest, 0, 7);
	iResult = cDurableFile.Read(16, szDest, 2, 3);
	AssertLongLongInt(3, iResult);
	AssertString("CLions", szDest);
	AssertLongLongInt(22, cDurableFile.Tell());
	AssertLongLongInt(38, cDurableFile.Size());

	memset(szDest, 0, 4);
	iResult = cDurableFile.Read(35, szDest, 3, 1);
	AssertLongLongInt(1, iResult);
	AssertString("see", szDest);
	AssertLongLongInt(38, cDurableFile.Tell());
	AssertLongLongInt(38, cDurableFile.Size());

	memset(szDest, 0, 5);
	iResult = cDurableFile.Read(35, szDest, 4, 1);
	AssertLongLongInt(0, iResult);
	AssertString("see", szDest);
	AssertLongLongInt(35, cDurableFile.Tell());
	AssertLongLongInt(38, cDurableFile.Size());

	cController.End();
	AssertFalse(cDurableFile.TestGetOpenedSinceBegin());
	AssertInt(0, cDurableFile.GetNumWrites());
	AssertInt(0, cController.NumFiles());

	cDurableFile.Kill();
	cController.Kill();

	cFileUtil.RemoveDirs(szDirectory, szRewrite, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileWriteRound2(BOOL bDurable)
{
	CFileUtil				cFileUtil;
	CDurableFile			cDurableFile;
	filePos					iResult;
	CDurableFileController	cController;
	char					szDirectory[] = "Durable5";
	char					szRewrite[] = "_Durable5";
	char					szFileName[] = "Durable5" _FS_ "WrittenFile.txt";
	char					szRewriteName[] = "_Durable5" _FS_ "_WrittenFile.txt";

	char					sz1[] = "Lord";
	char					sz2[] = " ";
	char					sz3[] = "Commander";
	char					sz4[] = "Mothball";
	int						iLen1 = strlen(sz1);
	int						iLen2 = strlen(sz2);
	int						iLen3 = strlen(sz3);
	int						iLen4 = strlen(sz4);

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewrite, NULL);

	cController.Init(szDirectory, SetDurable(szRewrite, bDurable));
	cDurableFile.Init(&cController, szFileName, szRewriteName);
	cController.Begin();

	AssertFalse(cFileUtil.Exists(szFileName));
	AssertFalse(cFileUtil.Exists(szRewriteName));

	iResult = cDurableFile.Write(iLen1 + iLen2, sz3, 1, iLen3);
	AssertLongLongInt(9, iResult);
	AssertLongLongInt(14, cDurableFile.Tell());
	AssertLongLongInt(14, cDurableFile.Size());
	AssertTrue(cDurableFile.TestGetOpenedSinceBegin());
	if (bDurable) AssertInt(1, cDurableFile.GetNumWrites());
	AssertBool(!bDurable, cFileUtil.Exists(szFileName));

	iResult = cDurableFile.Write(iLen1, sz2, 1, iLen2);
	AssertLongLongInt(1, iResult);
	AssertLongLongInt(5, cDurableFile.Tell());
	AssertLongLongInt(14, cDurableFile.Size());
	AssertTrue(cDurableFile.TestGetOpenedSinceBegin());
	if (bDurable) AssertInt(1, cDurableFile.GetNumWrites());

	iResult = cDurableFile.Write(0, sz1, 1, iLen1);
	AssertLongLongInt(4, iResult);
	AssertLongLongInt(4, cDurableFile.Tell());
	AssertLongLongInt(14, cDurableFile.Size());
	AssertTrue(cDurableFile.TestGetOpenedSinceBegin());
	if (bDurable) AssertInt(1, cDurableFile.GetNumWrites());

	iResult = cDurableFile.Write(iLen1 + iLen2 + iLen3 + iLen2, sz4, 1, iLen4);
	AssertLongLongInt(8, iResult);
	AssertLongLongInt(23, cDurableFile.Tell());
	AssertLongLongInt(23, cDurableFile.Size());
	AssertTrue(cDurableFile.TestGetOpenedSinceBegin());
	if (bDurable) AssertInt(2, cDurableFile.GetNumWrites());

	iResult = cDurableFile.Write(iLen1 + iLen2 + iLen3, sz2, 1, iLen2);
	AssertLongLongInt(1, iResult);
	AssertLongLongInt(15, cDurableFile.Tell());
	AssertLongLongInt(23, cDurableFile.Size());
	AssertTrue(cDurableFile.TestGetOpenedSinceBegin());
	if (bDurable) AssertInt(1, cDurableFile.GetNumWrites());

	cController.End();
	AssertFileString(szFileName, "Lord Commander Mothball");
	if (bDurable) AssertFileString(szRewriteName, "Lord Commander Mothball");

	cDurableFile.Kill();
	cController.Kill();

	cFileUtil.RemoveDirs(szDirectory, szRewrite, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileReadRound2(BOOL bDurable)
{
	CFileUtil				cFileUtil;
	CDurableFile			cDurableFile;
	filePos					iResult;
	CDurableFileController	cController;
	char					szDirectory[] = "Durable6";
	char					szRewrite[] = "_Durable6";
	char					szDest[2048];

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewrite, NULL);

	cController.Init(szDirectory, SetDurable(szRewrite, bDurable));
	cDurableFile.Init(&cController, "Durable6" _FS_ "ReadFile.txt", "_Durable6" _FS_ "_ReadFile.txt");
	cController.Begin();
	AssertFalse(cDurableFile.TestGetOpenedSinceBegin());
	AssertInt(0, cController.NumFiles());

	memset(szDest, 0, 10);
	
	iResult = cDurableFile.Read(szDest, 9, 1);
	AssertLongLongInt(0, iResult);
	AssertTrue(cDurableFile.TestGetOpenedSinceBegin());
	AssertInt(0, cDurableFile.GetNumWrites());
	AssertInt(1, cController.NumFiles());
	AssertLongLongInt(0, cDurableFile.Tell());
	AssertLongLongInt(0, cDurableFile.Size());

	memset(szDest, 0, 10);

	iResult = cDurableFile.Read(EFSO_SET, 0, szDest, 9, 1);
	AssertLongLongInt(0, iResult);
	AssertTrue(cDurableFile.TestGetOpenedSinceBegin());
	AssertInt(0, cDurableFile.GetNumWrites());
	AssertInt(1, cController.NumFiles());
	AssertLongLongInt(0, cDurableFile.Tell());
	AssertLongLongInt(0, cDurableFile.Size());

	cController.End();
	cDurableFile.Kill();
	cController.Kill();

	cFileUtil.RemoveDirs(szDirectory, szRewrite, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFile(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestDurableFileInit(TRUE);
	TestDurableFileInit(FALSE);
	TestDurableFileWrite(TRUE);
	TestDurableFileWrite(FALSE);
	//TestDurableFileCloseOpen(TRUE);
	TestDurableFileCloseOpen(FALSE);
	TestDurableFileComplex(TRUE);
	TestDurableFileComplex(FALSE);
	TestDurableFileRead(TRUE);
	TestDurableFileRead(FALSE);
	TestDurableFileWriteRound2(TRUE);
	TestDurableFileWriteRound2(FALSE);
	TestDurableFileReadRound2(TRUE);
	TestDurableFileReadRound2(FALSE);

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

