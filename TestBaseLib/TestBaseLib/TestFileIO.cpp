#include "BaseLib/FileIO.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/EnumeratorTemplate.h"
#include "BaseLib/EnumeratorBlock.h"
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

	//template<class M>	BOOL	ReadEnumeratorTemplate(CEnumeratorTemplate<M>* pcEnumerator);
	//BOOL	ReadEnumeratorBlock(CEnumeratorBlock* pcEnumerator);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOTree(void)
{
	CMemoryFile		cMemory;
	CFileBasic		cFile;

	TestFileIOBegin(&cMemory, &cFile);

	TestFileIOMiddle(&cFile);

	TestFileIOEnd(&cMemory, &cFile);

	//template<class M>	BOOL	ReadTreeTemplate(CTreeTemplate<M>* pcTree);
	//BOOL	ReadTreeUnknown(CTreeBlock* pcTree);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOLinkList(void)
{
	CMemoryFile		cMemory;
	CFileBasic		cFile;

	TestFileIOBegin(&cMemory, &cFile);

	TestFileIOMiddle(&cFile);

	TestFileIOEnd(&cMemory, &cFile);

	//BOOL	ReadLinkListBlock(CFileReader* pcFileReader);
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
	CArraySimple<CFileIOTest>		asTest;
	CArraySimple<CFileIOTest>		asTestIn;

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
void TestFileIO(void)
{
	BeginTests();

	TestFileIOHelpers();
	TestFileIOArray();
	TestFileIOString();
	TestFileIOEnumerator();
	TestFileIOTree();
	TestFileIOLinkList();

	TestStatistics();
}
