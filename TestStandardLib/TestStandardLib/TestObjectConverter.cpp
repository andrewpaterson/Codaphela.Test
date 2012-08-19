#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectConverterText.h"
#include "StandardLib/ObjectConverterChunked.h"
#include "StandardLib/String.h"
#include "TestLib/Assert.h"
#include "TestObjectConverter.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectConverterText(void)
{
	CObjectConverterText	cTextConverter;
	char					szTextInFile[] = {"This is text\nin a file.\n"};
	int						iTextLen;
	CMemoryFile				cMemoryFile;
	CObjectSource*			pcObjectSource;
	CPointerObject			pcObject;
	CPointer<CString>		pcString;
	
	iTextLen = strlen(szTextInFile);
	cMemoryFile.Init(szTextInFile, iTextLen);

	cTextConverter.Init();
	pcObjectSource = cTextConverter.CreateSource(&cMemoryFile, "");
	pcString = pcObjectSource->Convert("");
	AssertString(szTextInFile, pcString->Text());
	pcString->Kill();

	cMemoryFile.Kill();
	pcObjectSource->Kill();
	cTextConverter.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectConverterDragon(void)
{
	CObjectConverterChunked	cChunkedConverter;
	CObjectSource*			pcObjectSource;
	CPointerObject			pcObject;

	cChunkedConverter.Init();
	pcObjectSource = cChunkedConverter.CreateSource(NULL, "");
	pcObjectSource->Convert("");

	pcObjectSource->Kill();
	cChunkedConverter.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectConverter(void)
{
	ObjectsInit(NULL);
	BeginTests();

	TestObjectConverterText();
	TestObjectConverterDragon();

	TestStatistics();
	ObjectsKill();
}

