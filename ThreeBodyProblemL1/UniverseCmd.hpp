#pragma once
#include <vector>
#include <deque>
#include <unordered_map>
#include "DefaultBody.hpp"
#include <optional>
#include <mutex>
#include <iostream>
#define START_HISTORY_CAPACITY 131072 //2^17
struct UniverseCmd
{
private:
	std::optional<std::vector<DefaultBody*>> lastFullCalculation = std::nullopt;//full object
	std::unordered_map<int, Vector3D>*/*map[body_position,position]*/ cmdHistory = nullptr;
	int currentCapacity = START_HISTORY_CAPACITY;
	std::mutex lock;
public:
	std::optional<std::vector<DefaultBody>> lastLogicInstance = std::nullopt;//object-slice, for update logic
	const double deltaTime = 0.1;// action-interval s
	const double uGravity;//university gravity cosnt
	int currentTick{ 0 };
	int lastTick{ 0 };
	UniverseCmd(double dT, double uG) : deltaTime(dT), uGravity(uG) {
		lastFullCalculation = std::nullopt;
		cmdHistory = new std::unordered_map<int, Vector3D>[START_HISTORY_CAPACITY] {std::unordered_map<int,Vector3D>()};
	}
	~UniverseCmd() {
		delete[] cmdHistory;
	}
public:
	void update(int tick, std::vector<DefaultBody*>& bodyList) {
		if (lastTick > tick)return;
		std::vector<DefaultBody*>copy = std::vector<DefaultBody*>();
		std::vector<DefaultBody>copySlice = std::vector<DefaultBody>();
		std::unordered_map<int,Vector3D>historyItem = std::unordered_map<int, Vector3D>();

		if (lastLogicInstance.has_value()) {
			lastLogicInstance.value().clear();//clear data
		}
		for (const DefaultBody* body : bodyList) {
			copy.push_back(new DefaultBody(body));
			copySlice.push_back(*body);
			historyItem.insert({ body->getId(), body->getOrigin() });
		}
		if (lastFullCalculation.has_value()) {
			for (DefaultBody* copiedBodyPrev : lastFullCalculation.value()) {
				delete copiedBodyPrev;
			}
		}
		lastFullCalculation = copy;
		lastLogicInstance = copySlice;
		lock.lock();
		cmdHistory[tick % START_HISTORY_CAPACITY] = historyItem;
		lock.unlock();
		lastTick = tick;
	};
	std::vector<Vector3D> getAllPrevTicksPosition(int bodyId) {
		std::vector<Vector3D> vectorResult = std::vector<Vector3D>();
		vectorResult.reserve(lastTick);
		lock.lock();
		for (int i = 0; i < lastTick; i++) {
			auto result = cmdHistory[i].find(bodyId);
			if (result == cmdHistory[i].end())continue;
			vectorResult.emplace_back(result->second);
		}
		lock.unlock();
		return vectorResult;
	}
	std::vector<Vector3D> getLastNPrevTicksPosition(int bodyId, int ticksToTake) {
		std::vector<Vector3D> vectorResult = std::vector<Vector3D>();
		vectorResult.reserve(min(ticksToTake,lastTick));
		lock.lock();
		for (int i = max(lastTick-ticksToTake,0); i < max(lastTick, ticksToTake); i++) {
			auto result = cmdHistory[i].find(bodyId);
			if (result == cmdHistory[i].end())continue;
			vectorResult.emplace_back(result->second);
		}
		lock.unlock();
		return vectorResult;
	}
	std::optional<std::vector<DefaultBody*>> getPrevDataTick() {
		return lastFullCalculation;
	}
};