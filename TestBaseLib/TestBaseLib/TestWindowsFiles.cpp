#include "Windows.h"
#include "BaseLib/FileUtil.h"
#include "TestLib/Assert.h"

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
void TestWindowsFilesTruncate(void)
{
	CFileUtil		cFileUtil;
	char			szHello[] = "Hello";
	BOOL			bResult;
	char			szResult[100];
	HANDLE			hFile;
	unsigned int	uiResult;

	cFileUtil.TouchDir("Output");

	cFileUtil.Delete("Output" _FS_ "Test2.txt");

	hFile = CreateFile("Output" _FS_ "Test2.txt",
		GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		Fail();
	}

	DWORD bytesWritten;
	bResult = WriteFile(
		hFile,
		szHello,
		strlen(szHello),
		&bytesWritten,
		NULL);
	AssertTrue(bResult);

	uiResult = SetFilePointer(hFile, 3, NULL, FILE_BEGIN);
	if (uiResult == INVALID_SET_FILE_POINTER)
	{
		Fail();
	}
	bResult = SetEndOfFile(hFile);
	AssertTrue(bResult);

	uiResult = SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
	if (uiResult == INVALID_SET_FILE_POINTER)
	{
		Fail();
	}

	memset(szResult, 0, 100);
	bResult = ReadFile(hFile, szResult, 3, NULL, NULL);
	AssertTrue(bResult);

	AssertString("Hel", szResult);

	CloseHandle(hFile);

	hFile = CreateFile("Output" _FS_ "Test2.txt",
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	memset(szResult, 0, 100);
	bResult = ReadFile(hFile, szResult, 3, NULL, NULL);
	AssertTrue(bResult);

	CloseHandle(hFile);

	cFileUtil.Delete("Output" _FS_ "Test2.txt");
}
#endif // WIN_32

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestWindowsFiles(void)
{
	BeginTests();

#ifdef _WIN32
	TestWindowsFilesTruncate();
#endif // _WIN_32

	TestStatistics();
}

