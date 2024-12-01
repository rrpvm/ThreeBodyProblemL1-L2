#pragma once
#include <vector>
#include "DefaultBody.hpp"
#include <optional>
#include <mutex>
#include <iostream>
struct UniverseCmd
{
private:
	std::mutex lock;
	std::vector<DefaultBody>* cachedCalculations;
	int cachedCapacity;
	UniverseCmd() :UniverseCmd(0.1, 6.67e-11) {}//disable default constr, only input-mode
public:
	const double deltaTime = 0.1;// action-interval s
	const double uGravity;//university gravity cosnt
	int currentTick{ 0 };
	int lastTick{ 0 };
	UniverseCmd(double dT, double uG) : deltaTime(dT),uGravity(uG) {
		cachedCapacity = 10;
		cachedCalculations = new std::vector<DefaultBody>[10];
	}
public:
	void update(int tick, std::vector<DefaultBody*>& bodyList) {
		if (lastTick > tick)return;
		lock.lock();
		if (tick >= cachedCapacity) {
			std::vector<DefaultBody>* newCache = new std::vector<DefaultBody>[tick * 2];
			for (size_t i = 0u; i < cachedCapacity; i++) {
				newCache[i] = cachedCalculations[i];
			}
			cachedCapacity = (tick) * 2;
			delete[]cachedCalculations;
			cachedCalculations = newCache;
		}
		cachedCalculations[tick] = std::vector<DefaultBody>();
		cachedCalculations[tick].reserve(bodyList.size());
		for (const auto& body : bodyList) {
			cachedCalculations[tick].emplace_back(*body);
		}
		
		lastTick = tick;
		lock.unlock();
	};
	std::vector<DefaultBody> getOnTick(int tick) {
		lock.lock();
		if (tick > cachedCapacity) {
			lock.unlock();
			throw std::exception("invalid-future tick");
		}
		std::vector<DefaultBody> result = cachedCalculations[tick];
		lock.unlock();
		return result;
	}
	std::optional<std::vector<DefaultBody>> getPrevDataTick() {
		std::vector<DefaultBody> result;
		lock.lock();
		if (currentTick == 0) {
			lock.unlock();
			return std::nullopt;
		}
		result =  cachedCalculations[currentTick - 1];
		lock.unlock();
		return result;
	}
};