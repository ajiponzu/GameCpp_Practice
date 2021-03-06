// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
	, mPaddleDir(0)
	, ePaddleDir(0)
{
}

bool Game::Initialize()
{
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	//
	mPaddlePos.x = 10.0f;
	ePaddlePos.x = 1024.0f - 20.0f;
	ePaddlePos.y = mPaddlePos.y = 768.0f / 2.0f;
	auto a = 1024.0f / 2.0f, b = 768.0f / 2.0f, c = -150.0f, d = 235.0f;
	balls.push_back(MBall(a, b, c, d));
	balls.push_back(MBall(a, b + 50, -c, -d));
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	// Update paddle direction based on W/S keys
	mPaddleDir = 0;
	ePaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
	if (state[SDL_SCANCODE_I])
	{
		ePaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_K])
	{
		ePaddleDir += 1;
	}
}

void Game::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();

	// Update paddle position based on direction
	UpdateMBar(deltaTime);
	UpdateEBar(deltaTime);

	// Update ball position based on ball velocity
	for (auto& ball : balls)
	{
		ball.mBallPos.x += ball.mBallVel.x * deltaTime;
		ball.mBallPos.y += ball.mBallVel.y * deltaTime;
	}

	ColidBoll(true);
	ColidBoll(false);
}

/// <summary>
/// 1Pのバーを動かす
/// </summary>
/// <param name="delta">
/// 1フレームの時間変化
/// </param>
void Game::UpdateMBar(const float& delta)
{
	// Update paddle position based on direction
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * delta;
		// Make sure paddle doesn't move off screen!
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}
}

/// <summary>
/// 2Pのバーを動かす
/// </summary>
/// <param name="delta">
/// 1フレームの時間変化
/// </param>
void Game::UpdateEBar(const float& delta)
{
	// Update paddle position based on direction
	if (ePaddleDir != 0)
	{
		ePaddlePos.y += ePaddleDir * 300.0f * delta;
		// Make sure paddle doesn't move off screen!
		if (ePaddlePos.y < (paddleH / 2.0f + thickness))
		{
			ePaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (ePaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			ePaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}
}

/// <summary>
/// バーとボールの衝突処理
/// </summary>
/// <param name="flag">
/// trueなら1Pのバーについて，falseなら2Pのバーについて衝突処理を行う
/// </param>
void Game::ColidBoll(const bool flag)
{
	for (auto& ball : balls)
	{
		// Bounce if needed
		// Did we intersect with the paddle?
		float diff = flag ? (mPaddlePos.y - ball.mBallPos.y) : (ePaddlePos.y - ball.mBallPos.y);
		// Take absolute value of difference
		diff = (diff > 0.0f) ? diff : -diff;
		if ((
			// Our y-difference is small enough
			diff <= paddleH / 2.0f &&
			// We are in the correct x-position
			ball.mBallPos.x <= 25.0f && ball.mBallPos.x >= 20.0f &&
			// The ball is moving to the left
			ball.mBallVel.x < 0.0f) ||
			(
				// Our y-difference is small enough
				diff <= paddleH / 2.0f &&
				// We are in the correct x-position
				ball.mBallPos.x >= 1024.0f - 25.0f && ball.mBallPos.x <= 1024.0f - 20.0f &&
				// The ball is moving to the left
				ball.mBallVel.x > 0.0f
				))
		{
			ball.mBallVel.x *= -1.0f;
		}
		// Did the ball go off the screen? (if so, end game)
		else if (ball.mBallPos.x <= 0.0f || ball.mBallPos.x >= 1024.0f)
		{
			mIsRunning = false;
		}

		// Did the ball collide with the top wall?
		if (ball.mBallPos.y <= thickness && ball.mBallVel.y < 0.0f)
		{
			ball.mBallVel.y *= -1;
		}
		// Did the ball collide with the bottom wall?
		else if (ball.mBallPos.y >= (768 - thickness) &&
			ball.mBallVel.y > 0.0f)
		{
			ball.mBallVel.y *= -1;
		}
	}
}

void Game::GenerateOutput()
{
	// Set draw color to blue
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G
		255,	// B
		255		// A
	);

	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw paddle
	SDL_Rect paddleM{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddleM);
	SDL_Rect paddleE{
		static_cast<int>(ePaddlePos.x),
		static_cast<int>(ePaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddleE);

	// Draw ball
	for (auto& ball : balls)
	{
		SDL_Rect ballObj{
			static_cast<int>(ball.mBallPos.x - thickness / 2),
			static_cast<int>(ball.mBallPos.y - thickness / 2),
			thickness,
			thickness
		};
		SDL_RenderFillRect(mRenderer, &ballObj);
	}

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}