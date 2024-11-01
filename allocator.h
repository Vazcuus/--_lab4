#pragma once
#include <iostream>
#include <memory>
#include <map>
#include <limits>
#include <vector>

template <typename T>
class PoolAllocator {
public:
    using value_type = T;

    // Конструктор, принимающий количество элементов для выделения
    PoolAllocator(size_t num_elements = 10) 
        : block_size(num_elements * sizeof(T)), current_block(nullptr), current_offset(0) {}

    ~PoolAllocator() {
        for (auto block : blocks) {
            ::operator delete(block);
        }
    }

    T* allocate(std::size_t n) {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
            throw std::bad_alloc();
        }

        if (!current_block || current_offset + n * sizeof(T) > block_size) {
            allocate_block();
        }

        T* result = reinterpret_cast<T*>(reinterpret_cast<char*>(current_block) + current_offset);
        current_offset += n * sizeof(T);
        return result;
    }

    void deallocate(T* p, std::size_t n) 
    {
    }

private:
    size_t block_size; // размер блока в байтах
    void* current_block; // указатель на текущий блок
    size_t current_offset; // текущее смещение в блоке
    std::vector<void*> blocks; // вектор для хранения выделенных блоков

    void allocate_block() {
        current_block = ::operator new(block_size);
        blocks.push_back(current_block);
        current_offset = 0;
    }
};