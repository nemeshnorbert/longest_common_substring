#ifndef LONGEST_COMMON_SUBSTRING_COMMON_SUBSTRING_SEARCH_H_
#define LONGEST_COMMON_SUBSTRING_COMMON_SUBSTRING_SEARCH_H_

#include <vector>

struct SubstringInfo
{
    size_t start = 0;
    size_t length = 0;
};

size_t GetTotalStringsLength(const std::vector<std::string>& strings);

std::vector<size_t> GetPrefixTypes(const std::vector<std::string>& strings);

size_t GetMaximalGoodSegmentStart(const std::vector<size_t>& suffixArray,
    const std::vector<size_t>& prefixTypes,
    size_t stringsCount);

SubstringInfo ScanSuffixArray(const std::vector<size_t>& suffixArray,
    const std::vector<size_t>& lcpArray,
    const std::vector<size_t>& prefixTypes,
    size_t stringsCount);

std::string GetCommonSubstring(const std::vector<std::string>& strings);

std::pair<size_t, std::vector<int>> GetCommonSubstringPositions(
    const std::vector<std::string>& strings);

#endif
