#include <iostream>
#include <unistd.h>

void option0()
{
    std::cout << "Option 0 was choosen, looping" << std::endl;
    while (true)
    {
        sched_yield();
    }
}

void option1()
{
    std::cout << "Option 1 was choosen, looping" << std::endl;
    while (true)
    {
        sched_yield();
    }
}

int main(int argc, char* argv[])
{
    if (argc % 2 == 1)
    {
        option0();
    }
    else
    {
        option1();
    }
    return 0;
}