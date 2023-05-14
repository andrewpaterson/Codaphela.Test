#include <thread>
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TextFile.h"
#include "ThreadLib/ProcessFork.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestProcessFork(void)
{
	BeginTests();

	CFileUtil		cFileUtil;
	int				i;
	bool			bFileExists;
	char			szFileName[] = {"Output" _FS_ "test-client-process.txt"};
	CTextFile		cTextFile;

	cFileUtil.MakeDir("Output");
	cFileUtil.Delete(szFileName);
	AssertFalse(cFileUtil.Exists(szFileName));

	ForkProcess("--test-client-process", szFileName, false);

	bFileExists = false;
	for (i = 0; i < 50; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		bFileExists = cFileUtil.Exists(szFileName);
		if (bFileExists)
		{
			break;
		}
	}
	Pass();

	AssertTrue(bFileExists);

	AssertTrue(cTextFile.Init()->Read(szFileName));
	AssertString("Hello World\n", cTextFile.Text());
	cTextFile.Kill();
	Pass();

	cFileUtil.Delete(szFileName);

	TestStatistics();
}

