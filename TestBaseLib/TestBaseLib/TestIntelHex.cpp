#include "BaseLib/IntelHex.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
// Data records joined across an extended segment address record (02) and
// out of order behind an extended linear address record (04).
//
//////////////////////////////////////////////////////////////////////////
void TestIntelHexParse(void)
{
	CIntelHex	cHex;
	uint8		uiByte;
	uint8		auiBytes[8];

	cHex.Init();
	AssertTrue(cHex.Parse(
		":020000021000EC\r\n"
		":0400000001020304F2\r\n"
		"\r\n"
		":02000004000AF0\n"
		":02000400AABB95\n"
		":02000200CCDD53\n"
		":0400000500000000F7\n"
		":00000001FF\n"));
	AssertString("", cHex.GetError());
	AssertSize(2, cHex.NumSegments());
	AssertIntHex(0x10000, cHex.GetSegment(0)->uiAddress);
	AssertSize(4, cHex.GetSegment(0)->cBytes.NumElements());
	AssertIntHex(0xA0002, cHex.GetSegment(1)->uiAddress);
	AssertSize(4, cHex.GetSegment(1)->cBytes.NumElements());
	AssertIntHex(0x10000, cHex.GetLowAddress());
	AssertLongLongIntHex(0xA0006LL, cHex.GetEndAddress());
	AssertFalse(cHex.IsEmpty());

	AssertTrue(cHex.Get(0x10003, &uiByte));
	AssertByteHex((uint8)0x04, uiByte);
	AssertTrue(cHex.Get(0xA0004, &uiByte));
	AssertByteHex((uint8)0xAA, uiByte);
	AssertFalse(cHex.Get(0xA0001, &uiByte));
	AssertFalse(cHex.Get(0xA0006, &uiByte));

	cHex.Fill(0xA0000, 8, 0xFF, auiBytes);
	AssertByteHex((uint8)0xFF, auiBytes[0]);
	AssertByteHex((uint8)0xFF, auiBytes[1]);
	AssertByteHex((uint8)0xCC, auiBytes[2]);
	AssertByteHex((uint8)0xDD, auiBytes[3]);
	AssertByteHex((uint8)0xAA, auiBytes[4]);
	AssertByteHex((uint8)0xBB, auiBytes[5]);
	AssertByteHex((uint8)0xFF, auiBytes[6]);
	AssertByteHex((uint8)0xFF, auiBytes[7]);

	cHex.Fill(0x0FFFE, 4, 0x00, auiBytes);
	AssertByteHex((uint8)0x00, auiBytes[1]);
	AssertByteHex((uint8)0x01, auiBytes[2]);
	AssertByteHex((uint8)0x02, auiBytes[3]);
	cHex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AssertIntelHexError(const char* szExpected, const char* szText)
{
	CIntelHex	cHex;

	cHex.Init();
	AssertFalse(cHex.Parse(szText));
	AssertString(szExpected, cHex.GetError());
	AssertTrue(cHex.IsEmpty());
	cHex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntelHexErrors(void)
{
	AssertIntelHexError("Line 1: Bad checksum", ":0400000001020304F3\n:00000001FF\n");
	AssertIntelHexError("Line 2: A record must start with ':'", ":0400000001020304F2\n0400000001020304F2\n");
	AssertIntelHexError("Line 1: Bad hex digit", ":04000000010203G4F2\n:00000001FF\n");
	AssertIntelHexError("Line 1: Byte count does not match the record", ":0500000001020304F1\n:00000001FF\n");
	AssertIntelHexError("Line 1: Bad record length", ":0400000001020304F\n:00000001FF\n");
	AssertIntelHexError("Line 1: Unknown record type", ":00000006FA\n:00000001FF\n");
	AssertIntelHexError("Line 2: No end of file record", ":0400000001020304F2\n");
	AssertIntelHexError("Line 2: Record after the end of file record", ":00000001FF\n:0400000001020304F2\n");
	AssertIntelHexError("Line 1: An address record must have 2 bytes", ":0100000210ED\n:00000001FF\n");
	AssertIntelHexError("Address 00000002 is given more than once", ":0400000001020304F2\n:020002000506F1\n:00000001FF\n");
}


//////////////////////////////////////////////////////////////////////////
//
// A file: Input/IntelHex/Small.hex has DE AD BE EF at $10 and CA FE at $16.
//
//////////////////////////////////////////////////////////////////////////
void TestIntelHexRead(void)
{
	CIntelHex	cHex;
	uint8		auiBytes[8];

	cHex.Init();
	AssertTrue(cHex.Read("Input" _FS_ "IntelHex" _FS_ "Small.hex"));
	AssertString("", cHex.GetError());
	AssertSize(2, cHex.NumSegments());
	AssertIntHex((uint32)0x10, cHex.GetLowAddress());
	AssertLongLongIntHex(0x18LL, cHex.GetEndAddress());
	cHex.Fill(0x10, 8, 0xFF, auiBytes);
	AssertByteHex((uint8)0xDE, auiBytes[0]);
	AssertByteHex((uint8)0xEF, auiBytes[3]);
	AssertByteHex((uint8)0xFF, auiBytes[4]);
	AssertByteHex((uint8)0xFF, auiBytes[5]);
	AssertByteHex((uint8)0xCA, auiBytes[6]);
	AssertByteHex((uint8)0xFE, auiBytes[7]);

	AssertFalse(cHex.Read("Input" _FS_ "IntelHex" _FS_ "Missing.hex"));
	AssertString("Could not read Input" _FS_ "IntelHex" _FS_ "Missing.hex", cHex.GetError());
	AssertTrue(cHex.IsEmpty());
	cHex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntelHex(void)
{
	BeginTests();

	TestIntelHexParse();
	TestIntelHexErrors();
	TestIntelHexRead();

	TestStatistics();
}
