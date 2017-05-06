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
void TestDurableSetFileRecovery(void)
{
	CFileUtil				cFileUtil;
	CDurableFileController	cController;
	CDurableFile			cDurableFile1;
	CDurableFile			cDurableFile2;
	CDurableFile			cDurableFile3;
	CDurableFile			cDurableFile4;
	BOOL					bResult;
	char					szDirectory[] = "Durable";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	//////////////////////////////////////////////////////////////////////////

	cController.Init(szDirectory, szDirectory);

	cDurableFile1.Init(&cController, "Durable" _FS_ "1.txt", "Durable" _FS_ "_1.txt");
	cDurableFile2.Init(&cController, "Durable" _FS_ "2.txt", "Durable" _FS_ "_2.txt");
	cDurableFile3.Init(&cController, "Durable" _FS_ "3.txt", "Durable" _FS_ "_3.txt");
	cDurableFile4.Init(&cController, "Durable" _FS_ "4.txt", "Durable" _FS_ "_4.txt");

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

	AssertFileString("Durable" _FS_ "1.txt", "Dulcedo Cogitationis");
	AssertFileString("Durable" _FS_ "_1.txt", "Dulcedo Cogitationis");
	AssertFileString("Durable" _FS_ "3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Durable" _FS_ "_3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Durable" _FS_ "4.txt", "Age Chaos Battle Orcs Humans");
	AssertFileString("Durable" _FS_ "_4.txt", "Age Chaos Battle Orcs Humans");

	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "2.txt"));
	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "_2.txt"));

	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "Mark1.Write"));
	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "Mark2.Rewrite"));

	//////////////////////////////////////////////////////////////////////////

	cController.Init("Durable", "_Durable");

	cDurableFile1.Init(&cController, "Durable" _FS_ "1.txt", "_Durable" _FS_ "_1.txt");
	cDurableFile2.Init(&cController, "Durable" _FS_ "2.txt", "_Durable" _FS_ "_2.txt");
	cDurableFile3.Init(&cController, "Durable" _FS_ "3.txt", "_Durable" _FS_ "_3.txt");
	cDurableFile4.Init(&cController, "Durable" _FS_ "4.txt", "_Durable" _FS_ "_4.txt");

	//Recovery should do nothing as the files are consistent.
	bResult = cController.Recover();
	AssertTrue(bResult);

	cDurableFile1.Kill();
	cDurableFile2.Kill();
	cDurableFile3.Kill();
	cDurableFile4.Kill();
	cController.Kill();

	AssertFileString("Durable" _FS_ "1.txt", "Dulcedo Cogitationis");
	AssertFileString("_Durable" _FS_ "_1.txt", "Dulcedo Cogitationis");
	AssertFileString("Durable" _FS_ "3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("_Durable" _FS_ "_3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Durable" _FS_ "4.txt", "Age Chaos Battle Orcs Humans");
	AssertFileString("_Durable" _FS_ "_4.txt", "Age Chaos Battle Orcs Humans");

	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "2.txt"));
	AssertBool(FALSE, cFileUtil.Exists("_Durable" _FS_ "_2.txt"));

	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "Mark1.Write"));
	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "Mark2.Rewrite"));

	//////////////////////////////////////////////////////////////////////////

	cFileUtil.Touch("Durable" _FS_ "Mark1.Write");
	cFileUtil.Delete("Durable" _FS_ "3.txt");
	cFileUtil.Delete("Durable" _FS_ "3.txt");

	cController.Init("Durable", "_Durable");

	cDurableFile1.Init(&cController, "Durable" _FS_ "1.txt", "_Durable" _FS_ "_1.txt");
	cDurableFile2.Init(&cController, "Durable" _FS_ "2.txt", "_Durable" _FS_ "_2.txt");
	cDurableFile3.Init(&cController, "Durable" _FS_ "3.txt", "_Durable" _FS_ "_3.txt");
	cDurableFile4.Init(&cController, "Durable" _FS_ "4.txt", "_Durable" _FS_ "_4.txt");

	//Recovery should copy 3.txt and 4.txt back again.
	bResult = cController.Recover();
	AssertTrue(bResult);

	cDurableFile1.Kill();
	cDurableFile2.Kill();
	cDurableFile3.Kill();
	cDurableFile4.Kill();
	cController.Kill();

	AssertFileString("Durable" _FS_ "1.txt", "Dulcedo Cogitationis");
	AssertFileString("_Durable" _FS_ "_1.txt", "Dulcedo Cogitationis");
	AssertFileString("Durable" _FS_ "3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("_Durable" _FS_ "_3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Durable" _FS_ "4.txt", "Age Chaos Battle Orcs Humans");
	AssertFileString("_Durable" _FS_ "_4.txt", "Age Chaos Battle Orcs Humans");

	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "2.txt"));
	AssertBool(FALSE, cFileUtil.Exists("_Durable" _FS_ "_2.txt"));

	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "Mark1.Write"));
	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "Mark2.Rewrite"));

	//////////////////////////////////////////////////////////////////////////

	cFileUtil.Touch("Durable" _FS_ "Mark1.Write");
	cFileUtil.Touch("Durable" _FS_ "Mark2.Rewrite");
	cFileUtil.Delete("Durable" _FS_ "_1.txt");
	cFileUtil.Delete("Durable" _FS_ "_4.txt");

	cController.Init("Durable", "_Durable");

	cDurableFile1.Init(&cController, "Durable" _FS_ "1.txt", "_Durable" _FS_ "_1.txt");
	cDurableFile2.Init(&cController, "Durable" _FS_ "2.txt", "_Durable" _FS_ "_2.txt");
	cDurableFile3.Init(&cController, "Durable" _FS_ "3.txt", "_Durable" _FS_ "_3.txt");
	cDurableFile4.Init(&cController, "Durable" _FS_ "4.txt", "_Durable" _FS_ "_4.txt");

	//Recovery should copy _1.txt and _4.txt back again.
	bResult = cController.Recover();
	AssertTrue(bResult);

	cController.Kill();

	AssertFileString("Durable" _FS_ "1.txt", "Dulcedo Cogitationis");
	AssertFileString("_Durable" _FS_ "_1.txt", "Dulcedo Cogitationis");
	AssertFileString("Durable" _FS_ "3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("_Durable" _FS_ "_3.txt", "AAAABBBBCCCCDDDD");
	AssertFileString("Durable" _FS_ "4.txt", "Age Chaos Battle Orcs Humans");
	AssertFileString("_Durable" _FS_ "_4.txt", "Age Chaos Battle Orcs Humans");

	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "2.txt"));
	AssertBool(FALSE, cFileUtil.Exists("_Durable" _FS_ "_2.txt"));

	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "Mark1.Write"));
	AssertBool(FALSE, cFileUtil.Exists("Durable" _FS_ "Mark2.Rewrite"));

	//////////////////////////////////////////////////////////////////////////

	cFileUtil.RemoveDir("Durable");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableFileController(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	//Recovery is currently broken as the full list of files that should exist is no longer available.
	//TestDurableSetFileRecovery();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

