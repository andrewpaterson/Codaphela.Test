#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "TestLib/Assert.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeFile.h"
#include "TestIndexTreeObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockFileInit(void)
{
	CIndexTreeHelper	cHelper;
	CIndexTreeFile			cIndexFile;
	CDurableFileController		cDurableController;

	cHelper.Init("Database9", "primary", "backup", "RootFile.IDX", TRUE);

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexFile.Init(&cDurableController, cHelper.GetRootFileName(), &gcSystemAllocator);
	cDurableController.End();

	cIndexFile.Kill();
	cDurableController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockFileAdd(void)
{
	CIndexTreeHelper	cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile			cIndexFile;

	CTestIndexTreeObject		a;
	CTestIndexTreeObject		aa;
	CArrayVoidPtr				avp;
	BOOL						bResult;
	CIndexTreeNodeFile*			pcNode;
	CTestIndexTreeObject**		ppvTest;
	CTestIndexTreeObject***		ppvTestA;
	CTestIndexTreeObject***		ppvTestAA;

	cHelper.Init("Database10", "primary", "backup", "RootFile.IDX", TRUE);

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexFile.Init(&cDurableController, cHelper.GetRootFileName(), &gcSystemAllocator);

	a.Init("A");
	bResult = cIndexFile.PutPtr(a.GetName(), &a);
	AssertTrue(bResult);

	pcNode = cIndexFile.GetIndexNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&a, *ppvTest);

	aa.Init("AA");
	bResult = cIndexFile.PutPtr(aa.GetName(), &aa);
	AssertTrue(bResult);

	pcNode = cIndexFile.GetIndexNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&a, *ppvTest);

	pcNode = cIndexFile.GetIndexNode("AA", 2);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&aa, *ppvTest);

	avp.Init();
	cIndexFile.FindAll(&avp);
	AssertInt(2, avp.NumElements());
	ppvTestA = (CTestIndexTreeObject***)avp.Get(0);
	ppvTestAA = (CTestIndexTreeObject***)avp.Get(1);
	AssertPointer(&a, **ppvTestA);
	AssertPointer(&aa, **ppvTestAA);
	AssertString("A", (**ppvTestA)->mszName);
	AssertString("AA", (**ppvTestAA)->mszName);

	avp.Kill();
	
	cDurableController.End();

	cIndexFile.Kill();
	cDurableController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockFile(void)
{
	BeginTests();

	TestIndexTreeBlockFileInit();
	TestIndexTreeBlockFileAdd();

	TestStatistics();
}


