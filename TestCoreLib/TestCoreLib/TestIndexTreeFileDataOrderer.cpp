#include "BaseLib/AccessDataOrderer.h"
#include "BaseLib/ModificationDataOrderer.h"
#include "BaseLib/CreationDataOrderer.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/IndexTreeHelper.h"
#include "CoreLib/IndexTreeFile.h"
#include "CoreLib/IndexTreeFileAccess.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void PrintOrdererString(CIndexTreeDataOrderer* pcOrderer, CChars* psz)
{
	SDataOrderIterator	sIter;
	char*				pc;
	int					iSize;
	BOOL				bExists;

	bExists = pcOrderer->StartIteration(&sIter, (void**)&pc, &iSize);
	while (bExists)
	{
		psz->Append(*pc);
		bExists = pcOrderer->Iterate(&sIter, (void**)&pc, &iSize);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void DumpDataOrdererString(CIndexTreeDataOrderer* pcOrderer)
{
	CChars	sz;

	sz.Init();
	PrintOrdererString(pcOrderer, &sz);
	sz.AppendNewLine();
	sz.Dump();
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertIndexTreeDataOrdererString(CIndexTreeDataOrderer* pcOrderer, char* szExpected)
{
	CChars	sz;

	sz.Init();
	PrintOrdererString(pcOrderer, &sz);
	AssertString(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeDataOrdererAccess(EIndexWriteThrough eWriteThrough)
{
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CAccessDataOrderer			cOrderer;
	char						c;
	SIndexTreeFileIterator		sIter;
	BOOL						bExists;
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;

	cHelper.Init("Output" _FS_"IndexTreeDataOrderer1", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cOrderer.Init();
	cIndexTree.Init(&cController, "Index", eWriteThrough, IKR_No, &cOrderer);
	cAccess.Init(&cIndexTree);

	AssertIndexTreeDataOrdererString(&cOrderer, "");

	cAccess.PutStringChar("0000", 'a');
	cAccess.PutStringChar("0100", 'b');
	cAccess.PutStringChar("0010", 'c');
	cAccess.PutStringChar("0110", 'd');
	AssertIndexTreeDataOrdererString(&cOrderer, "dcba");

	c = cAccess.GetStringChar("0000");
	AssertIndexTreeDataOrdererString(&cOrderer, "adcb");

	c = cAccess.GetStringChar("0010");
	AssertIndexTreeDataOrdererString(&cOrderer, "cadb");

	cAccess.DeleteString("0100");
	cAccess.DeleteString("0110");
	AssertIndexTreeDataOrdererString(&cOrderer, "ca");

	cAccess.DeleteString("0010");
	cAccess.DeleteString("0000");
	AssertIndexTreeDataOrdererString(&cOrderer, "");

	cAccess.PutStringChar("0000", 'a');
	cAccess.PutStringChar("0100", 'b');
	cAccess.PutStringChar("0010", 'c');
	cAccess.PutStringChar("0110", 'd');
	AssertIndexTreeDataOrdererString(&cOrderer, "dcba");

	cAccess.HasString("0100");
	AssertIndexTreeDataOrdererString(&cOrderer, "bdca");

	cAccess.HasString("0100");
	AssertIndexTreeDataOrdererString(&cOrderer, "bdca");

	cAccess.HasString("0110");
	AssertIndexTreeDataOrdererString(&cOrderer, "dbca");

	bExists = cIndexTree.StartIteration(&sIter, NULL, NULL);
	AssertTrue(bExists);
	AssertIndexTreeDataOrdererString(&cOrderer, "adbc");
	bExists = cIndexTree.Iterate(&sIter, NULL, NULL);
	AssertTrue(bExists);
	AssertIndexTreeDataOrdererString(&cOrderer, "cadb");
	bExists = cIndexTree.Iterate(&sIter, NULL, NULL);
	AssertTrue(bExists);
	AssertIndexTreeDataOrdererString(&cOrderer, "bcad");
	bExists = cIndexTree.Iterate(&sIter, NULL, NULL);
	AssertTrue(bExists);
	AssertIndexTreeDataOrdererString(&cOrderer, "dbca");
	bExists = cIndexTree.Iterate(&sIter, NULL, NULL);
	AssertFalse(bExists);

	cAccess.Flush();
	cController.End();

	cIndexTree.Kill();
	cAccess.Kill();
	cOrderer.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeDataOrdererRemapListNodes(EIndexWriteThrough eWriteThrough)
{
	CIndexTreeFile			cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CAccessDataOrderer			cOrderer;
	int							i;
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;

	cHelper.Init("Output" _FS_"IndexTreeDataOrderer2", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cOrderer.Init();
	cIndexTree.Init(&cController, "Index", eWriteThrough, IKR_No, &cOrderer);
	cAccess.Init(&cIndexTree);

	AssertIndexTreeDataOrdererString(&cOrderer, "");

	for (i = 60; i >= 0; i--)
	{
		cAccess.PutIntLong(i << 8, i);
	}
	for (i = 60; i >= 0; i--)
	{
		cAccess.PutIntChar(i << 8, 'A' + (char)i);
	}
	AssertIndexTreeDataOrdererString(&cOrderer, "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}");

	for (i = 0; i <= 60; i += 2)
	{
		AssertTrue(cAccess.HasInt(i << 8));
	}
	AssertIndexTreeDataOrdererString(&cOrderer, "}{ywusqomkigeca_][YWUSQOMKIGECABDFHJLNPRTVXZ\\^`bdfhjlnprtvxz|");

	for (i = 0; i <= 60; i++)
	{
		cAccess.PutIntLong(i << 8, i);
	}
	for (i = 0; i <= 60; i++)
	{
		cAccess.PutIntChar(i << 8, 'A' + (char)i);
	}
	AssertIndexTreeDataOrdererString(&cOrderer, "}|{zyxwvutsrqponmlkjihgfedcba`_^]\\[ZYXWVUTSRQPONMLKJIHGFEDCBA");

	for (i = 60; i >= 0; i -= 2)
	{
		AssertTrue(cAccess.HasInt(i << 8));
	}
	AssertIndexTreeDataOrdererString(&cOrderer, "ACEGIKMOQSUWY[]_acegikmoqsuwy{}|zxvtrpnljhfdb`^\\ZXVTRPNLJHFDB");

	cAccess.Flush();
	cController.End();

	cIndexTree.Kill();
	cAccess.Kill();
	cOrderer.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeDataOrdererModification(EIndexWriteThrough eWriteThrough)
{
	CIndexTreeFile				cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CModificationDataOrderer	cOrderer;
	int							i;
	int							iKey;
	char						c;
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;

	cHelper.Init("Output" _FS_"IndexTreeDataOrderer3", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cOrderer.Init();
	cIndexTree.Init(&cController, "Index", eWriteThrough, IKR_No, &cOrderer);
	cAccess.Init(&cIndexTree);


	AssertIndexTreeDataOrdererString(&cOrderer, "");

	for (i = 25; i >= 0; i--)
	{
		iKey = i * 0b1010101010101010101010101010;
		cAccess.PutIntChar(iKey, 'A' + (char)i);
	}
	AssertIndexTreeDataOrdererString(&cOrderer, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	for (i = 0; i <= 25; i++)
	{
		iKey = i * 0b1010101010101010101010101010;
		c = cAccess.GetIntChar(iKey);
		AssertInt('A' + i, c)
	}
	AssertIndexTreeDataOrdererString(&cOrderer, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	for (i = 0; i <= 13; i++)
	{
		iKey = i * 0b1010101010101010101010101010;
		cAccess.PutIntChar(iKey, 'a' + (char)i);
	}
	AssertIndexTreeDataOrdererString(&cOrderer, "nmlkjihgfedcbaOPQRSTUVWXYZ");

	for (i = 0; i <= 25; i += 2)
	{
		iKey = i * 0b1010101010101010101010101010;
		AssertTrue(cAccess.HasInt(iKey));
	}
	AssertIndexTreeDataOrdererString(&cOrderer, "nmlkjihgfedcbaOPQRSTUVWXYZ");

	for (i = 14; i <= 25; i++)
	{
		iKey = i * 0b1010101010101010101010101010;
		cAccess.PutIntChar(iKey, 'a' + (char)i);
	}
	AssertIndexTreeDataOrdererString(&cOrderer, "zyxwvutsrqponmlkjihgfedcba");

	cAccess.Flush();
	cController.End();

	cIndexTree.Kill();
	cAccess.Kill();
	cOrderer.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeDataOrdererCreation(EIndexWriteThrough eWriteThrough)
{
	CIndexTreeFile			cIndexTree;
	CIndexTreeFileAccess		cAccess;
	CCreationDataOrderer		cOrderer;
	CIndexTreeHelper			cHelper;
	CDurableFileController		cController;

	cHelper.Init("Output" _FS_"IndexTreeDataOrderer4", "primary", "backup", TRUE);
	cController.Init(cHelper.GetPrimaryDirectory(), cHelper.GetBackupDirectory());

	cController.Begin();
	cOrderer.Init();
	cIndexTree.Init(&cController, "Index", eWriteThrough, IKR_No, &cOrderer);
	cAccess.Init(&cIndexTree);


	AssertIndexTreeDataOrdererString(&cOrderer, "");

	cAccess.PutStringChar("0000", 'a');
	cAccess.PutStringChar("0100", 'b');
	cAccess.PutStringChar("0010", 'c');
	cAccess.PutStringChar("0110", 'd');
	AssertIndexTreeDataOrdererString(&cOrderer, "dcba");

	cAccess.PutStringChar("0100", 'x');
	cAccess.PutStringChar("0010", 'y');
	AssertIndexTreeDataOrdererString(&cOrderer, "dyxa");

	cAccess.Flush();
	cController.End();

	cIndexTree.Kill();
	cAccess.Kill();
	cOrderer.Kill();
	cController.Kill();

	cHelper.Kill(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeDataOrderer(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestIndexTreeDataOrdererAccess(IWT_No);
	TestIndexTreeDataOrdererAccess(IWT_Yes);
	TestIndexTreeDataOrdererRemapListNodes(IWT_No);
	TestIndexTreeDataOrdererRemapListNodes(IWT_Yes);
	TestIndexTreeDataOrdererModification(IWT_No);
	TestIndexTreeDataOrdererModification(IWT_Yes);
	TestIndexTreeDataOrdererCreation(IWT_No);
	TestIndexTreeDataOrdererCreation(IWT_Yes);

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

