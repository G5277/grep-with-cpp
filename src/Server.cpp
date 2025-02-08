#include <iostream>
#include <string>
#include <regex>

// Literal
bool match_literal(const std::string &input_line, const std::string &pattern)
{
    return input_line.find(pattern) != std::string::npos;
}

// Digit
bool match_digit(const std::string &input_line)
{
    return std::regex_search(input_line, std::regex("\\d"));
}

// Alphanumeric
bool match_alphanumeric(const std::string &input_line)
{
    return std::regex_search(input_line, std::regex("\\w"));
}

// POS CHAR GRP
bool match_pos_char_grp(const std::string &input_line, const std::string &pattern)
{
    return input_line.find_first_of(pattern) != std::string::npos;
}

// NEG CHAR GRP
bool match_neg_char_grp(const std::string &input_line, const std::string &pattern)
{
    return input_line.find_first_not_of(pattern) != std::string::npos;
}

// COMBINATIONS
bool match_combinations(const std::string &input_line, const std::string &pattern)
{
    if (pattern.empty())
        return input_line.empty();

    if (input_line.empty())
        return false;

    if (input_line.substr(0, 1) == " ")
    {
        if (pattern.substr(0, 1) == " ")
        {
            return match_combinations(input_line.substr(1), pattern.substr(1));
        }
        else
        {
            return false;
        }
    }


    if (pattern.substr(0, 2) == "\\d")
    {
        bool check = match_digit(input_line.substr(0, 1));
        if (check == false)
        {
            return false;
        }
        else
        {
            return match_combinations(input_line.substr(1), pattern.substr(2));
        }
    }
    else if (pattern.substr(0, 2) == "\\w")
    {
        bool check = match_alphanumeric(input_line.substr(0, 1));
        if (check == false)
        {
            return false;
        }
        else
        {
            return match_combinations(input_line.substr(1), pattern.substr(2));
        }
    }
    else
    {
        bool check = match_literal(input_line.substr(0, 1), pattern.substr(0, 1));
        if (check == false)
        {
            return false;
        }
        else
        {
            return match_combinations(input_line.substr(1), pattern.substr(1));
        }
    }
    return true;
}

// COMPLETE
bool match_pattern(const std::string &input_line, const std::string &pattern)
{
    if (pattern.length() == 1)
    {
        return match_literal(input_line, pattern);
    }
    else if (pattern == "\\d")
    {
        return match_digit(input_line);
    }
    else if (pattern == "\\w")
    {
        return match_alphanumeric(input_line);
    }
    else if (pattern[0] == '[' && pattern[pattern.length() - 1] == ']')
    {
        if (pattern[1] == '^')
        {
            return match_neg_char_grp(input_line, pattern.substr(1, pattern.length() - 2));
        }
        return match_pos_char_grp(input_line, pattern.substr(1, pattern.length() - 2));
    }
    else if (pattern[0] == '(' && pattern[pattern.length() - 1] == ')')
    {
        return match_combinations(input_line, pattern.substr(1, pattern.length() - 1));
    }
    else
    {
        throw std::runtime_error("Unhandled pattern " + pattern);
    }
}

int main(int argc, char **argv)
{
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc != 3)
    {
        std::cout << "Expected two arguments!" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    std::string input_line;
    std::getline(std::cin, input_line);

    if (flag != "-E")
    {
        std::cerr << "Invalid flag! Use -E for regex matching." << std::endl;
        return 1;
    }

    try
    {
        if (match_pattern(input_line, pattern))
        {
            std::cout << "Match Found";
            return 0;
        }
        else
        {
            std::cout << "No Match Found";
            return 1;
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}