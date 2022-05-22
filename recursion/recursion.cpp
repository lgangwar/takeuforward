#include <iostream>

void printName(int a_Counter, int a_Num)
{
    if(a_Counter > a_Num)
        return;
    a_Counter++;

    std::cout << "recursion is dope" << std::endl;

    printName(a_Counter, a_Num);
}

int main()
{
    std::cout << "How many times you want to print" << std::endl;
    int n;
    std::cin >> n;

    printName(1, n);

    return 0;
}