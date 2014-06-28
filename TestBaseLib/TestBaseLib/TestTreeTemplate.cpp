#include "BaseLib/MemoryFile.h"
#include "BaseLib/TreeTemplate.h"
#include "TestLib/Assert.h"


struct STestTreeTemplateItem
{
	int	i1;
	int	i2;

	void Init(int i1, int i2);
	BOOL IsOkay(int i1, int i2);
};
void STestTreeTemplateItem::Init(int i1, int i2)
{
	this->i1 = i1;
	this->i2 = i2;
}
BOOL STestTreeTemplateItem::IsOkay(int i1, int i2)
{
	return (this->i1 == i1) && (this->i2 == i2);
}



typedef CTreeTemplate<STestTreeTemplateItem> CTestTree;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTreeTemplateInsert(void)
{
	CTestTree				cTree;
	STestTreeTemplateItem*	pcNode0;
	STestTreeTemplateItem*	pcNode00;
	STestTreeTemplateItem*	pcNode01;
	STestTreeTemplateItem*	pcNode02;
	STestTreeTemplateItem*	pcNode000;
	STestTreeTemplateItem*	pcTest;

	cTree.Init();
	pcNode0 = cTree.InsertRoot();
	pcNode0->Init(672, 7645);

	pcNode00 = cTree.InsertOnRightOfChildren(pcNode0);
	pcNode00->Init(720, 6);

	pcNode000 = cTree.InsertOnRightOfChildren(pcNode00);
	pcNode000->Init(325, 28274);

	pcNode01 = cTree.InsertOnRightOfChildren(pcNode0);
	pcNode01->Init(8, 12);

	pcNode02 = cTree.InsertOnRightOfChildren(pcNode0);
	pcNode02->Init(99, 7);

	AssertInt(5, cTree.NumElements());
	pcTest = cTree.GetRoot();
	AssertPointer(pcNode0, pcTest);
	AssertTrue(pcTest->IsOkay(672, 7645));
	pcTest = cTree.GetUp(pcNode0);
	AssertPointer(pcNode00, pcTest);
	AssertTrue(pcTest->IsOkay(720, 6));
	pcTest = cTree.GetUp(pcNode00);
	AssertPointer(pcNode000, pcTest);
	pcTest = cTree.GetRight(pcNode00);
	AssertPointer(pcNode01, pcTest);
	pcTest = cTree.GetRight(pcNode01);
	AssertPointer(pcNode02, pcTest);
	pcTest = cTree.GetRight(pcNode02);
	AssertNull(pcTest);
	AssertNull(cTree.GetUp(pcNode01));
	AssertNull(cTree.GetUp(pcNode02));
	AssertPointer(pcNode0, cTree.GetDown(pcNode00));
	AssertPointer(pcNode0, cTree.GetDown(pcNode01));
	AssertPointer(pcNode0, cTree.GetDown(pcNode02));

	cTree.Kill();
}


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

	TestTreeTemplateInsert();
	TestTreeTemplateFileHelper();

	TestStatistics();
}

