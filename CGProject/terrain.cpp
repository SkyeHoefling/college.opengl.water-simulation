#include "terrain.h"
#include "math.h"
#include <stdlib.h>
#include <time.h>

terrain::terrain(world wor)
{
	w = wor;
	tris = NULL;
	drawNormals = false;
}

terrain::~terrain(void)
{
}

void terrain::display(){
	// for loop, draw each point in the Grid, using the x, y, and z as set by the initialize.
	glColor3f(0.0, 0.0, 1.0);
	/*int i;
	// draw points
	glBegin(GL_POINTS);
		for ( i = 0; i < (w.getLength() * w.getWidth()); i++)
		{
			glVertex3f(w.getGrid()[i].getX(), w.getGrid()[i].getY(), w.getGrid()[i].getZ());
		}
	glEnd();*/
	// draw lines between consecutive vertices to show quads
	int j, k, triIter;
	triIter = 0;
	float lx, ly, lz, ex, ey, ez, mx, my, mz;
	vector3 p1,p2,p3;
	int triCount = w.getWidth() * w.getLength() * 2;
	tris = new triangle[triCount];
	for (k = 0; k < w.getLength(); k++)
	{
		for (j = 0; j < w.getWidth(); j++)
		{
			glColor3f(0,0,1);
			glBegin(GL_LINES);
			// vertical
			if (j < w.getWidth() - 1)
			{
				lx = w.getGrid()[j + (k * w.getWidth())].getX();
				ly = w.getGrid()[j + (k * w.getWidth())].getY();
				lz = w.getGrid()[j + (k * w.getWidth())].getZ();
				ex = w.getGrid()[j + 1 + (k * w.getWidth())].getX();
				ey = w.getGrid()[j + 1 + (k * w.getWidth())].getY();
				ez = w.getGrid()[j + 1 + (k * w.getWidth())].getZ();
				p1 = vector3(ex,ey,ez);
				glVertex3f(lx, ly, lz);
				glVertex3f(ex, ey, ez);
			}
			// horizontal lines
			if (k < w.getLength() - 1)
			{
				lx = w.getGrid()[j + (k * w.getWidth())].getX();
				ly = w.getGrid()[j + (k * w.getWidth())].getY();
				lz = w.getGrid()[j + (k * w.getWidth())].getZ();
				ex = w.getGrid()[j + w.getWidth() + (k * w.getWidth())].getX();
				ey = w.getGrid()[j + w.getWidth() + (k * w.getWidth())].getY();
				ez = w.getGrid()[j + w.getWidth() + (k * w.getWidth())].getZ();
				p2 = vector3(ex,ey,ez);
				glVertex3f(lx, ly, lz);
				glVertex3f(ex, ey, ez);
			}
			// diagonal lines
			if (j < w.getWidth() - 1 && k < w.getLength() - 1)
			{
				lx = w.getGrid()[j + (k * w.getWidth())].getX();
				ly = w.getGrid()[j + (k * w.getWidth())].getY();
				lz = w.getGrid()[j + (k * w.getWidth())].getZ();
				ex = w.getGrid()[j + w.getWidth() + (k * w.getWidth()) + 1].getX();
				ey = w.getGrid()[j + w.getWidth() + (k * w.getWidth()) + 1].getY();
				ez = w.getGrid()[j + w.getWidth() + (k * w.getWidth()) + 1].getZ();
				glVertex3f(lx, ly, lz);
				glVertex3f(ex, ey, ez);

				// now that we have made 2 triangles add them
				tris[triIter] = triangle(vector3(ex,ey,ez), p1, vector3(lx,ly,lz));
				if(drawNormals)tris[triIter].drawNormal();
				triIter++;
				tris[triIter] = triangle(vector3(lx,ly,lz), p2, vector3(ex,ey,ez));
				if(drawNormals)tris[triIter].drawNormal();
				triIter++;

			}
			glEnd();

			
			//glBegin(GL_LINES);
			/*if (j < w.getWidth() - 1 && k < w.getLength() - 1)
			{
				lx = w.getGrid()[j + (k * w.getWidth())].getX();
				ly = w.getGrid()[j + (k * w.getWidth())].getY();
				lz = w.getGrid()[j + (k * w.getWidth())].getZ();
				mx = w.getGrid()[j + w.getWidth() + (k * w.getWidth())].getX();
				my = w.getGrid()[j + w.getWidth() + (k * w.getWidth())].getY();
				mz = w.getGrid()[j + w.getWidth() + (k * w.getWidth())].getZ();
				ex = w.getGrid()[j + w.getWidth() + (k * w.getWidth()) + 1].getX();
				ey = w.getGrid()[j + w.getWidth() + (k * w.getWidth()) + 1].getY();
				ez = w.getGrid()[j + w.getWidth() + (k * w.getWidth()) + 1].getZ();
				//glVertex3f(lx, ly, lz);
				//glVertex3f(mx, my, mz);
				//glVertex3f(ex, ey, ez);
				//glVertex3f(lx, ly, lz);

				// build triangles
				//tris[triIter] = triangle(vector3(lx, ly, lx), vector3(mx, my, mz), vector3(ex, ey, ez));
				//tris[triIter].drawNormal();
				//triIter++;
			}*/
			//glEnd();
		}
	}	
}

void terrain::generate(int iterations, int gridWidth, int gridLength, float maxHeight)
{
	particleDeposition(iterations, gridWidth, gridLength, maxHeight);
}

void terrain::smooth(int iterations, int gridWidth, int gridLength, float k)
{
	smoothTerrain(5, gridWidth, gridLength, k);
}

bool terrain::particleDeposition(int iterations, int gridWidth, int gridLength, float maxHeight)
{
	// ints for use in the method
	// xGrid and zGrid to generate a point
	// direction to randomly select a direction to move from the point
	// an iterator
	int xGrid, zGrid, direction, iter;

	// terrain height is all set to 0 in the main

	// randomly generate a point
	xGrid = rand() % gridWidth;
	zGrid = rand() % gridLength;

	for (iter = 0; iter < iterations; iter++)
	{
		// chose a random direction
		direction = rand() % 4;

		// direction leads to a cardinal direction
		// direction 0 - increment x
		if (direction == 0)
		{
			xGrid += 1;
			// if we are over the grid, reset
			if (xGrid >= gridWidth)
			{
				xGrid = 0;
			}
		}
		// direction 1 - decrement x
		if (direction == 1)
		{
			xGrid -= 1;
			// if we are under the grid, reset
			if (xGrid < 0)
			{
				xGrid = gridWidth - 1;
			}
		}
		// direction 2 - increment z
		if (direction == 2)
		{
			zGrid += 1;
			// if we are over the grid, reset
			if (zGrid >= gridLength)
			{
				zGrid = 0;
			}
		}
		// direction 3 - decrement z
		if (direction == 3)
		{
			zGrid -= 1;
			// if we are under the grid, reset
			if(zGrid < 0)
			{
				zGrid = gridLength - 1;
			}
		}

		float adjHeight = ((float)(rand() % 100) / 100) * maxHeight;

		// set the height of that grid point
		w.getGrid()[xGrid * gridWidth + zGrid].setY(w.getGrid()[xGrid * gridWidth + zGrid].getY() + maxHeight);
	}

	return true;
}

bool terrain::smoothTerrain(int iterations, int gridWidth, int gridLength, float h)
{
	for (int i = 0; i < iterations; i++)
	{
		int j, k;
		// rows left to right
		for (j = 1; j < gridWidth; j++)
		{
			for (k = 0; k < gridLength; k++)
			{
				float height = (w.getGrid()[(j - 1) * gridWidth + k].getY() * (1-h)) +
							   (w.getGrid()[j * gridWidth + k].getY() * h);
				//w.getGrid()[j * gridWidth + k].setY(height);
				w.setPointAtY(j*gridWidth+k, height);
			}
		}

		// rows left to right
		for (j = gridWidth - 2; j < -1; j--)
		{
			for (k = 0; k < gridLength; k++)
			{
				float height = ((w.getGrid()[(j + 1) * gridWidth + k].getY()) * (1-h)) +
							   ((w.getGrid()[j * gridWidth + k].getY()) * h);
				//w.getGrid()[j * gridWidth + k].setY(height);
				w.setPointAtY(j*gridWidth+k,height);
			}
		}

		// columns bottom to top
		for (j = 0; j < gridWidth; j++)
		{
			for (k = 1; k < gridLength; k++)
			{
				float height = ((w.getGrid()[j * gridWidth + (k - 1)].getY()) * (1-h)) +
							   ((w.getGrid()[j * gridWidth + k].getY()) * h);
				//w.getGrid()[j * gridWidth + k].setY(height);
				w.setPointAtY(j*gridWidth+k,height);
			}
		}

		// columns top to bottom
		for (j = 0; j < gridWidth; j++)
		{
			for (k = gridLength - 2; k < -1; k--)
			{
				float height = ((w.getGrid()[j * gridWidth + (k + 1)].getY()) * (1-h)) +
							   ((w.getGrid()[j * gridWidth + k].getY()) * h);
				//w.getGrid()[j * gridWidth + k].setY(height);
				w.setPointAtY(j*gridWidth+k,height);
			}
		}
	}
	return true;
}
bool terrain::toggleNormals(){ drawNormals = !drawNormals; return drawNormals; }
triangle terrain::getTri(vector3* j){
	int triCount = w.getWidth() * w.getLength() * 2;
	for(int i = 0; i < triCount; i ++){
		if(tris[i].pointInTri(*j)) return tris[i];	
	}
}