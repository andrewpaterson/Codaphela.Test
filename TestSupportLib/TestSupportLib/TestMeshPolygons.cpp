#include "stdafx.h"
#include "TestMeshConnectivity.h"
#include "SupportLib/Mesh.h"
#include "SupportLib/MeshEditor.h"
#include "SupportLib/MeshPlaneEditor.h"
#include "TestLib/Assert.h"
#include "TestMeshPolygons.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMeshPolygonsAddFace(void)
{
	CMesh			cMesh;
	CMeshEditor		cMeshEditor;
	CMeshPolygon*	pcPolygon;

	cMesh.Init();
	cMeshEditor.Init(&cMesh);

	cMesh.AddCorner(&SFloat3(0, 0, 0));
	cMesh.AddCorner(&SFloat3(1, 0, 0));
	cMesh.AddCorner(&SFloat3(1, 1, 0));
	cMesh.AddCorner(&SFloat3(0, 1, 0));

	AssertInt(0, cMeshEditor.mcPolygons.mcPolygons.NumElements());

	cMeshEditor.AddFace(0, 1, 2,  1,  TRUE, TRUE, FALSE);

	AssertInt(3, cMeshEditor.mcEdgeVisibility.mcEdges.NumElements());
	AssertChar(1, cMeshEditor.mcEdgeVisibility.GetEdge(0));
	AssertChar(1, cMeshEditor.mcEdgeVisibility.GetEdge(1));
	AssertChar(0, cMeshEditor.mcEdgeVisibility.GetEdge(2));

	AssertInt(1, cMeshEditor.mcPolygons.mcPolygons.NumElements());

	pcPolygon = cMeshEditor.mcPolygons.mcPolygons.Get(0);
	
	AssertInt(0, cMeshEditor.mcPolygons.maiFacesToPolygons.GetValue(0));
	AssertInt(1, pcPolygon->maiFaces.NumElements());
	AssertInt(0, pcPolygon->maiFaces.GetValue(0));
	
	cMeshEditor.AddFace(0, 2, 3,  1,  FALSE, TRUE, TRUE);

	AssertInt(5, cMeshEditor.mcEdgeVisibility.mcEdges.NumElements());
	AssertChar(1, cMeshEditor.mcEdgeVisibility.GetEdge(0));
	AssertChar(1, cMeshEditor.mcEdgeVisibility.GetEdge(1));
	AssertChar(0, cMeshEditor.mcEdgeVisibility.GetEdge(2));
	AssertChar(1, cMeshEditor.mcEdgeVisibility.GetEdge(3));
	AssertChar(1, cMeshEditor.mcEdgeVisibility.GetEdge(4));

	AssertInt(1, cMeshEditor.mcPolygons.mcPolygons.NumElements());

	pcPolygon = cMeshEditor.mcPolygons.mcPolygons.Get(0);

	AssertInt(2, cMeshEditor.mcPolygons.maiFacesToPolygons.NumElements());
	AssertInt(0, cMeshEditor.mcPolygons.maiFacesToPolygons.GetValue(0));
	AssertInt(0, cMeshEditor.mcPolygons.maiFacesToPolygons.GetValue(1));
	AssertInt(2, pcPolygon->maiFaces.NumElements());
	AssertInt(0, pcPolygon->maiFaces.GetValue(0));
	AssertInt(1, pcPolygon->maiFaces.GetValue(1));

	cMesh.Kill();
	cMeshEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMeshPolygonsAddDiscontiguousFace(BOOL bOutEdgeValue)
{
	CMesh			cMesh;
	CMeshEditor		cMeshEditor;
	CMeshPolygon*	pcPolygon;

	cMesh.Init();
	cMeshEditor.Init(&cMesh);

	cMesh.AddCorner(&SFloat3(0, 0, 0));
	cMesh.AddCorner(&SFloat3(1, 0, 0));
	cMesh.AddCorner(&SFloat3(1, 1, 0));
	cMesh.AddCorner(&SFloat3(0, 1, 0));
	cMesh.AddCorner(&SFloat3(-0.5f, 0.5f, 0));
	cMesh.AddCorner(&SFloat3(0.5f, 1.5f, 0));

	AssertInt(0, cMeshEditor.mcPolygons.mcPolygons.NumElements());

	cMeshEditor.AddFace(0, 1, 2,  1,  bOutEdgeValue, bOutEdgeValue, FALSE);
	cMeshEditor.AddFace(0, 3, 4,  1,  FALSE, bOutEdgeValue, bOutEdgeValue);
	cMeshEditor.AddFace(5, 3, 2,  1,  bOutEdgeValue, FALSE, bOutEdgeValue);

	AssertInt(9, cMeshEditor.mcEdgeVisibility.mcEdges.NumElements());
	AssertInt(3, cMeshEditor.mcPolygons.mcPolygons.NumElements());

	cMeshEditor.AddFace(0, 2, 3,  1,  FALSE, FALSE, FALSE);

	AssertInt(9, cMeshEditor.mcEdgeVisibility.mcEdges.NumElements());
	AssertInt(1, cMeshEditor.mcPolygons.mcPolygons.NumElements());

	AssertInt(4, cMeshEditor.mcPolygons.maiFacesToPolygons.NumElements());
	AssertInt(0, cMeshEditor.mcPolygons.maiFacesToPolygons.GetValue(0));
	AssertInt(0, cMeshEditor.mcPolygons.maiFacesToPolygons.GetValue(1));
	AssertInt(0, cMeshEditor.mcPolygons.maiFacesToPolygons.GetValue(2));
	AssertInt(0, cMeshEditor.mcPolygons.maiFacesToPolygons.GetValue(3));

	pcPolygon = cMeshEditor.mcPolygons.Get(0);
	AssertInt(4, pcPolygon->maiFaces.NumElements());

	//The order isn't important.  We must not have lost any faces though.
	AssertInt(0, pcPolygon->maiFaces.GetValue(0));
	AssertInt(3, pcPolygon->maiFaces.GetValue(1));
	AssertInt(1, pcPolygon->maiFaces.GetValue(2));
	AssertInt(2, pcPolygon->maiFaces.GetValue(3));

	cMeshEditor.AddFace(5, 4, 3,  2,  TRUE, TRUE, TRUE);

	AssertInt(10, cMeshEditor.mcEdgeVisibility.mcEdges.NumElements());
	AssertInt(2, cMeshEditor.mcPolygons.mcPolygons.NumElements());

	cMesh.Kill();
	cMeshEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMeshPolygonAdjacency(void)
{
	CMeshEditor			cMeshEditor;
	CMesh				cMesh;
	CMeshPlaneEditor*	pcPlane;
	CArrayInt			aiAdjacent;

	cMesh.Init();
	cMeshEditor.Init(&cMesh);

	pcPlane = cMeshEditor.AddModifier<CMeshPlaneEditor>();
	pcPlane->Init(&SFloat3(3, 0, 0), &SFloat3(0, 3, 0), &SFloat3(0, 0, 0), 3, 3);

	cMeshEditor.Collapse();

	aiAdjacent.Init(4);
	cMeshEditor.mcPolygons.GetAdjacentPolygons(cMesh.GetConnectivity(), 4, &aiAdjacent);

	AssertInt(4, aiAdjacent.NumElements());
	AssertInt(1, aiAdjacent.GetValue(0));
	AssertInt(3, aiAdjacent.GetValue(1));
	AssertInt(5, aiAdjacent.GetValue(2));
	AssertInt(7, aiAdjacent.GetValue(3));

	aiAdjacent.Kill();

	aiAdjacent.Init(4);
	cMeshEditor.mcPolygons.GetAdjacentPolygons(cMesh.GetConnectivity(), 0, &aiAdjacent);

	AssertInt(2, aiAdjacent.NumElements());
	AssertInt(1, aiAdjacent.GetValue(0));
	AssertInt(3, aiAdjacent.GetValue(1));

	aiAdjacent.Kill();

	cMeshEditor.Kill();
	cMesh.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMeshPolygons(void)
{
	BeginTests();

	TestMeshPolygonsAddFace();
	TestMeshPolygonsAddDiscontiguousFace(TRUE);
	TestMeshPolygonsAddDiscontiguousFace(FALSE);
	TestMeshPolygonAdjacency();

	TestStatistics();
}

