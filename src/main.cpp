#include "io_tools.h"
#include "common_substring_search.h"

void Run(std::istream& inputStream, std::ostream& outputStream)
{
    auto stringsCount = IO::ReadValue<size_t>(inputStream);
    auto strings = IO::ReadValues<std::string>(stringsCount, inputStream);

    auto results = GetCommonSubstringPositions(strings);
    IO::WriteValue(results.first, outputStream, "\n");
    for (const auto& shift : results.second)
    {
        IO::WriteValue(shift + 1, outputStream, "\n");
    }
}

int main(int argc, char** argv)
{
    Run(std::cin, std::cout);
    return 0;
}

