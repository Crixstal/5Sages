#pragma once

#include <random>
#include <mutex>

std::default_random_engine rng;
std::uniform_int_distribution<int> uni(1, 5);

enum class State
{
	EAT, 
	STARVE
};

class Sage
{
	public:
		std::string m_name;

		State m_state{};

		int m_thinkTime = uni(rng);
		int m_eatTime = uni(rng);

		std::mutex* m_chopstick1{};
		std::mutex* m_chopstick2{};

		bool m_chopstick1IsUsed = false;
		bool m_chopstick2IsUsed = false;

		std::thread trd;

		void eat();

		Sage() = default;
		//~Sage();
};