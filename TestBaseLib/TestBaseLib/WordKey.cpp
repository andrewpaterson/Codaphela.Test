#include "WordKey.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void MakeKey(CRandom* cRandom, CArrayChars* aszWords, CChars* sz)
{
	int		iIndex;
	char* szWord;

	iIndex = cRandom->Next(0, aszWords->NumElements() - 1);
	szWord = aszWords->GetText(iIndex);
	sz->Init(szWord)->Append(" ");
	iIndex = cRandom->Next(0, aszWords->NumElements() - 1);
	szWord = aszWords->GetText(iIndex);
	sz->Append(szWord)->Append(" ");
	iIndex = cRandom->Next(0, aszWords->NumElements() - 1);
	szWord = aszWords->GetText(iIndex);
	sz->Append(szWord);
}

