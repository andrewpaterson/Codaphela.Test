#include "BaseLib/UTF-8.h"
#include "BaseLib/TextFile.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUTF8Example1(void)
{

	CUTF8		cUTF8;
	CTextFile	cTextFile;
	CChars		sz;
	uint16		c16;
	uint32		c32;

	cTextFile.Init();
	cTextFile.Read("Input" _FS_ "UTF8" _FS_ "Example1.txt");
	sz.Init(cTextFile.Text());
	cTextFile.Kill();

	cUTF8.Init(&sz);

	c16 = cUTF8.GetUint16();
	AssertChar('H', (char)c16);
	c16 = cUTF8.GetUint16();
	AssertChar('e', (char)c16);
	c16 = cUTF8.GetUint16();
	AssertChar('l', (char)c16);
	c16 = cUTF8.GetUint16();
	AssertChar('l', (char)c16);
	c16 = cUTF8.GetUint16();
	AssertChar('o', (char)c16);
	c16 = cUTF8.GetUint16();
	AssertChar(' ', (char)c16);

	c16 = cUTF8.GetUint16();
	AssertShort((uint16)0xFFFD, c16);

	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x4E16, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x754C, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x0020, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x1F43C, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x0020, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x002D, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x0020, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x20AC, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x0020, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x00A9, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x0020, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x1D7D9, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x1D7DA, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x1D7DB, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0, c32);

	cUTF8.Kill();
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUTF8Example2(void)
{
	CUTF8		cUTF8;
	CTextFile	cTextFile;
	CChars		sz;
	uint16		c16;
	uint32		c32;

	cTextFile.Init();
	cTextFile.Read("Input" _FS_ "UTF8" _FS_ "Example2.txt");
	sz.Init(cTextFile.Text());
	cTextFile.Kill();

	cUTF8.Init(&sz);

	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x1F993, c32);
	c16 = cUTF8.GetUint16();
	AssertChar('À', (char)c16);
	c16 = cUTF8.GetUint16();
	AssertChar('é', (char)c16);
	c16 = cUTF8.GetUint16();
	AssertShort((uint16)0x0142, c16);
	c16 = cUTF8.GetUint16();
	AssertChar('ö', (char)c16);
	c16 = cUTF8.GetUint16();
	AssertChar('ü', (char)c16);
	c16 = cUTF8.GetUint16();
	AssertShort((uint16)0x0000, c16);


	cUTF8.Kill();
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUTF8Example3(void)
{
	CUTF8		cUTF8;
	CTextFile	cTextFile;
	CChars		sz;
	uint32		c32;

	cTextFile.Init();
	cTextFile.Read("Input" _FS_ "UTF8" _FS_ "Example3.txt");
	sz.Init(cTextFile.Text());
	cTextFile.Kill();

	cUTF8.Init(&sz);

	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x1F469, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x200D, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x1F3FB, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x200D, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0x1F9B0, c32);
	c32 = cUTF8.GetUint32();
	AssertInt((uint32)0, c32);

	cUTF8.Kill();
	sz.Kill();
}
//U+1F469 U+200D U+1F3FB U+200D U+1F9B0

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUTF8(void)
{
	BeginTests();

	TestUTF8Example1();
	TestUTF8Example2();
	TestUTF8Example3();

	TestStatistics();
}

