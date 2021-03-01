#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using MapData = std::vector<int>;
using MapDataList = std::vector<MapData>;

class TileMapComponent :
	public SpriteComponent
{
public:
	TileMapComponent(Actor* owner, const int& tileSize = 32, const float& scrollSpeed = .0f, const int& drawOrder = 10);
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void LoadCsvMapData(const std::string& fileName);
	void SetScrollSpeed(const float& speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	MapDataList mMapDataList;
	int mTileSize;
	float mScrollSpeed;
	float mScrollOffset;
	int mScreenSizeX;
	int mScreenSizeY;
};
