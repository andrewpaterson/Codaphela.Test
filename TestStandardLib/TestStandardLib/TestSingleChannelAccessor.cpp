#include "BaseLib/GlobalMemory.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/Channels.h"
#include "StandardLib/SingleChannelAccessor.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSingleChannelAccessor(void)
{
	BeginTests();

	MemoryInit();
	TypesInit();
	TypeConverterInit();
	UnknownsInit();

	
	CChannels					cChannels;
	unsigned char				cData[9] = "ti@YA,\n#";
	CSingleChannelAccessor		cSingle;
	char						c;
	unsigned					s;

	cChannels.Init();
	cChannels.BeginChange();
	cChannels.SetData(cData);
	cChannels.AddChannel(16, 15, 14, 13, PT_nybble);
	cChannels.AddChannel(12, 11, PT_uchar);
	cChannels.AddChannel(10, PT_ushort);
	cChannels.AddChannel(9, 8, 7, 6, PT_bit);
	cChannels.AddChannel(5, 4, PT_crumb);
	cChannels.AddChannel(3, PT_uchar);
	cChannels.SetSize(1);
	cChannels.EndChange();
	cSingle.Init(&cChannels);
	AssertFloat(0.27f, cSingle.GetConvertToFloat(16), 2);
	AssertFloat(0.47f, cSingle.GetConvertToFloat(15), 2);
	AssertFloat(0.60f, cSingle.GetConvertToFloat(14), 2);
	AssertFloat(0.40f, cSingle.GetConvertToFloat(13), 2);
	cSingle.GetNative(16, &c); AssertChar(4, c);
	cSingle.GetNative(15, &c); AssertChar(7, c);
	cSingle.GetNative(14, &c); AssertChar(9, c);
	cSingle.GetNative(13, &c); AssertChar(6, c);

	AssertFloat(0.25f, cSingle.GetConvertToFloat(12), 2);
	AssertFloat(0.35f, cSingle.GetConvertToFloat(11), 2);
	cSingle.GetNative(12, &c); AssertChar('@', c);
	cSingle.GetNative(11, &c); AssertChar('Y', c);

	cSingle.GetNative(10, &s); AssertShortHex(0x2c41, s);

	AssertFloat(0.0f, cSingle.GetConvertToFloat(9), 1);
	AssertFloat(1.0f, cSingle.GetConvertToFloat(8), 1);
	AssertFloat(0.0f, cSingle.GetConvertToFloat(7), 1);
	AssertFloat(1.0f, cSingle.GetConvertToFloat(6), 1);

	AssertFloat(0.14f, cSingle.GetConvertToFloat(3), 2);
	cSingle.GetNative(3, &c); AssertChar('#', c);

	cChannels.Kill();


	UnknownsKill();
	TypeConverterKill();
	TypesKill();
	MemoryKill();

	TestStatistics();
}

