#include "BaseLib/DiskFile.h"
#include "BaseLib/BufferedFile.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TextFile.h"
#include "TestLib/Assert.h"
#include "TestBufferedFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBufferedFileRead(void)
{
	CFileUtil	cFileUtil;
	CFileBasic	cFile;
	CTextFile	cText;
	char		sz[20];
	char		c;
	int			iCount;
	int			i;
	char		szExpected[20];

	cFileUtil.Delete("Test.txt");

	cText.Init();
	cText.mcText.Append("abcdefghijk");
	cText.Write("Test.txt");
	cText.Kill();

	cFile.Init(BufferedFile(DiskFile("Test.txt"), 3));

	cFile.Open(EFM_Read);

	for (c = 'a'; c <= 'k'; c++)
	{
		AssertFalse(cFile.IsEndOfFile());
		memset(sz, 0, 20);
		iCount = (int)cFile.Read(sz, 1, 1);
		AssertChar(c, sz[0]);
		AssertChar(0, sz[1]);
		AssertInt(1, iCount);
	}
	AssertTrue(cFile.IsEndOfFile());

	cFile.Seek(0);

	szExpected[2] = 0;
	for (i = 0; i < 5; i++)
	{
		AssertFalse(cFile.IsEndOfFile());
		memset(sz, 0, 20);
		iCount = (int)cFile.Read(sz, 1, 2);
		szExpected[0] = 'a' + i*2;
		szExpected[1] = 'b' + i*2;
		AssertString(szExpected, sz);
		AssertInt(2, iCount);
	}
	AssertFalse(cFile.IsEndOfFile());
	memset(sz, 0, 20);
	iCount = (int)cFile.Read(sz, 1, 2);
	AssertString("k", sz);
	AssertInt(1, iCount);
	AssertTrue(cFile.IsEndOfFile());

	cFile.Seek(0);

	szExpected[3] = 0;
	for (i = 0; i < 3; i++)
	{
		AssertFalse(cFile.IsEndOfFile());
		memset(sz, 0, 20);
		iCount = (int)cFile.Read(sz, 1, 3);
		szExpected[0] = 'a' + i*3;
		szExpected[1] = 'b' + i*3;
		szExpected[2] = 'c' + i*3;
		AssertString(szExpected, sz);
		AssertInt(3, iCount);
	}
	AssertFalse(cFile.IsEndOfFile());
	memset(sz, 0, 20);
	iCount = (int)cFile.Read(sz, 1, 3);
	AssertString("jk", sz);
	AssertInt(2, iCount);
	AssertTrue(cFile.IsEndOfFile());

	cFile.Kill();

	cFileUtil.Delete("Test.txt");
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBufferedFileWrite(void)
{
	CFileUtil	cFileUtil;
	CFileBasic	cFile;
	CTextFile	cText;

	cFileUtil.Delete("Test.txt");

	cFile.Init(BufferedFile(DiskFile("Test.txt"), 3));
	cFile.Open(EFM_Write_Create);
	cFile.Write("ab", 1, 2);
	cFile.Write("cd", 1, 2);
	cFile.Close();
	cFile.Kill();

	cText.Init();
	cText.Read("Test.txt");
	AssertString("abcd", cText.mcText.Text());
	cText.Kill();

	cFile.Init(BufferedFile(DiskFile("Test.txt"), 5));
	cFile.Open(EFM_Write_Create);
	cFile.Write("abcdefghi", 1, 9);
	cFile.Write("jklmn", 1, 5);
	cFile.Close();
	cFile.Kill();

	cText.Init();
	cText.Read("Test.txt");
	AssertString("abcdefghijklmn", cText.mcText.Text());
	cText.Kill();

	cFile.Init(BufferedFile(DiskFile("Test.txt"), 5));
	cFile.Open(EFM_ReadWrite);
	cFile.Seek(4);
	cFile.Write("xyz", 3, 1);
	cFile.Close();
	cFile.Kill();

	cText.Init();
	cText.Read("Test.txt");
	AssertString("abcdxyzhijklmn", cText.mcText.Text());
	cText.Kill();

	cFile.Init(BufferedFile(DiskFile("Test.txt"), 8));
	cFile.Open(EFM_ReadWrite);
	cFile.Seek(0, EFSO_END);
	cFile.Write("opqrst", 6, 1);
	cFile.Seek(0);
	cFile.Write("123456", 6, 1);
	cFile.Write("78", 2, 1);
	cFile.Close();
	cFile.Kill();

	cText.Init();
	cText.Read("Test.txt");
	AssertString("12345678ijklmnopqrst", cText.mcText.Text());
	cText.Kill();

	cFile.Init(BufferedFile(DiskFile("Test.txt"), 3));
	cFile.Open(EFM_Write_Create);
	cFile.Write("ab", 1, 2);
	cFile.Write("cdef", 1, 4);
	cFile.Write("gh", 1, 2);
	cFile.Close();
	cFile.Kill();

	cText.Init();
	cText.Read("Test.txt");
	AssertString("abcdefgh", cText.mcText.Text());
	cText.Kill();

	cFileUtil.Delete("Test.txt");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBufferedFileReadWrite(void)
{
	CFileUtil	cFileUtil;
	CFileBasic	cFile;
	CTextFile	cText;
	char		sz[20];

	cFileUtil.Delete("Test.txt");

	cFile.Init(BufferedFile(DiskFile("Test.txt"), 3));
	cFile.Open(EFM_ReadWrite_Create);
	cFile.Write("abcdefghijklmn", 1, 14);
	cFile.Write("op", 1, 2);
	cFile.Seek(3);
	memset(sz, 0, 20);
	cFile.Read(sz, 2, 1);
	AssertString("de", sz);
	cFile.Read(sz, 2, 1);
	AssertString("fg", sz);
	cFile.Write("12", 2, 1);
	cFile.Read(sz, 2, 1);
	AssertString("jk", sz);
	cFile.Write("34", 2, 1);
	cFile.Read(sz, 2, 1);
	AssertString("no", sz);
	cFile.Seek(2);
	cFile.Write("XY", 2, 1);
	cFile.Read(sz, 1, 3);
	AssertString("efg", sz);
	cFile.Close();
	cFile.Kill();

	cText.Init();
	cText.Read("Test.txt");
	AssertString("abXYefg12jk34nop", cText.mcText.Text());
	cText.Kill();

	cFileUtil.Delete("Test.txt");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBufferedFile(void)
{
	BeginTests();

	TestBufferedFileRead();
	TestBufferedFileWrite();
	TestBufferedFileReadWrite();

	TestStatistics();
}

