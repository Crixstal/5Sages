#include <thread>
#include <iostream>
#include <chrono>
#include <windows.h>
#include <memory>

#include "sage.hpp"

// RANDOM
std::default_random_engine rng;
std::uniform_int_distribution<int> uni(1, 5);

// MUTEX
std::mutex one;
std::mutex two;
std::mutex three;
std::mutex four;
std::mutex five;

std::mutex sentence;

void printName(int totalSage, std::string name)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < totalSage; ++i)
	{
		for (int j = 0; j < totalSage; ++j)
			SetConsoleTextAttribute(hConsole, j | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);

		sentence.lock();
		std::cout << name << std::endl;
		sentence.unlock();
	}

	SetConsoleTextAttribute(hConsole, 7);
}

void Sage::eat()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	auto start = std::chrono::steady_clock::now();

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

	sentence.lock();
	std::cout << m_name << " thinks " << m_thinkTime << " seconds before eating\n" << std::endl;
	sentence.unlock();

	std::this_thread::sleep_for(std::chrono::seconds(m_thinkTime));

	int maxEat = 0;
	int eatCounter = 0;

	SetConsoleTextAttribute(hConsole, 7); //white text (default)

	while (maxEat <= 10)
	{
		if (m_chopstick1->try_lock()) // if can lock
		{
			if (m_chopstick2->try_lock())
			{
				m_state = State::EAT;

				sentence.lock();
				std::cout << m_name << " is eating during " << m_eatTime << " seconds\n" << std::endl;
				sentence.unlock();

				std::this_thread::sleep_for(std::chrono::seconds(m_eatTime));
				m_chopstick2->unlock();

				sentence.lock();
				std::cout << m_name << " puts down his chopsticks\n" << std::endl;
				sentence.unlock();

				maxEat += m_eatTime;
			}

			m_chopstick1->unlock();
		}
		else
		{
			if (m_state == State::STARVE)
				continue;
			else
			{
				m_state = State::STARVE;

				sentence.lock();
				std::cout << m_name << " is starving because he can't eat so he returns thinking " << m_thinkTime << " seconds" << std::endl;
				sentence.unlock();

				std::this_thread::sleep_for(std::chrono::seconds(m_thinkTime));
			}
		}
	}

	if (maxEat >= 10)
	{
		sentence.lock();
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		std::cout << m_name << " finished his plate and won't touch his chopsticks\n" << std::endl;
		sentence.unlock();

		SetConsoleTextAttribute(hConsole, 7);
	}

	auto end = std::chrono::steady_clock::now();
}

using namespace std;
int main()
{
	Array sage;
	
	std::cout << "How many sages dine around the table ?" << std::endl;
	std::cin >> sage.totalSage;

	for (int i = 0; i < sage.totalSage; i++)
	{
		sage.sageArray.push_back({ uni(rng) , uni(rng) });

		std::cout << "Name of the sage number " << i + 1 << " ?" << std::endl;
		std::cin >> sage.sageArray[i].m_name;
	}

		std::cout << '\n' << std::endl;

	// chopstick1 is on their right, chopstick2 on their left

	//for (int i = 0; i < sage.totalSage; i++)
	//{
		sage.sageArray[0].m_chopstick1 = &five, sage.sageArray[0].m_chopstick2 = &one;
		sage.sageArray[1].m_chopstick1 = &one, sage.sageArray[1].m_chopstick2 = &two;
		sage.sageArray[2].m_chopstick1 = &two, sage.sageArray[2].m_chopstick2 = &three;
		sage.sageArray[3].m_chopstick1 = &three, sage.sageArray[3].m_chopstick2 = &four;
		sage.sageArray[4].m_chopstick1 = &four, sage.sageArray[4].m_chopstick2 = &five;
	//}

	for (int i = 0; i < sage.totalSage; i++)
		sage.sageArray[i].trd = std::thread{ &Sage::eat, &sage.sageArray[i] };
	
	for (int i = 0; i < sage.totalSage; i++)
		sage.sageArray[i].trd.join();

	return 0;
}