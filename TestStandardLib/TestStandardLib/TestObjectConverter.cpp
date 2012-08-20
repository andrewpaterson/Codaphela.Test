#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectConverterText.h"
#include "StandardLib/ObjectConverterNative.h"
#include "StandardLib/String.h"
#include "TestLib/Assert.h"
#include "ObjectWriterChunkedTestClasses.h"


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
void SetupObjectConverterChunkFile(void)
{
	CPointer<CTestNamedString>	cNS1;
	CPointer<CString>			sz;

	cNS1 = ONMalloc(CTestNamedString, "NamedString 1");
	sz = OMalloc(CString);

	cNS1->Init(sz, gcObjects.Null<CTestNamedString>(), "Hello");
	sz->Init("World");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void SetupObjectConverterBasicFile(void)
{

}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectConverterDragon(void)
{
	SetupObjectConverterChunkFile();
	SetupObjectConverterBasicFile();

	CObjectConverterNative	cChunkedConverter;
	CObjectSource*			pcObjectSource;
	CPointerObject			pcObject;
	CObjectSourceNative*	pcNativeSource;

	cChunkedConverter.Init();
	pcObjectSource = cChunkedConverter.CreateSource(NULL, "");
	AssertNotNull(pcObjectSource);
	AssertTrue(pcObjectSource->IsNative());
	pcNativeSource = (CObjectSourceNative*)pcObjectSource;

	pcNativeSource->Convert("");

	pcObjectSource->Kill();
	cChunkedConverter.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectConverter(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/ObjectConverter");

	ObjectsInit(NULL);
	BeginTests();

	TestObjectConverterText();
	TestObjectConverterDragon();

	TestStatistics();
	ObjectsKill();

	cFileUtil.RemoveDir("Output");
}

