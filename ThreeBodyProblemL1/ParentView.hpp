#pragma once
#include "BaseView.h"
#include <vector>
class ParentView : public BaseView{
protected:
	std::vector<BaseView*> mViews = std::vector<BaseView*>();
public:
	ParentView(const char* debugId,	ViewSizeSpec _widthSize, ViewSizeSpec _heightSize)  : BaseView(debugId,	_widthSize, _heightSize){}
	ParentView(const char* debugId, uintptr_t width, uintptr_t height) : BaseView(debugId, width,height){}
	ParentView(const char* debugId, ViewSizeSpec _widthSize, uintptr_t height) :BaseView(debugId, _widthSize, height) {};
	ParentView(const char* debugId, uintptr_t width, ViewSizeSpec _heightSpec) :BaseView(debugId, widthSize, _heightSpec) {};

	~ParentView() {

	}
	virtual void addView(BaseView* mView) = 0;
	virtual void onGlobalOffsetChanged(const Vector2& globalOffsetChanged) {
		this->mGlobalOffset = globalOffsetChanged;
		for (auto view : mViews) {
			view->onGlobalOffsetChanged(globalOffsetChanged);
		}
	}
	virtual bool onInterceptMouseEvent(const MouseEvent& mouseEvent) { return false; };//перехват из dispatchMouseEvent  -> если мы хотим остановить проброску ивентов ниже (false)-> спускаемся дальше
private:

};