#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


class VertexID
{
public:
	int		vertIndex; //index of this vertex in the vertex list
	int		normIndex; // index of this vertex's normal
	int		colorIndex; // index of this vertex's color
};

class Face
{
public:
	int	nVerts;
	VertexID* vert;
	// danh sách các đỉnh + vector pháp tuyến của đỉnh
	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Normal
{
	int nNormals;
	Normal()
	{
		nNormals = 0;
	}
};

class Mesh
{
public:
	int	numVerts; // chiều dài
	Point3* pt; // danh sách các đỉnh

	int	numFaces; // chiều dài 
	Face* face; // danh sách các mặt

	int numNormals;
	Normal* normal;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();

	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateCylinderEmpty(int nSegment, float fHeight, float fRadius, float fRadius2);
	void CreateShape1(float fLength, float fWidth, float fHeight, float fRadius);
	void CreateShape2(float fLength1, float fRadius1, float fLength2, float fRadius2, float fHeight);
	void CreateShape3(float fLength1, float fLength2, float fWidth, float fHeight, float fRadius);

};

#endif