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

void Producer() 
{
	while (true)
	{
		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}

		::SetEvent(handle); //Signal 상태로 변경
		//this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

void Consumer()
{
	while (true)
	{
		::WaitForSingleObject(handle, INFINITE); //Signal 상태가 될때까지 대기

		unique_lock<mutex> lock(m);
		if (q.empty() == false)
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
