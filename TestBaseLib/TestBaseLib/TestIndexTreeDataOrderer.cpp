#include "BaseLib/IndexTreeMemory.h"
#include "BaseLib/IndexTreeMemoryAccess.h"
#include "BaseLib/AccessDataOrderer.h"
#include "BaseLib/ModificationDataOrderer.h"
#include "BaseLib/CreationDataOrderer.h"
#include "BaseLib/GlobalMemory.h"
#include "TestLib/Assert.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertIndexTreeDataOrdererString(CIndexTreeDataOrderer* pcOrderer, char* szExpected)
{
	SDataOrderIterator	sIter;
	char*				pc;
	int					iSize;
	BOOL				bExists;
	CChars				sz;

	sz.Init();
	bExists = pcOrderer->StartIteration(&sIter, (void**)&pc, &iSize);
	while (bExists)
	{
		sz.Append(*pc);
		bExists = pcOrderer->Iterate(&sIter, (void**)&pc, &iSize);
	}

	AssertString(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeDataOrdererAccess(void)
{
	CIndexTreeMemory			cIndexTree;
	CIndexTreeMemoryAccess		cAccess;
	CAccessDataOrderer			cOrderer;
	char						c;
	SIndexTreeMemoryIterator	sIter;
	BOOL						bExists;

	cOrderer.Init();
	cIndexTree.Init(IKR_No, &cOrderer);
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

	bExists = cIndexTree.StartUnsafeIteration(&sIter, NULL, NULL);
	AssertTrue(bExists);
	AssertIndexTreeDataOrdererString(&cOrderer, "adbc");
	bExists = cIndexTree.UnsafeIterate(&sIter, NULL, NULL);
	AssertTrue(bExists);
	AssertIndexTreeDataOrdererString(&cOrderer, "cadb");
	bExists = cIndexTree.UnsafeIterate(&sIter, NULL, NULL);
	AssertTrue(bExists);
	AssertIndexTreeDataOrdererString(&cOrderer, "bcad");
	bExists = cIndexTree.UnsafeIterate(&sIter, NULL, NULL);
	AssertTrue(bExists);
	AssertIndexTreeDataOrdererString(&cOrderer, "dbca");
	bExists = cIndexTree.UnsafeIterate(&sIter, NULL, NULL);
	AssertFalse(bExists);

	cIndexTree.Kill();
	cAccess.Kill();
	cOrderer.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeDataOrdererRemapListNodes(void)
{
	CIndexTreeMemory			cIndexTree;
	CIndexTreeMemoryAccess		cAccess;
	CAccessDataOrderer			cOrderer;
	int							i;

	cOrderer.Init();
	cIndexTree.Init(IKR_Yes, &cOrderer);
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

	for (i = 0; i <= 60; i+=2)
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

	for (i = 60; i >= 0; i-=2)
	{
		AssertTrue(cAccess.HasInt(i << 8));
	}
	AssertIndexTreeDataOrdererString(&cOrderer, "ACEGIKMOQSUWY[]_acegikmoqsuwy{}|zxvtrpnljhfdb`^\\ZXVTRPNLJHFDB");

	cIndexTree.Kill();
	cAccess.Kill();
	cOrderer.Kill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeDataOrdererModification(void)
{
	CIndexTreeMemory			cIndexTree;
	CIndexTreeMemoryAccess		cAccess;
	CModificationDataOrderer	cOrderer;
	int							i;
	int							iKey;
	char						c;

	cOrderer.Init();
	cIndexTree.Init(IKR_Yes, &cOrderer);
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

	for (i = 0; i <= 25; i+=2)
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

	cIndexTree.Kill();
	cAccess.Kill();
	cOrderer.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeDataOrdererCreation(void)
{
	CIndexTreeMemory			cIndexTree;
	CIndexTreeMemoryAccess		cAccess;
	CCreationDataOrderer		cOrderer;

	cOrderer.Init();
	cIndexTree.Init(IKR_Yes, &cOrderer);
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

	cIndexTree.Kill();
	cAccess.Kill();
	cOrderer.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeDataOrderer(void)
{
	BeginTests();
	FastFunctionsInit();
	MemoryInit();

	TestIndexTreeDataOrdererAccess();
	TestIndexTreeDataOrdererRemapListNodes();
	TestIndexTreeDataOrdererModification();
	TestIndexTreeDataOrdererCreation();

	MemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

