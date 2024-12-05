#pragma once
#include <vector>
#include <deque>
#include <unordered_map>
#include "DefaultBody.hpp"
#include <optional>
#include <mutex>
#include <iostream>
#define SEGMENT_HISTORY_CAPACITY 2048 //2^11
struct UniverseCmd
{
private:
	std::optional<std::vector<DefaultBody*>> lastFullCalculation = std::nullopt;//full object
	std::unordered_map<int, Vector3D>*/*map[body_position,position]*/ cmdHistory = nullptr;
	int currentCapacity = SEGMENT_HISTORY_CAPACITY;
	std::mutex lock;
public:
	std::vector<DefaultBody*> mBodies = std::vector<DefaultBody*>();
	const double deltaTime = 0.1;// action-interval s
	const double uGravity;//university gravity cosnt
	int currentTick{ 0 };
	int lastTick{ 0 };
	UniverseCmd(double dT, double uG) : deltaTime(dT), uGravity(uG) {
		lastFullCalculation = std::nullopt;
		cmdHistory = new std::unordered_map<int, Vector3D>[SEGMENT_HISTORY_CAPACITY] {std::unordered_map<int,Vector3D>()};
	}
	~UniverseCmd() {
		delete[] cmdHistory;
	}
public:
	void setBodies(const std::vector<DefaultBody*>& vector) {
		this->mBodies = vector;
	}
	void update(int tick) {
		if (lastTick > tick)return;
		std::vector<DefaultBody*>copy = std::vector<DefaultBody*>();
		std::unordered_map<int,Vector3D>historyItem = std::unordered_map<int, Vector3D>();
		for (const DefaultBody* body : mBodies) {
			copy.push_back(new DefaultBody(body));
			historyItem.insert({ body->getId(), body->getOrigin() });
		}
		if (lastFullCalculation.has_value()) {
			for (DefaultBody* copiedBodyPrev : lastFullCalculation.value()) {
				delete copiedBodyPrev;
			}
		}
		lastFullCalculation = copy;
		lock.lock();
		cmdHistory[tick % SEGMENT_HISTORY_CAPACITY] = historyItem;
		lock.unlock();
		lastTick = tick;
	};
	std::vector<Vector3D> getAllPrevTicksPosition(int bodyId) {
		std::vector<Vector3D> vectorResult = std::vector<Vector3D>();
		uintptr_t size = min(SEGMENT_HISTORY_CAPACITY, lastTick);
		uintptr_t startFrom = lastTick % SEGMENT_HISTORY_CAPACITY;
		vectorResult.reserve(size);
		lock.lock();
		//oldest
		for (uintptr_t i = startFrom + 1; i < size; i++) {
			auto result = cmdHistory[i].find(bodyId);
			if (result == cmdHistory[i].end())continue;
			vectorResult.emplace_back(result->second);
		}
		//new
		for (uintptr_t i = 0u; i < startFrom; ++i) {
			auto result = cmdHistory[i].find(bodyId);
			if (result == cmdHistory[i].end())continue;
			vectorResult.emplace_back(result->second);
		}
		lock.unlock();
		return vectorResult;
	}
	std::vector<Vector3D> getLastNPrevTicksPosition(int bodyId, int ticksToTake) {
		std::vector<Vector3D> vectorResult = std::vector<Vector3D>();
		uintptr_t balancePointer = lastTick % SEGMENT_HISTORY_CAPACITY;
		uintptr_t arrBoundRight = min(lastTick, SEGMENT_HISTORY_CAPACITY);
		int takesFromLeft = min(balancePointer, ticksToTake);//more new
		int startOldestData = arrBoundRight - takesFromLeft;
		int takesFromRight = ticksToTake - takesFromLeft;//more old
		vectorResult.reserve(min(ticksToTake,SEGMENT_HISTORY_CAPACITY));
		lock.lock();
		//oldest
		for (int i = startOldestData + 1; i < startOldestData + takesFromRight && i < arrBoundRight; i++) {
			auto result = cmdHistory[i].find(bodyId);
			if (result == cmdHistory[i].end())continue;
			vectorResult.emplace_back(result->second);
		}
		//newest
		for (int i = balancePointer; i > balancePointer - takesFromLeft; --i) {
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