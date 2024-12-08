#pragma once
#include "BaseView.h"
#include "OnClickListener.hpp"

class SelectableButton : public BaseView {
private:
	const char* buttonText;
	Color defaultColor{ Color(255,99,99,99) };
	Color hoveredColor{ Color(255,55,55,55) };
	Color selectedColor{ Color(255,77,77,77) };
	uintptr_t borderThickness{ 2u };
	Vector2 textPositionOffset{ 0,0 };
	Vector2 buttonPadding{ 32,16 };
	bool isHovered{ false };
	bool isSelected{ false };
	OnClickListener* mListener = nullptr;
public:
	SelectableButton(const char* debugId,
		const char* buttonText,
		uintptr_t borderThickness,
		const Color& borderColor,
		const Color& borderHoverColor,
		const Color& selectedColor,
		uintptr_t _width,
		uintptr_t _height) : BaseView(debugId, _width, _height) {
		this->buttonText = buttonText;
		this->defaultColor = borderColor;
		this->hoveredColor = borderHoverColor;
		this->selectedColor = selectedColor;
	};
	SelectableButton(const char* debugId,
		const char* buttonText,
		uintptr_t borderThickness,
		const Color& borderColor,
		const Color& borderHoverColor,
		const Color& selectedColor,
		ViewSizeSpec widthSpec,
		uintptr_t _height) : BaseView(debugId, widthSpec, _height) {
		this->buttonText = buttonText;
		this->defaultColor = borderColor;
		this->hoveredColor = borderHoverColor;
		this->selectedColor = selectedColor;
	};
	SelectableButton(const char* debugId,
		const char* buttonText,
		uintptr_t borderThickness,
		const Color& borderColor,
		const Color& borderHoverColor,
		const Color& selectedColor,
		ViewSizeSpec widthSpec,
		ViewSizeSpec _height) : BaseView(debugId, widthSpec, _height) {
		this->buttonText = buttonText;
		this->defaultColor = borderColor;
		this->hoveredColor = borderHoverColor;
		this->selectedColor = selectedColor;
	};
	void setSelected(bool isSelected) {
		this->isSelected = isSelected;
	}
	void setOnClickListener(OnClickListener* clickListener) {
		this->mListener = clickListener;
	}
protected:
	virtual bool onMouseEvent(const MouseEvent& mouseEvent)override;
	virtual void draw(IRender* renderer) override;
	virtual void onAttachedToWindow(Window*) override;
	virtual void onMeasure() override;
	virtual void measure(uintptr_t availW, uintptr_t availH) override;
	virtual void onLayout() override;
};