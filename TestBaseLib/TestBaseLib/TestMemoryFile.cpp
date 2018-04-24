#include "BaseLib/MemoryFile.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryFile(void)
{
	BeginTests();

	CMemoryFile	cMemoryFile;
	char		szHello[] = "Hello";
	char		szWorld[] = " World";
	BOOL		bResult;
	int			iResult;
	char		szResult[100];

	cMemoryFile.Init(szHello, (int)strlen(szHello)+1);
	bResult = cMemoryFile.Open(EFM_Read);
	AssertTrue(bResult);

	iResult = (int)cMemoryFile.Read(szResult, strlenFilePos(szHello)+1, 1);
	AssertInt(1, iResult);
	AssertString(szHello, szResult);
	cMemoryFile.Seek(0, EFSO_SET);
	iResult = (int)cMemoryFile.Read(szResult, 1, (int)strlen(szHello)+1);
	AssertInt((int)strlen(szHello)+1, iResult);
	AssertString(szHello, szResult);

	bResult = cMemoryFile.Close();
	AssertTrue(bResult);
	cMemoryFile.Kill();

	cMemoryFile.Init(szHello, (int)strlen(szHello));
	bResult = cMemoryFile.Open(EFM_ReadWrite);
	AssertTrue(bResult);
	cMemoryFile.Seek(0, EFSO_END);
	iResult = (int)cMemoryFile.Write(szWorld, (int)strlen(szWorld)+1, 1);
	AssertInt(1, iResult);
	AssertString("Hello World", (char*)cMemoryFile.GetBufferPointer());

	bResult = cMemoryFile.Close();
	AssertTrue(bResult);
	cMemoryFile.Kill();

	TestStatistics();
}

