#include "stdafx.h"

#include "IOTools.h"
#include "CommonSubstringSearch.h"

#include "Tests.h"

bool Test(const std::vector<std::string>& strings, const std::string& answer)
{
    auto commonSustring = GetCommonSubstring(strings);
    std::ostream& stream = std::cout;
    if (commonSustring != answer)
    {

        stream << "Wrong answer\nfor strings: ";
        IO::WriteValues(strings, stream);
        stream << "\nThe correct answer is: ";
        IO::WriteValue(answer, stream);
        return false;
    }
    else
    {
        stream << "Test passed!\n";
    }
    return true;
}

void Run(std::istream inputStream, std::ostream& outputStream)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto stringsCount = IO::ReadValue<size_t>(inputStream);
    auto stringsLength = IO::ReadValue<size_t>(inputStream);
    auto strings = IO::ReadValues<std::string>(stringsCount, inputStream);

    auto results = GetCommonSubstringPositions(strings);
    IO::WriteValue(results.first, outputStream, "\n");
    for (const auto& shift : results.second)
    {
        IO::WriteValue(shift + 1, outputStream, "\n");
    }
}
