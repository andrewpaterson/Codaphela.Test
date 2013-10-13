#include "BaseLib/FastFunctions.h"
#include "BaseLib/Log.h"
#include "CoreLib/TypeConverter.h"
#include "StandardLib/Channels.h"
#include "StandardLib/ChannelsAccessorCreator.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/ChannelsCopier.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestExternalChannelsSubBytePositions(void)
{
	CChannelsAccessor*			pcChannel0;
	CChannelsAccessor*			pcChannel1;
	CChannelsAccessorCreator	cCreator;
	CChannels					cSourceChannels;
	unsigned char				uc[11] = {0x29, 0x33, 0xBE, 0x84, 0xE1, 0x6C, 0xD6, 0xAE, 0x52, 0xE8, 0x01};
	unsigned char*				pucData;
//   MSb                                                                                           LSb
// X 1 11101000 0 10100101 0 10111011 0 10110011 0 11001110 0 00110000 1 00101111 1 00011001 1 00101001
// ^         ^          ^          ^          ^          ^          ^          ^          ^          ^
// 8 8 77777777 7 76666666 6 66555555 5 55544444 4 44443333 3 33333222 2 22222211 1 11111110 0 00000000
// 1 0 98765432 1 09876543 2 10987654 3 21098765 4 32109876 5 43210987 6 54321098 7 65432109 8 76543210

	TypeConverterInit();
	ClassStorageInit();
	UnknownsInit();

	cSourceChannels.Init();
	cSourceChannels.BeginChange();
	cSourceChannels.AddChannel(0, PT_uchar);
	cSourceChannels.AddChannel(1, PT_bit);
	cSourceChannels.SetData((char*)uc);
	cSourceChannels.SetSize(9);
	cSourceChannels.EndChange();

	cCreator.Init(&cSourceChannels);
	cCreator.AddAccess(0, PT_uchar);
	pcChannel0 = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorChannelBitty", pcChannel0->ClassName());

	cCreator.Init(&cSourceChannels);
	cCreator.AddAccess(1, PT_uchar);
	pcChannel1 = cCreator.CreateAndKill();
	AssertString("CChannelsAccessorChannelBitty", pcChannel1->ClassName());

	pucData = (unsigned char*)pcChannel0->Get(0);
	AssertInt(0x29, *pucData);

	
	pucData = (unsigned char*)pcChannel1->Get(0);
	AssertInt(0xFF, *pucData);  //LSb of the right hand 3 in 0x33 scaled up to a byte from a bit.

	pucData = (unsigned char*)pcChannel0->Get(1);
	AssertInt(0x19, *pucData);
	pucData = (unsigned char*)pcChannel1->Get(1);
	AssertInt(0xFF, *pucData);

	pucData = (unsigned char*)pcChannel0->Get(2);
	AssertInt(0x2F, *pucData);
	pucData = (unsigned char*)pcChannel1->Get(2);
	AssertInt(0xFF, *pucData);

	pucData = (unsigned char*)pcChannel0->Get(3);
	AssertInt(0x30, *pucData);
	
	pucData = (unsigned char*)pcChannel1->Get(3);
	AssertInt(0x00, *pucData);

	pucData = (unsigned char*)pcChannel0->Get(4);
	AssertInt(0xCE, *pucData);
	pucData = (unsigned char*)pcChannel1->Get(4);
	AssertInt(0x00, *pucData);

	pucData = (unsigned char*)pcChannel0->Get(5);
	AssertInt(0xB3, *pucData);
	pucData = (unsigned char*)pcChannel1->Get(5);
	AssertInt(0x00, *pucData);

	pucData = (unsigned char*)pcChannel0->Get(6);
	AssertInt(0xBB, *pucData);
	pucData = (unsigned char*)pcChannel1->Get(6);
	AssertInt(0x00, *pucData);

	pucData = (unsigned char*)pcChannel0->Get(7);
	AssertInt(0xA5, *pucData);
	pucData = (unsigned char*)pcChannel1->Get(7);
	AssertInt(0x00, *pucData);

	pucData = (unsigned char*)pcChannel0->Get(8);
	AssertInt(0xE8, *pucData);
	pucData = (unsigned char*)pcChannel1->Get(8);
	AssertInt(0xFF, *pucData);

	cSourceChannels.Kill();

	UnknownsKill();
	ClassStorageKill();
	TypeConverterKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestContiguousExternalChannels(void)
{
	CChannels			cChannels;
	CChannels			cExternalChannel;
	int					vSourse;
	int					iExpected0;
	int					iExpected1;
	int					iExpected2;
	int					iExpected3;

	TypeConverterInit();
	ClassStorageInit();
	UnknownsInit();

	//Rows      3 2 1 0
	vSourse = 0xFF00aa55;

	cExternalChannel.Init();
	cExternalChannel.BeginChange();
	cExternalChannel.AddChannel(3, PT_nybble);
	cExternalChannel.AddChannel(2, PT_bit);
	cExternalChannel.AddChannel(1, PT_bit);
	cExternalChannel.AddChannel(0, PT_crumb);
	cExternalChannel.SetData((char*)&vSourse);
	cExternalChannel.SetSize(4);
	cExternalChannel.EndChange();
	AssertInt(4, cExternalChannel.GetSize());

	cChannels.Init();
	cChannels.BeginChange();
	cChannels.AddChannel(3, PT_uchar);
	cChannels.AddChannel(2, PT_uchar);
	cChannels.AddChannel(1, PT_uchar);
	cChannels.AddChannel(0, PT_uchar);
	cChannels.SetSize(4);
	cChannels.EndChange();
	AssertInt(4, cChannels.GetSize());

	CChannelsCopier cCopy;

	cCopy.Init(&cExternalChannel, &cChannels);

	cCopy.Copy(0, 0, 4);

	iExpected0 = 0x5500ff55;
	iExpected1 = 0xaaff00aa;
	iExpected2 = 0x00000000;
	iExpected3 = 0xFFffffff;
	AssertPointer((void*)(size_t)iExpected0, (void*)(size_t)((int*)cChannels.GetData())[0]);
	AssertPointer((void*)(size_t)iExpected1, (void*)(size_t)((int*)cChannels.GetData())[1]);
	AssertPointer((void*)(size_t)iExpected2, (void*)(size_t)((int*)cChannels.GetData())[2]);
	AssertPointer((void*)(size_t)iExpected3, (void*)(size_t)((int*)cChannels.GetData())[3]);

	cCopy.Kill();
	cChannels.Kill();
	cExternalChannel.Kill();

	UnknownsKill();
	ClassStorageKill();
	TypeConverterKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestExternalChannels(void)
{
	BeginTests();

	TestExternalChannelsSubBytePositions();
	TestContiguousExternalChannels();

	TestStatistics();
}

