#include "Human.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Human::Human(Game* game)
	:Actor(game)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this, 100, 2.0f, false);
	std::unordered_map<State, std::vector<SDL_Texture*>> anims;
	anims[State::EActive] = {
		game->GetTexture("Assets/Character01.png"),
	};
	anims[State::EMoving] = {
		game->GetTexture("Assets/Character02.png"),
		game->GetTexture("Assets/Character03.png"),
		game->GetTexture("Assets/Character04.png"),
		game->GetTexture("Assets/Character05.png"),
		game->GetTexture("Assets/Character06.png"),
	};
	anims[State::EJumping] = {
		game->GetTexture("Assets/Character07.png"),
		game->GetTexture("Assets/Character08.png"),
		game->GetTexture("Assets/Character09.png"),
		game->GetTexture("Assets/Character10.png"),
		game->GetTexture("Assets/Character11.png"),
		game->GetTexture("Assets/Character12.png"),
		game->GetTexture("Assets/Character13.png"),
		game->GetTexture("Assets/Character14.png"),
		game->GetTexture("Assets/Character15.png"),
	};
	anims[State::EAtacking] = {
		game->GetTexture("Assets/Character16.png"),
		game->GetTexture("Assets/Character17.png"),
		game->GetTexture("Assets/Character18.png"),
	};
	asc->SetAnimTextures(anims);
}

void Human::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;

	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 1000.0f)
	{
		pos.x = 1000.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}
	SetPosition(pos);
}

void Human::ProcessKeyboard(const uint8_t* state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;

	SetState(State::EActive);
	// right/left
	if (state[SDL_SCANCODE_RIGHT])
	{
		SetState(State::EMoving);
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_LEFT])
	{
		SetState(State::EMoving);
		mRightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_DOWN])
	{
		SetState(State::EJumping);
		mDownSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_UP])
	{
		SetState(State::EJumping);
		mDownSpeed -= 300.0f;
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		SetState(State::EAtacking);
	}
}