#include "BaseLib/IndexTreeBlockMemory.h"
#include "BaseLib/TrackingAllocator.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryFile.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemoryAdd(void)
{
	CIndexTreeBlockMemory	cIndex;
	CTestIndexTreeObject	a;
	CTestIndexTreeObject	aa;
	CTestIndexTreeObject	temp;
	CArrayVoidPtr			avp;
	BOOL					bResult;
	CIndexTreeNodeMemory*	pcNode;
	CTestIndexTreeObject**	ppvTest;
	CTestIndexTreeObject***	ppvTestA;
	CTestIndexTreeObject***	ppvTestAA;

	cIndex.Init();
	a.Init("A");
	bResult = cIndex.PutPtr(a.GetName(), &a);
	AssertTrue(bResult);

	pcNode = cIndex.GetIndexNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&a, *ppvTest);

	aa.Init("AA");
	bResult = cIndex.PutPtr(aa.GetName(), &aa);
	AssertTrue(bResult);

	pcNode = cIndex.GetIndexNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&a, *ppvTest);

	pcNode = cIndex.GetIndexNode("AA", 2);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&aa, *ppvTest);

	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(2, avp.NumElements());
	ppvTestA = (CTestIndexTreeObject***)avp.Get(0);
	ppvTestAA = (CTestIndexTreeObject***)avp.Get(1);
	AssertPointer(&a, **ppvTestA);
	AssertPointer(&aa, **ppvTestAA);
	AssertString("A", (**ppvTestA)->mszName);
	AssertString("AA", (**ppvTestAA)->mszName);

	avp.Kill();
	cIndex.Kill();

	cIndex.Init();
	bResult = cIndex.PutPtr(NULL, &temp);
	AssertFalse(bResult);
	bResult = cIndex.PutPtr("", &temp);
	AssertFalse(bResult);

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemoryGet(void)
{
	CIndexTreeBlockMemory	cIndex;
	CTestIndexTreeObject	andrew;
	CTestIndexTreeObject**	pcResult;
	CArrayVoidPtr			avp;
	CTestIndexTreeObject	batman;
	CTestIndexTreeObject	batmam;
	CTestIndexTreeObject	andre;
	CIndexTreeNodeMemory*	pcNodeBatman;
	CIndexTreeNodeMemory*	pcNodeBatmam;
	char*					szBatmam;

	cIndex.Init();

	andrew.Init("Andrew");
	cIndex.PutPtr(andrew.GetName(), &andrew);
	pcResult = (CTestIndexTreeObject**)cIndex.Get("Andrew");
	AssertPointer(*pcResult, &andrew);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(1, avp.NumElements());
	avp.Kill();

	batman.Init("Batman");
	cIndex.PutPtr(batman.GetName(), &batman);
	pcNodeBatman = cIndex.GetIndexNode("Batman", 6);
	AssertInt(0, pcNodeBatman->GetNumIndexes());
	pcResult = (CTestIndexTreeObject**)cIndex.Get("Batman");
	AssertPointer(*pcResult, &batman);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(2, avp.NumElements());
	avp.Kill();

	szBatmam = "Batmam";
	batmam.Init(szBatmam);
	cIndex.PutPtr(szBatmam, &batmam);
	pcNodeBatman = cIndex.GetIndexNode("Batman", 6);
	pcNodeBatmam = cIndex.GetIndexNode(szBatmam, 6);
	pcResult = (CTestIndexTreeObject**)cIndex.Get(szBatmam);
	AssertPointer(&batmam, *pcResult);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(3, avp.NumElements());
	avp.Kill();

	andre.Init("Andre");
	cIndex.PutPtr(andre.GetName(), &andre);
	pcResult = (CTestIndexTreeObject**)cIndex.Get("Andre");
	AssertPointer(&andre, *pcResult);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(4, avp.NumElements());
	avp.Kill();

	AssertNull(cIndex.Get(NULL));
	AssertNull(cIndex.Get(""));
	AssertNull(cIndex.Get("Batma"));
	AssertNull(cIndex.Get("Batmano"));
	AssertNull(cIndex.Get("Batmao"));

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemoryPutDuplicate(void)
{
	CIndexTreeBlockMemory	cIndex;
	CTestIndexTreeObject	andrew;
	CTestIndexTreeObject	andrewToo;
	CTestIndexTreeObject**	pcResult;
	CArrayVoidPtr			avp;
	BOOL					bResult;

	cIndex.Init();

	andrew.Init("Andrew");
	bResult = cIndex.PutPtr(andrew.mszName, &andrew);
	AssertTrue(bResult);

	andrewToo.Init("Andrew");
	bResult = cIndex.PutPtr(andrewToo.GetName(), &andrewToo);
	AssertFalse(bResult);

	pcResult = (CTestIndexTreeObject**)cIndex.Get("Andrew");
	AssertPointer(&andrew, *pcResult);

	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(1, avp.NumElements());
	avp.Kill();

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemoryValidateInternalConsistency(void)
{
	CIndexTreeBlockMemory	cIndex;
	CTestIndexTreeObject	cObject;
	CTestIndexTreeObject	cType;
	CArrayVoidPtr			avp;

	cIndex.Init();

	cObject.Init("");

	cIndex.PutPtr("tonic", &cObject);
	cIndex.PutPtr("topia", &cObject);
	cIndex.PutPtr("topic", &cObject);
	cIndex.PutPtr("totem", &cObject);
	cIndex.PutPtr("tower", &cObject);
	cIndex.PutPtr("tracter", &cObject);
	cIndex.PutPtr("traction", &cObject);
	cIndex.PutPtr("trahend", &cObject);
	cIndex.PutPtr("translucence", &cObject);
	cIndex.PutPtr("translucency", &cObject);
	cIndex.PutPtr("transparentness", &cObject);
	cIndex.PutPtr("tread", &cObject);
	cIndex.PutPtr("treasurer", &cObject);
	cIndex.PutPtr("treasurership", &cObject);
	cIndex.PutPtr("treasury", &cObject);
	cIndex.PutPtr("trench", &cObject);
	cIndex.PutPtr("triangularity", &cObject);
	cIndex.PutPtr("tribe", &cObject);
	cIndex.PutPtr("triplication", &cObject);
	cIndex.PutPtr("truncation", &cObject);
	cIndex.PutPtr("trunk", &cObject);
	cIndex.PutPtr("tunic", &cObject);
	cIndex.PutPtr("tunnel", &cObject);
	cIndex.PutPtr("tutor", &cObject);
	cIndex.PutPtr("tutorship", &cObject);

	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tonic"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("topia"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("topic"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("totem"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tower"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tracter"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("traction"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("trahend"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("translucence"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("translucency"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("transparentness"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tread"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("treasurer"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("treasurership"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("treasury"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("trench"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("triangularity"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tribe"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("triplication"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("truncation"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("trunk"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tunic"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tunnel"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tutor"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tutorship"));

	cType.Init("type");
	cIndex.PutPtr(cType.GetName(), &cType);

	AssertPointer(&cType, *(CTestIndexTreeObject**)cIndex.Get("type"));

	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(26, avp.NumElements());
	avp.Kill();

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemoryCountAllocatedNodes(void)
{
	CIndexTreeBlockMemory	cIndex;
	CTestIndexTreeObject	cZebra;
	CTestIndexTreeObject	cAardvark;
	CTestIndexTreeObject	cAardvar;
	CTestIndexTreeObject	cAardvarc;
	CTestIndexTreeObject**	pvResult;

	cIndex.Init();

	AssertInt(1, cIndex.CountAllocatedNodes());

	cZebra.Init("Zebra");
	cAardvark.Init("Aardvark");
	cAardvar.Init("Aardvar");
	cAardvarc.Init("Aardvarc");

	cIndex.PutPtr(cZebra.GetName(), &cZebra);
	pvResult = (CTestIndexTreeObject**)cIndex.Get("Zebra");
	AssertPointer(&cZebra, *pvResult);
	AssertInt(6, cIndex.CountAllocatedNodes());

	cIndex.PutPtr(cAardvark.GetName(), &cAardvark);
	pvResult = (CTestIndexTreeObject**)cIndex.Get("Aardvark");
	AssertPointer(&cAardvark, *pvResult);
	AssertInt(14, cIndex.CountAllocatedNodes());

	cIndex.PutPtr(cAardvar.GetName(), &cAardvar);
	pvResult = (CTestIndexTreeObject**)cIndex.Get("Aardvar");
	AssertPointer(&cAardvar, *pvResult);
	AssertInt(14, cIndex.CountAllocatedNodes());

	cIndex.PutPtr(cAardvarc.GetName(), &cAardvarc);
	pvResult = (CTestIndexTreeObject**)cIndex.Get("Aardvarc");
	AssertPointer(&cAardvarc, *pvResult);
	AssertInt(15, cIndex.CountAllocatedNodes());

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemoryRemoveByObject(void)
{
	CIndexTreeBlockMemory	cIndex;
	CTestIndexTreeObject	object1;
	CTestIndexTreeObject	object2;
	CTestIndexTreeObject	object3;
	CTestIndexTreeObject**	ppcRemoved;

	cIndex.Init();

	AssertInt(1, cIndex.CountAllocatedNodes());

	object1.Init("denarii");
	cIndex.PutPtr(object1.GetName(), &object1);
	AssertInt(8, cIndex.CountAllocatedNodes());

	object2.Init("dendrodra");
	cIndex.PutPtr(object2.GetName(), &object2);

	object3.Init("dendrons");
	cIndex.PutPtr(object3.GetName(), &object3);

	AssertInt(3, cIndex.NumElements());
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Get(object2.GetName());
	AssertPointer(&object2, *ppcRemoved);
	AssertTrue(cIndex.Remove(object2.GetName()));
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Get(object2.GetName());
	AssertNull(ppcRemoved);
	AssertInt(2, cIndex.NumElements());
	AssertFalse(cIndex.Remove(object2.GetName()));
	AssertInt(2, cIndex.NumElements());

	AssertInt(13, cIndex.CountAllocatedNodes());
	cIndex.Remove(object3.GetName());

	AssertInt(1, cIndex.NumElements());
	AssertInt(8, cIndex.CountAllocatedNodes());

	cIndex.PutPtr(object3.GetName(), &object3);
	AssertInt(13, cIndex.CountAllocatedNodes());

	AssertInt(2, cIndex.NumElements());
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Get(object3.GetName());
	AssertPointer(&object3, *ppcRemoved);
	AssertTrue(cIndex.Remove(object3.GetName()));
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Get(object3.GetName());
	AssertNull(ppcRemoved);
	AssertInt(1, cIndex.NumElements());
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Get(object1.GetName());
	AssertPointer(&object1, *ppcRemoved);
	AssertTrue(cIndex.Remove(object1.GetName()));
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Get(object1.GetName());
	AssertNull(ppcRemoved);
	AssertInt(0, cIndex.NumElements());

	AssertFalse(cIndex.Remove(NULL));
	AssertFalse(cIndex.Remove(""));

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemoryHasKey(void)
{
	CIndexTreeBlockMemory	cIndex;
	CTestIndexTreeObject	cObject;

	cIndex.Init();
	cObject.Init("Not Important");

	cIndex.PutPtr("fabaceous", &cObject);
	cIndex.PutPtr("fabled", &cObject);
	cIndex.PutPtr("fabricative", &cObject);
	cIndex.PutPtr("fabulous", &cObject);
	cIndex.PutPtr("face-centered", &cObject);
	cIndex.PutPtr("face-centred", &cObject);
	cIndex.PutPtr("face-saving", &cObject);
	cIndex.PutPtr("faceable", &cObject);
	cIndex.PutPtr("faceless", &cObject);
	cIndex.PutPtr("facete", &cObject);
	cIndex.PutPtr("facetious", &cObject);
	cIndex.PutPtr("facile", &cObject);

	AssertFalse(cIndex.HasKey(NULL));
	AssertFalse(cIndex.HasKey(""));
	AssertFalse(cIndex.HasKey(" "));
	AssertFalse(cIndex.HasKey("fab"));
	AssertFalse(cIndex.HasKey("facilee"));

	AssertInt(13, cIndex.GetLargestKeySize());

	AssertTrue(cIndex.HasKey("fabricative"));
	AssertTrue(cIndex.HasKey("fabled"));
	AssertTrue(cIndex.HasKey("fabulous"));
	AssertTrue(cIndex.HasKey("face-centered"));
	AssertTrue(cIndex.HasKey("fabaceous"));
	AssertTrue(cIndex.HasKey("face-centred"));
	AssertTrue(cIndex.HasKey("face-saving"));
	AssertTrue(cIndex.HasKey("faceable"));
	AssertTrue(cIndex.HasKey("faceless"));
	AssertTrue(cIndex.HasKey("facete"));
	AssertTrue(cIndex.HasKey("facetious"));
	AssertTrue(cIndex.HasKey("facile"));

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemoryRemoveNullNode(void)
{
	CIndexTreeBlockMemory	cIndex;
	CTestIndexTreeObject	cObject;

	cIndex.Init();
	cObject.Init("Not Important");

	cIndex.PutPtr("aaa", &cObject);
	cIndex.PutPtr("aab", &cObject);

	AssertInt(2, cIndex.NumElements());
	AssertInt(2, cIndex.RecurseSize());

	cIndex.Remove("a");

	AssertInt(2, cIndex.NumElements());
	AssertInt(2, cIndex.RecurseSize());

	cIndex.Remove("aaa");

	AssertInt(1, cIndex.NumElements());
	AssertInt(1, cIndex.RecurseSize());

	cIndex.Remove("aaa");

	AssertInt(1, cIndex.NumElements());
	AssertInt(1, cIndex.RecurseSize());

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemoryAddLongLong(void)
{
	CIndexTreeBlockMemory	cIndex;
	long long				li;
	long long*				pli;

	cIndex.Init();

	li = 0x88LL;
	cIndex.Put("GraphRoot", &li, sizeof(long long));
	pli = (long long*)cIndex.Get("GraphRoot");
	AssertLongLongInt(li, *pli);

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemoryRemoveResize(void)
{
	CIndexTreeBlockMemory	cIndex;
	long long				li;
	CMemoryAllocator		cMemoryAlloc;
	CTrackingAllocator		cTrackingAlloc;
	int						iExpectedRootSize;

	cMemoryAlloc.Init();
	cTrackingAlloc.Init(&cMemoryAlloc);

	cIndex.Init(&cTrackingAlloc);
	AssertInt(1, cIndex.CountAllocatedNodes());
	AssertInt(0, cIndex.RecurseSize());
	iExpectedRootSize = sizeof(CIndexTreeNodeMemory*) * MAX_UCHAR + sizeof(CIndexTreeNodeMemory);
	AssertInt(1028, iExpectedRootSize);
	AssertInt(iExpectedRootSize, cTrackingAlloc.AllocatedSize());

	li = 0x77LL; cIndex.Put("M", &li, sizeof(long long));
	AssertInt(2, cIndex.CountAllocatedNodes());
	AssertInt(1, cIndex.RecurseSize());
	AssertInt(1044, iExpectedRootSize + sizeof(CIndexTreeNodeMemory) + sizeof(long long));
	AssertInt(1044, cTrackingAlloc.AllocatedSize());

	li = 0x88LL; cIndex.Put("MA", &li, sizeof(long long));
	AssertInt(1064, cTrackingAlloc.AllocatedSize());
	li = 0x99LL; cIndex.Put("MC", &li, sizeof(long long));
	AssertInt(4, cIndex.CountAllocatedNodes());
	AssertInt(3, cIndex.RecurseSize());
	AssertInt(1088, cTrackingAlloc.AllocatedSize());

	li = 0xaaLL; cIndex.Put("MB", &li, sizeof(long long));
	AssertInt(5, cIndex.CountAllocatedNodes());
	AssertInt(4, cIndex.RecurseSize());
	AssertInt(1104, cTrackingAlloc.AllocatedSize());

	li = 0xbbLL; cIndex.Put("MBP", &li, sizeof(long long));
	AssertInt(6, cIndex.CountAllocatedNodes());
	AssertInt(5, cIndex.RecurseSize());
	AssertInt(5, cIndex.NumElements());
	AssertInt(1124, cTrackingAlloc.AllocatedSize());

	AssertLongLongInt(0xaaLL, *((long long*)cIndex.Get("MB")));
	cIndex.Remove("MB");
	AssertInt(6, cIndex.CountAllocatedNodes());
	AssertInt(4, cIndex.RecurseSize());
	AssertInt(4, cIndex.NumElements());
	AssertInt(1124, cTrackingAlloc.AllocatedSize());
	AssertNull(cIndex.Get("MB"));

	AssertLongLongInt(0xbbLL, *((long long*)cIndex.Get("MBP")));
	cIndex.Remove("MBP");
	AssertInt(4, cIndex.CountAllocatedNodes());
	AssertInt(3, cIndex.RecurseSize());
	AssertInt(3, cIndex.NumElements());
	AssertInt(1088, cTrackingAlloc.AllocatedSize());
	AssertNull(cIndex.Get("MBP"));

	AssertLongLongInt(0x99LL, *((long long*)cIndex.Get("MC")));
	AssertLongLongInt(0x88LL, *((long long*)cIndex.Get("MA")));
	cIndex.Remove("MA");
	AssertInt(3, cIndex.CountAllocatedNodes());
	AssertInt(2, cIndex.RecurseSize());
	AssertInt(2, cIndex.NumElements());
	AssertInt(1064, cTrackingAlloc.AllocatedSize());
	AssertNull(cIndex.Get("MA"));

	AssertLongLongInt(0x99LL, *((long long*)cIndex.Get("MC")));
	cIndex.Remove("MC");
	AssertInt(2, cIndex.CountAllocatedNodes());
	AssertInt(1, cIndex.RecurseSize());
	AssertInt(1, cIndex.NumElements());
	AssertInt(1044, cTrackingAlloc.AllocatedSize());
	AssertNull(cIndex.Get("MC"));

	AssertLongLongInt(0x77LL, *((long long*)cIndex.Get("M")));
	cIndex.Remove("M");
	AssertInt(1, cIndex.CountAllocatedNodes());
	AssertInt(0, cIndex.RecurseSize());
	AssertInt(0, cIndex.NumElements());
	AssertInt(1028, cTrackingAlloc.AllocatedSize());
	AssertNull(cIndex.Get("M"));

	cIndex.Kill();
	cTrackingAlloc.Kill();
	cMemoryAlloc.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemoryIterate(void)
{
	CFileBasic				cFile;
	CIndexTreeBlockMemory	cIndex;
	SIndexTreeIterator		sIter;
	char*					szData;
	int						iDataSize;
	unsigned char			c;
	char					szKey[1024];
	int						iKeySize;

	cIndex.Init();
	cIndex.Put("AAA", "DENISA", 7);
	cIndex.Put("AA", "FATJETA", 8);
	cIndex.Put("AAB", "ARIANA", 7);
	cIndex.Put("AAC", "GEORGE", 7);
	cIndex.Put("AB", "IRMA", 5);
	cIndex.Put("ABA", "JULIANA", 8);
	cIndex.Put("ABB", "LULE", 5);
	cIndex.Put("C", "VENERA", 7);
	cIndex.Put("DDDD", "PRANVERA", 9);
	cIndex.Put("DD", "PRIMERA", 8);
	AssertInt(14, cIndex.CountAllocatedNodes());
	AssertInt(10, cIndex.RecurseSize());
	AssertInt(10, cIndex.NumElements());
	AssertInt(4, cIndex.GetLargestKeySize());

	AssertTrue(cIndex.StartIteration(&sIter, (void**)&szData, &iDataSize));
	AssertInt(8, iDataSize);
	AssertString("FATJETA", szData);
	iKeySize = cIndex.GetKey(szKey, szData, TRUE);
	AssertInt(2, iKeySize);
	AssertString("AA", szKey);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("DENISA", szData);
	AssertInt(3, cIndex.GetKey(szKey, szData, TRUE));
	AssertString("AAA", szKey);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("ARIANA", szData);
	AssertInt(3, cIndex.GetKey(szKey, szData, TRUE));
	AssertString("AAB", szKey);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("GEORGE", szData);
	AssertInt(3, cIndex.GetKey(szKey, szData, TRUE));
	AssertString("AAC", szKey);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(5, iDataSize);
	AssertString("IRMA", szData);
	AssertInt(2, cIndex.GetKey(szKey, szData, TRUE));
	AssertString("AB", szKey);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(8, iDataSize);
	AssertString("JULIANA", szData);
	AssertInt(3, cIndex.GetKey(szKey, szData, TRUE));
	AssertString("ABA", szKey);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(5, iDataSize);
	AssertString("LULE", szData);
	AssertInt(3, cIndex.GetKey(szKey, szData, TRUE));
	AssertString("ABB", szKey);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("VENERA", szData);
	AssertInt(1, cIndex.GetKey(szKey, szData, TRUE));
	AssertString("C", szKey);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(8, iDataSize);
	AssertString("PRIMERA", szData);
	AssertInt(2, cIndex.GetKey(szKey, szData, TRUE));
	AssertString("DD", szKey);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(9, iDataSize);
	AssertString("PRANVERA", szData);
	AssertInt(4, cIndex.GetKey(szKey, szData, TRUE));
	AssertString("DDDD", szKey);

	AssertFalse(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	cIndex.Kill();

	cIndex.Init();
	AssertInt(1, cIndex.CountAllocatedNodes());
	AssertInt(0, cIndex.RecurseSize());
	AssertInt(0, cIndex.NumElements());

	AssertFalse(cIndex.StartIteration(&sIter, (void**)&szData, &iDataSize));
	cIndex.Kill();

	cIndex.Init();
	c = 255;
	cIndex.Put(&c, 1, "Banks", 6);
	AssertString("Banks", (char*)cIndex.Get(&c, 1));
	AssertTrue(cIndex.StartIteration(&sIter, (void**)&szData, &iDataSize));
	AssertInt(6, iDataSize);
	AssertString("Banks", szData);

	AssertFalse(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	cIndex.Kill();

	cIndex.Init();
	c = 0;
	cIndex.Put(&c, 1, "Planks", 7);
	AssertString("Planks", (char*)cIndex.Get(&c, 1));
	AssertTrue(cIndex.StartIteration(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("Planks", szData);

	AssertFalse(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemoryReadWrite(void)
{
	CFileBasic				cFile;
	CIndexTreeBlockMemory	cIndex;
	CIndexTreeBlockMemory	cIndexIn;

	cIndex.Init();
	cIndex.Put("AAA", "DENISA", 7);
	cIndex.Put("AA", "FATJETA", 8);
	cIndex.Put("AAB", "ARIANA", 7);
	cIndex.Put("AAC", "GEORGE", 7);
	cIndex.Put("AB", "IRMA", 5);
	cIndex.Put("ABA", "JULIANA", 8);
	cIndex.Put("ABB", "LULE", 5);
	cIndex.Put("C", "VENERA", 7);
	cIndex.Put("DDDD", "PRANVERA", 9);
	cIndex.Put("DD", "PRIMERA", 8);
	AssertInt(14, cIndex.CountAllocatedNodes());
	AssertInt(10, cIndex.RecurseSize());
	AssertInt(10, cIndex.NumElements());
	AssertInt(4, cIndex.GetLargestKeySize());

	cFile.Init(MemoryFile());
	cFile.Open(EFM_Write_Create);
	AssertTrue(cIndex.Write(&cFile));
	cIndex.Kill();
	cFile.Close();

	cFile.Open(EFM_Read);
	AssertTrue(cIndexIn.Read(&cFile));
	cFile.Close();

	AssertInt(14, cIndexIn.CountAllocatedNodes());
	AssertInt(10, cIndexIn.RecurseSize());
	AssertInt(10, cIndexIn.NumElements());
	AssertInt(4, cIndexIn.GetLargestKeySize());
	AssertString("DENISA", (char*)cIndexIn.Get("AAA"));
	AssertString("FATJETA", (char*)cIndexIn.Get("AA"));
	AssertString("ARIANA", (char*)cIndexIn.Get("AAB"));
	AssertString("GEORGE", (char*)cIndexIn.Get("AAC"));
	AssertString("IRMA", (char*)cIndexIn.Get("AB"));
	AssertString("JULIANA", (char*)cIndexIn.Get("ABA"));
	AssertString("LULE", (char*)cIndexIn.Get("ABB"));
	AssertString("VENERA", (char*)cIndexIn.Get("C"));
	AssertString("PRANVERA", (char*)cIndexIn.Get("DDDD"));
	AssertString("PRIMERA", (char*)cIndexIn.Get("DD"));

	cIndexIn.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockMemory(void)
{
	BeginTests();
	FastFunctionsInit();
	MemoryInit();

	TestIndexTreeBlockMemoryAdd();
	TestIndexTreeBlockMemoryGet();
	TestIndexTreeBlockMemoryPutDuplicate();
	TestIndexTreeBlockMemoryValidateInternalConsistency();
	TestIndexTreeBlockMemoryCountAllocatedNodes();
	TestIndexTreeBlockMemoryRemoveResize();
	TestIndexTreeBlockMemoryRemoveByObject();
	TestIndexTreeBlockMemoryHasKey();
	TestIndexTreeBlockMemoryRemoveNullNode();
	TestIndexTreeBlockMemoryAddLongLong();
	TestIndexTreeBlockMemoryIterate();
	TestIndexTreeBlockMemoryReadWrite();

	MemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

