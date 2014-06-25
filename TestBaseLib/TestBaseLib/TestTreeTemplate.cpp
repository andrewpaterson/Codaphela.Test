#include "BaseLib/MemoryFile.h"
#include "BaseLib/TreeTemplate.h"
#include "TestLib/Assert.h"


struct STestTreeTemplateItem
{
	int	i1;
	int	i2;
};


typedef CTreeTemplate<STestTreeTemplateItem> CTestTree;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTreeTemplateFileHelper(void)
{
	CTestTree				cTree;
	STestTreeTemplateItem*	psRoot;
	STestTreeTemplateItem*	psChild1;
	STestTreeTemplateItem*	psChild2;
	CMemoryFile*			pcMemoryFile;
	CFileBasic				cFileBasic;
	BOOL					bResult;

	cTree.Init();

	psRoot = cTree.InsertRoot();
	psRoot->i1 = 5; psRoot->i2 = 7;

	psChild1 = cTree.InsertOnRightOfChildren(psRoot);
	psChild1->i1 = 1; psChild1->i2 = 2;

	psChild2 = cTree.InsertOnRightOfChildren(psRoot);
	psChild2->i1 = 3; psChild2->i2 = 9;

	pcMemoryFile = MemoryFile();
	pcMemoryFile->mbBasicFileMustFree = FALSE;

	cFileBasic.Init(pcMemoryFile);
	cFileBasic.Open(EFM_Write_Create);
	bResult = cTree.WriteTreeTemplate(&cFileBasic);
	AssertTrue(bResult);
	cFileBasic.Close();
	cFileBasic.Kill();

	cTree.Kill();

	cFileBasic.Init(pcMemoryFile);
	cFileBasic.Open(EFM_Read);
	bResult = cTree.ReadTreeTemplate(&cFileBasic);
	AssertTrue(bResult);
	cFileBasic.Close();
	cFileBasic.Kill();

	free(pcMemoryFile);

	psRoot = cTree.GetRoot();
	AssertInt(5, psRoot->i1);
	AssertInt(7, psRoot->i2);

	psChild1 = cTree.GetUp(psRoot);
	AssertInt(1, psChild1->i1);
	AssertInt(2, psChild1->i2);

	psChild2 = cTree.GetRight(psChild1);
	AssertInt(3, psChild2->i1);
	AssertInt(9, psChild2->i2);

	cTree.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTreeTemplate(void)
{
	BeginTests();

	TestTreeTemplateFileHelper();

	TestStatistics();
}

