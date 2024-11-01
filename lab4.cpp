#include "allocator.h"
#include "factorial.h"
#include "SeqCont.h"
#include <iomanip>
int main() {
    std::map<int, int, std::less<int>, PoolAllocator<std::pair<int, int>>> my_map;

    for (int i = 1; i < 10; i++)
    {
        my_map[i] = factorial(i);
    }

    for (const auto& pair : my_map) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    SeqCont<int> mycont;
    std::cout << std::setw(35) << "Cont with standart C++ allocator: ";
    for (int i = 0; i < 10; i++)
    {
        mycont[i] = i;
    }
    for (auto i = 0; i < 10; i++)
    {
        std::cout << mycont[i] << " ";
    }
    std::cout << std::endl;

    SeqCont<int, PoolAllocator<int>> mycont2;
    std::cout << std::setw(35) << "Cont with custom allocator: ";
    for (int i = 0; i < 10; i++)
    {
        mycont2[i] = i;
    }
    for (auto i = 0; i < 10; i++)
    {
        std::cout << mycont2[i] << " ";
    }
}
