#ifndef ARENA_HPP
#define ARENA_HPP

using namespace std;




template <auto _size_value, decltype (_size_value) _alignment = alignof (max_align_t)>
struct arena
{
    using size_type = decltype (_size_value);
    inline static constexpr size_type size_value = _size_value;
    inline static constexpr size_type alignment = _alignment;
    
    auto allocate (size_type n) noexcept -> byte*
    {
        size_type aligned_n = align_up (n);
        size_type available_bytes = static_cast <size_type> (m_buffer + size_value - m_ptr);
        
        if (available_bytes >= aligned_n)
        {
//            return exchange (m_ptr, m_ptr + aligned_n);
            auto* r = m_ptr;
            m_ptr += aligned_n;
            return r;
            
        } else
        {
            return static_cast<byte*> (::operator new (n));
        }
    }
    
    
    auto deallocate (byte* p, size_type n) noexcept -> void
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
    
    auto reset () noexcept -> void
    {
        m_ptr = m_buffer;
    }
    
    auto used () const noexcept -> size_t
    {
        return static_cast <size_t> (m_ptr - m_buffer);
    }
    
    template <typename T>
    [[nodiscard]] operator T* ()
    {
        return reinterpret_cast <T*> (allocate (sizeof (T)));
    }
    
    template <typename T>
    auto operator () (T* ptr) -> void
    {
        deallocate (reinterpret_cast <byte*> (ptr), sizeof (T));
    }
    
private:
    alignas (alignment) byte m_buffer [size_value];
    byte* m_ptr {m_buffer};
    
    static auto align_up (size_type n) noexcept -> size_type
    {
        return (n + (alignment - 1)) & ~(alignment - 1);
    }
    
    auto pointer_in_buffer (byte const* p) noexcept -> bool
    {
        return uintptr_t (p) >= uintptr_t (m_buffer) and uintptr_t (p)  < uintptr_t (m_buffer) +size_value;
    }
};


#endif
