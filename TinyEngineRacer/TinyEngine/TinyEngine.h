#pragma once
#include "Key.h"

typedef unsigned char uint8;

/*** ENGINE CONTROL ***/
// Starts the engine and opens a window
void engInit(unsigned int WindowWidth, unsigned int WindowHeight);
// Updates window, drawing, input and frame delta
void engUpdate();
// Flags the engine to shut down
void engClose();
// Destroys engine and shuts everything down. DONT call any engine functions after this.
void engDestroy();

// Gets if the engine is currently running
bool engIsOpen();

/*** FLOW CONTROL ***/
// Updates drawing and halts program for a set amount of time
void engDelay(int Milliseconds);
// Updates drawing and halts until the user hits a key, then returns that key
Key engWaitKey();

// Current frame delta time, NOTE: This wont be valid unless you're using engUpdate()
float engDelta();

/*** RENDERING ***/
// Clears the screen
void engClear();

// Sets current drawing color (RGB or HEX)
void engSetColor(uint8 Red, uint8 Green, uint8 Blue);
void engSetColor(unsigned int Color);

// Draws a filled rectangle at (X, Y) with dimensions (Width, Height)
void engDrawRect(int X, int Y, int Width, int Height);

void engDrawRects(class SDL_Rect* Rects[], int RectsCount);

class SDL_Rect engMakeRect(int X, int Y, int Width, int Height);
// Draws a line between pixels of (X, Y) and (X2, Y2)
void engDrawLine(int X, int Y, int X2, int Y2);
// Draw a sphere at position (X,Y) with radius (Radius)
void engDrawSphere(int X, int Y, float Radius);
// Draws a string at location
void engDrawString(int X, int Y, const char* String);
// Draws a string at location with formatting options
void engDrawStringFormat(int X, int Y, const char* String, ...);

void engDrawSprite(int x, int y, int size_w, int size_h, int image_w, int image_h, int imgX, int imgY, char* imagePath);

/*** INPUT ***/
/*** Note: None of these will do anything unless you call engUpdate() ***/
// Get if a key is pressed
bool engGetKey(Key InKey);
// Get if a key was pressed this frame
bool engGetKeyDown(Key InKey);
// Get if a key was released this frame
bool engGetKeyUp(Key InKey);

void engGetMousePosition(int& x, int& y);