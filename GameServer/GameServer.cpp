#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread> //윈도우,리눅스 등 다양한 환경에서 돌아가는 쓰레드 표준

void HelloThread() {
    cout << "Hello Thread" << endl;
}

void HelloThread_2(int32 num) {
    cout << num << endl;
}

int main()
{
    vector<std::thread> v;

    for (int32 i = 0; i < 10; i++)
    {
        v.push_back(std::thread(HelloThread_2, i)); 
        //순서대로 출력하지는 않음. 예상불가. 병렬적인 쓰레드임
        //순차적이지 않아서 출력되었을 때 순서가 뒤죽박죽임.
    }

    for (int32 i = 0; i < 10; i++)
    {
        if (v[i].joinable())
            v[i].join();
    }

    cout << "Hello Main" << endl;

}