#include "BaseLib/Logger.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/FileBasic.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/DurableFile.h"
#include "CoreLib/DurableSet.h"
#include "CoreLib/DurableFileController.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileControllerDirectoryCreation(void)
{
	CDurableFileController	cController;
	CDurableFile			cDurableFile;
	char					szDirectory[] = "Output" _FS_ "Durable2" _FS_ "Write";
	char					szRewrite[] = "Output" _FS_ "Durable2" _FS_ "Rewrite";
	CFileUtil				cFileUtil;

	cFileUtil.RemoveDir("Output" _FS_ "Durable2");

	cController.Init(szDirectory, szRewrite);

	cDurableFile.Init(&cController, "Sub" _FS_ "Test.txt", "Sub" _FS_ "Test.txt");

	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable2" _FS_ "Write" _FS_ "Sub" _FS_ "Test.txt"));
	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable2" _FS_ "Rewrite" _FS_ "Sub" _FS_ "Test.txt"));

	cController.Begin();
	cController.End();
	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable2" _FS_ "Write" _FS_ "Sub" _FS_ "Test.txt"));
	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable2" _FS_ "Rewrite" _FS_ "Sub" _FS_ "Test.txt"));


	cController.Begin();
	cDurableFile.Write("Conan", 5, 1);
	cController.End();
	AssertBool(true, cFileUtil.Exists("Output" _FS_ "Durable2" _FS_ "Write" _FS_ "Sub" _FS_ "Test.txt"));
	AssertBool(true, cFileUtil.Exists("Output" _FS_ "Durable2" _FS_ "Rewrite" _FS_ "Sub" _FS_ "Test.txt"));

	cDurableFile.Kill();
	cController.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Durable2");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileControllerRecovery(void)
{
	CFileUtil				cFileUtil;
	CDurableFileController	cController;
	CDurableFile			cDurableFile1;
	CDurableFile			cDurableFile2;
	CDurableFile			cDurableFile3;
	CDurableFile			cDurableFile4;
	bool					bResult;
	char					szDirectory[] = "Output" _FS_ "Durable1" _FS_ "Write";
	char					szRewrite[] = "Output" _FS_ "Durable1" _FS_ "Rewrite";

	cFileUtil.RemoveDir("Output" _FS_ "Durable1");

	cController.Init(szDirectory, szRewrite);

	cDurableFile1.Init(&cController, "1.txt", "1.txt");
	cDurableFile2.Init(&cController, "2.txt", "2.txt");
	cDurableFile3.Init(&cController, "3.txt", "3.txt");
	cDurableFile4.Init(&cController, "4.txt", "4.txt");

	cController.Begin();
	cDurableFile1.Write("Dulcedo ", 8, 1);
	cDurableFile1.Write("Cogitationis", 12, 1);

	//Write some date to the files.
	cDurableFile4.Write("Age ", 4, 1);
	cDurableFile4.Write("Chaos ", 6, 1);
	cDurableFile4.Write("Battle ", 7, 1);
	cDurableFile4.Write("Orcs ", 5, 1);
	cDurableFile4.Write("Humans", 6, 1);

	cDurableFile3.Write(4, "BBBB", 4, 1);
	cDurableFile3.Write(0, "AAAA", 4, 1);
	cDurableFile3.Write(12, "DDDD", 4, 1);
	cDurableFile3.Write(8, "CCCC", 4, 1);

	cController.End();
	cDurableFile1.Kill();
	cDurableFile2.Kill();
	cDurableFile3.Kill();
	cDurableFile4.Kill();
	cController.Kill();

	AssertFileString("Output" _FS_ "Durable1" _FS_ "Write" _FS_ "1.txt", "Dulcedo Cogitationis");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "1.txt", "Dulcedo Cogitationis");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Write" _FS_ "3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Write" _FS_ "4.txt", "Age Chaos Battle Orcs Humans");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "4.txt", "Age Chaos Battle Orcs Humans");

	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Write" _FS_ "2.txt"));
	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "2.txt"));

	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Write" _FS_ "Mark1.Write"));
	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "Mark2.Rewrite"));

	//////////////////////////////////////////////////////////////////////////

	cController.Init(szDirectory, szRewrite);

	cDurableFile1.Init(&cController, "1.txt", "1.txt");
	cDurableFile2.Init(&cController, "2.txt", "2.txt");
	cDurableFile3.Init(&cController, "3.txt", "3.txt");
	cDurableFile4.Init(&cController, "4.txt", "4.txt");

	//Recovery should do nothing as the files are consistent.
	bResult = cController.Recover(&cDurableFile1, &cDurableFile2, &cDurableFile3, &cDurableFile4, NULL);
	AssertTrue(bResult);

	cDurableFile1.Kill();
	cDurableFile2.Kill();
	cDurableFile3.Kill();
	cDurableFile4.Kill();
	cController.Kill();

	AssertFileString("Output" _FS_ "Durable1" _FS_ "Write" _FS_ "1.txt", "Dulcedo Cogitationis");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "1.txt", "Dulcedo Cogitationis");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Write" _FS_ "3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Write" _FS_ "4.txt", "Age Chaos Battle Orcs Humans");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "4.txt", "Age Chaos Battle Orcs Humans");

	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Write" _FS_ "2.txt"));
	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "2.txt"));

	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Write" _FS_ "Mark1.Write"));
	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "Mark2.Rewrite"));

	//////////////////////////////////////////////////////////////////////////

	cFileUtil.Touch("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "Mark1.Write");
	cFileUtil.Delete("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "3.txt");
	cFileUtil.Delete("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "4.txt");

	bResult = cController.Init(szDirectory, szRewrite);
	AssertFalse(bResult);

	cDurableFile1.Init(&cController, "1.txt", "1.txt");
	cDurableFile2.Init(&cController, "2.txt", "2.txt");
	cDurableFile3.Init(&cController, "3.txt", "3.txt");
	cDurableFile4.Init(&cController, "4.txt", "4.txt");

	//Recovery should copy 3.txt and 4.txt back again.
	bResult = cController.Recover(&cDurableFile1, &cDurableFile2, &cDurableFile3, &cDurableFile4, NULL);
	AssertTrue(bResult);

	cDurableFile1.Kill();
	cDurableFile2.Kill();
	cDurableFile3.Kill();
	cDurableFile4.Kill();
	cController.Kill();

	AssertFileString("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "1.txt", "Dulcedo Cogitationis");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "1.txt", "Dulcedo Cogitationis");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "4.txt", "Age Chaos Battle Orcs Humans");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "4.txt", "Age Chaos Battle Orcs Humans");

	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "2.txt"));
	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "2.txt"));

	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "Mark1.Write"));
	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "Mark2.Rewrite"));

	//////////////////////////////////////////////////////////////////////////

	cFileUtil.Touch("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "Mark1.Write");
	cFileUtil.Touch("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "Mark2.Rewrite");
	cFileUtil.Delete("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "1.txt");
	cFileUtil.Delete("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "4.txt");

	cController.Init(szDirectory, szRewrite);

	cDurableFile1.Init(&cController, "1.txt", "1.txt");
	cDurableFile2.Init(&cController, "2.txt", "2.txt");
	cDurableFile3.Init(&cController, "3.txt", "3.txt");
	cDurableFile4.Init(&cController, "4.txt", "4.txt");

	//Recovery should copy _1.txt and _4.txt back again.
	bResult = cController.Recover(&cDurableFile1, &cDurableFile2, &cDurableFile3, &cDurableFile4, NULL);
	AssertTrue(bResult);

	cController.Kill();

	AssertFileString("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "1.txt", "Dulcedo Cogitationis");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "1.txt", "Dulcedo Cogitationis");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "4.txt", "Age Chaos Battle Orcs Humans");
	AssertFileString("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "4.txt", "Age Chaos Battle Orcs Humans");

	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "2.txt"));
	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "2.txt"));

	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Write"  _FS_ "Mark1.Write"));
	AssertBool(false, cFileUtil.Exists("Output" _FS_ "Durable1" _FS_ "Rewrite"  _FS_ "Mark2.Rewrite"));

	//////////////////////////////////////////////////////////////////////////
	cDurableFile1.Kill();
	cDurableFile2.Kill();
	cDurableFile3.Kill();
	cDurableFile4.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Durable1");
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileControllerTwoInOneDirectory(void)
{
	CFileUtil				cFileUtil;
	CDurableFileController	cController1;
	CDurableFileController	cController2;
	CDurableFile			cDurableFile1;
	CDurableFile			cDurableFile2;
	CDurableFile			cDurableFile3;
	CDurableFile			cDurableFile4;
	bool					bResult;
	char					szDirectory[] = "Output" _FS_ "Durable3" _FS_ "Write";
	char					szRewrite[] = "Output" _FS_ "Durable3" _FS_ "Rewrite";

	cFileUtil.RemoveDir("Output" _FS_ "Durable3");

	bResult = cController1.Init(szDirectory, szRewrite, "C1_FileNames.Write", "C1_FileNames.Rewrite", "C1_Mark1.Write", "C1_Mark2.Rewrite");
	AssertTrue(bResult); 
	bResult = cController2.Init(szDirectory, szRewrite, "C2_FileNames.Write", "C2_FileNames.Rewrite", "C2_Mark1.Write", "C2_Mark2.Rewrite");
	AssertTrue(bResult);

	cController1.Begin();
	cController2.Begin();

	cDurableFile1.Init(&cController1, "1.txt", "1.txt");
	cDurableFile2.Init(&cController1, "2.txt", "2.txt");
	cDurableFile3.Init(&cController2, "3.txt", "3.txt");
	cDurableFile4.Init(&cController2, "4.txt", "4.txt");

	cDurableFile1.Write("Dulcedo ", 8, 1);
	cDurableFile1.Write("Cogitationis", 12, 1);

	cDurableFile2.Write("Alpha ", 6, 1);
	cDurableFile2.Write("Centauri", 8, 1);

	cDurableFile3.Write(4, "BBBB", 4, 1);
	cDurableFile3.Write(0, "AAAA", 4, 1);
	cDurableFile3.Write(12, "DDDD", 4, 1);
	cDurableFile3.Write(8, "CCCC", 4, 1);

	cDurableFile4.Write("Age ", 4, 1);
	cDurableFile4.Write("Chaos ", 6, 1);
	cDurableFile4.Write("Battle ", 7, 1);
	cDurableFile4.Write("Orcs ", 5, 1);
	cDurableFile4.Write("Humans", 6, 1);

	cController1.End();
	cController2.End();
	cDurableFile1.Kill();
	cDurableFile2.Kill();
	cDurableFile3.Kill();
	cDurableFile4.Kill();
	cController1.Kill();
	cController2.Kill();

	AssertTrue(cFileUtil.Touch("Output" _FS_ "Durable3" _FS_ "Write"  _FS_ "C2_Mark1.Write"));
	AssertTrue(cFileUtil.Delete("Output" _FS_ "Durable3" _FS_ "Write"  _FS_ "3.txt"));
	AssertTrue(cFileUtil.Delete("Output" _FS_ "Durable3" _FS_ "Write"  _FS_ "4.txt"));

	bResult = cController1.Init(szDirectory, szRewrite, "C1_FileNames.Write", "C1_FileNames.Rewrite", "C1_Mark1.Write", "C1_Mark2.Rewrite");
	AssertTrue(bResult);
	bResult = cController2.Init(szDirectory, szRewrite, "C2_FileNames.Write", "C2_FileNames.Rewrite", "C2_Mark1.Write", "C2_Mark2.Rewrite");
	AssertFalse(bResult);

	cDurableFile1.Init(&cController1, "1.txt", "1.txt");
	cDurableFile2.Init(&cController1, "2.txt", "2.txt");
	cDurableFile3.Init(&cController2, "3.txt", "3.txt");
	cDurableFile4.Init(&cController2, "4.txt", "4.txt");

	AssertInt(0, cController1.NumFiles());
	AssertInt(0, cController2.NumFiles());
	bResult = cController1.Recover(&cDurableFile1, &cDurableFile2, NULL);
	AssertTrue(bResult);

	bResult = cController2.Recover(&cDurableFile3, &cDurableFile4, NULL);
	AssertTrue(bResult);

	AssertTrue(cFileUtil.Exists("Output" _FS_ "Durable3" _FS_ "Write"  _FS_ "3.txt"));
	AssertTrue(cFileUtil.Exists("Output" _FS_ "Durable3" _FS_ "Write"  _FS_ "4.txt"));

	cDurableFile1.Kill();
	cDurableFile2.Kill();
	cDurableFile3.Kill();
	cDurableFile4.Kill();
	cController1.Kill();
	cController2.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Durable3");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileController(void)
{
	TypeConverterInit();
	BeginTests();

	TestDurableFileControllerDirectoryCreation();
	TestDurableFileControllerRecovery();
	TestDurableFileControllerTwoInOneDirectory();

	TestStatistics();
	TypeConverterKill();
}

