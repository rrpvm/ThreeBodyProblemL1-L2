#pragma once
#include "IRender.h"
#include "DefaultBody.hpp"
#include "SunBody.hpp"
#define EARTH_MASS_LESS 332946
#define EARTH_ID -4
class EarthBody  :public DefaultBody {
public:
	EarthBody(UniverseCmd* cmdPtr, SunBody* sun, const Vector3D& mOrigin);
	virtual void draw(IRender* renderer) override;
};