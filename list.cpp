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

    bool is_ready = false;
    std::vector<node*> pools_of_memory;
    node* current_allocate_point = nullptr;
    size_t  size = 2;
    static const size_t mx_pool_size = 8192;

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
public:
    FixedAllocator() {
        new_memory_pool();
    }
    FixedAllocator(const FixedAllocator& alloc): is_ready(alloc.is_ready), pools_of_memory(alloc.pools_of_memory), 
	current_allocate_point(alloc.current_allocate_point), size(alloc.size){}
    void* allocate() {
	    std::cout<<2;
        if (!is_ready) {
            new_memory_pool();
	    is_ready = true;
        }
	std::cout<<3;
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
    FastAllocator() = default;
    ~FastAllocator() = default;
    FastAllocator(const FastAllocator& alloc):fixedAlloc4(alloc.fixedAlloc4), fixedAlloc8(alloc.fixedAlloc8){}
    FixedAllocator<24> fixedAlloc4;
    FixedAllocator<8> fixedAlloc8;
    T* allocate(size_t n) {
	    std::cout<<6<<' ';
        if (n*sizeof(T) == n*24) {
		std::cout<<1;
            	return static_cast<T*>(fixedAlloc4.allocate());
        }
	else if(n*sizeof(T) == n*8){
		std::cout<<4;
                return static_cast<T*>(fixedAlloc8.allocate());
	}
        else {
		std::cout<<sizeof(T);
            	return std::allocator<T>().allocate(n);
        }
    }
    void deallocate(T* ptr, size_t n){
	    if (n*sizeof(T) == n*4) {
                fixedAlloc4.deallocate(ptr);
	    }
	    else if(n*sizeof(T) == n*8){
                fixedAlloc8.deallocate(ptr);
	    }
	    else{
            	return std::allocator<T>().deallocate(ptr, n);
	    }
    }
};
 
int main() {
    std::list<int> l1;
    std::list<int,FastAllocator<int>> l2;
    auto start_time = high_resolution_clock::now();
    for (int i = 0; i < 15; ++i) {
        l1.push_back(i);
    }
    auto end_time = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(end_time - start_time).count() << "ms" <<'\n';
    auto start_time1 = high_resolution_clock::now();
    std::cout<<8;
    for (int i = 0; i < 15; ++i) {
	    std::cout<<"aaaaaaaaaaaa";
        l2.push_back(i);
    }
    auto end_time1 = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(end_time1 - start_time1).count() << "ms" << std::endl;
    for(auto it: l1){
    	std::cout<<it<<' ';
    }
    std::cout<<'\n';
    for(auto it:l2){
   	std::cout<<it<<' ';
    }

}
