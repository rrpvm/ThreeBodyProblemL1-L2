#pragma once
#include "ParentView.hpp"
#include "Color.h"
enum LinearLayoutOrientation {
	VERTICAL,
	HORIZONTAL
};
class LinearLayout : public ParentView {
private:
	LinearLayoutOrientation mOrientation{ VERTICAL };
public:
	LinearLayout(
		const char* debugId,
		LinearLayoutOrientation orientation,
		ViewSizeSpec _widthSize, ViewSizeSpec _heightSize
	) : ParentView(debugId, _widthSize, _heightSize) {
		mOrientation = orientation;
	}
	LinearLayout(
		const char* debugId,
		LinearLayoutOrientation orientation,
		uintptr_t width, uintptr_t height
	) : ParentView(debugId, width, height) {
		mOrientation = orientation;
	}
	LinearLayout(const char* debugId, LinearLayoutOrientation orientation, ViewSizeSpec _widthSize, uintptr_t height) :ParentView(debugId, _widthSize, height) {
		mOrientation = orientation;
	};
	LinearLayout(const char* debugId, LinearLayoutOrientation orientation, uintptr_t width, ViewSizeSpec _heightSpec) :ParentView(debugId, widthSize, _heightSpec) {
		mOrientation = orientation;
	};
	~LinearLayout() {

	}
	virtual void addView(BaseView* mView) override;
protected:
	virtual void dispatchMouseEvent(const MouseEvent& mouseEvent) override;
	virtual bool onMouseEvent(const MouseEvent& mouseEvent) override;
	virtual void draw(IRender* renderer) override;
	virtual void onAttachedToWindow(Window*) override;
	virtual void onMeasure() override;
	virtual void measure(uintptr_t availW, uintptr_t availH) override;
	virtual void onLayout() override;
private:

};