// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

using Actor = class Actor;

class Component
{
public:
	// Constructor
	// (the lower the update order, the earlier the component updates)
	Component(Actor* owner, int updateOrder = 100);
	// Destructor
	virtual ~Component();
	// Update this component by delta time
	virtual void Update(float deltaTime);

	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// Owning actor
	Actor* mOwner;
	// Update order of component
	int mUpdateOrder;
};
