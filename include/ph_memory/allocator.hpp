#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP
#include "arena.hpp"
#include "memory.hpp"
namespace ph {
template <size_t arenaSize = SIZE_OF_ONE_MEMORY_PAGE, typename Arena = arena <arenaSize>>
struct allocator
{
    using value_type = void;
    using size_type = size_t;
    using arena_type = Arena;
    
//    inline static constexpr size_type size_value = bytes;
    
    
    template <typename T>
    auto allocate (size_type n) -> T*
    {
        return reinterpret_cast <T*> (m_arena.allocate (n));
    }
    
    template <typename T>
    operator T ()
    {
        return reinterpret_cast <T> (m_arena.allocate (sizeof (T)));
    }
    
    template <typename T>
    auto deallocate (T* ptr, size_type n) -> void
    {
        m_arena.deallocate (reinterpret_cast <byte*> (ptr), n);
    }
    
    allocator (arena_type& a) : m_arena {a}
    {
        
    }
    
    arena_type& m_arena;
};


} // namespace

#endif
