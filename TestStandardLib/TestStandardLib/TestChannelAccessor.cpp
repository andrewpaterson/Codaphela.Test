#include "CoreLib/TypeConverter.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/Channels.h"
#include "StandardLib/ChannelsAccessor.h"
#include "StandardLib/ChannelsAccessorCreator.h"
#include "TestLib/Assert.h"

#define CHANNEL_NAME_JACK	101
#define CHANNEL_NAME_BOB	7
#define CHANNEL_NAME_ALICE	3


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChannelsAccessorContiguous(void)
{
	CChannels*					pcChannels;
	CChannelsAccessor*			pcAccessor;
	CChannelsAccessorCreator	cCreator;
	void*						pvData;
	int							iData;
	short						sData;

	pcChannels = UMalloc(CChannels);
	pcChannels->Init();
	pcChannels->BeginChange();
	pcChannels->SetSize(2);
	pcChannels->AddChannel(CHANNEL_NAME_BOB, PT_int);
	pcChannels->EndChange();

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_BOB, PT_Undefined);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorContiguous", pcAccessor->ClassName());
	pvData = pcAccessor->Get(0);
	AssertPointer(pcChannels->GetData(), pvData);
	iData = 784;
	pcAccessor->Set(1, &iData);
	pvData = pcAccessor->Get(1);
	AssertInt(784, *(int*)pvData);
	pcAccessor->Kill();

	pcChannels->BeginChange();
	pcChannels->AddChannel(CHANNEL_NAME_ALICE, PT_short);
	pcChannels->EndChange();

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_BOB, PT_Undefined);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorContiguous", pcAccessor->ClassName());
	pvData = pcAccessor->Get(1);
	AssertInt(784, *(int*)pvData);
	pcAccessor->Kill();

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_ALICE, PT_Undefined);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorContiguous", pcAccessor->ClassName());
	pvData = pcAccessor->Get(0);
	AssertPointer(RemapSinglePointer(pcChannels->GetData(), 4), pvData);
	sData = 602;
	pcAccessor->Set(1, &sData);
	pvData = pcAccessor->Get(1);
	AssertShort(602, *(short*)pvData);
	pcAccessor->Kill();

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_BOB, CHANNEL_NAME_ALICE, PT_Undefined);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorContiguous", pcAccessor->ClassName());
	AssertInt(6, pcAccessor->GetByteSize());
	pvData = pcAccessor->Get(1);
	AssertInt(784, *(int*)pvData);
	pvData = RemapSinglePointer(pvData, 4);
	AssertInt(602, *(short*)pvData);
	pcAccessor->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChannelsAccessorByteAligned(void)
{
	CChannels*					pcChannels;
	CChannelsAccessor*			pcAccessor;
	CChannelsAccessorCreator	cCreator;
	short*						psData;
	short						sData[3];
	int							iData;

	pcChannels = UMalloc(CChannels);
	pcChannels->Init();
	pcChannels->BeginChange();
	pcChannels->SetSize(2);
	pcChannels->AddChannel(CHANNEL_NAME_JACK, PT_short);
	pcChannels->AddChannel(CHANNEL_NAME_BOB, PT_int);
	pcChannels->AddChannel(CHANNEL_NAME_ALICE, PT_short);
	pcChannels->EndChange();

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_JACK, PT_Undefined);
	cCreator.AddAccess(CHANNEL_NAME_ALICE, PT_Undefined);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorByteAligned", pcAccessor->ClassName());
	sData[0] = 784;
	sData[1] = 602;
	pcAccessor->Set(1, &sData);
	AssertShort(784, *(short*)RemapSinglePointer(pcChannels->GetData(), 8 + 0));
	AssertShort(602, *(short*)RemapSinglePointer(pcChannels->GetData(), 8 + 6));
	psData = (short*)pcAccessor->Get(1);
	AssertShort(784, psData[0]);
	AssertShort(602, psData[1]);
	pcAccessor->Kill();

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_BOB, PT_Undefined);
	pcAccessor = cCreator.CreateAndKill();
	iData = 999999;
	pcAccessor->Set(1, &iData);
	pcAccessor->Kill();

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_ALICE, PT_Undefined);
	cCreator.AddAccess(CHANNEL_NAME_BOB, PT_Undefined);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorByteAligned", pcAccessor->ClassName());
	psData = (short*)pcAccessor->Get(1);
	AssertShort(602, psData[0]);
	AssertInt(999999, *(int*)&psData[1]);
	sData[0] = 22172;
	sData[1] = 18432;
	sData[2] = 30812;
	pcAccessor->Set(0, sData);
	AssertInt(2019313664, *(int*)RemapSinglePointer(pcChannels->GetData(), 2));
	AssertShort(22172, *(short*)RemapSinglePointer(pcChannels->GetData(), 6));
	pcAccessor->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChannelsAccessorTypeConvert(void)
{
	CChannels*					pcChannels;
	CChannelsAccessor*			pcAccessor;
	CChannelsAccessorCreator	cCreator;
	float*						pfData;
	float						afData[3];

	pcChannels = UMalloc(CChannels);
	pcChannels->Init();
	pcChannels->BeginChange();
	pcChannels->SetSize(2);
	pcChannels->AddChannel(CHANNEL_NAME_JACK, PT_ushort);
	pcChannels->AddChannel(CHANNEL_NAME_BOB, PT_uint);
	pcChannels->AddChannel(CHANNEL_NAME_ALICE, PT_ushort);
	pcChannels->EndChange();
	pcChannels->Clear();

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_JACK, PT_float);
	cCreator.AddAccess(CHANNEL_NAME_ALICE, PT_float);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorTypeConvert", pcAccessor->ClassName());
	afData[0] = 1.0f;
	afData[1] = 0.34f;
	pcAccessor->Set(1, afData);
	AssertShortHex((short)0xffff, *(unsigned short*)RemapSinglePointer(pcChannels->GetData(), 8 + 0));
	AssertShortHex(0x5709, *(unsigned short*)RemapSinglePointer(pcChannels->GetData(), 8 + 6));
	pfData = (float*)pcAccessor->Get(1);
	AssertFloat(1.0f, pfData[0], 2);
	AssertFloat(0.34f, pfData[1], 2);
	pcAccessor->Kill();

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_BOB, PT_float);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorTypeConvert", pcAccessor->ClassName());
	afData[0] = 0.8f;
	pcAccessor->Set(1, afData);
	AssertIntHex(0xcccccd00, *(int*)RemapSinglePointer(pcChannels->GetData(), 8 + 2));
	pcAccessor->Kill();

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_ALICE, PT_float);
	cCreator.AddAccess(CHANNEL_NAME_BOB, PT_float);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorTypeConvert", pcAccessor->ClassName());
	pfData = (float*)pcAccessor->Get(1);
	AssertFloat(0.34f, pfData[0], 2);
	AssertFloat(0.80f, pfData[1], 2);
	pcAccessor->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChannelsAccessorChannelBitty(void)
{
	CChannels*					pcChannels;
	CChannelsAccessor*			pcAccessor;
	CChannelsAccessorCreator	cCreator;
	unsigned char*				pucData;
	unsigned char				aucData[3];
	float*						pfData;

	pcChannels = UMalloc(CChannels);
	pcChannels->Init();
	pcChannels->BeginChange();
	pcChannels->SetSize(1);
	pcChannels->AddChannel(CHANNEL_NAME_JACK, PT_bit);
	pcChannels->AddChannel(CHANNEL_NAME_BOB, PT_crumb);
	pcChannels->AddChannel(CHANNEL_NAME_ALICE, PT_bit);
	pcChannels->EndChange();
	pcChannels->Clear();
	AssertInt(1, pcChannels->GetByteSize());
	AssertInt(1, pcChannels->GetSize());

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_JACK, PT_uchar);
	cCreator.AddAccess(CHANNEL_NAME_BOB, PT_uchar);
	cCreator.AddAccess(CHANNEL_NAME_ALICE, PT_uchar);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorChannelBitty", pcAccessor->ClassName());
	aucData[0] = 0xff;
	aucData[1] = 0x55;
	aucData[2] = 0xff;
	pcAccessor->Set(0, aucData);
	AssertChar(0xb, *pcChannels->GetData());  //Or maybe 0xd.  I'm not sure of the ordering
	pucData = (unsigned char*)pcAccessor->Get(0);
	AssertChar((char)0xff, pucData[0]);
	AssertChar((char)0x55, pucData[1]);
	AssertChar((char)0xff, pucData[2]);
	pcAccessor->Kill();

	pcChannels->BeginChange();
	pcChannels->SetSize(2);
	pcChannels->EndChange();
	AssertInt(1, pcChannels->GetByteSize());
	AssertInt(2, pcChannels->GetSize());

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_JACK, PT_uchar);
	cCreator.AddAccess(CHANNEL_NAME_BOB, PT_uchar);
	cCreator.AddAccess(CHANNEL_NAME_ALICE, PT_uchar);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorChannelBitty", pcAccessor->ClassName());
	pucData = (unsigned char*)pcAccessor->Get(0);
	AssertChar((char)0xff, pucData[0]);
	AssertChar((char)0x55, pucData[1]);
	AssertChar((char)0xff, pucData[2]);

	aucData[0] = 0x00;
	aucData[1] = 0xaa;
	aucData[2] = 0xff;
	pcAccessor->Set(1, aucData);
	AssertChar(0xc, ((unsigned char)*pcChannels->GetData()) >> 4);  //Or maybe 0xd.  I'm not sure of the ordering
	pucData = (unsigned char*)pcAccessor->Get(1);
	AssertChar((char)0x00, pucData[0]);
	AssertChar((char)0xaa, pucData[1]);
	AssertChar((char)0xff, pucData[2]);
	pcAccessor->Kill();

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_ALICE, PT_float);
	cCreator.AddAccess(CHANNEL_NAME_BOB, PT_float);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorChannelBitty", pcAccessor->ClassName());
	pfData = (float*)pcAccessor->Get(0);
	AssertFloat(1.0f, pfData[0], 2);
	AssertFloat(0.33f, pfData[1], 2);
	pfData = (float*)pcAccessor->Get(1);
	AssertFloat(1.0f, pfData[0], 2);
	AssertFloat(0.67f, pfData[1], 2);
	pcAccessor->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChannelsAccessorAccessBitty(void)
{
	CChannels*					pcChannels;
	CChannelsAccessor*			pcAccessor;
	CChannelsAccessorCreator	cCreator;
	unsigned char*				pucData;
	unsigned char				aucData[2];

	pcChannels = UMalloc(CChannels);
	pcChannels->Init();
	pcChannels->BeginChange();
	pcChannels->SetSize(1);
	pcChannels->AddChannel(CHANNEL_NAME_JACK, PT_ushort);
	pcChannels->AddChannel(CHANNEL_NAME_BOB, PT_ushort);
	pcChannels->AddChannel(CHANNEL_NAME_ALICE, PT_ushort);
	pcChannels->EndChange();
	pcChannels->Clear();

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_JACK, PT_sixbits);
	cCreator.AddAccess(CHANNEL_NAME_BOB, PT_sixbits);
	cCreator.AddAccess(CHANNEL_NAME_ALICE, PT_nybble);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorAccessBitty", pcAccessor->ClassName());

	//XX10110010100011
	aucData[0] = 0xa3;
	aucData[1] = 0x2c;
	pcAccessor->Set(0, aucData);
	AssertShortHex((unsigned short)0x8e38, *(unsigned short*)RemapSinglePointer(pcChannels->GetData(), 0 + 0));
	AssertShortHex((unsigned short)0xcb2b, *(unsigned short*)RemapSinglePointer(pcChannels->GetData(), 0 + 2));
	AssertShortHex((unsigned short)0x2222, *(unsigned short*)RemapSinglePointer(pcChannels->GetData(), 0 + 4));
	pucData = (unsigned char*)pcAccessor->Get(0);
	AssertShortHex((unsigned short)0x2ca3, *(unsigned short*)pucData);
	pcAccessor->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChannelsAccessorWorstCase(void)
{
	CChannels*					pcChannels;
	CChannelsAccessor*			pcAccessor;
	CChannelsAccessorCreator	cCreator;
	unsigned char*				pucData;
	unsigned char				aucData[5];


	pcChannels = UMalloc(CChannels);
	pcChannels->Init();
	pcChannels->BeginChange();
	pcChannels->SetSize(2);
	pcChannels->AddChannel(CHANNEL_NAME_JACK, PT_bit);
	pcChannels->AddChannel(CHANNEL_NAME_BOB, PT_uint);
	pcChannels->AddChannel(CHANNEL_NAME_ALICE, PT_uchar);
	pcChannels->EndChange();
	pcChannels->Clear();
	AssertInt(2, pcChannels->GetSize());
	AssertInt(11, pcChannels->GetByteSize());
	AssertInt(41, pcChannels->GetBitStride());
	AssertInt(-1, pcChannels->GetByteStride());
	AssertInt(FALSE, pcChannels->IsOnlyBasicTypes());

	memset(aucData, 0, 5);

	cCreator.Init(pcChannels);
	cCreator.AddAccess(CHANNEL_NAME_JACK, PT_uint);
	cCreator.AddAccess(CHANNEL_NAME_BOB, PT_bit);
	cCreator.AddAccess(CHANNEL_NAME_ALICE, PT_nybble);
	pcAccessor = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorWorstCase", pcAccessor->ClassName());
	AssertInt(-1, pcAccessor->GetByteSize());
	AssertInt(37, pcAccessor->GetBitSize());
	AssertInt(5, pcAccessor->GetBufferSize());
	aucData[0] = 0xff;
	aucData[1] = 0xff;
	aucData[2] = 0xff;
	aucData[3] = 0xff;
	aucData[4] = 0xff;
	pcAccessor->Set(0, aucData);
	AssertChar((unsigned char)0xff, pcChannels->GetData()[0]);
	AssertChar((unsigned char)0xff, pcChannels->GetData()[1]);
	AssertChar((unsigned char)0xff, pcChannels->GetData()[2]);
	AssertChar((unsigned char)0xff, pcChannels->GetData()[3]);
	AssertChar((unsigned char)0xff, pcChannels->GetData()[4]);
	AssertChar((unsigned char)0x01, pcChannels->GetData()[5]);  //01 because the next 'pixel' is all zeros.  The 1 is the high bit of the char in ALICE.
	pucData = (unsigned char*)pcAccessor->Get(0);
	AssertChar((unsigned char)0xff, pucData[0]);
	AssertChar((unsigned char)0xff, pucData[1]);
	AssertChar((unsigned char)0xff, pucData[2]);
	AssertChar((unsigned char)0xff, pucData[3]);
	AssertChar((unsigned char)0x1f, pucData[4]);

	aucData[0] = 0xff;
	aucData[1] = 0xff;
	aucData[2] = 0xff;
	aucData[3] = 0xff;
	aucData[4] = 0xfe;
	pcAccessor->Set(1, aucData);
	AssertChar((unsigned char)0x03, pcChannels->GetData()[5]); //01 from 'pixel' 0 and 02 from the bit in JACK in 'pixel' 1.
	AssertChar((unsigned char)0x00, pcChannels->GetData()[6]);
	AssertChar((unsigned char)0x00, pcChannels->GetData()[7]);
	AssertChar((unsigned char)0x00, pcChannels->GetData()[8]);
	AssertChar((unsigned char)0xfc, pcChannels->GetData()[9]);  //fc it the six low bits of the char
	AssertChar((unsigned char)0x03, pcChannels->GetData()[10] & 0x03);  //03 is the two high bits.
	pucData = (unsigned char*)pcAccessor->Get(1);
	AssertChar((unsigned char)0xff, pucData[0]);
	AssertChar((unsigned char)0xff, pucData[1]);
	AssertChar((unsigned char)0xff, pucData[2]);
	AssertChar((unsigned char)0xff, pucData[3]);
	AssertChar((unsigned char)0x1e, pucData[4]);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChannelsAccessor(void)
{
	BeginTests();
	ClassStorageInit();
	TypeConverterInit();
	UnknownsInit();

	TestChannelsAccessorContiguous();
	TestChannelsAccessorByteAligned();
	TestChannelsAccessorTypeConvert();
	TestChannelsAccessorChannelBitty();
	TestChannelsAccessorAccessBitty();
	TestChannelsAccessorWorstCase();

	UnknownsKill();
	TypeConverterKill();
	ClassStorageKill();
	TestStatistics();
}

