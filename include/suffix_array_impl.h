#ifndef LONGEST_COMMON_SUBSTRING_SUFFIX_ARRAY_IMPL_H_
#define LONGEST_COMMON_SUBSTRING_SUFFIX_ARRAY_IMPL_H_

#include <cstddef>

namespace StringProcessing
{
    namespace Internal
    {
        // lexicographical compare for pairs
        bool ComparePair(size_t lhsFirst, size_t lhsSecond,
            size_t rhsFirst, size_t rhsSecond);

        // lexicographical compare for triples
        bool CompareTriple(size_t lhsFirst, size_t lhsSecond, size_t lhsThird,
            size_t rhsFirst, size_t rhsSecond, size_t rhsThird);

        // stably sort source[0..length-1] to target[0..length-1]
        // with keys in 0..alphabetSize from ranks
        void RadixPass(const size_t* source, size_t* target, const size_t* ranks,
            size_t length, size_t alphabetSize);

        // find the suffix array suffixArray of text[0 .. textLength - 1]
        // in alphabet {1..alphabetSize}^textLength. Algorithm requires
        // text and suffixArray be of length textLength + 3 with 3 zeros at the end
        void BuildSuffixArray(const size_t* text, size_t* suffixArray,
            size_t textLength, size_t alphabetSize);

    } // namespace Internal
} // namespace StringProcessing

#endif
