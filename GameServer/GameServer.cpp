#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread> //윈도우,리눅스 등 다양한 환경에서 돌아가는 쓰레드 표준

void HelloThread() {
    cout << "Hello Thread" << endl;
}

int main()
{
    HelloThread(); //main 쓰레드가 함수 호출
    std::thread t(HelloThread); //새로운 쓰레드가 생성되고 해당 함수를 실행 (main과 병렬로 실행)

    cout << "Hello Main" << endl;

    t.join(); //t가 끝날 때까지 대기

}