#include "TestLib/Assert.h"
#include "BaseLib/FastFunctions.h"
#include "CoreLib/DurableFile.h"
#include "CoreLib/DurableSet.h"
#include "CoreLib/DurableFileController.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/FileBasic.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/TypeConverter.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableSetAdd(void)
{
	CFileUtil				cFileUtil;
	CDurableFileController	cController;
	CDurableFile			cDurableFile1;
	CDurableFile			cDurableFile2;
	CDurableFile			cDurableFile3;
	CDurableFile			cDurableFile4;
	char					szDirectory[] = "Durable2";
	char					szRewrite[] = "_Durable2";
	CDurableFile*			pcDurableFile;

	cFileUtil.MakeDirs(TRUE, szDirectory, szRewrite, NULL);

	cController.Init(szDirectory, szRewrite);

	cDurableFile1.Init(&cController, "Durable2" _FS_ "1.txt", "_Durable2" _FS_ "_1.txt");
	cDurableFile2.Init(&cController, "Durable2" _FS_ "2.txt", "_Durable2" _FS_ "_2.txt");
	cDurableFile3.Init(&cController, "Durable2" _FS_ "3.txt", "_Durable2" _FS_ "_3.txt");
	cDurableFile4.Init(&cController, "Durable2" _FS_ "4.txt", "_Durable2" _FS_ "_4.txt");
	cController.Begin();

	cController.AddFile(&cDurableFile1);
	AssertInt(1, cController.NumFiles());
	pcDurableFile = cController.GetFile(0);
	AssertPointer(&cDurableFile1, pcDurableFile);

	cController.AddFile(&cDurableFile1);
	AssertInt(1, cController.NumFiles());
	pcDurableFile = cController.GetFile(0);
	AssertPointer(&cDurableFile1, pcDurableFile);

	cController.AddFile(&cDurableFile2);
	AssertInt(2, cController.NumFiles());
	cController.AddFile(&cDurableFile3);
	AssertInt(3, cController.NumFiles());
	cController.AddFile(&cDurableFile4);
	AssertInt(4, cController.NumFiles());

	cController.AddFile(&cDurableFile2);
	AssertInt(4, cController.NumFiles());
	cController.AddFile(&cDurableFile3);
	AssertInt(4, cController.NumFiles());
	cController.AddFile(&cDurableFile4);
	AssertInt(4, cController.NumFiles());

	cController.End();
	cDurableFile1.Kill();
	cDurableFile2.Kill();
	cDurableFile3.Kill();
	cDurableFile4.Kill();
	cController.Kill();

	cFileUtil.RemoveDirs(szDirectory, szRewrite, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDurableSet(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestDurableSetAdd();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

