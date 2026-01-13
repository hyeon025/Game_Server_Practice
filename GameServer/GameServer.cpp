#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>

mutex m;
queue<int32> q;
HANDLE handle;

//컨디션 변수 사용 (User-Level object이다. 커널	오브젝트 X)
condition_variable cv;

void Producer() 
{
	while (true)
	{
		//1) Lock 잡기
		//2) 공유 변수 값을 수정
		//3) Lock 해제
		//4) 조건변수를 통해 다른 쓰레드에게 통지

		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}

		cv.notify_one(); //대기중인 쓰레드 딱 1개를 깨움

		//this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

void Consumer()
{
	while (true)
	{
		unique_lock<mutex> lock(m);
		cv.wait(lock, []() { return q.empty() == false; });
		//1) Lock 잡기
		//2) 조건 확인
		//	-만족O->빠져나와 다음 코드 실행
		//	-만족X->Lock 풀고 대기 상태

		
		//Spurious Wakeup(가짜 깨움 현상) 방지를 위해 조건을 다시 확인
		//notify_one을 할 때 lock을 잡고있는 것이 아니기 때문

		//while (q.empty() == false)
		{
			int32 data = q.front();
			q.pop();
			cout << q.size() << endl;
		}
	}
}

int main()
{

	//커널 오브젝트(커널에서 관리하는 객체)
	//Usage count (참조 카운트)
	//Signal / Non-signal
	//Auto / Manual
	handle = ::CreateEvent(NULL, FALSE, FALSE, NULL); //보안속성, 메뉴얼리셋, 초기상태, 이름
	
	thread t1(Producer);
	thread t2(Consumer);

	t1.join();
	t2.join();

	::CloseHandle(handle);

}
