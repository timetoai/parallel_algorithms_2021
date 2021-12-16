#include <iostream>

bool isDelimiter(char c)
{
    return c == '\n' | c == ' ' | c == '\t';
}

int countWords(char* chars)
{
    int ret = 0; // number of non-empty words
    int cur = 0; // number of characters in current word

    for (int i=0; chars[i] != '\0'; i++)
    {
        if (isDelimiter(chars[i]))
        {
            if (cur > 0)
                ret += 1;
            cur = 0;
        }
        else
        {
            cur += 1;
        }
    }
    if (cur > 0)
        ret += 1;

    return ret;
}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::cout << countWords(argv[1]) << std::endl;
    }
    else
    {
        return - 1;
    }
}