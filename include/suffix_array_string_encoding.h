#ifndef LONGEST_COMMON_SUBSTRING_SUFFIX_ARRAY_STRING_ENCODING_H_
#define LONGEST_COMMON_SUBSTRING_SUFFIX_ARRAY_STRING_ENCODING_H_

#include <map>
#include <vector>
#include <string>

namespace StringProcessing
{
    template <typename TChar>
    struct EncodingReport
    {
        std::vector<size_t> encodedText;
        std::map<TChar, size_t> symbolToCode;
    };

    // Encodes text for computation of suffix array
    template <typename TChar>
    EncodingReport<TChar> EncodeToIntegers(const std::basic_string<TChar>& text)
    {
        EncodingReport<TChar> report;
        for (const auto& symbol : text)
        {
            if (report.symbolToCode.find(symbol) == report.symbolToCode.end())
            {
                report.symbolToCode.insert({ symbol, 0 });
            }
        }
        size_t code = 1;
        for (auto& symbolCodePair : report.symbolToCode)
        {
            symbolCodePair.second = code++;
        }
        report.encodedText.resize(text.size() + 3);
        for (size_t symbolId = 0; symbolId < text.size(); ++symbolId)
        {
            report.encodedText[symbolId] = report.symbolToCode[text[symbolId]];
        }
        return std::move(report);
    }
}

#endif
