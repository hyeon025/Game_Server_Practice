#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>

mutex m;
queue<int32> q;

void Producer() 
{
	while (true)
	{
		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void Consumer()
{
	while (true)
	{
		{
			unique_lock<mutex> lock(m);
			if (q.empty() == false)
			{
				int32 data = q.front();
				q.pop();
				cout << data << endl;
			}
		}
	}
}

int main()
{
	thread t1(Producer);
	thread t2(Consumer);

	t1.join();
	t2.join();
}
