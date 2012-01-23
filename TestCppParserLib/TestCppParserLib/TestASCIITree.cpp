#include "stdafx.h"
#include "BaseLib/ASCIITree.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertTreeIndicies(CArrayInt* pcArrayInt, int iFirst, ...)
{
	va_list		vaMarker;
	int			i;
	int			iIndex;
	int			iActual;

	va_start(vaMarker, iFirst);
	iIndex = 0;
	i = iFirst;

	for (;;)
	{
		iActual = pcArrayInt->GetValue(iIndex);
		AssertInt(i, iActual);
		iIndex++;

		i = va_arg(vaMarker, int);
		if (i == -1)
		{
			break;
		}
	}
	va_end(vaMarker);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestASCIITreeGetZeroTerminated(void)
{
	CASCIITree		cTree;
	int				iIndex;
	int				iNode;
	CASCIINode* 	pcNode;
	int				iWord;
	CASCIINode* 	pcWord;

	cTree.Init();

	cTree.Add("Andrew");
	cTree.Add("Andre");

	cTree.PrivateGetZeroTerminated(&pcNode, &pcWord, &iNode, &iWord, "Andrew");
	AssertNotNull(pcNode);
	AssertInt(5, iNode);
	AssertInt(0, pcNode->maiWordEnds['w'-32]);
	AssertPointer(pcNode, pcWord);
	AssertInt(iNode, iWord);

	cTree.PrivateGetZeroTerminated(&pcNode, &pcWord, &iNode, &iWord, "Andrewicus");
	AssertNotNull(pcNode);
	AssertInt(5, iNode);
	AssertBool(TRUE, strlen("Andrewicus") != iNode);  //Did not find.  Letter not equal to string length.
	AssertPointer(pcNode, pcWord);
	AssertInt(iNode, iWord);

	cTree.PrivateGetZeroTerminated(&pcNode, &pcWord, &iNode, &iWord, "Andre");
	AssertNotNull(pcNode);
	AssertInt(4, iNode);
	AssertInt(1, pcNode->maiWordEnds['e'-32]);
	AssertPointer(pcNode, pcWord);
	AssertInt(iNode, iWord);

	cTree.PrivateGetZeroTerminated(&pcNode, &pcWord, &iNode, &iWord, "Heather");
	AssertPointer(cTree.mpcRoot, pcNode);
	AssertInt(0, iNode);
	AssertInt(-1, pcNode->maiWordEnds['H'-32]);  //Did not find.  Word end on last letter equal to -1.
	AssertNull(pcWord);
	AssertInt(-1, iWord);

	cTree.Add("An");
	cTree.PrivateGetZeroTerminated(&pcNode, &pcWord, &iNode, &iWord, "Andr");
	AssertNotNull(pcWord);
	AssertInt(1, iWord);
	AssertInt(2, pcWord->maiWordEnds['n'-32]);
	AssertInt(3, iNode);

	cTree.PrivateGetZeroTerminated(&pcNode, &pcWord, &iNode, &iWord, "");
	AssertNull(pcNode);
	AssertInt(-1, iNode);
	AssertNull(pcWord);
	AssertInt(-1, iWord);

	cTree.PrivateGetZeroTerminated(&pcNode, &pcWord, &iNode, &iWord, NULL);
	AssertNull(pcNode);
	AssertInt(-1, iNode);
	AssertNull(pcWord);
	AssertInt(-1, iWord);

	iIndex = cTree.GetIndex("");
	AssertInt(-1, iIndex);
	iIndex = cTree.GetIndex("A");
	AssertInt(-1, iIndex);
	iIndex = cTree.GetIndex("An");
	AssertInt(2, iIndex);
	iIndex = cTree.GetIndex("And");
	AssertInt(-1, iIndex);
	iIndex = cTree.GetIndex("Andr");
	AssertInt(-1, iIndex);
	iIndex = cTree.GetIndex("Andre");
	AssertInt(1, iIndex);
	iIndex = cTree.GetIndex("Andrew");
	AssertInt(0, iIndex);
	iIndex = cTree.GetIndex("Andrewi");
	AssertInt(-1, iIndex);
	iIndex = cTree.GetIndex("Andrewic");
	AssertInt(-1, iIndex);

	iIndex = cTree.GetIndex("", NULL, FALSE);
	AssertInt(-1, iIndex);
	iIndex = cTree.GetIndex("A", NULL, FALSE);
	AssertInt(-1, iIndex);
	iIndex = cTree.GetIndex("An", NULL, FALSE);
	AssertInt(2, iIndex);
	iIndex = cTree.GetIndex("And", NULL, FALSE);
	AssertInt(2, iIndex);
	iIndex = cTree.GetIndex("Andr", NULL, FALSE);
	AssertInt(2, iIndex);
	iIndex = cTree.GetIndex("Andre", NULL, FALSE);
	AssertInt(1, iIndex);
	iIndex = cTree.GetIndex("Andrew", NULL, FALSE);
	AssertInt(0, iIndex);
	iIndex = cTree.GetIndex("Andrewi", NULL, FALSE);
	AssertInt(0, iIndex);
	iIndex = cTree.GetIndex("Andrewic", NULL, FALSE);
	AssertInt(0, iIndex);

	cTree.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestASCIITreeGetLengthTerminated(void)
{
	CASCIITree		cTree;
	char			szAndrewicus[] = "Andrewicus";
	int				iIndex;
	int				iNode;
	CASCIINode* 	pcNode;
	int				iWord;
	CASCIINode* 	pcWord;
	char			szHeather[] = "Heather";

	cTree.Init();

	cTree.Add("Andrew");
	cTree.Add("Andre");

	cTree.PrivateGetLengthTerminated(&pcNode, &pcWord, &iNode, &iWord, &szAndrewicus[0], &szAndrewicus[5]);
	AssertNotNull(pcNode);
	AssertInt(5, iNode);
	AssertInt(0, pcNode->maiWordEnds['w'-32]);
	AssertPointer(pcNode, pcWord);
	AssertInt(iNode, iWord);

	cTree.PrivateGetLengthTerminated(&pcNode, &pcWord, &iNode, &iWord, &szAndrewicus[0], &szAndrewicus[9]);
	AssertNotNull(pcNode);
	AssertInt(5, iNode);
	AssertBool(TRUE, strlen("Andrewicus") != iNode);  //Did not find.  Letter not equal to string length.
	AssertPointer(pcNode, pcWord);
	AssertInt(iNode, iWord);

	cTree.PrivateGetLengthTerminated(&pcNode, &pcWord, &iNode, &iWord, &szAndrewicus[0], &szAndrewicus[4]);
	AssertNotNull(pcNode);
	AssertInt(4, iNode);
	AssertInt(1, pcNode->maiWordEnds['e'-32]);
	AssertPointer(pcNode, pcWord);
	AssertInt(iNode, iWord);

	cTree.PrivateGetLengthTerminated(&pcNode, &pcWord, &iNode, &iWord, &szHeather[0], &szHeather[6]);
	AssertPointer(cTree.mpcRoot, pcNode);
	AssertInt(0, iNode);
	AssertInt(-1, pcNode->maiWordEnds['H'-32]);  //Did not find.  Word end on last letter equal to -1.
	AssertNull(pcWord);
	AssertInt(-1, iWord);

	cTree.Add("An");
	cTree.PrivateGetLengthTerminated(&pcNode, &pcWord, &iNode, &iWord, &szAndrewicus[0], &szAndrewicus[3]);
	AssertNotNull(pcWord);
	AssertInt(1, iWord);
	AssertInt(2, pcWord->maiWordEnds['n'-32]);
	AssertInt(3, iNode);

	cTree.PrivateGetLengthTerminated(&pcNode, &pcWord, &iNode, &iWord, NULL, NULL);
	AssertNull(pcNode);
	AssertInt(-1, iNode);
	AssertNull(pcWord);
	AssertInt(-1, iWord);

	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[0]);
	AssertInt(-1, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[1]);
	AssertInt(2, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[2]);
	AssertInt(-1, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[3]);
	AssertInt(-1, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[4]);
	AssertInt(1, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[5]);
	AssertInt(0, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[6]);
	AssertInt(-1, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[7]);
	AssertInt(-1, iIndex);

	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[0], FALSE);
	AssertInt(-1, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[1], FALSE);
	AssertInt(2, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[2], FALSE);
	AssertInt(2, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[3], FALSE);
	AssertInt(2, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[4], FALSE);
	AssertInt(1, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[5], FALSE);
	AssertInt(0, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[6], FALSE);
	AssertInt(0, iIndex);
	iIndex = cTree.GetIndex(&szAndrewicus[0], &szAndrewicus[7], FALSE);
	AssertInt(0, iIndex);

	cTree.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestASCIITreeAdd(void)
{
	CASCIITree		cTree;
	int				iIndex;

	cTree.Init();
	iIndex = cTree.Add("");
	AssertInt(-1, iIndex);
	iIndex = cTree.Add("A");
	AssertInt(0, iIndex);
	iIndex = cTree.Add("An");
	AssertInt(1, iIndex);
	iIndex = cTree.Add("And");
	AssertInt(2, iIndex);
	iIndex = cTree.Add("Andr");
	AssertInt(3, iIndex);
	iIndex = cTree.Add("Andre");
	AssertInt(4, iIndex);
	iIndex = cTree.Add("Andrew");
	AssertInt(5, iIndex);
	iIndex = cTree.GetIndex("And");
	AssertInt(2, iIndex);
	cTree.Kill();

	cTree.Init();
	iIndex = cTree.Add("Andrew");
	AssertInt(0, iIndex);
	iIndex = cTree.Add("Andre");
	AssertInt(1, iIndex);
	iIndex = cTree.Add("Andr");
	AssertInt(2, iIndex);
	iIndex = cTree.Add("And");
	AssertInt(3, iIndex);
	iIndex = cTree.Add("An");
	AssertInt(4, iIndex);
	iIndex = cTree.Add("A");
	AssertInt(5, iIndex);
	iIndex = cTree.GetIndex("And");
	AssertInt(3, iIndex);
	cTree.Kill();

	cTree.Init();
	cTree.Add("A");
	cTree.Add("AA");
	cTree.Add("AB");
	cTree.Add("AAA");
	cTree.Add("AAB");
	cTree.Add("ABA");
	cTree.Add("ABB");
	cTree.Add("B");
	cTree.Add("BA");
	cTree.Add("BB");
	cTree.Add("BAA");
	cTree.Add("BAB");
	cTree.Add("BBA");
	cTree.Add("BBB");

	iIndex = cTree.GetIndex("A");
	AssertInt(0, iIndex);
	iIndex = cTree.GetIndex("AA");
	AssertInt(1, iIndex);
	iIndex = cTree.GetIndex("AB");
	AssertInt(2, iIndex);
	iIndex = cTree.GetIndex("AAA");
	AssertInt(3, iIndex);
	iIndex = cTree.GetIndex("AAB");
	AssertInt(4, iIndex);
	iIndex = cTree.GetIndex("ABA");
	AssertInt(5, iIndex);
	iIndex = cTree.GetIndex("ABB");
	AssertInt(6, iIndex);
	iIndex = cTree.GetIndex("B");
	AssertInt(7, iIndex);
	iIndex = cTree.GetIndex("BA");
	AssertInt(8, iIndex);
	iIndex = cTree.GetIndex("BB");
	AssertInt(9, iIndex);
	iIndex = cTree.GetIndex("BAA");
	AssertInt(10, iIndex);
	iIndex = cTree.GetIndex("BAB");
	AssertInt(11, iIndex);
	iIndex = cTree.GetIndex("BBA");
	AssertInt(12, iIndex);
	iIndex = cTree.GetIndex("BBB");
	AssertInt(13, iIndex);
	cTree.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestASCIITreeRemove(void)
{
	CASCIITree		cTree;
	int				iIndex;
	int				iNumWords;
	BOOL			bResult;

	cTree.Init();
	cTree.Add("A");
	cTree.Add("AA");
	cTree.Add("AB");
	cTree.Add("AAA");
	cTree.Add("AAB");
	cTree.Add("ABA");
	cTree.Add("ABB");
	cTree.Add("B");
	cTree.Add("BA");
	cTree.Add("BB");
	cTree.Add("BAA");
	cTree.Add("BAB");
	cTree.Add("BBA");
	cTree.Add("BBB");

	iNumWords = cTree.mcWords.NumElements();
	AssertInt(14, iNumWords);

	iIndex = cTree.GetIndex("AB");
	AssertInt(2, iIndex);

	cTree.Remove(ATRS_OnlyEndOfWordMarker, "AB");
	iIndex = cTree.GetIndex("AB");
	AssertInt(-1, iIndex);

	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "A");
	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "AA");
	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "AAA");
	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "AAB");
	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "BAA");
	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "ABA");
	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "B");
	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "BA");
	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "BBA");
	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "BBB");
	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "ABB");
	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "BB");
	cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "BAB");

	AssertInt(-1, cTree.GetIndex("A"));
	AssertInt(-1, cTree.GetIndex("AA"));
	AssertInt(-1, cTree.GetIndex("AAA"));
	AssertInt(-1, cTree.GetIndex("AAB"));
	AssertInt(-1, cTree.GetIndex("ABA"));
	AssertInt(-1, cTree.GetIndex("ABB"));
	AssertInt(-1, cTree.GetIndex("B"));
	AssertInt(-1, cTree.GetIndex("BA"));
	AssertInt(-1, cTree.GetIndex("BB"));
	AssertInt(-1, cTree.GetIndex("BAA"));
	AssertInt(-1, cTree.GetIndex("BAB"));
	AssertInt(-1, cTree.GetIndex("BBA"));
	AssertInt(-1, cTree.GetIndex("BBB"));

	iNumWords = cTree.mcWords.NumElements();
	AssertInt(14, iNumWords);

	cTree.Add("A");
	cTree.Add("AA");
	cTree.Add("AB");
	cTree.Add("AAA");
	cTree.Add("AAB");
	cTree.Add("ABA");
	cTree.Add("ABB");
	cTree.Add("B");
	cTree.Add("BA");
	cTree.Add("BB");
	cTree.Add("BAA");
	cTree.Add("BAB");
	cTree.Add("BBA");
	cTree.Add("BBB");

	iNumWords = cTree.mcWords.NumElements();
	AssertInt(14, iNumWords);

	bResult = cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "AAA");
	AssertBool(TRUE, bResult);
	bResult = cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "AAA");
	AssertBool(FALSE, bResult);
	bResult = cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, "");
	AssertBool(FALSE, bResult);
	bResult = cTree.Remove(ATRS_EndOfWordMarkerReuseIndex, NULL);
	AssertBool(FALSE, bResult);

	cTree.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestASCIITreeGetBetween(void)
{
	CASCIITree		cTree;
	CArrayInt		caiIndicies;

	cTree.Init();
	cTree.Add("A");
	cTree.Add("AA");
	cTree.Add("AAA");
	cTree.Add("AAB");
	cTree.Add("AB");
	cTree.Add("ABA");
	cTree.Add("ABB");
	cTree.Add("B");
	cTree.Add("BA");
	cTree.Add("BAA");
	cTree.Add("BAB");
	cTree.Add("BB");
	cTree.Add("BBA");
	cTree.Add("BBB");

	//ASCIINodes need to know their parents.

	caiIndicies.Init();
	cTree.GetBetween(&caiIndicies, "A", "B");
	AssertTreeIndicies(&caiIndicies, 1,2,3,4,5,6,-1);
	caiIndicies.Kill();

	caiIndicies.Init();
	cTree.GetBetween(&caiIndicies, "AB", "BA");
	AssertTreeIndicies(&caiIndicies, 5, 6, 7, -1);
	caiIndicies.Kill();

	caiIndicies.Init();
	cTree.GetBetween(&caiIndicies, "A", "ABB");
	AssertTreeIndicies(&caiIndicies, 1, 2, 3, 4, 5, -1);
	caiIndicies.Kill();

	caiIndicies.Init();
	cTree.GetBetween(&caiIndicies, "AAB", "BB");
	AssertTreeIndicies(&caiIndicies, 4, 5, 6, 7, 8, 9, 10, -1);
	caiIndicies.Kill();

	caiIndicies.Init();
	cTree.GetBetween(&caiIndicies, "BAA", "BBB");
	AssertTreeIndicies(&caiIndicies, 10, 11, 12, -1);
	caiIndicies.Kill();

	caiIndicies.Init();
	cTree.GetBetween(&caiIndicies, "A", "A");
	AssertInt(0, caiIndicies.NumElements());
	caiIndicies.Kill();

	caiIndicies.Init();
	cTree.GetBetween(&caiIndicies, NULL, "AB");
	AssertTreeIndicies(&caiIndicies, 0, 1, 2, 3, -1);
	caiIndicies.Kill();

	caiIndicies.Init();
	cTree.GetBetween(&caiIndicies, "BBA", NULL);
	AssertTreeIndicies(&caiIndicies, 13, -1);
	caiIndicies.Kill();

	caiIndicies.Init();
	cTree.GetBetween(&caiIndicies, NULL, NULL);
	AssertTreeIndicies(&caiIndicies, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, -1);
	caiIndicies.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestASCIITreeIterate(void)
{
	CASCIITree		cTree;
	SASCIITreeIter	sIter;
	long long int	iWordEnd;
	char*			sz;
	char*			sz2;
	CArrayString	casz;
	int				i;

	casz.Init(1);
	casz.Add("A");
	casz.Add("AA");
	casz.Add("AAA");
	casz.Add("AAB");
	casz.Add("AABTwopence");
	casz.Add("AABTwosense");
	casz.Add("AB");
	casz.Add("ABA");
	casz.Add("ABB");
	casz.Add("B");
	casz.Add("BA");
	casz.Add("BAA");
	casz.Add("BAB");
	casz.Add("BB");
	casz.Add("BBA");
	casz.Add("BBB");
	casz.Add("Mahogany");
	casz.Add("Muriel");
	casz.Add("Qwerty");
	
	cTree.Init();
	for (i = 0; i < casz.NumElements(); i++)
	{
		sz = casz.GetText(i);
		cTree.Add(sz);
	}

	i = 0;
	iWordEnd = cTree.StartIteration(&sIter);
	while (iWordEnd != -1)
	{
		sz = cTree.GetWord((int)iWordEnd);
		sz2 = casz.GetText(i);
		AssertString(sz2, sz);

		iWordEnd = cTree.Iterate(&sIter);
		i++;
	}

	cTree.Kill();
	casz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestASCIITree(void)
{
	FastFunctionsInit();

	BeginTests();

	TestASCIITreeGetZeroTerminated();
	TestASCIITreeGetLengthTerminated();
	TestASCIITreeAdd();
	TestASCIITreeRemove();
	TestASCIITreeGetBetween();
	TestASCIITreeIterate();

	TestStatistics();

	FastFunctionsKill();
}

