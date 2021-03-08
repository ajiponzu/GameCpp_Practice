// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	// Lower update order to update first
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;
	
	float GetAngularSpeed() const { return mAngularSpeed; }
	Vector2 GetForcePerFrame() const { return mForcePerFrame; }
	Vector2 GetSumOfForce() const { return mSumOfForce; }
	float GetMass() const { return mMass; }
	Vector2 GetVelocity() const { return mVelocity; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForcePerFrame(Vector2 forcePerFrame) { mForcePerFrame = forcePerFrame; }
	void SetSumOfForce(Vector2 sumOfForce) { mSumOfForce = sumOfForce; }
	void SetMass(float mass) { mMass = mass; }
	void SetVelocity(Vector2 velocity) { mVelocity = velocity; }

	void AddForce();
	void AddForce(class Vector2& force);
private:
	// Controls rotation (radians/second)
	float mAngularSpeed;
	// Controls forward movement (units/second)
	//float mForwardSpeed;

	Vector2 mSumOfForce{};
	float mMass;
	Vector2 mVelocity{};

	Vector2 mForcePerFrame{};
};
