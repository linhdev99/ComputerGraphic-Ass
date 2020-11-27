#include "Mesh.h"
#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;

#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0},
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0},
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} };





void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts=nSegment*2 + 2; // đỉnh ở phía trên + dưới (bao gồm cả tâm)
	//cout << numVerts << endl;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2*PI/nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight/2, 0);
	for(i = 0; i<nSegment; i++)
	{
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = fHeight/2;
		pt[i+1].set(x, y, z);

		y = -fHeight/2;
		pt[i +1 + nSegment].set(x, y, z);
	}
	pt[numVerts-1].set(0, -fHeight/2, 0);

	numFaces= nSegment*3;
	face = new Face[numFaces];

	idx = 0;
	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if(i < nSegment -1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		
		face[idx].vert[0].vertIndex = i+1;
		if(i <nSegment - 1)
			face[idx].vert[1].vertIndex = i+2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if(i < nSegment -1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}

void Mesh::CreateCylinderEmpty(int nSegment, float fHeight, float fRadius, float fRadius2)
{
	numVerts = nSegment * 4; // đỉnh ở phía trên + dưới (bao gồm cả tâm)
	//cout << numVerts << endl;
	pt = new Point3[numVerts]; // tạo số điểm = số đỉnh

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	//pt[0].set(0, fHeight / 2, 0);
	for (i = 0; i < nSegment; i++)
	{
		// trên , ngoài
		x = fRadius * cos(fAngle * i); 
		z = fRadius * sin(fAngle * i);
		y = fHeight / 2;
		pt[i].set(x, y, z);

		// dưới, ngoài
		y = -fHeight / 2;
		pt[i + nSegment*2].set(x, y, z); 

		// trên, trong
		x = fRadius2 * cos(fAngle * i);
		z = fRadius2 * sin(fAngle * i);
		y = fHeight / 2;
		pt[i + nSegment].set(x, y, z);

		// dưới, trong
		y = -fHeight / 2;
		pt[i + nSegment*3].set(x, y, z);



	}
	/*for (int i = 0; i < nSegment; i++)
	{
		cout << pt[i].printPoint3() << endl;
		cout << pt[i + nSegment].printPoint3() << endl;
		cout << pt[i + nSegment * 2].printPoint3() << endl;
		cout << pt[i + nSegment * 3].printPoint3() << endl << endl;
	}*/
	//pt[numVerts - 1].set(0, -fHeight / 2, 0);

	numFaces = nSegment * 4;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4; // 4 đỉnh
		face[idx].vert = new VertexID[face[idx].nVerts]; // 4 đỉnh
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + nSegment;
		face[idx].vert[3].vertIndex = i+1;
		face[idx].vert[2].vertIndex = i+1 + nSegment;
		if (i == nSegment - 1)
		{
			face[idx].vert[3].vertIndex = 0;
			face[idx].vert[2].vertIndex = nSegment;
		}
		idx++;
		/*if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;*/
	}
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4; // 4 đỉnh
		face[idx].vert = new VertexID[face[idx].nVerts]; // 4 đỉnh
		face[idx].vert[0].vertIndex = i + nSegment * 2;
		face[idx].vert[1].vertIndex = i + nSegment + nSegment * 2;
		face[idx].vert[3].vertIndex = i + 1 + nSegment * 2;
		face[idx].vert[2].vertIndex = i + 1 + nSegment + nSegment * 2;
		if (i == nSegment - 1)
		{
			face[idx].vert[3].vertIndex = 0 + nSegment * 2;
			face[idx].vert[2].vertIndex = nSegment + nSegment * 2;
		}
		idx++;
	}
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4; // 4 đỉnh
		face[idx].vert = new VertexID[face[idx].nVerts]; // 4 đỉnh
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[3].vertIndex = i + 1;
		face[idx].vert[1].vertIndex = i + nSegment * 2;
		face[idx].vert[2].vertIndex = i + 1 + nSegment * 2;
		if (i == nSegment - 1)
		{
			face[idx].vert[3].vertIndex = 0;
			face[idx].vert[2].vertIndex = nSegment * 2;
		}
		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4; // 4 đỉnh
		face[idx].vert = new VertexID[face[idx].nVerts]; // 4 đỉnh
		face[idx].vert[0].vertIndex = i + nSegment;
		face[idx].vert[3].vertIndex = i + 1 + nSegment;
		face[idx].vert[1].vertIndex = i + nSegment * 3;
		face[idx].vert[2].vertIndex = i + 1 + nSegment * 3;
		if (i == nSegment - 1)
		{
			face[idx].vert[3].vertIndex = nSegment;
			face[idx].vert[2].vertIndex = nSegment * 3;
		}
		idx++;
	}

	/*for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if (i < nSegment - 1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}*/

}

void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::CreateShape1(float fLength, float fWidth, float fHeight, float fRadius)
{
	int i;
	int nSegment = 36;
	int qSegment = nSegment / 4 + 1;
	numVerts = (qSegment * 2 + 2) + 8; // 1/4 hinh tron + 8 dinh
	float fOx = fWidth;
	float fOy = fHeight;
	float fOz = fLength;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;
	int iStart = 8;


	numFaces = qSegment * 3 + 7;
	face = new Face[numFaces];
	pt = new Point3[numVerts];
	// Ve khoi hinh thang vuong
	{
		pt[0].set(0, 0, 0);
		pt[1].set(fOx, 0, 0);
		pt[2].set(fRadius, 0, fOz);
		pt[3].set(0, 0, fOz);
		pt[4].set(0, fOy, 0);
		pt[5].set(fOx, fOy, 0);
		pt[6].set(fRadius, fOy, fOz);
		pt[7].set(0, fOy, fOz);

		//Left face
		face[0].nVerts = 4;
		face[0].vert = new VertexID[face[0].nVerts];
		face[0].vert[0].vertIndex = 1;
		face[0].vert[1].vertIndex = 5;
		face[0].vert[2].vertIndex = 6;
		face[0].vert[3].vertIndex = 2;
		for (i = 0; i < face[0].nVerts; i++)
			face[0].vert[i].colorIndex = 0;

		//Right face
		face[1].nVerts = 4;
		face[1].vert = new VertexID[face[1].nVerts];
		face[1].vert[0].vertIndex = 0;
		face[1].vert[1].vertIndex = 3;
		face[1].vert[2].vertIndex = 7;
		face[1].vert[3].vertIndex = 4;
		for (i = 0; i < face[1].nVerts; i++)
			face[1].vert[i].colorIndex = 1;

		//top face
		face[2].nVerts = 4;
		face[2].vert = new VertexID[face[2].nVerts];
		face[2].vert[0].vertIndex = 0;
		face[2].vert[1].vertIndex = 1;
		face[2].vert[2].vertIndex = 2;
		face[2].vert[3].vertIndex = 3;
		for (i = 0; i < face[2].nVerts; i++)
			face[2].vert[i].colorIndex = 2;

		//bottom face
		face[3].nVerts = 4;
		face[3].vert = new VertexID[face[3].nVerts];
		face[3].vert[0].vertIndex = 7;
		face[3].vert[1].vertIndex = 6;
		face[3].vert[2].vertIndex = 5;
		face[3].vert[3].vertIndex = 4;
		for (i = 0; i < face[3].nVerts; i++)
			face[3].vert[i].colorIndex = 3;

		//near face
		face[4].nVerts = 4;
		face[4].vert = new VertexID[face[4].nVerts];
		face[4].vert[0].vertIndex = 4;
		face[4].vert[1].vertIndex = 5;
		face[4].vert[2].vertIndex = 1;
		face[4].vert[3].vertIndex = 0;
		for (i = 0; i < face[4].nVerts; i++)
			face[4].vert[i].colorIndex = 4;

		//Far face
		face[5].nVerts = 4;
		face[5].vert = new VertexID[face[5].nVerts];
		face[5].vert[0].vertIndex = 3;
		face[5].vert[1].vertIndex = 2;
		face[5].vert[2].vertIndex = 6;
		face[5].vert[3].vertIndex = 7;
		for (i = 0; i < face[5].nVerts; i++)
			face[5].vert[i].colorIndex = 5;
	}

	// Ve 1/4 hinh tru
	{
		pt[0 + iStart].set(0, 0, fOz);
		pt[1 + qSegment + iStart].set(0, fOy, fOz);
		for (i = 0; i < qSegment; i++)
		{
			x = fRadius * cos(fAngle * i);
			z = fRadius * sin(fAngle * i) + fOz;
			y = 0;
			pt[i + 1 + iStart].set(x, y, z);
			y = fOy;
			pt[i + 2 + qSegment + iStart].set(x, y, z);
		}
		cout << "them diem xong " << endl;
		idx = 6;
		for (i = 0; i < qSegment; i++)
		{
			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];

			face[idx].vert[0].vertIndex = 0 + iStart;
			face[idx].vert[1].vertIndex = i + 1 + iStart;
			face[idx].vert[2].vertIndex = i + 2 + iStart;
			if (i == qSegment - 1)
			{
				face[idx].vert[2].vertIndex = 0 + iStart;
			}
			idx++;
		}
		for (i = 0; i < qSegment; i++)
		{
			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];

			face[idx].vert[0].vertIndex = 1 + iStart + qSegment;
			face[idx].vert[1].vertIndex = i + 2 + iStart + qSegment;
			face[idx].vert[2].vertIndex = i + 3 + iStart + qSegment;
			if (i == qSegment - 1)
			{
				face[idx].vert[2].vertIndex = 1 + iStart + qSegment;
			}
			idx++;
		}
		for (i = 0; i < qSegment; i++)
		{
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];

			face[idx].vert[0].vertIndex = i + 1 + iStart;
			face[idx].vert[1].vertIndex = i + 2 + qSegment + iStart;
			face[idx].vert[2].vertIndex = i + 3 + qSegment + iStart;
			face[idx].vert[3].vertIndex = i + 2 + iStart;
			if (i == qSegment - 1)
			{
				face[idx].vert[2].vertIndex = 2 + qSegment + iStart;
				face[idx].vert[3].vertIndex = 1 + iStart;
			}
			idx++;
		}
		{
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];

			face[idx].vert[0].vertIndex = iStart;
			face[idx].vert[1].vertIndex = qSegment + iStart;
			face[idx].vert[2].vertIndex = qSegment * 2 + 1 + iStart;
			face[idx].vert[3].vertIndex = qSegment + 1 + iStart;
		}
	}
}

void Mesh::CreateShape2(float fLength1, float fRadius1, float fLength2, float fRadius2, float fHeight)
{
	//int i;
	int nSegment = 36;
	int hSegment = nSegment / 2 + 1;
	numVerts = ((hSegment + 2) * 8) + 8 * 2; // 1/2 hinh tron + 16 dinh
	int		idx = 0, idp = 0;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;
	int iStart = 8;
	/*
		fLength1 / 4
		1 phần bên trái + 3 phần bên phải
		x1 = 0
		x2 = fLength1
		z1 = fRadius1
		z2 = -fRadius1

		A					    B
		  ******************* E   F
		  *					* ****
		  *					* ****
		  ******************* H   G
		D					    C

		A(x1,z1)
		B(x2,z1)
		C(x2,z2)
		D(x1,z2)

		E (x_C, fRadius2)
		F (x_C + fLength2, fRadius2)
		G (x_C + fLength2, -fRadius2)
		H (x_C, -fRadius2)

	*/

	numFaces = 6 * 2 + hSegment * 6 + 4;
	face = new Face[numFaces];
	pt = new Point3[numVerts];
	// Ve cube 1
	{
		float Oxz_x1 = 0;
		float Oxz_x2 = fLength1;
		float Oxz_z1 = fRadius1;
		float Oxz_z2 = -fRadius1;
		float Oxz_y = fHeight;
		pt[0].set(Oxz_x1, 0, Oxz_z1); //A
		pt[1].set(Oxz_x2, 0, Oxz_z1 + 0.1); //B
		pt[2].set(Oxz_x2, 0, Oxz_z2 - 0.1); //C
		pt[3].set(Oxz_x1, 0, Oxz_z2); //D
		pt[4].set(Oxz_x1, Oxz_y, Oxz_z1); //A'
		pt[5].set(Oxz_x2, Oxz_y, Oxz_z1 + 0.1); //B'
		pt[6].set(Oxz_x2, Oxz_y, Oxz_z2 - 0.1); //C'
		pt[7].set(Oxz_x1, Oxz_y, Oxz_z2);// D'

		//Left face
		face[0].nVerts = 4;
		face[0].vert = new VertexID[face[0].nVerts];
		face[0].vert[0].vertIndex = 1;
		face[0].vert[1].vertIndex = 5;
		face[0].vert[2].vertIndex = 6;
		face[0].vert[3].vertIndex = 2;
		for (int i = 0; i < face[0].nVerts; i++)
			face[0].vert[i].colorIndex = 0;

		//Right face
		face[1].nVerts = 4;
		face[1].vert = new VertexID[face[1].nVerts];
		face[1].vert[0].vertIndex = 0;
		face[1].vert[1].vertIndex = 3;
		face[1].vert[2].vertIndex = 7;
		face[1].vert[3].vertIndex = 4;
		for (int i = 0; i < face[1].nVerts; i++)
			face[1].vert[i].colorIndex = 1;

		//top face
		face[2].nVerts = 4;
		face[2].vert = new VertexID[face[2].nVerts];
		face[2].vert[0].vertIndex = 0;
		face[2].vert[1].vertIndex = 1;
		face[2].vert[2].vertIndex = 2;
		face[2].vert[3].vertIndex = 3;
		for (int i = 0; i < face[2].nVerts; i++)
			face[2].vert[i].colorIndex = 2;

		//bottom face
		face[3].nVerts = 4;
		face[3].vert = new VertexID[face[3].nVerts];
		face[3].vert[0].vertIndex = 7;
		face[3].vert[1].vertIndex = 6;
		face[3].vert[2].vertIndex = 5;
		face[3].vert[3].vertIndex = 4;
		for (int i = 0; i < face[3].nVerts; i++)
			face[3].vert[i].colorIndex = 3;

		//near face
		face[4].nVerts = 4;
		face[4].vert = new VertexID[face[4].nVerts];
		face[4].vert[0].vertIndex = 4;
		face[4].vert[1].vertIndex = 5;
		face[4].vert[2].vertIndex = 1;
		face[4].vert[3].vertIndex = 0;
		for (int i = 0; i < face[4].nVerts; i++)
			face[4].vert[i].colorIndex = 4;

		//Far face
		face[5].nVerts = 4;
		face[5].vert = new VertexID[face[5].nVerts];
		face[5].vert[0].vertIndex = 3;
		face[5].vert[1].vertIndex = 2;
		face[5].vert[2].vertIndex = 6;
		face[5].vert[3].vertIndex = 7;
		for (int i = 0; i < face[5].nVerts; i++)
			face[5].vert[i].colorIndex = 5;
	}
	// Ve cube 2
	{
		float Oxz_x1 = fLength1;
		float Oxz_x2 = fLength1 + fLength2;
		float Oxz_z1 = fRadius2;
		float Oxz_z2 = -fRadius2;
		float Oxz_y = fHeight;
		pt[8].set(Oxz_x1, 0, Oxz_z1); //A					0
		pt[9].set(Oxz_x2, 0, Oxz_z1); //B				1
		pt[10].set(Oxz_x2, 0, Oxz_z2); //C			2
		pt[11].set(Oxz_x1, 0, Oxz_z2); //D					3
		pt[12].set(Oxz_x1, Oxz_y, Oxz_z1); //A'				4
		pt[13].set(Oxz_x2, Oxz_y, Oxz_z1); //B'		5
		pt[14].set(Oxz_x2, Oxz_y, Oxz_z2); //C'		6
		pt[15].set(Oxz_x1, Oxz_y, Oxz_z2);// D'				7

		//Left face
		face[6].nVerts = 4;
		face[6].vert = new VertexID[face[6].nVerts];
		face[6].vert[0].vertIndex = 1 + 8;
		face[6].vert[1].vertIndex = 5 + 8;
		face[6].vert[2].vertIndex = 6 + 8;
		face[6].vert[3].vertIndex = 2 + 8;
		for (int i = 0; i < face[6].nVerts; i++)
			face[6].vert[i].colorIndex = 0;

		//Right face
		face[7].nVerts = 4;
		face[7].vert = new VertexID[face[7].nVerts];
		face[7].vert[0].vertIndex = 0 + 8;
		face[7].vert[1].vertIndex = 3 + 8;
		face[7].vert[2].vertIndex = 7 + 8;
		face[7].vert[3].vertIndex = 4 + 8;
		for (int i = 0; i < face[7].nVerts; i++)
			face[7].vert[i].colorIndex = 1;

		//top face ========> chinh sua cho nay
		face[8].nVerts = 4;
		face[8].vert = new VertexID[face[8].nVerts];
		face[8].vert[0].vertIndex = 0 + 8;
		face[8].vert[1].vertIndex = 1 + 8;
		face[8].vert[2].vertIndex = 2 + 8;
		face[8].vert[3].vertIndex = 3 + 8;
		for (int i = 0; i < face[8].nVerts; i++)
			face[8].vert[i].colorIndex = 2;

		//bottom face
		face[9].nVerts = 4;
		face[9].vert = new VertexID[face[9].nVerts];
		face[9].vert[0].vertIndex = 7 + 8;
		face[9].vert[1].vertIndex = 6 + 8;
		face[9].vert[2].vertIndex = 5 + 8;
		face[9].vert[3].vertIndex = 4 + 8;
		for (int i = 0; i < face[9].nVerts; i++)
			face[9].vert[i].colorIndex = 3;

		//near face
		face[10].nVerts = 4;
		face[10].vert = new VertexID[face[10].nVerts];
		face[10].vert[0].vertIndex = 4 + 8;
		face[10].vert[1].vertIndex = 5 + 8;
		face[10].vert[2].vertIndex = 1 + 8;
		face[10].vert[3].vertIndex = 0 + 8;
		for (int i = 0; i < face[10].nVerts; i++)
			face[10].vert[i].colorIndex = 4;

		//Far face
		face[11].nVerts = 4;
		face[11].vert = new VertexID[face[11].nVerts];
		face[11].vert[0].vertIndex = 3 + 8;
		face[11].vert[1].vertIndex = 2 + 8;
		face[11].vert[2].vertIndex = 6 + 8;
		face[11].vert[3].vertIndex = 7 + 8;
		for (int i = 0; i < face[11].nVerts; i++)
			face[11].vert[i].colorIndex = 5;

	}
	// ve hinh tron 1
	{
		idx = 12;
		idp = 16;
		float iStartFace = idx;
		float iStartPoint = idp;
		pt[idp].set(0, 0, 0); //16
		idp++; //17
		for (int i = 0; i < hSegment; i++)
		{
			x = fRadius1 * cos(fAngle * i + PI / 2.0);
			z = fRadius1 * sin(fAngle * i + PI / 2.0);
			y = 0;
			//cout << x << ";" << z << endl;
			pt[i + idp].set(x, y, z); // 17
			//cout << i + idp << endl;
		}
		for (int i = 0; i < hSegment; i++)
		{
			face[idx + i].nVerts = 3;
			face[idx + i].vert = new VertexID[face[idx + i].nVerts];
			face[idx + i].vert[0].vertIndex = idp - 1;
			face[idx + i].vert[1].vertIndex = idp + i;
			face[idx + i].vert[2].vertIndex = idp + i + 1;
			if (i == hSegment - 1)
			{
				face[idx + i].vert[2].vertIndex = idp - 1;
			}
		}

		idx += hSegment;
		idp += hSegment; //17 + 18 = 35
		pt[idp].set(0, fHeight, 0); //16
		idp++;
		for (int i = 0; i < hSegment; i++)
		{
			x = fRadius1 * cos(fAngle * i + PI / 2.0);
			z = fRadius1 * sin(fAngle * i + PI / 2.0);
			y = fHeight;
			pt[i + idp].set(x, y, z); // 17
		}
		for (int i = 0; i < hSegment; i++)
		{
			face[idx + i].nVerts = 3;
			face[idx + i].vert = new VertexID[face[idx + i].nVerts];
			face[idx + i].vert[0].vertIndex = idp - 1;
			face[idx + i].vert[1].vertIndex = idp + i;
			face[idx + i].vert[2].vertIndex = idp + i + 1;
			if (i == hSegment - 1)
			{
				face[idx + i].vert[2].vertIndex = idp - 1;
			}
		}
		idx += hSegment;
		idp += hSegment;
		for (int i = 0; i < hSegment; i++)
		{
			face[idx + i].nVerts = 4;
			face[idx + i].vert = new VertexID[face[idx + i].nVerts];
			face[idx + i].vert[0].vertIndex = i + iStartPoint;
			face[idx + i].vert[1].vertIndex = i + iStartPoint + hSegment + 1;
			face[idx + i].vert[2].vertIndex = i + iStartPoint + hSegment + 2;
			face[idx + i].vert[3].vertIndex = i + iStartPoint + 1;
			
		}
	}
	// ve hinh tron 2
	{
		idx += hSegment;
		idp += hSegment;
		float iStartFace = idx;
		float iStartPoint = idp;
		pt[idp].set(fLength1 + fLength2, 0, 0); //16
		idp++; //17
		for (int i = 0; i < hSegment; i++)
		{
			x = fRadius2 * cos(-fAngle * i + PI / 2.0);
			x += fLength1 + fLength2;
			z = fRadius2 * sin(-fAngle * i + PI / 2.0);
			y = 0;
			//cout << x << ";" << z << endl;
			pt[i + idp].set(x, y, z); // 17
			//cout << i + idp << endl;
		}
		for (int i = 0; i < hSegment; i++)
		{
			face[idx + i].nVerts = 3;
			face[idx + i].vert = new VertexID[face[idx + i].nVerts];
			face[idx + i].vert[0].vertIndex = idp - 1;
			face[idx + i].vert[1].vertIndex = idp + i;
			face[idx + i].vert[2].vertIndex = idp + i + 1;
			if (i == hSegment - 1)
			{
				face[idx + i].vert[2].vertIndex = idp - 1;
			}
		}

		idx += hSegment;
		idp += hSegment; //17 + 18 = 35
		pt[idp].set(fLength1 + fLength2, fHeight, 0); //16
		idp++;
		for (int i = 0; i < hSegment; i++)
		{
			x = fRadius1 * cos(-fAngle * i + PI / 2.0);
			x += fLength1 + fLength2;
			z = fRadius2 * sin(-fAngle * i + PI / 2.0);
			y = fHeight;
			pt[i + idp].set(x, y, z); // 17
		}
		for (int i = 0; i < hSegment; i++)
		{
			face[idx + i].nVerts = 3;
			face[idx + i].vert = new VertexID[face[idx + i].nVerts];
			face[idx + i].vert[0].vertIndex = idp - 1;
			face[idx + i].vert[1].vertIndex = idp + i;
			face[idx + i].vert[2].vertIndex = idp + i + 1;
			if (i == hSegment - 1)
			{
				face[idx + i].vert[2].vertIndex = idp - 1;
			}
		}
		idx += hSegment;
		idp += hSegment;
		for (int i = 0; i < hSegment; i++)
		{
			face[idx + i].nVerts = 4;
			face[idx + i].vert = new VertexID[face[idx + i].nVerts];
			face[idx + i].vert[0].vertIndex = i + iStartPoint;
			face[idx + i].vert[1].vertIndex = i + iStartPoint + hSegment + 1;
			face[idx + i].vert[2].vertIndex = i + iStartPoint + hSegment + 2;
			face[idx + i].vert[3].vertIndex = i + iStartPoint + 1;

		}
	}
	idx += hSegment;
	idp += hSegment;
	//cout << idx << ";" << idp << endl;
}

void Mesh::CreateShape3(float fLength1, float fLength2, float fWidth, float fHeight, float fRadius)
{
	/*
		A(0,0)
		B(0,fLength1)
		C(fWidth, fLength1)
		D(fWidth, fLength1 - fLength2)
	*/
	int nSegment = 36;
	int	idx = 0, idp = 0;
	float fAngle = 2 * PI / nSegment;
	float x, y, z;

	numVerts = 26 + nSegment * 2;
	numFaces = 6 + 5 * 3 + nSegment * 3;
	face = new Face[numFaces];
	pt = new Point3[numVerts];
	// Ve cube 1
	{
		pt[idp].set(0, 0, 0); //A
		pt[++idp].set(0, 0, fLength1); //B
		pt[++idp].set(fWidth, 0, fLength1); //C
		pt[++idp].set(fWidth, 0, fLength1 - fLength2); //D
		pt[++idp].set(0, fHeight, 0); //A'
		pt[++idp].set(0, fHeight, fLength1); //B'
		pt[++idp].set(fWidth, fHeight, fLength1); //C'
		pt[++idp].set(fWidth, fHeight, fLength1 - fLength2); //D'

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = 2;
		face[idx].vert[3].vertIndex = 3;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 4;
		face[idx].vert[1].vertIndex = 5;
		face[idx].vert[2].vertIndex = 6;
		face[idx].vert[3].vertIndex = 7;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 2;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 3;
		face[idx].vert[2].vertIndex = 7;
		face[idx].vert[3].vertIndex = 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 3;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 1;
		face[idx].vert[1].vertIndex = 2;
		face[idx].vert[2].vertIndex = 6;
		face[idx].vert[3].vertIndex = 5;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 4;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 2;
		face[idx].vert[1].vertIndex = 3;
		face[idx].vert[2].vertIndex = 7;
		face[idx].vert[3].vertIndex = 6;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 5;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = 5;
		face[idx].vert[3].vertIndex = 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 6;
		idx++;
	}
	// Ve khoi 
	{
		/*
		A(0,0)
		D(fWidth, fLength1 - fLength2)
		M(x,y)

		MA = (x,y)
		MD = (x - fWidth, y - fLength1 + fLength2)
		x(x-fWidth) + y(y - fLength1 + fLength2) = 0
		MD = d^2 = (x-fWidth)^2 + (y - fLength1 + fLength2)^2
		x = sqrt(d^2 - (y - fLength1 + fLength2)^2) + fWidth

		AD = sqrt(fWitdth^2 + (fLength1 - fLength2)^2)
		MD = fWidth
		MA = sqrt(AD^2 - MD^2)

		*/
		float MA = fLength1 - fLength2;
		float MD = fWidth;
		float alpha = asinf(MD / MA) * 2.0;
		float x_circle = sin(alpha) * MA;
		float z_circle = cos(alpha) * MA;
		float x_n = x_circle;
		float z_n = z_circle - fRadius;
		float beta = PI - (asinf(x_circle / MA) + acosf(fRadius / MD));
		float x_e = cos(beta) * fRadius + x_circle;
		float z_e = sin(beta) * fRadius + z_circle;
		int iStart = idp + 1;

		// Tam giac 1
		{
			pt[++idp].set(0, 0, 0); //A
			pt[++idp].set(MD, 0, MA); //D
			pt[++idp].set(x_circle, 0, z_circle); //M
			pt[++idp].set(0, fHeight, 0); //A'
			pt[++idp].set(MD, fHeight, MA); //D'
			pt[++idp].set(x_circle, fHeight, z_circle); //M'

			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 1;
			face[idx].vert[2].vertIndex = iStart + 2;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 3;
			face[idx].vert[1].vertIndex = iStart + 4;
			face[idx].vert[2].vertIndex = iStart + 5;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 1;
			face[idx].vert[2].vertIndex = iStart + 4;
			face[idx].vert[3].vertIndex = iStart + 3;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 2;
			face[idx].vert[2].vertIndex = iStart + 5;
			face[idx].vert[3].vertIndex = iStart + 3;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 1;
			face[idx].vert[1].vertIndex = iStart + 2;
			face[idx].vert[2].vertIndex = iStart + 5;
			face[idx].vert[3].vertIndex = iStart + 4;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;
		}
		// Tam giac 2
		{
			iStart = idp + 1;
			pt[++idp].set(0, 0, 0); //A
			pt[++idp].set(x_circle, 0, z_circle); //M
			pt[++idp].set(x_n, 0, z_n); //N
			pt[++idp].set(0, fHeight, 0); //A'
			pt[++idp].set(x_circle, fHeight, z_circle); //M'
			pt[++idp].set(x_n, fHeight, z_n); //N'

			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 1;
			face[idx].vert[2].vertIndex = iStart + 2;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 3;
			face[idx].vert[1].vertIndex = iStart + 4;
			face[idx].vert[2].vertIndex = iStart + 5;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 1;
			face[idx].vert[2].vertIndex = iStart + 4;
			face[idx].vert[3].vertIndex = iStart + 3;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 2;
			face[idx].vert[2].vertIndex = iStart + 5;
			face[idx].vert[3].vertIndex = iStart + 3;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 1;
			face[idx].vert[1].vertIndex = iStart + 2;
			face[idx].vert[2].vertIndex = iStart + 5;
			face[idx].vert[3].vertIndex = iStart + 4;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;
		}
		// Tam giac 3
		{
			iStart = idp + 1;
			pt[++idp].set(x_circle, 0, z_circle); //M
			pt[++idp].set(MD, 0, MA); //D
			pt[++idp].set(x_e, 0, z_e); //E
			pt[++idp].set(x_circle, fHeight, z_circle); //M'
			pt[++idp].set(MD, fHeight, MA); //D'
			pt[++idp].set(x_e, fHeight, z_e); //E'

			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 1;
			face[idx].vert[2].vertIndex = iStart + 2;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 3;
			face[idx].vert[1].vertIndex = iStart + 4;
			face[idx].vert[2].vertIndex = iStart + 5;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 1;
			face[idx].vert[2].vertIndex = iStart + 4;
			face[idx].vert[3].vertIndex = iStart + 3;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 2;
			face[idx].vert[2].vertIndex = iStart + 5;
			face[idx].vert[3].vertIndex = iStart + 3;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 1;
			face[idx].vert[1].vertIndex = iStart + 2;
			face[idx].vert[2].vertIndex = iStart + 5;
			face[idx].vert[3].vertIndex = iStart + 4;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;
		}
		// hinh tron
		{
			iStart = idp + 1;
			float iStop;
			float iCount = 0;
			pt[iStart].set(x_circle, 0, z_circle);
			//cout << "===" << iStart << endl;
			idp++;
			for (int i = 0; i < nSegment/2; i++)
			{
				//cout << sin(fAngle * i) << ";" << cos(fAngle * i) << " -- " << fAngle * i << ">" << beta << endl;
				x = fRadius * sin(fAngle * i) + x_circle;
				z = fRadius * -cos(fAngle * i) + z_circle;
				y = 0;
				pt[i + iStart + 1].set(x, y, z); // 17
				idp++;
				//cout << i + iStart + 1 << endl;
				//cout << i + idp << endl;
			}
			int iStart2 = idp + 1;
			//cout << "===" << iStart2 << endl;
			pt[iStart2].set(x_circle, fHeight, z_circle);
			idp++;
			for (int i = 0; i < nSegment/2; i++)
			{
				x = fRadius * sin(fAngle * i) + x_circle; 
				z = fRadius * -cos(fAngle * i) + z_circle;
				y = fHeight;
				//cout << x << ";" << z << endl;
				pt[i + iStart2 + 1].set(x, y, z); // 17
				//cout << i + iStart2 + 1 << endl;
				idp++;
				//cout << i + idp << endl;
			}
			for (int i = 0; i < nSegment/2; i++)
			{
				face[idx].nVerts = 3;
				face[idx].vert = new VertexID[face[idx].nVerts];
				face[idx].vert[0].vertIndex = iStart;
				face[idx].vert[1].vertIndex = iStart + i + 1;
				face[idx].vert[2].vertIndex = iStart + i + 2;
				if (i == nSegment/2 - 1)
				{
					cout << pt[iStart + i + 1].y << endl;
					face[idx].vert[2].vertIndex = iStart;
				}
				idx++;
			}
			for (int i = 0; i < nSegment/2; i++)
			{
				face[idx].nVerts = 3;
				face[idx].vert = new VertexID[face[idx].nVerts];
				face[idx].vert[0].vertIndex = iStart2;
				face[idx].vert[1].vertIndex = iStart2 + i + 1;
				face[idx].vert[2].vertIndex = iStart2 + i + 2;
				if (i == nSegment/2 - 1)
				{
					face[idx].vert[2].vertIndex = iStart2;
				}
				idx++;
			}
			for (int i = 0; i < nSegment/2; i++)
			{
				face[idx].nVerts = 4;
				face[idx].vert = new VertexID[face[idx].nVerts];
				face[idx].vert[0].vertIndex = iStart + i + 1;
				face[idx].vert[1].vertIndex = iStart2 + i + 1;
				face[idx].vert[2].vertIndex = iStart2 + i + 2;
				face[idx].vert[3].vertIndex = iStart + i + 2;
				if (i == nSegment / 2 - 1)
				{
					face[idx].vert[2].vertIndex = iStart2 + 1;
					face[idx].vert[3].vertIndex = iStart + 1;
				}
				idx++;
			}
		}
	}
}


void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}



