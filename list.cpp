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

template<typename T, typename Allocator = std::allocator<T>>
class List{
	struct Node{
		Node* prev = nullptr;
		Node* next = nullptr;
		T val;
		Node (T value): val(value){}
		Node() = default;
	};
	size_t size = 0;
	Node* fake_node;
	Node* head;
	typename std::allocator_traits<Allocator>::template rebind_alloc<Node> alloc;
	using AllocTraits = std::allocator_traits<typename std::allocator_traits<Allocator>::template rebind_alloc<Node>>;
public:
	explicit List(const Allocator& alloc = Allocator()) : alloc(alloc){}
	List(size_t count, const T& value = T(), const Allocator& alloc = Allocator()) : alloc(alloc){
	}
	void push_back(const T& val){
		if(size == 0){
			head = AllocTraits::allocate(alloc, 1);
			AllocTraits::construct(alloc, head, val);
			head->prev = fake_node;
			head->next = fake_node;
			fake_node->prev = head;
			fake_node->next = head;
		}
		else{
			Node* new_node = AllocTraits::allocate(alloc, 1);
			AllocTraits::construct(alloc, new_node, val);
			fake_node->prev->next = new_node;
			new_node->prev = fake_node->prev;
			fake_node->prev = new_node;
			new_node->next = fake_node;
		}
	}
};


int main() {
	List<int> l;
	l.push_back(1);
}
