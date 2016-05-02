#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "TestLib/Assert.h"
#include "CoreLib/IndexTreeBlockFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockFileInit(void)
{
	CIndexTreeBlockFile		cIndexFile;
	CDurableFileController	cDurableController;
	CFileUtil				cFileUtil;
	char					szWorkingDirectory[] = "Database9";
	CChars					szDirectory;
	CChars					szRewriteDirectory;
	CChars					szRootFileName;

	cFileUtil.RemoveDir(szWorkingDirectory);

	szDirectory.Init(szWorkingDirectory);
	cFileUtil.AppendToPath(&szDirectory, "primary");
	szRewriteDirectory.Init(szWorkingDirectory);
	cFileUtil.AppendToPath(&szRewriteDirectory, "backup");
	szRootFileName.Init(szWorkingDirectory);
	cFileUtil.AppendToPath(&szRootFileName, "RootFile.IDX");

	cDurableController.Init(szDirectory.Text(), szRewriteDirectory.Text());

	cDurableController.Begin();
	cIndexFile.Init(&cDurableController, szRootFileName.Text(), &gcSystemAllocator);
	cDurableController.End();

	cIndexFile.Kill();
	cDurableController.Kill();

	szDirectory.Kill();
	szRewriteDirectory.Kill();
	szRootFileName.Kill();
	cFileUtil.RemoveDir(szWorkingDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockFile(void)
{
	BeginTests();

	TestIndexTreeBlockFileInit();

	TestStatistics();
}


