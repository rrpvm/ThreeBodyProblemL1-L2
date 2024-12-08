#pragma once
#include "LinearLayout.hpp"
class ViewPager :public LinearLayout {
private:
	ParentView* mCurrentFragment = nullptr;
	int selectViewIndex = -1;
public:
	ViewPager(const char* debugId,
		ViewSizeSpec _widthSize,
		ViewSizeSpec _heightSize
	) : LinearLayout(debugId, LinearLayoutOrientation::HORIZONTAL, _widthSize, _heightSize) {

	};
	void showViewIndex(int index);
protected:
	virtual void dispatchMouseEvent(const MouseEvent& mouseEvent) override;
	virtual void onMeasure() override;
	virtual void onLayout() override;
private:
};