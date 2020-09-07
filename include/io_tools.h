#ifndef LONGEST_COMMON_SUBSTRING_IO_TOOLS_H_
#define LONGEST_COMMON_SUBSTRING_IO_TOOLS_H_

#include <iostream>
#include <vector>
#include <string>

namespace IO
{
    template <typename TValue>
    TValue ReadValue(std::istream& inputStream = std::cin)
    {
        TValue value;
        inputStream >> value;
        return value;
    }

    template <typename TValue>
    void WriteValue(const TValue& value,
        std::ostream& outputStream = std::cout,
        const std::string& separator = " ")
    {
        outputStream << value << separator;
    }

    template <typename TCollection>
    void WriteValues(const TCollection& collection,
        std::ostream& outputStream = std::cout,
        const std::string& separator = " ")
    {
        for (const auto& value : collection)
        {
            WriteValue(value, outputStream);
            outputStream << separator;
        }
    }

    template <typename TValue>
    std::vector<TValue> ReadValues(size_t count, std::istream& inputStream = std::cin)
    {
        std::vector<TValue> values(count);
        for (size_t idx = 0; idx < count; ++idx)
        {
            values[idx] = ReadValue<TValue>(inputStream);
        }
        return values;
    }
} // namespace IO

#endif
