#ifndef LONGEST_COMMON_SUBSTRING_PRIORITY_QUEUE_H_
#define LONGEST_COMMON_SUBSTRING_PRIORITY_QUEUE_H_

#include <cassert>
#include "priority_stack.h"

template <typename TValue, typename TComparer = std::less<TValue>>
class PriorityQueue
{
public:
    PriorityQueue() : leftStack_(), rightStack_()
    {}

    PriorityQueue(const PriorityQueue<TValue, TComparer>& right)
        : leftStack_(right.leftStack_), rightStack_(right.rightStack_)
    {}

    void Push(const TValue& value)
    {
        leftStack_.Push(value);
    }

    void Pop()
    {
        if (rightStack_.Empty())
        {
            do
            {
                rightStack_.Push(leftStack_.Top());
                leftStack_.Pop();
            } while (!leftStack_.Empty());
        }
        rightStack_.Pop();
    }

    bool Empty() const
    {
        return leftStack_.Empty() && rightStack_.Empty();
    }

    size_t Size() const
    {
        return leftStack_.Size() + rightStack_.Size();
    }

    TValue PriorityValue() const
    {
        assert(!leftStack_.Empty() || !rightStack_.Empty());
        if (!leftStack_.Empty() && !rightStack_.Empty())
        {
            return std::max(leftStack_.PriorityValue(),
                rightStack_.PriorityValue(),
                TComparer());
        }
        else if (!leftStack_.Empty() && rightStack_.Empty())
        {
            return leftStack_.PriorityValue();
        }
        return rightStack_.PriorityValue();
    }

    void Swap(PriorityQueue<TValue, TComparer>& right)
    {
        leftStack_.Swap(right.leftStack_);
        rightStack_.Swap(right.rightStack_);
    }

private:
    PriorityStack<TValue, TComparer> leftStack_;
    PriorityStack<TValue, TComparer> rightStack_;
};

#endif
