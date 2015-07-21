#ifndef LONGEST_COMMON_SUBSTRING_OF_SEVERAL_STRINGS_SUFFIX_LCP_ARRAY_H_
#define LONGEST_COMMON_SUBSTRING_OF_SEVERAL_STRINGS_SUFFIX_LCP_ARRAY_H_

#include "SuffixArrayImpl.h"
#include "SuffixArrayStringEncoding.h"

namespace StringProcessing
{
    // Three padding 0 elements required in the end of encodedText. The remaining elements
    // of encodedText are from {1, ..., alphabetSize}
    std::vector<size_t> BuildSuffixArray(const std::vector<size_t>& encodedText,
        size_t alphabetSize);

    // Three padding 0 elements required in the end of encodedText. The remaining elements
    // of encodedText are from {1, ..., alphabetSize}
    template <typename TChar>
    std::vector<size_t> BuildSuffixArray(const std::basic_string<TChar>& text)
    {
        auto report = EncodeToIntegers(text);
        return BuildSuffixArray(report.encodedText, report.symbolToCode.size());
    }

    std::vector<size_t> BuildRankArray(const std::vector<size_t>& suffixArray);

    template <typename TSequence>
    std::vector<size_t> BuildLcpArray(const std::vector<size_t>& suffixArray,
        const std::vector<size_t>& ranksArray,
        const TSequence& text)
    {
        if (suffixArray.size() <= 1)
        {
            return std::vector<size_t>();
        }

        std::vector<size_t> lcpArray_(suffixArray.size() - 1);
        auto length = suffixArray.size();
        for (size_t idx = 0, hop = 0; idx < length; ++idx)
        {
            if (ranksArray[idx] < length - 1)
            {
                for (size_t j = suffixArray[ranksArray[idx] + 1];
                    std::max(idx, j) + hop < length && text[idx + hop] == text[j + hop];)
                {
                    ++hop;
                }
                lcpArray_[ranksArray[idx]] = hop;
                if (hop > 0)
                {
                    --hop;
                }
            }
        }
        return std::move(lcpArray_);
    }
}

#endif