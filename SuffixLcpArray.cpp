#include "stdafx.h"

#include <cassert>

#include "SuffixLcpArray.h"
#include "SuffixArrayStringEncoding.h"
#include "SuffixArrayImpl.h"

namespace StringProcessing
{
    // Three padding 0 elements required in the end of encodedText. The remaining elements
    // of encodedText are from {1, ..., alphabetSize}
    std::vector<size_t> BuildSuffixArray(const std::vector<size_t>& encodedText,
        size_t alphabetSize)
    {
        assert(encodedText.size() >= 3);
        std::vector<size_t> suffixArray(encodedText.size(), 0);
        size_t textLength = encodedText.size() - 3;
        if (textLength > 1)
        {
            Internal::BuildSuffixArray(encodedText.data(), suffixArray.data(),
                textLength, alphabetSize);
        }
        suffixArray.resize(encodedText.size() - 3);
        return std::move(suffixArray);
    }

    std::vector<size_t> BuildRankArray(const std::vector<size_t>& suffixArray)
    {
        std::vector<size_t> ranksArray(suffixArray.size(), 0);
        for (size_t idx = 0; idx < suffixArray.size(); ++idx)
        {
            ranksArray[suffixArray[idx]] = idx;
        }
        return std::move(ranksArray);
    }
}