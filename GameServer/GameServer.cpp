﻿#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>

class SpinLock
{
public:
	void lock() 
	{
		//CAS (Compare-And-Swap)

		bool expected = false;
		bool desired = true;

		////CAS 의사코드
		//if(_locked == expected)
		//{
		//	expected = _locked;
		//	_locked = desired;
		//	return true;
		//}
		//else
		//{
		//	expected = _locked;
		//	return false;
		//}

		while (_locked.compare_exchange_strong(expected, desired) == false) //CAS 코드
		{
			//성공할 때까지 반복
			expected = false;
		}
	}

	void unlock() 
	{
		_locked.store(false);
	}
private:
	atomic<bool> _locked = false; //atomic에 valatile 기능도 포함
};

int32 sum = 0;
mutex m;
SpinLock spinLock;

void Add()
{
	for (int32 i = 0; i < 10'000; i++)
	{
		lock_guard<SpinLock> guard(spinLock);
		sum++;
	}
}

void Sub()
{
	for (int32 i = 0; i < 10'000; i++)
	{
		lock_guard<SpinLock> guard(spinLock);
		sum--;
	}
}

int main()
{
	//spinlock은 락이 금방 풀릴 것이라 예측될 때 사용한다.
	//커널모드로 전환하지 않고 유저모드에 계속 있기 때문에 cpu점유율이 높다.
	//context switch를 하지 않는다.

	thread t1(Add);
	thread t2(Sub);

	t1.join();
	t2.join();

	cout << sum << endl;
}
