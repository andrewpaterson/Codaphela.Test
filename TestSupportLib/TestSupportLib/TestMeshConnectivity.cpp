#include "stdafx.h"
#include "TestMeshConnectivity.h"
#include "SupportLib/Mesh.h"
#include "SupportLib/MeshEditor.h"
#include "SupportLib/MeshPlaneEditor.h"
#include "TestLib/Assert.h"
#include "TestMeshConnectivity.h"


void AssertCornerFaces(CMeshCorner* pcCorner, int iNumFaces, ...);
void AssertCornerEdges(CMeshCorner* pcCorner, int iNumEdges, ...);
void AssertEdgeFaces(CMeshEdge* pcEdge, int iFace1, int iFace2);
void AssertEdgeCorners(CMeshEdge* pcEdge, int iCorner1, int iCorner2);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMeshEdgeConnectivity(void)
{
	CMesh				cMesh;
	SFloat3				sXDirection;
	SFloat3				sYDirection;
	SFloat3				sZDirection;
	SFloat3				sStart;
	CMeshPlaneEditor*	pcPlaneEditor;
	CMeshEditor			cMeshEditor;
	CMeshConnectivity*	pcConn;
	int					i;
	CCornerEdgesMap*	pcCornerEdgesMap;

	cMesh.Init();
	cMeshEditor.Init(&cMesh);

	sXDirection.Init(1, 0, 0);
	sYDirection.Init(0, 1, 0);
	sZDirection.Init(0, 0, 1);
	sStart.Init(-0.5f, -0.5f, -0.5f);

	pcPlaneEditor = cMeshEditor.AddModifier<CMeshPlaneEditor>();
	pcPlaneEditor->Init(&sXDirection, &sYDirection, &sStart, 1, 2);

	cMeshEditor.Collapse();

	pcConn = cMesh.GetConnectivity();
	AssertInt(9, pcConn->mcEdges.NumElements());
	AssertInt(6, pcConn->mcCorners.NumElements());
	AssertInt(6, pcConn->mcCornerEdgesMap.NumElements());
	AssertInt(4, pcConn->mcFaces.NumElements());

	AssertCornerFaces(pcConn->mcCorners.Get(0),  1,  0);
	AssertCornerFaces(pcConn->mcCorners.Get(1),  2,  0, 1);
	AssertCornerFaces(pcConn->mcCorners.Get(2),  3,  0, 1, 2);
	AssertCornerFaces(pcConn->mcCorners.Get(3),  3,  1, 2, 3);
	AssertCornerFaces(pcConn->mcCorners.Get(4),  2,  2, 3);
	AssertCornerFaces(pcConn->mcCorners.Get(5),  1,  3);

	AssertCornerEdges(pcConn->mcCorners.Get(0),  2,  0, 2);
	AssertCornerEdges(pcConn->mcCorners.Get(1),  3,  0, 1, 3);
	AssertCornerEdges(pcConn->mcCorners.Get(2),  4,  1, 2, 4, 6);
	AssertCornerEdges(pcConn->mcCorners.Get(3),  4,  3, 4, 5, 7);
	AssertCornerEdges(pcConn->mcCorners.Get(4),  3,  5, 6, 8);
	AssertCornerEdges(pcConn->mcCorners.Get(5),  2,  7, 8);

	for (i = 0; i < pcConn->mcCornerEdgesMap.NumElements(); i++)
	{
		pcCornerEdgesMap = pcConn->mcCornerEdgesMap.Get(i);
		AssertInt(pcCornerEdgesMap->maiEdgeIndex.NumElements(), pcCornerEdgesMap->maiLargerCornerIndex.NumElements());
	}

	AssertEdgeCorners(pcConn->mcEdges.Get(0), 0, 1);
	AssertEdgeCorners(pcConn->mcEdges.Get(1), 1, 2);
	AssertEdgeCorners(pcConn->mcEdges.Get(2), 0, 2);
	AssertEdgeCorners(pcConn->mcEdges.Get(3), 1, 3);
	AssertEdgeCorners(pcConn->mcEdges.Get(4), 2, 3);
	AssertEdgeCorners(pcConn->mcEdges.Get(5), 3, 4);
	AssertEdgeCorners(pcConn->mcEdges.Get(6), 2, 4);
	AssertEdgeCorners(pcConn->mcEdges.Get(7), 3, 5);
	AssertEdgeCorners(pcConn->mcEdges.Get(8), 4, 5);

	AssertEdgeFaces(pcConn->mcEdges.Get(0), 0, -1);
	AssertEdgeFaces(pcConn->mcEdges.Get(1), 0, 1);
	AssertEdgeFaces(pcConn->mcEdges.Get(2), 0, -1);
	AssertEdgeFaces(pcConn->mcEdges.Get(3), 1, -1);
	AssertEdgeFaces(pcConn->mcEdges.Get(4), 1, 2);
	AssertEdgeFaces(pcConn->mcEdges.Get(5), 2, 3);
	AssertEdgeFaces(pcConn->mcEdges.Get(6), 2, -1);
	AssertEdgeFaces(pcConn->mcEdges.Get(7), 3, -1);
	AssertEdgeFaces(pcConn->mcEdges.Get(8), 3, -1);

	cMesh.Kill();
	cMeshEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertCornerFaces(CMeshCorner* pcCorner, int iNumFaces, ...)
{
	va_list		vaMarker;
	int			i;
	int			iFaceNum;

	AssertInt(iNumFaces, pcCorner->aiFace.NumElements());
	if (iNumFaces != pcCorner->aiFace.NumElements())
	{
		return;
	}

	va_start(vaMarker, iNumFaces);
	for (i = 0; i < iNumFaces; i++)
	{
		iFaceNum = va_arg(vaMarker, int);
		AssertInt(iFaceNum, pcCorner->aiFace.GetValue(i));
	}
	va_end(vaMarker);
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertCornerEdges(CMeshCorner* pcCorner, int iNumEdges, ...)
{
	va_list		vaMarker;
	int			i;
	int			iEdgeNum;

	AssertInt(iNumEdges, pcCorner->aiEdge.NumElements());
	if (iNumEdges != pcCorner->aiEdge.NumElements())
	{
		return;
	}

	va_start(vaMarker, iNumEdges);
	for (i = 0; i < iNumEdges; i++)
	{
		iEdgeNum = va_arg(vaMarker, int);
		AssertInt(iEdgeNum, pcCorner->aiEdge.GetValue(i));
	}
	va_end(vaMarker);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertEdgeFaces(CMeshEdge* pcEdge, int iFace1, int iFace2)
{
	AssertInt(iFace1, pcEdge->aiFace[0]);
	AssertInt(iFace2, pcEdge->aiFace[1]);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertEdgeCorners(CMeshEdge* pcEdge, int iCorner1, int iCorner2)
{
	AssertInt(iCorner1, pcEdge->aiCorner[0]);
	AssertInt(iCorner2, pcEdge->aiCorner[1]);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMeshConnectivity(void)
{
	BeginTests();

	TestMeshEdgeConnectivity();

	TestStatistics();
}

