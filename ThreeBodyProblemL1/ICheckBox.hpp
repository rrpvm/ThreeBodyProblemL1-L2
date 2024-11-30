#pragma once
#include <functional>
class ICheckBox {
protected:
	bool checked{ false };
	std::function<void(bool)> function;
	void onClicked() {
		checked = !checked;
		function(checked);
	}
public:
	ICheckBox(std::function<void(bool)>onClickListener) {
		this->function = onClickListener;
	}
private:

};