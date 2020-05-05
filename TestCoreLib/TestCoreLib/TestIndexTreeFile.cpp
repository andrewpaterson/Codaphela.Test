#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/Logger.h"
#include "BaseLib/DebugOutput.h"
#include "BaseLib/GlobalMemory.h"
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
char* GetString(CIndexTreeFileAccess* pcAccess, char* szKey)
{
	char*	szResult;

	szResult = pcAccess->GetStringString(szKey, gszIndexTreeString);
	return szResult;
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertIndexFileEmpty(char* szFileName)
{
	CNaiveFile	cNaiveFile;
	int			i;
	char*		pcFileMem;

	cNaiveFile.Init();
	AssertTrue(cNaiveFile.Read(szFileName));
	pcFileMem = (char*)cNaiveFile.Get();
	for (i = 0; i < cNaiveFile.Size(); i++)
	{
		AssertChar(INDEX_FILE_EMPTY_CHAR, pcFileMem[i]);
	}
	cNaiveFile.Kill();
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
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cController;

	cHelper.Init("Output" _FS_"QuakeMinusOne", "primary", "backup", TRUE);

	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL);
	cController.End();

	cIndexTree.Kill();
	cController.Kill();

	cHelper.RemoveWorkingDirectory();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAdd(EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		a;
	CTestIndexTreeObject		aa;
	CTestIndexTreeObject		aaa;
	CTestIndexTreeObject		ab;
	CTestIndexTreeObject		aab;
	BOOL						bResult;
	CIndexTreeNodeFile* pcNode;
	CTestIndexTreeObject** ppvTest;
	SIndexTreeFileIterator		sIter;
	BOOL						bContinue;
	int							iSize;

	cHelper.Init("Output" _FS_"IndexTree0", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);

	a.Init("A");
	bResult = cAccess.PutStringPtr(a.GetName(), &a);
	AssertTrue(bResult);
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	pcNode = cIndexTree.GetNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetDataPtr();
	AssertPointer(&a, *ppvTest);

	aa.Init("AA");
	bResult = cAccess.PutStringPtr(aa.GetName(), &aa);
	AssertTrue(bResult);
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	aaa.Init("AAA");
	bResult = cAccess.PutStringPtr(aaa.GetName(), &aaa);
	AssertTrue(bResult);
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	ab.Init("AB");
	bResult = cAccess.PutStringPtr(ab.GetName(), &ab);
	AssertTrue(bResult);
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	aab.Init("AAB");
	bResult = cAccess.PutStringPtr(aab.GetName(), &aab);
	AssertTrue(bResult);
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());


	pcNode = cIndexTree.GetNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetDataPtr();
	AssertPointer(&a, *ppvTest);

	pcNode = cIndexTree.GetNode("AA", 2);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetDataPtr();
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

	if (eKeyReverse == IKR_No)
	{
		bContinue = cIndexTree.Iterate(&sIter, (void**)(&ppvTest), &iSize);
		AssertTrue(bContinue);
		AssertInt(sizeof(CTestIndexTreeObject*), iSize);
		AssertString("AAB", (*ppvTest)->mszName);

		bContinue = cIndexTree.Iterate(&sIter, (void**)(&ppvTest), &iSize);
		AssertTrue(bContinue);
		AssertInt(sizeof(CTestIndexTreeObject*), iSize);
		AssertString("AB", (*ppvTest)->mszName);
	}
	else if (eKeyReverse == IKR_Yes)
	{
		bContinue = cIndexTree.Iterate(&sIter, (void**)(&ppvTest), &iSize);
		AssertTrue(bContinue);
		AssertInt(sizeof(CTestIndexTreeObject*), iSize);
		AssertString("AB", (*ppvTest)->mszName);

		bContinue = cIndexTree.Iterate(&sIter, (void**)(&ppvTest), &iSize);
		AssertTrue(bContinue);
		AssertInt(sizeof(CTestIndexTreeObject*), iSize);
		AssertString("AAB", (*ppvTest)->mszName);
	}

	bContinue = cIndexTree.Iterate(&sIter, (void**)(&ppvTest), &iSize);
	AssertFalse(bContinue);

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileGetNodeKey(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		a;
	BOOL						bResult;
	CIndexTreeNodeFile*			pcNode;
	int							iSize;
	char						szKey[7];

	cHelper.Init("Output" _FS_"IndexTree0a", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL);
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

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAddLongKeys(EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		szAmicable;
	CTestIndexTreeObject		szAmigo;

	cHelper.Init("Output" _FS_"IndexTree0b", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);

	szAmicable.Init("Amicable");
	AssertTrue(cAccess.PutStringPtr(szAmicable.GetName(), NULL));

	szAmigo.Init("Amigo");
	AssertTrue(cAccess.PutStringPtr(szAmigo.GetName(), NULL));
	AssertTrue(cAccess.PutLongPtr(0x4142434430313233ll, NULL));

	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAddSimple(EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		ab;
	BOOL						bResult;
	CIndexTreeNodeFile*			pcNode;
	CTestIndexTreeObject**		ppvTest;

	cHelper.Init("Output" _FS_"IndexTree0c", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);

	ab.Init("AB");
	bResult = cAccess.PutStringPtr(ab.GetName(), &ab);
	AssertTrue(bResult);
	pcNode = cIndexTree.GetNode("AB", 2);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetDataPtr();
	AssertPointer(&ab, *ppvTest);
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());


	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

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
	CDurableFileController	cController;
	SIndexTreeFileIterator	sIter;
	BOOL					bContinue;
	char*					szData;
	int						iSize;
	SLogConfig				sLogConfig;

	cHelper.Init("Output" _FS_"IndexTree1", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, 255, MAX_KEY_SIZE);
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

	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cAccess.PutLongString(0xEE89DD67CC45BB23LL, "Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sente."));
	gcLogger.SetConfig(&sLogConfig);
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

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

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
	CDurableFileController	cController;
	CMemoryAllocator		cAllocator;
	CGeneralMemory*			pcMemory;

	cHelper.Init("Output" _FS_"IndexTree2", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();

	cController.Begin();
	cIndexTree.Init(&cController, NULL, &cAllocator, IWT_Yes, IKR_No);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringData("AA", szAAObject, (unsigned char)strlen(szAAObject) + 1);
	cAccess.PutStringData("AC", szACObject, (unsigned char)strlen(szACObject) + 1);

	pcNode = cIndexTree.GetNode("A", 1);
	pcOldNode = pcNode;
	AssertInt(3, pcNode->NumIndexes());
	AssertInt(2, pcNode->NumValidIndexes());
	AssertInt(0, pcNode->GetDataSize());
	iNodeMemoryOffset1 = (size_t)pcNode->GetNodesMemory() - (size_t)pcNode;
	AssertInt(cIndexTree.SizeofNode(), iNodeMemoryOffset1);

	cAccess.PutStringData("A", szAObject, (unsigned char)strlen(szAObject) + 1);

	pcNode = cIndexTree.GetNode("A", 1);
	AssertFalse(pcNode == pcOldNode);
	AssertInt(3, pcNode->NumIndexes());
	AssertInt(2, pcNode->NumValidIndexes());
	AssertInt(18, pcNode->GetDataSize());
	iNodeMemoryOffset2 = (size_t)pcNode->GetNodesMemory() - (size_t)pcNode;
	AssertInt(cIndexTree.SizeofNode() + pcNode->GetDataSize(), iNodeMemoryOffset2);
	AssertTrue(iNodeMemoryOffset2 > iNodeMemoryOffset1);

	AssertString(szAAObject, GetString(&cAccess, "AA"));
	AssertString(szACObject, GetString(&cAccess, "AC"));
	AssertString(szAObject, GetString(&cAccess, "A"));

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

	cController.End();

	cIndexTree.Kill();
	cController.Kill();

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
	char					szAAA[] = "NEAR";
	char					szA[] = "Florida";
	CIndexTreeFile			cIndexTree;
	CIndexTreeHelper		cHelper;
	CDurableFileController	cController;
	CIndexTreeFileAccess	cAccess;

	cHelper.Init("Output" _FS_"IndexTree3", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, eWriteThrough, IKR_No);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringData("AAA", szAAA, (unsigned char)strlen(szAAA) + 1);
	cAccess.PutStringData("A", szA, (unsigned char)strlen(szA) + 1);

	AssertInt(2, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cAccess.DeleteString("A"));
	AssertString(NULL, GetString(&cAccess, "A"));
	AssertString(szAAA, GetString(&cAccess, "AAA"));
	AssertInt(1, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cAccess.DeleteString("AAA"));
	AssertString(NULL, GetString(&cAccess, "A"));
	AssertString(NULL, GetString(&cAccess, "AAA"));
	AssertInt(0, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

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
	CDurableFileController	cController;
	CIndexTreeFileAccess	cAccess;

	cHelper.Init("Output" _FS_"IndexTree3a", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, eWriteThrough, IKR_No);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringData("AA", szAA, (unsigned char)strlen(szAA) + 1);
	cAccess.PutStringData("AAA", szAAA, (unsigned char)strlen(szAAA) + 1);
	cAccess.PutStringData("A", szA, (unsigned char)strlen(szA) + 1);
	AssertInt(3, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cAccess.DeleteString("AAA"));
	AssertString(szA, GetString(&cAccess, "A"));
	AssertString(szAA, GetString(&cAccess, "AA"));
	AssertString(NULL, GetString(&cAccess, "AAA"));
	AssertInt(2, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cAccess.DeleteString("AA"));
	AssertString(szA, GetString(&cAccess, "A"));
	AssertString(NULL, GetString(&cAccess, "AA"));
	AssertString(NULL, GetString(&cAccess, "AAA"));
	AssertInt(1, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertTrue(cAccess.DeleteString("A"));
	AssertString(NULL, GetString(&cAccess, "A"));
	AssertString(NULL, GetString(&cAccess, "AA"));
	AssertString(NULL, GetString(&cAccess, "AAA"));
	AssertInt(0, cIndexTree.NumElements());
	AssertTrue(cAccess.Flush());
	AssertTrue(cIndexTree.ValidateIndexTree());

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

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
	CDurableFileController	cController;
	CIndexTreeFileAccess	cAccess;
	CArrayIndexedFilePtr	apc;
	CIndexedFile*			pcFile;
	CArrayBit				ab;

	cHelper.Init("Output" _FS_"IndexTree3b", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, eWriteThrough, IKR_No);
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


	AssertTrue(cAccess.DeleteString("AAAA"));
	AssertNull(GetString(&cAccess, "AAAA"));
	AssertInt(0, cIndexTree.NumElements());
	AssertFalse(cAccess.DeleteString("AAAA"));

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

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

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
	CDurableFileController	cController;
	CIndexTreeFileAccess	cAccess;
	CArrayIndexedFilePtr	apc;
	CIndexedFile*			pcFile;
	CArrayBit				ab;

	cHelper.Init("Output" _FS_"IndexTree3c", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);

	AssertTrue(cIndexTree.IsFlushed());
	cAccess.PutStringData("ABCD", szABCD, (unsigned char)strlen(szABCD) + 1);
	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertFalse(cIndexTree.IsFlushed());
	AssertTrue(cAccess.EvictString("ABCD"));
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


	AssertTrue(cAccess.DeleteString("ABCD"));
	AssertTrue(cAccess.EvictString("ABCD"));

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
	cController.End();
	cIndexTree.Kill();
	cController.Kill();
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
	CDurableFileController		cController;
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
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, &cAllocator, IWT_Yes, IKR_No);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutStringString(szAABAA, szAABAA));
	AssertTrue(cAccess.PutStringString(szAABBB, szAABBB));
	AssertTrue(cAccess.PutStringString(szAACAA, szAACAA));
	AssertTrue(cAccess.PutStringString(szAACBB, szAACBB));

	cController.End();
	cIndexTree.Kill();

	cController.Begin();
	cIndexTree.Init(&cController, NULL, &cAllocator, IWT_No, IKR_No);
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

	cController.End();

	cIndexTree.Kill();
	cController.Kill();
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
	CDurableFileController	cController;
	CIndexTreeFileAccess	cAccess;
	
	cHelper.Init("Output" _FS_"IndexTree4", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_Yes, IKR_No);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringData("AA", szAA, (unsigned char)strlen(szAA) + 1);
	cAccess.PutStringData("AAA", szAAA, (unsigned char)strlen(szAAA) + 1);
	cAccess.PutStringData("A", szA, (unsigned char)strlen(szA) + 1);
	AssertInt(3, cIndexTree.NumElements());

	cIndexTree.SetWriteThrough(IWT_No);

	cAccess.DeleteString("AA");
	AssertString(szA, GetString(&cAccess, "A"));
	AssertString(NULL, GetString(&cAccess, "AA"));
	AssertString(szAAA, GetString(&cAccess, "AAA"));
	AssertInt(2, cIndexTree.NumElements());
	AssertInt(4, cIndexTree.NumNodes());

	cIndexTree.Flush();
	AssertInt(4, cIndexTree.NumNodes());
	cIndexTree.ValidateIndexTree();

	cAccess.DeleteString("A");
	AssertString(NULL, GetString(&cAccess, "A"));
	AssertString(NULL, GetString(&cAccess, "AA"));
	AssertString(szAAA, GetString(&cAccess, "AAA"));
	AssertInt(1, cIndexTree.NumElements());
	AssertInt(4, cIndexTree.NumNodes());

	cAccess.DeleteString("AAA");
	AssertString(NULL, GetString(&cAccess, "A"));
	AssertString(NULL, GetString(&cAccess, "AA"));
	AssertString(NULL, GetString(&cAccess, "AAA"));
	AssertInt(0, cIndexTree.NumElements());
	AssertInt(4, cIndexTree.NumNodes());

	cIndexTree.Flush();
	AssertInt(1, cIndexTree.NumNodes());  //Just the root node left.
	cIndexTree.ValidateIndexTree();

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

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
	CDurableFileController	cController;
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
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL);
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

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

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
	CDurableFileController	cController;
	CIndexTreeFileAccess	cAccess;

	cHelper.Init("Output" _FS_"IndexTree6", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringData("Foot", szFoot, (unsigned char)strlen(szFoot) + 1);
	cIndexTree.Flush();
	AssertInt(5, cIndexTree.NumNodes());
	cIndexTree.ValidateIndexTree();
	cController.End();

	cController.Begin();
	cAccess.PutStringData("Fork", szFork, (unsigned char)strlen(szFork) + 1);
	cAccess.PutStringData("Gemstone", szGemstone, (unsigned char)strlen(szGemstone) + 1);
	cIndexTree.Flush();
	AssertInt(15, cIndexTree.NumNodes());
	cIndexTree.ValidateIndexTree();

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileReplaceData(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	BOOL						bResult;
	char						acData[5];
	char						acResult[5];
	int							iDataSize;

	cHelper.Init("Output" _FS_"IndexTree7", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL);
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

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAddUnallocated(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		a;
	CTestIndexTreeObject		b;
	CTestIndexTreeObject		c;
	BOOL						bResult;

	cHelper.Init("Output" _FS_"IndexTree8", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL);
	cAccess.Init(&cIndexTree);

	a.Init("1A");
	c.Init("1C");
	b.Init("1B");

	bResult = cAccess.PutStringPtr(a.GetName(), &a);
	AssertTrue(bResult);
	AssertPointer(&a, *((CTestIndexTreeObject**)cIndexTree.GetNode(a.GetName(), 2)->GetDataPtr()));

	bResult = cAccess.PutStringPtr(c.GetName(), &c);
	AssertTrue(bResult);
	AssertPointer(&a, *((CTestIndexTreeObject**)cIndexTree.GetNode(a.GetName(), 2)->GetDataPtr()));
	AssertPointer(&c, *((CTestIndexTreeObject**)cIndexTree.GetNode(c.GetName(), 2)->GetDataPtr()));

	bResult = cAccess.PutStringPtr(b.GetName(), &b);
	AssertTrue(bResult);
	AssertPointer(&a, *((CTestIndexTreeObject**)cIndexTree.GetNode(a.GetName(), 2)->GetDataPtr()));
	AssertPointer(&b, *((CTestIndexTreeObject**)cIndexTree.GetNode(b.GetName(), 2)->GetDataPtr()));
	AssertPointer(&c, *((CTestIndexTreeObject**)cIndexTree.GetNode(c.GetName(), 2)->GetDataPtr()));

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileRemoveThenDirty(void)
{
	CIndexTreeFile				cIndexTree;
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		a;
	CTestIndexTreeObject		b;
	CTestIndexTreeObject		c;
	char						sz[MAX_DATA_SIZE];
	CIndexTreeNodeFile*			pcNode;

	cHelper.Init("Output" _FS_"IndexTree9", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);
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
	pcNode = cIndexTree.GetNode(a.GetName(), a.NameLength());
	AssertNotNull(pcNode);
	AssertFalse(pcNode->IsDeleted());
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

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileAddThenAdd(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		a;
	CTestIndexTreeObject		b;
	char						sz[MAX_DATA_SIZE];

	cHelper.Init("Output" _FS_"IndexTree9a", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);

	a.Init("AA");
	b.Init("AAAA");

	AssertTrue(cAccess.PutStringString(a.GetName(), a.GetName()));

	cIndexTree.Flush();
	cController.End();
	cIndexTree.Kill();


	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutStringString(b.GetName(), b.GetName()));

	cIndexTree.Flush();
	cController.End();
	cIndexTree.Kill();


	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);

	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString(a.GetName(), sz);
	AssertNotNull(cAccess.GetStringString(b.GetName(), sz));
	AssertString(b.GetName(), sz);

	cIndexTree.Flush();
	cController.End();
	cIndexTree.Kill();

	cAccess.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertContainsFiles(CArrayChars* pacFiles, char* szFirstFile, ...)
{
	va_list			vaMarker;
	char*			szFile;
	CArrayChars		asz;
	int				i;

	szFile = szFirstFile;
	asz.Init();

	va_start(vaMarker, szFirstFile);
	while (szFile != NULL)
	{
		asz.Add(szFile);
		szFile = va_arg(vaMarker, char*);
	}
	va_end(vaMarker);

	AssertInt(pacFiles->NumElements(), asz.NumElements());
	for (i = 0; i < asz.NumElements(); i++)
	{
		szFile = asz.GetText(i);
		if (!pacFiles->ContainsSubString(szFile))
		{
			AssertString(szFile, "");
		}
	}
	
	asz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileRemoveBeforeFlush(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		a;
	char						sz[MAX_DATA_SIZE];
	char*						szDirectory;
	CFileUtil					cFileUtil;
	CArrayChars					acFiles;
	CIndexTreeNodeFile*			pcNode;

	cHelper.Init("Output" _FS_"IndexTree9b", "primary", "backup", TRUE);
	szDirectory = cHelper.GetPrimaryDirectory();
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cAccess.Init(&cIndexTree);

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);

	a.Init("A");

	AssertTrue(cAccess.PutStringString(a.GetName(), "Onomatopoeia"));
	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString("Onomatopoeia", sz);

	AssertTrue(cAccess.DeleteString(a.GetName()));
	AssertNull(cAccess.GetStringString(a.GetName(), sz));

	cAccess.Flush();

	cController.End();

	acFiles.Init();
	cFileUtil.FindFilesWithExtension(szDirectory, "IDAT", &acFiles);
	AssertContainsFiles(&acFiles, "2062", NULL);
	acFiles.Kill();


	cController.Begin();

	AssertTrue(cAccess.PutStringString(a.GetName(), "Zootopic"));
	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString("Zootopic", sz);

	AssertTrue(cAccess.PutStringString(a.GetName(), "Franschhoek"));
	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString("Franschhoek", sz);

	AssertTrue(cAccess.DeleteString(a.GetName()));
	AssertNull(cAccess.GetStringString(a.GetName(), sz));

	cAccess.Flush();

	cController.End();

	acFiles.Init();
	cFileUtil.FindFilesWithExtension(szDirectory, "IDAT", &acFiles);
	AssertContainsFiles(&acFiles, "2062", NULL);
	acFiles.Kill();


	cController.Begin();

	AssertTrue(cAccess.PutStringString(a.GetName(), "Blobfish"));
	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString("Blobfish", sz);

	cAccess.Flush();
	cController.End();

	acFiles.Init();
	cFileUtil.FindFilesWithExtension(szDirectory, "IDAT", &acFiles);
	AssertContainsFiles(&acFiles, "2062", "23", NULL);
	acFiles.Kill();

	cController.Begin();

	AssertTrue(cAccess.DeleteString(a.GetName()));
	AssertNull(cAccess.GetStringString(a.GetName(), sz));

	cAccess.Flush();
	cController.End();
	
	acFiles.Init();
	cFileUtil.FindFilesWithExtension(szDirectory, "IDAT", &acFiles);
	AssertContainsFiles(&acFiles, "2062", "23", NULL);
	acFiles.Kill();


	cController.Begin();

	AssertTrue(cAccess.PutStringString(a.GetName(), "Blobfish"));
	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString("Blobfish", sz);

	cAccess.Flush();
	cController.End();

	acFiles.Init();
	cFileUtil.FindFilesWithExtension(szDirectory, "IDAT", &acFiles);
	AssertContainsFiles(&acFiles, "2062", "23", NULL);
	acFiles.Kill();

	cController.Begin();

	AssertTrue(cAccess.PutStringString(a.GetName(), "Avagadrocardo"));
	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString("Avagadrocardo", sz);

	AssertTrue(cAccess.DeleteString(a.GetName()));
	AssertNull(cAccess.GetStringString(a.GetName(), sz));

	cAccess.Flush();
	cController.End();

	acFiles.Init();
	cFileUtil.FindFilesWithExtension(szDirectory, "IDAT", &acFiles);
	AssertContainsFiles(&acFiles, "2062", "23", NULL);
	acFiles.Kill();


	cController.Begin();

	AssertTrue(cAccess.PutStringString(a.GetName(), "Escape"));
	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString("Escape", sz);

	cAccess.Flush();
	cController.End();

	acFiles.Init();
	cFileUtil.FindFilesWithExtension(szDirectory, "IDAT", &acFiles);
	AssertContainsFiles(&acFiles, "2062", "23", "21", NULL);
	acFiles.Kill();

	cController.Begin();

	AssertTrue(cAccess.DeleteString(a.GetName()));
	pcNode = cIndexTree.GetNode(a.GetName(), a.NameLength());
	AssertTrue(pcNode->IsDeleted());
	AssertTrue(pcNode->IsPathDeleted());
	AssertFalse(pcNode->IsDirty());
	AssertFalse(pcNode->IsPathDirty());
	AssertNull(cAccess.GetStringString(a.GetName(), sz));

	AssertTrue(cAccess.PutStringString(a.GetName(), "Pentatonix"));
	pcNode = cIndexTree.GetNode(a.GetName(), a.NameLength());
	AssertFalse(pcNode->IsDeleted());
	AssertFalse(pcNode->IsPathDeleted());
	AssertTrue(pcNode->IsDirty());
	AssertTrue(pcNode->IsPathDirty());
	AssertNotNull(cAccess.GetStringString(a.GetName(), sz));
	AssertString("Pentatonix", sz);

	cAccess.Flush();
	cController.End();

	acFiles.Init();
	cFileUtil.FindFilesWithExtension(szDirectory, "IDAT", &acFiles);
	AssertContainsFiles(&acFiles, "2062", "23", "21", "25", NULL);
	acFiles.Kill();

	cIndexTree.Kill();
	cController.Kill();
	cAccess.Kill();

	AssertIndexFileEmpty("Output/IndexTree9b/primary/23_0.IDAT");
	AssertIndexFileEmpty("Output/IndexTree9b/primary/21_0.IDAT");

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileRead(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	char						sz[MAX_DATA_SIZE];
	CIndexTreeNodeFile*			pcHell;
	int							iOldFile;
	int							iNewFile;
	CIndexedFile*				pcFile;

	cHelper.Init("Output" _FS_"IndexTreeA", "primary", "backup", TRUE);
	cHelper.RemoveWorkingDirectory();

	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringString("Hello", "World");

	cAccess.Flush();
	cController.End();
	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	AssertTrue(cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory()));
	AssertTrue(cController.Begin());
	AssertTrue(cIndexTree.Init(&cController, NULL, IWT_No, IKR_No));
	AssertTrue(cAccess.Init(&cIndexTree));

	AssertNotNull(cAccess.GetStringString("Hello", sz));
	AssertString("World", sz)

	AssertTrue(cAccess.Flush());
	pcHell = cIndexTree.GetNode("Hell", 4);
	iOldFile = pcHell->GetFileIndex()->miFile;
	pcFile = cIndexTree.GetFile(iOldFile);
	AssertNotNull(pcFile);
	AssertInt(22, pcFile->GetDataSize());
	AssertTrue(cController.End());
	cIndexTree.Kill();
	cController.Kill();

	AssertTrue(cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory()));
	AssertTrue(cController.Begin());
	AssertTrue(cIndexTree.Init(&cController, NULL, IWT_Yes, IKR_No));
	AssertTrue(cController.End());

	AssertTrue(cController.Begin());
	AssertTrue(cAccess.PutStringString("Hell", "Fuzz"));
	pcHell = cIndexTree.GetNode("Hell", 4);
	iNewFile = pcHell->GetFileIndex()->miFile;
	AssertTrue(iOldFile != iNewFile);
	pcFile = cIndexTree.GetFile(iNewFile);
	AssertNotNull(pcFile);
	AssertInt(27, pcFile->GetDataSize());
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertTrue(cController.End());
	iOldFile = iNewFile;

	AssertTrue(cController.Begin());
	AssertNotNull(cAccess.GetStringString("Hell", sz));
	AssertString("Fuzz", sz);
	AssertNotNull(cAccess.GetStringString("Hello", sz));
	AssertString("World", sz);
	AssertTrue(cController.End());

	cIndexTree.Kill();

	AssertTrue(cController.Begin());
	AssertTrue(cIndexTree.Init(&cController, NULL, IWT_Yes, IKR_No));
	AssertNotNull(cAccess.GetStringString("Hell", sz));
	AssertString("Fuzz", sz);
	pcHell = cIndexTree.GetNode("Hell", 4);
	iNewFile = pcHell->GetFileIndex()->miFile;
	AssertTrue(iOldFile == iNewFile);
	AssertTrue(cController.End());
	cIndexTree.Kill();

	AssertTrue(cController.Begin());
	AssertTrue(cIndexTree.Init(&cController, NULL, IWT_Yes, IKR_No));
	AssertTrue(cController.End());

	AssertTrue(cController.Begin());
	AssertTrue(cAccess.PutStringString("HelloX", "3"));
	AssertTrue(cController.End());

	AssertTrue(cController.Begin());
	AssertNotNull(cAccess.GetStringString("Hell", sz));
	AssertString("Fuzz", sz);
	AssertNotNull(cAccess.GetStringString("HelloX", sz));
	AssertString("3", sz);
	AssertNotNull(cAccess.GetStringString("Hello", sz));
	AssertString("World", sz);
	AssertTrue(cController.End());
	cIndexTree.Kill();

	AssertTrue(cAccess.Kill());
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileDeleteOnDisk(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	char						sz[MAX_DATA_SIZE];
	CIndexTreeNodeFile*			pcNode;

	cHelper.Init("Output" _FS_"IndexTreeB", "primary", "backup", TRUE);
	cHelper.RemoveWorkingDirectory();

	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_Yes, IKR_No);
	cAccess.Init(&cIndexTree);
	cAccess.PutStringString("Hello", "World");
	cController.End();
	cIndexTree.Kill();

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_Yes, IKR_No);
	cAccess.DeleteString("Hello");
	cController.End();
	cIndexTree.Kill();

	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_Yes, IKR_No);
	AssertNull(cAccess.GetStringString("Hello", sz));
	pcNode = cIndexTree.GetNode("H", 1);
	cController.End();
	cIndexTree.Kill();

	AssertIndexFileEmpty("Output/IndexTreeB/primary/20_0.IDAT");
	AssertIndexFileEmpty("Output/IndexTreeB/primary/22_0.IDAT");

	cAccess.Kill();
	cController.Kill();
	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileComplex(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
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
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_Yes, IKR_No);
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

	cController.End();
	cIndexTree.Kill();
	cAccess.Kill();
	cController.Kill();

	//////////////////////////////////////////////////////////////////////////////////////
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cController.Begin();
	cIndexTree.Init(&cController, NULL, IWT_Yes, IKR_No);
	cAccess.Init(&cIndexTree);

	bHasNext = cMap.StartIteration(&sIter, (void**)&szKey, (void**)&szValue);
	while (bHasNext)
	{
		AssertNotNull(cAccess.GetStringString(szKey, sz));
		szValue = cMap.Get(szKey);
		AssertString(szValue, sz);
		
		bHasNext = cMap.Iterate(&sIter, (void**)&szKey, (void**)&szValue);
	}

	cController.End();
	cIndexTree.Kill();
	cAccess.Kill();
	cController.Kill();

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
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		a;
	CTestIndexTreeObject		b;
	BOOL						bResult;

	//This is supposed to be checking that the nodes indexed in file are in sync with the nodes pointed to in memory.
	cHelper.Init("Output" _FS_"IndexTreeD", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL);
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

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileMemorySize(void)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CTestIndexTreeObject		aaa;
	CTestIndexTreeObject		aab;
	BOOL						bResult;

	cHelper.Init("Output" _FS_"IndexTreeE", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL);
	cAccess.Init(&cIndexTree);

	AssertInt(1, cIndexTree.NumMemoryNodes());
	AssertInt(3096, cIndexTree.ByteSize());
	AssertInt(3096, cIndexTree.GetUserMemorySize());
	AssertInt(3096 + 4, cIndexTree.GetSystemMemorySize());

	aaa.Init("AAA");
	bResult = cAccess.PutStringPtr(aaa.GetName(), &aaa);
	AssertTrue(bResult);

	AssertInt(4, cIndexTree.NumMemoryNodes());
	AssertInt(3196, cIndexTree.ByteSize());
	AssertInt(3196, cIndexTree.GetUserMemorySize());
	AssertInt(3196 + 16, cIndexTree.GetSystemMemorySize());

	aab.Init("AAB");
	bResult = cAccess.PutStringPtr(aab.GetName(), &aab);
	AssertTrue(bResult);

	AssertInt(5, cIndexTree.NumMemoryNodes());
	AssertInt(3236, cIndexTree.ByteSize());
	AssertInt(3236, cIndexTree.GetUserMemorySize());
	AssertInt(3236 + 20, cIndexTree.GetSystemMemorySize());

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileEvictNew(EIndexWriteThrough eWriteThrough)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
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
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, &cAllocator, eWriteThrough, IKR_No);
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

	AssertTrue(cAccess.EvictString("AAAAA"));
	AssertLongLongInt(3258, pcMemory->GetTotalAllocatedMemory());
	AssertInt(3, cIndexTree.NumMemoryElements());
	AssertInt(5, cIndexTree.NumMemoryNodes());

	AssertTrue(cAccess.EvictString("AAAB"));
	AssertLongLongInt(3227, pcMemory->GetTotalAllocatedMemory());
	AssertInt(2, cIndexTree.NumMemoryElements());
	AssertInt(4, cIndexTree.NumMemoryNodes());
	AssertTrue(cAccess.EvictString("AAA"));
	AssertLongLongInt(3137, pcMemory->GetTotalAllocatedMemory());
	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertInt(2, cIndexTree.NumMemoryNodes());
	AssertTrue(cAccess.EvictString("A"));
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

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();
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
	CDurableFileController		cController;
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
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, &cAllocator, eWriteThrough, IKR_No);
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

	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cAccess.EvictString("AAA"));
	gcLogger.SetConfig(&sLogConfig);
	AssertInt(4, cIndexTree.NumMemoryElements());
	AssertTrue(cAccess.EvictString("AAAAA"));
	AssertInt(3, cIndexTree.NumMemoryElements());
	AssertTrue(cAccess.EvictString("AAAB"));
	AssertInt(2, cIndexTree.NumMemoryElements());
	AssertTrue(cAccess.EvictString("AAA"));
	AssertTrue(cIndexTree.ValidateIndexTree(FALSE));
	AssertInt(1, cIndexTree.NumMemoryElements());
	AssertTrue(cAccess.EvictString("A"));
	AssertInt(0, cIndexTree.NumMemoryElements());
	AssertTrue(cIndexTree.ValidateIndexTree(FALSE));

	cController.End();

	cAccess.Kill();
	cIndexTree.Kill();
	cController.Kill();
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
	pcIndexTree->Init(pcDurableController, NULL, pcAllocator, eWriteThrough, IKR_No);
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
	pcIndexTree->Init(pcDurableController, NULL, pcAllocator, eWriteThrough, IKR_No);
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
	CDurableFileController		cController;
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
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	TestIndexTreeFileEvictComplexSetup(&cController, &cIndexTree, &cAllocator);
	cAccess.Init(&cIndexTree);
	AssertLongLongInt(3801, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cAccess.EvictString(szAABBB));
	AssertTrue(cAccess.EvictString(szAAAAA));
	AssertTrue(cAccess.EvictString(szAAABB));
	AssertTrue(cAccess.EvictString(szAABAA));
	AssertTrue(cAccess.EvictString(szAACAA));
	AssertTrue(cAccess.EvictString(szAACBB));
	AssertLongLongInt(3204, pcMemory->GetTotalAllocatedMemory());

	AssertInt(0, cIndexTree.NumMemoryElements());
	AssertInt(3, cIndexTree.NumMemoryNodes());
	AssertInt(3, cIndexTree.NumElements());
	AssertInt(11, cIndexTree.NumNodes());
	
	//Also test to make sure that the CIndexedFiles in the tree reflect the correct number of allocated and deleted nodes.

	cController.End();
	cIndexTree.Kill();
	cController.Kill();
	cAllocator.Kill();
	cAccess.Kill();

	cAllocator.Init();
	pcMemory = cAllocator.GetMemory();
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cController.Begin();
	cIndexTree.Init(&cController, NULL, &cAllocator, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);
	AssertNotNull(cAccess.GetStringString(szAAAAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAAABB, szDest));
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNull(cAccess.GetStringString(szAACBB, szDest));
	AssertTrue(cIndexTree.ValidateIndexTree());
	cController.End();
	cIndexTree.Kill();

	cController.Kill();
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
	CDurableFileController		cController;
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
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	TestIndexTreeFileEvictComplexSetup(&cController, &cIndexTree, &cAllocator);
	cAccess.Init(&cIndexTree);
	AssertLongLongInt(3801, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cAccess.EvictString(szAABBB));
	AssertTrue(cAccess.EvictString(szAAAAA));
	AssertTrue(cAccess.EvictString(szAAABB));
	AssertTrue(cAccess.EvictString(szAABAA));
	AssertTrue(cAccess.EvictString(szAACAA));
	AssertTrue(cAccess.EvictString(szAACBB));

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

	cController.End();
	cIndexTree.Kill();
	cController.Kill();
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
	CDurableFileController		cController;
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
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	TestIndexTreeFileEvictComplexSetup(&cController, &cIndexTree, &cAllocator);
	cAccess.Init(&cIndexTree);
	AssertLongLongInt(3801, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cAccess.EvictString(szAABBB));
	AssertTrue(cAccess.EvictString(szAAABB));
	AssertTrue(cAccess.EvictString(szAACAA));

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
	cController.End();
	cIndexTree.Kill();
	cController.Kill();
	cAllocator.Kill();
	cAccess.Kill();

	cAllocator.Init();
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cController.Begin();
	cIndexTree.Init(&cController, NULL, &cAllocator, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);
	AssertNotNull(cAccess.GetStringString(szAAAAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAAABB, szDest));
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNull(cAccess.GetStringString(szAACBB, szDest));
	cController.End();
	cIndexTree.Kill();
	cController.Kill();
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
	CDurableFileController		cController;
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
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	TestIndexTreeFileEvictComplexSetup(&cController, &cIndexTree, &cAllocator);
	cAccess.Init(&cIndexTree);
	AssertLongLongInt(3801, pcMemory->GetTotalAllocatedMemory());

	AssertTrue(cAccess.EvictString(szAABAA));
	AssertTrue(cAccess.EvictString(szAAAAA));
	AssertTrue(cAccess.EvictString(szAACBB));

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
	cController.End();
	cIndexTree.Kill();
	cController.Kill();
	cAllocator.Kill();
	cAccess.Kill();

	cAllocator.Init();
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cController.Begin();
	cIndexTree.Init(&cController, NULL, &cAllocator, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);
	AssertNotNull(cAccess.GetStringString(szAAAAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAAABB, szDest));
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNull(cAccess.GetStringString(szAACBB, szDest));
	cController.End();
	cIndexTree.Kill();
	cController.Kill();
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
	CDurableFileController		cController;
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
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	TestIndexTreeFileEvictComplexSetup(&cController, &cIndexTree, &cAllocator);
	cAccess.Init(&cIndexTree);
	AssertLongLongInt(3801, pcMemory->GetTotalAllocatedMemory());

	cAccess.Init(&cIndexTree);
	AssertTrue(cAccess.FlushString(szAAAAA));
	AssertTrue(cAccess.FlushString(szAAABB));
	AssertTrue(cAccess.FlushString(szAABAA));
	AssertTrue(cAccess.FlushString(szAABBB));
	AssertTrue(cAccess.FlushString(szAACAA));
	AssertTrue(cAccess.FlushString(szAACBB));

	cController.End();
	cIndexTree.Kill();
	cController.Kill();
	cAllocator.Kill();
	cAccess.Kill();

	cAllocator.Init();
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());
	cController.Begin();
	cIndexTree.Init(&cController, NULL, &cAllocator, IWT_No, IKR_No);
	cAccess.Init(&cIndexTree);
	AssertNotNull(cAccess.GetStringString(szAAAAA, szDest));
	AssertNotNull(cAccess.GetStringString(szAAABB, szDest));
	AssertNotNull(cAccess.GetStringString(szAABAA, szDest));
	AssertNull(cAccess.GetStringString(szAABBB, szDest));
	AssertNull(cAccess.GetStringString(szAACAA, szDest));
	AssertNull(cAccess.GetStringString(szAACBB, szDest));
	cController.End();
	cIndexTree.Kill();
	cController.Kill();
	cAllocator.Kill();
	cAccess.Kill();

	cHelper.Kill(TRUE);
}




//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeFileRemoveComplex(EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse)
{
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;
	CIndexTreeFile				cIndexTree;
	char						szData[256];
	int							uiSize;
	char						szSmellsLikeTeenSpirit[] = { "Smells Like Teen Spirit" };
	char						szSeizedPotPlants[] = { "Seized pot plants turn out to be daisies" };
	char						szCallingFromWindows[] = { "I am calling you from Windows" };
	char						szDirectory[] = "Output" _FS_ "Database8";
	CIndexTreeFileAccess		cAccess;


	cHelper.Init("Output" _FS_"IndexTreeI", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cIndexTree.Init(&cController, NULL, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);
	cController.End();

	cController.Begin();
	cAccess.PutLongString(0x7634, szSmellsLikeTeenSpirit);
	cAccess.PutLongString(0x3589, szSeizedPotPlants);
	cAccess.PutLongString(0x8743, szCallingFromWindows);
	AssertLongLongInt(3, cIndexTree.NumElements());
	AssertTrue(cAccess.HasLong(0x7634));
	AssertTrue(cAccess.HasLong(0x3589));
	AssertTrue(cAccess.HasLong(0x8743));

	AssertTrue(cAccess.Flush());
	cController.End();
	cIndexTree.Kill();
	cAccess.Kill();


	cController.Begin();
	cIndexTree.Init(&cController, NULL, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);
	cController.End();

	cController.Begin();
	AssertTrue(cAccess.HasLong(0x7634));
	AssertTrue(cAccess.HasLong(0x3589));
	AssertTrue(cAccess.HasLong(0x8743));
	cController.End();
	cIndexTree.Kill();
	cAccess.Kill();


	cController.Begin();
	cIndexTree.Init(&cController, NULL, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);
	cController.End();

	cController.Begin();
	AssertTrue(cAccess.DeleteLong(0x7634));
	AssertLongLongInt(2, cIndexTree.NumElements());
	AssertFalse(cAccess.HasLong(0x7634));
	AssertTrue(cAccess.HasLong(0x3589));
	AssertTrue(cAccess.HasLong(0x8743));
	AssertFalse(cAccess.GetLongData(0x7634, szData, &uiSize));

	AssertTrue(cAccess.Flush());
	cController.End();
	cIndexTree.Kill();
	cAccess.Kill();


	cController.Begin();
	cIndexTree.Init(&cController, NULL, eWriteThrough, eKeyReverse);
	cAccess.Init(&cIndexTree);
	cController.End();

	cController.Begin();
	AssertTrue(cAccess.DeleteLong(0x3589));
	AssertTrue(cAccess.DeleteLong(0x8743));
	AssertFalse(cAccess.HasLong(0x7634));
	AssertFalse(cAccess.HasLong(0x3589));
	AssertFalse(cAccess.HasLong(0x8743));
	AssertLongLongInt(0, cIndexTree.NumElements());
	AssertFalse(cAccess.DeleteLong(0x7634));
	AssertFalse(cAccess.DeleteLong(0x3589));
	AssertFalse(cAccess.DeleteLong(0x8743));

	AssertTrue(cAccess.Flush());
	AssertFalse(cAccess.DeleteLong(0x7634));
	AssertFalse(cAccess.DeleteLong(0x3589));
	AssertFalse(cAccess.DeleteLong(0x8743));

	cController.End();
	cIndexTree.Kill();
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
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestIndexTreeFileSizeOfs();
	TestIndexTreeFileInit();
	TestIndexTreeFileAddSimple(IWT_No, IKR_No);
	TestIndexTreeFileAddSimple(IWT_No, IKR_Yes);
	TestIndexTreeFileAddSimple(IWT_Yes, IKR_Yes);
	TestIndexTreeFileAddSimple(IWT_Yes, IKR_No);
	TestIndexTreeFileAdd(IWT_No, IKR_No);
	TestIndexTreeFileAdd(IWT_No, IKR_Yes);
	TestIndexTreeFileAdd(IWT_Yes, IKR_Yes);
	TestIndexTreeFileAdd(IWT_Yes, IKR_No);
	TestIndexTreeFileAddLongKeys(IWT_No, IKR_Yes);
	TestIndexTreeFileAddLongKeys(IWT_Yes, IKR_Yes);
	TestIndexTreeFileAddLongKeys(IWT_No, IKR_No);
	TestIndexTreeFileAddLongKeys(IWT_Yes, IKR_No);
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
	TestIndexTreeFileRemoveBeforeFlush();
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
	TestIndexTreeFileRemoveComplex(IWT_No, IKR_No);
	TestIndexTreeFileRemoveComplex(IWT_Yes, IKR_No);

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

