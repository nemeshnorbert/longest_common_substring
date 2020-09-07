#include <cassert>
#include <random>
#include "io_tools.h"
#include "common_substring_search.h"


std::string GetRandomString(int minLength, int maxLength)
{
    assert(minLength <= maxLength);
    static std::mt19937_64 engine;
    std::uniform_int_distribution<size_t> lengthGenerator(minLength, maxLength);
    std::uniform_int_distribution<int> charGenerator(0, 25);
    size_t length = lengthGenerator(engine);
    std::string string(length, 0);
    for (size_t index = 0; index < length; ++index)
    {
        string[index] = static_cast<char>(static_cast<int>('a') + charGenerator(engine));
    }
    return string;
}

std::vector<std::string> GetRandomStrings(size_t minLength, size_t maxLength, size_t count)
{
    std::vector<std::string> strings;
    for (size_t index = 0; index < count; ++index)
    {
        strings.push_back(GetRandomString(minLength, maxLength));
    }
    return strings;
}


bool RunTest(std::ostream& out, const std::vector<std::string>& strings)
{
    try
    {
        auto commonSubstring = GetCommonSubstring(strings);
    }
    catch (const std::exception& exc)
    {
        out << "Test failed. Reason: " << exc.what() << '\n';
        out << "Strings: \n";
        for (const auto& string : strings)
        {
            out << string << '\n';
        }
        return false;
    }
    out << "Test passed\n";
    return true;
}

int main() {
    for (int attempt = 0; attempt < 10; ++attempt)
    {
        if(!RunTest(std::cout, GetRandomStrings(0, 20, 4)))
        {
            return 1;
        }
    }
    return 0;
}

