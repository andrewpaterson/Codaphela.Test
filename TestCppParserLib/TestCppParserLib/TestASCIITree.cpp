#include "stdafx.h"
#include "CPPParserLib/ASCIITree.h"
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

	cTree.AddIndex("Andrew");
	cTree.AddIndex("Andre");

	cTree.PrivateGetZeroTerminated(&pcNode, &pcWord, &iNode, &iWord, "Andrew");
	AssertNotNull(pcNode);
	AssertInt(5, iNode);
	AssertInt(0, pcNode->maiWordEnds['w'-32]);
	AssertPointer(pcNode, pcWord);
	AssertInt(iNode, iWord);

	cTree.PrivateGetZeroTerminated(&pcNode, &pcWord, &iNode, &iWord, "Andrewicus");
	AssertNotNull(pcNode);
	AssertInt(5, iNode);
	AssertBool(TRUE, strlen("Andrewicus") != (size_t)iNode);  //Did not find.  Letter not equal to string length.
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

	cTree.AddIndex("An");
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

	cTree.AddIndex("Andrew");
	cTree.AddIndex("Andre");

	cTree.PrivateGetLengthTerminated(&pcNode, &pcWord, &iNode, &iWord, &szAndrewicus[0], &szAndrewicus[5]);
	AssertNotNull(pcNode);
	AssertInt(5, iNode);
	AssertInt(0, pcNode->maiWordEnds['w'-32]);
	AssertPointer(pcNode, pcWord);
	AssertInt(iNode, iWord);

	cTree.PrivateGetLengthTerminated(&pcNode, &pcWord, &iNode, &iWord, &szAndrewicus[0], &szAndrewicus[9]);
	AssertNotNull(pcNode);
	AssertInt(5, iNode);
	AssertBool(TRUE, strlen("Andrewicus") != (size_t)iNode);  //Did not find.  Letter not equal to string length.
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

	cTree.AddIndex("An");
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
	iIndex = cTree.AddIndex("");
	AssertInt(-1, iIndex);
	iIndex = cTree.AddIndex("A");
	AssertInt(0, iIndex);
	iIndex = cTree.AddIndex("An");
	AssertInt(1, iIndex);
	iIndex = cTree.AddIndex("And");
	AssertInt(2, iIndex);
	iIndex = cTree.AddIndex("Andr");
	AssertInt(3, iIndex);
	iIndex = cTree.AddIndex("Andre");
	AssertInt(4, iIndex);
	iIndex = cTree.AddIndex("Andrew");
	AssertInt(5, iIndex);
	iIndex = cTree.GetIndex("And");
	AssertInt(2, iIndex);
	cTree.Kill();

	cTree.Init();
	iIndex = cTree.AddIndex("Andrew");
	AssertInt(0, iIndex);
	iIndex = cTree.AddIndex("Andre");
	AssertInt(1, iIndex);
	iIndex = cTree.AddIndex("Andr");
	AssertInt(2, iIndex);
	iIndex = cTree.AddIndex("And");
	AssertInt(3, iIndex);
	iIndex = cTree.AddIndex("An");
	AssertInt(4, iIndex);
	iIndex = cTree.AddIndex("A");
	AssertInt(5, iIndex);
	iIndex = cTree.GetIndex("And");
	AssertInt(3, iIndex);
	cTree.Kill();

	cTree.Init();
	cTree.AddIndex("A");
	cTree.AddIndex("AA");
	cTree.AddIndex("AB");
	cTree.AddIndex("AAA");
	cTree.AddIndex("AAB");
	cTree.AddIndex("ABA");
	cTree.AddIndex("ABB");
	cTree.AddIndex("B");
	cTree.AddIndex("BA");
	cTree.AddIndex("BB");
	cTree.AddIndex("BAA");
	cTree.AddIndex("BAB");
	cTree.AddIndex("BBA");
	cTree.AddIndex("BBB");

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
	cTree.AddIndex("A");
	cTree.AddIndex("AA");
	cTree.AddIndex("AB");
	cTree.AddIndex("AAA");
	cTree.AddIndex("AAB");
	cTree.AddIndex("ABA");
	cTree.AddIndex("ABB");
	cTree.AddIndex("B");
	cTree.AddIndex("BA");
	cTree.AddIndex("BB");
	cTree.AddIndex("BAA");
	cTree.AddIndex("BAB");
	cTree.AddIndex("BBA");
	cTree.AddIndex("BBB");

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

	cTree.AddIndex("A");
	cTree.AddIndex("AA");
	cTree.AddIndex("AB");
	cTree.AddIndex("AAA");
	cTree.AddIndex("AAB");
	cTree.AddIndex("ABA");
	cTree.AddIndex("ABB");
	cTree.AddIndex("B");
	cTree.AddIndex("BA");
	cTree.AddIndex("BB");
	cTree.AddIndex("BAA");
	cTree.AddIndex("BAB");
	cTree.AddIndex("BBA");
	cTree.AddIndex("BBB");

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
	cTree.AddIndex("A");
	cTree.AddIndex("AA");
	cTree.AddIndex("AAA");
	cTree.AddIndex("AAB");
	cTree.AddIndex("AB");
	cTree.AddIndex("ABA");
	cTree.AddIndex("ABB");
	cTree.AddIndex("B");
	cTree.AddIndex("BA");
	cTree.AddIndex("BAA");
	cTree.AddIndex("BAB");
	cTree.AddIndex("BB");
	cTree.AddIndex("BBA");
	cTree.AddIndex("BBB");

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
	CArrayChars	casz;
	int				i;

	casz.Init();
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
		cTree.AddIndex(sz);
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
void TestASCIITreeAddLong(void)
{
	CASCIITree		cTree;
	long long int	lliID;
	long long int	lli1;
	long long int	lli2;
	long long int	lli3;
	long long int	lli4;
	long long int	lli5;
	long long int	lli6;
	long long int	lli7;
	long long int	lli8;
	long long int	lli9;

	cTree.Init();

	lli1 = 237489LL;
	cTree.AddIndex(lli1, "Seven/Hundred");
	lliID = cTree.Get("Seven/Hundred");
	AssertLongLongInt(lli1, lliID);

	lli2 = 237222LL; cTree.AddIndex(lli2, "Seven/Battalion");
	lli3 = 7328423132LL; cTree.AddIndex(lli3, "Creating");
	lli4 = 28LL; cTree.AddIndex(lli4, "Nineteen/O/Five");
	lli5 = 8993992939LL; cTree.AddIndex(lli5, "Creative");

	AssertLongLongInt(lli1, cTree.Get("Seven/Hundred"));
	AssertLongLongInt(lli2, cTree.Get("Seven/Battalion"));
	AssertLongLongInt(lli3, cTree.Get("Creating"));
	AssertLongLongInt(lli4, cTree.Get("Nineteen/O/Five"));
	AssertLongLongInt(lli5, cTree.Get("Creative"));

	lli6 = 27LL; cTree.AddIndex(lli6, "Seven/Aardvarks");
	lli7 = 874289234LL; cTree.AddIndex(lli7, "Nineteen/O/Four");
	lli8 = 882191919LL; cTree.AddIndex(lli8, "Squiggly");
	lli9 = 8993992938LL; cTree.AddIndex(lli9, "Puff");

	AssertLongLongInt(lli1, cTree.Get("Seven/Hundred"));
	AssertLongLongInt(lli2, cTree.Get("Seven/Battalion"));
	AssertLongLongInt(lli3, cTree.Get("Creating"));
	AssertLongLongInt(lli4, cTree.Get("Nineteen/O/Five"));
	AssertLongLongInt(lli5, cTree.Get("Creative"));
	AssertLongLongInt(lli6, cTree.Get("Seven/Aardvarks"));
	AssertLongLongInt(lli7, cTree.Get("Nineteen/O/Four"));
	AssertLongLongInt(lli8, cTree.Get("Squiggly"));
	AssertLongLongInt(lli9, cTree.Get("Puff"));


	cTree.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestASCIITreeRemoveLong(void)
{
	CASCIITree		cTree;
	long long int	lli1;
	long long int	lli2;
	long long int	lli3;
	long long int	lli4;
	long long int	lli5;
	long long int	lli6;
	long long int	lli7;
	long long int	lli8;
	long long int	lli9;
	BOOL			bResult;

	cTree.Init();

	lli1 = 237489LL; cTree.AddIndex(lli1, "Seven/Hundred");
	lli2 = 237222LL; cTree.AddIndex(lli2, "Seven/Battalion");
	lli3 = 7328423132LL; cTree.AddIndex(lli3, "Creating");
	lli4 = 28LL; cTree.AddIndex(lli4, "Nineteen/O/Five");
	lli5 = 8993992939LL; cTree.AddIndex(lli5, "Creative");
	lli6 = 27LL; cTree.AddIndex(lli6, "Seven/Aardvarks");
	lli7 = 874289234LL; cTree.AddIndex(lli7, "Nineteen/O/Four");
	lli8 = 882191919LL; cTree.AddIndex(lli8, "Squiggly");
	lli9 = 8993992938LL; cTree.AddIndex(lli9, "Puff");

	AssertInt(9, cTree.NumElements());

	bResult = cTree.Remove("Nineteen/O/Four");
	AssertTrue(bResult);
	AssertTrue(cTree.TestConsistency());
	AssertInt(8, cTree.NumElements());

	AssertLongLongInt(lli1, cTree.Get("Seven/Hundred"));
	AssertLongLongInt(lli2, cTree.Get("Seven/Battalion"));
	AssertLongLongInt(lli3, cTree.Get("Creating"));
	AssertLongLongInt(lli4, cTree.Get("Nineteen/O/Five"));
	AssertLongLongInt(lli5, cTree.Get("Creative"));
	AssertLongLongInt(lli6, cTree.Get("Seven/Aardvarks"));
	AssertLongLongInt(-1LL, cTree.Get("Nineteen/O/Four"));
	AssertLongLongInt(lli8, cTree.Get("Squiggly"));
	AssertLongLongInt(lli9, cTree.Get("Puff"));

	bResult = cTree.Remove("Squiggly");
	AssertTrue(bResult);
	AssertTrue(cTree.TestConsistency());
	AssertInt(7, cTree.NumElements());

	AssertLongLongInt(lli1, cTree.Get("Seven/Hundred"));
	AssertLongLongInt(lli2, cTree.Get("Seven/Battalion"));
	AssertLongLongInt(lli3, cTree.Get("Creating"));
	AssertLongLongInt(lli4, cTree.Get("Nineteen/O/Five"));
	AssertLongLongInt(lli5, cTree.Get("Creative"));
	AssertLongLongInt(lli6, cTree.Get("Seven/Aardvarks"));
	AssertLongLongInt(-1LL, cTree.Get("Nineteen/O/Four"));
	AssertLongLongInt(-1LL, cTree.Get("Squiggly"));
	AssertLongLongInt(lli9, cTree.Get("Puff"));

	bResult = cTree.Remove("Seven/Hundred");
	AssertTrue(bResult);
	AssertTrue(cTree.TestConsistency());
	AssertInt(6, cTree.NumElements());

	AssertLongLongInt(-1LL, cTree.Get("Seven/Hundred"));
	AssertLongLongInt(lli2, cTree.Get("Seven/Battalion"));
	AssertLongLongInt(lli3, cTree.Get("Creating"));
	AssertLongLongInt(lli4, cTree.Get("Nineteen/O/Five"));
	AssertLongLongInt(lli5, cTree.Get("Creative"));
	AssertLongLongInt(lli6, cTree.Get("Seven/Aardvarks"));
	AssertLongLongInt(-1LL, cTree.Get("Nineteen/O/Four"));
	AssertLongLongInt(-1LL, cTree.Get("Squiggly"));
	AssertLongLongInt(lli9, cTree.Get("Puff"));

	AssertTrue(cTree.Remove("Puff"));
	AssertTrue(cTree.TestConsistency());
	AssertTrue(cTree.Remove("Seven/Battalion"));
	AssertTrue(cTree.TestConsistency());
	AssertTrue(cTree.Remove("Creating"));
	AssertTrue(cTree.TestConsistency());
	AssertTrue(cTree.Remove("Nineteen/O/Five"));
	AssertTrue(cTree.TestConsistency());
	AssertTrue(cTree.Remove("Creative"));
	AssertTrue(cTree.TestConsistency());

	AssertInt(1,  cTree.NumElements());

	AssertTrue(cTree.Remove("Seven/Aardvarks"));
	AssertTrue(cTree.TestConsistency());
	AssertInt(0,  cTree.NumElements());
	AssertTrue(cTree.IsEmpty());

	cTree.Kill();
}
//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestASCIITreeDiamondError(void)
{
	CASCIITree		cTree;

	cTree.Init();

	AssertInt(0, cTree.AddIndex(1, "GraphRoot"));
	AssertInt(1, cTree.AddIndex(3, "Diamond End"));
	AssertInt(2, cTree.AddIndex(5, "NamedString 1"));
	AssertInt(3, cTree.AddIndex(6, "NamedString 2"));
	AssertInt(4, cTree.AddIndex(10, "Double Start"));
	AssertInt(5, cTree.AddIndex(11, "NamedString 3"));
	AssertTrue(cTree.TestConsistency());

	cTree.Kill();
	cTree.Init();

	AssertInt(0, cTree.AddIndex(1, "GraphRoot"));
	AssertInt(1, cTree.AddIndex(10, "Double Start"));
	AssertInt(2, cTree.AddIndex(11, "NamedString 3"));
	AssertTrue(cTree.Remove(ATRS_MoveLastToRemoved, "Double Start"));
	AssertTrue(cTree.TestConsistency());
	AssertInt(2, cTree.AddIndex(10, "Double Start"));
	AssertInt(3, cTree.AddIndex(6, "NamedString 2"));
	AssertInt(4, cTree.AddIndex(5, "NamedString 1"));
	AssertTrue(cTree.Remove(ATRS_MoveLastToRemoved, "NamedString 2"));
	AssertTrue(cTree.TestConsistency());
	AssertInt(4, cTree.AddIndex(6, "NamedString 2"));
	AssertInt(5, cTree.AddIndex(3, "Diamond End"));
	AssertTrue(cTree.TestConsistency());

	cTree.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestASCIITree(void)
{
	BeginTests();
	FastFunctionsInit();

	TestASCIITreeAdd();
	TestASCIITreeRemove();
	TestASCIITreeDiamondError();
	TestASCIITreeGetZeroTerminated();
	TestASCIITreeGetLengthTerminated();
	TestASCIITreeAddLong();
	TestASCIITreeRemoveLong();
	TestASCIITreeGetBetween();
	TestASCIITreeIterate();

	FastFunctionsKill();
	TestStatistics();
}

