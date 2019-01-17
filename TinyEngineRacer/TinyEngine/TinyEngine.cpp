#include "TinyEngine.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <chrono>
#include <varargs.h>
#define TAU 6.28318530718f

/* NOTE
 * This engine is not for any sort of serious use, it's just used as a tool for teaching basic programming
 * However; if you're here to hack, here are some things you could try implementing;

 - Drawing sprites/images
 - Changing font
 - Mouse support
 - Gamepad support
 - Sound support
 - Refactor into separate files
 - Make the engine object-oriented (using classes and/or structs)

 * Good luck!
 */

// Variables controlling the SDL context
static SDL_Window* Window;
static SDL_Renderer* Renderer;
static bool IsOpen = false;

static SDL_Color CurrentColor = { 255, 255, 255, 255 };

// Delta tracking
using namespace std::chrono;
using hr_clock = high_resolution_clock;

static hr_clock::time_point LastFrameTime;
static float FrameDelta = 0.f;

// Text stuff
static TTF_Font* StandardFont = nullptr;

SDL_Texture* LoadTexture;
SDL_Texture* Texture;
SDL_Surface* ImageSurface;

// Input stuff
struct InputState
{
	bool Pressed;
	int FrameNum;
};
static InputState KeyStates[(unsigned int)Key::MAX];
static int CurrentFrameNum = 1;

void engInit(unsigned int ScreenWidth, unsigned int ScreenHeight)
{
	// Initalize SDL and TTF
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);

	// Open window
	Window = SDL_CreateWindow("Racer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	Texture = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 600);
	LoadTexture = NULL;

	IsOpen = true;

	// Set last frame time to now, so that delta doesnt get messed up later
	LastFrameTime = hr_clock::now();

	// Load standard font
	StandardFont = TTF_OpenFont("Roboto.ttf", 24);
}

void engClear()
{
	// Clear for next frame
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(Renderer);
}

void engUpdate()
{
	CurrentFrameNum++;

	// Poll window events
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			engClose();

		if (e.type == SDL_KEYDOWN)
		{
			// We dont care about repeats
			if (e.key.repeat == 0)
			{
				InputState& state = KeyStates[e.key.keysym.scancode];
				state.Pressed = true;
				state.FrameNum = CurrentFrameNum;
			}
		}

		if (e.type == SDL_KEYUP)
		{
			InputState& state = KeyStates[e.key.keysym.scancode];
			state.Pressed = false;
			state.FrameNum = CurrentFrameNum;
		}
	}

	// Calculate next frame delta
	hr_clock::time_point Now = hr_clock::now();
	FrameDelta = duration_cast<microseconds>(Now - LastFrameTime).count() * 1e-6f;  // 10^6 microseconds in a second
	LastFrameTime = Now;

	// Present SDL renderer
	SDL_RenderPresent(Renderer);
	engClear();

	// Do a small delay so we dont fry the CPU
	SDL_Delay(1);
}

void engClose()
{
	// 'Closes' the window (sets the flag to close, actual closing happens in Destroy
	IsOpen = false;
}

void engDestroy()
{
	// Destroys the inner APIs and does a clean exit
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);

	Renderer = nullptr;
	Window = nullptr;

	TTF_CloseFont(StandardFont);
	StandardFont = nullptr;

	SDL_Quit();
	TTF_Quit();
}

bool engIsOpen()
{
	// Return if the window is open
	return IsOpen;
}

void engDelay(int Milliseconds)
{
	// Draw whats up, so its not just black
	SDL_RenderPresent(Renderer);
	SDL_Delay(Milliseconds);
}

Key engWaitKey()
{
	// Draw whats up, so its not just black
	SDL_RenderPresent(Renderer);

	SDL_Event e;

	do
	{
		SDL_WaitEvent(&e);
	} while (e.type != SDL_KEYDOWN && e.type != SDL_QUIT);

	if (e.type == SDL_QUIT)
	{
		// We want to handle quitting messages, so people dont think we're locked
		engClose();
		return Key::Undefined;
	}
	else
		return (Key)e.key.keysym.scancode;
}

float engDelta()
{
	// Returns the deltatime for this frame
	return FrameDelta;
}

void engSetColor(uint8 Red, uint8 Green, uint8 Blue)
{
	CurrentColor.r = Red;
	CurrentColor.g = Green;
	CurrentColor.b = Blue;
	CurrentColor.a = 255;
}

void engSetColor(unsigned int Color)
{
	CurrentColor.r = (Color >> 24) & 0xFF;
	CurrentColor.g = (Color >> 16) & 0xFF;
	CurrentColor.b = (Color >> 8) & 0xFF;
	CurrentColor.a = Color & 0xFF;
}

void engDrawRect(int X, int Y, int Width, int Height)
{
	SDL_SetRenderDrawColor(Renderer, CurrentColor.r, CurrentColor.g, CurrentColor.b, CurrentColor.a);

	SDL_Rect rect = {X - (Width/2), Y - Height, Width, Height};
	SDL_RenderFillRect(Renderer, &rect);
}

void engDrawRects(SDL_Rect* Rects[], int RectsCount)
{
	SDL_SetRenderDrawColor(Renderer, CurrentColor.r, CurrentColor.g, CurrentColor.b, CurrentColor.a);
//	SDL_RenderFillRects(Renderer, *Rects, RectsCount);
}

SDL_Rect engMakeRect(int X, int Y, int Width, int Height)
{
	SDL_Rect rect = { X - (Width / 2), Y - Height, Width, Height };
	return rect;
}

void engDrawLine(int X, int Y, int X2, int Y2)
{
	SDL_SetRenderDrawColor(Renderer, CurrentColor.r, CurrentColor.g, CurrentColor.b, CurrentColor.a);
	SDL_RenderDrawLine(Renderer, X, Y, X2, Y2);
}

void engDrawSphere(int X, int Y, float Radius)
{
	const int SPHERE_RES = 500;
	SDL_Point SpherePoints[SPHERE_RES];
	for (int i = 0; i < SPHERE_RES; i++)
	{
		float Angle = ((float)i / (float)(SPHERE_RES - 1)) * TAU;
		
		SDL_Point Point;
		Point.x = X + Radius * cos(Angle);
		Point.y = Y + Radius * sin(Angle);

		SpherePoints[i] = Point;
	}
	
	SDL_SetRenderDrawColor(Renderer, CurrentColor.r, CurrentColor.g, CurrentColor.b, CurrentColor.a);
	SDL_RenderDrawLines(Renderer, SpherePoints, SPHERE_RES);
}

void engDrawString(int X, int Y, const char* String)
{
	// Render text onto surface
	SDL_Surface* MsgSurface = TTF_RenderText_Solid(StandardFont, String, CurrentColor);
	SDL_Texture* MsgTexture = SDL_CreateTextureFromSurface(Renderer, MsgSurface);

	// Find out dimensions
	int MsgW = 0, MsgH = 0;
	TTF_SizeText(StandardFont, String, &MsgW, &MsgH);

	// Copy that bad boy
	SDL_Rect MessageRect = { X, Y, MsgW, MsgH };
	SDL_RenderCopy(Renderer, MsgTexture, NULL, &MessageRect);

	// Remember to clean up
	SDL_FreeSurface(MsgSurface);
	SDL_DestroyTexture(MsgTexture);
}

void engDrawStringFormat(int X, int Y, const char* String, ...)
{
	static char Buffer[1024];

	// Vararg lists, scary stuff
	va_list vl;
	va_start(vl, String);
	vsprintf_s<1024>(Buffer, String, vl);
	va_end(vl);

	engDrawString(X, Y, Buffer);
}

void engDrawSprite(int X, int Y, int Size_w, int Size_h, int Image_w, int Image_h, int ImgX, int ImgY, char* ImagePath)
{
	ImageSurface = IMG_Load(ImagePath);

	SDL_Texture* SpriteTexture = SDL_CreateTextureFromSurface(Renderer, ImageSurface);

	SDL_SetRenderDrawColor(Renderer, CurrentColor.r, CurrentColor.g, CurrentColor.b, CurrentColor.a);
	SDL_Rect rect = { X,Y,Size_w,Size_h };
	SDL_Rect src{ ImgX,ImgY,Image_w, Image_h };

	SDL_RenderCopy(Renderer, SpriteTexture, &src, &rect);
	SDL_DestroyTexture(SpriteTexture);
	SDL_FreeSurface(ImageSurface);
}

bool engGetKey(Key InKey)
{
	return KeyStates[(int)InKey].Pressed;
}

bool engGetKeyDown(Key InKey)
{
	// Is pressed and changed this frame
	InputState& State = KeyStates[(int)InKey];
	return State.Pressed && State.FrameNum == CurrentFrameNum;
}

bool engGetKeyUp(Key InKey)
{
	// Is not pressed and changed this frame
	InputState& State = KeyStates[(int)InKey];
	return !State.Pressed && State.FrameNum == CurrentFrameNum;
}

void engGetMousePosition(int& x, int& y)
{
	SDL_GetMouseState(&x, &y);
}
