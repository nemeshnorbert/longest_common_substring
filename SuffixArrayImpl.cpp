#include "stdafx.h"

#include <vector>
#include "SuffixArrayImpl.h"

namespace StringProcessing
{
    namespace Internal
    {
        bool ComparePair(size_t lhsFirst, size_t lhsSecond,
            size_t rhsFirst, size_t rhsSecond)
        {
            return  lhsFirst < rhsFirst ||
                lhsFirst == rhsFirst &&
                lhsSecond <= rhsSecond;
        }

        bool CompareTriple(size_t lhsFirst, size_t lhsSecond, size_t lhsThird,
            size_t rhsFirst, size_t rhsSecond, size_t rhsThird)
        {
            return  lhsFirst < rhsFirst ||
                lhsFirst == rhsFirst &&
                ComparePair(lhsSecond, lhsThird, rhsSecond, rhsThird);
        }

        void RadixPass(const size_t* source, size_t* target, const size_t* ranks,
            size_t length, size_t alphabetSize)
        {
            // count occurrences
            std::vector<size_t> counter(alphabetSize + 1, 0);

            for (size_t idx = 0; idx < length; ++idx)
            {
                // count occurrences
                counter[ranks[source[idx]]]++;
            }
            for (size_t idx = 0, sum = 0; idx <= alphabetSize; ++idx)
            {
                // exclusive prefix sums
                size_t count = counter[idx];
                counter[idx] = sum;
                sum += count;
            }

            for (size_t idx = 0; idx < length; ++idx)
            {
                // sort
                target[counter[ranks[source[idx]]]++] = source[idx];
            }
        }

        void BuildSuffixArray(const size_t* text, size_t* suffixArray,
            size_t textLength, size_t alphabetSize)
        {
            size_t lengthZero = (textLength + 2) / 3;
            size_t lengthOne = (textLength + 1) / 3;
            size_t lengthTwo = textLength / 3;
            size_t lengthZeroTwo = lengthZero + lengthTwo;

            std::vector<size_t> textOneTwo(lengthZeroTwo + 3);
            textOneTwo[lengthZeroTwo] = 0;
            textOneTwo[lengthZeroTwo + 1] = 0;
            textOneTwo[lengthZeroTwo + 2] = 0;

            std::vector<size_t> suffixArrayOneTwo(lengthZeroTwo + 3);
            suffixArrayOneTwo[lengthZeroTwo] = 0;
            suffixArrayOneTwo[lengthZeroTwo + 1] = 0;
            suffixArrayOneTwo[lengthZeroTwo + 2] = 0;

            std::vector<size_t> textZero(lengthZero);
            std::vector<size_t> suffixArrayZero(lengthZero);

            // generate positions of mod 1 and mod  2 suffixes
            // the "+(lengthZero - lengthOne)" adds a dummy 
            // mod 1 suffix if textLength % 3 == 1
            for (size_t idx = 0, textOneTwoIdx = 0;
                idx < textLength + (lengthZero - lengthOne);
                ++idx)
            {
                if (idx % 3 != 0)
                {
                    textOneTwo[textOneTwoIdx++] = idx;
                }
            }

            // lsb radix sort the mod 1 and mod 2 triples
            RadixPass(textOneTwo.data(), suffixArrayOneTwo.data(),
                text + 2, lengthZeroTwo, alphabetSize);
            RadixPass(suffixArrayOneTwo.data(), textOneTwo.data(),
                text + 1, lengthZeroTwo, alphabetSize);
            RadixPass(textOneTwo.data(), suffixArrayOneTwo.data(),
                text, lengthZeroTwo, alphabetSize);

            // find lexicographic names of triples
            size_t name = 0, classZero = -1, classOne = -1, classTwo = -1;
            for (size_t idx = 0; idx < lengthZeroTwo; ++idx)
            {
                if (text[suffixArrayOneTwo[idx]] != classZero ||
                    text[suffixArrayOneTwo[idx] + 1] != classOne ||
                    text[suffixArrayOneTwo[idx] + 2] != classTwo)
                {
                    name++;
                    classZero = text[suffixArrayOneTwo[idx]];
                    classOne = text[suffixArrayOneTwo[idx] + 1];
                    classTwo = text[suffixArrayOneTwo[idx] + 2];
                }
                if (suffixArrayOneTwo[idx] % 3 == 1)
                {
                    textOneTwo[suffixArrayOneTwo[idx] / 3] = name;
                } // left half
                else
                {
                    textOneTwo[suffixArrayOneTwo[idx] / 3 + lengthZero] = name;
                } // right half
            }

            // recurse if names are not yet unique
            if (name < lengthZeroTwo)
            {
                BuildSuffixArray(textOneTwo.data(), suffixArrayOneTwo.data(),
                    lengthZeroTwo, name);
                // store unique names in textOneTwo using the suffix array 
                for (size_t idx = 0; idx < lengthZeroTwo; ++idx)
                {
                    textOneTwo[suffixArrayOneTwo[idx]] = idx + 1;
                }
            }
            else
            {
                // generate the suffix array of textOneTwo directly
                for (size_t idx = 0; idx < lengthZeroTwo; ++idx)
                {
                    suffixArrayOneTwo[textOneTwo[idx] - 1] = idx;
                }
            }

            // stably sort the mod 0 suffixes from 
            // suffixArrayOneTwo by their first character
            for (size_t idx = 0, textOneTwoIdx = 0; idx < lengthZeroTwo; ++idx)
            {
                if (suffixArrayOneTwo[idx] < lengthZero)
                {
                    textZero[textOneTwoIdx++] = 3 * suffixArrayOneTwo[idx];
                }
            }
            RadixPass(textZero.data(), suffixArrayZero.data(),
                text, lengthZero, alphabetSize);

            // merge sorted suffixArrayZero suffixes 
            // and sorted suffixArrayOneTwo suffixes
            for (size_t position = 0, oneTwoIdx = lengthZero - lengthOne, idx = 0;
                idx < textLength;
                ++idx)
            {
                // position of current offset 12 suffix
                size_t offsetPosOneTwo =
                    suffixArrayOneTwo[oneTwoIdx] < lengthZero ?
                    suffixArrayOneTwo[oneTwoIdx] * 3 + 1 :
                    (suffixArrayOneTwo[oneTwoIdx] - lengthZero) * 3 + 2;

                // position of current offset 0 suffix
                size_t offsetPosZero = suffixArrayZero[position];
                if (suffixArrayOneTwo[oneTwoIdx] < lengthZero ?
                    ComparePair(text[offsetPosOneTwo],
                    textOneTwo[suffixArrayOneTwo[oneTwoIdx] + lengthZero],
                    text[offsetPosZero],
                    textOneTwo[offsetPosZero / 3]) :
                    CompareTriple(text[offsetPosOneTwo],
                    text[offsetPosOneTwo + 1],
                    textOneTwo[suffixArrayOneTwo[oneTwoIdx] - lengthZero + 1],
                    text[offsetPosZero],
                    text[offsetPosZero + 1],
                    textOneTwo[offsetPosZero / 3 + lengthZero]))
                {
                    // suffix from suffixArrayOneTwo is smaller
                    suffixArray[idx] = offsetPosOneTwo;
                    oneTwoIdx++;
                    if (oneTwoIdx == lengthZeroTwo)
                    {
                        // done, only suffixArrayZero suffixes left
                        for (++idx; position < lengthZero; ++position, ++idx)
                        {
                            suffixArray[idx] = suffixArrayZero[position];
                        }
                    }
                }
                else
                {
                    suffixArray[idx] = offsetPosZero;
                    position++;
                    if (position == lengthZero)
                    {
                        // done, only suffixArrayOneTwo suffixes left
                        for (idx++;
                            oneTwoIdx < lengthZeroTwo;
                            oneTwoIdx++, idx++)
                        {
                            suffixArray[idx] =
                                suffixArrayOneTwo[oneTwoIdx] < lengthZero ?
                                suffixArrayOneTwo[oneTwoIdx] * 3 + 1 :
                                (suffixArrayOneTwo[oneTwoIdx] - lengthZero) * 3 + 2;
                        }
                    }
                }
            }
        }
    }
};