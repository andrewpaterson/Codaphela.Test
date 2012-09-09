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
void SetupObjectConverterConstructors(void)
{
	gcObjects.AddConstructor<CTestWithArray>();
	gcObjects.AddConstructor<CTestInteger>();
	gcObjects.AddConstructor<CTestNamedString>();
	gcObjects.AddConstructor<CTestDoubleNamedString>();
	gcObjects.AddConstructor<CString>();
	gcObjects.AddConstructor<CArray>();
	gcObjects.AddConstructor<CSet>();
	gcObjects.AddConstructor<CRoot>();
}


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
	CObjectConverterNative				cChunkedConverter;
	CObjectSource*						pcObjectSource;
	CObjectMultipleSource*				pcObjectMultipleSource;
	CPointerObject						pcObject;
	CDiskFile*							pcDiskFile;
	CPointer<CTestDoubleNamedString>	pcDoubleNamedString;
	CPointer<CRoot>						pcRoot;

	ObjectsInit(NULL);
	WriteObjectConverterChunkedFile();
	ObjectsKill();

	ObjectsInit(NULL);
	SetupObjectConverterConstructors();

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

	pcDoubleNamedString = pcObject;
	AssertNotNull(&pcDoubleNamedString->mszString);
	AssertFalse(pcDoubleNamedString->mszString->IsHollow());
	AssertString("Start", pcDoubleNamedString->mszString->Text());
	AssertInt(-1, pcDoubleNamedString->mszString->DistToRoot());

	pcObject = pcDoubleNamedString->mpSplit1;
	AssertTrue(pcObject.IsNotNull());
	AssertTrue(pcObject.IsHollow());
	AssertInt(-1, pcObject.DistToRoot());

	pcRoot = ORoot();
	pcRoot->Add(pcDoubleNamedString);
	AssertInt(2, pcDoubleNamedString->DistToRoot());
	AssertInt(3, pcDoubleNamedString->mszString->DistToRoot());
	AssertTrue(pcObject.IsNotNull());
	AssertTrue(pcObject.IsHollow());
	AssertInt(3, pcObject.DistToRoot());

	pcObjectSource->Kill();
	cChunkedConverter.Kill();

	ObjectsKill();
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

	ObjectsInit(NULL);

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

	ObjectsKill();
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

	BeginTests();

	TestObjectConverterText();
	TestObjectConverterDragon();

	TestStatistics();

	cFileUtil.RemoveDir("Output");
}

