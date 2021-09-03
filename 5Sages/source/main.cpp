#include <thread>
#include <iostream>
#include <chrono>

#include "sage.hpp"

std::mutex one;
std::mutex two;
std::mutex three;
std::mutex four;
std::mutex five;

void Sage::eat()
{
	auto start = std::chrono::steady_clock::now();

	std::cout << m_name << " is thinking\n" << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(m_thinkTime));

	m_state = State::STARVE;

	while (m_state == State::STARVE)
	{
		if (m_chopstick1->try_lock()) // if can lock
		{
			if (m_chopstick2->try_lock())
			{
				m_state = State::EAT;
				std::cout << m_name << " is eating\n" << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(m_eatTime));
				m_chopstick2->unlock();
			}

			m_chopstick1->unlock();
		}
		else
		{
			m_state = State::STARVE;
			std::cout << m_name << " is starving\n" << std::endl;
		}
	}

	std::cout << m_name << " puts down his chopsticks\n" << std::endl;

	auto end = std::chrono::steady_clock::now();
}

using namespace std;
int main()
{
	Sage platon, descartes, voltaire, socrate, heraclite;

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
	heraclite.trd.join();

	return 0;
}