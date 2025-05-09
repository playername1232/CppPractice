#pragma once
#include <utility>

template<typename T>
class PUniquePtr
{
private:
    T* ptr = nullptr;
public:
    explicit PUniquePtr<T>(T* ptr) : ptr(ptr) {}

    ~PUniquePtr()
    {
        delete ptr;
    }

    PUniquePtr(const PUniquePtr& other) = delete;
    PUniquePtr& operator=(PUniquePtr& other) = delete;

    PUniquePtr(PUniquePtr&& other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    PUniquePtr& operator=(PUniquePtr&& other) noexcept
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        
        return *this;
    }

    T& operator*() const
    {
        return *ptr;
    }
    
    T* operator->() const
    {
        return ptr;
    }

    // returns managed pointer
    T* Get() const
    {
        return ptr;
    }

    // Releases managed pointer
    T* Release()
    {
        T* temp = ptr;
        ptr = nullptr;

        return temp;
    }

    void Reset()
    {
        if (ptr != nullptr)
        {
            delete ptr;
            ptr = nullptr;
        }
    }

    explicit operator bool() const
    {
        return ptr != nullptr;
    }
};