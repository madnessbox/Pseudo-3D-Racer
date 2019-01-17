#include "WorldGenerator.h"
#include "TinyEngine.h"
#include "Vector3.h"
#include "Color.h"
#include "RoadMapSegment.h"
#include "Car.h"

#include <SDL/SDL.h>

const unsigned int NumOfRoadSegments = 10000;
const float RoadSegmentSeperationScale = 0.2f;
const unsigned int RenderDistance = 700;
const unsigned int MapSegments = 50;
RoadSegment RoadSegmentsArray[NumOfRoadSegments];
SDL_Rect* RectsToDraw[RenderDistance * 6];

// Contains Map data
RoadMapSegment RoadMap[MapSegments];

float DX, DDX, CurrentX = 0;
float DY, DDY, CurrentY = 0;
int HorizonHeight = 500;

WorldGenerator::WorldGenerator(unsigned int WindowWidth, unsigned int WindowHeight, Camera& Cam) :
	WindowWidth(WindowWidth), WindowHeight(WindowHeight), Cam(Cam)
{
	GenerateRoad();

	//PlayerCar = new Car(WindowWidth, WindowHeight);
}

void WorldGenerator::GenerateRoad()
{
	for (int i = 0; i < NumOfRoadSegments; i++)
	{
		Vector3 NewPos(0, 0, i * RoadSegmentSeperationScale);
		RoadSegment RoadSeg;
		RoadSeg.Position3D = NewPos;
		RoadSeg.Index = i;
		RoadSegmentsArray[i] = RoadSeg;
	}


	RoadSegmentsArray[100].RightSideSprite = "palm_tree.png";

	RoadMap[0].Length = 500;
	RoadMap[0].Curvature = 0.f;

	RoadMap[1].Length = 200;
	RoadMap[1].Curvature = 0.005f;

	RoadMap[2].Length = 300;
	RoadMap[2].Curvature = 0.f;

	RoadMap[3].Length = 1000;
	RoadMap[3].Curvature = 0.05f;
	RoadMap[3].Hill = -0.001f;

	RoadMap[4].Length = 200;
	RoadMap[4].Curvature = 0.f;
	RoadMap[4].Hill = 0.0005f;

	RoadMap[6].Length = 200;
	RoadMap[6].Curvature = 0.f;

	RoadMap[7].Length = 200;
	RoadMap[7].Curvature = 0.02f;


	RoadMap[8].Length = 100;
	RoadMap[8].Curvature = 0;
	RoadMap[8].Hill = 0.0005f;

	RoadMap[9].Length = 50;
	RoadMap[9].Curvature = 0;
	RoadMap[9].Hill = -0.0005f;

	RoadMap[10].Length = 1000;
	RoadMap[10].Curvature = 0;

	RoadMap[11].Length = 1000;
	RoadMap[11].Curvature = 0.005f;


	int TotalDistance = 0;

	for (int i = 0; i < MapSegments; i++)
	{
		for (int y = TotalDistance; y <= TotalDistance + RoadMap[i].Length; y++)
		{
			RoadSegmentsArray[y].Curve = RoadMap[i].Curvature;
			RoadSegmentsArray[y].Hill = RoadMap[i].Hill;
		}

		TotalDistance += RoadMap[i].Length;
	}

}


void WorldGenerator::DrawRoad()
{
	DDX = 0;
	DX = 0;

	DDY = 0;
	DY = 0;

	CurrentX = WindowWidth / 2;
	CurrentY = 0;
	int RenderDistanceBuffer = Cam.Position.Z * (1 / RoadSegmentSeperationScale);
	RenderDistanceBuffer = RenderDistanceBuffer < 0 ? 0 : RenderDistanceBuffer;

	// Only draw the road segments within render distance
	for (int i = RenderDistanceBuffer; i < RenderDistanceBuffer + RenderDistance; i++)
	{
		// If the segment is infront of us
		if (RoadSegmentsArray[i].Position3D.Z > RenderDistanceBuffer)
		{
			DX = RoadSegmentsArray[RenderDistanceBuffer].Curve;
		}
		else if (RoadSegmentsArray[i].Position3D.Z < RenderDistanceBuffer)
		{
			DX = RoadSegmentsArray[i].Curve;
		}

		CurrentX += DDX;
		DDX += DX;


		if (RoadSegmentsArray[i].Position3D.Z > RenderDistanceBuffer)
		{
			DY = RoadSegmentsArray[RenderDistanceBuffer].Hill;
		}
		else if (RoadSegmentsArray[i].Position3D.Z < RenderDistanceBuffer)
		{
			DY = RoadSegmentsArray[i].Hill;
		}

		CurrentY += DDY;
		RoadSegmentsArray[i].Position3D.Y = CurrentY;

		DDY += DY;

		CalculateRoadLineScreenPositions(RoadSegmentsArray[i], i);
	}

	int z = 0;

	for (int i = RenderDistanceBuffer + RenderDistance; i > RenderDistanceBuffer; i--)
	{
		DrawRoadLine(RoadSegmentsArray[i], i, z);
		z++;
	}
}

void WorldGenerator::DrawRoadLine(RoadSegment& S, int Index, int RectsIndex)
{
	// Draw Ground
	//engSetColor(VAPORPURP);
	//engDrawRect(WindowWidth / 2, S.ScreenPosition.y, WindowWidth, S.ZLength);

	if (Index % 50 == 0)
	{
		engSetColor(VAPORBLUE);
		engDrawRect(WindowWidth / 2, S.ScreenPosition.y, WindowWidth, S.ZLength * 0.8f);

		//RectsToDraw[RectsIndex] = &engMakeRect(WindowWidth / 2, S.ScreenPosition.y, WindowWidth, S.ZLength * 0.8f);
	}

	for (int i = 1; i <= 5; i++)
	{
		engSetColor(VAPORBLUE);
		engDrawRect(S.ScreenPosition.x + (S.Width * i), S.ScreenPosition.y, S.ZLength * 1.2f, S.ZLength);
		engDrawRect(S.ScreenPosition.x - (S.Width * i), S.ScreenPosition.y, S.ZLength * 1.2f, S.ZLength);

		//RectsToDraw[RectsIndex] = &engMakeRect(S.ScreenPosition.x + (S.Width * i), S.ScreenPosition.y, S.ZLength * 1.2f, S.ZLength);
		//RectsToDraw[RectsIndex] = &engMakeRect(S.ScreenPosition.x - (S.Width * i), S.ScreenPosition.y, S.ZLength * 1.2f, S.ZLength);

	}

	// Set Rubble Color
	if (Index % 50 == 0 || Index % 50 == 1)
		engSetColor(0xFFFFFFFF);
	else
		engSetColor(0xb967ffFF);

	// Draw Rubble
	engDrawRect(S.ScreenPosition.x, S.ScreenPosition.y, S.Width * 1.1f, S.ZLength);
	//RectsToDraw[RectsIndex] = &engMakeRect(S.ScreenPosition.x, S.ScreenPosition.y, S.Width * 1.1f, S.ZLength);


	// Draw Road
	engSetColor(S.RenderColor);
	engDrawRect(S.ScreenPosition.x, S.ScreenPosition.y, S.Width, S.ZLength);
	//RectsToDraw[RectsIndex] = &engMakeRect(S.ScreenPosition.x, S.ScreenPosition.y, S.Width, S.ZLength);


	// Draw RoadLines
	if (Index % 20 > 0 && Index % 20 < 10)
	{
		engSetColor(0xFFFFFFFF);
		engDrawRect(S.ScreenPosition.x, S.ScreenPosition.y, S.Width * 0.05f, S.ZLength);
		//RectsToDraw[RectsIndex] = &engMakeRect(S.ScreenPosition.x, S.ScreenPosition.y, S.Width * 0.05f, S.ZLength);

	}


	if (Index % 50 == 0)
	{
		engDrawSprite(S.ScreenPosition.x + (S.Width * 0.3f), S.ScreenPosition.y - (540 * S.ZLength) / 10, (215 * S.ZLength) / 10, (540 * S.ZLength) / 10, 215, 540, 0, 0, "palm_treeS.png");
		engDrawSprite(S.ScreenPosition.x - (S.Width * 0.7f), S.ScreenPosition.y - (540 * S.ZLength) / 10, (215 * S.ZLength) / 10, (540 * S.ZLength) / 10, 215, 540, 0, 0, "palm_tree_rS.png");
	}

}

void WorldGenerator::CalculateRoadLineScreenPositions(RoadSegment& S, int I)
{
	Vector ScreenPosition(0);
	ScreenPosition = S.Project(Cam);

	if (S.Scale > 0)
	{
		S.ScreenPosition = Vector(CurrentX + ScreenPosition.x, ScreenPosition.y);
	}
}

void WorldGenerator::DrawBackground()
{
	// Draw Sky
	engSetColor(0x2d1f36FF);
	engDrawRect(WindowWidth / 2, WindowHeight, WindowWidth, WindowHeight);


	// Draw Gradient background
	/*for (int i = 0; i < 10; i++)
	{

	}*/

	// Draw Sun
	engDrawSprite((WindowWidth / 2) - 250, (WindowHeight / 2) - 400, 500, 465, 500, 465, 0, 0, "sun.png");
}

void WorldGenerator::DrawCar()
{
	PlayerCar->RenderCar();
}

void WorldGenerator::DrawWorld()
{
	DrawBackground();
	DrawRoad();
	//engDrawRects(RectsToDraw, RenderDistance * 6);

	DrawCar();
}