#pragma once
#include "RoadSegment.h"
#include "Camera.h"

class WorldGenerator
{
public:
	WorldGenerator(unsigned int WindowWidth, unsigned int WindowHeight, Camera& Cam);

	// Draw world
	void GenerateRoad();
	void DrawWorld();

	Camera& Cam;
	class Car* PlayerCar;

private:
	unsigned int WindowWidth;
	unsigned int WindowHeight;

	void DrawRoad();
	void DrawBackground();
	void DrawCar();

	void DrawRoadLine(RoadSegment& S, int Index, int RectsIndex);
	void CalculateRoadLineScreenPositions(RoadSegment& S, int I);

};