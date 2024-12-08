#pragma once
#include "BaseView.h"
#include "Color.h"
#include "ICheckBox.hpp"
const class CheckBoxView : public BaseView,public ICheckBox {
private:
	Color borderColor{ COLORS::PRIMARY };
	Color activeBorderColor{ COLORS::SECONDARY_PRIMARY };
	Color checkedColor{COLORS::PRIMARY};
	Color uncheckedColor{COLORS::SECONDARY_PRIMARY};
	Color textColor{ COLORS::ON_SURFACE };
	Color activeTextColor{ COLORS::ON_PRIMARY };
	Vector2 textSize{ 0,0 };
	uintptr_t checkboxSize{ 20u };
	std::function<void(bool)> mCheckboxStateListener;
	const char* label = nullptr;
	const uintptr_t checkboxPaddingEnd = 8u;
	Vector2 textPosition{ 0,0 };
public:
	CheckBoxView(const char* debugId,const char* label,	uintptr_t checkBoxSize) : BaseView(debugId,ViewSizeSpec::WRAP_CONTENT, ViewSizeSpec::WRAP_CONTENT), ICheckBox([this](bool isChecked) {
		if (mCheckboxStateListener != nullptr) {
			mCheckboxStateListener(isChecked);
		}
	}){
		this->checkboxSize = checkBoxSize;
		this->label = label;
	};

	void setColors(const Color& _checked, const Color& _unchecked) {
		checkedColor = _checked;
		uncheckedColor = _unchecked;
	}
	void onCheckboxStateChanged(const std::function<void(bool)>& lambda) {
		this->mCheckboxStateListener = lambda;
	}

protected:
	virtual bool onMouseEvent(const MouseEvent& mouseEvent)override;
	virtual void draw(IRender* renderer) override;
	virtual void onAttachedToWindow(Window*) override;
	virtual void onMeasure() override;
	virtual void measure(uintptr_t availW, uintptr_t availH) override;
	virtual void onLayout() override;

private:
};