#pragma once
class IRender;
class IRenderable {
public:
	IRenderable() {

	}
	~IRenderable() {

	}
	virtual void draw(IRender* renderer) = 0;
};