#ifndef ARENA_HPP
#define ARENA_HPP
using namespace std;


template <size_t N>
struct arena
{
    static constexpr size_t alignment = alignof (max_align_t);
    
    auto allocate (size_t n) -> byte*
    {
        size_t aligned_n = align_up (n);
        size_t available_bytes = static_cast <size_t> (m_buffer + N - m_ptr);
        
        if (available_bytes >= aligned_n)
        {
            return exchange (m_ptr, m_ptr + aligned_n);
            
        } else
        {
            return (byte*) ::operator new (n);
        }
    }
    
    auto deallocate (byte* p, size_t n) -> void
    {
        if (pointer_in_buffer (p))
        {
            n = align_up (n);
            
            if (p + n == m_ptr)
            {
                m_ptr = p;
            }
            
        } else
        {
            ::operator delete (p);
        }
    }
    
private:
    alignas (alignment) byte m_buffer [N];
    byte* m_ptr;
    
    static auto align_up (size_t n) noexcept -> size_t
    {
        return (n + (alignment - 1) & ~(alignment - 1));
    }
    
    auto pointer_in_buffer (byte const* p) noexcept -> bool
    {
        return uintptr_t (p) >= uintptr_p (m_buffer) and uintptr_t (p)  < uintptr_p (m_buffer) + N;
    }
};


#endif
