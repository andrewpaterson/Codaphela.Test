#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/Logger.h"
#include "BaseLib/DebugOutput.h"
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

	cHelper.Init("Output" _FS_"QuakeMinusOne", "primary", "backup", TRUE);

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController);
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

	cHelper.Init("Output" _FS_"IndexTree0", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController);
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

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileGetNodeKey(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		a;
	BOOL						bResult;
	CIndexTreeNodeFile*			pcNode;
	int							iSize;
	char						szKey[7];

	cHelper.Init("Output" _FS_"IndexTree0a", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController);
	cAccess.Init(&cIndexTree);

	a.Init("Helper");
	bResult = cAccess.PutStringPtr(a.GetName(), &a);
	AssertTrue(bResult);

	pcNode = cIndexTree.GetNode(a.GetName(), a.NameLength());
	AssertNotNull(pcNode);

	iSize = cIndexTree.GetNodeKeySize(pcNode);
	AssertInt(a.NameLength(), iSize);

	cIndexTree.GetNodeKey(pcNode, (unsigned char*)szKey, 7);
	AssertString(a.GetName(), szKey);

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAddLongKeys(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		szAmicable;
	CTestIndexTreeObject		szAmigo;

	cHelper.Init("Output" _FS_"IndexTree0b", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController);
	cAccess.Init(&cIndexTree);

	szAmicable.Init("Amicable");
	AssertTrue(cAccess.PutStringPtr(szAmicable.GetName(), NULL));

	szAmigo.Init("Amigo");
	AssertTrue(cAccess.PutStringPtr(szAmigo.GetName(), NULL));

	cAccess.PutLongPtr(0x4142434430313233ll, NULL);
	
	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

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

	cHelper.Init("Output" _FS_"IndexTree1", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutLongString(0x0000000000000000LL, "Zero"));
	AssertInt(1, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree())

	AssertNotNull(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);

	bContinue = cIndexTree.StartIteration(&sIter, (void**)(&szData), &iSize);
	AssertTrue(bContinue);
	AssertInt(5, iSize);
	AssertString("Zero", szData);
	bContinue = cIndexTree.Iterate(&sIter, (void**)(&szData), &iSize);
	AssertFalse(bContinue);

	AssertNull(cAccess.GetLongString(0x0100000000000000LL, sz));

	AssertFalse(cAccess.PutLongString(0xEE89DD67CC45BB23LL, "Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sente."));
	AssertTrue(cAccess.PutLongString(0xEE89DD67CC45BB23LL, "Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent."));
	AssertInt(2, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree())

	AssertNotNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
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

	AssertNotNull(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("MORE node DATA", sz);

	AssertTrue(cAccess.PutLongString(0x0000DD00CC54BB23LL, "Another DATUM of doom"));
	AssertInt(4, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertNotNull(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.PutLongString(0x0098DD67CC45BB23LL, "Changed your data lengh"));
	AssertInt(4, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertNotNull(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertNotNull(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);
	AssertNotNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent.", sz);
	AssertNotNull(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.PutLongString(0xEE89DD67CC45BB23LL, "Make the long short."));
	AssertInt(4, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertNotNull(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertNotNull(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);
	AssertNotNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long short.", sz);
	AssertNotNull(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertFalse(cAccess.DeleteLong(0x0100000000000000LL));
	AssertFalse(cAccess.DeleteLong(0x00000000000000FFLL));
	AssertTrue(cAccess.DeleteLong(0x0000000000000000LL));
	AssertInt(3, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertNotNull(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertNotNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long short.", sz);
	AssertNotNull(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.DeleteLong(0x0098DD67CC45BB23LL));
	AssertInt(2, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertNull(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));

	AssertNotNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long short.", sz);
	AssertNotNull(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
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
	AssertNull(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));

	bContinue = cIndexTree.StartIteration(&sIter, (void**)(&szData), &iSize);
	AssertTrue(bContinue);
	AssertInt(21, iSize);
	AssertString("Make the long short.", szData);

	bContinue = cIndexTree.Iterate(&sIter, (void**)(&szData), &iSize);
	AssertFalse(bContinue);

	AssertNotNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long short.", sz);

	AssertTrue(cAccess.DeleteLong(0xEE89DD67CC45BB23LL));
	AssertInt(0, cIndexTree.NumElements());
	AssertNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

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
	CIndexTreeFileAccess	cAccess;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;
	CMemoryAllocator		cAllocator;
	CGeneralMemory*			pcMemory;

	cHelper.Init("Output" _FS_"IndexTree2", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cAllocator, IWT_Yes);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringData("AA", szAAObject, (unsigned char)strlen(szAAObject) + 1);
	cAccess.PutStringData("AC", szACObject, (unsigned char)strlen(szACObject) + 1);

	pcNode = cIndexTree.GetNode("A", 1);
	pcOldNode = pcNode;
	AssertInt(3, pcNode->NumIndexes());
	AssertInt(2, pcNode->NumValidIndexes());
	AssertInt(0, pcNode->ObjectSize());
	iNodeMemoryOffset1 = (size_t)pcNode->GetNodesMemory() - (size_t)pcNode;
	AssertInt(cIndexTree.SizeofNode(), iNodeMemoryOffset1);

	cAccess.PutStringData("A", szAObject, (unsigned char)strlen(szAObject) + 1);

	pcNode = cIndexTree.GetNode("A", 1);
	AssertFalse(pcNode == pcOldNode);
	AssertInt(3, pcNode->NumIndexes());
	AssertInt(2, pcNode->NumValidIndexes());
	AssertInt(18, pcNode->ObjectSize());
	iNodeMemoryOffset2 = (size_t)pcNode->GetNodesMemory() - (size_t)pcNode;
	AssertInt(cIndexTree.SizeofNode() + pcNode->ObjectSize(), iNodeMemoryOffset2);
	AssertTrue(iNodeMemoryOffset2 > iNodeMemoryOffset1);

	AssertString(szAAObject, GetString(&cIndexTree, "AA"));
	AssertString(szACObject, GetString(&cIndexTree, "AC"));
	AssertString(szAObject, GetString(&cIndexTree, "A"));

	pcRoot = cIndexTree.GetRoot();
	sz.Init(); pcRoot->Print(&sz, FALSE);
	AssertString("0:255 .................................................................X..............................................................................................................................................................................................", sz.Text()); sz.Kill();
	pcNode = pcRoot->Get('A')->u.mpcMemory;
	sz.Init(); pcNode->Print(&sz, FALSE);
	AssertString("65:67 (18) X.X", sz.Text()); sz.Kill();
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

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileRemoveNearestFirst(EIndexWriteThrough eWriteThrough)
{
	char					szAA[] = "MEDIUM";
	char					szAAA[] = "NEAR";
	char					szA[] = "Florida";
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;
	CIndexTreeFileAccess	cAccess;

	cHelper.Init("Output" _FS_"IndexTree3", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, eWriteThrough);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringData("AA", szAA, (unsigned char)strlen(szAA) + 1);
	cAccess.PutStringData("AAA", szAAA, (unsigned char)strlen(szAAA) + 1);
	cAccess.PutStringData("A", szA, (unsigned char)strlen(szA) + 1);
	AssertInt(3, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cIndexTree.Remove("A"));
	AssertString(NULL, GetString(&cIndexTree, "A"));
	AssertString(szAA, GetString(&cIndexTree, "AA"));
	AssertString(szAAA, GetString(&cIndexTree, "AAA"));
	AssertInt(2, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cIndexTree.Remove("AA"));
	AssertString(NULL, GetString(&cIndexTree, "A"));
	AssertString(NULL, GetString(&cIndexTree, "AA"));
	AssertString(szAAA, GetString(&cIndexTree, "AAA"));
	AssertInt(1, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cIndexTree.Remove("AAA"));
	AssertString(NULL, GetString(&cIndexTree, "A"));
	AssertString(NULL, GetString(&cIndexTree, "AA"));
	AssertString(NULL, GetString(&cIndexTree, "AAA"));
	AssertInt(0, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileRemoveFurthestFirst(EIndexWriteThrough eWriteThrough)
{
	char					szAA[] = "MEDIUM";
	char					szAAA[] = "NEAR";
	char					szA[] = "Florida";
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;
	CIndexTreeFileAccess	cAccess;

	cHelper.Init("Output" _FS_"IndexTree3a", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, eWriteThrough);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringData("AA", szAA, (unsigned char)strlen(szAA) + 1);
	cAccess.PutStringData("AAA", szAAA, (unsigned char)strlen(szAAA) + 1);
	cAccess.PutStringData("A", szA, (unsigned char)strlen(szA) + 1);
	AssertInt(3, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cIndexTree.Remove("AAA"));
	AssertString(szA, GetString(&cIndexTree, "A"));
	AssertString(szAA, GetString(&cIndexTree, "AA"));
	AssertString(NULL, GetString(&cIndexTree, "AAA"));
	AssertInt(2, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cIndexTree.Remove("AA"));
	AssertString(szA, GetString(&cIndexTree, "A"));
	AssertString(NULL, GetString(&cIndexTree, "AA"));
	AssertString(NULL, GetString(&cIndexTree, "AAA"));
	AssertInt(1, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cIndexTree.Remove("A"));
	AssertString(NULL, GetString(&cIndexTree, "A"));
	AssertString(NULL, GetString(&cIndexTree, "AA"));
	AssertString(NULL, GetString(&cIndexTree, "AAA"));
	AssertInt(0, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileRemove(EIndexWriteThrough eWriteThrough)
{
	char					szAAAA[] = "One and Ony";
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;
	CIndexTreeFileAccess	cAccess;
	CArrayIndexedFilePtr	apc;
	CIndexedFile*			pcFile;
	CArrayBit				ab;

	cHelper.Init("Output" _FS_"IndexTree3b", "primary", "backup", eWriteThrough);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_No);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringData("AAAA", szAAAA, (unsigned char)strlen(szAAAA) + 1);
	AssertInt(1, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	apc.Init();
	cIndexTree.GetFiles(&apc);
	AssertInt(3, apc.NumElements());

	pcFile = *apc.Get(0);
	AssertInt(26, pcFile->GetDataSize());
	ab.Init();
	AssertInt(1, pcFile->GetUsedDataIndices(&ab));
	AssertInt(1, ab.NumElements());
	ab.Kill();

	pcFile = *apc.Get(1);
	AssertInt(22, pcFile->GetDataSize());
	ab.Init();
	AssertInt(3, pcFile->GetUsedDataIndices(&ab));
	AssertInt(3, ab.NumElements());
	ab.Kill();

	pcFile = *apc.Get(2);
	AssertInt(2062, pcFile->GetDataSize());
	ab.Init();
	AssertInt(1, pcFile->GetUsedDataIndices(&ab));
	AssertInt(1, ab.NumElements());
	ab.Kill();
	apc.Kill();


	AssertTrue(cIndexTree.Remove("AAAA"));
	AssertNull(GetString(&cIndexTree, "AAAA"));
	AssertInt(0, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	apc.Init();
	cIndexTree.GetFiles(&apc);
	AssertInt(3, apc.NumElements());

	pcFile = *apc.Get(0);
	AssertInt(26, pcFile->GetDataSize());
	ab.Init();
	AssertInt(0, pcFile->GetUsedDataIndices(&ab));
	AssertInt(1, ab.NumElements());
	ab.Kill();

	pcFile = *apc.Get(1);
	AssertInt(22, pcFile->GetDataSize());
	ab.Init();
	AssertInt(0, pcFile->GetUsedDataIndices(&ab));
	AssertInt(3, ab.NumElements());
	ab.Kill();

	pcFile = *apc.Get(2);
	AssertInt(2062, pcFile->GetDataSize());
	ab.Init();
	AssertInt(1, pcFile->GetUsedDataIndices(&ab));
	AssertInt(1, ab.NumElements());
	ab.Kill();
	apc.Kill();

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileRemoveAndEvict(void)
{
	char					szABCD[] = "One and Only";
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;
	CIndexTreeFileAccess	cAccess;
	CArrayIndexedFilePtr	apc;
	CIndexedFile*			pcFile;
	CArrayBit				ab;

	cHelper.Init("Output" _FS_"IndexTree3c", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_No);
	cAccess.Init(&cIndexTree);

	AssertTrue(cIndexTree.IsFlushed());
	cAccess.PutStringData("ABCD", szABCD, (unsigned char)strlen(szABCD) + 1);
	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertFalse(cIndexTree.IsFlushed());
	AssertTrue(cIndexTree.Evict("ABCD"));
	AssertTrue(cIndexTree.IsFlushed());

	apc.Init();
	cIndexTree.GetFiles(&apc);
	AssertInt(3, apc.NumElements());

	pcFile = *apc.Get(0);
	AssertInt(27, pcFile->GetDataSize());
	ab.Init();
	AssertInt(1, pcFile->GetUsedDataIndices(&ab));
	AssertInt(1, ab.NumElements());
	ab.Kill();

	pcFile = *apc.Get(1);
	AssertInt(22, pcFile->GetDataSize());
	ab.Init();
	AssertInt(3, pcFile->GetUsedDataIndices(&ab));
	AssertInt(3, ab.NumElements());
	ab.Kill();

	pcFile = *apc.Get(2);
	AssertInt(2062, pcFile->GetDataSize());
	ab.Init();
	AssertInt(1, pcFile->GetUsedDataIndices(&ab));
	AssertInt(1, ab.NumElements());
	ab.Kill();
	apc.Kill();


	AssertTrue(cIndexTree.Remove("ABCD"));
	AssertTrue(cIndexTree.Evict("ABCD"));

	apc.Init();
	cIndexTree.GetFiles(&apc);
	AssertInt(3, apc.NumElements());

	pcFile = *apc.Get(0);
	AssertInt(27, pcFile->GetDataSize());
	ab.Init();
	AssertInt(0, pcFile->GetUsedDataIndices(&ab));
	AssertInt(1, ab.NumElements());
	ab.Kill();

	pcFile = *apc.Get(1);
	AssertInt(22, pcFile->GetDataSize());
	ab.Init();
	AssertInt(0, pcFile->GetUsedDataIndices(&ab));
	AssertInt(3, ab.NumElements());
	ab.Kill();

	pcFile = *apc.Get(2);
	AssertInt(2062, pcFile->GetDataSize());
	ab.Init();
	AssertInt(1, pcFile->GetUsedDataIndices(&ab));
	AssertInt(1, ab.NumElements());
	ab.Kill();
	apc.Kill();

	cIndexTree.ValidateIndexTree();
	cDurableController.End();
	cIndexTree.Kill();
	cDurableController.Kill();
	cAccess.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileRemoveAndFlush(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CMemoryAllocator			cAllocator;
	char						szAABAA[] = "AABAA";
	char						szAABBB[] = "AABBB";
	char						szAACAA[] = "AACAA";
	char						szAACBB[] = "AACBB";
	CIndexTreeFileAccess		cAccess;
	char						szDest[16];

	cAllocator.Init();
	cHelper.Init("Output" _FS_"IndexTree3d", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cAllocator, IWT_Yes);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutStringString(szAABAA, szAABAA));
	AssertTrue(cAccess.PutStringString(szAABBB, szAABBB));
	AssertTrue(cAccess.PutStringString(szAACAA, szAACAA));
	AssertTrue(cAccess.PutStringString(szAACBB, szAACBB));

	cDurableController.End();
	cIndexTree.Kill();

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cAllocator, IWT_No);
	cAccess.Init(&cIndexTree);
	AssertInt(0, cIndexTree.NumMemoryElements());
	AssertInt(1, cIndexTree.NumMemoryNodes());
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNotNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAACBB, szDest));
	AssertInt(4, cIndexTree.NumElements());
	AssertInt(13, cIndexTree.NumNodes());
	AssertInt(4, cIndexTree.NumMemoryElements());
	AssertInt(13, cIndexTree.NumMemoryNodes());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cAccess.DeleteString(szAACBB));
	AssertTrue(cAccess.Flush());

	AssertInt(3, cIndexTree.NumMemoryElements());
	AssertInt(11, cIndexTree.NumMemoryNodes());
	AssertInt(3, cIndexTree.NumElements());
	AssertInt(11, cIndexTree.NumNodes());
	AssertTrue(cIndexTree.ValidateIndexTree());

	cDurableController.End();

	cIndexTree.Kill();
	cDurableController.Kill();
	cAllocator.Kill();

	cHelper.Kill(TRUE);
	cAccess.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileDeleteInMemory(void)
{
	char					szAA[] = "MEDIUM";
	char					szAAA[] = "NEAR";
	char					szA[] = "Florida";
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cDurableController;
	CIndexTreeFileAccess	cAccess;
	
	cHelper.Init("Output" _FS_"IndexTree4", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_Yes);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringData("AA", szAA, (unsigned char)strlen(szAA) + 1);
	cAccess.PutStringData("AAA", szAAA, (unsigned char)strlen(szAAA) + 1);
	cAccess.PutStringData("A", szA, (unsigned char)strlen(szA) + 1);
	AssertInt(3, cIndexTree.NumElements());

	cIndexTree.SetWriteThrough(IWT_No);

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
	CIndexTreeFileAccess	cAccess;
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

	cHelper.Init("Output" _FS_"IndexTree5", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringData(szKeyName, szData, 5);
	cAccess.PutStringData(szAmphibious, szData, 5);
	cAccess.PutStringData(szAmorphous, szData, 5);
	cAccess.PutStringData(szTestFly, szData, 5);

	pcNode1 = cIndexTree.GetNode("Key Name", strlen(szKeyName));
	pcNode2 = cIndexTree.GetNode("Amphibious", strlen(szAmphibious));
	pcNode3 = cIndexTree.GetNode("Amorphous", strlen(szAmorphous));
	pcNode4 = cIndexTree.GetNode("Test Fly", strlen(szTestFly));

	acKey.Init();
	cIndexTree.FindKey(pcNode1, &acKey);
	AssertInt(8, acKey.NumElements());
	acKey.Add(0);
	AssertString(szKeyName, acKey.GetData());
	acKey.Kill();

	acKey.Init();
	cIndexTree.FindKey(pcNode2, &acKey);
	acKey.Add(0);
	AssertString(szAmphibious, acKey.GetData());
	acKey.Kill();

	acKey.Init();
	cIndexTree.FindKey(pcNode3, &acKey);
	acKey.Add(0);
	AssertString(szAmorphous, acKey.GetData());
	acKey.Kill();

	acKey.Init();
	cIndexTree.FindKey(pcNode4, &acKey);
	acKey.Add(0);
	AssertString(szTestFly, acKey.GetData());
	acKey.Kill();

	acKey.Init();
	cIndexTree.FindKey(cIndexTree.GetRoot(), &acKey);
	AssertInt(0, acKey.NumElements());
	acKey.Kill();

	acKey.Init();
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

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

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

	cHelper.Init("Output" _FS_"IndexTree6", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_No);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringData("Foot", szFoot, (unsigned char)strlen(szFoot) + 1);
	cIndexTree.Flush();
	AssertInt(5, cIndexTree.NumNodes());
	cIndexTree.ValidateIndexTree();
	cDurableController.End();

	cDurableController.Begin();
	cAccess.PutStringData("Fork", szFork, (unsigned char)strlen(szFork) + 1);
	cAccess.PutStringData("Gemstone", szGemstone, (unsigned char)strlen(szGemstone) + 1);
	cIndexTree.Flush();
	AssertInt(15, cIndexTree.NumNodes());
	cIndexTree.ValidateIndexTree();

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

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
	unsigned int				iDataSize;

	cHelper.Init("Output" _FS_"IndexTree7", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController);
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

	cHelper.Init("Output" _FS_"IndexTree8", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController);
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

	cHelper.Init("Output" _FS_"IndexTree9", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_No);
	cAccess.Init(&cIndexTree);

	a.Init("1A");
	c.Init("1C");
	b.Init("1B");

	AssertTrue(cAccess.PutStringString(a.GetName(), a.GetName()));
	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString(a.GetName(), sz);

	AssertTrue(cAccess.PutStringString(c.GetName(), c.GetName()));
	AssertNotNull(cAccess.GetStringString(c.GetName(), sz));
	AssertString(c.GetName(), sz);

	AssertTrue(cIndexTree.Flush());

	AssertTrue(cAccess.DeleteString(a.GetName()));
	AssertNull(cAccess.GetStringString(a.GetName(), sz));

	AssertTrue(cAccess.PutStringString(a.GetName(), b.GetName()));
	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString(b.GetName(), sz);

	AssertTrue(cIndexTree.Flush());
	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString(b.GetName(), sz);

	AssertTrue(cAccess.DeleteString(a.GetName()));
	AssertNull(cAccess.GetStringString(a.GetName(), sz));

	AssertTrue(cAccess.PutStringString(a.GetName(), a.GetName()));
	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString(a.GetName(), sz);

	AssertTrue(cAccess.DeleteString(a.GetName()));
	AssertNull(cAccess.GetStringString(a.GetName(), sz));

	AssertTrue(cIndexTree.Flush());
	AssertNull(cAccess.GetStringString(a.GetName(), sz));

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

	cHelper.Kill(TRUE);
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAddThenAdd(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		a;
	CTestIndexTreeObject		b;
	char						sz[MAX_DATA_SIZE];

	cHelper.Init("Output" _FS_"IndexTree9a", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_No);
	cAccess.Init(&cIndexTree);

	a.Init("AA");
	b.Init("AAAA");

	AssertTrue(cAccess.PutStringString(a.GetName(), a.GetName()));

	cIndexTree.Flush();
	cDurableController.End();
	cIndexTree.Kill();


	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_No);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutStringString(b.GetName(), b.GetName()));

	cIndexTree.Flush();
	cDurableController.End();
	cIndexTree.Kill();


	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_No);
	cAccess.Init(&cIndexTree);

	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString(a.GetName(), sz);
	AssertNotNull(cAccess.GetStringString(b.GetName(), sz));
	AssertString(b.GetName(), sz);

	cIndexTree.Flush();
	cDurableController.End();
	cIndexTree.Kill();

	cAccess.Kill();
	cDurableController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileRead(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	char						sz[MAX_DATA_SIZE];
	CIndexTreeNodeFile*			pcHell;
	int							iOldFile;
	int							iNewFile;
	CIndexedFile*				pcFile;

	cHelper.Init("Output" _FS_"IndexTreeA", "primary", "backup", TRUE);
	cHelper.RemoveWorkingDirectory();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_No);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringString("Hello", "World");

	cAccess.Flush();
	cDurableController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

	AssertTrue(cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory()));
	AssertTrue(cDurableController.Begin());
	AssertTrue(cIndexTree.Init(&cDurableController, IWT_No));
	AssertTrue(cAccess.Init(&cIndexTree));

	AssertNotNull(cAccess.GetStringString("Hello", sz));
	AssertString("World", sz)

	AssertTrue(cAccess.Flush());
	pcHell = cIndexTree.GetNode("Hell", 4);
	iOldFile = pcHell->GetFileIndex()->miFile;
	pcFile = cIndexTree.GetFile(iOldFile);
	AssertNotNull(pcFile);
	AssertInt(22, pcFile->GetDataSize());
	AssertTrue(cDurableController.End());
	cIndexTree.Kill();
	cDurableController.Kill();

	AssertTrue(cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory()));
	AssertTrue(cDurableController.Begin());
	AssertTrue(cIndexTree.Init(&cDurableController, IWT_Yes));
	AssertTrue(cDurableController.End());

	AssertTrue(cDurableController.Begin());
	AssertTrue(cAccess.PutStringString("Hell", "Fuzz"));
	pcHell = cIndexTree.GetNode("Hell", 4);
	iNewFile = pcHell->GetFileIndex()->miFile;
	AssertTrue(iOldFile != iNewFile);
	pcFile = cIndexTree.GetFile(iNewFile);
	AssertNotNull(pcFile);
	AssertInt(27, pcFile->GetDataSize());
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertTrue(cDurableController.End());
	iOldFile = iNewFile;

	AssertTrue(cDurableController.Begin());
	AssertNotNull(cAccess.GetStringString("Hell", sz));
	AssertString("Fuzz", sz);
	AssertNotNull(cAccess.GetStringString("Hello", sz));
	AssertString("World", sz);
	AssertTrue(cDurableController.End());

	cIndexTree.Kill();

	AssertTrue(cDurableController.Begin());
	AssertTrue(cIndexTree.Init(&cDurableController, IWT_Yes));
	AssertNotNull(cAccess.GetStringString("Hell", sz));
	AssertString("Fuzz", sz);
	pcHell = cIndexTree.GetNode("Hell", 4);
	iNewFile = pcHell->GetFileIndex()->miFile;
	AssertTrue(iOldFile == iNewFile);
	AssertTrue(cDurableController.End());
	cIndexTree.Kill();

	AssertTrue(cDurableController.Begin());
	AssertTrue(cIndexTree.Init(&cDurableController, IWT_Yes));
	AssertTrue(cDurableController.End());

	AssertTrue(cDurableController.Begin());
	AssertTrue(cAccess.PutStringString("HelloX", "3"));
	AssertTrue(cDurableController.End());

	AssertTrue(cDurableController.Begin());
	AssertNotNull(cAccess.GetStringString("Hell", sz));
	AssertString("Fuzz", sz);
	AssertNotNull(cAccess.GetStringString("HelloX", sz));
	AssertString("3", sz);
	AssertNotNull(cAccess.GetStringString("Hello", sz));
	AssertString("World", sz);
	AssertTrue(cDurableController.End());
	cIndexTree.Kill();

	AssertTrue(cAccess.Kill());
	cDurableController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileDeleteOnDisk(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	char						sz[MAX_DATA_SIZE];
	CIndexTreeNodeFile*			pcNode;

	cHelper.Init("Output" _FS_"IndexTreeB", "primary", "backup", TRUE);
	cHelper.RemoveWorkingDirectory();

	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_Yes);
	cAccess.Init(&cIndexTree);
	cAccess.PutStringString("Hello", "World");
	cDurableController.End();
	cIndexTree.Kill();

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_Yes);
	cAccess.DeleteString("Hello");
	cDurableController.End();
	cIndexTree.Kill();

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_Yes);
	AssertNull(cAccess.GetStringString("Hello", sz));
	pcNode = cIndexTree.GetNode("H", 1);
	cDurableController.End();
	cIndexTree.Kill();

	CNaiveFile	cNaiveFile;
	int			i;
	char*		pcFileMem;

	cNaiveFile.Init();
	AssertTrue(cNaiveFile.Read("Output/IndexTreeB/primary/20_0.IDAT"));
	pcFileMem = (char*)cNaiveFile.Get();
	for (i = 0; i < cNaiveFile.Size(); i++)
	{
		AssertChar(INDEX_FILE_EMPTY_CHAR, pcFileMem[i]);
	}
	cNaiveFile.Kill();

	cNaiveFile.Init();
	AssertTrue(cNaiveFile.Read("Output/IndexTreeB/primary/22_0.IDAT"));
	pcFileMem = (char*)cNaiveFile.Get();
	for (i = 0; i < cNaiveFile.Size(); i++)
	{
		AssertChar(INDEX_FILE_EMPTY_CHAR, pcFileMem[i]);
	}
	cNaiveFile.Kill();

	cAccess.Kill();
	cDurableController.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileComplex(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	char						sz[MAX_DATA_SIZE];
	CMapStringString			cMap;
	SMapIterator				sIter;
	BOOL						bHasNext;
	char*						szKey;
	char*						szValue;

	cMap.Init(32);

	cMap.Put("bane", "poison");
	cMap.Put("baseborn", "of low birth or social standing");
	cMap.Put("bedlam", "an asylum");
	cMap.Put("behoo", "see or observe");
	cMap.Put("behoof", "benefit or advantage");
	cMap.Put("beldam", "an old woman");
	cMap.Put("bethink oneself of", "remember; recollect");
	cMap.Put("betimes", "in good time; early");
	cMap.Put("bibliopole", "a dealer in books");
	cMap.Put("bijoux", "jewellery; trinkets");
	cMap.Put("billow", "a large sea wave");
	cMap.Put("blackguard", "a scoundrel");
	cMap.Put("blow", "produce flowers or be in flower");
	cMap.Put("bodkin", "a dagger");
	cMap.Put("bootless", "ineffectual; useless");
	cMap.Put("breech", "a person's buttocks");
	cMap.Put("bridewell", "a prison or reform school for petty offenders");
	cMap.Put("brimstone", "sulphur");
	cMap.Put("bruit", "a report or rumour");
	cMap.Put("buck", "a fashionable and daring young man");
	cMap.Put("bumper", "a generous glass of an alcoholic drink");
	cMap.Put("burgess", "a full citizen of a town or borough");
	cMap.Put("buss", "a kiss");

	cMap.Put("dame", "an elderly or mature woman");
	cMap.Put("damsel", "a young unmarried woman");
	cMap.Put("dandiprat", "a young or insignificant person");
	cMap.Put("darbies", "handcuffs");
	cMap.Put("dark", "ignorant");
	cMap.Put("degrade", "reduce to a lower rank, especially as a punishment");
	cMap.Put("degree", "social or official rank");
	cMap.Put("delate", "report(an offence)");
	cMap.Put("demesne", "a region or domain");
	cMap.Put("demit", "resign from(an office or position)");
	cMap.Put("demoralize", "corrupt the morals of");
	cMap.Put("dight", "clothed or equipped");
	cMap.Put("discover", "divulge(a secret)");
	cMap.Put("disport", "frolic");
	cMap.Put("dispraise", "censure or criticize");
	cMap.Put("divers", "of varying types; several");
	cMap.Put("doti", "a very small amount of money");
	cMap.Put("dot", "a dowry from which only the interest or annual income was available to the husband");
	cMap.Put("doxy", "a lover or mistress");
	cMap.Put("drab", "a slovenly woman");
	cMap.Put("drought", "thirst");

	cHelper.Init("Output" _FS_"IndexTreeC", "primary", "backup", TRUE);
	cHelper.RemoveWorkingDirectory();

	//////////////////////////////////////////////////////////////////////////////////////
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_Yes);
	cAccess.Init(&cIndexTree);

	bHasNext = cMap.StartIteration(&sIter, (void**)&szKey, (void**)&szValue);
	while (bHasNext)
	{
		AssertTrue(cAccess.PutStringString(szKey, szValue));
		cIndexTree.ValidateKey(szKey, strlen(szKey));
		bHasNext = cMap.Iterate(&sIter, (void**)&szKey, (void**)&szValue);
	}
	AssertInt(cMap.NumElements(), cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	bHasNext = cMap.StartIteration(&sIter, (void**)&szKey, (void**)&szValue);
	while (bHasNext)
	{
		AssertNotNull(cAccess.GetStringString(szKey, sz));
		szValue = cMap.Get(szKey);
		AssertString(szValue, sz);

		bHasNext = cMap.Iterate(&sIter, (void**)&szKey, (void**)&szValue);
	}

	cDurableController.End();
	cIndexTree.Kill();
	cAccess.Kill();
	cDurableController.Kill();

	//////////////////////////////////////////////////////////////////////////////////////
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, IWT_Yes);
	cAccess.Init(&cIndexTree);

	bHasNext = cMap.StartIteration(&sIter, (void**)&szKey, (void**)&szValue);
	while (bHasNext)
	{
		AssertNotNull(cAccess.GetStringString(szKey, sz));
		szValue = cMap.Get(szKey);
		AssertString(szValue, sz);
		
		bHasNext = cMap.Iterate(&sIter, (void**)&szKey, (void**)&szValue);
	}

	cDurableController.End();
	cIndexTree.Kill();
	cAccess.Kill();
	cDurableController.Kill();

	cMap.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAddToRoot(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		a;
	CTestIndexTreeObject		b;
	BOOL						bResult;

	//This is supposed to be checking that the nodes indexed in file are in sync with the nodes pointed to in memory.
	cHelper.Init("Output" _FS_"IndexTreeD", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController);
	cAccess.Init(&cIndexTree);

	a.Init("A1");
	bResult = cAccess.PutStringPtr(a.GetName(), &a);
	AssertTrue(bResult);
	cIndexTree.ValidateKey(a.GetName(), a.NameLength());
	AssertTrue(cIndexTree.ValidateIndexTree());

	b.Init("D1");
	bResult = cAccess.PutStringPtr(b.GetName(), &b);
	cIndexTree.ValidateKey(a.GetName(), a.NameLength());
	cIndexTree.ValidateKey(b.GetName(), b.NameLength());
	AssertTrue(bResult);
	AssertTrue(cIndexTree.ValidateIndexTree());

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileMemorySize(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		aaa;
	CTestIndexTreeObject		aab;
	BOOL						bResult;

	cHelper.Init("Output" _FS_"IndexTreeE", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController);
	cAccess.Init(&cIndexTree);

	AssertInt(3096, cIndexTree.ByteSize());
	AssertInt(3096, cIndexTree.GetUserMemorySize());
	AssertInt(3100, cIndexTree.GetSystemMemorySize());

	aaa.Init("AAA");
	bResult = cAccess.PutStringPtr(aaa.GetName(), &aaa);
	AssertTrue(bResult);

	AssertInt(3196, cIndexTree.ByteSize());
	AssertInt(3196, cIndexTree.GetUserMemorySize());
	AssertInt(3212, cIndexTree.GetSystemMemorySize());

	aab.Init("AAB");
	bResult = cAccess.PutStringPtr(aab.GetName(), &aab);
	AssertTrue(bResult);

	AssertInt(3236, cIndexTree.ByteSize());
	AssertInt(3236, cIndexTree.GetUserMemorySize());
	AssertInt(3256, cIndexTree.GetSystemMemorySize());

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileEvictNew(EIndexWriteThrough eWriteThrough)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	char						szAAA[] = "North";
	char						szAAAAA[] = "Volcano";
	char						szA[] = "Tier";
	char						szAAAB[] = "Abland";
	CMemoryAllocator			cAllocator;
	CGeneralMemory*				pcMemory;

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();

	cHelper.Init("Output" _FS_"IndexTreeF", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cAllocator, eWriteThrough);
	cAccess.Init(&cIndexTree);

	AssertInt(0, cIndexTree.NumElements());
	AssertInt(1, cIndexTree.NumNodes());
	AssertInt(0, cIndexTree.NumMemoryElements());
	AssertInt(1, cIndexTree.NumMemoryNodes());
	AssertLongLongInt(3096, pcMemory->GetTotalAllocatedMemory());

	cAccess.PutStringData("AAA", szAAA, (unsigned char)strlen(szAAA) + 1);
	cAccess.PutStringData("AAAAA", szAAAAA, (unsigned char)strlen(szAAAAA) + 1);
	cAccess.PutStringData("A", szA, (unsigned char)strlen(szA) + 1);
	cAccess.PutStringData("AAAB", szAAAB, (unsigned char)strlen(szAAAB) + 1);
	AssertLongLongInt(3326, pcMemory->GetTotalAllocatedMemory());
	AssertInt(4, cIndexTree.NumElements());
	AssertInt(7, cIndexTree.NumNodes());
	AssertInt(4, cIndexTree.NumMemoryElements());
	AssertInt(7, cIndexTree.NumMemoryNodes());

	AssertTrue(cIndexTree.Evict("AAAAA"));
	AssertLongLongInt(3258, pcMemory->GetTotalAllocatedMemory());
	AssertInt(3, cIndexTree.NumMemoryElements());
	AssertInt(5, cIndexTree.NumMemoryNodes());

	AssertTrue(cIndexTree.Evict("AAAB"));
	AssertLongLongInt(3227, pcMemory->GetTotalAllocatedMemory());
	AssertInt(2, cIndexTree.NumMemoryElements());
	AssertInt(4, cIndexTree.NumMemoryNodes());
	AssertTrue(cIndexTree.Evict("AAA"));
	AssertLongLongInt(3137, pcMemory->GetTotalAllocatedMemory());
	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertInt(2, cIndexTree.NumMemoryNodes());
	AssertTrue(cIndexTree.Evict("A"));
	AssertLongLongInt(3096, pcMemory->GetTotalAllocatedMemory());
	AssertInt(0, cIndexTree.NumMemoryElements());
	AssertInt(1, cIndexTree.NumMemoryNodes());

	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertTrue(cAccess.HasString("A"));
	AssertTrue(cAccess.HasString("AAA"));
	AssertTrue(cAccess.HasString("AAAB"));
	AssertTrue(cAccess.HasString("AAAAA"));
	AssertInt(4, cIndexTree.NumMemoryElements());
	AssertInt(7, cIndexTree.NumMemoryNodes());
	AssertInt(4, cIndexTree.NumElements());
	AssertInt(7, cIndexTree.NumNodes());

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();
	cAllocator.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileEvictDirty(EIndexWriteThrough eWriteThrough)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	char						szAAA[] = "North";
	char						szAAAAA[] = "Volcano";
	char						szA[] = "Tier";
	char						szAAAB[] = "Abland";
	CMemoryAllocator			cAllocator;
	CGeneralMemory*				pcMemory;
	SLogConfig					sLogConfig;

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();

	cHelper.Init("Output" _FS_"IndexTreeFa", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cAllocator, eWriteThrough);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringString("AAA", "North");
	cAccess.PutStringString("AAAAA", "Volcano");
	cAccess.PutStringString("A", "Tier");
	cAccess.PutStringString("AAAB", "Abland");
	AssertTrue(cAccess.Flush());
	AssertInt(4, cIndexTree.NumMemoryElements());
	AssertTrue(cIndexTree.ValidateIndexTree(FALSE));

	cAccess.PutStringString("AAA", "South");
	cAccess.PutStringString("AAAAA", "Dome");

	gcLogger.GetConfig(&sLogConfig);
	gcLogger.SetBreakOnError(FALSE);
	AssertFalse(cIndexTree.Evict("AAA"));
	gcLogger.SetConfig(&sLogConfig);
	AssertInt(4, cIndexTree.NumMemoryElements());
	AssertTrue(cIndexTree.Evict("AAAAA"));
	AssertInt(3, cIndexTree.NumMemoryElements());
	AssertTrue(cIndexTree.Evict("AAAB"));
	AssertInt(2, cIndexTree.NumMemoryElements());
	AssertTrue(cIndexTree.Evict("AAA"));
	AssertTrue(cIndexTree.ValidateIndexTree(FALSE));
	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertTrue(cIndexTree.Evict("A"));
	AssertInt(0, cIndexTree.NumMemoryElements());
	AssertTrue(cIndexTree.ValidateIndexTree(FALSE));

	cDurableController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cDurableController.Kill();
	cAllocator.Kill();

	cHelper.Kill(TRUE);
}


/////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileEvictComplexSetup(CDurableFileController* pcDurableController, CIndexTreeFile* pcIndexTree, CMemoryAllocator* pcAllocator)
{
	CIndexTreeFileAccess		cAccess;
	char						szAAAAA[] = "AAAAA";
	char						szAAABB[] = "AAABB";
	char						szAABAA[] = "AABAA";
	char						szAABBB[] = "AABBB";
	char						szAACAA[] = "AACAA";
	char						szAACBB[] = "AACBB";
	char						szDest[16];
	EIndexWriteThrough			eWriteThrough;
	CGeneralMemory*				pcMemory;

	eWriteThrough = IWT_No;
	pcMemory = pcAllocator->GetMemory();

	pcDurableController->Begin();
	pcIndexTree->Init(pcDurableController, pcAllocator, eWriteThrough);
	cAccess.Init(pcIndexTree);

	AssertTrue(cAccess.PutStringString(szAAAAA, szAAAAA));
	AssertTrue(cAccess.PutStringString(szAAABB, szAAABB));
	AssertTrue(cAccess.PutStringString(szAABAA, szAABAA));
	AssertTrue(cAccess.PutStringString(szAABBB, szAABBB));
	AssertTrue(cAccess.PutStringString(szAACAA, szAACAA));
	AssertTrue(cAccess.PutStringString(szAACBB, szAACBB));
	AssertLongLongInt(3732, pcMemory->GetTotalAllocatedMemory());
	AssertInt(6, pcIndexTree->NumMemoryElements());
	AssertInt(18, pcIndexTree->NumMemoryNodes());
	AssertInt(6, pcIndexTree->NumElements());
	AssertInt(18, pcIndexTree->NumNodes());

	AssertTrue(cAccess.Flush());
	AssertTrue(pcIndexTree->ValidateIndexTree());

	pcDurableController->End();
	pcIndexTree->Kill();
	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());


	pcDurableController->Begin();
	pcIndexTree->Init(pcDurableController, pcAllocator, eWriteThrough);
	cAccess.Init(pcIndexTree);
	AssertLongLongInt(3120, pcMemory->GetTotalAllocatedMemory());
	AssertInt(0, pcIndexTree->NumMemoryElements());
	AssertInt(1, pcIndexTree->NumMemoryNodes());
	AssertInt(6, pcIndexTree->NumElements());
	AssertInt(18, pcIndexTree->NumNodes());
	AssertInt(6, pcIndexTree->NumMemoryElements());
	AssertInt(18, pcIndexTree->NumMemoryNodes());
	AssertLongLongInt(3828, pcMemory->GetTotalAllocatedMemory());
	AssertNotNull(cAccess.GetStringString(szAAAAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAAABB, szDest));
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNotNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAACBB, szDest));

	AssertTrue(cAccess.PutStringString(szAAAAA, "Update 1"));
	AssertTrue(cAccess.PutStringString(szAAABB, "Update 2"));
	AssertTrue(cAccess.PutStringString(szAABAA, "Update 3"));
	AssertTrue(cAccess.DeleteString(szAABBB));
	AssertTrue(cAccess.DeleteString(szAACAA));
	AssertTrue(cAccess.DeleteString(szAACBB));

	cAccess.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileEvictComplexEvictCloseGet(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CGeneralMemory*				pcMemory;
	CIndexTreeFile				cIndexTree;
	CMemoryAllocator			cAllocator;
	char						szAAAAA[] = "AAAAA";
	char						szAAABB[] = "AAABB";
	char						szAABAA[] = "AABAA";
	char						szAABBB[] = "AABBB";
	char						szAACAA[] = "AACAA";
	char						szAACBB[] = "AACBB";
	CIndexTreeFileAccess		cAccess;
	char						szDest[16];

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();
	
	cHelper.Init("Output" _FS_"IndexTreeG", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	TestIndexTreeFileEvictComplexSetup(&cDurableController, &cIndexTree, &cAllocator);
	AssertLongLongInt(3801, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cIndexTree.Evict(szAABBB));
	AssertTrue(cIndexTree.Evict(szAAAAA));
	AssertTrue(cIndexTree.Evict(szAAABB));
	AssertTrue(cIndexTree.Evict(szAABAA));
	AssertTrue(cIndexTree.Evict(szAACAA));
	AssertTrue(cIndexTree.Evict(szAACBB));
	AssertLongLongInt(3204, pcMemory->GetTotalAllocatedMemory());

	AssertInt(0, cIndexTree.NumMemoryElements());
	AssertInt(3, cIndexTree.NumMemoryNodes());
	AssertInt(3, cIndexTree.NumElements());
	AssertInt(11, cIndexTree.NumNodes());
	
	//Also test to make sure that the CIndexedFiles in the tree reflect the correct number of allocated and deleted nodes.

	cDurableController.End();
	cIndexTree.Kill();
	cDurableController.Kill();
	cAllocator.Kill();

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cAllocator, IWT_No);
	cAccess.Init(&cIndexTree);
	AssertNotNull(cAccess.GetStringString(szAAAAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAAABB, szDest));
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNull(cAccess.GetStringString(szAACBB, szDest));
	AssertTrue(cIndexTree.ValidateIndexTree());
	cDurableController.End();
	cIndexTree.Kill();

	cDurableController.Kill();
	cAllocator.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileEvictComplexEvictGetClose(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CGeneralMemory*				pcMemory;
	CIndexTreeFile				cIndexTree;
	CMemoryAllocator			cAllocator;
	char						szAAAAA[] = "AAAAA";
	char						szAAABB[] = "AAABB";
	char						szAABAA[] = "AABAA";
	char						szAABBB[] = "AABBB";
	char						szAACAA[] = "AACAA";
	char						szAACBB[] = "AACBB";
	CIndexTreeFileAccess		cAccess;
	char						szDest[16];

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();

	cHelper.Init("Output" _FS_"IndexTreeG", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	TestIndexTreeFileEvictComplexSetup(&cDurableController, &cIndexTree, &cAllocator);
	AssertLongLongInt(3801, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cIndexTree.Evict(szAABBB));
	AssertTrue(cIndexTree.Evict(szAAAAA));
	AssertTrue(cIndexTree.Evict(szAAABB));
	AssertTrue(cIndexTree.Evict(szAABAA));
	AssertTrue(cIndexTree.Evict(szAACAA));
	AssertTrue(cIndexTree.Evict(szAACBB));

	AssertInt(0, cIndexTree.NumMemoryElements());
	AssertInt(3, cIndexTree.NumMemoryNodes());
	AssertInt(3, cIndexTree.NumElements());
	AssertInt(11, cIndexTree.NumNodes());

	cAccess.Init(&cIndexTree);
	AssertNotNull(cAccess.GetStringString(szAAAAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAAABB, szDest));
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNull(cAccess.GetStringString(szAACBB, szDest));

	cDurableController.End();
	cIndexTree.Kill();
	cDurableController.Kill();
	cAllocator.Kill();
	cAccess.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileEvictComplexEvictOdd(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CGeneralMemory*				pcMemory;
	CIndexTreeFile				cIndexTree;
	CMemoryAllocator			cAllocator;
	char						szAAAAA[] = "AAAAA";
	char						szAAABB[] = "AAABB";
	char						szAABAA[] = "AABAA";
	char						szAABBB[] = "AABBB";
	char						szAACAA[] = "AACAA";
	char						szAACBB[] = "AACBB";
	CIndexTreeFileAccess		cAccess;
	char						szDest[16];

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();

	cHelper.Init("Output" _FS_"IndexTreeG", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	TestIndexTreeFileEvictComplexSetup(&cDurableController, &cIndexTree, &cAllocator);
	AssertLongLongInt(3801, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cIndexTree.Evict(szAABBB));
	AssertTrue(cIndexTree.Evict(szAAABB));
	AssertTrue(cIndexTree.Evict(szAACAA));

	AssertInt(2, cIndexTree.NumMemoryElements());
	AssertInt(12, cIndexTree.NumMemoryNodes());

	cAccess.Init(&cIndexTree);
	AssertNotNull(cAccess.GetStringString(szAAAAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAAABB, szDest));
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNull(cAccess.GetStringString(szAACBB, szDest));

	cAccess.Flush();
	cDurableController.End();
	cIndexTree.Kill();
	cDurableController.Kill();
	cAllocator.Kill();
	cAccess.Kill();

	cAllocator.Init();
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cAllocator, IWT_No);
	cAccess.Init(&cIndexTree);
	AssertNotNull(cAccess.GetStringString(szAAAAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAAABB, szDest));
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNull(cAccess.GetStringString(szAACBB, szDest));
	cDurableController.End();
	cIndexTree.Kill();
	cDurableController.Kill();
	cAllocator.Kill();
	cAccess.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileEvictComplexEvictEven(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CGeneralMemory*				pcMemory;
	CIndexTreeFile				cIndexTree;
	CMemoryAllocator			cAllocator;
	char						szAAAAA[] = "AAAAA";
	char						szAAABB[] = "AAABB";
	char						szAABAA[] = "AABAA";
	char						szAABBB[] = "AABBB";
	char						szAACAA[] = "AACAA";
	char						szAACBB[] = "AACBB";
	CIndexTreeFileAccess		cAccess;
	char						szDest[16];

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();

	cHelper.Init("Output" _FS_"IndexTreeG", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	TestIndexTreeFileEvictComplexSetup(&cDurableController, &cIndexTree, &cAllocator);
	AssertLongLongInt(3801, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cIndexTree.Evict(szAABAA));
	AssertTrue(cIndexTree.Evict(szAAAAA));
	AssertTrue(cIndexTree.Evict(szAACBB));

	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertInt(12, cIndexTree.NumMemoryNodes());

	cAccess.Init(&cIndexTree);
	AssertNotNull(cAccess.GetStringString(szAAAAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAAABB, szDest));
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNull(cAccess.GetStringString(szAACBB, szDest));

	cAccess.Flush();
	cDurableController.End();
	cIndexTree.Kill();
	cDurableController.Kill();
	cAllocator.Kill();
	cAccess.Kill();

	cAllocator.Init();
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cAllocator, IWT_No);
	cAccess.Init(&cIndexTree);
	AssertNotNull(cAccess.GetStringString(szAAAAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAAABB, szDest));
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNull(cAccess.GetStringString(szAACBB, szDest));
	cDurableController.End();
	cIndexTree.Kill();
	cDurableController.Kill();
	cAllocator.Kill();
	cAccess.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileFlushNodes(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cDurableController;
	CGeneralMemory*				pcMemory;
	CIndexTreeFile				cIndexTree;
	CMemoryAllocator			cAllocator;
	char						szAAAAA[] = "AAAAA";
	char						szAAABB[] = "AAABB";
	char						szAABAA[] = "AABAA";
	char						szAABBB[] = "AABBB";
	char						szAACAA[] = "AACAA";
	char						szAACBB[] = "AACBB";
	CIndexTreeFileAccess		cAccess;
	char						szDest[16];

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();

	cHelper.Init("Output" _FS_"IndexTreeH", "primary", "backup", TRUE);
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	TestIndexTreeFileEvictComplexSetup(&cDurableController, &cIndexTree, &cAllocator);
	AssertLongLongInt(3801, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cIndexTree.Flush(szAAAAA));
	AssertTrue(cIndexTree.Flush(szAAABB));
	AssertTrue(cIndexTree.Flush(szAABAA));
	AssertTrue(cIndexTree.Flush(szAABBB));
	AssertTrue(cIndexTree.Flush(szAACAA));
	AssertTrue(cIndexTree.Flush(szAACBB));

	cDurableController.End();
	cIndexTree.Kill();
	cDurableController.Kill();
	cAllocator.Kill();

	cAllocator.Init();
	cDurableController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cDurableController.Begin();
	cIndexTree.Init(&cDurableController, &cAllocator, IWT_No);
	cAccess.Init(&cIndexTree);
	AssertNotNull(cAccess.GetStringString(szAAAAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAAABB, szDest));
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNull(cAccess.GetStringString(szAACBB, szDest));
	cDurableController.End();
	cIndexTree.Kill();
	cDurableController.Kill();
	cAllocator.Kill();
	cAccess.Kill();

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

	//TestIndexTreeFileSizeOfs();
	//TestIndexTreeFileInit();
	//TestIndexTreeFileAdd();
	TestIndexTreeFileAddLongKeys();
	TestIndexTreeFileGetNodeKey();
	TestIndexTreeFileMemorySize();
	TestIndexTreeFileAddToRoot();
	TestIndexTreeFileAddUnallocated();
	TestIndexTreeFileReplaceData();
	TestIndexTreeFileFindKey();
	TestIndexTreeFileResizeData();
	TestIndexTreeFileRemove(IWT_Yes);
	TestIndexTreeFileRemove(IWT_No);
	TestIndexTreeFileRemoveAndEvict();
	TestIndexTreeFileRemoveNearestFirst(IWT_Yes);
	TestIndexTreeFileRemoveNearestFirst(IWT_No);
	TestIndexTreeFileRemoveFurthestFirst(IWT_Yes);
	TestIndexTreeFileRemoveFurthestFirst(IWT_No);
	TestIndexTreeFileRemoveAndFlush();
	TestIndexTreeFileNoCacheEviction();
	TestIndexTreeFileDeleteInMemory();
	TestIndexTreeFileDirty();
	TestIndexTreeFileRemoveThenDirty();
	TestIndexTreeFileAddThenAdd();
	TestIndexTreeFileRead();
	TestIndexTreeFileDeleteOnDisk();
	TestIndexTreeFileComplex();
	TestIndexTreeFileEvictNew(IWT_Yes);
	TestIndexTreeFileEvictNew(IWT_No);
	TestIndexTreeFileEvictDirty(IWT_Yes);
	TestIndexTreeFileEvictDirty(IWT_No);
	TestIndexTreeFileEvictComplexEvictCloseGet();
	TestIndexTreeFileEvictComplexEvictGetClose();
	TestIndexTreeFileEvictComplexEvictOdd();
	TestIndexTreeFileEvictComplexEvictEven();
	TestIndexTreeFileFlushNodes();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

