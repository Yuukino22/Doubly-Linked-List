#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <stdio.h>
#include "Queue.hpp"

#include "multi.hpp"
#include "single.hpp"





int main()
{
    int simulation;
    int registers;
    int maxLineLength;
    bool single;
    std::cin >> simulation;
    std::cin >> registers;
    std::cin >> maxLineLength;
    std::string s;
    std::cin >> s;
    single = (s == "S");
    std::vector<int> registerTime;
    for (int i = 0; i < registers; i++)
    {
        int t;
        std::cin >> t;
        registerTime.push_back(t);
    }
    std::vector<std::pair<int, int>> customerArrival;
    std::string temp;
    std::getline(std::cin, temp);
    while(true)
    {
        std::string l;
        std::getline(std::cin, l);
        if(l == "END")
        {
            break;
        }
        std::size_t space = l.find(" ");
        int cNum = std::stoi(l.substr(0, space));
        int time = std::stoi(l.substr(space + 1));
        customerArrival.push_back(std::make_pair(cNum, time));
    }
    std::cout << "LOG" << std::endl;
    std::cout << "0 start" << std::endl;
    int simulationTime = simulation * 60;
    if(single)
    {  
        singleLine(simulationTime, registers, maxLineLength, registerTime, customerArrival);
    }
    else
    {
        multiLine(simulationTime, registers, maxLineLength, registerTime, customerArrival);
    }

    return 0;
}

