#include "BaseLib/FileIO.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/EnumeratorTemplate.h"
#include "BaseLib/EnumeratorBlock.h"
#include "BaseLib/LinkListAligned.h"
#include "BaseLib/LinkListBlock.h"
#include "BaseLib/TreeTemplate.h"
#include "BaseLib/TreeBlock.h"
#include "TestLib/Assert.h"
#include "FileIOTestObjects.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOBegin(CMemoryFile* pcMemory, CFileBasic* pcFile)
{
	pcMemory->Init();
	pcFile->Init(pcMemory);

	AssertTrue(pcFile->Open(EFM_Write_Create));
	AssertTrue(pcFile->WriteData("MagicPadding\0", 14));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOMiddle(CFileBasic* pcFile)
{
	char			szMagic[14];

	AssertTrue(pcFile->WriteData("HappyEnding\0", 13));
	AssertTrue(pcFile->Close());
	AssertTrue(pcFile->Open(EFM_Read));
	AssertTrue(pcFile->ReadData(szMagic, 14));
	AssertString("MagicPadding", szMagic);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOEnd(CMemoryFile* pcMemory, CFileBasic* pcFile)
{
	char			szHappy[13];

	AssertTrue(pcFile->ReadData(szHappy, 13));
	AssertString("HappyEnding", szHappy);
	AssertTrue(pcFile->Close());
	pcFile->Kill();
	pcMemory->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOHelpers(void)
{
	CMemoryFile		cMemory;
	CFileBasic		cFile;
	unsigned char	ab[7] = {0x5e, 0xe1, 0x9e, 0x03, 0x32, 0x1f, 0x93};
	int				ai[3] = {0x7deb74f3, 0x41b0f58c, 0x5cbf05d8};
	int				i;
	long long int	l;
	float			f;
	double			d;
	char			c;
	unsigned char	uc;
	BOOL			b;
	short			s;
	unsigned short	us;
	unsigned char	abi[7];
	int				aii[3];

	TestFileIOBegin(&cMemory, &cFile);

	AssertTrue(cFile.WriteInt(0xf48e33a9));
	AssertTrue(cFile.WriteLong(0xcbb671c1babc0022LL));
	AssertTrue(cFile.WriteFloat(3.34759834536f));
	AssertTrue(cFile.WriteDouble(8.4936205629457392304853));
	AssertTrue(cFile.WriteChar('g'));
	AssertTrue(cFile.WriteChar((unsigned char)255));
	AssertTrue(cFile.WriteBool(TRUE));
	AssertTrue(cFile.WriteShort((short)0x5a0a));
	AssertTrue(cFile.WriteShort((unsigned short)0x6be4));
	AssertTrue(cFile.WriteBits(ab, 7));
	AssertTrue(cFile.WriteIntArray(ai, 3));

	AssertTrue(cFile.WriteInt(0x091bfe25));
	AssertTrue(cFile.WriteLong(0xe98ebf36c079e63aLL));
	AssertTrue(cFile.WriteFloat(6.478389585938f));
	AssertTrue(cFile.WriteDouble(2.74944978325209529023823));
	AssertTrue(cFile.WriteChar('@'));
	AssertTrue(cFile.WriteChar((unsigned char)1));
	AssertTrue(cFile.WriteBool(FALSE));
	AssertTrue(cFile.WriteShort((short)0x0001));
	AssertTrue(cFile.WriteShort((unsigned short)0xffff));

	TestFileIOMiddle(&cFile);
	
	AssertTrue(cFile.ReadInt(&i));
	AssertInt(0xf48e33a9, i);
	AssertTrue(cFile.ReadLong(&l));
	AssertLongLongInt(0xcbb671c1babc0022LL, l);
	AssertTrue(cFile.ReadFloat(&f));
	AssertFloat(3.34759834536f, f, 13);
	AssertTrue(cFile.ReadDouble(&d));
	AssertDouble(8.4936205629457392304853, d, 19);
	AssertTrue(cFile.ReadChar(&c));
	AssertChar('g', c);
	AssertTrue(cFile.ReadChar(&uc));
	AssertChar((char)255, uc);
	AssertTrue(cFile.ReadBool(&b));
	AssertBool(TRUE, b);
	AssertTrue(cFile.ReadShort(&s));
	AssertShort((short)0x5a0a, s);
	AssertTrue(cFile.ReadShort((unsigned short*)&us));
	AssertShort((unsigned short)0x6be4, us);
	AssertTrue(cFile.ReadBits(abi, 7));
	AssertMemory(ab, abi, 7);
	AssertTrue(cFile.ReadIntArray(aii, 3));
	AssertMemory(ai, aii, 3 * sizeof(int));

	AssertTrue(cFile.ReadInt(&i));
	AssertInt(0x091bfe25, i);
	AssertTrue(cFile.ReadLong(&l));
	AssertLongLongInt(0xe98ebf36c079e63aLL, l);
	AssertTrue(cFile.ReadFloat(&f));
	AssertFloat(6.478389585938f, f, 13);
	AssertTrue(cFile.ReadDouble(&d));
	AssertDouble(2.74944978325209529023823, d, 19);
	AssertTrue(cFile.ReadChar(&c));
	AssertChar('@', c);
	AssertTrue(cFile.ReadChar(&uc));
	AssertChar(1, uc);
	AssertTrue(cFile.ReadBool(&b));
	AssertBool(FALSE, b);
	AssertTrue(cFile.ReadShort(&s));
	AssertShort((short)0x0001, s);
	AssertTrue(cFile.ReadShort((unsigned short*)&us));
	AssertShort((unsigned short)0xffff, us);

	TestFileIOEnd(&cMemory, &cFile);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOEnumerator(void)
{
	CMemoryFile							cMemory;
	CFileBasic							cFile;
	CEnumeratorTemplate<CFileIOTest>	cEnumerator;
	CFileIOTest							cTest;
	CFileIOTest*						pcTestIn;
	CEnumeratorTemplate<CFileIOTest>	cEnumeratorIn;

	TestFileIOBegin(&cMemory, &cFile);

	cTest.Init(83);
	cEnumerator.Init();
	cEnumerator.Add("I Dunno", &cTest, 2);

	AssertTrue(cEnumerator.WriteEnumeratorTemplate(&cFile));

	cEnumerator.Kill();
	TestFileIOMiddle(&cFile);

	AssertTrue(cEnumeratorIn.ReadEnumeratorTemplate(&cFile));
	AssertInt(2, cEnumeratorIn.Get("I Dunno", &pcTestIn));
	AssertTrue(pcTestIn->IsOkay(83));

	cEnumeratorIn.Kill();
	TestFileIOEnd(&cMemory, &cFile);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOTree(void)
{
	CMemoryFile					cMemory;
	CFileBasic					cFile;
	CTreeTemplate<CFileIOTest>	cTree;
	CTreeBlock					cBlock;
	CTreeBlock					cBlockIn;
	CFileIOTest*				pcRoot;
	CFileIOTest*				pcChild;
	CFileIOTest*				pcGrandChild;
	CTreeTemplate<CFileIOTest>	cTreeIn;
	CFileIOTest*				pcRootIn;
	CFileIOTest*				pcChildIn;
	CFileIOTest*				pcGrandChildIn;
	CFileIOTest*				pcBlockRoot;
	CFileIOTest*				pcBlockChild;

	TestFileIOBegin(&cMemory, &cFile);

	cTree.Init();
	pcRoot = cTree.InsertRoot();
	pcRoot->Init(672);
	pcChild = cTree.InsertOnRightOfChildren(pcRoot);
	pcChild->Init(720);
	pcGrandChild = cTree.InsertOnRightOfChildren(pcChild);
	pcGrandChild->Init(666);
	pcChild = cTree.InsertOnRightOfChildren(pcRoot);
	pcChild->Init(8);
	pcChild = cTree.InsertOnRightOfChildren(pcRoot);
	pcChild->Init(99);
	AssertInt(5, cTree.NumElements());
	AssertTrue(cTree.WriteTreeTemplate(&cFile));
	pcRoot = cTree.GetRoot();
	AssertTrue(pcRoot->IsOkay(672));
	pcChild = cTree.GetUp(pcRoot);
	AssertTrue(pcChild->IsOkay(720));
	AssertNull(cTree.GetDown(pcRoot));

	cBlock.Init();
	pcBlockRoot = (CFileIOTest*)cBlock.InsertRoot(sizeof(CFileIOTest));
	pcBlockRoot->Init(1337);
	pcBlockChild = (CFileIOTest*)cBlock.InsertOnRightOfChildren(pcBlockRoot, sizeof(CFileIOTest));
	pcBlockChild->Init(54321);
	AssertInt(2, cBlock.NumElements());
	AssertTrue(cBlock.WriteTreeUnknown(&cFile));

	cBlock.Kill();
	cTree.Kill();
	TestFileIOMiddle(&cFile);

	AssertTrue(cTreeIn.ReadTreeTemplate(&cFile));
	AssertInt(5, cTreeIn.NumElements());
	pcRootIn = cTreeIn.GetRoot();
	AssertTrue(pcRootIn->IsOkay(672));
	pcChildIn = cTreeIn.GetUp(pcRootIn);
	AssertTrue(pcChildIn->IsOkay(720));
	pcGrandChildIn = cTreeIn.GetUp(pcChildIn);
	AssertTrue(pcGrandChildIn->IsOkay(666));
	pcChildIn = cTreeIn.GetRight(pcChildIn);
	AssertTrue(pcChildIn->IsOkay(8));
	pcChildIn = cTreeIn.GetRight(pcChildIn);
	AssertTrue(pcChildIn->IsOkay(99));
	pcChildIn = cTreeIn.GetRight(pcChildIn);
	AssertNull(pcChildIn);
	pcChildIn = cTreeIn.GetUp(pcRootIn);
	pcChildIn = cTreeIn.GetRight(pcChildIn);
	pcGrandChildIn = cTreeIn.GetUp(pcChildIn);
	AssertNull(pcGrandChildIn);
	AssertNull(cTreeIn.GetDown(pcRootIn));

	AssertTrue(cBlockIn.ReadTreeUnknown(&cFile));
	AssertInt(2, cBlockIn.NumElements());
	pcBlockRoot = (CFileIOTest*)cBlockIn.GetRoot();
	AssertTrue(pcBlockRoot->IsOkay(1337));
	pcBlockChild = (CFileIOTest*)cBlockIn.GetUp(pcBlockRoot);
	AssertTrue(pcBlockChild->IsOkay(54321));

	cTreeIn.Kill();
	TestFileIOEnd(&cMemory, &cFile);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOLinkList(void)
{
	CMemoryFile						cMemory;
	CFileBasic						cFile;
	CLinkListTemplate<CFileIOTest>	cLinkList;
	CFileIOTest*					pcTest1;
	CFileIOTest*					pcTest2;
	CLinkListTemplate<CFileIOTest>	cLinkListIn;
	CFileIOTest*					pcTestIn;
	CLinkListBlock					cBlock;
	char							sz[20];
	void*							pv;
	CLinkListBlock					cBlockIn;

	TestFileIOBegin(&cMemory, &cFile);

	cLinkList.Init();
	pcTest1 = cLinkList.Add();
	pcTest1->Init(3);
	pcTest2 = cLinkList.Add();
	pcTest2->Init(887);
	AssertInt(cLinkList.NumElements(), 2);
	AssertTrue(cLinkList.WriteLinkListTemplate(&cFile));

	cBlock.Init();
	strcpy(sz, "Lurching Larch");
	pv = cBlock.InsertAfterTail(strlen(sz)+1);
	strcpy((char*)pv, sz);
	strcpy(sz, "Black Larch");
	pv = cBlock.InsertAfterTail(strlen(sz)+1);
	strcpy((char*)pv, sz);
	strcpy(sz, "Wheeling Willow");
	pv = cBlock.InsertAfterTail(strlen(sz)+1);
	strcpy((char*)pv, sz);
	AssertInt(cBlock.NumElements(), 3);
	AssertTrue(cBlock.WriteLinkListBlock(&cFile));

	cBlock.Kill();
	cLinkList.Kill();
	TestFileIOMiddle(&cFile);

	AssertTrue(cLinkListIn.ReadLinkListTemplate(&cFile));
	AssertInt(cLinkListIn.NumElements(), 2);
	pcTestIn = cLinkListIn.GetHead();
	AssertNotNull(pcTestIn);
	AssertTrue(pcTestIn->IsOkay(3));
	pcTestIn = cLinkListIn.GetNext(pcTestIn);
	AssertTrue(pcTestIn->IsOkay(887));
	pcTestIn = cLinkListIn.GetNext(pcTestIn);
	AssertNull(pcTestIn);

	AssertTrue(cBlockIn.ReadLinkListBlock(&cFile));
	AssertInt(cBlockIn.NumElements(), 3);
	pv = cBlockIn.GetHead();
	AssertString("Lurching Larch", (char*)pv);
	pv = cBlockIn.GetNext(pv);
	AssertString("Black Larch", (char*)pv);
	pv = cBlockIn.GetNext(pv);
	AssertString("Wheeling Willow", (char*)pv);
	pv = cBlockIn.GetNext(pv);
	AssertNull(pv);

	cBlockIn.Kill();
	cLinkListIn.Kill();
	TestFileIOEnd(&cMemory, &cFile);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOLinkListAligned(void)
{
	//CMemoryFile						cMemory;
	//CFileBasic						cFile;
	//CFileIOTest*					pcTestIn;
	//CLinkListAligned				cAligned;
	//CLinkListAligned				cAlignedIn;
	//CFileIOAlignedTest*				pcAli1;
	//CFileIOAlignedTest*				pcAli2;
	//CFileIOAlignedTest*				pcAliIn;

	//TestFileIOBegin(&cMemory, &cFile);

	//cAligned.Init();
	//pcAli1 = (CFileIOAlignedTest*)cAligned.Add(sizeof(CFileIOAlignedTest), 13);
	//AssertTrue(pcAli1->IsAligned(13));
	//pcAli1->Init(56);
	//pcAli2 = (CFileIOAlignedTest*)cAligned.Add(sizeof(CFileIOAlignedTest), 17);
	//AssertTrue(pcAli2->IsAligned(17));
	//pcAli2->Init(-7);
	//AssertInt(cAligned.NumElements(), 2);
	//AssertTrue(cAligned.WriteLinkListAligned(&cFile));

	//cAligned.Kill();
	//TestFileIOMiddle(&cFile);

	//AssertTrue(cAlignedIn.ReadLinkListAligned(&cFile));
	//AssertInt(cAlignedIn.NumElements(), 2);
	//pcAliIn = (CFileIOAlignedTest*)cAlignedIn.GetHead();
	//AssertNotNull(pcAliIn);
	//AssertTrue(pcAliIn->IsAligned(13));
	//AssertTrue(pcAliIn->IsOkay(56));
	//pcAliIn = (CFileIOAlignedTest*)cAlignedIn.GetNext(pcTestIn);
	//AssertNotNull(pcAliIn);
	//AssertTrue(pcAliIn->IsAligned(17));
	//AssertTrue(pcAliIn->IsOkay(-7));
	//pcAliIn = (CFileIOAlignedTest*)cAlignedIn.GetNext(pcTestIn);
	//AssertNull(pcAliIn);

	//TestFileIOEnd(&cMemory, &cFile);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOArray(void)
{
	CMemoryFile						cMemory;
	CFileBasic						cFile;
	CArrayTemplate<CFileIOTest>		acTest;
	int								i;
	CFileIOTest*					pcTest;
	CArrayTemplate<CFileIOTest>		acTestIn;
	CArrayInt						ai;
	CArrayInt						aii;
	int								ii;
	CArrayBlock						av;
	CArrayBlock						avi;
	CArrayTemplateMinimal<CFileIOTest>	asTest;
	CArrayTemplateMinimal<CFileIOTest>	asTestIn;

	TestFileIOBegin(&cMemory, &cFile);

	acTest.Init(5);
	for (i = 0; i <= 8; i++)
	{
		pcTest = acTest.Add();
		pcTest->Init(i);
	}
	ai.Init();
	for (i = 0; i <= 5; i++)
	{
		ai.Add(8-i);
	}
	av.Allocate(1, 7, 12);
	memcpy(av.GetData(), "ABCDEFGHIJK\0", 12);
	asTest.Init();
	for (i = 0; i <= 10; i++)
	{
		pcTest = asTest.Add();
		pcTest->Init(i*3-2);
	}

	AssertInt(9, acTest.NumElements());
	AssertInt(10, acTest.AllocatedElements());
	AssertInt(6, ai.NumElements());
	AssertInt(6, ai.AllocatedElements());
	AssertInt(12, av.NumElements());
	AssertInt(14, av.AllocatedElements());
	AssertInt(11, asTest.NumElements());
	AssertTrue(acTest.WriteArrayTemplate(&cFile));
	AssertTrue(ai.WriteArrayInt(&cFile));
	AssertTrue(av.WriteArrayUnknown(&cFile));
	AssertTrue(asTest.WriteArraySimple(&cFile));

	asTest.Kill();
	av.Kill();
	ai.Kill();
	acTest.Kill();
	TestFileIOMiddle(&cFile);

	AssertTrue(acTestIn.ReadArrayTemplate(&cFile));
	AssertInt(9, acTestIn.NumElements());
	AssertInt(10, acTestIn.AllocatedElements());
	for (i = 0; i <= 8; i++)
	{
		pcTest = acTestIn.Get(i);
		AssertTrue(pcTest->IsOkay(i));
	}
	AssertTrue(aii.ReadArrayInt(&cFile));
	AssertInt(6, aii.NumElements());
	AssertInt(6, aii.AllocatedElements());
	for (i = 0; i <= 5; i++)
	{
		ii = aii.GetValue(i);
		AssertInt(8-i, ii);
	}
	AssertTrue(avi.ReadArrayUnknown(&cFile));
	AssertInt(12, avi.NumElements());
	AssertInt(14, avi.AllocatedElements());
	AssertString("ABCDEFGHIJK", (char*)avi.GetData());
	AssertTrue(asTestIn.ReadArraySimple(&cFile));
	AssertInt(11, asTestIn.NumElements());
	for (i = 0; i <= 10; i++)
	{
		pcTest = asTestIn.Get(i);
		AssertTrue(pcTest->IsOkay(i*3-2));
	}

	asTestIn.Kill();
	avi.Kill();
	aii.Kill();
	acTestIn.Kill();

	TestFileIOEnd(&cMemory, &cFile);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOString(void)
{
	CMemoryFile		cMemory;
	CFileBasic		cFile;
	CChars			sz;
	CChars			szi;
	CChars			szi2;
	char			szc[4];
	int				i;

	TestFileIOBegin(&cMemory, &cFile);

	sz.Init("You, flock of seagulls, you know why we're here?");
	AssertTrue(sz.WriteString(&cFile));
	AssertTrue(cFile.WriteString("That means they only eat vegetables, but for you, I think they'd make an exception."));
	AssertTrue(cFile.WriteString("123"));

	sz.Kill();
	TestFileIOMiddle(&cFile);

	AssertTrue(szi.ReadString(&cFile));
	AssertString("You, flock of seagulls, you know why we're here?", szi.Text());
	AssertTrue(szi2.ReadChars(&cFile));
	AssertString("That means they only eat vegetables, but for you, I think they'd make an exception.", szi2.Text());
	AssertTrue(cFile.ReadStringLength(&i));
	AssertInt(4, i);
	AssertTrue(cFile.ReadStringChars(szc, i));
	AssertString("123", szc);

	szi2.Kill();
	szi.Kill();
	TestFileIOEnd(&cMemory, &cFile);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOMap(void)
{
	CMemoryFile						cMemory;
	CFileBasic						cFile;
	CMapTemplate<int, long double>	cMap;
	int								i;
	long double						ld;
	CMapTemplate<int, long double>	cMapIn;
	CMapStringInt					mssi;
	CMapStringInt					mssii;

	TestFileIOBegin(&cMemory, &cFile);
	
	cMap.Init(10, &CompareInt);
	i = 9;	ld = 1.4783409838732098273349;
	cMap.Put(&i, &ld);
	i = 22;	ld = 1.7983487629380598763752;
	cMap.Put(&i, &ld);
	i = 4;	ld = 1.9237643187634765139872;
	cMap.Put(&i, &ld);
	AssertInt(3, cMap.NumElements());
	AssertTrue(cMap.WriteMapHeader(&cFile));

	mssi.Init(10, TRUE);
	mssi.Put("lion", 7);
	mssi.Put("eat", 1);
	mssi.Put("zebra", 12);
	mssi.Put("for real!", -1);
	AssertInt(4, mssi.NumElements());
	AssertTrue(mssi.WriteMapHeader(&cFile));

	mssi.Kill();
	cMap.Kill();
	TestFileIOMiddle(&cFile);

	AssertTrue(cMapIn.ReadMapHeader(&cFile));
	AssertInt(3, cMapIn.NumElements());
	//CMapTemplate doesn't actually have full read and write methods.

	AssertTrue(mssii.ReadMapHeader(&cFile));
	AssertInt(4, mssii.NumElements());
	//CMapStringInt doesn't actually have full read and write methods.

	mssii.KillArray();
	cMapIn.KillArray();
	TestFileIOEnd(&cMemory, &cFile);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIO(void)
{
	BeginTests();

	TestFileIOHelpers();
	TestFileIOArray();
	TestFileIOString();
	TestFileIOEnumerator();
	TestFileIOTree();
	TestFileIOLinkList();
	TestFileIOLinkListAligned();
	TestFileIOMap();

	TestStatistics();
}
