#include "pch.h"
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
		while (_locked)
		{

		}

		_locked = true;
	}

	void unlock() 
	{
		_locked = false;
	}
private:
	volatile bool _locked = false; //volatile : 컴파일러 최적화 방지
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
	//volatile 테스트
	int32 a = 0;
	a = 1;
	a = 2;
	a = 3;
	a = 4; // volatile 미사용시 최적화로 a가 4로 바로 바뀜
	cout << a << endl;
	///////////////////////

	thread t1(Add);
	thread t2(Sub);

	t1.join();
	t2.join();

	cout << sum << endl;
}
