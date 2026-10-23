#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/Logger.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Sound.h"
#include "SupportLib/ImageChannel.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSoundInit(void)
{
	CChannel*	pcChannel;

	Ptr<CSound> pcSound = OMalloc<CSound>(44100, 100, PT_int16, SOUND_LEFT, SOUND_RIGHT, CHANNEL_STOP);
	AssertSize(2, pcSound->NumChannels());
	AssertSize(100, pcSound->GetNumFrames());
	AssertInt(44100, pcSound->GetSampleRate());
	AssertSize(4, pcSound->GetFrameByteStride());
	AssertSize(400, pcSound->GetByteSize());
	AssertTrue(pcSound->HasChannels(SOUND_LEFT, SOUND_RIGHT, CHANNEL_STOP));
	AssertFalse(pcSound->HasChannel(SOUND_FRONT_CENTRE));
	AssertInt(PT_int16, pcSound->GetPrimitiveType());
	AssertDouble(100.0 / 44100.0, pcSound->GetDuration(), 12);
	AssertTrue(pcSound->CanAccessSamples());

	pcChannel = pcSound->GetChannelAtIndex(1);
	AssertSize(SOUND_RIGHT, pcChannel->iChannel);
	AssertSize(2, pcChannel->miByteOffset);

	Ptr<CSound> pcCopy = OMalloc<CSound>(pcSound);
	AssertTrue(pcCopy->IsSameFormat(pcSound));
	AssertSize(100, pcCopy->GetNumFrames());

	Ptr<CSound> pcRate = OMalloc<CSound>(22050, 100, pcSound);
	AssertFalse(pcRate->IsSameFormat(pcSound));

	pcSound = NULL;
	pcCopy = NULL;
	pcRate = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSoundSampleConversion(void)
{
	int16	ai16[4];
	uint8	aui8[4];
	int32	ai32[2];
	float32	af32[2];
	int		i;
	int		iMismatches;
	int16	i16;

	Ptr<CSound> pcSound = OMalloc<CSound>(8000, 4, PT_int16, SOUND_MONO, CHANNEL_STOP);
	pcSound->SetSample(0, 0, -1.0);
	pcSound->SetSample(1, 0, 0.5);
	pcSound->SetSample(2, 0, 1.0);
	pcSound->SetSample(3, 0, -7.0);
	memcpy(ai16, pcSound->GetData(), sizeof(ai16));
	AssertInt(-32768, ai16[0]);
	AssertInt(16384, ai16[1]);
	AssertInt(32767, ai16[2]);
	AssertInt(-32768, ai16[3]);
	AssertDouble(-1.0, pcSound->GetSample(0, 0), 12);
	AssertDouble(0.5, pcSound->GetSample(1, 0), 12);

	//Every 16 bit value survives a trip through float64.
	iMismatches = 0;
	for (i = -32768; i <= 32767; i++)
	{
		i16 = (int16)i;
		ConvertSampleFromFloat(&i16, PT_int16, ConvertSampleToFloat(&i16, PT_int16));
		if (i16 != i)
		{
			iMismatches++;
		}
	}
	AssertInt(0, iMismatches);

	pcSound = OMalloc<CSound>(8000, 4, PT_uint8, SOUND_MONO, CHANNEL_STOP);
	pcSound->SetSample(0, 0, 0.0);
	pcSound->SetSample(1, 0, -1.0);
	pcSound->SetSample(2, 0, 1.0);
	pcSound->SetSample(3, 0, 0.25);
	memcpy(aui8, pcSound->GetData(), sizeof(aui8));
	AssertInt(128, aui8[0]);
	AssertInt(0, aui8[1]);
	AssertInt(255, aui8[2]);
	AssertInt(160, aui8[3]);
	AssertDouble(-1.0, pcSound->GetSample(1, 0), 12);
	AssertDouble(0.25, pcSound->GetSample(3, 0), 12);

	pcSound = OMalloc<CSound>(8000, 2, PT_int32, SOUND_MONO, CHANNEL_STOP);
	pcSound->SetSample(0, 0, -0.5);
	pcSound->SetSample(1, 0, 2.0);
	memcpy(ai32, pcSound->GetData(), sizeof(ai32));
	AssertInt(-1073741824, ai32[0]);
	AssertInt(2147483647, ai32[1]);

	//Floating point samples are not clamped.
	pcSound = OMalloc<CSound>(8000, 2, PT_float32, SOUND_MONO, CHANNEL_STOP);
	pcSound->SetSample(0, 0, 0.125);
	pcSound->SetSample(1, 0, 1.5);
	memcpy(af32, pcSound->GetData(), sizeof(af32));
	AssertFloat(0.125f, af32[0], 7);
	AssertFloat(1.5f, af32[1], 7);

	pcSound = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSoundSamples(void)
{
	float64		afSource[10];
	float64		afDest[10];
	int			i;
	int			iMismatches;

	Ptr<CSound> pcSound = OMalloc<CSound>(48000, 10, PT_float64, SOUND_LEFT, SOUND_RIGHT, SOUND_LOW_FREQUENCY, CHANNEL_STOP);
	pcSound->Silence();
	for (i = 0; i < 10; i++)
	{
		afSource[i] = i / 16.0;
	}
	AssertTrue(pcSound->SetSamples(2, 0, 10, afSource));
	AssertTrue(pcSound->GetSamples(2, 3, 5, afDest));

	iMismatches = 0;
	for (i = 0; i < 5; i++)
	{
		if (afDest[i] != afSource[i + 3])
		{
			iMismatches++;
		}
		if ((pcSound->GetSample(i, 0) != 0.0) || (pcSound->GetSample(i, 1) != 0.0))
		{
			iMismatches++;
		}
	}
	AssertInt(0, iMismatches);

	pcSound = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSoundSilence(void)
{
	uint8*	pui;
	int		i;
	int		iMismatches;

	Ptr<CSound> pcSound = OMalloc<CSound>(8000, 20, PT_uint8, SOUND_LEFT, SOUND_RIGHT, CHANNEL_STOP);
	memset(pcSound->GetData(), 7, pcSound->GetByteSize());
	pcSound->Silence();

	pui = (uint8*)pcSound->GetData();
	iMismatches = 0;
	for (i = 0; i < 40; i++)
	{
		if (pui[i] != 128)
		{
			iMismatches++;
		}
	}
	AssertInt(0, iMismatches);
	AssertDouble(0.0, pcSound->GetSample(19, 1), 12);

	pcSound = OMalloc<CSound>(8000, 20, PT_int16, SOUND_MONO, CHANNEL_STOP);
	memset(pcSound->GetData(), 7, pcSound->GetByteSize());
	pcSound->Silence();
	AssertDouble(0.0, pcSound->GetSample(5, 0), 12);

	pcSound = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
// Adding a channel and changing the length keeps the samples there are.
//
//////////////////////////////////////////////////////////////////////////
void TestSoundChange(void)
{
	int		i;
	int		iMismatches;

	Ptr<CSound> pcSound = OMalloc<CSound>(8000, 100, PT_int16, SOUND_LEFT, SOUND_RIGHT, CHANNEL_STOP);
	for (i = 0; i < 100; i++)
	{
		pcSound->SetSample(i, 0, i / 128.0);
		pcSound->SetSample(i, 1, -i / 128.0);
	}

	pcSound->BeginChange();
	pcSound->AddChannel(SOUND_FRONT_CENTRE, PT_int16);
	pcSound->SetNumFrames(50);
	pcSound->SetSampleRate(16000);
	AssertSize(50, pcSound->GetNumFrames());
	AssertInt(16000, pcSound->GetSampleRate());
	AssertTrue(pcSound->EndChange());

	AssertSize(3, pcSound->NumChannels());
	AssertSize(50, pcSound->GetNumFrames());
	AssertInt(16000, pcSound->GetSampleRate());
	AssertSize(6, pcSound->GetFrameByteStride());

	iMismatches = 0;
	for (i = 0; i < 50; i++)
	{
		if ((pcSound->GetSample(i, 0) != i / 128.0) || (pcSound->GetSample(i, 1) != -i / 128.0))
		{
			iMismatches++;
		}
	}
	AssertInt(0, iMismatches);

	pcSound = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSoundBadAccess(void)
{
	SLogConfig	sLogConfig;
	float64		af[4];

	sLogConfig = gcLogger.SetSilent();

	Ptr<CSound> pcSound = OMalloc<CSound>(8000, 4, PT_int16, SOUND_MONO, CHANNEL_STOP);
	AssertFalse(pcSound->GetSamples(1, 0, 4, af));
	AssertFalse(pcSound->GetSamples(0, 1, 4, af));
	AssertTrue(pcSound->GetSamples(0, 4, 0, af));
	AssertDouble(0.0, pcSound->GetSample(4, 0), 12);

	//Samples that aren't whole bytes can't be read as floats.
	pcSound = OMalloc<CSound>(8000, 4, PT_nybble, SOUND_LEFT, SOUND_RIGHT, CHANNEL_STOP);
	AssertFalse(pcSound->CanAccessSamples());
	AssertFalse(pcSound->GetSamples(1, 0, 4, af));

	gcLogger.SetConfig(&sLogConfig);
	pcSound = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSoundChannels(void)
{
	CChars	sz;

	AssertTrue(IsSoundSpeaker(SOUND_MONO));
	AssertTrue(IsSoundSpeaker(SOUND_TOP_BACK_RIGHT));
	AssertFalse(IsSoundSpeaker(SOUND_DISCRETE(0)));
	AssertTrue(IsSoundDiscrete(SOUND_DISCRETE(254)));
	AssertFalse(IsSoundDiscrete(SOUND_IGNORED));
	AssertSize(3, GetSoundDiscreteIndex(SOUND_DISCRETE(3)));
	AssertInt(SS_BackRight, GetSoundSpeaker(SOUND_BACK_RIGHT));
	AssertInt(NUM_SOUND_SPEAKERS, GetSoundSpeaker(IMAGE_DIFFUSE_RED));

	AssertInt(0x00001, GetSoundSpeakerMask(SOUND_FRONT_LEFT));
	AssertInt(0x00020, GetSoundSpeakerMask(SOUND_BACK_RIGHT));
	AssertInt(0x20000, GetSoundSpeakerMask(SOUND_TOP_BACK_RIGHT));
	AssertInt(0, GetSoundSpeakerMask(SOUND_MONO));
	AssertInt(0, GetSoundSpeakerMask(SOUND_DISCRETE(0)));
	AssertSize(SOUND_LOW_FREQUENCY, GetSoundSpeakerForMaskBit(3));
	AssertSize(CHANNEL_STOP, GetSoundSpeakerForMaskBit(18));

	//Sound channels never have the same number as image channels.
	AssertTrue(SOUND_MONO > IMAGE_ILLUMINATION_BLUE);
	AssertTrue(SOUND_MONO > CHANNEL(IP_Palette1, CT_Index));

	sz.Init();
	PrintSoundChannel(SOUND_FRONT_LEFT_OF_CENTRE, &sz);
	sz.Append(", ");
	PrintSoundChannel(SOUND_DISCRETE(12), &sz);
	sz.Append(", ");
	PrintSoundChannel(SOUND_IGNORED, &sz);
	AssertString("Front Left of Centre, Discrete 12, Ignored", sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSound(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestSoundInit();
	TestSoundSampleConversion();
	TestSoundSamples();
	TestSoundSilence();
	TestSoundChange();
	TestSoundBadAccess();
	TestSoundChannels();

	ObjectsKill(false);
	DataIOKill();

	TestStatistics();
}

