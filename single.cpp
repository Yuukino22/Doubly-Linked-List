#include "single.hpp"

void singleLine(int simulationTime, int registers, int maxLineLength, std::vector<int> registerTime, std::vector<std::pair<int, int>> customerArrival)
{
    int enteredLine = 0;
    int exitedLine = 0;
    int exitedRegister = 0;
    int sumWaitTime = 0;
    double avgWaitTime;
    int leftInLine = 0;
    int leftInRegister = 0;
    int lost = 0;
    std::vector<int> Register(registers, 0);
    std::vector<int> WaitTime;
    Queue<int> Customer;
    int l = 0;
    for(int t = 0; t < simulationTime; t++)
    {   
        Queue<int>::ConstIterator iterator = Customer.constIterator();
        for(int i = 0; i < Customer.size(); i++)
        {
            WaitTime[iterator.value()]++;
            iterator.moveToNext();
        }
        if(l < customerArrival.size())
        {
            if(t == customerArrival[l].second)
            {
                for(int i = 0; i < customerArrival[l].first; i++)
                {
                    if(Customer.size() < maxLineLength)
                    {
                        WaitTime.push_back(0);
                        Customer.enqueue(WaitTime.size() - 1);
                        std::cout << t << " entered line 1 length " << Customer.size() << std::endl;
                        enteredLine++;
                    }
                    else
                    {
                        WaitTime.push_back(-1);
                        std::cout << t << " lost" << std::endl;
                        lost++;
                    }
                }
                l++;
            }
        }
        

        for (int j = 0; j < Register.size(); j++)
        {
            if(Register[j] > 0)
            {
                Register[j]--;
                if(Register[j] == 0)
                {
                    std::cout << t << " exited register " << (j + 1) << std::endl;
                    exitedRegister++;
                }
            }
        }

        if(! Customer.isEmpty())
        {
            int c = Customer.size();
            for(int i = 0; i < Register.size(); i++)
            {
                if(Register[i] == 0)
                {
                    Register[i] = registerTime[i];
                    c--;
                    std::cout << t << " exited line 1 length " << c << " wait time " << WaitTime[Customer.front()] << std::endl;
                    std::cout << t << " entered register " << (i + 1) << std::endl;
                    exitedLine++;
                    sumWaitTime += WaitTime[Customer.front()];
                    Customer.dequeue();
                    if(c == 0)
                    {
                        break;
                    }
                }
            }
        }
    }
    leftInLine = Customer.size();
    for(int i = 0; i < Register.size(); i++)
    {
        if(Register[i] != 0)
        {
            leftInRegister++;
        }
    }
    std::cout << simulationTime << " end" << std::endl;
    std::cout << std::endl;
    std::cout << "STATS" << std::endl;
    if(exitedLine == 0)
    {
        avgWaitTime = 0;
    }
    else
    {
        avgWaitTime = (double)sumWaitTime / exitedLine;
    }
    std::cout << "Entered Line    : " << enteredLine    << std::endl;
    std::cout << "Exited Line     : " << exitedLine     << std::endl;
    std::cout << "Exited Register : " << exitedRegister << std::endl;
    std::cout << "Avg Wait Time   : ";
    printf("%.2lf", avgWaitTime);
    std::cout << std::endl;
    std::cout << "Left In Line    : " << leftInLine     << std::endl;
    std::cout << "Left In Register: " << leftInRegister << std::endl;
    std::cout << "Lost            : " << lost           << std::endl;
}