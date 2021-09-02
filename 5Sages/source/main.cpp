#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <random>

std::mutex my_mutex;

//unsigned int sageNumber;
unsigned int minEatTime, maxEatTime;
unsigned int minThinkTime, maxThinkTime;

struct PHILO {
	bool isThinking = true;
	bool isStarving = false;
	bool isEating = false;
	bool isDoneEating = false;

	unsigned int eatTime = rand() % ((maxEatTime - minEatTime) + 1) + minEatTime;
	unsigned int thinkTime = rand() % ((maxThinkTime - minThinkTime) + 1) + minThinkTime;

	unsigned int chopstick1, chopstick2;
};


using namespace std;
int main()
{
	PHILO platon, descartes, voltaire, socrate, heraclite;

	platon.chopstick1 = 5, platon.chopstick2 = 1;
	descartes.chopstick1 = 1, descartes.chopstick2 = 2;
	voltaire.chopstick1 = 2, voltaire.chopstick2 = 3;
	socrate.chopstick1 = 3, socrate.chopstick2 = 4;
	heraclite.chopstick1 = 4, heraclite.chopstick2 = 5;


	//std::cout << "Enter number of sage : ";
	//std::cin >> sageNumber;

	std::cout << "Enter minimum eat time : ";
	std::cin >> minEatTime;
	std::cout << "Enter maximum eat time : ";
	std::cin >> maxEatTime;

	std::cout << "Enter minimum think time : ";
	std::cin >> minThinkTime;
	std::cout << "Enter maximum think time : ";
	std::cin >> maxThinkTime;

	//for (int i = 0; i < sageNumber; ++i)
	//{
		thread t1 {};
		thread t2 {};
		thread t3 {};
		thread t4 {};
		thread t5 {};
	//}

	return 0;
}