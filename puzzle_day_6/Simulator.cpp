#include "Simulator.h"

Simulator::Simulator(const std::vector<int>& fishes)
{
    for (int i = 0; i <= 8; ++i)
    {
        m_fishes.push_back(0);
    }
    for (int i = 0; i <= 8; ++i)
    {
        m_nextFishes.push_back(0);
    }

    //initialize fish grouped by timer
    for (const auto& fish : fishes)
    {
        m_fishes[fish]++;
    }
}

void Simulator::simulate(int days)
{
    for (int i = 0; i < days; ++i)
    {
        for (int j = 0; j < m_fishes.size(); ++j)
        {
            tick(j);
        }

        //copy next state to current
        for (int j = 0; j < m_nextFishes.size(); ++j)
        {
            m_fishes[j] = m_nextFishes[j];
            m_nextFishes[j] = 0;
        }
//        printFishes();
   }
}

void Simulator::printFishes()
{
    std::cout << "Current state:";
    for (int i = 0; i < m_fishes.size(); ++i)
    {
        std::cout<< "\n\ttimer: " << i << " size: " << m_fishes[i];
    }
    std::cout<<"\n";
}

void Simulator::tick(int timer)
{
    if(timer == 0)
    {
        m_nextFishes[8] += m_fishes[timer];
        m_nextFishes[6] += m_fishes[timer];
    }
    else
    {
        m_nextFishes[timer - 1] += m_fishes[timer];
    }
}

long long int Simulator::fishCount()
{
    long long int size = 0;
    for (int i = 0; i < m_fishes.size(); ++i)
    {
        size += m_fishes[i];
    }

    return size;
}