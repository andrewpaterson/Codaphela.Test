#include <string.h>
#include "SupportLib/RLEPacketEncoder.h"
#include "SupportLib/RLEPacketDecoder.h"
#include "SupportLib/RLEBitmapDecoder.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRLEPacketEncoderSingleBytes(void)
{
	CRLEPacketEncoder	cEncoder;
	uint8				auiDest[300];
	uint8				auiSource[200];
	size				uiSize;
	int					i;

	cEncoder.Init(1);

	//A single run.
	uint8 auiRun[] = { 5, 5, 5, 5 };
	uint8 auiRunExpected[] = { 0x83, 5 };
	uiSize = cEncoder.Encode(auiRun, 4, auiDest);
	AssertSize(2, uiSize);
	AssertMemory(auiRunExpected, auiDest, uiSize);

	//A single raw packet.
	uint8 auiRaw[] = { 1, 2, 3, 4 };
	uint8 auiRawExpected[] = { 0x03, 1, 2, 3, 4 };
	uiSize = cEncoder.Encode(auiRaw, 4, auiDest);
	AssertSize(5, uiSize);
	AssertMemory(auiRawExpected, auiDest, uiSize);

	//One element is a raw packet.
	uint8 auiSingle[] = { 9 };
	uint8 auiSingleExpected[] = { 0x00, 9 };
	uiSize = cEncoder.Encode(auiSingle, 1, auiDest);
	AssertSize(2, uiSize);
	AssertMemory(auiSingleExpected, auiDest, uiSize);

	//A raw packet ends where a run of two starts.
	uint8 auiMixed[] = { 1, 2, 2, 3 };
	uint8 auiMixedExpected[] = { 0x00, 1, 0x81, 2, 0x00, 3 };
	uiSize = cEncoder.Encode(auiMixed, 4, auiDest);
	AssertSize(6, uiSize);
	AssertMemory(auiMixedExpected, auiDest, uiSize);

	//Runs longer than 128 are split.
	memset(auiSource, 7, 200);
	uint8 auiLongRunExpected[] = { 0xFF, 7, 0xC7, 7 };
	uiSize = cEncoder.Encode(auiSource, 200, auiDest);
	AssertSize(4, uiSize);
	AssertMemory(auiLongRunExpected, auiDest, uiSize);

	//Raw packets longer than 128 are split.
	for (i = 0; i < 130; i++)
	{
		auiSource[i] = (uint8)i;
	}
	uiSize = cEncoder.Encode(auiSource, 130, auiDest);
	AssertSize(132, uiSize);
	AssertInt(0x7F, auiDest[0]);
	AssertMemory(auiSource, &auiDest[1], 128);
	AssertInt(0x01, auiDest[129]);
	AssertInt(128, auiDest[130]);
	AssertInt(129, auiDest[131]);

	cEncoder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRLEPacketEncoderMultipleBytes(void)
{
	CRLEPacketEncoder	cEncoder;
	uint8				auiDest[64];
	size				uiSize;

	cEncoder.Init(3);

	uint8 auiPixels[] = { 1, 2, 3,  1, 2, 3,  4, 5, 6 };
	uint8 auiExpected[] = { 0x81, 1, 2, 3,  0x00, 4, 5, 6 };
	uiSize = cEncoder.Encode(auiPixels, 3, auiDest);
	AssertSize(8, uiSize);
	AssertMemory(auiExpected, auiDest, uiSize);

	//Elements that only partly match are not a run.
	uint8 auiPartial[] = { 1, 2, 3,  1, 2, 4 };
	uint8 auiPartialExpected[] = { 0x01, 1, 2, 3, 1, 2, 4 };
	uiSize = cEncoder.Encode(auiPartial, 2, auiDest);
	AssertSize(7, uiSize);
	AssertMemory(auiPartialExpected, auiDest, uiSize);

	//The worst case is a packet header for every element.
	AssertSize(40, cEncoder.GetMaxEncodedSize(10));

	cEncoder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRLEPacketDecoder(void)
{
	CRLEPacketDecoder	cDecoder;
	uint8*				puiElement;

	uint8 auiData[] = { 0x82, 9, 0x01, 1, 2 };
	cDecoder.Init(auiData, 5, 1);
	puiElement = cDecoder.Next();
	AssertPointer(&auiData[1], puiElement);
	AssertSize(2, cDecoder.GetPosition());

	//Every element of a run is the same pointer.
	AssertPointer(&auiData[1], cDecoder.Next());
	AssertPointer(&auiData[1], cDecoder.Next());
	AssertPointer(&auiData[3], cDecoder.Next());
	AssertPointer(&auiData[4], cDecoder.Next());
	AssertSize(5, cDecoder.GetPosition());
	AssertNull(cDecoder.Next());
	cDecoder.Kill();

	uint8 auiPixels[] = { 0x81, 0xA, 0xB,  0x00, 0xC, 0xD };
	cDecoder.Init(auiPixels, 6, 2);
	AssertPointer(&auiPixels[1], cDecoder.Next());
	AssertPointer(&auiPixels[1], cDecoder.Next());
	AssertPointer(&auiPixels[4], cDecoder.Next());
	AssertNull(cDecoder.Next());
	cDecoder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Truncated data returns NULL rather than reading past the end.
//
//////////////////////////////////////////////////////////////////////////
void TestRLEPacketDecoderTruncated(void)
{
	CRLEPacketDecoder	cDecoder;

	uint8 auiEmpty[] = { 0 };
	cDecoder.Init(auiEmpty, 0, 1);
	AssertNull(cDecoder.Next());
	cDecoder.Kill();

	//A raw packet of three elements with only two present.
	uint8 auiRaw[] = { 0x02, 1, 2 };
	cDecoder.Init(auiRaw, 3, 1);
	AssertPointer(&auiRaw[1], cDecoder.Next());
	AssertPointer(&auiRaw[2], cDecoder.Next());
	AssertNull(cDecoder.Next());
	cDecoder.Kill();

	//A run header with no element.
	uint8 auiRun[] = { 0x80 };
	cDecoder.Init(auiRun, 1, 1);
	AssertNull(cDecoder.Next());
	cDecoder.Kill();

	//A run with only part of a two byte element.
	uint8 auiPartial[] = { 0x80, 1 };
	cDecoder.Init(auiPartial, 2, 2);
	AssertNull(cDecoder.Next());
	cDecoder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRLEPacketRoundTrip(void)
{
	CRLEPacketEncoder	cEncoder;
	CRLEPacketDecoder	cDecoder;
	uint8				auiSource[300 * 2];
	uint8				auiEncoded[300 * 3];
	size				uiSize;
	uint8*				puiElement;
	int					i;
	bool				bSame;

	//Runs of varying lengths, including some longer than a packet, between raw elements.
	for (i = 0; i < 300; i++)
	{
		auiSource[i * 2] = (uint8)((i < 150) ? (i / 7) : i);
		auiSource[i * 2 + 1] = (uint8)((i % 50 == 0) ? i : 0);
	}

	cEncoder.Init(2);
	uiSize = cEncoder.Encode(auiSource, 300, auiEncoded);
	AssertTrue(uiSize <= cEncoder.GetMaxEncodedSize(300));
	cEncoder.Kill();

	bSame = true;
	cDecoder.Init(auiEncoded, uiSize, 2);
	for (i = 0; i < 300; i++)
	{
		puiElement = cDecoder.Next();
		if ((puiElement == NULL) || (memcmp(puiElement, &auiSource[i * 2], 2) != 0))
		{
			bSame = false;
			break;
		}
	}
	AssertTrue(bSame);
	AssertSize(uiSize, cDecoder.GetPosition());
	AssertNull(cDecoder.Next());
	cDecoder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRLEBitmapDecoderRLE8(void)
{
	CRLEBitmapDecoder	cDecoder;
	uint8				auiIndices[4 * 3];
	bool				bResult;

	uint8 auiData[] = {
		0x03, 0x01,							//Row 0: three pixels of index 1.
		0x00, 0x00,							//End of line.
		0x00, 0x02, 0x01, 0x00,				//Row 1: delta one pixel right.
		0x02, 0x07,							//Two pixels of index 7.
		0x00, 0x00,							//End of line.
		0x00, 0x03, 0x04, 0x05, 0x06, 0x00,	//Row 2: absolute run of three pixels, padded.
		0x05, 0x09,							//Five pixels of index 9, clipped to one.
		0x00, 0x01,							//End of bitmap.
		0x02, 0x08 };						//Ignored.

	uint8 auiExpected[] = {
		0x01, 0x01, 0x01, 0xEE,
		0xEE, 0x07, 0x07, 0xEE,
		0x04, 0x05, 0x06, 0x09 };

	memset(auiIndices, 0xEE, sizeof(auiIndices));
	cDecoder.Init(4, 3, false);
	bResult = cDecoder.Decode(auiData, sizeof(auiData), auiIndices);
	AssertTrue(bResult);
	AssertMemory(auiExpected, auiIndices, sizeof(auiIndices));
	cDecoder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRLEBitmapDecoderRLE4(void)
{
	CRLEBitmapDecoder	cDecoder;
	uint8				auiIndices[8];
	bool				bResult;

	uint8 auiData[] = {
		0x03, 0xAB,							//Three pixels alternating index 0xA and 0xB.
		0x00, 0x05, 0xCD, 0xEF, 0x10, 0x00,	//Absolute run of five pixels in three bytes, padded.
		0x00, 0x01 };						//End of bitmap.

	uint8 auiExpected[] = { 0x0A, 0x0B, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0x01 };

	memset(auiIndices, 0xEE, sizeof(auiIndices));
	cDecoder.Init(8, 1, true);
	bResult = cDecoder.Decode(auiData, sizeof(auiData), auiIndices);
	AssertTrue(bResult);
	AssertMemory(auiExpected, auiIndices, sizeof(auiIndices));
	cDecoder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRLEBitmapDecoderEdges(void)
{
	CRLEBitmapDecoder	cDecoder;
	uint8				auiIndices[4];
	bool				bResult;

	cDecoder.Init(4, 1, false);

	//An absolute run past the end of the data fails.
	uint8 auiAbsolute[] = { 0x00, 0x04, 0x01, 0x02 };
	bResult = cDecoder.Decode(auiAbsolute, sizeof(auiAbsolute), auiIndices);
	AssertFalse(bResult);

	//A delta past the end of the data fails.
	uint8 auiDelta[] = { 0x00, 0x02, 0x01 };
	bResult = cDecoder.Decode(auiDelta, sizeof(auiDelta), auiIndices);
	AssertFalse(bResult);

	//A missing end of bitmap is allowed.
	uint8 auiNoEnd[] = { 0x02, 0x05 };
	uint8 auiNoEndExpected[] = { 0x05, 0x05, 0xEE, 0xEE };
	memset(auiIndices, 0xEE, sizeof(auiIndices));
	bResult = cDecoder.Decode(auiNoEnd, sizeof(auiNoEnd), auiIndices);
	AssertTrue(bResult);
	AssertMemory(auiNoEndExpected, auiIndices, sizeof(auiIndices));

	//Pixels below the last row are ignored.
	uint8 auiBelow[] = { 0x00, 0x00, 0x02, 0x03, 0x00, 0x03, 0x04, 0x05, 0x06, 0x00 };
	uint8 auiBelowExpected[] = { 0xEE, 0xEE, 0xEE, 0xEE };
	memset(auiIndices, 0xEE, sizeof(auiIndices));
	bResult = cDecoder.Decode(auiBelow, sizeof(auiBelow), auiIndices);
	AssertTrue(bResult);
	AssertMemory(auiBelowExpected, auiIndices, sizeof(auiIndices));

	cDecoder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCompressionRLE(void)
{
	BeginTests();

	TestRLEPacketEncoderSingleBytes();
	TestRLEPacketEncoderMultipleBytes();
	TestRLEPacketDecoder();
	TestRLEPacketDecoderTruncated();
	TestRLEPacketRoundTrip();
	TestRLEBitmapDecoderRLE8();
	TestRLEBitmapDecoderRLE4();
	TestRLEBitmapDecoderEdges();

	TestStatistics();
}
