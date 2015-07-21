#include "stdafx.h"

#include <functional>
#include <algorithm>

#include "StringSearch.h"
#include "SuffixLcpArray.h"
#include "PriorityQueue.h"
#include "CommonSubstringSearch.h"

size_t GetTotalStringsLength(const std::vector<std::string>& strings)
{
    size_t totalLength = 0;
    for (const auto& string : strings)
    {
        totalLength += string.size();
    }
    return totalLength;
}

std::vector<size_t> GetPrefixTypes(const std::vector<std::string>& strings)
{
    std::vector<size_t> prefixTypes;
    prefixTypes.reserve(GetTotalStringsLength(strings) + strings.size());
    size_t type = 0;
    for (const auto& string : strings)
    {
        for (const auto& symbol : string)
        {
            prefixTypes.push_back(type);
        }
        prefixTypes.push_back(std::numeric_limits<size_t>::max());
        ++type;
    }
    return std::move(prefixTypes);
}

size_t GetMaximalGoodSegmentStart(const std::vector<size_t>& suffixArray,
    const std::vector<size_t>& prefixTypes,
    size_t stringsCount)
{
    size_t typesCount = 0;
    std::vector<size_t> typeCounters(stringsCount, 0);
    size_t idx = suffixArray.size() - 1;

    for (; idx >= 0; --idx)
    {
        size_t type = prefixTypes[suffixArray[idx]];
        if (typeCounters[type] == 0)
        {
            ++typesCount;
            if (typesCount == stringsCount)
            {
                break;
            }
        }
        ++typeCounters[type];
    }
    return idx;
}

SubstringInfo ScanSuffixArray(const std::vector<size_t>& suffixArray,
    const std::vector<size_t>& lcpArray,
    const std::vector<size_t>& prefixTypes,
    size_t stringsCount)
{
    size_t textLength = suffixArray.size();
    std::vector<size_t> typeCounters(stringsCount, 0);
    PriorityQueue<size_t, std::greater<size_t>> queue_;

    size_t typesCount = 0;
    size_t maximalSegmentStart =
        GetMaximalGoodSegmentStart(suffixArray, prefixTypes, stringsCount);

    SubstringInfo bestSubstring;

    for (size_t segmentStart = stringsCount, segmentEnd = stringsCount;
        segmentStart <= maximalSegmentStart; ++segmentStart)
    {
        while (segmentEnd < suffixArray.size() && typesCount < stringsCount)
        {
            ++segmentEnd;
            if (segmentEnd - segmentStart >= 2)
            {
                queue_.Push(lcpArray[segmentEnd - 2]);
            }
            size_t endType = prefixTypes[suffixArray[segmentEnd - 1]];
            if (typeCounters[endType] == 0)
            {
                ++typesCount;
            }
            ++typeCounters[endType];
        }
        auto commonSubstringLength = !queue_.Empty() ? queue_.PriorityValue() : 0;
        if (commonSubstringLength > bestSubstring.length)
        {
            bestSubstring.start = segmentStart;
            bestSubstring.length = commonSubstringLength;
        }
        auto startType = prefixTypes[suffixArray[segmentStart]];
        if (!queue_.Empty())
        {
            queue_.Pop();
        }
        if (typeCounters[startType] == 1)
        {
            --typesCount;
        }
        --typeCounters[startType];
    }
    return bestSubstring;
}

std::string GetCommonSubstring(const std::vector<std::string>& strings)
{
    if (strings.size() < 2)
    {
        return strings.size() < 1 ? std::string() : strings[0];
    }

    std::vector<size_t> encodedText;
    encodedText.reserve(GetTotalStringsLength(strings) + strings.size() + 3);
    for (size_t stringId = 0, symbolId = 0; stringId < strings.size(); ++stringId)
    {
        for (const auto& symbol : strings[stringId])
        {
            encodedText.push_back(static_cast<size_t>(symbol)+strings.size() + 1);
        }
        encodedText.push_back(stringId + 1);
    }
    encodedText.push_back(0);
    encodedText.push_back(0);
    encodedText.push_back(0);

    auto suffixArray = StringProcessing::BuildSuffixArray(encodedText,
        *std::max_element(encodedText.begin(), encodedText.end()));
    auto lcpArray = StringProcessing::BuildLcpArray(suffixArray,
        StringProcessing::BuildRankArray(suffixArray),
        encodedText);
    auto prefixTypes = GetPrefixTypes(strings);

    SubstringInfo substringInfo = ScanSuffixArray(suffixArray, lcpArray,
        prefixTypes, strings.size());

    std::string commonSubstring(substringInfo.length, 0);
    for (size_t shift = 0; shift < substringInfo.length; ++shift)
    {
        commonSubstring[shift] = static_cast<char>(
            encodedText[suffixArray[substringInfo.start] + shift] - strings.size() - 1);
    }
    return commonSubstring;
}

std::pair<size_t, std::vector<int>> GetCommonSubstringPositions(
    const std::vector<std::string>& strings)
{
    auto commonSubstring = GetCommonSubstring(strings);

    std::vector<int> positions;
    for (const auto& string : strings)
    {
        positions.push_back(StringProcessing::TryGetFirstOccurrence(string, 
            commonSubstring));
    }

    return std::make_pair(commonSubstring.size(), positions);
}