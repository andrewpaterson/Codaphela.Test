#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/ArrayVoidPtr.h"
#include "BaseLib/ArrayBit.h"
#include "BaseLib/DataOrderers.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/IndexUnknown.h"
#include "StandardLib/IndexUnknown.h"
#include "TestLib/Assert.h"
#include "UnknownTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexUnknownAdd(void)
{
	MemoryInit();
	UnknownsInit();

	CIndexUnknown			cIndex;
	CTestUnknownJobbie*		pcValue1;
	CTestUnknownJobbie*		pcValue2;

	gcUnknowns.AddConstructor<CTestUnknown>();
	gcUnknowns.AddConstructor<CTestNamedUnknown>();
	gcUnknowns.AddConstructor<CTestUnknownJobbie>();
	gcUnknowns.AddConstructor<CTestIterableUnknown>();
	AssertInt(0, gcUnknowns.NumElements());

	cIndex.Init();

	pcValue1 = gcUnknowns.Add<CTestUnknownJobbie>();
	pcValue2 = gcUnknowns.Add<CTestUnknownJobbie>();
	pcValue1->Init(4, "Snurk");
	pcValue2->Init(67, "krust");
	AssertSize(0, cIndex.NumElements());

	cIndex.Put("Hello", pcValue1);
	AssertSize(1, cIndex.NumElements());

	cIndex.Put("World", pcValue2);
	AssertSize(2, cIndex.NumElements());

	cIndex.Kill();

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexUnknownIterate(void)
{
	MemoryInit();
	UnknownsInit();

	CIndexUnknown				cIndex;
	CTestUnknownJobbie*			pcValue1;
	CTestUnknownJobbie*			pcValue2;
	CTestUnknownJobbie*			pcValue3;
	SIndexTreeMemoryIterator	sIter;
	CUnknown*					pcValue;
	bool						bExists;
	size						uiKeyLength;
	char						szKey[20];

	gcUnknowns.AddConstructor<CTestUnknown>();
	gcUnknowns.AddConstructor<CTestNamedUnknown>();
	gcUnknowns.AddConstructor<CTestUnknownJobbie>();
	gcUnknowns.AddConstructor<CTestIterableUnknown>();
	AssertInt(0, gcUnknowns.NumElements());

	cIndex.Init();

	pcValue1 = gcUnknowns.Add<CTestUnknownJobbie>();
	pcValue2 = gcUnknowns.Add<CTestUnknownJobbie>();
	pcValue3 = gcUnknowns.Add<CTestUnknownJobbie>();
	pcValue1->Init(4, "Snurk");
	pcValue2->Init(67, "krust");
	pcValue3->Init(67, "Berry");
	AssertSize(0, cIndex.NumElements());

	cIndex.Put("SDFHLGJADH", pcValue1);
	cIndex.Put("SDFLKJF", pcValue2);
	cIndex.Put("SDBJHDFGKASFSDGF", pcValue3);
	AssertSize(3, cIndex.NumElements());

	memset(szKey, 0, 20);
	bExists = cIndex.StartIteration(&sIter, (uint8*)szKey, &uiKeyLength, 20, &pcValue);
	AssertTrue(bExists);
	AssertString("SDBJHDFGKASFSDGF", szKey);
	AssertPointer(pcValue3, pcValue);
	memset(szKey, 0, 20);
	bExists = cIndex.Iterate(&sIter, (uint8*)szKey, &uiKeyLength, 20, &pcValue);
	AssertTrue(bExists);
	AssertString("SDFHLGJADH", szKey);
	AssertPointer(pcValue1, pcValue);
	memset(szKey, 0, 20);
	bExists = cIndex.Iterate(&sIter, (uint8*)szKey, &uiKeyLength, 20, &pcValue);
	AssertTrue(bExists);
	AssertString("SDFLKJF", szKey);
	AssertPointer(pcValue2, pcValue);
	memset(szKey, 0, 20);
	bExists = cIndex.Iterate(&sIter, (uint8*)szKey, &uiKeyLength, 20, &pcValue);
	AssertFalse(bExists);

	AssertSize(3, cIndex.NumElements());

	cIndex.Kill();

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexUnknownGet(void)
{
	MemoryInit();
	UnknownsInit();

	CIndexUnknown			cIndex;
	CTestUnknownJobbie*		pcValue;
	size					ui;
	CUnknown*				pcTestValue;
	bool					bValid;
	char*					szKey;

	gcUnknowns.AddConstructor<CTestUnknown>();
	gcUnknowns.AddConstructor<CTestNamedUnknown>();
	gcUnknowns.AddConstructor<CTestUnknownJobbie>();
	gcUnknowns.AddConstructor<CTestIterableUnknown>();
	AssertInt(0, gcUnknowns.NumElements());

	cIndex.Init();

	for (ui = 0; ui < 12000; ui++)
	{
		pcValue = gcUnknowns.Add<CTestUnknownJobbie>();
		pcValue->Init((ui + 1) * 7, SizeToString(ui));
		szKey = SizeToString(ui);
		cIndex.Put(szKey, pcValue);
	}
	AssertSize(12000, cIndex.NumElements());

	bValid = false;
	for (ui = 0; ui < 12000; ui++)
	{
		szKey = SizeToString(ui);
		pcTestValue = cIndex.Get(szKey);

		bValid = StringCompare("CTestUnknownJobbie", pcTestValue->ClassName()) == 0;
		
		pcValue = (CTestUnknownJobbie*)pcTestValue;
		bValid &= ((int)ui + 1) * 7 == pcValue->miANumber;
		bValid &= StringCompare(SizeToString(ui), pcValue->mszText.Text()) == 0;

		if (!bValid)
		{
			AssertTrue(bValid);
			break;
		}
	}
	AssertTrue(bValid);


	AssertSize(12000, cIndex.NumElements());

	cIndex.Kill();

	UnknownsKill();
	MemoryKill();
}


////////////////////////////////////////////////////////////////////////////
////
////
////////////////////////////////////////////////////////////////////////////
void TestIndexUnknownLoad(void)
{
	MemoryInit();
	UnknownsInit();
	DataOrderersInit();

	CIndexUnknown				cIndex;
	CIndexUnknown				cIndexIn;
	CFileUtil					cFileUtil;
	CTestUnknownJobbie*			pcValue1;
	CUnknown*					pcValue;
	size						ui;
	CChunkFile					cFile;
	bool						bResult;
	SIndexTreeMemoryIterator	sIter;
	bool						bExists;
	bool						bValid;
	char*						szKey1;
	size						uiKeyLength;
	char						szKey[20];

	gcUnknowns.AddConstructor<CTestUnknown>();
	gcUnknowns.AddConstructor<CTestNamedUnknown>();
	gcUnknowns.AddConstructor<CTestUnknownJobbie>();
	gcUnknowns.AddConstructor<CTestIterableUnknown>();
	AssertInt(0, gcUnknowns.NumElements());

	cFileUtil.RemoveDir("Output" _FS_ "IndexUnknown");
	cFileUtil.MakeDir("Output" _FS_ "IndexUnknown");

	cIndex.Init();

	for (ui = 0; ui < 12000; ui++)
	{
		pcValue1 = gcUnknowns.Add<CTestUnknownJobbie>();
		pcValue1->Init((ui + 1) * 7, SizeToString(ui));
		szKey1 = SizeToString(ui);
		cIndex.Put(szKey1, pcValue1);
	}
	AssertSize(12000, cIndex.NumElements());
	AssertInt(12000, gcUnknowns.NumElements());

	cFile.Init(DiskFile("Output" _FS_ "IndexUnknown" _FS_ "Map.dat"));
	bResult = cFile.WriteOpen();
	AssertTrue(bResult);

	bResult = cIndex.Save(&cFile);
	AssertTrue(bResult);

	bResult = cFile.WriteClose();
	AssertTrue(bResult);

	cFile.Kill();
	cIndex.Kill();
	AssertInt(0, gcUnknowns.NumElements());

	cFile.Init(DiskFile("Output" _FS_ "IndexUnknown" _FS_ "Map.dat"));
	bResult = cFile.ReadOpen();
	AssertTrue(bResult);

	bResult = cIndexIn.Load(&cFile);
	AssertTrue(bResult);

	bResult = cFile.ReadClose();
	AssertTrue(bResult);
	cFile.Kill();
	AssertInt(12000, cIndexIn.NumElements());
	AssertInt(12000, gcUnknowns.NumElements());

	ui = 0;
	bValid = false;
	bExists = cIndexIn.StartIteration(&sIter, (uint8*)szKey, &uiKeyLength, 20, &pcValue);
	while (bExists)
	{
		bValid = StringCompare("CTestUnknownJobbie", pcValue->ClassName()) == 0;
		if (!bValid)
		{
			AssertTrue(bValid);
			break;
		}

		bExists = cIndexIn.Iterate(&sIter, (uint8*)szKey, &uiKeyLength, 20, &pcValue);
		ui++;
	}
	AssertTrue(bValid);
	AssertSize(12000, ui);

	cIndexIn.Kill();

	DataOrderersKill();
	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//                                                                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void TestIndexUnknown(void)
{
	BeginTests();

	TestIndexUnknownAdd();
	TestIndexUnknownIterate();
	TestIndexUnknownGet();
	TestIndexUnknownLoad();

	TestStatistics();
}

