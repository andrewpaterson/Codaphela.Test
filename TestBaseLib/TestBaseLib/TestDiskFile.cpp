#include "BaseLib/DiskFile.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TextFile.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDiskFileComplex(void)
{
	CFileUtil		cFileUtil;
	CDiskFile		cDiskFile;
	filePos			iResult;
	CFileBasic		cFile;

	char			szA[] = "AAAA";
	char			szB[] = "BBBB";
	char			szC[] = "CCDD";
	char			szE[] = "EEEE";
	char			szF[] = "FFFF";

	char			szDest[5];
	char			szAll[18];

	cFileUtil.TouchDir("Output");
	cFileUtil.Delete("Output" _FS_ "Test1.txt");

	cDiskFile.Init("Output" _FS_ "Test1.txt");
	cFile.Init(&cDiskFile);
	cFile.Open(EFM_ReadWrite_Create);

	AssertTrue(cFile.Seek(4));
	iResult = cFile.Write(szB, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertLongLongInt(8, cDiskFile.Tell());
	AssertLongLongInt(8, cDiskFile.Size());

	AssertTrue(cFile.Seek(10));
	iResult = cDiskFile.Write(szC, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertLongLongInt(14, cDiskFile.Tell());
	AssertLongLongInt(14, cDiskFile.Size());

	memset(szDest, 0, 5);
	AssertTrue(cFile.Seek(8));
	iResult = cDiskFile.Read(szDest, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertString("", szDest);
	AssertString("CC", &szDest[2]);
	AssertLongLongInt(12, cDiskFile.Tell());
	AssertLongLongInt(12, cDiskFile.Tell());
	AssertLongLongInt(14, cDiskFile.Size());

	AssertTrue(cFile.Seek(12));
	iResult = cDiskFile.Write(szE, 1, 4);
	AssertLongLongInt(4, iResult);
	AssertLongLongInt(16, cDiskFile.Tell());
	AssertLongLongInt(16, cDiskFile.Size());

	memset(szDest, 0, 5);
	AssertTrue(cFile.Seek(14));
	iResult = cDiskFile.Read(szDest, 2, 2);
	AssertLongLongInt(1, iResult);
	AssertString("EE", szDest);
	AssertLongLongInt(16, cDiskFile.Tell());
	AssertLongLongInt(16, cDiskFile.Tell());
	AssertLongLongInt(16, cDiskFile.Size());

	AssertTrue(cFile.Flush());
	AssertTrue(cFile.Close());
	cDiskFile.Kill();
	cFile.Kill();

	cDiskFile.Init("Output" _FS_ "Test1.txt");
	cFile.Init(&cDiskFile);
	cFile.Open(EFM_ReadWrite);

	AssertString("Output" _FS_ "Test1.txt", cDiskFile.GetFilename());
	AssertLongLongInt(0, cDiskFile.Tell());
	AssertLongLongInt(16, cDiskFile.Size());

	AssertLongLongInt(0, cDiskFile.Tell());
	AssertLongLongInt(16, cDiskFile.Size());
	AssertLongLongInt(0, cDiskFile.Tell());
	AssertLongLongInt(16, cDiskFile.Size());

	AssertTrue(cFile.Seek(0));
	iResult = cDiskFile.Write(szA, 2, 2);
	AssertLongLongInt(2, iResult);
	AssertLongLongInt(4, cDiskFile.Tell());
	AssertTrue(cFile.Seek(8));
	iResult = cDiskFile.Write(szC, 2, 1);

	memset(szAll, 0, 18);
	AssertTrue(cFile.Seek(0));
	iResult = cDiskFile.Read(szAll, 4, 4);
	AssertLongLongInt(4, iResult);
	AssertString("AAAABBBBCCCCEEEE", szAll);

	memset(szAll, 0, 18);
	AssertTrue(cFile.Seek(11));
	iResult = cDiskFile.Read(szAll, 3, 2);
	AssertLongLongInt(1, iResult);
	AssertString("CEEEE", szAll);

	memset(szAll, 0, 18);
	AssertTrue(cFile.Seek(16));
	iResult = cDiskFile.Write(szF, 1, 1);
	AssertTrue(cFile.Seek(11));
	iResult = cDiskFile.Read(szAll, 3, 2);
	AssertLongLongInt(2, iResult);
	AssertString("CEEEEF", szAll);

	AssertTrue(cFile.Flush());
	AssertTrue(cFile.Close());
	cDiskFile.Kill();
	cFile.Kill();

	AssertFileString("Output" _FS_ "Test1.txt", "AAAABBBBCCCCEEEEF");
		
	cFileUtil.Delete("Output" _FS_ "Test1.txt");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDiskFileTruncate(void)
{
	CDiskFile	cDiskFile;
	CFileUtil	cFileUtil;
	char		szHello[] = "Hello";
	BOOL		bResult;
	filePos		iResult;

	cFileUtil.TouchDir("Output");

	cFileUtil.Delete("Output" _FS_ "Test2.txt");

	cDiskFile.Init("Output" _FS_ "Test2.txt");
	bResult = cDiskFile.Open(EFM_Write_Create);
	AssertTrue(bResult);
	iResult = (int)cDiskFile.Write(szHello, strlenFilePos(szHello) + 1, 1);
	AssertLongLongInt(1, iResult);
	bResult = cDiskFile.Truncate(4);
	bResult = cDiskFile.Close();

	AssertTrue(bResult);
	cDiskFile.Kill();

	cFileUtil.Delete("Output" _FS_ "Test2.txt");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDiskFileWrite(void)
{
	CFileUtil	cFileUtil;
	CFileBasic	cFile;
	CTextFile	cText;

	cFileUtil.TouchDir("Output");
	AssertTrue(cFileUtil.Delete("Output" _FS_ "Test3.txt"));

	cFile.Init(DiskFile("Output" _FS_ "Test3.txt"));
	AssertTrue(cFile.Open(EFM_Write_Create));
	AssertLongLongInt(2, cFile.Write("ab", 1, 2));
	AssertLongLongInt(2, cFile.Write("cd", 1, 2));
	AssertTrue(cFile.Close());
	cFile.Kill();

	cText.Init();
	AssertTrue(cText.Read("Output" _FS_ "Test3.txt"));
	AssertString("abcd", cText.mcText.Text());
	cText.Kill();

	cFile.Init(DiskFile("Output" _FS_ "Test3.txt"));
	AssertTrue(cFile.Open(EFM_Write_Create));
	AssertLongLongInt(9, cFile.Write("abcdefghi", 1, 9));
	AssertLongLongInt(5, cFile.Write("jklmn", 1, 5));
	AssertTrue(cFile.Close());
	cFile.Kill();

	cText.Init();
	AssertTrue(cText.Read("Output" _FS_ "Test3.txt"));
	AssertString("abcdefghijklmn", cText.mcText.Text());
	cText.Kill();

	cFile.Init(DiskFile("Output" _FS_ "Test3.txt"));
	AssertTrue(cFile.Open(EFM_ReadWrite));
	AssertTrue(cFile.Seek(4));
	AssertLongLongInt(1, cFile.Write("xyz", 3, 1));
	AssertTrue(cFile.Close());
	cFile.Kill();

	cText.Init();
	AssertTrue(cText.Read("Output" _FS_ "Test3.txt"));
	AssertString("abcdxyzhijklmn", cText.mcText.Text());
	cText.Kill();

	cFile.Init(DiskFile("Output" _FS_ "Test3.txt"));
	AssertTrue(cFile.Open(EFM_ReadWrite));
	AssertTrue(cFile.Seek(0, EFSO_END));
	AssertLongLongInt(1, cFile.Write("opqrst", 6, 1));
	AssertTrue(cFile.Seek(0));
	AssertLongLongInt(1, cFile.Write("123456", 6, 1));
	AssertLongLongInt(1, cFile.Write("78", 2, 1));
	AssertTrue(cFile.Close());
	cFile.Kill();

	cText.Init();
	AssertTrue(cText.Read("Output" _FS_ "Test3.txt"));
	AssertString("12345678ijklmnopqrst", cText.mcText.Text());
	cText.Kill();

	cFile.Init(DiskFile("Output" _FS_ "Test3.txt"));
	AssertTrue(cFile.Open(EFM_Write_Create));
	AssertLongLongInt(2, cFile.Write("ab", 1, 2));
	AssertLongLongInt(4, cFile.Write("cdef", 1, 4));
	AssertLongLongInt(2, cFile.Write("gh", 1, 2));
	AssertLongLongInt(20, cFile.GetFileLength());
	AssertTrue(cFile.Close());
	cFile.Kill();

	cText.Init();
	AssertTrue(cText.Read("Output" _FS_ "Test3.txt"));
	AssertString("abcdefghijklmnopqrst", cText.mcText.Text());
	cText.Kill();

	AssertTrue(cFileUtil.Delete("Output" _FS_ "Test3.txt"));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDiskFile(void)
{
	BeginTests();

	TestDiskFileWrite();
	TestDiskFileComplex();
	TestDiskFileTruncate();

	TestStatistics();
}

