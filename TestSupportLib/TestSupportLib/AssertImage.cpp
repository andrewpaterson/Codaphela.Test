#include <string.h>
#include "BaseLib/TypeNames.h"
#include "TestLib/Assert.h"
#include "AssertImage.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool PrivateAssertChannel(EImagePurpose ePurpose, EChannelType eType, EPrimitiveType ePrimitive, SChannel* psChannel, size iLine, char* szFile)
{
	size			uiActualChannel;
	EPrimitiveType	eActualPrimitive;
	size			uiExpectedChannel;
	CChars			szExpected;
	CChars			szActual;
	EImagePurpose	eActualPurpose;
	EChannelType	eActualType;
	bool			bFailed;

	uiExpectedChannel = CHANNEL(ePurpose, eType);
	uiActualChannel = psChannel->iChannel;
	eActualPrimitive = psChannel->eType;

	if (uiExpectedChannel != uiActualChannel)
	{
		eActualPurpose = (EImagePurpose)((psChannel->iChannel - 1) / NUM_CHANNEL_TYPES);
		eActualType = (EChannelType)((psChannel->iChannel - 1) % NUM_CHANNEL_TYPES);

		szExpected.Init("(");
		szActual.Init("(");
		PrintImagePurpose(ePurpose, &szExpected);
		PrintImagePurpose(eActualPurpose, &szActual);
		szExpected.Append(", ");
		szActual.Append(", ");
		PrintChannelType(eType, &szExpected);
		PrintChannelType(eActualType, &szActual);
		szExpected.Append(")");
		szActual.Append(")");

		bFailed = Failed(szExpected.Text(), szActual.Text(), NULL, iLine, szFile, false);
		szExpected.Kill();
		szActual.Kill();
		return false;
	}

	if (ePrimitive != psChannel->eType)
	{
		szExpected.Init();
		szActual.Init();
		PrintPrimitiveType(ePrimitive, &szExpected);
		PrintPrimitiveType(psChannel->eType, &szActual);

		bFailed = Failed(szExpected.Text(), szActual.Text(), NULL, iLine, szFile, false);
		szExpected.Kill();
		szActual.Kill();
		return false;
	}
	else
	{
		return true;
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Compares channel by channel so images with the same channels in a
// different order (LoadPNG puts opacity first) are the same.
//
//////////////////////////////////////////////////////////////////////////
void AssertSameImage(Ptr<CImage> pcExpected, Ptr<CImage> pcActual)
{
	CArraySize		aiExpectedChannels;
	CArraySize		aiActualChannels;
	size			i;
	size			uiChannel;
	CChannel*		pcExpectedChannel;
	CChannel*		pcActualChannel;
	int				iNumPixels;
	size			uiExpectedStride;
	size			uiActualStride;
	uint8*			puiExpected;
	uint8*			puiActual;
	int				iPixel;
	int				iMismatches;

	AssertTrue(pcExpected.IsNotNull());
	AssertTrue(pcActual.IsNotNull());
	if (pcExpected.IsNull() || pcActual.IsNull())
	{
		return;
	}

	AssertInt(pcExpected->GetWidth(), pcActual->GetWidth());
	AssertInt(pcExpected->GetHeight(), pcActual->GetHeight());
	if ((pcExpected->GetWidth() != pcActual->GetWidth()) || (pcExpected->GetHeight() != pcActual->GetHeight()))
	{
		return;
	}

	aiExpectedChannels.Init();
	aiActualChannels.Init();
	pcExpected->GetAllChannels(&aiExpectedChannels);
	pcActual->GetAllChannels(&aiActualChannels);
	AssertSize(aiExpectedChannels.NumElements(), aiActualChannels.NumElements());

	iNumPixels = pcExpected->GetWidth() * pcExpected->GetHeight();
	uiExpectedStride = pcExpected->GetByteSize() / iNumPixels;
	uiActualStride = pcActual->GetByteSize() / iNumPixels;
	puiExpected = (uint8*)pcExpected->GetData();
	puiActual = (uint8*)pcActual->GetData();
	iMismatches = 0;
	for (i = 0; i < aiExpectedChannels.NumElements(); i++)
	{
		uiChannel = aiExpectedChannels.GetValue(i);
		pcExpectedChannel = pcExpected->GetChannel(uiChannel);
		pcActualChannel = pcActual->GetChannel(uiChannel);
		AssertNotNull(pcActualChannel);
		if (pcActualChannel == NULL)
		{
			continue;
		}
		AssertInt((int)pcExpectedChannel->eType, (int)pcActualChannel->eType);
		if (pcExpectedChannel->eType != pcActualChannel->eType)
		{
			continue;
		}
		for (iPixel = 0; iPixel < iNumPixels; iPixel++)
		{
			if (memcmp(&puiExpected[iPixel * uiExpectedStride + pcExpectedChannel->miByteOffset], &puiActual[iPixel * uiActualStride + pcActualChannel->miByteOffset], pcExpectedChannel->miByteSize) != 0)
			{
				iMismatches++;
			}
		}
	}
	AssertInt(0, iMismatches);

	aiExpectedChannels.Kill();
	aiActualChannels.Kill();
}


