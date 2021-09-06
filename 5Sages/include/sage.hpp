#pragma once

#include <random>
#include <mutex>
#include <vector>

std::default_random_engine rng;
std::uniform_int_distribution<int> uni(1, 5);

enum class State
{
	THINK,
	EAT, 
	STARVE
};

class Sage
{
	public:
		std::string m_name;

		State m_state = State::THINK;

		int m_thinkTime = uni(rng);
		int m_eatTime = uni(rng);

		std::mutex* m_chopstick1{};
		std::mutex* m_chopstick2{};

		std::thread trd;

		void eat();

		Sage() {};
		//~Sage();
};

class Array
{
	public:
		int totalSage = 0;
		std::vector<Sage> sageArray;
};