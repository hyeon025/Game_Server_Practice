#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <future>


int64 Calculate()
{
	int64 sum = 0;

	for (int32 i = 0; i < 100'000; i++)
	{
		sum += i;
	}

	return sum;
}

int main()
{
	////동기 방식의 실행 (synchronous)
	//int64 sum = Calculate();
	//cout << sum << endl;

	//std::future
	{
		//1)deferred -> lazy evaluation (지연시켜 실행)
		//2)async -> 별도의 쓰레드를 만들어서 실행
		//3)deferred | async -> 알아서 선택
		std::future<int64> future = std::async(std::launch::async,Calculate);

		//작업이 끝났는지 잠시 살펴보기
		std::future_status status = future.wait_for(std::chrono::milliseconds(1));
		if (status == future_status::ready)
		{
			std::cout << "작업 끝남" << std::endl;
		}

		int64 sum = future.get();  //결과물 가져오기
	}
}