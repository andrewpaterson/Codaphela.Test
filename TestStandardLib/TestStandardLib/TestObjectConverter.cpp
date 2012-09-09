#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectConverterText.h"
#include "StandardLib/ObjectConverterNative.h"
#include "StandardLib/String.h"
#include "StandardLib/ObjectWriterChunked.h"
#include "StandardLib/ObjectGraphSerialiser.h"
#include "TestLib/Assert.h"
#include "ObjectWriterChunkedTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer<CTestDoubleNamedString> SetupObjectConverterChunkFile(void)
{
	CPointer<CTestNamedString>			cNS1;
	CPointer<CTestNamedString>			cNS2;
	CPointer<CTestNamedString>			cDiamond;
	CPointer<CTestDoubleNamedString>	cDouble;
	CPointer<CString>					sz1;
	CPointer<CString>					sz3;
	CPointer<CString>					sz2;
	CPointer<CString>					sz4;
	CPointer<CRoot>						cRoot;

	cRoot = ORoot();

	cDiamond = ONMalloc(CTestNamedString, "Diamond End");

	cNS1 = ONMalloc(CTestNamedString, "NamedString 1");
	sz1 = OMalloc(CString);

	cNS1->Init(sz1, cDiamond, "Hello");
	sz1->Init("World");

	cNS2 = ONMalloc(CTestNamedString, "NamedString 2");
	sz2 = OMalloc(CString);

	cNS2->Init(sz2, cDiamond, "Hello");
	sz2->Init("World");

	sz3 = OMalloc(CString);
	sz3->Init("End");
	cDiamond->Init(sz3, ONNull(CTestNamedString), "1234");

	sz4 = OMalloc(CString);
	sz4->Init("Start");
	cDouble = ONMalloc(CTestDoubleNamedString, "Double Start");
	cDouble->Init(sz4, cNS1, ONNull(CTestNamedString));

	cRoot->Add(cDouble);

	AssertInt(2, cDouble->DistToRoot());
	AssertInt(3, cNS1->DistToRoot());
	AssertInt(4, cDiamond->DistToRoot());
	AssertInt(-1, cNS2->DistToRoot());

	cDouble->mpSplit1 = cNS2;

	AssertInt(3, cNS2->DistToRoot());
	AssertInt(4, cDiamond->DistToRoot());

	return cDouble;
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
void WriteObjectConverterChunkedFile(void)
{
	CPointer<CTestDoubleNamedString>	cDouble;
	CObjectWriterChunked				cWriter;
	CObjectGraphSerialiser				cGraphSerialiser;

	cDouble = SetupObjectConverterChunkFile();

	cWriter.Init("Output\\ObjectConverter\\", "", "Double");
	cGraphSerialiser.Init(&cWriter);
	AssertTrue(cGraphSerialiser.Write(&cDouble));
	cGraphSerialiser.Kill();
	cWriter.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectConverterDragon(void)
{
	CObjectConverterNative	cChunkedConverter;
	CObjectSource*			pcObjectSource;
	CObjectMultipleSource*	pcObjectMultipleSource;
	CPointerObject			pcObject;
	CDiskFile*				pcDiskFile;

	WriteObjectConverterChunkedFile();

	pcDiskFile = DiskFile("Output\\ObjectConverter\\Double.DRG");
	cChunkedConverter.Init(gcObjects.GetIndexGenerator());
	pcObjectSource = cChunkedConverter.CreateSource(pcDiskFile, "Double");
	AssertNotNull(pcObjectSource);
	AssertTrue(pcObjectSource->IsNative());
	AssertTrue(pcObjectSource->IsMultiSource());

	pcObjectMultipleSource = (CObjectMultipleSource*)pcObjectSource;
	AssertInt(4, pcObjectMultipleSource->NumNames());
	AssertString("Diamond End", pcObjectMultipleSource->GetName(0));
	AssertString("Double Start", pcObjectMultipleSource->GetName(1));
	AssertString("NamedString 1", pcObjectMultipleSource->GetName(2));
	AssertString("NamedString 2", pcObjectMultipleSource->GetName(3));

	AssertTrue(pcObjectSource->Contains("Diamond End"));
	AssertTrue(pcObjectSource->Contains("Double Start"));
	AssertTrue(pcObjectSource->Contains("NamedString 1"));
	AssertTrue(pcObjectSource->Contains("NamedString 2"));
	AssertFalse(pcObjectSource->Contains("Unnamed/0000000000000006"));

	pcObject = pcObjectSource->Convert("Double Start");
	AssertNotNull(&pcObject);

	pcObjectSource->Kill();
	cChunkedConverter.Kill();
}


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
	pcObjectSource = cTextConverter.CreateSource(&cMemoryFile, "TextFile");
	AssertTrue(pcObjectSource->Contains("TextFile"));
	AssertFalse(pcObjectSource->Contains("AnythingElse"));
	AssertFalse(pcObjectSource->Contains(""));
	AssertFalse(pcObjectSource->Contains(NULL));
	pcString = pcObjectSource->Convert("TextFile");
	AssertString(szTextInFile, pcString->Text());
	pcString->Kill();

	pcString = pcObjectSource->Convert("");
	AssertNull(&pcString);

	cMemoryFile.Kill();
	pcObjectSource->Kill();
	cTextConverter.Kill();
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
	//TestObjectConverterDragon();

	TestStatistics();
	ObjectsKill();

	cFileUtil.RemoveDir("Output");
}

