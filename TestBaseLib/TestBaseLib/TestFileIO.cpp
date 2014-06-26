#include "BaseLib/FileIO.h"
#include "BaseLib/MemoryFile.h"
#include "TestLib/Assert.h"


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
	
	int				i;
	long long int	l;
	float			f;
	double			d;
	char			c;
	unsigned char	uc;
	BOOL			b;
	short			s;
	unsigned short	us;
	
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
	CMemoryFile		cMemory;

	cMemory.Init();
	cMemory.Open(EFM_ReadWrite_Create);

	//template<class M>	BOOL	ReadEnumeratorTemplate(CEnumeratorTemplate<M>* pcEnumerator);
	//BOOL	ReadEnumeratorBlock(CEnumeratorBlock* pcEnumerator);

	cMemory.Close();
	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOTree(void)
{
	CMemoryFile		cMemory;

	cMemory.Init();
	cMemory.Open(EFM_ReadWrite_Create);

	//template<class M>	BOOL	ReadTreeTemplate(CTreeTemplate<M>* pcTree);
	//BOOL	ReadTreeUnknown(CTreeBlock* pcTree);

	cMemory.Close();
	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOArray(void)
{
	CMemoryFile		cMemory;

	cMemory.Init();
	cMemory.Open(EFM_ReadWrite_Create);

	//template<class M>	BOOL	ReadArrayTemplate(CArrayTemplate<M>* pcArray);
	//template<class M>	BOOL	ReadArrayTemplateHeader(CArrayTemplate<M>* pcArray);
	//BOOL	ReadArrayInt(CArrayInt* pcArray);
	//BOOL	ReadArrayUnknown(CArrayBlock* pcArray);
	//template<class M>	BOOL	ReadArraySimple(CArraySimple<M>* pcArray);

	cMemory.Close();
	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOString(void)
{
	CMemoryFile		cMemory;

	cMemory.Init();
	cMemory.Open(EFM_ReadWrite_Create);

	//BOOL	ReadStringLength(int* piLength);
	//BOOL	ReadStringChars(char* szString, int iLength);
	//BOOL	ReadString(CChars* szString);  //Call this one if the string was saved from a CChars
	//BOOL	ReadString(CChars* szString, BOOL bDoesntMatter);  //Or this one if the string was saved from a char*

	cMemory.Close();
	cMemory.Kill();
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

	TestStatistics();
}
