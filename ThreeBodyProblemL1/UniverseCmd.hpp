#pragma once
#include <vector>
#include "DefaultBody.hpp"
#include <optional>
#include <mutex>
#include <iostream>
struct UniverseCmd
{
private:
	std::optional<std::vector<DefaultBody*>> lastFullCalculation = std::nullopt;//full object
	
public:
	std::optional<std::vector<DefaultBody>> lastLogicInstance = std::nullopt;//object-slice
	const double deltaTime = 0.1;// action-interval s
	const double uGravity;//university gravity cosnt
	int currentTick{ 0 };
	int lastTick{ 0 };
	UniverseCmd(double dT, double uG) : deltaTime(dT), uGravity(uG) {
		lastFullCalculation = std::nullopt;
	}
public:
	void update(int tick, std::vector<DefaultBody*>& bodyList) {
		if (lastTick > tick)return;
		std::vector<DefaultBody*>copy = std::vector<DefaultBody*>();
		std::vector<DefaultBody>copySlice = std::vector<DefaultBody>();
		if (lastLogicInstance.has_value()) {
			lastLogicInstance.value().clear();//clear data
		}
		for (const DefaultBody* body : bodyList) {
			copy.push_back(new DefaultBody(body));
			copySlice.push_back(*body);
		}
		if (lastFullCalculation.has_value()) {
			for (DefaultBody* copiedBodyPrev : lastFullCalculation.value()) {
				delete copiedBodyPrev;
			}
		}
		lastFullCalculation = copy;
		lastLogicInstance = copySlice;
	};
	std::optional<std::vector<DefaultBody*>> getPrevDataTick() {
		return lastFullCalculation;
	}
};