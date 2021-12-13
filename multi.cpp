#include "multi.hpp"

int minLine(std::vector<Queue<int>> Customer)
{
    std::vector<int> l;
    for(int i = 0; i < Customer.size(); i++)
    {
        l.push_back(Customer[i].size());
    }
    std::vector<int>::iterator result = std::min_element(l.begin(), l.end());
    return std::distance(l.begin(), result);
}

void multiLine(int simulationTime, int registers, int maxLineLength, std::vector<int> registerTime, std::vector<std::pair<int, int>> customerArrival)
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
    std::vector<Queue<int>> Customer;
    for(int i = 0; i < registers; i++)
    {
        Customer.push_back(Queue<int>());
    }
    int l = 0;
    for(int t = 0; t < simulationTime; t++)
    {

        for(auto q: Customer)
        {
            Queue<int>::ConstIterator iterator = q.constIterator();
            for(int i = 0; i < q.size(); i++)
            {
                WaitTime[iterator.value()]++;
                iterator.moveToNext();
            }
        }
        if(l < customerArrival.size())
        {
            if(t == customerArrival[l].second)
            {
                for(int i = 0; i < customerArrival[l].first; i++)
                {
                    if(Customer.size() != 0)
                    {
                        int result = minLine(Customer);
                        if(Customer[result].size() < maxLineLength)
                        {
                            WaitTime.push_back(0);
                            Customer[result].enqueue(WaitTime.size() - 1);
                            std::cout << t << " entered line " << (result + 1) << " length " << Customer[result].size() << std::endl;
                            enteredLine++;
                        }
                        else
                        {
                            WaitTime.push_back(-1);
                            std::cout << t << " lost" << std::endl;
                            lost++;
                        }
                    }
                }
                l++;
            }
        }
        
        for(int j = 0; j < Customer.size(); j++)
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
            if(! Customer[j].isEmpty())
            {
                int c = Customer[j].size();
                if(Register[j] == 0)
                {
                    Register[j] = registerTime[j];
                    c--;
                    std::cout << t << " exited line " << (j + 1) << " length " << c << " wait time " << WaitTime[Customer[j].front()] << std::endl;
                    std::cout << t << " entered register " << (j + 1) << std::endl;
                    sumWaitTime += WaitTime[Customer[j].front()];
                    Customer[j].dequeue();
                    exitedLine++;
                }
            }
        }
    }
    for(int i = 0; i < Customer.size(); i++)
    {
        leftInLine += Customer[i].size();
    }
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