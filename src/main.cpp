#include "io_tools.h"
#include "common_substring_search.h"

void Run(std::istream& inputStream, std::ostream& outputStream)
{
    auto stringsCount = ReadValue<size_t>(inputStream);
    auto strings = ReadValues<std::string>(stringsCount, inputStream);

    auto results = GetCommonSubstringPositions(strings);
    WriteValue(results.first, outputStream, "\n");
    for (const auto& shift : results.second)
    {
        WriteValue(shift + 1, outputStream, "\n");
    }
}

int main(int argc, char** argv)
{
    Run(std::cin, std::cout);
    return 0;
}

