#pragma once
#include "ParentView.hpp"
#include "Color.h"
enum LinearLayoutOrientation {
	VERTICAL,
	HORIZONTAL
};
class LinearLayout : public ParentView {
private:
	LinearLayoutOrientation mOrientation{VERTICAL};
	
public:
	LinearLayout(
		LinearLayoutOrientation orientation,
		ViewSizeSpec _widthSize, ViewSizeSpec _heightSize
	): ParentView(_widthSize, _heightSize) {
		mOrientation = orientation;
	}
	LinearLayout(
		LinearLayoutOrientation orientation,
		uintptr_t width, uintptr_t height
	) : ParentView(width, height) {
		mOrientation = orientation;
	}
	LinearLayout(LinearLayoutOrientation orientation,ViewSizeSpec _widthSize, uintptr_t height) :ParentView(_widthSize, height) {
		mOrientation = orientation;
	};
	LinearLayout(LinearLayoutOrientation orientation, uintptr_t width, ViewSizeSpec _heightSpec) :ParentView(widthSize, _heightSpec) {
		mOrientation = orientation;
	};
	virtual void draw(IRender* renderer) override;
	virtual void onAttachedToWindow(Window*) override;
	virtual void onMeasure() override;
	virtual void onLayout() override;
	~LinearLayout() {

	}
private:

};