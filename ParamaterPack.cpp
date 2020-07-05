// ParamaterPack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>



struct Packed
{
    char* parameters;
    char* returnValue;
    int size;
};
template<typename ...Ts> Packed f(Ts&&... args)
{
    Packed packed;
    packed.size = 0;
    packed.size = ((sizeof(Ts) + packed.size % sizeof(Ts)) + ...);
    printf("size is %i\n", packed.size);
    char* memoryBlock = (char*)calloc(1, packed.size);
    packed.parameters = memoryBlock;


    int written = 0;

    auto pack = [&memoryBlock, &packed, &written](auto& item)
    {
        memoryBlock += written % sizeof(item);
        printf("moving %i forward...\n", written % sizeof(item));
        memcpy(memoryBlock, &item, sizeof(item));
        printf("wrote data to %p for a total of %i bytes.\n", memoryBlock, sizeof(item));
        packed.returnValue = memoryBlock;
        memoryBlock += sizeof(item); //move pointer forward
        written += sizeof(item);
    };
    (pack(args), ...);
    return packed;
}

struct MyStruct
{
    char a;
    double b;
    int ret;
};

void test(MyStruct* data)
{
    std::cout << "my data is " << data->a << " and " << data->b << "\n";
    data->ret = 69;
}

int main()
{
    std::cout << "Hello World!\n";
    Packed block = f(65, 10., 0);
    ((void(*)(void*))test)(block.parameters); //just to call by a function pointer
    printf("Returned value %i\n", *block.returnValue);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
