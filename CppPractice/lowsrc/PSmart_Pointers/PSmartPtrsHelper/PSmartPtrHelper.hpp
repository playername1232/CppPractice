#pragma once
#include "../PUniquePtr/PUniquePtr.hpp"

template <typename T, typename Args>
PUniquePtr<T> MakePUnique(Args&&... args)
{
    return PUniquePtr<T>(new T(std::forward<Args>(args)...));
}