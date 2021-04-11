#include <iostream>
#include <list>
#include <vector>
#include <chrono>
using namespace std::chrono;

template <size_t chunkSize>
class FixedAllocator {
private:
    union node {
	int8_t data[chunkSize];
        node* next;
    };
    std::vector<node*> pools_of_memory;
    node* current_allocate_point;
    size_t  size = 2;
    static const size_t mx_pool_size = 8192;
public:
    FixedAllocator() {
        new_memory_pool();
    }
    void new_memory_pool() {
        if (size < mx_pool_size) {
            size *= 2;
        }
        current_allocate_point  = new node[size];
        pools_of_memory.push_back(current_allocate_point);
        for (int i = 0; i < size; ++i) {
            current_allocate_point[i].next = &current_allocate_point[i + 1];
        }
        current_allocate_point[size - 1].next = nullptr;
    }
    void* allocate() {
        if (!current_allocate_point) {
            new_memory_pool();
        }
        node*  memory_for_work = current_allocate_point; 
 	current_allocate_point = current_allocate_point->next; 
        return static_cast<void*>(memory_for_work);
    }
    void deallocate(void* memory_for_delete) {
        node* for_delete = static_cast<node*>(memory_for_delete);
        for_delete->next = current_allocate_point;
        current_allocate_point = for_delete;
    }
    ~FixedAllocator() {
        for (auto curr_memory_point : pools_of_memory) {
            delete curr_memory_point ;
        }
    }
};
template <class T>
class FastAllocator {
public:
    using value_type = T;
    FixedAllocator<24> fixedAlloc4;
    FastAllocator(){}
    T* allocate(size_t n) {
        if (n*sizeof(T) == n*24) {
            	return static_cast<T*>(fixedAlloc4.allocate());
        }
        else {
		std::cout<<sizeof(T);
            	return std::allocator<T>().allocate(n);
        }
    }
    void deallocate(T* ptr, size_t n){
	    if (n*sizeof(T) == n*24) {
                fixedAlloc4.deallocate(ptr);
	    }
	    else{
            	return std::allocator<T>().deallocate(ptr, n);
	    }
    }
};
 
int main() {
    std::list<long long> l1;
    std::list<long long,FastAllocator<long long>> l2;
    auto start_time = high_resolution_clock::now();
    for (int i = 0; i < 1e7; ++i) {
        l1.push_back(100000000000000);
    }
    auto end_time = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(end_time - start_time).count() << "ms" <<'\n';
    auto start_time1 = high_resolution_clock::now();
    for (int i = 0; i < 1e7; ++i) {
        l2.push_back(100000000000000);
    }
    auto end_time1 = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(end_time1 - start_time1).count() << "ms" << std::endl;
}
