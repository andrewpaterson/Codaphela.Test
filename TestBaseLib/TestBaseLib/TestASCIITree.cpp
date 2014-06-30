#include "BaseLib/ASCIITree.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestASCIITreeAdd(void)
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
void TestASCIITreeRemove(void)
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

	TestASCIITreeAdd();
	TestASCIITreeRemove();
	TestASCIITreeDiamondError();

	TestStatistics();
}

