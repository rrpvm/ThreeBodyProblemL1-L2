#pragma once
#include "IRender.h"
#include "DefaultBody.hpp"
#include <iostream>
#include <format>
#define SUN_MASS 1337448
#define SUN_ID -1
class SunBody : public DefaultBody {
public:
	SunBody( const Vector3D& origin, const Vector3D& speed, UniverseCmd* cmdPtr) :DefaultBody(SUN_ID, SUN_MASS, origin, speed, cmdPtr) {
		std::cout << "Sun inited, mass :" << this->mass << std::format("origin: x,y,z {} {} {} \t", origin.x, origin.y, origin.z) << std::endl;
	}
	SunBody(const SunBody& mCopyObj) : DefaultBody(mCopyObj){}
	void draw(IRender* renderer) override;
};