#include "BaseLib/GlobalMemory.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/Channels.h"
#include "StandardLib/ChannelsAccessorCreator.h"
#include "StandardLib/ExternalObjectSerialiser.h"
#include "StandardLib/MultiFileObjectWriter.h"
#include "StandardLib/ExternalObjectDeserialiser.h"
#include "StandardLib/FileObjectReader.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChannelsStuff(void)
{
	ObjectsInit();

	CChannels					cChannels;
	CChannelsAccessor*			pcAccessor;
	CChannelsAccessor*			pcAccessor2;
	CChannelsAccessor*			pcAccessor3;
	char						c;

	cChannels.Init();

	cChannels.BeginChange();
	cChannels.SetSize(4);
	cChannels.AddChannel(0, PT_uint8);
	cChannels.EndChange();
	AssertInt(4*1, cChannels.GetByteSize());

	pcAccessor = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 0, PT_uint8);
	pcAccessor->Set(0, &(c = 'A'));
	pcAccessor->Set(1, &(c = 'a'));
	pcAccessor->Set(2, &(c = 'A'));
	pcAccessor->Set(3, &(c = 0));
	AssertString("AaA", (char*)cChannels.GetData());
	pcAccessor->Kill();

	cChannels.BeginChange();
	cChannels.AddChannel(1, 2, PT_uint8);
	cChannels.EndChange();
	AssertInt(4*3, cChannels.GetByteSize());

	pcAccessor = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 1, PT_uint8);
	pcAccessor->Set(0, &(c = 'B'));
	pcAccessor->Set(1, &(c = 'b'));
	pcAccessor->Set(2, &(c = 'B'));
	pcAccessor->Set(3, &(c = 'X'));
	pcAccessor->Kill();

	pcAccessor = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 2, PT_uint8);
	pcAccessor->Set(0, &(c = 'C'));
	pcAccessor->Set(1, &(c = 'c'));
	pcAccessor->Set(2, &(c = 'C'));
	pcAccessor->Set(3, &(c = 'Z'));
	pcAccessor->Kill();

	AssertString("ABCabcABC", (char*)cChannels.GetData());

	cChannels.BeginChange();
	cChannels.AddChannel(3, PT_uint8);
	cChannels.EndChange();
	AssertInt(4*4, cChannels.GetByteSize());

	pcAccessor = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 0, PT_uint8);

	pcAccessor->Set(3, &(c = 'V'));
	pcAccessor->Kill();

	pcAccessor = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 3, PT_uint8);
	pcAccessor->Set(0, &(c = 'D'));
	pcAccessor->Set(1, &(c = 'd'));
	pcAccessor->Set(2, &(c = 'D'));
	pcAccessor->Set(3, &(c = (char)0));
	pcAccessor->Kill();

	AssertString("ABCDabcdABCDVXZ", (char*)cChannels.GetData());

	cChannels.Kill();

	char*	pvUserData;

	pvUserData = (char*)malloc(4*3 + 1);
	pvUserData[0] = 'Q'; pvUserData[1] =  'A'; pvUserData[2] =  'Z';
	pvUserData[3] = 'W'; pvUserData[4] =  'S'; pvUserData[5] =  'X';
	pvUserData[6] = 'E'; pvUserData[7] =  'D'; pvUserData[8] =  'C';
	pvUserData[9] = 'R'; pvUserData[10] = 'F'; pvUserData[11] = 'V';
	pvUserData[12] = 0;

	cChannels.Init();
	cChannels.BeginChange();
	cChannels.AddChannel(100, 110, 120, PT_uint8);
	cChannels.SetSize(4);
	cChannels.SetData(pvUserData);
	cChannels.EndChange();

	pcAccessor = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 110, PT_uint8);
	pcAccessor2 = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 120, PT_uint8);
	pcAccessor3 = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 100, PT_uint8);
	AssertNotNull(pcAccessor);
	AssertNotNull(pcAccessor2);
	AssertInt(4, cChannels.GetSize());
	AssertInt(4*3, cChannels.GetByteSize());
	AssertChar('S', *((char*)pcAccessor->Get(1)));
	AssertChar('V', *((char*)pcAccessor2->Get(3)));
	AssertChar('R', *((char*)pcAccessor3->Get(3)));
	pcAccessor->Kill();
	pcAccessor2->Kill();
	pcAccessor3->Kill();

	cChannels.BeginChange();
	cChannels.SetData(NULL);
	cChannels.EndChange();

	cChannels.Kill();
	free(pvUserData);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChannelsLoad(void)
{
	ObjectsInit();

	Ptr<CChannels>				pcChannels;
	CChannelsAccessor*			pcAccessorR;
	CChannelsAccessor*			pcAccessorG;
	CChannelsAccessor*			pcAccessorB;
	int							r;
	int							g;
	int							b;
	int							iCount;
	int							x;
	int							y;
	CExternalObjectSerialiser	cSerialiser;
	CMultiFileObjectWriter		cWriter;
	CFileUtil					cFileUtil;
	CChannels*					pcOld;
	CChannels*					pcNew;
	CChannel*					pcChannel;

	pcChannels = ONMalloc<CChannels>("File");
	pcChannels.GetIndex();

	pcOld = (CChannels*)pcChannels.Object();

	pcChannels->BeginChange();
	pcChannels->SetSize(8 * 32);
	pcChannels->AddChannel(0, PT_uint8);
	pcChannels->AddChannel(1, PT_uint8);
	pcChannels->AddChannel(2, PT_uint8);
	pcChannels->EndChange();
	AssertInt(8 * 32 * 3, pcChannels->GetByteSize());

	pcAccessorR = CChannelsAccessorCreator::CreateSingleChannelAccessor(&pcChannels, 0);
	pcAccessorG = CChannelsAccessorCreator::CreateSingleChannelAccessor(&pcChannels, 1);
	pcAccessorB = CChannelsAccessorCreator::CreateSingleChannelAccessor(&pcChannels, 2);

	x = 0;
	y = 0;
	iCount = 0;
	for (r = 0; r < 8; r++)
	{
		for (g = 0; g < 8; g++)
		{
			for (b = 0; b < 4; b++)
			{
				pcAccessorR->Set(x + y * 8, &r);
				pcAccessorG->Set(x + y * 8, &g);
				pcAccessorB->Set(x + y * 8, &b);

				x++;
				if (x >= 8)
				{
					x = 0;
					y++;
				}

				iCount++;
			}
		}
	}

	AssertInt(256, iCount);

	pcAccessorR->Kill();
	pcAccessorG->Kill();
	pcAccessorB->Kill();

	AssertTrue(cFileUtil.RemoveDir("Output" _FS_ "Channels"));
	AssertTrue(cFileUtil.TouchDir("Output" _FS_ "Channels"));

	cWriter.Init("Output" _FS_ "Channels" _FS_, "");
	cSerialiser.Init(&cWriter);
	AssertTrue(cSerialiser.Write(&pcChannels));
	cSerialiser.Kill();
	cWriter.Kill();

	ObjectsFlush();
	ObjectsKill();

	ObjectsInit();

	gcObjects.AddConstructor<CChannels>();

	CFileObjectReader				cReader;
	CExternalObjectDeserialiser		cDeserialiser;
	CFileBasic						cFileBasic;
	CDiskFile*						pcDiskFile;
	uint8							ar;
	uint8							ag;
	uint8							ab;

	pcDiskFile = DiskFile("Output" _FS_ "Channels" _FS_ "File.DRG");
	cFileBasic.Init(pcDiskFile);

	cReader.Init(&cFileBasic);
	cDeserialiser.Init(&cReader, false, &gcObjects, gcObjects.GetMemory());
	pcChannels = cDeserialiser.Read("File");
	cDeserialiser.Kill();
	cReader.Kill();

	pcNew = (CChannels*)pcChannels.Object();
	AssertFalse(pcOld == pcNew);
	
	AssertSize(8 * 32 * 3, pcChannels->GetByteSize());
	AssertSize(3, pcChannels->GetByteStride());
	AssertSize(3 * 8, pcChannels->GetBitStride());
	AssertSize(3, pcChannels->GetNumChannels());

	pcChannel = pcChannels->GetChannel(0);
	AssertSize(1, pcChannel->miByteSize);
	AssertSize(0, pcChannel->miByteOffset);
	AssertSize(8, pcChannel->miBitSize);
	AssertSize(0, pcChannel->miBitOffset);
	AssertSize(PT_uint8, pcChannel->eType);
	AssertSize(0, pcChannel->iChannel);
	AssertBool(false, pcChannel->bReverse);

	pcChannel = pcChannels->GetChannel(1);
	AssertSize(1, pcChannel->miByteSize);
	AssertSize(1, pcChannel->miByteOffset);
	AssertSize(8, pcChannel->miBitSize);
	AssertSize(8, pcChannel->miBitOffset);
	AssertSize(PT_uint8, pcChannel->eType);
	AssertSize(1, pcChannel->iChannel);
	AssertBool(false, pcChannel->bReverse);

	pcChannel = pcChannels->GetChannel(2);
	AssertSize(1, pcChannel->miByteSize);
	AssertSize(2, pcChannel->miByteOffset);
	AssertSize(8, pcChannel->miBitSize);
	AssertSize(16, pcChannel->miBitOffset);
	AssertSize(PT_uint8, pcChannel->eType);
	AssertSize(2, pcChannel->iChannel);
	AssertBool(false, pcChannel->bReverse);

	AssertBool(true, pcChannels->IsOnlyBasicTypes());

	pcAccessorR = CChannelsAccessorCreator::CreateSingleChannelAccessor(&pcChannels, 0);
	pcAccessorG = CChannelsAccessorCreator::CreateSingleChannelAccessor(&pcChannels, 1);
	pcAccessorB = CChannelsAccessorCreator::CreateSingleChannelAccessor(&pcChannels, 2);

	iCount = 0;

	x = 0;
	y = 0;
	iCount = 0;
	for (r = 0; r < 8; r++)
	{
		for (g = 0; g < 8; g++)
		{
			for (b = 0; b < 4; b++)
			{
				ar = *((uint8*)pcAccessorR->Get(x + y * 8));
				ag = *((uint8*)pcAccessorG->Get(x + y * 8));
				ab = *((uint8*)pcAccessorB->Get(x + y * 8));

				if ((ar != (uint8)r) ||
					(ag != (uint8)g) ||
					(ab != (uint8)b))
				{
					AssertChar(r, (uint8)ar);
					AssertChar(g, (uint8)ag);
					AssertChar(b, (uint8)ab);
				}

				x++;
				if (x >= 8)
				{
					x = 0;
					y++;
				}

				iCount++;
			}
		}
	}
	AssertInt(256, iCount);

	pcAccessorR->Kill();
	pcAccessorG->Kill();
	pcAccessorB->Kill();

	pcChannels = NULL;

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChannels(void)
{
	BeginTests();
	MemoryInit();
	TypesInit();
	TypeConverterInit();
	DataIOInit();

	TestChannelsStuff();
	TestChannelsLoad();

	DataIOKill();
	TypeConverterKill();
	TypesKill();
	MemoryKill();
	TestStatistics();
}

