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

		bFailed = Failed(szExpected.Text(), szActual.Text(), iLine, szFile, false);
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

		bFailed = Failed(szExpected.Text(), szActual.Text(), iLine, szFile, false);
		szExpected.Kill();
		szActual.Kill();
		return false;
	}
	else
	{
		return true;
	}
}

