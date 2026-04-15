#pragma once

#include "set.h"
#include "concepts.h"

// Constructors
template <CopiableMoveableAssignable T>
Set<T>::SetNode::SetNode(const T& value) noexcept : data(value), next(nullptr) { }

template <CopiableMoveableAssignable T>
Set<T>::SetNode::SetNode(T&& value) noexcept : data(std::move(value)), next(nullptr) { }

template <CopiableMoveableAssignable T>
Set<T>::SetNode::SetNode(const std::shared_ptr<SetNode> current_node, const T&value) noexcept :
    next(current_node), data(value) { }

// Factory method
template <CopiableMoveableAssignable T>
template <typename... Args>
std::shared_ptr<typename Set<T>::SetNode> Set<T>::SetNode::create(Args&&... args)
{
    struct EnableMakeShared : public Set<T>::SetNode
    {
        EnableMakeShared(Args&&... args) : Set<T>::SetNode(std::forward<Args>(args)...) {}
    }
    return std::make_shared<EnableMakeShared>(std::forward<Args>(args)...);
}

// Getters
template <CopiableMoveableAssignable T>
const T& Set<T>::SetNode::value() const noexcept
{
    return this->data;
}

template <CopiableMoveableAssignable T>
std::shared_ptr<T> Set<T>::SetNode::get()
{
    std::shared_ptr<SetNode> temp = this->shared_from_this();
    return { temp, &temp->data }; // aliasing constructor to return a shared_ptr to the data
}

template <CopiableMoveableAssignable T>
std::shared_ptr<typename Set<T>::SetNode> Set<T>::SetNode::getNext() const noexcept
{
    return this->next;
}

// Setters
template <CopiableMoveableAssignable T>
void Set<T>::SetNode::set(const T& data) noexcept
{
    this->data = data;
}

template <CopiableMoveableAssignable T>
void Set<T>::SetNode::setNext(const typename Set<T>::SetNode& node)
{
    try
    {
        this->next = std::make_shared<SetNode>(node);
    }
    catch(const std::bad_alloc& e)
    {
        throw MemoryException("Error allocating memory for next node!");
    }    
}

template <CopiableMoveableAssignable T>
void Set<T>::SetNode::setNext(const std::shared_ptr<SetNode>& pnode) noexcept
{
    this->next = pnode;
}

template <CopiableMoveableAssignable T>
void Set<T>::SetNode::setNextNull() noexcept
{
    this->next.reset();
}

// Operators
template <CopiableMoveableAssignable T>
bool Set<T>::SetNode::operator==(const std::shared_ptr<SetNode>& other) const noexcept
{
    if (!other)
        return false;
    return this->data == other->data && this->next == other->next;
}

template <CopiableMoveableAssignable T>
bool Set<T>::SetNode::operator!=(const std::shared_ptr<SetNode>& other) const noexcept
{   
    return this->data != other->data || this->next != other->next;
}