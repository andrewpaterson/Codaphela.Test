#include "BaseLib/FastFunctions.h"
#include "BaseLib/Log.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/ChannelPadder.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestOptimalPadding(void)
{
	CChannels		cChannels;
	CChannelPadder	cPadder;
	CChannel*		cChannel;

	TypesInit();

	cChannels.Init();
	cChannels.BeginChange();
	cChannels.AddChannel(0, PT_char);
	cChannels.AddChannel(1, PT_int);
	cChannels.AddChannel(2, PT_long);
	cChannels.EndChange();

	cPadder.Init(&cChannels);
	cPadder.OptimalPadding();

	cChannel = cChannels.GetChannelAtIndex(0);
	AssertInt(0, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(1);
	AssertInt(4, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(2);
	AssertInt(8, cChannel->miByteOffset);
	AssertInt(16, cChannels.GetByteStride());

	cChannels.Kill();

	cChannels.Init();
	cChannels.BeginChange();
	cChannels.AddChannel(0, PT_long);
	cChannels.AddChannel(1, PT_int);
	cChannels.AddChannel(2, PT_char);
	cChannels.EndChange();

	cPadder.Init(&cChannels);
	cPadder.OptimalPadding();

	cChannel = cChannels.GetChannelAtIndex(0);
	AssertInt(0, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(1);
	AssertInt(8, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(2);
	AssertInt(12, cChannel->miByteOffset);
	AssertInt(16, cChannels.GetByteStride());

	cChannels.Kill();

	cChannels.Init();
	cChannels.BeginChange();
	cChannels.AddChannel(0, PT_char);
	cChannels.AddChannel(1, PT_char);
	cChannels.AddChannel(2, PT_char);
	cChannels.AddChannel(3, PT_char);
								   
	cChannels.AddChannel(4, PT_char);
	cChannels.AddChannel(5, PT_char);
	cChannels.AddChannel(6, PT_char);
	cChannels.AddChannel(7, PT_char);

	cChannels.AddChannel(8, PT_long);
	cChannels.EndChange();

	cPadder.Init(&cChannels);
	cPadder.OptimalPadding();

	cChannel = cChannels.GetChannelAtIndex(0);
	AssertInt(0, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(1);
	AssertInt(1, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(2);
	AssertInt(2, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(3);
	AssertInt(3, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(4);
	AssertInt(4, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(5);
	AssertInt(5, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(6);
	AssertInt(6, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(7);
	AssertInt(7, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(8);
	AssertInt(8, cChannel->miByteOffset);
	AssertInt(16, cChannels.GetByteStride());

	cChannels.Kill();

	cChannels.Init();
	cChannels.BeginChange();
	cChannels.AddChannel(0, PT_char);
	cChannels.AddChannel(1, PT_long);
	cChannels.AddChannel(2, PT_char);
	cChannels.AddChannel(3, PT_long);
	cChannels.EndChange();

	cPadder.Init(&cChannels);
	cPadder.OptimalPadding();

	cChannel = cChannels.GetChannelAtIndex(0);
	AssertInt(0, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(1);
	AssertInt(8, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(2);
	AssertInt(16, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(3);
	AssertInt(24, cChannel->miByteOffset);
	AssertInt(32, cChannels.GetByteStride());

	cChannels.Kill();

	cChannels.Init();
	cChannels.BeginChange();
	cChannels.AddChannel(0, PT_char);
	cChannels.AddChannel(1, PT_short);
	cChannels.AddChannel(2, PT_char);
	cChannels.AddChannel(3, PT_short);
	cChannels.AddChannel(4, PT_long);
	cChannels.AddChannel(5, PT_short);
	cChannels.AddChannel(6, PT_char);
	cChannels.AddChannel(7, PT_int);
	cChannels.AddChannel(8, PT_long);
	cChannels.EndChange();

	cPadder.Init(&cChannels);
	cPadder.OptimalPadding();

	cChannel = cChannels.GetChannelAtIndex(0);
	AssertInt(0, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(1);
	AssertInt(2, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(2);
	AssertInt(4, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(3);
	AssertInt(6, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(4);
	AssertInt(8, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(5);
	AssertInt(16, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(6);
	AssertInt(18, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(7);
	AssertInt(20, cChannel->miByteOffset);
	cChannel = cChannels.GetChannelAtIndex(8);
	AssertInt(24, cChannel->miByteOffset);
	AssertInt(32, cChannels.GetByteStride());

	cChannels.Kill();

	TypesKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestExternalChannelPadder(void)
{
	BeginTests();

	TestOptimalPadding();

	TestStatistics();
}

