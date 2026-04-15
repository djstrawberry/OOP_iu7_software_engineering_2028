#pragma once

#include "const_iterator.h"
#include "exception.h"

//Constructors
template <CopiableMoveableAssignable T>
ConstIterator<T>::ConstIterator() noexcept
{
    this->curr.reset();
}

template <CopiableMoveableAssignable T>
ConstIterator<T>::ConstIterator(const std::shared_ptr<typename Set<T>::SetNode> &pnode) noexcept
{
    this->curr = pnode;
}

template <CopiableMoveableAssignable T>
ConstIterator<T>::ConstIterator(const ConstIterator<T> &other)
{
    other.checkExpired();
    this->curr = other.curr.lock();
}

// Getters
template <CopiableMoveableAssignable T>
typename Set<T>::SetNode &ConstIterator<T>::getCurr() const
{
    this->checkExpired();
    return *this->curr.lock();
}

// Change iterator
template <CopiableMoveableAssignable T>
void ConstIterator<T>::next() noexcept
{
    auto curr_ptr = this->curr.lock();
    if (curr_ptr)
        this->curr = curr_ptr->getNext();
}

// Operators
template <CopiableMoveableAssignable T>
ConstIterator<T> &ConstIterator<T>::operator++() noexcept
{
    this->next();
    return *this;
}

template <CopiableMoveableAssignable T>
ConstIterator<T> ConstIterator<T>::operator++(int) noexcept
{
    auto copy = *this;
    this->next();
    return copy;
}

template <CopiableMoveableAssignable T>
ConstIterator<T>::operator bool() const noexcept
{
    return this->curr.lock() != nullptr;
}

template <CopiableMoveableAssignable T>
ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator<T> &other) noexcept
{
    this->curr = other.curr.lock();
    return *this;
}

template <CopiableMoveableAssignable T>
ConstIterator<T> &ConstIterator<T>::operator=(ConstIterator<T> &&other) noexcept
{
    this->curr = std::move(other.curr.lock());
    return *this;
}

template <CopiableMoveableAssignable T>
const T &ConstIterator<T>::operator*() const
{
    this->checkExpired();

    return getCurr().value();
}

template <CopiableMoveableAssignable T>
const std::shared_ptr<T> ConstIterator<T>::operator->() const
{
    this->checkExpired();

    return this->curr.lock()->get();
}

template <CopiableMoveableAssignable T>
bool ConstIterator<T>::operator==(const ConstIterator<T> &other) const noexcept
{
    return this->curr.lock() == other.curr.lock();
}

template <CopiableMoveableAssignable T>
bool ConstIterator<T>::operator!=(const ConstIterator<T> &other) const noexcept
{
    return this->curr.lock() != other.curr.lock();
}

// Check iterator
template <CopiableMoveableAssignable T>
void ConstIterator<T>::checkExpired() const
{
    if (this->curr.expired())
        throw IteratorException("Iterator pointer expired.");
}
