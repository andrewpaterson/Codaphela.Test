#include "BaseLib/IndexTreeMemory.h"
#include "BaseLib/IndexTreeMemoryAccess.h"
#include "BaseLib/TrackingAllocator.h"
#include "BaseLib/CountingAllocator.h"
#include "BaseLib/CreationDataOrderer.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/Logger.h"
#include "BaseLib/LocalMallocatorConstructors.h"
#include "BaseLib/DataOrderers.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeObject.h"
#include "TestIndexTreeMemory.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryKill(void)
{
	CIndexTreeMemory	cIndex;

	cIndex.Init();
	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryDescribeNode(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	CIndexTreeNodeMemory**	pcChildNodes;
	CIndexTreeNodeMemory*	pcNode;

	cIndex.Init();
	cAccess.Init(&cIndex);

	cAccess.PutStringString("zx", "Jackrabbit");

	pcNode = cIndex.GetNode("zx", 2);
	AssertNotNull(pcNode);
	AssertFalse(pcNode->HasNodes());
	AssertTrue(pcNode->HasData());
	Pass();

	AssertShort(11, pcNode->GetDataSize());
	AssertString("Jackrabbit", (char*)pcNode->GetDataPtr());
	pcChildNodes = (CIndexTreeNodeMemory**)pcNode->GetNodesMemory();
	AssertNull(pcChildNodes);

	cIndex.Kill();
	cAccess.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryAdd(EIndexKeyReverse eKeyReverse)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	CTestIndexTreeObject	a;
	CTestIndexTreeObject	aa;
	CTestIndexTreeObject	temp;
	CArrayVoidPtr			avp;
	BOOL					bResult;
	CIndexTreeNodeMemory*	pcNode;
	CTestIndexTreeObject**	ppvTest;
	CTestIndexTreeObject***	ppvTestA;
	CTestIndexTreeObject***	ppvTestAA;
	SLogConfig				sLogConfig;

	cIndex.Init(eKeyReverse);
	cAccess.Init(&cIndex);
	a.Init("A");
	bResult = cAccess.PutStringPtr(a.GetName(), &a);
	AssertTrue(bResult);

	pcNode = cIndex.GetNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetDataPtr();
	AssertPointer(&a, *ppvTest);

	aa.Init("AB");
	bResult = cAccess.PutStringPtr(aa.GetName(), &aa);
	AssertTrue(bResult);

	pcNode = cIndex.GetNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetDataPtr();
	AssertPointer(&a, *ppvTest);

	pcNode = cIndex.GetNode("AB", 2);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetDataPtr();
	AssertPointer(&aa, *ppvTest);

	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(2, avp.NumElements());
	ppvTestA = (CTestIndexTreeObject***)avp.Get(0);
	ppvTestAA = (CTestIndexTreeObject***)avp.Get(1);
	AssertPointer(&a, **ppvTestA);
	AssertPointer(&aa, **ppvTestAA);
	AssertString("A", (**ppvTestA)->mszName);
	AssertString("AB", (**ppvTestAA)->mszName);

	cIndex.ValidateIndexTree();

	avp.Kill();
	cIndex.Kill();

	cIndex.Init(eKeyReverse);
	sLogConfig = gcLogger.SetSilent();
	bResult = cAccess.PutStringPtr(NULL, &temp);
	gcLogger.SetConfig(&sLogConfig);
	AssertFalse(bResult);
	sLogConfig = gcLogger.SetSilent();
	bResult = cAccess.PutStringPtr("", &temp);
	gcLogger.SetConfig(&sLogConfig);
	AssertFalse(bResult);

	cIndex.Kill();
	cAccess.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryAddDataOnExistingKey(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	char					sz[256];
	CIndexTreeNodeMemory*	pcNode;

	cIndex.Init();
	cAccess.Init(&cIndex);

	cAccess.PutStringString("zx", "Jackrabbit");
	cAccess.PutStringString("z", "Dukeling");
	AssertString("Jackrabbit", cAccess.GetStringString("zx", sz));
	AssertString("Dukeling", cAccess.GetStringString("z", sz));
	pcNode = cIndex.GetNode("z", 1);
	AssertTrue(pcNode->HasData());
	AssertTrue(pcNode->HasNodes());
	Pass();

	cAccess.PutStringString("z", "Big Dukeling of Doom");
	AssertString("Jackrabbit", cAccess.GetStringString("zx", sz));
	AssertString("Big Dukeling of Doom", cAccess.GetStringString("z", sz));
	pcNode = cIndex.GetNode("z", 1);
	AssertTrue(pcNode->HasData());
	AssertTrue(pcNode->HasNodes());
	Pass();

	cAccess.PutStringString("z", "o");
	AssertString("Jackrabbit", cAccess.GetStringString("zx", sz));
	AssertString("o", cAccess.GetStringString("z", sz));
	pcNode = cIndex.GetNode("z", 1);
	AssertTrue(pcNode->HasData());
	AssertTrue(pcNode->HasNodes());
	Pass();

	cAccess.DeleteString("z");
	AssertString("Jackrabbit", cAccess.GetStringString("zx", sz));
	AssertNull(cAccess.GetStringString("z", sz));
	pcNode = cIndex.GetNode("z", 1);
	AssertFalse(pcNode->HasData());
	AssertTrue(pcNode->HasNodes());
	Pass();

	cAccess.PutStringString("z", "Dukeling");
	AssertString("Jackrabbit", cAccess.GetStringString("zx", sz));
	AssertString("Dukeling", cAccess.GetStringString("z", sz));
	pcNode = cIndex.GetNode("z", 1);
	AssertTrue(pcNode->HasData());
	AssertTrue(pcNode->HasNodes());
	Pass();

	cAccess.DeleteString("z");
	cAccess.DeleteString("zx");
	AssertNull(cAccess.GetStringString("zx", sz));
	pcNode = cIndex.GetNode("z", 1);
	AssertNull(pcNode);
	AssertInt(0, cIndex.NumElements());
	Pass();

	cIndex.Kill();
	cAccess.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryGet(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	CTestIndexTreeObject	cAndrew;
	CTestIndexTreeObject*	pcResult;
	CArrayVoidPtr			avp;
	CTestIndexTreeObject	batman;
	CTestIndexTreeObject	batmam;
	CTestIndexTreeObject	andre;
	CIndexTreeNodeMemory*	pcNodeBatman;
	CIndexTreeNodeMemory*	pcNodeBatmam;
	char*					szBatmam;
	CIndexTreeNodeMemory*	pcNodeAndre;
	CIndexTreeNodeMemory*	pcNodeAndrew;
	CIndexTreeNodeMemory*	pcNode;
	CIndexTreeNodeMemory**	pcNodes;

	cIndex.Init();
	cAccess.Init(&cIndex);

	cAndrew.Init("Andrew");
	cAccess.PutStringPtr(cAndrew.GetName(), &cAndrew);
	pcResult = (CTestIndexTreeObject*)cAccess.GetStringPtr("Andrew");
	AssertPointer(&cAndrew, pcResult);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(1, avp.NumElements());
	avp.Kill();

	pcNodeAndrew = cIndex.GetNode("Andrew", 6);
	pcNodes = (CIndexTreeNodeMemory**)pcNodeAndrew->GetNodesMemory();
	AssertNull(pcNodes);

	pcNodeAndre = cIndex.GetNode("Andre", 5);
	pcNodes = (CIndexTreeNodeMemory**)pcNodeAndre->GetNodesMemory();
	pcNode = pcNodes[0];
	AssertPointer(pcNodeAndrew, pcNode);

	batman.Init("Batman");
	cAccess.PutStringPtr(batman.GetName(), &batman);
	pcNodeBatman = cIndex.GetNode("Batman", 6);
	AssertInt(0, pcNodeBatman->NumIndexes());
	pcResult = (CTestIndexTreeObject*)cAccess.GetStringPtr("Batman");
	AssertPointer(&batman, pcResult);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(2, avp.NumElements());
	avp.Kill();

	szBatmam = "Batmam";
	batmam.Init(szBatmam);
	cAccess.PutStringPtr(szBatmam, &batmam);
	pcNodeBatman = cIndex.GetNode("Batman", 6);
	pcNodeBatmam = cIndex.GetNode(szBatmam, 6);
	pcResult = (CTestIndexTreeObject*)cAccess.GetStringPtr(szBatmam);
	AssertPointer(&batmam, pcResult);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(3, avp.NumElements());
	avp.Kill();

	pcNodeAndre = cIndex.GetNode("Andre", 5);
	AssertTrue(pcNodeAndre->HasNodes());
	AssertFalse(pcNodeAndre->HasData());
	pcNodes = (CIndexTreeNodeMemory**)pcNodeAndre->GetNodesMemory();
	AssertNotNull(pcNodes);

	andre.Init("Andre");
	cAccess.PutStringPtr(andre.GetName(), &andre);
	pcResult = (CTestIndexTreeObject*)cAccess.GetStringPtr("Andre");
	AssertPointer(&andre, pcResult);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(4, avp.NumElements());
	avp.Kill();

	AssertNull(cAccess.GetStringPtr(NULL));
	AssertNull(cAccess.GetStringPtr(""));
	AssertNull(cAccess.GetStringPtr("Batma"));
	AssertNull(cAccess.GetStringPtr("Batmano"));
	AssertNull(cAccess.GetStringPtr("Batmao"));

	cAccess.Kill();
	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryPutPtrDuplicate(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	CTestIndexTreeObject	andrew;
	CTestIndexTreeObject	andrewToo;
	CTestIndexTreeObject*	pcResult;
	CArrayVoidPtr			avp;
	BOOL					bResult;

	cIndex.Init();
	cAccess.Init(&cIndex);

	andrew.Init("Andrew");
	bResult = cAccess.PutStringPtr(andrew.mszName, &andrew);
	AssertTrue(bResult);
	AssertTrue(cIndex.ValidateSize());
	AssertInt(1, cIndex.NumElements());

	andrewToo.Init("Andrew");
	bResult = cAccess.PutStringPtr(andrewToo.GetName(), &andrewToo);
	AssertTrue(bResult);
	AssertTrue(cIndex.ValidateSize());
	AssertInt(1, cIndex.NumElements());

	pcResult = (CTestIndexTreeObject*)cAccess.GetStringPtr("Andrew");
	AssertPointer(&andrewToo, pcResult);

	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(1, avp.NumElements());
	avp.Kill();

	cAccess.Kill();
	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryPutDifferenceSizeDuplicates(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	char					szOne[] = "1";
	char					szTwo[] = "22";
	char					szOtherTwo[] = "OT";
	char					szThree[] = "333";
	char					szKerfuffle[] = "kerfuffle";
	CCountingAllocator		cAllocator;
	int						iKeyLength;
	CIndexTreeNodeMemory*	pcNode;
	CIndexTreeNodeMemory*	pcChildNode;
	char					szResult[256];

	cAllocator.Init(&gcSystemAllocator);
	AssertInt(0, cAllocator.AllocatedUserSize());

	cIndex.Init(LifeLocal<CMallocator>(&cAllocator), IKR_No);
	cAccess.Init(&cIndex);
	AssertInt(0, cIndex.NumElements());
	AssertInt(cIndex.ByteSize(), cAllocator.AllocatedUserSize());

	iKeyLength = strlen("Spoedling");
	AssertNull(cIndex.GetNode("Spoedling", iKeyLength));

	AssertTrue(cAccess.PutStringData("SpoedlingZ", szKerfuffle, 10));
	AssertInt(1, cIndex.NumElements());

	AssertInt(cIndex.ByteSize(), cAllocator.AllocatedUserSize());
	pcNode = cIndex.GetNode("Spoedling", iKeyLength);
	AssertNotNull(pcNode);
	pcChildNode = pcNode->Get('Z');
	AssertNotNull(pcChildNode);
	AssertPointer(pcNode, pcChildNode->GetParent());

	AssertTrue(cAccess.PutStringData("Spoedling", szTwo, 3));
	AssertInt(2, cIndex.NumElements());
	AssertInt(cIndex.ByteSize(), cAllocator.AllocatedUserSize());
	AssertString("kerfuffle", cAccess.GetStringString("SpoedlingZ", szResult));
	AssertString("22", cAccess.GetStringString("Spoedling", szResult));

	pcNode = cIndex.GetNode("Spoedling", iKeyLength);
	AssertNotNull(pcNode);
	pcChildNode = pcNode->Get('Z');
	AssertNotNull(pcChildNode);
	AssertPointer(pcNode, pcChildNode->GetParent());

	AssertTrue(cAccess.PutStringData("Spoedling", szOtherTwo, 3));
	AssertInt(2, cIndex.NumElements());
	AssertInt(cIndex.ByteSize(), cAllocator.AllocatedUserSize());
	AssertString("kerfuffle", cAccess.GetStringString("SpoedlingZ", szResult));
	AssertString("OT", cAccess.GetStringString("Spoedling", szResult));

	pcNode = cIndex.GetNode("Spoedling", iKeyLength);
	AssertNotNull(pcNode);
	pcChildNode = pcNode->Get('Z');
	AssertNotNull(pcChildNode);
	AssertPointer(pcNode, pcChildNode->GetParent());

	AssertTrue(cAccess.PutStringData("Spoedling", szThree, 4));
	AssertInt(2, cIndex.NumElements());
	AssertInt(cIndex.ByteSize(), cAllocator.AllocatedUserSize());
	AssertString("kerfuffle", cAccess.GetStringString("SpoedlingZ", szResult));
	AssertString("333", cAccess.GetStringString("Spoedling", szResult));

	pcNode = cIndex.GetNode("Spoedling", iKeyLength);
	AssertNotNull(pcNode);
	pcChildNode = pcNode->Get('Z');
	AssertNotNull(pcChildNode);
	AssertPointer(pcNode, pcChildNode->GetParent());

	AssertTrue(cAccess.PutStringData("Spoedling", szOne, 2));
	AssertInt(2, cIndex.NumElements());
	AssertInt(cIndex.ByteSize(), cAllocator.AllocatedUserSize());
	AssertString("kerfuffle", cAccess.GetStringString("SpoedlingZ", szResult));
	AssertString("1", cAccess.GetStringString("Spoedling", szResult));

	pcNode = cIndex.GetNode("Spoedling", iKeyLength);
	AssertNotNull(pcNode);
	pcChildNode = pcNode->Get('Z');
	AssertNotNull(pcChildNode);
	AssertPointer(pcNode, pcChildNode->GetParent());

	cAccess.Kill();
	cIndex.Kill();
	AssertInt(0, cAllocator.AllocatedUserSize());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryValidateInternalConsistency(void)
{
	CIndexTreeMemory		cIndex;
	CIndexTreeMemoryAccess	cAccess;
	CTestIndexTreeObject	cObject;
	CTestIndexTreeObject	cType;
	CArrayVoidPtr			avp;

	cIndex.Init();
	cAccess.Init(&cIndex);

	cObject.Init("");

	cAccess.PutStringPtr("tonic", &cObject);
	cAccess.PutStringPtr("topia", &cObject);
	cAccess.PutStringPtr("topic", &cObject);
	cAccess.PutStringPtr("totem", &cObject);
	cAccess.PutStringPtr("tower", &cObject);
	cAccess.PutStringPtr("tracter", &cObject);
	cAccess.PutStringPtr("traction", &cObject);
	cAccess.PutStringPtr("trahend", &cObject);
	cAccess.PutStringPtr("translucence", &cObject);
	cAccess.PutStringPtr("translucency", &cObject);
	cAccess.PutStringPtr("transparentness", &cObject);
	cAccess.PutStringPtr("tread", &cObject);
	cAccess.PutStringPtr("treasurer", &cObject);
	cAccess.PutStringPtr("treasurership", &cObject);
	cAccess.PutStringPtr("treasury", &cObject);
	cAccess.PutStringPtr("trench", &cObject);
	cAccess.PutStringPtr("triangularity", &cObject);
	cAccess.PutStringPtr("tribe", &cObject);
	cAccess.PutStringPtr("triplication", &cObject);
	cAccess.PutStringPtr("truncation", &cObject);
	cAccess.PutStringPtr("trunk", &cObject);
	cAccess.PutStringPtr("tunic", &cObject);
	cAccess.PutStringPtr("tunnel", &cObject);
	cAccess.PutStringPtr("tutor", &cObject);
	cAccess.PutStringPtr("tutorship", &cObject);

	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("tonic"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("topia"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("topic"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("totem"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("tower"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("tracter"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("traction"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("trahend"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("translucence"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("translucency"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("transparentness"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("tread"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("treasurer"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("treasurership"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("treasury"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("trench"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("triangularity"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("tribe"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("triplication"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("truncation"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("trunk"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("tunic"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("tunnel"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("tutor"));
	AssertPointer(&cObject, (CTestIndexTreeObject*)cAccess.GetStringPtr("tutorship"));

	cType.Init("type");
	cAccess.PutStringPtr(cType.GetName(), &cType);

	AssertPointer(&cType, (CTestIndexTreeObject*)cAccess.GetStringPtr("type"));

	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(26, avp.NumElements());
	avp.Kill();

	cAccess.Kill();
	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryCountAllocatedNodes(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	CTestIndexTreeObject	cZebra;
	CTestIndexTreeObject	cAardvark;
	CTestIndexTreeObject	cAardvar;
	CTestIndexTreeObject	cAardvarc;
	CTestIndexTreeObject*	pcResult;

	cIndex.Init();
	cAccess.Init(&cIndex);

	AssertInt(1, cIndex.NumAllocatedNodes());

	cZebra.Init("Zebra");
	cAardvark.Init("Aardvark");
	cAardvar.Init("Aardvar");
	cAardvarc.Init("Aardvarc");

	cAccess.PutStringPtr(cZebra.GetName(), &cZebra);
	pcResult = (CTestIndexTreeObject*)cAccess.GetStringPtr("Zebra");
	AssertPointer(&cZebra, pcResult);
	AssertInt(6, cIndex.NumAllocatedNodes());

	cAccess.PutStringPtr(cAardvark.GetName(), &cAardvark);
	pcResult = (CTestIndexTreeObject*)cAccess.GetStringPtr("Aardvark");
	AssertPointer(&cAardvark, pcResult);
	AssertInt(14, cIndex.NumAllocatedNodes());

	cAccess.PutStringPtr(cAardvar.GetName(), &cAardvar);
	pcResult = (CTestIndexTreeObject*)cAccess.GetStringPtr("Aardvar");
	AssertPointer(&cAardvar, pcResult);
	AssertInt(14, cIndex.NumAllocatedNodes());

	cAccess.PutStringPtr(cAardvarc.GetName(), &cAardvarc);
	pcResult = (CTestIndexTreeObject*)cAccess.GetStringPtr("Aardvarc");
	AssertPointer(&cAardvarc, pcResult);
	AssertInt(15, cIndex.NumAllocatedNodes());

	cAccess.Kill();
	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryRemoveByObject(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	CTestIndexTreeObject	object1;
	CTestIndexTreeObject	object2;
	CTestIndexTreeObject	object3;
	CTestIndexTreeObject*	ppcRemoved;

	cIndex.Init();
	cAccess.Init(&cIndex);

	AssertInt(1, cIndex.NumAllocatedNodes());

	object1.Init("denarii");
	cAccess.PutStringPtr(object1.GetName(), &object1);
	AssertInt(8, cIndex.NumAllocatedNodes());

	object2.Init("dendrodra");
	cAccess.PutStringPtr(object2.GetName(), &object2);

	object3.Init("dendrons");
	cAccess.PutStringPtr(object3.GetName(), &object3);

	AssertInt(3, cIndex.NumElements());
	ppcRemoved = (CTestIndexTreeObject*)cAccess.GetStringPtr(object2.GetName());
	AssertPointer(&object2, ppcRemoved);
	AssertTrue(cAccess.DeleteString(object2.GetName()));
	AssertInt(2, cIndex.NumElements());
	AssertTrue(cIndex.ValidateIndexTree())
	AssertInt(13, cIndex.NumAllocatedNodes());
	ppcRemoved = (CTestIndexTreeObject*)cAccess.GetStringPtr(object2.GetName());
	AssertNull(ppcRemoved);
	AssertInt(2, cIndex.NumElements());
	AssertFalse(cAccess.DeleteString(object2.GetName()));
	AssertInt(2, cIndex.NumElements());
	AssertTrue(cIndex.ValidateIndexTree())
	AssertInt(13, cIndex.NumAllocatedNodes());

	cAccess.DeleteString(object3.GetName());
	AssertInt(1, cIndex.NumElements());
	AssertInt(8, cIndex.NumAllocatedNodes());
	AssertTrue(cIndex.ValidateIndexTree())

	cAccess.PutStringPtr(object3.GetName(), &object3);
	AssertInt(13, cIndex.NumAllocatedNodes());
	AssertTrue(cIndex.ValidateIndexTree())
	AssertInt(2, cIndex.NumElements());

	ppcRemoved = (CTestIndexTreeObject*)cAccess.GetStringPtr(object3.GetName());
	AssertPointer(&object3, ppcRemoved);
	AssertTrue(cAccess.DeleteString(object3.GetName()));
	ppcRemoved = (CTestIndexTreeObject*)cAccess.GetStringPtr(object3.GetName());
	AssertNull(ppcRemoved);
	AssertInt(1, cIndex.NumElements());
	ppcRemoved = (CTestIndexTreeObject*)cAccess.GetStringPtr(object1.GetName());
	AssertPointer(&object1, ppcRemoved);
	AssertTrue(cAccess.DeleteString(object1.GetName()));
	ppcRemoved = (CTestIndexTreeObject*)cAccess.GetStringPtr(object1.GetName());
	AssertNull(ppcRemoved);
	AssertInt(0, cIndex.NumElements());

	AssertFalse(cAccess.DeleteString((char*)NULL));
	AssertTrue(cIndex.ValidateIndexTree())
	AssertFalse(cAccess.DeleteString(""));
	AssertTrue(cIndex.ValidateIndexTree());

	cAccess.Kill();
	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryHasKey(void)
{
	CIndexTreeMemory		cIndex;
	CIndexTreeMemoryAccess	cAccess;
	CTestIndexTreeObject	cObject;

	cIndex.Init();
	cAccess.Init(&cIndex);

	cObject.Init("Not Important");

	cAccess.PutStringPtr("fabaceous", &cObject);
	cAccess.PutStringPtr("fabled", &cObject);
	cAccess.PutStringPtr("fabricative", &cObject);
	cAccess.PutStringPtr("fabulous", &cObject);
	cAccess.PutStringPtr("face-centered", &cObject);
	cAccess.PutStringPtr("face-centred", &cObject);
	cAccess.PutStringPtr("face-saving", &cObject);
	cAccess.PutStringPtr("faceable", &cObject);
	cAccess.PutStringPtr("faceless", &cObject);
	cAccess.PutStringPtr("facete", &cObject);
	cAccess.PutStringPtr("facetious", &cObject);
	cAccess.PutStringPtr("facile", &cObject);

	AssertFalse(cAccess.HasString(NULL));
	AssertFalse(cAccess.HasString(""));
	AssertFalse(cAccess.HasString(" "));
	AssertFalse(cAccess.HasString("fab"));
	AssertFalse(cAccess.HasString("facilee"));

	AssertTrue(cAccess.HasString("fabricative"));
	AssertTrue(cAccess.HasString("fabled"));
	AssertTrue(cAccess.HasString("fabulous"));
	AssertTrue(cAccess.HasString("face-centered"));
	AssertTrue(cAccess.HasString("fabaceous"));
	AssertTrue(cAccess.HasString("face-centred"));
	AssertTrue(cAccess.HasString("face-saving"));
	AssertTrue(cAccess.HasString("faceable"));
	AssertTrue(cAccess.HasString("faceless"));
	AssertTrue(cAccess.HasString("facete"));
	AssertTrue(cAccess.HasString("facetious"));
	AssertTrue(cAccess.HasString("facile"));

	cIndex.Kill();
	cAccess.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryRemoveNullNode(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	CTestIndexTreeObject	cObject;

	cIndex.Init();
	cAccess.Init(&cIndex);
	cObject.Init("Not Important");

	cAccess.PutStringPtr("aaa", &cObject);
	cAccess.PutStringPtr("aab", &cObject);

	AssertInt(2, cIndex.NumElements());
	AssertInt(2, cIndex.RecurseSize());

	cAccess.DeleteString("a");

	AssertInt(2, cIndex.NumElements());
	AssertInt(2, cIndex.RecurseSize());

	cAccess.DeleteString("aaa");

	AssertInt(1, cIndex.NumElements());
	AssertInt(1, cIndex.RecurseSize());

	cAccess.DeleteString("aaa");

	AssertInt(1, cIndex.NumElements());
	AssertInt(1, cIndex.RecurseSize());

	cIndex.Kill();
	cAccess.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryAddLongLong(void)
{
	CIndexTreeMemory		cIndex;
	CIndexTreeMemoryAccess	cAccess;
	long long				li;
	long long				li2;

	cIndex.Init();
	cAccess.Init(&cIndex);

	li = 0x88LL;
	cAccess.PutStringLong("GraphRoot", li);
	li2 =	cAccess.GetStringLong("GraphRoot");
	AssertLongLongInt(li, li2);

	cAccess.Kill();
	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryRemoveResize(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	long long				li;
	CMemoryAllocator		cMemoryAlloc;
	CCountingAllocator		cTrackingAlloc;
	int						iExpectedRootSize;

	cMemoryAlloc.Init();
	cTrackingAlloc.Init(&cMemoryAlloc);

	cIndex.Init(LifeLocal<CMallocator>(&cTrackingAlloc) , IKR_No);
	cAccess.Init(&cIndex);

	AssertInt(1, cIndex.NumAllocatedNodes());
	AssertInt(0, cIndex.RecurseSize());
	AssertInt(16, cIndex.SizeofNode());
	AssertInt(4, cIndex.SizeofNodePtr());
	iExpectedRootSize = cIndex.CalculateRootNodeSize();
	AssertInt(1040, iExpectedRootSize);
	AssertInt(1040, cTrackingAlloc.AllocatedUserSize());

	li = 0x77LL; cAccess.PutStringLong("M", li);
	AssertInt(2, cIndex.NumAllocatedNodes());
	AssertInt(1, cIndex.RecurseSize());
	AssertInt(1064, iExpectedRootSize + sizeof(CIndexTreeNodeMemory) + sizeof(long long));
	AssertInt(1076, cTrackingAlloc.AllocatedUserSize());

	li = 0x88LL; cAccess.PutStringLong("MA", li);
	AssertInt(1116, cTrackingAlloc.AllocatedUserSize());
	li = 0x99LL; cAccess.PutStringLong("MC", li);
	AssertInt(4, cIndex.NumAllocatedNodes());
	AssertInt(3, cIndex.RecurseSize());
	AssertInt(1160, cTrackingAlloc.AllocatedUserSize());

	li = 0xaaLL; cAccess.PutStringLong("MB", li);
	AssertInt(5, cIndex.NumAllocatedNodes());
	AssertInt(4, cIndex.RecurseSize());
	AssertInt(1196, cTrackingAlloc.AllocatedUserSize());

	li = 0xbbLL; cAccess.PutStringLong("MBP", li);
	AssertInt(6, cIndex.NumAllocatedNodes());
	AssertInt(5, cIndex.RecurseSize());
	AssertInt(5, cIndex.NumElements());
	AssertInt(1236, cTrackingAlloc.AllocatedUserSize());

	AssertLongLongInt(0xaaLL, cAccess.GetStringLong("MB"));
	cAccess.DeleteString("MB");
	AssertInt(6, cIndex.NumAllocatedNodes());
	AssertInt(4, cIndex.RecurseSize());
	AssertInt(4, cIndex.NumElements());
	AssertInt(1216, cTrackingAlloc.AllocatedUserSize());
	AssertFalse(cAccess.HasString("MB"));

	AssertLongLongInt(0xbbLL, cAccess.GetStringLong("MBP"));
	cAccess.DeleteString("MBP");
	AssertInt(4, cIndex.NumAllocatedNodes());
	AssertInt(3, cIndex.RecurseSize());
	AssertInt(3, cIndex.NumElements());
	AssertInt(1160, cTrackingAlloc.AllocatedUserSize());
	AssertFalse(cAccess.HasString("MBP"));

	AssertLongLongInt(0x99LL, cAccess.GetStringLong("MC"));
	AssertLongLongInt(0x88LL, cAccess.GetStringLong("MA"));
	cAccess.DeleteString("MA");
	AssertInt(3, cIndex.NumAllocatedNodes());
	AssertInt(2, cIndex.RecurseSize());
	AssertInt(2, cIndex.NumElements());
	AssertInt(1116, cTrackingAlloc.AllocatedUserSize());
	AssertFalse(cAccess.HasString("MA"));

	AssertLongLongInt(0x99LL, cAccess.GetStringLong("MC"));
	cAccess.DeleteString("MC");
	AssertInt(2, cIndex.NumAllocatedNodes());
	AssertInt(1, cIndex.RecurseSize());
	AssertInt(1, cIndex.NumElements());
	AssertInt(1076, cTrackingAlloc.AllocatedUserSize());
	AssertFalse(cAccess.HasString("MC"));

	AssertLongLongInt(0x77LL, cAccess.GetStringLong("M"));
	cAccess.DeleteString("M");
	AssertInt(1, cIndex.NumAllocatedNodes());
	AssertInt(0, cIndex.RecurseSize());
	AssertInt(0, cIndex.NumElements());
	AssertInt(1040, cTrackingAlloc.AllocatedUserSize());
	AssertFalse(cAccess.HasString("M"));

	cAccess.Kill();
	cIndex.Kill();
	cTrackingAlloc.Kill();
	cMemoryAlloc.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryIterate(void)
{
	CFileBasic						cFile;
	CTestIndexTreeMemory			cIndex;
	CIndexTreeMemoryAccess			cAccess;
	SIndexTreeMemoryUnsafeIterator	sIter;
	char*							szData;
	size_t							iDataSize;
	unsigned char					c;
	char							szKey[1024];
	size_t							iKeySize;
	char							szResult[256];

	cIndex.Init();
	cAccess.Init(&cIndex);
	cAccess.PutStringData("AAA", "DENISA", 7);
	cAccess.PutStringData("AA", "FATJETA", 8);
	cAccess.PutStringData("AAB", "ARIANA", 7);
	cAccess.PutStringData("AAC", "GEORGE", 7);
	cAccess.PutStringData("AB", "IRMA", 5);
	cAccess.PutStringData("ABA", "JULIANA", 8);
	cAccess.PutStringData("ABB", "LULE", 5);
	cAccess.PutStringData("C", "VENERA", 7);
	cAccess.PutStringData("DDDD", "PRANVERA", 9);
	cAccess.PutStringData("DD", "PRIMERA", 8);
	AssertInt(14, cIndex.NumAllocatedNodes());
	AssertInt(10, cIndex.RecurseSize());
	AssertInt(10, cIndex.NumElements());

	AssertTrue(cIndex.StartUnsafeIteration(&sIter, (void**)&szData, &iDataSize));
	AssertInt(8, iDataSize);
	AssertString("FATJETA", szData);
	Pass();

	iKeySize = cIndex.GetKey(szData, szKey, 1024);
	AssertInt(2, iKeySize);
	AssertString("AA", szKey);

	AssertTrue(cIndex.UnsafeIterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("DENISA", szData);
	AssertInt(3, cIndex.GetKey(szData, szKey, 1024));
	AssertString("AAA", szKey);

	AssertTrue(cIndex.UnsafeIterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("ARIANA", szData);
	AssertInt(3, cIndex.GetKey(szData, szKey, 1024));
	AssertString("AAB", szKey);

	AssertTrue(cIndex.UnsafeIterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("GEORGE", szData);
	AssertInt(3, cIndex.GetKey(szData, szKey, 1024));
	AssertString("AAC", szKey);

	AssertTrue(cIndex.UnsafeIterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(5, iDataSize);
	AssertString("IRMA", szData);
	AssertInt(2, cIndex.GetKey(szData, szKey, 1024));
	AssertString("AB", szKey);

	AssertTrue(cIndex.UnsafeIterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(8, iDataSize);
	AssertString("JULIANA", szData);
	AssertInt(3, cIndex.GetKey(szData, szKey, 1024));
	AssertString("ABA", szKey);

	AssertTrue(cIndex.UnsafeIterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(5, iDataSize);
	AssertString("LULE", szData);
	AssertInt(3, cIndex.GetKey(szData, szKey, 1024));
	AssertString("ABB", szKey);

	AssertTrue(cIndex.UnsafeIterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("VENERA", szData);
	AssertInt(1, cIndex.GetKey(szData, szKey, 1024));
	AssertString("C", szKey);

	AssertTrue(cIndex.UnsafeIterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(8, iDataSize);
	AssertString("PRIMERA", szData);
	AssertInt(2, cIndex.GetKey(szData, szKey, 1024));
	AssertString("DD", szKey);

	AssertTrue(cIndex.UnsafeIterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(9, iDataSize);
	AssertString("PRANVERA", szData);
	AssertInt(4, cIndex.GetKey(szData, szKey, 1024));
	AssertString("DDDD", szKey);

	AssertFalse(cIndex.UnsafeIterate(&sIter, (void**)&szData, &iDataSize));
	cIndex.Kill();

	cIndex.Init();
	AssertInt(1, cIndex.NumAllocatedNodes());
	AssertInt(0, cIndex.RecurseSize());
	AssertInt(0, cIndex.NumElements());

	AssertFalse(cIndex.StartUnsafeIteration(&sIter, (void**)&szData, &iDataSize));
	cIndex.Kill();

	cIndex.Init();
	c = 255;
	cAccess.PutKeyString(&c, 1, "Banks");
	AssertString("Banks", cAccess.GetKeyString(&c, 1, szResult));
	AssertTrue(cIndex.StartUnsafeIteration(&sIter, (void**)&szData, &iDataSize));
	AssertInt(6, iDataSize);
	AssertString("Banks", szData);

	AssertFalse(cIndex.UnsafeIterate(&sIter, (void**)&szData, &iDataSize));
	cIndex.Kill();

	cIndex.Init();
	c = 0;
	cAccess.PutKeyString(&c, 1, "Planks");
	AssertString("Planks", cAccess.GetKeyString(&c, 1, szResult));
	AssertTrue(cIndex.StartUnsafeIteration(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("Planks", szData);

	AssertFalse(cIndex.UnsafeIterate(&sIter, (void**)&szData, &iDataSize));
	cIndex.Kill();
	cAccess.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryReadWrite(void)
{
	CFileBasic				cFile;
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	CTestIndexTreeMemory	cIndexIn;
	CIndexTreeMemoryAccess	cAccessIn;
	char					szResult[256];
	BOOL					bResult;

	cIndex.Init();
	cAccess.Init(&cIndex);

	cAccess.PutStringData("AAA", "DENISA", 7);
	cAccess.PutStringData("AA", "FATJETA", 8);
	cAccess.PutStringData("AAB", "ARIANA", 7);
	cAccess.PutStringData("AAC", "GEORGE", 7);
	cAccess.PutStringData("AB", "IRMA", 5);
	cAccess.PutStringData("ABA", "JULIANA", 8);
	cAccess.PutStringData("ABB", "LULE", 5);
	cAccess.PutStringData("C", "VENERA", 7);
	cAccess.PutStringData("DDDD", "PRANVERA", 9);
	cAccess.PutStringData("DD", "PRIMERA", 8);
	AssertInt(14, cIndex.NumAllocatedNodes());
	AssertInt(10, cIndex.RecurseSize());
	AssertInt(10, cIndex.NumElements());

	cFile.Init(MemoryFile());
	cFile.Open(EFM_Write_Create);
	AssertTrue(cIndex.Write(&cFile));
	cAccess.Kill();
	cIndex.Kill();
	cFile.Close();

	cFile.Open(EFM_Read);
	bResult = cIndexIn.Read(&cFile);
	AssertTrue(bResult);
	cAccessIn.Init(&cIndexIn);
	cFile.Close();
	cFile.Kill();

	AssertInt(14, cIndexIn.NumAllocatedNodes());
	AssertInt(10, cIndexIn.RecurseSize());
	AssertInt(10, cIndexIn.NumElements());
	AssertString("DENISA", cAccessIn.GetStringString("AAA", szResult));
	AssertString("FATJETA", cAccessIn.GetStringString("AA", szResult));
	AssertString("ARIANA", cAccessIn.GetStringString("AAB", szResult));
	AssertString("GEORGE", cAccessIn.GetStringString("AAC", szResult));
	AssertString("IRMA", cAccessIn.GetStringString("AB", szResult));
	AssertString("JULIANA", cAccessIn.GetStringString("ABA", szResult));
	AssertString("LULE", cAccessIn.GetStringString("ABB", szResult));
	AssertString("VENERA", cAccessIn.GetStringString("C", szResult));
	AssertString("PRANVERA", cAccessIn.GetStringString("DDDD", szResult));
	AssertString("PRIMERA", cAccessIn.GetStringString("DD", szResult));

	cAccessIn.Kill();
	cIndexIn.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryRemoveOnRoot(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	int						i;
	unsigned char			cKey;
	int						iData;
	CIndexTreeNodeMemory*	pcRoot;
	CIndexTreeNodeMemory*	pcOldRoot;
	CArrayVoidPtr			avp;

	cIndex.Init();
	cAccess.Init(&cIndex);
	pcOldRoot = cIndex.GetRoot();
	pcRoot = pcOldRoot;

	AssertInt(0, pcRoot->GetFirstIndex());
	AssertInt(255, pcRoot->GetLastIndex());
	AssertInt(256, pcRoot->NumIndexes());
	AssertInt(0, pcRoot->NumValidIndexes());
	AssertInt(0, cIndex.NumElements());
	AssertPointer(pcOldRoot, pcRoot);
	AssertInt(1, cIndex.NumAllocatedNodes());

	for (i = 0; i <= UCHAR_MAX; i++)
	{
		cKey = (unsigned char)i;
		memset(&iData, cKey, sizeof(int));
		cIndex.Put(&cKey, 1, &iData, sizeof(int));

		pcRoot = cIndex.GetRoot();
		AssertPointer(pcOldRoot, pcRoot);

		AssertInt(0, pcRoot->GetFirstIndex());
		AssertInt(255, pcRoot->GetLastIndex());
		AssertInt(256, pcRoot->NumIndexes());
		AssertInt(i + 1, pcRoot->NumValidIndexes());
		AssertInt(i + 1, cIndex.NumElements());
		AssertInt(i + 2, cIndex.NumAllocatedNodes());
	}
	AssertInt(256, cIndex.NumElements());

	for (i = 0; i <= UCHAR_MAX; i++)
	{
		cKey = (unsigned char)(i / 2);
		if (i % 2 == 1)
		{
			cKey = 255 - cKey;
		}
		cAccess.DeleteKey(&cKey, 1);

		pcRoot = cIndex.GetRoot();
		AssertPointer(pcOldRoot, pcRoot);

		AssertInt(0, pcRoot->GetFirstIndex());
		AssertInt(255, pcRoot->GetLastIndex());
		AssertInt(256, pcRoot->NumIndexes());
		AssertInt(255 - i, pcRoot->NumValidIndexes());
		AssertInt(255 - i, cIndex.NumElements());
		AssertInt(256 - i, cIndex.NumAllocatedNodes());

		avp.Init();
		cIndex.FindAll(&avp);
		AssertInt(255 - i, avp.NumElements());
		avp.Kill();
	}

	cAccess.Kill();
	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryResizeData(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	CIndexTreeNodeMemory*	pcNode;
	CIndexTreeNodeMemory*	pcOldNode;
	CIndexTreeNodeMemory*	pcRoot;
	char					szAAObject[] = "Hello";
	char					szACObject[] = "Goodbye";
	char					szAObject[] = "Centrist Policies";
	int						iNodeMemoryOffset1;
	int						iNodeMemoryOffset2;
	CChars					sz;
	char					szResult[256];

	cIndex.Init();
	cAccess.Init(&cIndex);
	AssertTrue(cAccess.PutStringString("AA", szAAObject));
	AssertTrue(cAccess.PutStringString("AC", szACObject));

	pcNode = cIndex.GetNode("A", 1);
	pcOldNode = pcNode;
	AssertInt(3, pcNode->NumIndexes());
	AssertInt(2, pcNode->NumValidIndexes());
	AssertInt(0, pcNode->GetDataSize());
	iNodeMemoryOffset1 = (size_t)pcNode->GetNodesMemory() - (size_t)pcNode;
	AssertInt(cIndex.SizeofNode(), iNodeMemoryOffset1);

	AssertTrue(cAccess.PutStringData("A", szAObject, (unsigned char)strlen(szAObject) + 1));

	pcNode = cIndex.GetNode("A", 1);
	AssertInt(3, pcNode->NumIndexes());
	AssertInt(2, pcNode->NumValidIndexes());
	AssertInt(18, pcNode->GetDataSize());
	iNodeMemoryOffset2 = (size_t)pcNode->GetNodesMemory() - (size_t)pcNode;
	AssertInt(cIndex.SizeofDataNode() + pcNode->GetDataSize(), iNodeMemoryOffset2);
	AssertTrue(iNodeMemoryOffset2 > iNodeMemoryOffset1);

	AssertString(szAAObject, cAccess.GetStringString("AA", szResult));
	AssertString(szACObject, cAccess.GetStringString("AC", szResult));
	AssertString(szAObject, cAccess.GetStringString("A", szResult));

	pcRoot = cIndex.GetRoot();
	sz.Init(); pcRoot->Print(&sz, FALSE);
	AssertString("0:255 .................................................................x..............................................................................................................................................................................................", sz.Text());
	sz.Kill();
	pcNode = pcRoot->Get('A');
	sz.Init(); pcNode->Print(&sz, FALSE);
	AssertString("65:67 (18) x.x", sz.Text());
	sz.Kill();
	sz.Init(); pcNode->Get('A')->Print(&sz, FALSE);
	AssertString("0:0 (6)", sz.Text());
	sz.Kill();
	AssertNull(pcNode->Get('B'));
	sz.Init(); pcNode->Get('C')->Print(&sz, FALSE);
	AssertString("0:0 (8)", sz.Text());
	sz.Kill();

	cIndex.Kill();
	cAccess.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryDescribeData()
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	char					szObject1[] = "Sharp Dressed Man";
	char					szObject2[] = "Built this City";
	int64					iKey1;
	int64					iKey2;
	CIndexTreeNodeMemory*	pcNode;

	iKey1 = 0x5769498897234234LL;
	iKey2 = 0x8357690109812368LL;
	cIndex.Init(IKR_Yes);
	cAccess.Init(&cIndex);
	cAccess.PutLongString(iKey1, szObject1);
	cAccess.PutLongString(iKey2, szObject2);
	AssertInt(2, cIndex.NumElements());

	pcNode = cIndex.GetNode(&iKey1, sizeof(int64));
	AssertNotNull(pcNode);
	AssertTrue(pcNode->HasData());

	pcNode = pcNode->GetParent();
	AssertNotNull(pcNode);
	AssertFalse(pcNode->HasData());

	cIndex.Kill();
	cAccess.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryPut(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	long long int			lliLarry;
	long long int			lliThe;
	long long int			lliLamb;
	long long int			lliResult;

	cIndex.Init();
	cAccess.Init(&cIndex);

	lliLarry = 0x4224f9be509f7b36LL;
	lliThe = 0x392168ee06b4c0d0;
	lliLamb = 0xf855181fab7e51e5;

	AssertTrue(cAccess.PutStringLong("Larry", lliLarry));
	AssertTrue(cAccess.PutStringLong("The", lliThe));
	AssertTrue(cAccess.PutStringLong("Lamb", lliLamb));

	AssertInt(3, cIndex.NumElements());
	AssertInt(3, cIndex.RecurseSize());

	lliResult = cAccess.GetStringLong("Lamb");
	AssertLongLongInt(lliLamb, lliResult);
	lliResult = cAccess.GetStringLong("The");
	AssertLongLongInt(lliThe, lliResult);
	lliResult = cAccess.GetStringLong("Larry");
	AssertLongLongInt(lliLarry, lliResult);

	AssertTrue(cAccess.DeleteString("The"));
	lliResult = cAccess.GetStringLong("The");
	AssertLongLongInt(-1LL, lliResult);

	AssertInt(2, cIndex.NumElements());
	AssertInt(2, cIndex.RecurseSize());

	cAccess.Kill();
	cIndex.Kill();
}


char	gszIndexTreeMemoryCallbackData[64];
int		giIndexTreeMemoryCallbackData = 0;

void TestIndexTreeMemoryDataFreeCallback(const void* pvData)
{
	memset(gszIndexTreeMemoryCallbackData, 0, 64);
	strcpy(gszIndexTreeMemoryCallbackData, (char*)pvData);
	giIndexTreeMemoryCallbackData++;
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryDataFree(void)
{
	CTestIndexTreeMemory	cIndex;
	CIndexTreeMemoryAccess	cAccess;
	long long int			lliLarry;
	long long int			lliThe;
	long long int			lliLamb;
	CDataFreeCallBack		cDataFree;

	giIndexTreeMemoryCallbackData = 0;

	cIndex.Init();
	cDataFree.Init(TestIndexTreeMemoryDataFreeCallback);
	cIndex.SetDataFreeCallback(&cDataFree);
	cAccess.Init(&cIndex);

	lliLarry = 0x4224f9be509f7b36LL;
	lliThe = 0x392168ee06b4c0d0;
	lliLamb = 0xf855181fab7e51e5;

	TestIndexTreeMemoryDataFreeCallback("");
	AssertTrue(cAccess.PutStringString("Larry", "Paige"));
	AssertString("", gszIndexTreeMemoryCallbackData);
	AssertInt(1, giIndexTreeMemoryCallbackData);
	AssertTrue(cAccess.PutStringString("The", "Live"));
	AssertTrue(cAccess.PutStringString("Lamb", "Currants"));

	AssertTrue(cAccess.DeleteString("The"));
	AssertString("Live", gszIndexTreeMemoryCallbackData);

	AssertTrue(cAccess.PutStringString("Larry", "Kinge"));
	AssertString("Paige", gszIndexTreeMemoryCallbackData);

	AssertTrue(cAccess.PutStringString("Lamb", "Is Delicious"));
	AssertString("Currants", gszIndexTreeMemoryCallbackData);
	AssertInt(4, giIndexTreeMemoryCallbackData);

	cAccess.Kill();
	cIndex.Kill();
	AssertInt(6, giIndexTreeMemoryCallbackData);
	AssertString("Kinge", gszIndexTreeMemoryCallbackData);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryReadWriteDataOrderer(void)
{
	CFileBasic							cFile;
	CTestIndexTreeMemory				cIndex;
	CIndexTreeMemoryAccess				cAccess;
	CTestIndexTreeMemory				cIndexIn;
	CIndexTreeMemoryAccess				cAccessIn;
	char								szResult[256];
	BOOL								bResult;
	CIndexTreeMemoryConfig				cConfig;
	CLifeInit<CMallocator>				cMallocInit;
	CMemoryAllocator					cMalloc;
	CLifeInit<CIndexTreeDataOrderer>	cOrdererInit;
	CCreationDataOrderer				cOrderer;
	SDataOrderIterator					sIter;
	char								szData[128];
	char								szKey[24];
	BOOL								bExists;
	CIndexTreeDataOrderer*				pcOrderer;

	cMalloc.Init();
	cMallocInit.Init(&cMalloc, FALSE, TRUE);
	cOrderer.Init();
	cOrdererInit.Init(&cOrderer, FALSE, TRUE);
	cConfig.Init(cMallocInit, IKR_No, 128, 24, cOrdererInit);

	cIndex.Init(&cConfig);
	cAccess.Init(&cIndex);
	cConfig.Kill();

	cAccess.PutStringData("AAA", "DENISA", 7);
	cAccess.PutStringData("AAB", "ARIANA", 7);
	cAccess.PutStringData("C", "VENERA", 7);
	cAccess.PutStringData("AA", "FATJETA", 8);
	cAccess.PutStringData("AB", "IRMA", 5);
	cAccess.PutStringData("DD", "PRIMERA", 8);
	cAccess.PutStringData("DDDD", "PRANVERA", 9);
	cAccess.PutStringData("AAC", "GEORGE", 7);
	cAccess.PutStringData("ABB", "LULE", 5);
	cAccess.PutStringData("ABA", "JULIANA", 8);

	bExists = cOrderer.StartIteration(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("ABA", szKey); AssertString("JULIANA", szData);
	bExists = cOrderer.Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("ABB", szKey); AssertString("LULE", szData);
	bExists = cOrderer.Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("AAC", szKey); AssertString("GEORGE", szData);
	bExists = cOrderer.Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("DDDD", szKey); AssertString("PRANVERA", szData);
	bExists = cOrderer.Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("DD", szKey); AssertString("PRIMERA", szData);

	bExists = cOrderer.Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("AB", szKey); AssertString("IRMA", szData);
	bExists = cOrderer.Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("AA", szKey); AssertString("FATJETA", szData);
	bExists = cOrderer.Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("C", szKey); AssertString("VENERA", szData);
	bExists = cOrderer.Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("AAB", szKey); AssertString("ARIANA", szData);
	bExists = cOrderer.Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("AAA", szKey); AssertString("DENISA", szData);

	bExists = cOrderer.Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertFalse(bExists);

	cFile.Init(MemoryFile());
	cFile.Open(EFM_Write_Create);
	AssertTrue(cIndex.Write(&cFile));
	cAccess.Kill();
	cIndex.Kill();
	cFile.Close();

	cFile.Open(EFM_Read);
	bResult = cIndexIn.Read(&cFile);
	AssertTrue(bResult);
	cAccessIn.Init(&cIndexIn);
	cFile.Close();
	cFile.Kill();

	pcOrderer = cIndexIn.GetDataOrderer();
	AssertString("CCreationDataOrderer", pcOrderer->ClassName());

	AssertInt(14, cIndexIn.NumAllocatedNodes());
	AssertInt(10, cIndexIn.RecurseSize());
	AssertInt(10, cIndexIn.NumElements());
	AssertString("DENISA", cAccessIn.GetStringString("AAA", szResult));
	AssertString("FATJETA", cAccessIn.GetStringString("AA", szResult));
	AssertString("ARIANA", cAccessIn.GetStringString("AAB", szResult));
	AssertString("GEORGE", cAccessIn.GetStringString("AAC", szResult));
	AssertString("IRMA", cAccessIn.GetStringString("AB", szResult));
	AssertString("JULIANA", cAccessIn.GetStringString("ABA", szResult));
	AssertString("LULE", cAccessIn.GetStringString("ABB", szResult));
	AssertString("VENERA", cAccessIn.GetStringString("C", szResult));
	AssertString("PRANVERA", cAccessIn.GetStringString("DDDD", szResult));
	AssertString("PRIMERA", cAccessIn.GetStringString("DD", szResult));

	bExists = pcOrderer->StartIteration(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("DDDD", szKey); AssertString("PRANVERA", szData);
	bExists = pcOrderer->Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("DD", szKey); AssertString("PRIMERA", szData);
	bExists = pcOrderer->Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("C", szKey); AssertString("VENERA", szData);
	bExists = pcOrderer->Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("ABB", szKey); AssertString("LULE", szData);
	bExists = pcOrderer->Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("ABA", szKey); AssertString("JULIANA", szData);

	bExists = pcOrderer->Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("AB", szKey); AssertString("IRMA", szData);
	bExists = pcOrderer->Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("AAC", szKey); AssertString("GEORGE", szData);
	bExists = pcOrderer->Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("AAB", szKey); AssertString("ARIANA", szData);
	bExists = pcOrderer->Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("AAA", szKey); AssertString("DENISA", szData);
	bExists = pcOrderer->Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("AA", szKey); AssertString("FATJETA", szData);

	bExists = pcOrderer->Iterate(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertFalse(bExists);

	cAccessIn.PutStringData("ZZZ", "EXCELSIOR", 10);
	bExists = pcOrderer->StartIteration(&sIter, szKey, NULL, 24, szData, NULL, 128);
	AssertTrue(bExists); AssertString("ZZZ", szKey); AssertString("EXCELSIOR", szData);

	cAccessIn.Kill();
	cIndexIn.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemory(void)
{

	BeginTests();
	FastFunctionsInit();
	MemoryInit();
	LocalMallocatorsInit();
	DataOrderersInit();

	TestIndexTreeMemoryKill();
	TestIndexTreeMemoryDescribeNode();
	TestIndexTreeMemoryAdd(IKR_Yes);
	TestIndexTreeMemoryAdd(IKR_No);
	TestIndexTreeMemoryAddDataOnExistingKey();
	TestIndexTreeMemoryGet();
	TestIndexTreeMemoryPutPtrDuplicate();
	TestIndexTreeMemoryPutDifferenceSizeDuplicates();
	TestIndexTreeMemoryValidateInternalConsistency();
	TestIndexTreeMemoryCountAllocatedNodes();
	TestIndexTreeMemoryRemoveResize();
	TestIndexTreeMemoryRemoveByObject();
	TestIndexTreeMemoryHasKey();
	TestIndexTreeMemoryRemoveNullNode();
	TestIndexTreeMemoryAddLongLong();
	TestIndexTreeMemoryIterate();
	TestIndexTreeMemoryReadWrite();
	TestIndexTreeMemoryRemoveOnRoot();
	TestIndexTreeMemoryResizeData();
	TestIndexTreeMemoryDescribeData();
	TestIndexTreeMemoryPut();
	TestIndexTreeMemoryDataFree();
	TestIndexTreeMemoryReadWriteDataOrderer();

	DataOrderersKill();
	MemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

