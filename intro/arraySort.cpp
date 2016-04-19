#include <algorithm>
#include <ctime>
#include <iostream>
#include <climits>

int main(int argc, char **argv)
{
    // generate data
    const unsigned arraySize = 32768;
    int data[arraySize];
    int option = atoi(argv[1]);
    long long sum = 0;

    for (unsigned c = 0; c < arraySize; ++c)
        data[c] = std::rand();

    if(option)
        std::sort(data, data + arraySize);

    for (unsigned c = 0; c < arraySize*10000; ++c) {
        if (data[c%32768] >= INT_MAX/2)
                sum ++;
    }
    std::cout << "sum = " << sum << std::endl;
}
