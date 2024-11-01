#include "allocator.h"

template <typename T, typename Alloc = std::allocator<T>>
class SeqCont {
public:
    SeqCont(size_t capacity = 10) 
        : capacity(capacity), size(0), data(alloc.allocate(capacity)) {}

    ~SeqCont() {
        for (size_t i = 0; i < size; ++i) {
            data[i].~T(); // Вызываем деструктор для каждого элемента
        }
        alloc.deallocate(data, capacity);
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            resize();
        }
        new (&data[size]) T(value); //new для создания объекта
        ++size;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

private:
    Alloc alloc;
    T* data;
    size_t capacity;
    size_t size;

    void resize() {
        size_t new_capacity = capacity * 2;
        T* new_data = alloc.allocate(new_capacity);

        for (size_t i = 0; i < size; ++i) {
            new (&new_data[i]) T(std::move(data[i])); // Перемещаем элементы
            data[i].~T(); // Вызываем деструктор старых элементов
        }

        alloc.deallocate(data, capacity);
        data = new_data;
        capacity = new_capacity;
    }
};