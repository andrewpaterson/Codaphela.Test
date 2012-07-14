#include "TestDurableSet.h"
#include "TestLib/Assert.h"
#include "BaseLib/FastFunctions.h"
#include "CoreLib/DurableSet.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/FileBasic.h"
#include "BaseLib/TextFile.h"
#include "CoreLib/TypeConverter.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertFileContents(char* szFileName, char* szExpectedContents)
{
	CTextFile		cTextFile;

	cTextFile.Init();
	AssertBool(TRUE, cTextFile.Read(szFileName));
	AssertString(szExpectedContents, cTextFile.Text());
	cTextFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileRecovery(void)
{
	CFileUtil cFileUtil;

	FastFunctionsInit();
	TypeConverterInit();
	cFileUtil.RemoveDir("Durable");
	cFileUtil.MakeDir("Durable");

	CDurableSet		cDurableSet;
	CDurableFile	cDurableFile1;
	CDurableFile	cDurableFile2;
	CDurableFile	cDurableFile3;
	CDurableFile	cDurableFile4;

	//////////////////////////////////////////////////////////////////////////

	cDurableFile1.Init(TRUE, "Durable\\1.txt", "Durable\\_1.txt");	cDurableFile1.Open();
	cDurableFile2.Init(TRUE, "Durable\\2.txt", "Durable\\_2.txt");	cDurableFile2.Open();
	cDurableFile3.Init(TRUE, "Durable\\3.txt", "Durable\\_3.txt");	cDurableFile3.Open();
	cDurableFile4.Init(TRUE, "Durable\\4.txt", "Durable\\_4.txt");	cDurableFile4.Open();

	cDurableSet.Init("Durable\\Mark1.Write", "Durable\\Mark2.Rewrite");
	cDurableSet.Add(&cDurableFile1);
	cDurableSet.Add(&cDurableFile2);
	cDurableSet.Add(&cDurableFile3);
	cDurableSet.Add(&cDurableFile4);

	cDurableSet.Begin();
	cDurableFile1.Write("Dulcedo ", 8, 1);
	cDurableFile1.Write("Cogitationis", 13, 1);

	cDurableFile4.Write("Age ", 4, 1);
	cDurableFile4.Write("Chaos ", 6, 1);
	cDurableFile4.Write("Battle ", 7, 1);
	cDurableFile4.Write("Orcs ", 5, 1);
	cDurableFile4.Write("Humans", 7, 1);

	cDurableFile3.Write(4, "BBBB", 4, 1);
	cDurableFile3.Write(0, "AAAA", 4, 1);
	cDurableFile3.Write(12, "DDDD", 4, 1);
	cDurableFile3.Write(8, "CCCC", 4, 1);

	cDurableSet.End();
	cDurableSet.Kill();

	cDurableFile1.Close(); 
	cDurableFile2.Close(); 
	cDurableFile3.Close(); 
	cDurableFile4.Close(); 

	AssertFileContents("Durable\\1.txt", "Dulcedo Cogitationis");
	AssertFileContents("Durable\\_1.txt", "Dulcedo Cogitationis");
	AssertFileContents("Durable\\3.txt", "AAAABBBBCCCCDDDD");
	AssertFileContents("Durable\\_3.txt", "AAAABBBBCCCCDDDD");
	AssertFileContents("Durable\\4.txt", "Age Chaos Battle Orcs Humans");
	AssertFileContents("Durable\\_4.txt", "Age Chaos Battle Orcs Humans");

	AssertBool(FALSE, cFileUtil.Exists("Durable\\2.txt"));
	AssertBool(FALSE, cFileUtil.Exists("Durable\\_2.txt"));

	AssertBool(FALSE, cFileUtil.Exists("Durable\\Mark1.Write"));
	AssertBool(FALSE, cFileUtil.Exists("Durable\\Mark2.Rewrite"));

	//////////////////////////////////////////////////////////////////////////

	cFileUtil.Touch("Durable\\Mark1.Write");
	cFileUtil.Delete("Durable\\3.txt");
	cFileUtil.Delete("Durable\\4.txt");

	cDurableFile1.Init(TRUE, "Durable\\1.txt", "Durable\\_1.txt");	cDurableFile1.Open();
	cDurableFile2.Init(TRUE, "Durable\\2.txt", "Durable\\_2.txt");	cDurableFile2.Open();
	cDurableFile3.Init(TRUE, "Durable\\3.txt", "Durable\\_3.txt");	cDurableFile3.Open();
	cDurableFile4.Init(TRUE, "Durable\\4.txt", "Durable\\_4.txt");	cDurableFile4.Open();

	cDurableSet.Init("Durable\\Mark1.Write", "Durable\\Mark2.Rewrite");
	cDurableSet.Add(&cDurableFile1);
	cDurableSet.Add(&cDurableFile2);
	cDurableSet.Add(&cDurableFile3);
	cDurableSet.Add(&cDurableFile4);

	cDurableSet.Recover();
	cDurableSet.Kill();

	cDurableFile1.Close(); 
	cDurableFile2.Close(); 
	cDurableFile3.Close(); 
	cDurableFile4.Close(); 

	AssertFileContents("Durable\\1.txt", "Dulcedo Cogitationis");
	AssertFileContents("Durable\\_1.txt", "Dulcedo Cogitationis");
	AssertFileContents("Durable\\3.txt", "AAAABBBBCCCCDDDD");
	AssertFileContents("Durable\\_3.txt", "AAAABBBBCCCCDDDD");
	AssertFileContents("Durable\\4.txt", "Age Chaos Battle Orcs Humans");
	AssertFileContents("Durable\\_4.txt", "Age Chaos Battle Orcs Humans");

	AssertBool(FALSE, cFileUtil.Exists("Durable\\2.txt"));
	AssertBool(FALSE, cFileUtil.Exists("Durable\\_2.txt"));

	AssertBool(FALSE, cFileUtil.Exists("Durable\\Mark1.Write"));
	AssertBool(FALSE, cFileUtil.Exists("Durable\\Mark2.Rewrite"));

	//////////////////////////////////////////////////////////////////////////

	cFileUtil.Touch("Durable\\Mark1.Write");
	cFileUtil.Touch("Durable\\Mark2.Rewrite");
	cFileUtil.Delete("Durable\\_1.txt");
	cFileUtil.Delete("Durable\\_4.txt");

	cDurableFile1.Init(TRUE, "Durable\\1.txt", "Durable\\_1.txt");	cDurableFile1.Open();
	cDurableFile2.Init(TRUE, "Durable\\2.txt", "Durable\\_2.txt");	cDurableFile2.Open();
	cDurableFile3.Init(TRUE, "Durable\\3.txt", "Durable\\_3.txt");	cDurableFile3.Open();
	cDurableFile4.Init(TRUE, "Durable\\4.txt", "Durable\\_4.txt");	cDurableFile4.Open();

	cDurableSet.Init("Durable\\Mark1.Write", "Durable\\Mark2.Rewrite");
	cDurableSet.Add(&cDurableFile1);
	cDurableSet.Add(&cDurableFile2);
	cDurableSet.Add(&cDurableFile3);
	cDurableSet.Add(&cDurableFile4);

	cDurableSet.Recover();
	cDurableSet.Kill();

	cDurableFile1.Close(); 
	cDurableFile2.Close(); 
	cDurableFile3.Close(); 
	cDurableFile4.Close(); 

	AssertFileContents("Durable\\1.txt", "Dulcedo Cogitationis");
	AssertFileContents("Durable\\_1.txt", "Dulcedo Cogitationis");
	AssertFileContents("Durable\\3.txt", "AAAABBBBCCCCDDDD");
	AssertFileContents("Durable\\_3.txt", "AAAABBBBCCCCDDDD");
	AssertFileContents("Durable\\4.txt", "Age Chaos Battle Orcs Humans");
	AssertFileContents("Durable\\_4.txt", "Age Chaos Battle Orcs Humans");

	AssertBool(FALSE, cFileUtil.Exists("Durable\\2.txt"));
	AssertBool(FALSE, cFileUtil.Exists("Durable\\_2.txt"));

	AssertBool(FALSE, cFileUtil.Exists("Durable\\Mark1.Write"));
	AssertBool(FALSE, cFileUtil.Exists("Durable\\Mark2.Rewrite"));

	//////////////////////////////////////////////////////////////////////////

	cFileUtil.RemoveDir("Durable");
	FastFunctionsKill();
	TypeConverterKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableSet(void)
{
	BeginTests();

	TestDurableFileRecovery();

	TestStatistics();
}

