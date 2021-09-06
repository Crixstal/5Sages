#include <thread>
#include <iostream>
#include <chrono>
#include <windows.h>
#include <memory>

#include "sage.hpp"

std::mutex one;
std::mutex two;
std::mutex three;
std::mutex four;
std::mutex five;

std::mutex sentence;

void Sage::eat()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	auto start = std::chrono::steady_clock::now();

	sentence.lock();
	std::cout << m_name << " is thinking\n" << std::endl;
	sentence.unlock();

	std::this_thread::sleep_for(std::chrono::seconds(m_thinkTime));

	int maxEat = 0;
	int eatCounter = 0;

	while (maxEat <= 5)
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
				std::cout << m_name << " is starving\n" << std::endl;
				sentence.unlock();
			}
		}
	}

	sentence.lock();
	std::cout << m_name << " puts down his chopsticks\n" << std::endl;
	sentence.unlock();

	if (maxEat >= 5)
	{
		sentence.lock();
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // light green text
		std::cout << m_name << " finished his plate\n" << std::endl;
		sentence.unlock();

		SetConsoleTextAttribute(hConsole, 7); //white text (default)
	}

	auto end = std::chrono::steady_clock::now();
}

using namespace std;
int main()
{
	Array sage;
	
	int nextIndex = 0;

	std::cout << "How many sages dine around the table ?" << std::endl;
	std::cin >> sage.totalSage;

	for (int i = 0; i < sage.totalSage; i++)
	{
		//nextIndex = i + 1;
		//if (i == sage.totalSage - 1)
		//	nextIndex = 0;

		//sage.sageArray.push_back({ uni(rng), uni(rng), i, nextIndex }); //thinkTime, eatime, stick, nextStick
		//sticks.push_back(std::unique_ptr<std::mutex>(new std::mutex));
		std::cout << "Name of the sage number " << i + 1 << " ?" << std::endl;
		std::cin >> sage.sageArray[i].m_name;
	}

	for (int i = 0; i < sage.totalSage; ++i)
		std::cout << sage.sageArray[i].m_name << std::endl;

	//for (int i = 0; i < sage.totalSage; i++)
	//	sage.sageArray[i].trd = std::thread{ &Sage::eat, &sage.sageArray[i] };
	//
	//for (int i = 0; i < sage.totalSage; i++)
	//	sage.sageArray[i].trd.join();

	/*Sage platon, descartes, voltaire, socrate, heraclite;

	// chopstick1 is on their right, chopstick2 on their left

	platon.m_chopstick1 = &five, platon.m_chopstick2 = &one;
	descartes.m_chopstick1 = &one, descartes.m_chopstick2 = &two;
	voltaire.m_chopstick1 = &two, voltaire.m_chopstick2 = &three;
	socrate.m_chopstick1 = &three, socrate.m_chopstick2 = &four;
	heraclite.m_chopstick1 = &four, heraclite.m_chopstick2 = &five;

	platon.m_name = "Platon";
	descartes.m_name = "Descartes";
	voltaire.m_name = "Voltaire";
	socrate.m_name = "Socrate";
	heraclite.m_name = "Heraclite";

	platon.trd = thread{&Sage::eat, &platon};
	descartes.trd = thread{&Sage::eat, &descartes};
	voltaire.trd = thread{&Sage::eat, &voltaire};
	socrate.trd = thread{&Sage::eat, &socrate};
	heraclite.trd = thread{&Sage::eat, &heraclite};

	platon.trd.join();
	descartes.trd.join();
	voltaire.trd.join();
	socrate.trd.join();
	heraclite.trd.join();*/

	return 0;
}