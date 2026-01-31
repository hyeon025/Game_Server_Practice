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
void PromiseWorker(std::promise<string>&& promise)
{
	promise.set_value("Secret Message");
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

		

		int64 sum = future.get();  //결과물 가져오기
	}

	//std::promise
	{
		//미래(std::future)에 결과물을 반환해줄 것이라 약속
		std::promise<string> promise;
		std::future<string> future = promise.get_future();

		thread t(PromiseWorker, std::move(promise)); //promise 소유권 이동

		string message = future.get(); //데이터 가져오기 (future.get()은 한 번만 호출)
		cout << message << endl;

		t.join();
	}

}