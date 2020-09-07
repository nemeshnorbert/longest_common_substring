#include "io_tools.h"
#include "common_substring_search.h"

bool Test(const std::vector<std::string>& strings, const std::string& answer)
{
    auto commonSustring = GetCommonSubstring(strings);
    std::ostream& stream = std::cout;
    if (commonSustring != answer)
    {

        stream << "Wrong answer\nfor strings: ";
        WriteValues(strings, stream);
        stream << "\nThe correct answer is: ";
        WriteValue(answer, stream);
        return false;
    }
    else
    {
        stream << "Test passed!\n";
    }
    return true;
}

int main(int argc, char** argv)
{
    Test({ "acbc", "bcbc", "ccbcc" }, "cbc");
    return 0;
}


