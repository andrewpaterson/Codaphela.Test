#include "BaseLib/FileIO.h"
#include "BaseLib/MemoryFile.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOHelpers(void)
{
	CMemoryFile		cFile;

	cFile.Init();
	cFile.Open(EFM_ReadWrite_Create);

	////Helpers.		
	//BOOL	ReadInt(int* pi);
	//BOOL	ReadLong(long long int* plli);
	//BOOL	ReadFloat(float* pf);
	//BOOL	ReadDouble(double* pf);
	//BOOL	ReadChar(char* pc);
	//BOOL	ReadChar(unsigned char* pc);
	//BOOL	ReadBool(BOOL* pb);
	//BOOL	ReadShort(short int* pi);
	//BOOL	ReadShort(unsigned short int* pi);
	//BOOL	ReadBits(void* pvData, int iByteLength);
	//BOOL	ReadIntArray(int* pai, int iLength);

	cFile.Close();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOEnumerator(void)
{
	CMemoryFile		cFile;

	cFile.Init();
	cFile.Open(EFM_ReadWrite_Create);

	//template<class M>	BOOL	ReadEnumeratorTemplate(CEnumeratorTemplate<M>* pcEnumerator);
	//BOOL	ReadEnumeratorBlock(CEnumeratorBlock* pcEnumerator);

	cFile.Close();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOTree(void)
{
	CMemoryFile		cFile;

	cFile.Init();
	cFile.Open(EFM_ReadWrite_Create);

	//template<class M>	BOOL	ReadTreeTemplate(CTreeTemplate<M>* pcTree);
	//BOOL	ReadTreeUnknown(CTreeBlock* pcTree);

	cFile.Close();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOArray(void)
{
	CMemoryFile		cFile;

	cFile.Init();
	cFile.Open(EFM_ReadWrite_Create);

	//template<class M>	BOOL	ReadArrayTemplate(CArrayTemplate<M>* pcArray);
	//template<class M>	BOOL	ReadArrayTemplateHeader(CArrayTemplate<M>* pcArray);
	//BOOL	ReadArrayInt(CArrayInt* pcArray);
	//BOOL	ReadArrayUnknown(CArrayBlock* pcArray);
	//template<class M>	BOOL	ReadArraySimple(CArraySimple<M>* pcArray);

	cFile.Close();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFileIOString(void)
{
	CMemoryFile		cFile;

	cFile.Init();
	cFile.Open(EFM_ReadWrite_Create);

	//BOOL	ReadStringLength(int* piLength);
	//BOOL	ReadStringChars(char* szString, int iLength);
	//BOOL	ReadString(CChars* szString);  //Call this one if the string was saved from a CChars
	//BOOL	ReadString(CChars* szString, BOOL bDoesntMatter);  //Or this one if the string was saved from a char*

	cFile.Close();
	cFile.Kill();
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


