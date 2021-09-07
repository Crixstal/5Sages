#pragma once

#include <random>
#include <mutex>
#include <vector>

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

		int m_thinkTime = 0;
		int m_eatTime = 0;
		int m_finishEatTime = 0;

		std::mutex* m_chopstick1{};
		std::mutex* m_chopstick2{};

		std::thread trd;

		void eat();

		Sage() {}
		Sage(int think, int eat, int finishEatTime);
		//~Sage() {}
};

class Array
{
	public:
		int m_totalSage = 0;
		std::vector<Sage> sageArray;
};