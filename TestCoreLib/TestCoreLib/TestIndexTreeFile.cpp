#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include"BaseLib/MemoryAllocator.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeFile.h"
#include "CoreLib/IndexTreeFileAccess.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeObject.h"


char	gszIndexTreeString[257];

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* GetString(CIndexTreeFile* pcIndexTree, char* szKey)
{
	int		iKeySize;
	BOOL	bResult;

	iKeySize = strlen(szKey);
	bResult = pcIndexTree->Get(szKey, iKeySize, &gszIndexTreeString, NULL);
	if (bResult)
	{
		return gszIndexTreeString;
	}
	else
	{
		return NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileSizeOfs(void)
{
	CIndexTreeFile		cIndexTree;
	size_t				tRootNodeSize;
	size_t				tNodeSize;
	size_t				tNodePointer;

	cIndexTree.FakeInit();
	tRootNodeSize = cIndexTree.CalculateRootNodeSize();
	tNodeSize = cIndexTree.SizeofNode();
	tNodePointer = cIndexTree.SizeofNodePtr();

	AssertInt(24, tNodeSize);
	AssertInt(12, tNodePointer);
	AssertInt(tNodePointer * 256 + tNodeSize, tRootNodeSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileInit(void)
{
	CIndexTreeHelper		cHelper;
	CIndexTreeFile			cIndexTree;
	CDurableFileController	cDurableController;

	cHelper.Init("Output" _FS_"QuakeMinusOne", "primary", "backup", "RootFile.IDX", TRUE);

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName());
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
	CTestIndexTreeObject		aaa;
	CTestIndexTreeObject		ab;
	CTestIndexTreeObject		aab;
	BOOL						bResult;
	CIndexTreeNodeFile*			pcNode;
	CTestIndexTreeObject**		ppvTest;
	SIndexTreeFileIterator		sIter;
	BOOL						bContinue;
	int							iSize;

	cHelper.Init("Output" _FS_"IndexTree0", "primary", "backup", "RootFile.IDX", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName());
	cAccess.Init(&cIndexTree);

	a.Init("A");
	bResult = cAccess.PutStringPtr(a.GetName(), &a);
	AssertTrue(bResult);
	AssertTrue(cIndexTree.ValidateIndexTree());

	pcNode = cIndexTree.GetNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&a, *ppvTest);

	aa.Init("AA");
	bResult = cAccess.PutStringPtr(aa.GetName(), &aa);
	AssertTrue(bResult);
	AssertTrue(cIndexTree.ValidateIndexTree());

	aaa.Init("AAA");
	bResult = cAccess.PutStringPtr(aaa.GetName(), &aaa);
	AssertTrue(bResult);
	AssertTrue(cIndexTree.ValidateIndexTree());

	ab.Init("AB");
	bResult = cAccess.PutStringPtr(ab.GetName(), &ab);
	AssertTrue(bResult);
	AssertTrue(cIndexTree.ValidateIndexTree());

	aab.Init("AAB");
	bResult = cAccess.PutStringPtr(aab.GetName(), &aab);
	AssertTrue(bResult);
	AssertTrue(cIndexTree.ValidateIndexTree());


	pcNode = cIndexTree.GetNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&a, *ppvTest);

	pcNode = cIndexTree.GetNode("AA", 2);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&aa, *ppvTest);

	bContinue = cIndexTree.StartIteration(&sIter, (void**)(&ppvTest), &iSize);
	AssertTrue(bContinue);
	AssertInt(sizeof(CTestIndexTreeObject*), iSize);
	AssertString("A", (*ppvTest)->mszName);

	bContinue = cIndexTree.Iterate(&sIter, (void**)(&ppvTest), &iSize);
	AssertTrue(bContinue);
	AssertInt(sizeof(CTestIndexTreeObject*), iSize);
	AssertString("AA", (*ppvTest)->mszName);

	bContinue = cIndexTree.Iterate(&sIter, (void**)(&ppvTest), &iSize);
	AssertTrue(bContinue);
	AssertInt(sizeof(CTestIndexTreeObject*), iSize);
	AssertString("AAA", (*ppvTest)->mszName);

	bContinue = cIndexTree.Iterate(&sIter, (void**)(&ppvTest), &iSize);
	AssertTrue(bContinue);
	AssertInt(sizeof(CTestIndexTreeObject*), iSize);
	AssertString("AAB", (*ppvTest)->mszName);

	bContinue = cIndexTree.Iterate(&sIter, (void**)(&ppvTest), &iSize);
	AssertTrue(bContinue);
	AssertInt(sizeof(CTestIndexTreeObject*), iSize);
	AssertString("AB", (*ppvTest)->mszName);

	bContinue = cIndexTree.Iterate(&sIter, (void**)(&ppvTest), &iSize);
	AssertFalse(bContinue);

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
	char					sz[MAX_DATA_SIZE];
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;
	SIndexTreeFileIterator	sIter;
	BOOL					bContinue;
	char*					szData;
	int						iSize;

	cHelper.Init("Output" _FS_"IndexTree1", "primary", "backup", "RootFile.IDX", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName());
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutLongString(0x0000000000000000LL, "Zero"));
	AssertInt(1, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree())

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
	AssertTrue(cIndexTree.ValidateIndexTree())

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
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("MORE node DATA", sz);

	AssertTrue(cAccess.PutLongString(0x0000DD00CC54BB23LL, "Another DATUM of doom"));
	AssertInt(4, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.PutLongString(0x0098DD67CC45BB23LL, "Changed your data lengh"));
	AssertInt(4, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

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
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertTrue(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);
	AssertTrue(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long short.", sz);
	AssertTrue(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertFalse(cAccess.DeleteLong(0x0100000000000000LL));
	AssertFalse(cAccess.DeleteLong(0x00000000000000FFLL));
	AssertTrue(cAccess.DeleteLong(0x0000000000000000LL));
	AssertInt(3, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertTrue(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long short.", sz);
	AssertTrue(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.DeleteLong(0x0098DD67CC45BB23LL));
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
	AssertInt(22, iSize);
	AssertString("Another DATUM of doom", szData);

	bContinue = cIndexTree.Iterate(&sIter, (void**)(&szData), &iSize);
	AssertFalse(bContinue);

	AssertTrue(cAccess.DeleteLong(0x0000DD00CC54BB23LL));
	AssertInt(1, cIndexTree.NumElements());
	AssertFalse(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));

	bContinue = cIndexTree.StartIteration(&sIter, (void**)(&szData), &iSize);
	AssertTrue(bContinue);
	AssertInt(21, iSize);
	AssertString("Make the long short.", szData);

	bContinue = cIndexTree.Iterate(&sIter, (void**)(&szData), &iSize);
	AssertFalse(bContinue);

	AssertTrue(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long short.", sz);

	AssertTrue(cAccess.DeleteLong(0xEE89DD67CC45BB23LL));
	AssertInt(0, cIndexTree.NumElements());
	AssertFalse(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));

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
void TestIndexTreeFileResizeData(void)
{
	CIndexTreeNodeFile*		pcNode;
	CIndexTreeNodeFile*		pcOldNode;
	CIndexTreeNodeFile*		pcRoot;
	char					szAAObject[] = "Hello";
	char					szACObject[] = "Goodbye";
	char					szAObject[] = "Centrist Policies";
	int						iNodeMemoryOffset1;
	int						iNodeMemoryOffset2;
	CChars					sz;
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;
	CMemoryAllocator		cAllocator;
	CMemory*				pcMemory;

	cHelper.Init("Output" _FS_"IndexTree2", "primary", "backup", "RootFile.IDX", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName(), &cAllocator, TRUE);

	cIndexTree.Put("AA", szAAObject, (unsigned char)strlen(szAAObject) + 1);
	cIndexTree.Put("AC", szACObject, (unsigned char)strlen(szACObject) + 1);

	pcNode = cIndexTree.GetNode("A", 1);
	pcOldNode = pcNode;
	AssertInt(3, pcNode->GetNumIndexes());
	AssertInt(2, pcNode->NumInitialisedIndexes());
	AssertInt(0, pcNode->GetObjectSize());
	iNodeMemoryOffset1 = (size_t)pcNode->GetNodesMemory() - (size_t)pcNode;
	AssertInt(cIndexTree.SizeofNode(), iNodeMemoryOffset1);

	cIndexTree.Put("A", szAObject, (unsigned char)strlen(szAObject) + 1);

	pcNode = cIndexTree.GetNode("A", 1);
	AssertFalse(pcNode == pcOldNode);
	AssertInt(3, pcNode->GetNumIndexes());
	AssertInt(2, pcNode->NumInitialisedIndexes());
	AssertInt(18, pcNode->GetObjectSize());
	iNodeMemoryOffset2 = (size_t)pcNode->GetNodesMemory() - (size_t)pcNode;
	AssertInt(cIndexTree.SizeofNode() + pcNode->GetObjectSize(), iNodeMemoryOffset2);
	AssertTrue(iNodeMemoryOffset2 > iNodeMemoryOffset1);

	AssertString(szAAObject, GetString(&cIndexTree, "AA"));
	AssertString(szACObject, GetString(&cIndexTree, "AC"));
	AssertString(szAObject, GetString(&cIndexTree, "A"));

	pcRoot = cIndexTree.GetRoot();
	sz.Init(); pcRoot->Print(&sz, FALSE);
	AssertString("0:255 .................................................................x..............................................................................................................................................................................................", sz.Text()); sz.Kill();
	pcNode = pcRoot->Get('A')->u.mpcMemory;
	sz.Init(); pcNode->Print(&sz, FALSE);
	AssertString("65:67 (18) x.x", sz.Text()); sz.Kill();
	sz.Init(); pcNode->Get('A')->u.mpcMemory->Print(&sz, FALSE);
	AssertString("0:0 (6)", sz.Text()); sz.Kill();
	AssertFalse(pcNode->Get('B')->IsValid());
	sz.Init(); pcNode->Get('C')->u.mpcMemory->Print(&sz, FALSE);
	AssertString("0:0 (8)", sz.Text()); sz.Kill();

	cDurableController.End();

	cIndexTree.Kill();
	cDurableController.Kill();

	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());
	cAllocator.Kill();

	cHelper.RemoveWorkingDirectory();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileRemove(void)
{
	char					szAA[] = "MEDIUM";
	char					szAAA[] = "NEAR";
	char					szA[] = "Florida";
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;

	cHelper.Init("Output" _FS_"IndexTree3", "primary", "backup", "RootFile.IDX", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName());

	cIndexTree.Put("AA", szAA, (unsigned char)strlen(szAA) + 1);
	cIndexTree.Put("AAA", szAAA, (unsigned char)strlen(szAAA) + 1);
	cIndexTree.Put("A", szA, (unsigned char)strlen(szA) + 1);
	AssertInt(3, cIndexTree.NumElements());

	AssertTrue(cIndexTree.Remove("A"));
	AssertString(NULL, GetString(&cIndexTree, "A"));
	AssertString(szAA, GetString(&cIndexTree, "AA"));
	AssertString(szAAA, GetString(&cIndexTree, "AAA"));
	AssertInt(2, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cIndexTree.Remove("AA"));
	AssertString(NULL, GetString(&cIndexTree, "A"));
	AssertString(NULL, GetString(&cIndexTree, "AA"));
	AssertString(szAAA, GetString(&cIndexTree, "AAA"));
	AssertInt(1, cIndexTree.NumElements());

	AssertTrue(cIndexTree.Remove("AAA"));
	AssertString(NULL, GetString(&cIndexTree, "A"));
	AssertString(NULL, GetString(&cIndexTree, "AA"));
	AssertString(NULL, GetString(&cIndexTree, "AAA"));
	AssertInt(0, cIndexTree.NumElements());

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
void TestIndexTreeFileDelete(void)
{
	char					szAA[] = "MEDIUM";
	char					szAAA[] = "NEAR";
	char					szA[] = "Florida";
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;
	CIndexTreeFileAccess	cAccess;
	
	cHelper.Init("Output" _FS_"IndexTree4", "primary", "backup", "RootFile.IDX", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName(), TRUE);
	cAccess.Init(&cIndexTree);

	cIndexTree.Put("AA", szAA, (unsigned char)strlen(szAA) + 1);
	cIndexTree.Put("AAA", szAAA, (unsigned char)strlen(szAAA) + 1);
	cIndexTree.Put("A", szA, (unsigned char)strlen(szA) + 1);
	AssertInt(3, cIndexTree.NumElements());

	cIndexTree.SetWriteThrough(FALSE);

	cAccess.DeleteString("AA");
	AssertString(szA, GetString(&cIndexTree, "A"));
	AssertString(NULL, GetString(&cIndexTree, "AA"));
	AssertString(szAAA, GetString(&cIndexTree, "AAA"));
	AssertInt(2, cIndexTree.NumElements());
	AssertInt(4, cIndexTree.NumNodes());

	cIndexTree.Flush();
	AssertInt(4, cIndexTree.NumNodes());
	cIndexTree.ValidateIndexTree();

	cAccess.DeleteString("A");
	AssertString(NULL, GetString(&cIndexTree, "A"));
	AssertString(NULL, GetString(&cIndexTree, "AA"));
	AssertString(szAAA, GetString(&cIndexTree, "AAA"));
	AssertInt(1, cIndexTree.NumElements());
	AssertInt(4, cIndexTree.NumNodes());

	cAccess.DeleteString("AAA");
	AssertString(NULL, GetString(&cIndexTree, "A"));
	AssertString(NULL, GetString(&cIndexTree, "AA"));
	AssertString(NULL, GetString(&cIndexTree, "AAA"));
	AssertInt(0, cIndexTree.NumElements());
	AssertInt(4, cIndexTree.NumNodes());

	cIndexTree.Flush();
	AssertInt(1, cIndexTree.NumNodes());  //Just the root node left.
	cIndexTree.ValidateIndexTree();

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
void TestIndexTreeFileFindKey(void)
{
	char					szData[] = "Data";
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;
	char					szKeyName[] = "Key Name";
	char					szAmphibious[] = "Amphibious";
	char					szAmorphous[] = "Amorphous";
	char					szTestFly[] = "Test Fly";
	CIndexTreeNodeFile*		pcNode1;
	CIndexTreeNodeFile*		pcNode2;
	CIndexTreeNodeFile*		pcNode3;
	CIndexTreeNodeFile*		pcNode4;
	CArrayChar				acKey;
	unsigned char			auiKey[MAX_KEY_SIZE];
	int						iKeySize;
	CArrayVoidPtr			apvNodes;
	CListCharsMinimal*		paszKeyNames;

	cHelper.Init("Output" _FS_"IndexTree5", "primary", "backup", "RootFile.IDX", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName());

	cIndexTree.Put(szKeyName, szData, 5);
	cIndexTree.Put(szAmphibious, szData, 5);
	cIndexTree.Put(szAmorphous, szData, 5);
	cIndexTree.Put(szTestFly, szData, 5);

	pcNode1 = cIndexTree.GetNode("Key Name", strlen(szKeyName));
	pcNode2 = cIndexTree.GetNode("Amphibious", strlen(szAmphibious));
	pcNode3 = cIndexTree.GetNode("Amorphous", strlen(szAmorphous));
	pcNode4 = cIndexTree.GetNode("Test Fly", strlen(szTestFly));

	acKey.Init(8);
	cIndexTree.FindKey(pcNode1, &acKey);
	AssertInt(8, acKey.NumElements());
	acKey.Add(0);
	AssertString(szKeyName, acKey.GetData());
	acKey.Kill();

	acKey.Init(8);
	cIndexTree.FindKey(pcNode2, &acKey);
	acKey.Add(0);
	AssertString(szAmphibious, acKey.GetData());
	acKey.Kill();

	acKey.Init(8);
	cIndexTree.FindKey(pcNode3, &acKey);
	acKey.Add(0);
	AssertString(szAmorphous, acKey.GetData());
	acKey.Kill();

	acKey.Init(8);
	cIndexTree.FindKey(pcNode4, &acKey);
	acKey.Add(0);
	AssertString(szTestFly, acKey.GetData());
	acKey.Kill();

	acKey.Init(8);
	cIndexTree.FindKey(cIndexTree.GetRoot(), &acKey);
	AssertInt(0, acKey.NumElements());
	acKey.Kill();

	acKey.Init(8);
	cIndexTree.FindKey(NULL, &acKey);
	AssertInt(0, acKey.NumElements());
	acKey.Kill();

	memset(auiKey, 0, MAX_KEY_SIZE);
	cIndexTree.FindKey(pcNode1, auiKey, &iKeySize);
	AssertInt(8, iKeySize);
	AssertString(szKeyName, (char*)auiKey);

	cIndexTree.FindKey(pcNode4, auiKey, &iKeySize);
	AssertInt(8, iKeySize);
	AssertString(szTestFly, (char*)auiKey);

	cIndexTree.FindKey(pcNode3, auiKey, &iKeySize);
	AssertInt(9, iKeySize);
	AssertString(szAmorphous, (char*)auiKey);

	cIndexTree.FindKey(pcNode2, auiKey, &iKeySize);
	AssertInt(10, iKeySize);
	AssertString(szAmphibious, (char*)auiKey);

	apvNodes.Init();
	apvNodes.Add(pcNode1);
	apvNodes.Add(pcNode2);
	apvNodes.Add(pcNode3);
	apvNodes.Add(pcNode4);

	paszKeyNames = cIndexTree.FindStringKeys(&apvNodes);
	AssertInt(4, paszKeyNames->NumElements());
	AssertString(szKeyName, paszKeyNames->Get(0));
	AssertString(szAmphibious, paszKeyNames->Get(1));
	AssertString(szAmorphous, paszKeyNames->Get(2));
	AssertString(szTestFly, paszKeyNames->Get(3));

	paszKeyNames->Get(0, &iKeySize);  AssertInt(strlen(szKeyName) + 1, iKeySize);
	paszKeyNames->Get(1, &iKeySize);  AssertInt(strlen(szAmphibious) + 1, iKeySize);
	paszKeyNames->Get(2, &iKeySize);  AssertInt(strlen(szAmorphous) + 1, iKeySize);
	paszKeyNames->Get(3, &iKeySize);  AssertInt(strlen(szTestFly) + 1, iKeySize);

	free(paszKeyNames);
	apvNodes.Kill();

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
void TestIndexTreeFileDirty(void)
{
	char					szFoot[] = "Foot";
	char					szFork[] = "Fork";
	char					szGemstone[] = "Gemstone";
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;
	CIndexTreeFileAccess	cAccess;

	cHelper.Init("Output" _FS_"IndexTree6", "primary", "backup", "RootFile.IDX", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName(), FALSE);
	cAccess.Init(&cIndexTree);

	cIndexTree.Put("Foot", szFoot, (unsigned char)strlen(szFoot) + 1);
	cIndexTree.Flush();
	AssertInt(5, cIndexTree.NumNodes());
	cIndexTree.ValidateIndexTree();
	cDurableController.End();

	cDurableController.Begin();
	cIndexTree.Put("Fork", szFork, (unsigned char)strlen(szFork) + 1);
	cIndexTree.Put("Gemstone", szGemstone, (unsigned char)strlen(szGemstone) + 1);
	cIndexTree.Flush();
	AssertInt(15, cIndexTree.NumNodes());
	cIndexTree.ValidateIndexTree();

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
void TestIndexTreeFileReplaceData(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	BOOL						bResult;
	char						acData[5];
	char						acResult[5];
	int							iDataSize;

	cHelper.Init("Output" _FS_"IndexTree7", "primary", "backup", "RootFile.IDX", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName());
	cAccess.Init(&cIndexTree);

	memset(acData, 5, 5);
	bResult = cAccess.PutStringData("Quebc", acData, 5);
	AssertTrue(bResult);

	memset(acResult, 0, 5);
	bResult = cAccess.GetStringData("Quebc", acResult, &iDataSize);
	AssertTrue(bResult);
	AssertInt(0, memcmp(acData, acResult, 5));

	memset(acData, 0xfe, 5);
	bResult = cAccess.PutStringData("Quebc", acData, 5);
	AssertTrue(bResult);
	
	memset(acResult, 0, 5);
	bResult = cAccess.GetStringData("Quebc", acResult, &iDataSize);
	AssertTrue(bResult);
	AssertInt(0, memcmp(acData, acResult, 5));

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
void TestIndexTreeFileAddUnallocated(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		a;
	CTestIndexTreeObject		b;
	CTestIndexTreeObject		c;
	BOOL						bResult;

	cHelper.Init("Output" _FS_"IndexTree8", "primary", "backup", "RootFile.IDX", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName());
	cAccess.Init(&cIndexTree);

	a.Init("1A");
	c.Init("1C");
	b.Init("1B");

	bResult = cAccess.PutStringPtr(a.GetName(), &a);
	AssertTrue(bResult);
	AssertPointer(&a, *((CTestIndexTreeObject**)cIndexTree.GetNode(a.GetName(), 2)->GetObjectPtr()));

	bResult = cAccess.PutStringPtr(c.GetName(), &c);
	AssertTrue(bResult);
	AssertPointer(&a, *((CTestIndexTreeObject**)cIndexTree.GetNode(a.GetName(), 2)->GetObjectPtr()));
	AssertPointer(&c, *((CTestIndexTreeObject**)cIndexTree.GetNode(c.GetName(), 2)->GetObjectPtr()));

	bResult = cAccess.PutStringPtr(b.GetName(), &b);
	AssertTrue(bResult);
	AssertPointer(&a, *((CTestIndexTreeObject**)cIndexTree.GetNode(a.GetName(), 2)->GetObjectPtr()));
	AssertPointer(&b, *((CTestIndexTreeObject**)cIndexTree.GetNode(b.GetName(), 2)->GetObjectPtr()));
	AssertPointer(&c, *((CTestIndexTreeObject**)cIndexTree.GetNode(c.GetName(), 2)->GetObjectPtr()));

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
void TestIndexTreeFileRemoveThenDirty(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		a;
	CTestIndexTreeObject		b;
	CTestIndexTreeObject		c;
	char						sz[MAX_DATA_SIZE];

	cHelper.Init("Output" _FS_"IndexTree9", "primary", "backup", "RootFile.IDX", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, cHelper.GetRootFileName(), FALSE);
	cAccess.Init(&cIndexTree);

	a.Init("1A");
	c.Init("1C");
	b.Init("1B");

	AssertTrue(cAccess.PutStringString(a.GetName(), a.GetName()));
	AssertTrue(cAccess.GetStringString(a.GetName(), sz));
	AssertString(a.GetName(), sz);

	AssertTrue(cAccess.PutStringString(c.GetName(), c.GetName()));
	AssertTrue(cAccess.GetStringString(c.GetName(), sz));
	AssertString(c.GetName(), sz);

	AssertTrue(cIndexTree.Flush());

	AssertTrue(cAccess.DeleteString(a.GetName()));
	AssertFalse(cAccess.GetStringString(a.GetName(), sz));

	AssertTrue(cAccess.PutStringString(a.GetName(), b.GetName()));
	AssertTrue(cAccess.GetStringString(a.GetName(), sz));
	AssertString(b.GetName(), sz);

	AssertTrue(cIndexTree.Flush());
	AssertTrue(cAccess.GetStringString(a.GetName(), sz));
	AssertString(b.GetName(), sz);

	AssertTrue(cAccess.DeleteString(a.GetName()));
	AssertFalse(cAccess.GetStringString(a.GetName(), sz));

	AssertTrue(cAccess.PutStringString(a.GetName(), a.GetName()));
	AssertTrue(cAccess.GetStringString(a.GetName(), sz));
	AssertString(a.GetName(), sz);

	AssertTrue(cAccess.DeleteString(a.GetName()));
	AssertFalse(cAccess.GetStringString(a.GetName(), sz));

	AssertTrue(cIndexTree.Flush());
	AssertFalse(cAccess.GetStringString(a.GetName(), sz));

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

	TestIndexTreeFileSizeOfs();
	TestIndexTreeFileInit();
	TestIndexTreeFileAdd();
	TestIndexTreeFileAddUnallocated();
	TestIndexTreeFileReplaceData();
	TestIndexTreeFileFindKey();
	TestIndexTreeFileResizeData();
	TestIndexTreeFileRemove();
	TestIndexTreeFileNoCacheEviction();
	TestIndexTreeFileDelete();
	TestIndexTreeFileDirty();
	TestIndexTreeFileRemoveThenDirty();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

