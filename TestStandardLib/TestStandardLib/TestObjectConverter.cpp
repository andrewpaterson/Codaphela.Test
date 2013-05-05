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

	cNS2->Init(sz2, cDiamond, "12345");
	sz2->Init("6789");

	sz3 = OMalloc(CString);
	sz3->Init("End");
	cDiamond->Init(sz3, ONNull(CTestNamedString), "Before Swine");

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
void TestObjectConverterDragonExistingHollows(void)
{
	CObjectConverterNative				cChunkedConverter;
	CObjectSource*						pcObjectSource;
	CObjectMultipleSource*				pcObjectMultipleSource;
	CPointerObject						pcObject;
	CDiskFile*							pcDiskFile;
	CPointer<CTestDoubleNamedString>	pcDoubleNamedString;
	CPointer<CRoot>						pcRoot;
	CPointer<CTestNamedString>			pcObject2;
	CTestNamedString*					pcEnd;
	CNamedHollowObject*					pcHollow;
	CPointer<CTestNamedString>			pcObject3;
	CTestNamedString*					pcTestNamedString3;
	CTestNamedString*					pcTestNamedString2;

	ObjectsInit();
	WriteObjectConverterChunkedFile();
	ObjectsKill();

	ObjectsInit();
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
	AssertString("CTestDoubleNamedString", pcObject.ClassName());

	pcDoubleNamedString = pcObject;
	AssertNotNull(&pcDoubleNamedString->mszString);
	AssertFalse(pcDoubleNamedString->mszString->IsHollow());
	AssertString("Start", pcDoubleNamedString->mszString->Text());
	AssertInt(-1, pcDoubleNamedString->mszString->DistToRoot());

	pcObject = pcDoubleNamedString->mpSplit1;
	AssertTrue(pcObject.IsNotNull());
	AssertTrue(pcObject.IsHollow());
	AssertInt(-1, pcObject.DistToRoot());
	AssertString("NamedString 2", pcObject.GetName());

	pcRoot = ORoot();
	AssertLongLongInt(5, pcRoot->GetOI());

	pcRoot->Add(pcDoubleNamedString);
	AssertInt(2, pcDoubleNamedString->DistToRoot());
	AssertInt(3, pcDoubleNamedString->mszString->DistToRoot());
	AssertTrue(pcObject.IsNotNull());
	AssertTrue(pcObject.IsHollow());
	AssertInt(3, pcObject.DistToRoot());
	AssertString("NamedString 2", pcObject.GetName());
	AssertLongLongInt(3, pcObject.GetIndex());

	AssertString("NamedString 1", pcDoubleNamedString->mpSplit2.GetName());
	AssertTrue(pcDoubleNamedString->mpSplit2.IsNotNull());
	AssertTrue(pcDoubleNamedString->mpSplit2.IsHollow());
	AssertInt(3, pcDoubleNamedString->mpSplit2.DistToRoot());
	
	pcHollow = (CNamedHollowObject*)gcObjects.GetInMemoryObject(3LL);
	AssertNotNull(pcHollow);
	AssertString("NamedString 2", pcHollow->GetName());

	pcEnd = (CTestNamedString*)gcObjects.GetInMemoryObject(7LL);
	AssertNull(pcEnd);

	pcObject2 = pcObjectSource->Convert("NamedString 2");
	AssertString("CTestNamedString", pcObject2.ClassName());
	AssertLongLongInt(3, pcObject2.GetIndex());
	AssertTrue(pcObject2.IsNotNull());
	pcObject = pcDoubleNamedString->mpSplit1;
	AssertPointer(pcObject.Object(), pcObject2.Object());
	AssertFalse(pcObject2.IsHollow());
	AssertInt(3, pcObject2.DistToRoot());
	AssertString("NamedString 2", pcObject2.GetName());
	pcTestNamedString2 = (CTestNamedString*)pcObject2.Object();
	AssertString("6789", pcTestNamedString2->mszString->Text());
	AssertTrue(pcTestNamedString2->mpAnother.IsHollow());
	AssertString("Diamond End", pcTestNamedString2->mpAnother.GetName());
	AssertLongLongInt(9, pcTestNamedString2->mpAnother.GetIndex());

	pcObject3 = pcObjectSource->Convert("NamedString 1");
	AssertFalse(pcObject3.IsNull());
	AssertString("CTestNamedString", pcObject3.ClassName());
	pcTestNamedString3 = (CTestNamedString*)pcObject3.Object();
	AssertString("World", pcTestNamedString3->mszString->Text());
	AssertTrue(pcTestNamedString3->mpAnother.IsHollow());
	AssertString("Diamond End", pcTestNamedString3->mpAnother.GetName());
	AssertLongLongInt(9, pcTestNamedString3->mpAnother.GetIndex());
	AssertPointer(pcTestNamedString2->mpAnother.Object(), pcTestNamedString3->mpAnother.Object());
	AssertTrue(pcTestNamedString2->mpAnother.IsHollow());

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

	ObjectsInit();

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
CPointer<CTestDoubleNamedString> SetupObjectConverterChunkFile2(void)
{
	CPointer<CTestNamedString>			cNS1;
	CPointer<CTestNamedString>			cNS2;
	CPointer<CTestNamedString>			cNS3;
	CPointer<CTestNamedString>			cDiamond;
	CPointer<CTestDoubleNamedString>	cDouble;
	CPointer<CRoot>						cRoot;

	cRoot = ORoot();

	cDiamond = ONMalloc(CTestNamedString, "Diamond");

	cNS1 = ONMalloc(CTestNamedString, "NS1");
	cNS1->Init(ONNull(CString), cDiamond, "NS1");

	cNS2 = ONMalloc(CTestNamedString, "NS2");
	cNS2->Init(ONNull(CString), cDiamond, "NS2");

	cNS3 = ONMalloc(CTestNamedString, "NS3");
	cNS3->Init(ONNull(CString), cNS1, "NS3");

	cDiamond->Init(ONNull(CString), ONNull(CTestNamedString), "Diamond");

	cDouble = ONMalloc(CTestDoubleNamedString, "Double");
	cDouble->Init(ONNull(CString), cNS2, cNS3);

	cRoot->Add(cDouble);
	return cDouble;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void WriteObjectConverterChunkedFile2(void)
{
	CPointer<CTestDoubleNamedString>	cDouble;
	CObjectWriterChunked				cWriter;
	CObjectGraphSerialiser				cGraphSerialiser;

	cDouble = SetupObjectConverterChunkFile2();

	cWriter.Init("Output\\ObjectConverter\\", "", "Trouble");
	cGraphSerialiser.Init(&cWriter);
	AssertTrue(cGraphSerialiser.Write(&cDouble));
	cGraphSerialiser.Kill();
	cWriter.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectConverterDragonRootDistance(void)
{
	CObjectConverterNative				cChunkedConverter;
	CObjectSource*						pcObjectSource;
	CPointer<CTestDoubleNamedString>	pcDouble;
	CPointer<CTestNamedString>			pcNS1;
	CPointer<CTestNamedString>			pcNS2;
	CPointer<CTestNamedString>			pcNS3;
	CPointer<CTestNamedString>			pcDiamond;
	CDiskFile*							pcDiskFile;
	CPointer<CRoot>						pcRoot;

	ObjectsInit();
	WriteObjectConverterChunkedFile2();
	ObjectsKill();

	ObjectsInit();
	SetupObjectConverterConstructors();

	pcDiskFile = DiskFile("Output\\ObjectConverter\\Trouble.DRG");
	cChunkedConverter.Init(gcObjects.GetIndexGenerator());
	pcObjectSource = cChunkedConverter.CreateSource(pcDiskFile, "Trouble");

	pcDouble = pcObjectSource->Convert("Double");
	pcRoot = ORoot();
	pcRoot->Add(pcDouble);

	pcNS1 = pcObjectSource->Convert("NS1");
	pcNS3 = pcObjectSource->Convert("NS3");
	AssertPointer(&pcNS1, &pcNS3->mpAnother);
	AssertPointer(&pcNS3, &pcDouble->mpSplit1);

	AssertInt(2, pcDouble->DistToRoot());
	AssertInt(3, pcNS3->DistToRoot());
	AssertInt(4, pcNS1->DistToRoot());

	pcDiamond = pcObjectSource->Convert("Diamond");
	AssertPointer(&pcDiamond, &pcNS1->mpAnother);
	AssertInt(5, pcDiamond->DistToRoot());

	pcNS2 = pcObjectSource->Convert("NS2");
	AssertPointer(&pcNS2, &pcDouble->mpSplit2);
	AssertInt(3, pcNS2->DistToRoot());

	AssertPointer(&pcDiamond, &pcNS2->mpAnother);
	AssertInt(4, pcDiamond->DistToRoot());

	pcObjectSource->Kill();
	cChunkedConverter.Kill();

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
	TestObjectConverterDragonExistingHollows();
	TestObjectConverterDragonRootDistance();

	TestStatistics();

	cFileUtil.RemoveDir("Output");
}

