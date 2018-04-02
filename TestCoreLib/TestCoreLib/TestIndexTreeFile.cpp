#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeFile.h"
#include "CoreLib/IndexTreeFileAccess.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileInit(void)
{
	CIndexTreeHelper		cHelper;
	CIndexTreeFile			cIndexTree;
	CDurableFileController	cDurableController;

	cHelper.Init("Output" _FS_"Database9", "primary", "backup", "RootFile.IDX", TRUE);

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName(), &gcSystemAllocator);
	cDurableController.End();

	cIndexTree.Kill();
	cDurableController.Kill();

	cHelper.RemoveWorkingDirectory();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAdd(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;

	CTestIndexTreeObject		a;
	CTestIndexTreeObject		aa;
	BOOL						bResult;
	CIndexTreeNodeFile*			pcNode;
	CTestIndexTreeObject**		ppvTest;
	//CTestIndexTreeObject***		ppvTestA;
	//CTestIndexTreeObject***		ppvTestAA;

	cHelper.Init("Output" _FS_"Database10", "primary", "backup", "RootFile.IDX", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName(), &gcSystemAllocator);
	cAccess.Init(&cIndexTree);

	a.Init("A");
	bResult = cAccess.PutStringPtr(a.GetName(), &a);
	AssertTrue(bResult);

	pcNode = cIndexTree.GetNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&a, *ppvTest);

	aa.Init("AA");
	bResult = cAccess.PutStringPtr(aa.GetName(), &aa);
	AssertTrue(bResult);

	pcNode = cIndexTree.GetNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&a, *ppvTest);

	pcNode = cIndexTree.GetNode("AA", 2);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&aa, *ppvTest);

	//avp.Init();
	//cIndexTree.FindAll(&avp);
	//AssertInt(2, avp.NumElements());
	//ppvTestA = (CTestIndexTreeObject***)avp.Get(0);
	//ppvTestAA = (CTestIndexTreeObject***)avp.Get(1);
	//AssertPointer(&a, **ppvTestA);
	//AssertPointer(&aa, **ppvTestAA);
	//AssertString("A", (**ppvTestA)->mszName);
	//AssertString("AA", (**ppvTestAA)->mszName);
	//avp.Kill();
	
	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

	cHelper.RemoveWorkingDirectory();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileNoCacheEviction(void)
{
	CIndexTreeFile			cIndexTree;
	CIndexTreeFileAccess	cAccess;
	char					sz[MAX_UCHAR];
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;
	SIndexTreeFileIterator	sIter;
	BOOL					bContinue;
	char*					szData;
	int						iSize;

	cHelper.Init("Output" _FS_"IndexTree1", "primary", "backup", "RootFile.IDX", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName(), &gcSystemAllocator);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutLongString(0x0000000000000000LL, "Zero"));
	AssertInt(1, cIndexTree.NumElements());

	AssertTrue(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);

	bContinue = cIndexTree.StartIteration(&sIter, (void**)(&szData), &iSize);
	AssertTrue(bContinue);
	AssertInt(5, iSize);
	AssertString("Zero", szData);
	bContinue = cIndexTree.Iterate(&sIter, (void**)(&szData), &iSize);
	AssertFalse(bContinue);

	AssertFalse(cAccess.GetLongString(0x0100000000000000LL, sz));

	AssertFalse(cAccess.PutLongString(0xEE89DD67CC45BB23LL, "Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sente."));
	AssertTrue(cAccess.PutLongString(0xEE89DD67CC45BB23LL, "Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent."));
	AssertInt(2, cIndexTree.NumElements());

	AssertTrue(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent.", sz);

	bContinue = cIndexTree.StartIteration(&sIter, (void**)(&szData), &iSize);
	AssertTrue(bContinue);
	AssertInt(5, iSize);
	AssertString("Zero", szData);
	bContinue = cIndexTree.Iterate(&sIter, (void**)(&szData), &iSize);
	AssertTrue(bContinue);
	AssertInt(255, iSize);
	AssertString("Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent.", szData);
	bContinue = cIndexTree.Iterate(&sIter, (void**)(&szData), &iSize);
	AssertFalse(bContinue);

	AssertTrue(cAccess.PutLongString(0x0098DD67CC45BB23LL, "MORE node DATA"));
	AssertInt(3, cIndexTree.NumElements());

	AssertTrue(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("MORE node DATA", sz);

	AssertTrue(cAccess.PutLongString(0x0000DD00CC54BB23LL, "Another DATUM of doom"));
	AssertInt(4, cIndexTree.NumElements());

	AssertTrue(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.PutLongString(0x0098DD67CC45BB23LL, "Changed your data lengh"));
	AssertInt(4, cIndexTree.NumElements());

	AssertTrue(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertTrue(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);
	AssertTrue(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent.", sz);
	AssertTrue(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.PutLongString(0xEE89DD67CC45BB23LL, "Make the long short."));
	AssertInt(4, cIndexTree.NumElements());

	AssertTrue(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertTrue(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);
	AssertTrue(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long short.", sz);
	AssertTrue(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertFalse(cAccess.RemoveLong(0x0100000000000000LL));
	AssertFalse(cAccess.RemoveLong(0x00000000000000FFLL));
	AssertTrue(cAccess.RemoveLong(0x0000000000000000LL));
	AssertInt(3, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertTrue(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long short.", sz);
	AssertTrue(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.RemoveLong(0x0098DD67CC45BB23LL));
	AssertInt(2, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertFalse(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));

	AssertTrue(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long short.", sz);
	AssertTrue(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	bContinue = cIndexTree.StartIteration(&sIter, (void**)(&szData), &iSize);
	AssertTrue(bContinue);
	AssertInt(21, iSize);
	AssertString("Make the long short.", szData);

	bContinue = cIndexTree.Iterate(&sIter, (void**)(&szData), &iSize);
	AssertTrue(bContinue);
	AssertInt(21, iSize);
	AssertString("", szData);

	bContinue = cIndexTree.Iterate(&sIter, (void**)(&szData), &iSize);
	AssertFalse(bContinue);

	AssertTrue(cAccess.RemoveLong(0x0000DD00CC54BB23LL));
	AssertInt(1, cIndexTree.NumElements());
	AssertFalse(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));

	bContinue = cIndexTree.StartIteration(&sIter, (void**)(&szData), &iSize);
	AssertTrue(bContinue);
	AssertInt(10, iSize);
	AssertString("", szData);

	bContinue = cIndexTree.Iterate(&sIter, (void**)(&szData), &iSize);
	AssertFalse(bContinue);

	AssertTrue(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Make the long short.", sz);

	AssertTrue(cAccess.RemoveLong(0x23BB45CC67DD89EELL));
	AssertInt(0, cIndexTree.NumElements());
	AssertFalse(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

	cHelper.RemoveWorkingDirectory();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFile(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestIndexTreeFileInit();
	TestIndexTreeFileAdd();
	TestIndexTreeFileNoCacheEviction();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

