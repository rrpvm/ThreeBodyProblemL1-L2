#pragma once
#include "Vector3D.hpp"
#include "Renderable.h"
#include "assert.h"
#include <random>
#include <Windows.h>
#define MAX_ORIGIN_X 50.0F

class UniverseCmd;
class DefaultBody : public IRenderable {
protected:
	int id;
	double mass{ 0.0 };//kg
	Vector3D mOrigin{};
	Vector3D mV{};//скорость по осям
	Vector3D mA{};//ускорение по осям
	UniverseCmd* mCmdPtr{ nullptr };//const
public:
	virtual ~DefaultBody(){

	}
	DefaultBody(size_t id, UniverseCmd* cmdPtr) :id(id) {
		mCmdPtr = cmdPtr;
		mOrigin = {
			//[-0.5,0.5](-50,50)
			(rand() % 100) - MAX_ORIGIN_X,
			(rand() % 100) - MAX_ORIGIN_X,
			0,
		};
		mV = {
			//-50,50 
		((rand() % 200) - 100.0F) / 2.0F,
		((rand() % 200) - 100.0F) / 2.0F,
		0,
		};
		this->mass = rand() % 10000;
	};
	DefaultBody(const DefaultBody& mCopyObj) :id(mCopyObj.id) {
		this->mOrigin = mCopyObj.mOrigin;
		this->mV = mCopyObj.mV;
		this->mA = mCopyObj.mA;
		this->mass = mCopyObj.mass;
		this->mCmdPtr = mCopyObj.mCmdPtr;
	}
	DefaultBody(const DefaultBody* mCopyObj) : DefaultBody(*mCopyObj) {};
	void update(float elapsedTimeFromPrevUpdate);
	const Vector3D& getOrigin() {
		return this->mOrigin;
	}
	const double getMass() {
		return this->mass;
	}
	bool operator==(DefaultBody* other) {
		return this->id == other->id;
	}
	virtual void draw(IRender* renderer) override;
protected:
	DefaultBody(size_t id, double objMass, const Vector3D& origin, const Vector3D& speed, UniverseCmd* cmdPtr) :id(id) {
		assert(objMass >= 0.0 && cmdPtr != nullptr && "invalid object mass");
		mCmdPtr = cmdPtr;
		mOrigin = origin;
		mV = speed;
		this->mass = objMass;
	};
};