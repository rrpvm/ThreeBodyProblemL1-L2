#pragma once
#include <vector>
#include "DefaultBody.hpp"
#include <optional>
#include <mutex>
#include <iostream>
#define DEFAULT_CMD_CAPACITY 76800
struct UniverseCmd
{
public:
	std::vector<DefaultBody>* cachedCalculations;
	int cachedCapacity;
	UniverseCmd() :UniverseCmd(0.1, 6.67e-11) {}//disable default constr, only input-mode
public:
	std::mutex lock;
	std::optional<std::vector<DefaultBody>> lastCalculation = std::nullopt;
	const double deltaTime = 0.1;// action-interval s
	const double uGravity;//university gravity cosnt
	int currentTick{ 0 };
	int lastTick{ 0 };
	UniverseCmd(double dT, double uG) : deltaTime(dT),uGravity(uG) {
		lastCalculation = std::nullopt;
		cachedCapacity = DEFAULT_CMD_CAPACITY;
		cachedCalculations = new std::vector<DefaultBody>[cachedCapacity];
	}
public:
	void update(int tick, std::vector<DefaultBody*>& bodyList) {
		if (lastTick > tick)return;
		if (tick >= cachedCapacity) {
			std::vector<DefaultBody>* newCache = new std::vector<DefaultBody>[tick * 2];
			for (size_t i = 0u; i < cachedCapacity; i++) {
				newCache[i] = cachedCalculations[i];
			}
			lock.lock();
			cachedCapacity = (tick) * 2;
			delete[]cachedCalculations;
			cachedCalculations = newCache;
			lock.unlock();
		}
		cachedCalculations[tick] = std::vector<DefaultBody>();
		cachedCalculations[tick].reserve(bodyList.size());
		for (const auto& body : bodyList) {
			cachedCalculations[tick].push_back(*body);
		}
		lastTick = tick;
		lastCalculation = cachedCalculations[tick];
	};
	std::vector<DefaultBody> getOnTick(int tick) {
		
		if (tick > cachedCapacity) {
			
			throw std::exception("invalid-future tick");
		}
		std::vector<DefaultBody> result = cachedCalculations[tick];
		
		return result;
	}
	std::optional<std::vector<DefaultBody>> getPrevDataTick() {
		std::vector<DefaultBody> result;
		
		if (currentTick == 0) {
			
			return std::nullopt;
		}
		result =  cachedCalculations[currentTick - 1];
	
		return result;
	}
};