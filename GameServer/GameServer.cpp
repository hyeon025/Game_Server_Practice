#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex> //lock을 위한 헤더

vector<int32> v;

//Mutual Exclusive (상호배타적)
mutex m;

//RAII (Resource Acquisition Is Initialization)

void Push()
{
	for (int32 i = 0; i < 10000; i++)
	{
		//자물쇠 잠그기
		//std::lock_guard<std::mutex> lockGuard(m); //알아서 락 하고 풀어준다.
		std::unique_lock<std::mutex> uniqueLock(m, std::defer_lock);

		uniqueLock.lock(); //락 시점 미루기

		//m.lock();
		//m.lock();

		v.push_back(i);

		//자물쇠 풀기
		//m.unlock();
		//m.unlock();
	}
}

int main()
{
	std::thread t1(Push);
	std::thread t2(Push);

	t1.join();
	t2.join();

	cout << v.size() << endl;
}
