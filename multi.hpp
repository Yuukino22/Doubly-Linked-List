#ifndef MULTI_HPP
#define MULTI_HPP

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <stdio.h>
#include "Queue.hpp"

//Return the queue which has the smallest size.
//If there are more than 1 result, return the left most one(index min).
int minLine(std::vector<Queue<int>> Customer);

//The main function of multiply lines.
void multiLine(int simulationTime, int registers, int maxLineLength, std::vector<int> registerTime, std::vector<std::pair<int, int>> customerArrival);

#endif