#include "CoreLib/TypeConverter.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/Channels.h"
#include "StandardLib/ChannelsAccessorCreator.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChannelsStuff(void)
{
	CChannels					cChannels;
	CChannelsAccessor*			pcAccessor;
	CChannelsAccessor*			pcAccessor2;
	CChannelsAccessor*			pcAccessor3;
	char						c;

	cChannels.Init();

	cChannels.BeginChange();
	cChannels.SetSize(4);
	cChannels.AddChannel(0, PT_uchar);
	cChannels.EndChange();
	AssertInt(4*1, cChannels.GetByteSize());

	pcAccessor = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 0, PT_uchar);
	pcAccessor->Set(0, &(c = 'A'));
	pcAccessor->Set(1, &(c = 'a'));
	pcAccessor->Set(2, &(c = 'A'));
	pcAccessor->Set(3, &(c = 0));
	AssertString("AaA", (char*)cChannels.GetData());
	pcAccessor->Kill();

	cChannels.BeginChange();
	cChannels.AddChannel(1, 2, PT_uchar);
	cChannels.EndChange();
	AssertInt(4*3, cChannels.GetByteSize());

	pcAccessor = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 1, PT_uchar);
	pcAccessor->Set(0, &(c = 'B'));
	pcAccessor->Set(1, &(c = 'b'));
	pcAccessor->Set(2, &(c = 'B'));
	pcAccessor->Set(3, &(c = 'X'));
	pcAccessor->Kill();

	pcAccessor = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 2, PT_uchar);
	pcAccessor->Set(0, &(c = 'C'));
	pcAccessor->Set(1, &(c = 'c'));
	pcAccessor->Set(2, &(c = 'C'));
	pcAccessor->Set(3, &(c = 'Z'));
	pcAccessor->Kill();

	AssertString("ABCabcABC", (char*)cChannels.GetData());

	cChannels.BeginChange();
	cChannels.AddChannel(3, PT_uchar);
	cChannels.EndChange();
	AssertInt(4*4, cChannels.GetByteSize());

	pcAccessor = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 0, PT_uchar);

	pcAccessor->Set(3, &(c = 'V'));
	pcAccessor->Kill();

	pcAccessor = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 3, PT_uchar);
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
	cChannels.AddChannel(100, 110, 120, PT_uchar);
	cChannels.SetSize(4);
	cChannels.SetData(pvUserData);
	cChannels.EndChange();

	pcAccessor = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 110, PT_uchar);
	pcAccessor2 = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 120, PT_uchar);
	pcAccessor3 = CChannelsAccessorCreator::CreateSingleChannelAccessor(&cChannels, 100, PT_uchar);
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
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChannels(void)
{
	BeginTests();
	ClassStorageInit();
	TypeConverterInit();
	UnknownsInit();

	TestChannelsStuff();

	UnknownsKill();
	TypeConverterKill();
	ClassStorageKill();
	TestStatistics();
}

