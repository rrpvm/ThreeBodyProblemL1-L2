#pragma once
#include "Vector3D.hpp"
#include "Renderable.h"
#include "assert.h"
#include <random>
#include <Windows.h>
class UniverseCmd;
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
			(float)(rand() % 640),
			(float)(rand() % 640),
			(float)(rand() % 640)
		};
		mV = {
			(float)(rand() % 10),
			(float)(rand() % 10),
			(float)(rand() % 10)
		};
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