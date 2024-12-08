#pragma once
#include <functional>
class OnClickListener {
public:
	OnClickListener(std::function<void()> lambda) {
		this->onClickCallback = lambda;
	}
	void invoke() {
		onClickCallback();
	};
private:
	std::function<void()> onClickCallback;
};