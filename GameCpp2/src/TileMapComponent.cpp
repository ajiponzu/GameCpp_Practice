#include "TileMapComponent.h"
#include "Actor.h"

TileMapComponent::TileMapComponent(Actor* owner, const int& tileSize, const float& scrollSpeed, const int& drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mTileSize(tileSize)
	, mScrollSpeed(scrollSpeed)
	, mScrollOffset(.0f)
	, mScreenSizeX(0)
	, mScreenSizeY(0)
{
}

void TileMapComponent::Update(float deltaTime)
{
	if (mOwner->GetState() == Actor::State::EMoving)
	{
		mScrollOffset += mScrollSpeed * deltaTime;
	}
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		int displayX = 0, offset = static_cast<int>(mScrollOffset);
		const int& tileNumX = mTexWidth / mTileSize;

		SDL_Rect srcR{}, destR{};
		srcR.w = srcR.h = destR.w = destR.h = mTileSize;

		for (const auto& mapData : mMapDataList)
		{
			displayX = 0;
			for (const auto & tileIdx : mapData)
			{
				srcR.x = ((displayX % mTileSize) * mTileSize + offset) % mScreenSizeX;
				srcR.y = (displayX / mTileSize) * mTileSize;

				destR.x = (tileIdx % tileNumX) * mTileSize;
				destR.y = (tileIdx / tileNumX) * mTileSize;

				SDL_RenderCopyEx(renderer,
					mTexture,
					&destR,
					&srcR,
					-Math::ToDegrees(mOwner->GetRotation()),
					nullptr,
					SDL_FLIP_NONE);
				displayX++;
			}
		}
	}
}

//Åuhttps://qiita.com/shirosuke_93/items/d5d068bb15c8e8817c34Åv
void TileMapComponent::LoadCsvMapData(const std::string& fileName)
{
	int lineNum = 0, lineLen = 0;
	std::ifstream ifs(fileName);
	std::string lineBuf, buf;

	mMapDataList.emplace_back();
	auto& tail = mMapDataList.back();
	while (getline(ifs, lineBuf))
	{
		lineNum++;
		lineLen = 0;
		std::istringstream istream(lineBuf);
		while (getline(istream, buf, ','))
		{
			tail.emplace_back(stoi(buf));
			lineLen++;
		}
	}
	mScreenSizeX = mTileSize * lineLen;
	mScreenSizeY = mTileSize * lineNum;
}