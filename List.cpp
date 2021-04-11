#include <iostream>
#include <list>
#include <vector>
#include <chrono>
using namespace std::chrono;

template <size_t ChunkSize>
class TFixedAllocator {
    union TNode { // union
        char data[ChunkSize];
        TNode* next; // free chunks of memory form a stack; pointer to the next (or nullptr)
    };

    TNode* free; // the topmost free chunk of memory (or nullptr)
    std::vector<TNode*> pools; // all allocated pools of memory
    int size = 1; // size of the last allocated pool of memory
    const int MAX_SIZE = 1024;

    void new_pool() { // allocate new pool of memory
        if (size < MAX_SIZE) {
            size *= 2;
        }
        free = new TNode[size];

        // form a stack of chunks of this pool
        pools.push_back(free);
        for (int i = 0; i < size; ++i) {
            free[i].next = &free[i + 1];
        }
        free[size - 1].next = nullptr;
    }
    TFixedAllocator() { // private for singleton
        new_pool();
    }
public:
    TFixedAllocator(const TFixedAllocator&) = delete; // for singleton
    static TFixedAllocator& instance() { // singleton
        static TFixedAllocator instance;
        return instance;
    }
    void* allocate() {
        if (!free) {
            new_pool();
        }
        TNode* result = free; // allocate the topmost element (saved in free)
        free = free->next; // and pop it from the stack of free chunks
        return static_cast<void*>(result);
    }
    void deallocate(void* elem) {
        TNode* node = static_cast<TNode*>(elem);

        // add to the stack of chunks
        node->next = free;
        free = node;
    }
    ~TFixedAllocator() {
        for (auto ptr : pools) {
            delete ptr;
        }
    }
};
template <class T>
class TFSBAllocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    template <class U>
    class rebind {
    public:
        using other = TFSBAllocator<U>;
    };

    pointer allocate(size_t n) {
        if (n == 1) {
            return static_cast<T*>(TFixedAllocator<sizeof(T)>::instance().allocate());
        }
        else {
            return std::allocator<T>().allocate(n);
        }
    }
    void deallocate(pointer p, size_t n) {
        if (n == 1) {
            TFixedAllocator<sizeof(T)>::instance().deallocate(static_cast<void*>(p));
        }
        else {
            return std::allocator<T>().deallocate(p, n);
        }
    }
    void construct(pointer p, const_reference t) {
        new (p) T(t);
    }
    void destroy(pointer p) {
        p->~T();
    }
};


template <class List>
void test(std::string comment, List l) {
    std::cout << comment;
    auto start_time = high_resolution_clock::now();
    for (int i = 0; i < 1e7; ++i) {
        l.push_back(i);
    }
    auto end_time = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(end_time - start_time).count() << "ms" << std::endl;
}

int main() {
    std::list<int> l1;
    std::list<int,TFSBAllocator<int>> l2;
    auto start_time = high_resolution_clock::now();
    for (int i = 0; i < 1e7; ++i) {
        l1.push_back(i);
    }
    auto end_time = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(end_time - start_time).count() << "ms" << std::endl;
    
    auto start_time1 = high_resolution_clock::now();
    for (int i = 0; i < 1e7; ++i) {
        l2.push_back(i);
    }
    auto end_time1 = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(end_time1 - start_time1).count() << "ms" << std::endl;
}

