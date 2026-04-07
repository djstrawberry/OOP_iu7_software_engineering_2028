#pragma once

#include "set.h"

// Constructors
template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T>::Set(std::initializer_list<U> ilist) : Set()
{
    std::ranges::for_each(ilist, [this](const U& el){ this->add(el); });
}