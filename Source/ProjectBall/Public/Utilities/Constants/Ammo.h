// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

namespace Constants::Ammo
{
	// TODO spl: this might need refactor, since maybe we won't want an arrow to travel at the same speed as a bullet
	namespace PMC
	{
		constexpr float INITIAL_SPEED = 5000.f;
		constexpr float MAX_SPEED = 10000.f;
		constexpr float PROJECTILE_GRAVITY_SCALE = 0.f;
		constexpr float MAXIMUM_DISTANCE_TRAVEL = 3000.f;
	}
}