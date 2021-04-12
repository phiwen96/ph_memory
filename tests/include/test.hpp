#include <catch2/catch.hpp>
#include <ph_memory/allocator.hpp>
#include <ph_type_list/type_list.hpp>
#include <variant>
using namespace std;
using namespace ph;



struct user
{
    inline static arena <1024> m_arena {};
    auto operator new (size_t t) -> void*
    {
        return m_arena.allocate (sizeof (t));
    }
    auto operator delete (void* p) -> void
    {
        m_arena.deallocate (static_cast<byte*>(p), sizeof (m_arena));
    }
//    auto operator new[] (size_t size) -> void*
//    {
//        return m_arena.allocate (size);
//    }
//    auto operator delete[] (void* p, size_t size) -> void
//    {
//        m_arena.deallocate (static_cast<byte*>(p), size);
//    }
    
    
    
    int i;
};

inline static arena <500000> m_arena;


auto run () -> int 
{
    cout << alignof (int) << endl;
    int* j {m_arena};
    *j = 2;
    
    m_arena (j);
    
    cout << *j << endl;
    
//    cout << sizeof (string) << endl;
//    auto user1 = new user {2};
//    delete user1;
    
    byte m_bytes [10];
    
    user* u = new user{4};
    
    int* i = new (m_bytes) int {7};
    cout << *i << endl;
//    int* j = new (m_bytes) int {9};
    
    
    return 0;
}
