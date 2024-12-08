#pragma once
#include "BaseView.h"

class SpacerView : public BaseView {
public:
	SpacerView(const char* debugId, uintptr_t _width, uintptr_t _height) : BaseView(debugId, _width, _height) {};
	SpacerView(const char* debugId, ViewSizeSpec widthSpec, uintptr_t _height) : BaseView(debugId, widthSpec, _height) {};
	virtual void draw(IRender* renderer) override;
	virtual void onAttachedToWindow(Window*) override;
	virtual void onMeasure() override;
	virtual void onLayout() override;
	virtual void measure(uintptr_t availW, uintptr_t availH)override;
};