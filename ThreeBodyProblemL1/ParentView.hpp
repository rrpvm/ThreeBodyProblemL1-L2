#pragma once
#include "BaseView.h"
#include <vector>
class ParentView : public BaseView{
protected:
	std::vector<BaseView*> mViews = std::vector<BaseView*>(32);
public:
	ParentView(ViewSizeSpec _widthSize, ViewSizeSpec _heightSize)  : BaseView(_widthSize, _heightSize){}
	ParentView(uintptr_t width, uintptr_t height) : BaseView(width,height){}
	ParentView(ViewSizeSpec _widthSize, uintptr_t height) :BaseView(_widthSize, height) {};
	ParentView(uintptr_t width, ViewSizeSpec _heightSpec) :BaseView(widthSize, _heightSpec) {};

	~ParentView() {

	}
private:

};