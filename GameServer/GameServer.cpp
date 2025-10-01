#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include "AccountManager.h"
#include "UserManager.h"

void Func1()
{
	for (int32 i = 0; i < 100; i++)
	{
		UserManager::Instance()->ProcessSave();
	}
}

void Func2()
{
	for (int32 i = 0; i < 100; i++)
	{
		AccountManager::Instance()->ProcessLogin();
	}
}

int main()
{
	std::thread t1(Func1); //(유저 락 -> 어카운트 락)
	std::thread t2(Func2); //(어카운트락 -> 유저 락)
	//데드락 상황 발생 (서로 락 걸려서 둘 다 기다리는 상황)

	//데드락을 해결하기 위해서는 락의 순서를 정하면 된다.


	t1.join();
	t2.join();

	cout << "Jobs Done" << endl;

	//참고
	mutex m1;
	mutex m2;

	std::lock(m1, m2); //m1.lock(); m2.lock();
	//알아서 일관적인 순서로 잠굼. 실전에서 많이 쓰지는 않음

	//adopt_lock : 이미 lock이 된 상태이니 나중에 소멸될 때 풀어줘라.
	lock_guard<mutex> g1(m1, std::adopt_lock);
}
