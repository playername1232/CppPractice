#pragma once
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <functional>

template <typename T>
class MemoryPool
{
private:
    T*      mem_pool_   = nullptr;
    bool*   mem_alloc_  = nullptr;

    size_t size_;
    size_t element_size_  = sizeof(T);

    static bool validatePtr(T* ptr, T* mem_start, size_t size)
    {
        return (ptr != nullptr && mem_start != nullptr) && ptr >= mem_start && ptr < mem_start + size;
    }

    void printMemoryValueInBytes(const T& element)
    {
        const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&element);
        for (size_t i = 0; i < sizeof(T); ++i)
        {
            printf("%02X ", bytes[i]);
        }
    }
    
public:
    MemoryPool() : size_(0) {}
    
    MemoryPool(const size_t size) : size_(size)
    {
        mem_pool_   = (T*)malloc(size * sizeof(T));
        // Type size alloc safety
        mem_alloc_  = (bool*)calloc(size, sizeof(bool));
    }

    ~MemoryPool()
    {
        free(mem_pool_);
        free(mem_alloc_);
    }
    
    MemoryPool(const MemoryPool& other) = delete;
    MemoryPool(MemoryPool&& other) noexcept = delete;

    T* AllocateMemory() noexcept
    {
        for (size_t i = 0; i < size_; i++)
        {
            if (mem_alloc_[i] == false)
            {
                mem_alloc_[i] = true;
                return mem_pool_ + i;
            }
        }

        return nullptr;
    }

    bool FreeMemory(T* ptr)
    {
        if (ptr == nullptr || (ptr < mem_pool_ || ptr >= mem_pool_ + size_))
            return false;

        size_t idx = ptr - mem_pool_;
        
        if (!mem_alloc_[idx])
            return false;
        
        mem_alloc_[ptr - mem_pool_] = false;
        return true;
    }

    /**
     * @param ptrs Array of pointers to reassign
     * @param newSize New size of memory block
     * @return 0 = operation unsuccessful | 1 = operation was successful
     * @warning May cause SIGSEGV if any pointer in ptrs is not retrieved from the current memory pool. All pointers must have been retrieved via AllocateMemory()!
   */
    bool ReallocateMemory(T** ptrs, const size_t newSize)
    {
        if (newSize == size_)
            return false;

        T* oldMemPool = mem_pool_;
        
        mem_pool_ = (T*)realloc(mem_pool_, newSize * element_size_);

        // reallocation failed
        if (!mem_pool_)
            return false;

        std::function<void(T* oldMem, T** ptr, T* newMem, size_t size)> func;

        bool* buffer = (bool*)calloc(newSize, sizeof(bool));
        
        if (size_ > newSize)
        {
            memcpy(buffer, mem_alloc_, newSize);

            func = [this](T* oldMem, T** ptr, T* newMem, size_t size)
            {
                if (this->validatePtr(*ptr, oldMem, size))
                {
                    size_t offset = *ptr - oldMem;
                    if (offset < size)
                        *ptr = newMem + offset;
                    else
                        *ptr = nullptr;
                }
            };
        }
        else
        {
            memcpy(buffer, mem_alloc_, size_);

            func = [this](T* oldMem, T** ptr, T* newMem, size_t size)
            {
                if (this->validatePtr(*ptr, oldMem, size))
                    *ptr = newMem + (*ptr - oldMem);
            };
        }

        size_t ptrCount = size_ > newSize ? newSize : size_;
        
        for (size_t i = 0; i < ptrCount; i++)
        {
            func(oldMemPool, &ptrs[i], mem_pool_, size_);
        }
        
        size_ = newSize;

        free(mem_alloc_);
        mem_alloc_ = buffer;
        
        return true;
    }

    void VisualizeMemory()
    {
        std::cout << "------------------------MEMORY VISUALIZER------------------------" << '\n';
        std::cout << "Allocated size: " << size_ << '\n';

        for (size_t i = 0; i < size_; i++)
        {
            std::cout << "Mem[" << i << "] Status: " << (mem_alloc_[i] ? "ALLOCATED" : "FREE") << " | Value: ";
            printMemoryValueInBytes(mem_pool_[i]);
            printf("\n");
        }

        std::cout << "------------------------END OF MEMORY VISUALIZER------------------------";
    }
};
