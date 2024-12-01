#pragma once
#include "Vector3D.hpp"
#include "Renderable.h"
#include "assert.h"
#include <random>
#include <Windows.h>
class UniverseCmd;
#define MAX_ORIGIN_X 50.0F
class DefaultBody : public IRenderable{
private:
	Vector3D mOrigin{};
	Vector3D mV{};//скорость по осям
	Vector3D mA{};//ускорение по осям
	double mass{ 0.0 };//kg
	UniverseCmd* mCmdPtr{ nullptr };//const
public:
	DefaultBody(double objMass, UniverseCmd* cmdPtr) {
		assert(objMass >= 0.0 && cmdPtr != nullptr && "invalid object mass");
		mCmdPtr = cmdPtr;
	
		mOrigin = {
			//[-0.5,0.5](-50,50)
			(rand() % 100) - MAX_ORIGIN_X,
			(rand() % 100) - MAX_ORIGIN_X,
			(rand() % 100) - MAX_ORIGIN_X,
		};
		mV = {
			//[-0.5,0.5](-5,5)
		(rand() % 10) - 5.0F,
		(rand() % 10) - 5.0F,
		(rand() % 10) - 5.0F,
		};
		this->mass = objMass;
	};
	DefaultBody(double objMass,const Vector3D& origin, const Vector3D& speed, UniverseCmd* cmdPtr) {
		assert(objMass >= 0.0 && cmdPtr != nullptr && "invalid object mass");
		mCmdPtr = cmdPtr;
		mOrigin = origin;
		mV = speed;
		this->mass = objMass;
	};
	DefaultBody(const DefaultBody& mCopyObj) {
		this->mOrigin = mCopyObj.mOrigin;
		this->mV = mCopyObj.mV;
		this->mA = mCopyObj.mA;
		this->mass = mCopyObj.mass;
		this->mCmdPtr = mCopyObj.mCmdPtr;
	}
	void update(float elapsedTimeFromPrevUpdate);
	virtual void draw(IRender* renderer) override;
private:
};