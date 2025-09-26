#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread> //윈도우,리눅스 등 다양한 환경에서 돌아가는 쓰레드 표준

void HelloThread() {
    cout << "Hello Thread" << endl;
}

int main()
{
    std::thread t; //만들기만 하는 것
    
    auto id = t.get_id(); //쓰레드 id가 0이 나온다. 

    t = std::thread(HelloThread); //이제야 id가 생겼다.

    int32 count = t.hardware_concurrency(); //난 8개 나옴
    auto id2 = t.get_id(); //id가 생긴 것을 볼 수 있다.

    if(t.joinable()) //t가 join상태이면
        t.join(); //t가 끝날 때까지 대기

    cout << "Hello Main" << endl;

}