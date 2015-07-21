#ifndef LONGEST_COMMON_SUBSTRING_OF_SEVERAL_STRINGS_STRING_SEARCH_H_
#define LONGEST_COMMON_SUBSTRING_OF_SEVERAL_STRINGS_STRING_SEARCH_H_

#include <vector>
#include <string>

namespace StringProcessing
{
    std::vector<size_t> BuildPrefixFunction(const std::string& text);

    std::vector<size_t> BuildZFunction(const std::string& text);

    int TryGetFirstOccurrence(const std::string& text, const std::string& pattern);

    bool IsSubstring(const std::string& text, const std::string& pattern);
}

#endif