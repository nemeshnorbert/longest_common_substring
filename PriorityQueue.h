#ifndef LONGEST_COMMON_SUBSTRING_OF_SEVERAL_STRINGS_PRIORITY_QUEUE_H_
#define LONGEST_COMMON_SUBSTRING_OF_SEVERAL_STRINGS_PRIORITY_QUEUE_H_

#include "PriorityStack.h"

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
        if (!leftStack_.Empty() && !rightStack_.Empty())
        {
            return std::max(leftStack_.PriorityValue(),
                rightStack_.PriorityValue(),
                TComparer());
        }
        if (!leftStack_.Empty() && rightStack_.Empty())
        {
            return leftStack_.PriorityValue();
        }
        return rightStack_.PriorityValue();
    }

    void Swap(PriorityQueue<TValue, TComparer>& right)
    {
        leftStack_.swap(right.leftStack_);
        rightStack_.swap(right.rightStack_);
    }

private:
    ProirityStack<TValue, TComparer> leftStack_;
    ProirityStack<TValue, TComparer> rightStack_;
};

#endif 
