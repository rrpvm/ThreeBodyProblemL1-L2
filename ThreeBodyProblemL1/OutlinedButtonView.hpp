#pragma once
#include "Color.h"
#include "BaseView.h"
class OutlinedButtonView : public BaseView {
private:
	const char* buttonText;
	Color borderColor{BLACK};
	Color borderHoverColor{WHITE};
	uintptr_t borderThickness{ 1u };
	Vector2 textPositionOffset{ 0,0 };
	Vector2 buttonPadding{ 32,16 };
	bool isHovered{ false };
public:
	OutlinedButtonView(const char* debugId, 
		const char* buttonText,
		uintptr_t borderThickness,
		const Color& borderColor,
		const Color& borderHoverColor,
		uintptr_t _width,
		uintptr_t _height) : BaseView(debugId, _width, _height) {
		this->buttonText = buttonText;
		this->borderColor = borderColor;
		this->borderHoverColor = borderHoverColor;
	};
	OutlinedButtonView(const char* debugId,
		const char* buttonText,
		uintptr_t borderThickness,
		const Color& borderColor,
		const Color& borderHoverColor,
		ViewSizeSpec widthSpec, 
		uintptr_t _height) : BaseView(debugId, widthSpec, _height) {
		this->buttonText = buttonText;
		this->borderColor = borderColor;
		this->borderHoverColor = borderHoverColor;
	};
	OutlinedButtonView(const char* debugId,
		const char* buttonText,
		uintptr_t borderThickness,
		const Color& borderColor,
		const Color& borderHoverColor, 
		ViewSizeSpec widthSpec,
		ViewSizeSpec _height) : BaseView(debugId, widthSpec, _height) {
		this->buttonText = buttonText;
		this->borderColor = borderColor;
		this->borderHoverColor = borderHoverColor;
	};
protected:
	virtual bool onMouseEvent(const MouseEvent& mouseEvent)override;
	virtual void draw(IRender* renderer) override;
	virtual void onAttachedToWindow(Window*) override;
	virtual void onMeasure() override;
	virtual void measure(uintptr_t availW, uintptr_t availH) override;
	virtual void onLayout() override;
private:
};