#include "io_tools.h"
#include "common_substring_search.h"

void Run()
{
    std::ostream& out = std::cout;
    std::istream& in = std::cin;
    out << "Given a list of strings we compute their longest common substring.\n";
    out << "Enter strings count: ";
    size_t stringsCount = 0;
    in >> stringsCount;
    std::vector<std::string> strings;
    for (size_t index = 0; index < stringsCount; ++index)
    {
        std::string string;
        out << "Enter string #" << index + 1 << ": ";
        in >> string;
        strings.push_back(string);
    }

    auto results = GetCommonSubstringPositions(strings);
    auto commonLength = results.first;
    for (size_t index = 0; index < stringsCount; ++index)
    {
        const auto& string = strings[index];
        const auto position = results.second[index];
        out << string << '\n';
        out << std::string(position, ' ') << std::string(commonLength, '~') << '\n';
        out << std::string(position, ' ');
        for (size_t shift = 0; shift < commonLength; ++shift)
        {
            out << string[position + shift];
        }
        out << "\n\n";
    }
}

int main(int argc, char** argv)
{
    Run();
    return 0;
}

