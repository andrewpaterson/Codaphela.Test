#include "BaseLib/UTF-16.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/ArrayUint16.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUTF16Example1(void)
{
	CUTF16			cUTF16;
	CTextFile		cTextFile;
	uint16			c16;
	uint32			c32;
	bool			bRead;
	CArrayUint16	aui;

	cTextFile.Init();
	bRead = cTextFile.Read("Input" _FS_ "UTF16LE" _FS_ "Example1.txt");
	AssertTrue(bRead);
	aui.Init(&gcSystemAllocator, (uint16*)cTextFile.Text(), cTextFile.Length() / sizeof(uint16));
	cTextFile.Kill();

	cUTF16.Init(aui.GetData(), aui.NumElements());

	AssertTrue(cUTF16.GetByteOrderMark());

	c16 = cUTF16.GetUint16();
	AssertChar('H', (char)c16);
	c16 = cUTF16.GetUint16();
	AssertChar('e', (char)c16);
	c16 = cUTF16.GetUint16();
	AssertChar('l', (char)c16);
	c16 = cUTF16.GetUint16();
	AssertChar('l', (char)c16);
	c16 = cUTF16.GetUint16();
	AssertChar('o', (char)c16);
	c16 = cUTF16.GetUint16();
	AssertChar(' ', (char)c16);

	c16 = cUTF16.GetUint16();
	AssertShort((uint16)0x4E16, c16);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x754C, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x0020, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x1F43C, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x0020, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x002D, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x0020, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x20AC, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x0020, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x00A9, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x0020, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x1D7D9, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x1D7DA, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x1D7DB, c32);
	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0, c32);

	cUTF16.Kill();
	aui.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUTF16Example2(void)
{
	CUTF16			cUTF16;
	CTextFile		cTextFile;
	CArrayUint16	aui;
	uint16			c16;
	uint32			c32;
	bool			bRead;

	cTextFile.Init();
	bRead = cTextFile.Read("Input" _FS_ "UTF16LE" _FS_ "Example2.txt");
	AssertTrue(bRead);
	aui.Init(&gcSystemAllocator, (uint16*)cTextFile.Text(), cTextFile.Length() / sizeof(uint16));
	cTextFile.Kill();

	cUTF16.Init(aui.GetData(), aui.NumElements());

	AssertTrue(cUTF16.GetByteOrderMark());

	c32 = cUTF16.GetUint32();
	AssertInt((uint32)0x1F993, c32);
	c16 = cUTF16.GetUint16();
	AssertChar('À', (char)c16);
	c16 = cUTF16.GetUint16();
	AssertChar('é', (char)c16);
	c16 = cUTF16.GetUint16();
	AssertShort((uint16)0x0142, c16);
	c16 = cUTF16.GetUint16();
	AssertChar('ö', (char)c16);
	c16 = cUTF16.GetUint16();
	AssertChar('ü', (char)c16);
	c16 = cUTF16.GetUint16();
	AssertShort((uint16)0x0000, c16);


	cUTF16.Kill();
	aui.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUTF16Example3(void)
{
	CUTF16			cUTF16;
	CTextFile		cTextFile;
	CArrayUint16	aui;
	uint32			c32;
	size			uiUTF16ElementLength;
	size			uiCodePointLength;
	size			uiPos;
	uint8			auiBuffer[0x13];
	uint8*			psz;
	bool			bRead;

	cTextFile.Init();
	bRead = cTextFile.Read("Input" _FS_ "UTF16LE" _FS_ "Example3.txt");
	AssertTrue(bRead);
	aui.Init(&gcSystemAllocator, (uint16*)cTextFile.Text(), cTextFile.Length() / sizeof(uint16));
	cTextFile.Kill();

	cUTF16.Init(aui.GetData(), aui.NumElements());

	AssertTrue(cUTF16.GetByteOrderMark());

	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0x0041, c32);
	AssertSize(1, GetUnicodeCodePointLength(c32));
	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0x1F469, c32);
	AssertSize(3, GetUnicodeCodePointLength(c32));
	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0x200D, c32);
	AssertSize(2, GetUnicodeCodePointLength(c32));
	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0x1F3FB, c32);
	AssertSize(3, GetUnicodeCodePointLength(c32));
	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0x200D, c32);
	AssertSize(2, GetUnicodeCodePointLength(c32));
	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0x1F9B0, c32);
	AssertSize(3, GetUnicodeCodePointLength(c32));
	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0, c32);
	cUTF16.Kill();

	cUTF16.Init(aui.GetData(), aui.NumElements());

	AssertTrue(cUTF16.GetByteOrderMark());

	uiPos = cUTF16.GetPosition();
	AssertSize(1, uiPos);
	uiUTF16ElementLength = cUTF16.Peek();
	AssertSize(1, uiUTF16ElementLength);
	uiPos = cUTF16.GetPosition();
	AssertSize(1, uiPos);

	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0x0041, c32);
	AssertSize(1, GetUnicodeCodePointLength(c32));

	uiUTF16ElementLength = cUTF16.Peek();
	AssertSize(8, uiUTF16ElementLength);
	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0x1F469, c32);
	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0x200D, c32);
	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0x1F3FB, c32);
	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0x200D, c32);
	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0x1F9B0, c32);

	uiPos = cUTF16.GetPosition();
	AssertSize(10, uiPos);
	uiUTF16ElementLength = cUTF16.Peek();
	AssertSize(0, uiUTF16ElementLength);

	c32 = cUTF16.GetUint32();
	AssertIntHex((uint32)0, c32);
	cUTF16.Kill();

	cUTF16.Init(aui.GetData(), aui.NumElements());

	AssertTrue(cUTF16.GetByteOrderMark());

	uiPos = cUTF16.GetPosition();
	AssertSize(1, uiPos);
	uiUTF16ElementLength = cUTF16.Peek();
	AssertSize(1, uiUTF16ElementLength);
	memset(auiBuffer, 0, 0x13);
	uiCodePointLength = cUTF16.GetMulti(auiBuffer, 0x12);
	AssertSize(1, uiCodePointLength);
	AssertString("A", (char*)auiBuffer);

	uiPos = cUTF16.GetPosition();
	AssertSize(2, uiPos);
	uiUTF16ElementLength = cUTF16.Peek();
	AssertSize(8, uiUTF16ElementLength);
	memset(auiBuffer, 0, 0x13);
	uiCodePointLength = cUTF16.GetMulti(auiBuffer, 0x12);
	AssertSize(11, uiCodePointLength);
	psz = auiBuffer;
	AssertString("iô", (char*)psz);
	psz = (uint8*)NextString((char*)psz);
	AssertString("ûó", (char*)psz);
	psz = (uint8*)NextString((char*)psz);
	AssertString("°ù", (char*)psz);

	uiPos = cUTF16.GetPosition();
	uiUTF16ElementLength = cUTF16.Peek();
	AssertSize(10, uiPos);
	AssertSize(0, uiUTF16ElementLength);
	memset(auiBuffer, 0, 0x13);
	uiCodePointLength = cUTF16.GetMulti(auiBuffer, 0x12);
	AssertSize(0, uiCodePointLength);
	AssertString("", (char*)auiBuffer);
	cUTF16.Kill();

	aui.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUTF16Example4(void)
{
	CUTF16			cUTF16;
	CTextFile		cTextFile;
	CArrayUint16	aui;
	size			uiUTF16ElementLength;
	size			uiCodePointLength;
	size			uiPos;
	uint8			auiBuffer[0x13];
	uint8*			psz;
	bool			bRead;

	cTextFile.Init();
	bRead = cTextFile.Read("Input" _FS_ "UTF16LE" _FS_ "Example4.txt");
	AssertTrue(bRead);
	aui.Init(&gcSystemAllocator, (uint16*)cTextFile.Text(), cTextFile.Length() / sizeof(uint16));
	cTextFile.Kill();

	cUTF16.Init(aui.GetData(), aui.NumElements());
	
	AssertTrue(cUTF16.GetByteOrderMark());

	uiPos = cUTF16.GetPosition();
	AssertSize(1, uiPos);
	uiUTF16ElementLength = cUTF16.Peek();
	AssertSize(1, uiUTF16ElementLength);
	memset(auiBuffer, 0, 0x13);
	uiCodePointLength = cUTF16.GetMulti(auiBuffer, 0x12);
	AssertSize(2, uiCodePointLength);
	AssertShort((uint16)322, *((uint16*)auiBuffer));

	uiPos = cUTF16.GetPosition();
	uiUTF16ElementLength = cUTF16.Peek();
	AssertSize(2, uiPos);
	AssertSize(8, uiUTF16ElementLength);
	memset(auiBuffer, 0, 0x13);
	uiCodePointLength = cUTF16.GetMulti(auiBuffer, 0x12);
	AssertSize(11, uiCodePointLength);
	psz = auiBuffer;
	AssertString("iô", (char*)psz);
	psz = (uint8*)NextString((char*)psz);
	AssertString("ûó", (char*)psz);
	psz = (uint8*)NextString((char*)psz);
	AssertString("°ù", (char*)psz);

	uiPos = cUTF16.GetPosition();
	uiUTF16ElementLength = cUTF16.Peek();
	AssertSize(10, uiPos);
	AssertSize(1, uiUTF16ElementLength);
	memset(auiBuffer, 0, 0x13);
	uiCodePointLength = cUTF16.GetMulti(auiBuffer, 0x12);
	AssertSize(2, uiCodePointLength);
	AssertShort((uint16)322, *((uint16*)auiBuffer));

	uiPos = cUTF16.GetPosition();
	uiUTF16ElementLength = cUTF16.Peek();
	AssertSize(11, uiPos);
	AssertSize(0, uiUTF16ElementLength);
	memset(auiBuffer, 0, 0x13);
	uiCodePointLength = cUTF16.GetMulti(auiBuffer, 0x12);
	AssertSize(0, uiCodePointLength);
	AssertString((char*)auiBuffer, "");
	cUTF16.Kill();

	aui.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUTF16(void)
{
	BeginTests();

	TestUTF16Example1();
	TestUTF16Example2();
	TestUTF16Example3();
	TestUTF16Example4();

	TestStatistics();
}

