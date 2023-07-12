#include "JAKAZuRobot.h"
#include "jakaAPI.h"
#include <iostream>
#include <thread>

int main()
{
    int i;
    std::cout << "main-----------------------------------" << std::endl;
    #if 1
    JAKAZuRobot test;
    test.login_in("192.168.2.192");
    // test.power_on();
    #endif
    std::cout << "ok..." << std::endl;
    while(1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        RobotStatus rs;
        test.get_robot_status(&rs);
        std::cout << i++ <<" is_connect"<<rs.is_socket_connect << std::endl;
    }
    return 0;
}

