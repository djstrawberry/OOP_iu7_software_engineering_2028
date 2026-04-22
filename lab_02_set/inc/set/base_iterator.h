#pragma once

#include "concepts.h"

#include <memory>

template <CopiableMoveableAssignable T>
class Set;

template <CopiableMoveableAssignable T>
class BaseIterator
{
    static_assert(CopiableMoveableAssignable<T>, 
                  "BaseIterator value type must be copyable, movable, and assignable");
public:
    BaseIterator() = default;
    virtual ~BaseIterator() = 0;

protected:
    std::weak_ptr<typename Set<T>::SetNode> curr;
    friend class Set<T>;
};

#include "base_iterator.hpp"
