#include "BaseLib/Chars.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCharsReplace(void)
{
	CChars sz;

	sz.Init("1");
	sz.Overwrite(0, "22");
	AssertString("2", sz.Text());
	sz.Kill();

	sz.Init("Hello\nWorld\nMy Name is Henry\n");
	sz.Replace("\n", "[ ]");
	AssertString("Hello[ ]World[ ]My Name is Henry[ ]", sz.Text());
	sz.Replace("[ ]", "X");
	AssertString("HelloXWorldXMy Name is HenryX", sz.Text());
	sz.Replace("X", "*");
	AssertString("Hello*World*My Name is Henry*", sz.Text());
	sz.Replace("*", NULL);
	AssertString("HelloWorldMy Name is Henry", sz.Text());
	sz.Kill();

	sz.Init("XXZybot");
	sz.Replace("XX", "^");
	AssertString("^Zybot", sz.Text());
	sz.Replace("t", NULL);
	AssertString("^Zybo", sz.Text());
	sz.Replace("^", NULL);
	AssertString("Zybo", sz.Text());
	sz.Kill();

	sz.Init("XXZybot");
	sz.Replace("XX", "^^^^");
	AssertString("^^^^Zybot", sz.Text());
	sz.Replace("^^^^Zybot", "In the Age of Chaos");
	AssertString("In the Age of Chaos", sz.Text());
	sz.Replace("In the Age of Chaos", "Short");
	AssertString("Short", sz.Text());
	sz.Kill();

	sz.Init("SXSXSX56");
	sz.Replace("SX", "x");
	AssertString("xxx56", sz.Text());
	sz.Kill();

	sz.Init("   56");
	sz.Replace(" ", "");
	AssertString("56", sz.Text());
	sz.Kill();

	sz.Init("XXXXXXHelloXXXXXXXXXWorldXXXXXX");
	sz.Replace("XXX", "-");
	AssertString("--Hello---World--", sz.Text());
	sz.Kill();

	sz.Init("XXXXXXHelloXXXXXXXXXWorldXXXXXX");
	sz.Replace("XXX", "-+*+-");
	AssertString("-+*+--+*+-Hello-+*+--+*+--+*+-World-+*+--+*+-", sz.Text());
	sz.Kill();

	sz.Init("XXXXXXHelloXXXXXXXXXWorldXXXXXX");
	sz.Replace("XXX", "");
	AssertString("HelloWorld", sz.Text());
	sz.Kill();

	sz.Init("XXXXXXHelloXXXXXXXXXWorldXXXXXX");
	sz.Replace("XXX", NULL);
	AssertString("HelloWorld", sz.Text());
	sz.Kill();

	sz.Init("Q2");
	sz.Replace("Q2", "Queue");
	AssertString("Queue", sz.Text());
	sz.Kill();

	sz.Init("Q2");
	sz.Replace("Q2", "q");
	AssertString("q", sz.Text());
	sz.Kill();

	sz.Init("Q2Q2");
	sz.Replace("Q2", "");
	AssertString("", sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCharsInsert(void)
{
	CChars sz;

	sz.Init("Hell World");
	sz.Insert(4, "1234");
	AssertString("Hell1234 World", sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSplit(void)
{
	CChars			sz;
	CArrayString	cStrings;
	CChars*			psz;
	CChars			sz2;

	cStrings.Init(1);
	sz.Init("A.B");
	sz.Split(&cStrings, '.');

	AssertInt(2, cStrings.NumElements());
	AssertString("A", cStrings.Get(0)->Text());
	AssertString("B", cStrings.Get(1)->Text());


	sz.Init("\
Turburust CoreLib is free software: you can redistribute it and/or modify\n\
it under the terms of the GNU Lesser General Public License as published by\n\
the Free Software Foundation, either version 3 of the License, or\n\
(at your option) any later version.");
	sz2.Init(sz);

	cStrings.Init(1);
	sz.SplitLines(&cStrings);
	sz.Kill();
	
	AssertInt(4, cStrings.NumElements());
	AssertString("Turburust CoreLib is free software: you can redistribute it and/or modify", cStrings.Get(0)->Text());
	AssertString("it under the terms of the GNU Lesser General Public License as published by", cStrings.Get(1)->Text());
	AssertString("the Free Software Foundation, either version 3 of the License, or", cStrings.Get(2)->Text());
	AssertString("(at your option) any later version.", cStrings.Get(3)->Text());

	cStrings.Kill();

	cStrings.Init(1, TRUE);
	sz2.SplitLines(&cStrings);

	AssertInt(4, cStrings.NumElements());
	psz = cStrings.Get(0);
	AssertPointer(sz2.Text(), psz->Text());
	AssertInt(73, psz->Length());
	AssertBool(TRUE, psz->Equals("Turburust CoreLib is free software: you can redistribute it and/or modify", 73));
	psz = cStrings.Get(1);
	AssertInt(75, psz->Length());
	AssertBool(TRUE, psz->Equals("it under the terms of the GNU Lesser General Public License as published by", 75));
	psz = cStrings.Get(2);
	AssertInt(65, psz->Length());
	AssertBool(TRUE, psz->Equals("the Free Software Foundation, either version 3 of the License, or", 65));
	psz = cStrings.Get(3);
	AssertInt(35, psz->Length());
	AssertBool(TRUE, psz->Equals("(at your option) any later version.", 35));
	
	sz2.Kill();
	cStrings.Kill();
	
	sz.Init("\\Names\\Of\\Doom\\");
	cStrings.Init(1);
	sz.Split(&cStrings, '\\');
	sz.Kill();

	AssertInt(5, cStrings.NumElements());
	AssertString("", cStrings.Get(0)->Text());
	AssertString("Names", cStrings.Get(1)->Text());
	AssertString("Of", cStrings.Get(2)->Text());
	AssertString("Doom", cStrings.Get(3)->Text());
	AssertString("", cStrings.Get(4)->Text());

	sz.Init("\\Names\\Of\\Doom\\");
	cStrings.Init(1, TRUE);
	sz.Split(&cStrings, '\\');

	AssertInt(5, cStrings.NumElements());

	psz = cStrings.Get(0);
	AssertInt(0, psz->Length());
	psz = cStrings.Get(1);
	AssertInt(5, psz->Length());
	psz = cStrings.Get(2);
	AssertInt(2, psz->Length());
	psz = cStrings.Get(3);
	AssertInt(4, psz->Length());
	psz = cStrings.Get(4);
	AssertInt(0, psz->Length());

	cStrings.Kill();
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChars(void)
{
	BeginTests();

	TestCharsReplace();
	TestCharsInsert();
	TestSplit();

	TestStatistics();
}

