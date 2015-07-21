#include "stdafx.h"

#include <algorithm>

#include "StringSearch.h"


namespace StringProcessing
{
    std::vector<size_t> BuildPrefixFunction(const std::string& text)
    {
        size_t length = text.length();
        std::vector<size_t> prefixFunc(length);
        for (size_t position = 1; position < length; ++position)
        {
            size_t rollBackPosition = prefixFunc[position - 1];
            while (rollBackPosition > 0 &&
                text[position] != text[rollBackPosition])
            {
                rollBackPosition = prefixFunc[rollBackPosition - 1];
            }
            if (text[position] == text[rollBackPosition])
            {
                ++rollBackPosition;
            }
            prefixFunc[position] = rollBackPosition;
        }
        return std::move(prefixFunc);
    }

    std::vector<size_t> BuildZFunction(const std::string& text)
    {
        size_t length = text.length();
        std::vector<size_t> zFunc(length);
        zFunc[0] = length;
        for (size_t position = 1, left = 0, right = 0;
            position < length;
            ++position)
        {
            if (position <= right)
            {
                zFunc[position] = std::min(right - position + 1,
                    zFunc[position - left]);
            }
            while (position + zFunc[position] < length &&
                text[zFunc[position]] == text[position + zFunc[position]])
            {
                ++zFunc[position];
            }
            if (position + zFunc[position] - 1 > right)
            {
                left = position;
                right = position + zFunc[position] - 1;
            }
        }
        return std::move(zFunc);
    }

    int TryGetFirstOccurrence(const std::string& text, const std::string& pattern)
    {
        std::string compound = pattern + text;
        std::vector<size_t> zFunc = BuildZFunction(compound);
        for (size_t idx = pattern.size(); idx < zFunc.size(); ++idx)
        {
            if (zFunc[idx] >= pattern.size())
            {
                return idx - pattern.size();
            }
        }
        return -1;
    }

    bool IsSubstring(const std::string& text, const std::string& pattern)
    {
        return (TryGetFirstOccurrence(text, pattern) > 0);
    }
}
