// clang++ -std=c++11 testPointerTraits.cpp

#include <memory>
#include <type_traits>
#include <vector>

template <class T>
inline T* to_raw_pointer(T* p)
{
    return p;
}

template <class Pointer>
inline typename std::pointer_traits<Pointer>::element_type*
to_raw_pointer(Pointer& p)
{
    return to_raw_pointer(p.operator->());
}

template<typename T>
class SmartPoint {
public:
    SmartPoint()
        : m_ptr(nullptr)
    {
    }

    SmartPoint(T* ptr)
        : m_ptr(ptr)
    {
    }

    static T pointer_to(SmartPoint<T> p)
    {
        return p.m_ptr;
    }

private:
    T* m_ptr;
};

int main (int argc, char const *argv[])
{
    static_assert(std::is_same<std::pointer_traits<int*>::element_type, int>::value, "");
    static_assert(std::is_same<std::pointer_traits<std::unique_ptr<int>>::element_type, int>::value, "");
    static_assert(std::is_same<std::pointer_traits<std::unique_ptr<int>>::element_type*, int*>::value, "");
    static_assert(std::is_same<std::pointer_traits<SmartPoint<int>>::element_type, int>::value, "");
    static_assert(std::is_same<std::pointer_traits<SmartPoint<int>>::element_type*, int*>::value, "");
    
    static_assert(std::is_same<std::pointer_traits<std::vector<int>>::element_type, int>::value, "");

    std::unique_ptr<int> unique_ptr_to_int = std::unique_ptr<int>(new int(9));
    int* int_pointer = to_raw_pointer(unique_ptr_to_int);

    return 0;
}
