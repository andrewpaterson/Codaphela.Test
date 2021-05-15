#include "BaseLib/MapIndexAccess.h"
#include "BaseLib/MapBlock.h"
#include "TestLib/Assert.h"


struct STestMapIndexAccessData
{
	int		ma;
	int		mb;
	int		mc;
	int		md;

	void Init(int a, int b, int c, int d)
	{
		ma = a;
		mb = b;
		mc = c;
		md = d;
	}
};



struct STestMapIndexAccessKey
{
	int		ma;
	short	mb;

	void Init(int a, short b)
	{
		ma = a;
		mb = b;
	}
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapIndexAccessPut(void)
{
	CMapBlock					cMap;
	CMapIndexAccess				cAccess;
	STestMapIndexAccessData		s1;
	STestMapIndexAccessData		s2;
	STestMapIndexAccessData		s3;
	STestMapIndexAccessData		s4;
	STestMapIndexAccessData		s5;
	STestMapIndexAccessData		s6;
	STestMapIndexAccessData		s7;
	STestMapIndexAccessKey		sk1;
	STestMapIndexAccessKey		sk2;
	STestMapIndexAccessKey		sk3;
	STestMapIndexAccessData*	ps;
	STestMapIndexAccessData		sDest;
	size_t						uiSize;
	char						sz[256];


	s1.Init(1, 2, 3, 4);
	s2.Init(5, 6, 7, 8);
	s3.Init(11, 12, 13, 14);
	s4.Init(15, 16, 17, 18);
	s5.Init(21, 22, 23, 24);
	s6.Init(25, 26, 27, 28);
	s7.Init(31, 32, 33, 34);

	sk1.Init(0x10000001, 0x0000);
	sk2.Init(0x10000001, 0x0001);
	sk3.Init(0x10000001, 0x0002);

	cMap.Init();
	cAccess.Init(&cMap);

	AssertTrue(cAccess.PutLongPtr(0x1000000000000001L, &s1));
	AssertTrue(cAccess.PutLongInt(0x1000000000000004L, 102));
	AssertTrue(cAccess.PutLongLong(0x1000000000000006L, 0x1000000000000022L));
	AssertTrue(cAccess.PutLongChar(0x1000000000000003L, 'c'));
	AssertTrue(cAccess.PutLongString(0x1000000000000002L, "Whole Hole"));
	AssertTrue(cAccess.PutLongData(0x1000000000000005L, &s2, sizeof(STestMapIndexAccessData)));
	AssertTrue(cAccess.PutIntPtr(0x10000003, &s3));
	AssertTrue(cAccess.PutIntInt(0x10000001, 101));
	AssertTrue(cAccess.PutIntLong(0x10000004, 0x1000000000000004L));
	AssertTrue(cAccess.PutIntChar(0x10000002, 'd'));
	AssertTrue(cAccess.PutIntString(0x10000005, "Spot the Dog"));
	AssertTrue(cAccess.PutIntData(0x10000006, &s4, sizeof(STestMapIndexAccessData)));
	AssertTrue(cAccess.PutStringPtr("01", &s5));
	AssertTrue(cAccess.PutStringData("02", &s6, sizeof(STestMapIndexAccessData)));
	AssertTrue(cAccess.PutStringChar("1", 'e'));
	AssertTrue(cAccess.PutStringInt("10", 203));
	AssertTrue(cAccess.PutStringLong("11", 0x1000000000000001L));
	AssertTrue(cAccess.PutStringString("12", "Jip the Cat"));
	AssertTrue(cAccess.PutKeyData(&sk1, sizeof(STestMapIndexAccessKey), &s7, sizeof(STestMapIndexAccessData)));
	AssertTrue(cAccess.PutKeyInt(&sk2, sizeof(STestMapIndexAccessKey), 88));
	AssertTrue(cAccess.PutKeyString(&sk3, sizeof(STestMapIndexAccessKey), "Dangerous"));

	ps = (STestMapIndexAccessData*)cAccess.GetLongPtr(0x1000000000000001L);
	AssertPointer(&s1, ps);
	AssertInt(102, cAccess.GetLongInt(0x1000000000000004L));
	AssertLongLongInt(0x1000000000000022L, cAccess.GetLongLong(0x1000000000000006L));
	AssertChar('c', cAccess.GetLongChar(0x1000000000000003L));
	AssertString("Whole Hole", cAccess.GetLongString(0x1000000000000002L, sz, 256));
	AssertTrue(cAccess.GetLongData(0x1000000000000005L, &sDest, &uiSize, sizeof(STestMapIndexAccessData)));
	AssertSize(sizeof(STestMapIndexAccessData), uiSize);
	AssertMemory(&s2, &sDest, sizeof(STestMapIndexAccessData));
	ps = (STestMapIndexAccessData*)cAccess.GetIntPtr(0x10000003);
	AssertPointer(&s3, ps);
	AssertInt(101, cAccess.GetIntInt(0x10000001, 101));
	AssertLongLongInt(0x1000000000000004L, cAccess.GetIntLong(0x10000004));
	AssertChar('d', cAccess.GetIntChar(0x10000002));
	AssertString("Spot the Dog", cAccess.GetIntString(0x10000005, sz, 256));
	AssertTrue(cAccess.GetIntData(0x10000006, &sDest, &uiSize, sizeof(STestMapIndexAccessData)));
	AssertSize(sizeof(STestMapIndexAccessData), uiSize);
	AssertMemory(&s4, &sDest, sizeof(STestMapIndexAccessData));
	ps = (STestMapIndexAccessData*)cAccess.GetStringPtr("01");
	AssertPointer(&s5, ps);
	AssertTrue(cAccess.GetStringData("02", &sDest, &uiSize, sizeof(STestMapIndexAccessData)));
	AssertSize(sizeof(STestMapIndexAccessData), uiSize);
	AssertMemory(&s6, &sDest, sizeof(STestMapIndexAccessData));
	AssertChar('e', cAccess.GetStringChar("1"));
	AssertInt(203, cAccess.GetStringInt("10"));
	AssertLongLongInt(0x1000000000000001L, cAccess.GetStringLong("11"));
	AssertString("Jip the Cat", cAccess.GetStringString("12", sz, 256));
	AssertTrue(cAccess.GetKeyData(&sk1, sizeof(STestMapIndexAccessKey), &sDest, &uiSize, sizeof(STestMapIndexAccessData)));
	AssertSize(sizeof(STestMapIndexAccessData), uiSize);
	AssertMemory(&s7, &sDest, sizeof(STestMapIndexAccessData));
	AssertInt(88, cAccess.GetKeyInt(&sk2, sizeof(STestMapIndexAccessKey)));
	AssertString("Dangerous", cAccess.GetKeyString(&sk3, sizeof(STestMapIndexAccessKey), sz, 256));
			
	cAccess.Kill();
	cMap.Kill();
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapIndexAccess(void)
{
	BeginTests();

	TestMapIndexAccessPut();

	TestStatistics();
}


