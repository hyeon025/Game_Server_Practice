#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>

int32 sum = 0;

void Add()
{
	for (int32 i = 0; i < 100'0000; i++)
	{
		//sum++;

		//cpu 레지스터에 sum값을 가져와서 덧셈 처리
		int32 eax = sum;
		//eax = 0
		eax = eax + 1;
		//eax = 1
		sum = eax;
		//sum = 1
	}
}

void Sub()
{
	for (int32 i = 0; i < 100'0000; i++)
	{
		//sum--;

		//cpu 레지스터에 sum값을 가져와서 뺄셈 처리
		int32 eax = sum;
		//eax = 0
		eax = eax - 1;
		//eax = -1
		sum = eax;
		//sum = -1
	}
}

int main()
{
	Add();
	Sub();
	cout << sum << endl;

	//stack에서 정의하면 쓰레드 혼자 쓰기에 다른 쓰레드의 영향을 받지 않음. 
	//data나 heap 영역은 쓰레드끼리 공유해서 쓸 수 있다.

	std::thread t1(Add); //같은 데이터를 다른 쓰레드에서 처리.
	std::thread t2(Sub);
	t1.join();
	t2.join();
	cout << sum << endl;
}


