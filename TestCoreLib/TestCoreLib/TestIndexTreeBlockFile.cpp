#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "TestLib/Assert.h"
#include "CoreLib/IndexTreeBlockFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockFileSomething(void)
{
	CIndexTreeBlockFile		cIndexFile;
	CDurableFileController	cDurableController;
	CFileUtil				cFileUtil;
	char					szWorkingDirectory[] = "Database9";
	CChars					szDirectory;
	CChars					szRewriteDirectory;

	cFileUtil.RemoveDir(szWorkingDirectory);

	szDirectory.Init(szWorkingDirectory);
	cFileUtil.AppendToPath(&szDirectory, "primary");
	szRewriteDirectory.Init(szWorkingDirectory);
	cFileUtil.AppendToPath(&szRewriteDirectory, "backup");
	cDurableController.Init(szDirectory.Text(), szRewriteDirectory.Text(), TRUE);

	cIndexFile.Init(&cDurableController, &gcSystemAllocator);

	cIndexFile.Kill();
	cDurableController.Kill();

	szDirectory.Kill();
	szRewriteDirectory.Kill();
	cFileUtil.RemoveDir(szWorkingDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockFile(void)
{
	BeginTests();

	TestIndexTreeBlockFileSomething();

	TestStatistics();
}


