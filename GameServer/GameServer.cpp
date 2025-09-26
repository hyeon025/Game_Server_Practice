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
    
    t = std::thread(HelloThread); //뒤늦게 쓰레드 구동이 되도록 만들 수 있음.

    int32 count = t.hardware_concurrency(); // CPU 코어 개수 정보 추출(추출이 불가할 때는 0 리턴)
    auto id = t.get_id(); //쓰레드마다 id
    t.detach(); //std::thread 객체에서 실제 쓰레드를 분리(t를 이용해서 정보를 추출할 수 없어짐 - 거의 안씀)
    t.joinable(); //연동된 쓰레드가 없는 걸 확인

    cout << "Hello Main" << endl;
    


    t.join(); //t가 끝날 때까지 대기

}