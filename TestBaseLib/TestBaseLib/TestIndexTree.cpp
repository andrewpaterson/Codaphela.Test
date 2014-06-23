#include "BaseLib/IndexTree.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeAdd(void)
{
	CIndexTree				cIndex;
	CTestIndexTreeObject	a;
	CTestIndexTreeObject	aa;
	CTestIndexTreeObject	temp;
	CArrayVoidPtr			avp;
	BOOL					bResult;

	cIndex.Init();
	a.Init("A");
	bResult = cIndex.Put(&a, a.GetName());
	AssertTrue(bResult);

	aa.Init("AA");
	bResult = cIndex.Put(&aa, aa.GetName());
	AssertTrue(bResult);

	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(2, avp.NumElements());
	AssertPointer(&a, *avp.Get(0));
	AssertPointer(&aa, *avp.Get(1));
	AssertString("A", ((CTestIndexTreeObject*)*avp.Get(0))->mszName);
	AssertString("AA", ((CTestIndexTreeObject*)*avp.Get(1))->mszName);

	avp.Kill();
	cIndex.Kill();

	cIndex.Init();
	bResult = cIndex.Put(&temp, NULL);
	AssertFalse(bResult);
	bResult = cIndex.Put(&temp, "");
	AssertFalse(bResult);

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeGet(void)
{
	CIndexTree				cIndex;
	CTestIndexTreeObject	andrew;
	CTestIndexTreeObject*	pcResult;
	CArrayVoidPtr			avp;
	CTestIndexTreeObject	batman;
	CTestIndexTreeObject	batmam;
	CTestIndexTreeObject	andre;

	cIndex.Init();

	andrew.Init("Andrew");
	cIndex.Put(&andrew, andrew.GetName());
	pcResult = (CTestIndexTreeObject*)cIndex.Get("Andrew");
	AssertPointer(pcResult, &andrew);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(1, avp.NumElements());
	avp.Kill();

	batman.Init("Batman");
	cIndex.Put(&batman, batman.GetName());
	pcResult = (CTestIndexTreeObject*)cIndex.Get("Batman");
	AssertPointer(pcResult, &batman);
	cIndex.FindAll(&avp);
	AssertInt(2, avp.NumElements());
	avp.Kill();

	batmam.Init("Batmam");
	cIndex.Put(&batmam, batmam.GetName());
	pcResult = (CTestIndexTreeObject*)cIndex.Get("Batmam");
	AssertPointer(pcResult, &batmam);
	cIndex.FindAll(&avp);
	AssertInt(3, avp.NumElements());
	avp.Kill();

	andre.Init("Andre");
	cIndex.Put(&andre, andre.GetName());
	pcResult = (CTestIndexTreeObject*)cIndex.Get("Andre");
	AssertPointer(pcResult, &andre);
	cIndex.FindAll(&avp);
	AssertInt(4, avp.NumElements());

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
void TestIndexTreePutDuplicate(void)
{
	CIndexTree				cIndex;
	CTestIndexTreeObject	andrew;
	CTestIndexTreeObject	andrewToo;
	CTestIndexTreeObject*	pcResult;
	CArrayVoidPtr			avp;
	BOOL					bResult;

	cIndex.Init();

	andrew.Init("Andrew");
	bResult = cIndex.Put(&andrew, andrew.mszName);
	AssertTrue(bResult);

	andrewToo.Init("Andrew");
	bResult = cIndex.Put(&andrewToo, andrewToo.GetName());
	AssertFalse(bResult);

	pcResult = (CTestIndexTreeObject*)cIndex.Get("Andrew");
	AssertPointer(&andrew, pcResult);

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
void TestIndexTreeValidateInternalConsistency(void)
{
	CIndexTree				cIndex;
	CTestIndexTreeObject	cObject;
	CTestIndexTreeObject	cType;

	cIndex.Init();

	cObject.Init("");

	cIndex.Put(&cObject, "tonic");
	cIndex.Put(&cObject, "topia");
	cIndex.Put(&cObject, "topic");
	cIndex.Put(&cObject, "totem");
	cIndex.Put(&cObject, "tower");
	cIndex.Put(&cObject, "tracter");
	cIndex.Put(&cObject, "traction");
	cIndex.Put(&cObject, "trahend");
	cIndex.Put(&cObject, "translucence");
	cIndex.Put(&cObject, "translucency");
	cIndex.Put(&cObject, "transparentness");
	cIndex.Put(&cObject, "tread");
	cIndex.Put(&cObject, "treasurer");
	cIndex.Put(&cObject, "treasurership");
	cIndex.Put(&cObject, "treasury");
	cIndex.Put(&cObject, "trench");
	cIndex.Put(&cObject, "triangularity");
	cIndex.Put(&cObject, "tribe");
	cIndex.Put(&cObject, "triplication");
	cIndex.Put(&cObject, "truncation");
	cIndex.Put(&cObject, "trunk");
	cIndex.Put(&cObject, "tunic");
	cIndex.Put(&cObject, "tunnel");
	cIndex.Put(&cObject, "tutor");
	cIndex.Put(&cObject, "tutorship");

	AssertPointer(&cObject, cIndex.Get("tonic"));
	AssertPointer(&cObject, cIndex.Get("topia"));
	AssertPointer(&cObject, cIndex.Get("topic"));
	AssertPointer(&cObject, cIndex.Get("totem"));
	AssertPointer(&cObject, cIndex.Get("tower"));
	AssertPointer(&cObject, cIndex.Get("tracter"));
	AssertPointer(&cObject, cIndex.Get("traction"));
	AssertPointer(&cObject, cIndex.Get("trahend"));
	AssertPointer(&cObject, cIndex.Get("translucence"));
	AssertPointer(&cObject, cIndex.Get("translucency"));
	AssertPointer(&cObject, cIndex.Get("transparentness"));
	AssertPointer(&cObject, cIndex.Get("tread"));
	AssertPointer(&cObject, cIndex.Get("treasurer"));
	AssertPointer(&cObject, cIndex.Get("treasurership"));
	AssertPointer(&cObject, cIndex.Get("treasury"));
	AssertPointer(&cObject, cIndex.Get("trench"));
	AssertPointer(&cObject, cIndex.Get("triangularity"));
	AssertPointer(&cObject, cIndex.Get("tribe"));
	AssertPointer(&cObject, cIndex.Get("triplication"));
	AssertPointer(&cObject, cIndex.Get("truncation"));
	AssertPointer(&cObject, cIndex.Get("trunk"));
	AssertPointer(&cObject, cIndex.Get("tunic"));
	AssertPointer(&cObject, cIndex.Get("tunnel"));
	AssertPointer(&cObject, cIndex.Get("tutor"));
	AssertPointer(&cObject, cIndex.Get("tutorship"));

	cType.Init("type");
	cIndex.Put(&cType, cType.GetName());

	AssertPointer(&cType, cIndex.Get("type"));
	

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeCountAllocatedNodes(void)
{
	CIndexTree				cIndex;
	CTestIndexTreeObject	cZebra;
	CTestIndexTreeObject	cAardvark;
	CTestIndexTreeObject	cAardvar;
	CTestIndexTreeObject	cAardvarc;
	void*					pvResult;

	cIndex.Init();

	AssertInt(1, cIndex.CountAllocatedNodes());

	cZebra.Init("Zebra");
	cAardvark.Init("Aardvark");
	cAardvar.Init("Aardvar");
	cAardvarc.Init("Aardvarc");

	cIndex.Put(&cZebra, cZebra.GetName());
	pvResult = cIndex.Get("Zebra");
	AssertPointer(&cZebra, pvResult);
	AssertInt(6, cIndex.CountAllocatedNodes());

	cIndex.Put(&cAardvark, cAardvark.GetName());
	pvResult = cIndex.Get("Aardvark");
	AssertPointer(&cAardvark, pvResult);
	AssertInt(14, cIndex.CountAllocatedNodes());

	cIndex.Put(&cAardvar, cAardvar.GetName());
	pvResult = cIndex.Get("Aardvar");
	AssertPointer(&cAardvar, pvResult);
	AssertInt(14, cIndex.CountAllocatedNodes());

	cIndex.Put(&cAardvarc, cAardvarc.GetName());
	pvResult = cIndex.Get("Aardvarc");
	AssertPointer(&cAardvarc, pvResult);
	AssertInt(15, cIndex.CountAllocatedNodes());

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeRemoveByObject(void)
{
	CIndexTree cIndex;
	CTestIndexTreeObject	object1;
	CTestIndexTreeObject	object2;
	CTestIndexTreeObject	object3;


	cIndex.Init();

	AssertInt(1, cIndex.CountAllocatedNodes());

	object1.Init("denarii");
	cIndex.Put(&object1, object1.GetName());
	AssertInt(8, cIndex.CountAllocatedNodes());

	object2.Init("dendrodra");
	cIndex.Put(&object2, object2.GetName());

	object3.Init("dendrons");
	cIndex.Put(&object3, object3.GetName());

	AssertInt(3, cIndex.GetSize());
	AssertPointer(&object2, cIndex.Remove(object2.GetName()));
	AssertInt(2, cIndex.GetSize());
	AssertNull(cIndex.Remove(object2.GetName()));
	AssertInt(2, cIndex.GetSize());

	AssertInt(13, cIndex.CountAllocatedNodes());
	cIndex.Remove(object3.GetName());

	AssertInt(1, cIndex.GetSize());
	AssertInt(8, cIndex.CountAllocatedNodes());

	cIndex.Put(&object3, object3.GetName());
	AssertInt(13, cIndex.CountAllocatedNodes());

	AssertInt(2, cIndex.GetSize());
	AssertPointer(&object3, cIndex.Remove(object3.GetName()));
	AssertInt(1, cIndex.GetSize());
	AssertPointer(&object1, cIndex.Remove(object1.GetName()));
	AssertInt(0, cIndex.GetSize());

	AssertNull(cIndex.Remove(NULL));
	AssertNull(cIndex.Remove(""));

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeHasKey(void)
{
	CIndexTree				cIndex;
	CTestIndexTreeObject	cObject;

	cIndex.Init();
	cObject.Init("Not Important");

	cIndex.Put(&cObject, "fabaceous");
	cIndex.Put(&cObject, "fabled");
	cIndex.Put(&cObject, "fabricative");
	cIndex.Put(&cObject, "fabulous");
	cIndex.Put(&cObject, "face-centered");
	cIndex.Put(&cObject, "face-centred");
	cIndex.Put(&cObject, "face-saving");
	cIndex.Put(&cObject, "faceable");
	cIndex.Put(&cObject, "faceless");
	cIndex.Put(&cObject, "facete");
	cIndex.Put(&cObject, "facetious");
	cIndex.Put(&cObject, "facile");

	AssertFalse(cIndex.HasKey(NULL));
	AssertFalse(cIndex.HasKey(""));
	AssertFalse(cIndex.HasKey(" "));
	AssertFalse(cIndex.HasKey("fab"));
	AssertFalse(cIndex.HasKey("facilee"));

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
void TestIndexTreeRemoveNullNode(void)
{
	CIndexTree				cIndex;
	CTestIndexTreeObject	cObject;

	cIndex.Init();
	cObject.Init("Not Important");

	cIndex.Put(&cObject, "aaa");
	cIndex.Put(&cObject, "aab");

	AssertInt(2, cIndex.GetSize());
	AssertInt(2, cIndex.RecurseSize());

	cIndex.Remove("a");

	AssertInt(2, cIndex.GetSize());
	AssertInt(2, cIndex.RecurseSize());

	cIndex.Remove("aaa");

	AssertInt(1, cIndex.GetSize());
	AssertInt(1, cIndex.RecurseSize());

	cIndex.Remove("aaa");

	AssertInt(1, cIndex.GetSize());
	AssertInt(1, cIndex.RecurseSize());

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTree(void)
{
	BeginTests();

	TestIndexTreeAdd();
	TestIndexTreeGet();
	TestIndexTreePutDuplicate();
	TestIndexTreeValidateInternalConsistency();
	TestIndexTreeCountAllocatedNodes();
	TestIndexTreeRemoveByObject();
	TestIndexTreeHasKey();
	TestIndexTreeRemoveNullNode();

	TestStatistics();
}

