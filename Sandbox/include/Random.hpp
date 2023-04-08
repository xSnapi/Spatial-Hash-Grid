#pragma once

#include <random>

class Random {
public:
	template<typename T>
	static T Rand(T min, T max) {
		return std::uniform_real_distribution<T>(min, max)(m_randEngine);
	}

	static int Rand(int min, int max) {
		return std::uniform_int_distribution<int>(min, max)(m_randEngine);
	}

private:
	Random() {
		m_randEngine.seed(std::random_device()());
	}

	~Random() = default;

	static std::mt19937 m_randEngine;
};
