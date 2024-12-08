#pragma once
#include "BaseView.h"
#include "Color.h"
#include "ICheckBox.hpp"
const class CheckBoxView : public BaseView,public ICheckBox {
private:
	Color borderColor{ COLORS::PRIMARY };
	Color checkedColor{COLORS::PRIMARY};
	Color uncheckedColor{COLORS::SECONDARY_PRIMARY};
public:
	CheckBoxView(const char* debugId,	uintptr_t _width, uintptr_t _height) : BaseView(debugId,_width, _height), ICheckBox([](bool isChecked) {

	}){};

	void setColors(const Color& _checked, const Color& _unchecked) {
		checkedColor = _checked;
		uncheckedColor = _unchecked;
	}
protected:
	virtual void draw(IRender* renderer) override;
	virtual void onAttachedToWindow(Window*) override;
	virtual void onMeasure() override;
	virtual void measure(uintptr_t availW, uintptr_t availH) override;
	virtual void onLayout() override;

private:
};