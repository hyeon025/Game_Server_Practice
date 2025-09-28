#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>

// [1][2][3]
// 메모리가 꽉차면
// [1][2][3][4][5][6]
// 더 큰 메모리 할당해서 이전 메모리 복사하고 삭제

//두개의 쓰레드가 둘 다 delete를 해서 double free 문제 발생.

vector<int32> v;

void Push()
{
	for (int32 i = 0; i < 10000; i++)
	{
		v.push_back(i);
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
