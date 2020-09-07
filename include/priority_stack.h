#ifndef LONGEST_COMMON_SUBSTRING_PRIORITY_STACK_H_
#define LONGEST_COMMON_SUBSTRING_PRIORITY_STACK_H_

#include <vector>

template <typename TValue, typename TComparer = std::less<TValue>>
class ProirityStack
{
public:
    ProirityStack() : data_(), prefixPriorityId_(), comparer_()
    {}

    ProirityStack(const ProirityStack<TValue, TComparer>& right)
        : data_(right.data_),
        prefixPriorityId_(right.prefixPriorityId_),
        comparer_(right.comparer_)
    {}

    void Push(const TValue& value)
    {
        data_.push_back(value);
        if (!prefixPriorityId_.empty())
        {
            prefixPriorityId_.push_back(
                comparer_(value, data_[prefixPriorityId_.back()]) ?
                prefixPriorityId_.back() :
                data_.size() - 1);
        }
        else
        {
            prefixPriorityId_.push_back(data_.size() - 1);
        }
    }

    void Pop()
    {
        data_.pop_back();
        prefixPriorityId_.pop_back();
    }

    bool Empty() const
    {
        return data_.empty();
    }

    size_t Size() const
    {
        return data_.size();
    }

    const TValue& Top() const
    {
        return data_.back();
    }

    TValue PriorityValue() const
    {
        return data_[prefixPriorityId_.back()];
    }

    void swap(ProirityStack<TValue, TComparer>& right)
    {
        data_.swap(right.data_);
        prefixPriorityId_.swap(right.prefixPriorityId_);
        std::swap(comparer_, right.comparer_);
    }

private:
    std::vector<TValue> data_;
    std::vector<size_t> prefixPriorityId_;
    TComparer comparer_;
};


#endif
