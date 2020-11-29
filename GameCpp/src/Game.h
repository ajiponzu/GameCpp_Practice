// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "SDL.h"

// Vector2 struct just stores x/y coordinates
// (for now)
struct Vector2
{
	float x;
	float y;
};

	struct MBall {
		// Position of ball
		Vector2 mBallPos;
		// Velocity of ball
		Vector2 mBallVel;
		MBall(float a, float b, float c, float d)
		{
			mBallPos.x = a;
			mBallPos.y = b;
			mBallVel.x = c;
			mBallVel.y = d;
		}
	};

// Game class
class Game
{
public:
	Game();
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the gam
	void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void UpdateMBar(const float&);
	void UpdateEBar(const float&);
	void ColidBoll(const bool);
	void GenerateOutput();

	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;
	// Number of ticks since start of game
	Uint32 mTicksCount;
	// Game should continue to run
	bool mIsRunning;
	
	// Pong specific
	// Direction of paddle
	int mPaddleDir;
	int ePaddleDir;
	// Position of paddle
	Vector2 mPaddlePos;
	Vector2 ePaddlePos;

	std::vector<MBall> balls;
};
