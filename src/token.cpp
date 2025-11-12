#include "token.h"
#include "libraries.h"

TokenType tokenTypeFromString(const std::string &name)
{
    static std::unordered_map<std::string, TokenType> map =
            {
                    // Keywords
                    {"Display", TokenType::Display},
                    {"Group", TokenType::Group},
                    {"Return", TokenType::Return},
                    {"Break", TokenType::Break},
                    {"If", TokenType::If},
                    {"While", TokenType::While},

                    // Types
                    {"Int", TokenType::Int},
                    {"Str", TokenType::Str},
                    {"Bool", TokenType::Bool},
                    {"Arr", TokenType::Arr},
                    {"Float", TokenType::Float},

                    // Punctuation
                    {"Semicolon", TokenType::Semicolon},
                    {"Colon", TokenType::Colon},
                    {"CurlyOpen", TokenType::CurlyOpen},
                    {"CurlyClose", TokenType::CurlyClose},
                    {"Open", TokenType::Open},
                    {"Close", TokenType::Close},
                    {"SquareOpen", TokenType::SquareOpen},
                    {"SquareClose", TokenType::SquareClose},

                    // Operators (fixed to use token *names*, not symbols)
                    {"True", TokenType::True},
                    {"False", TokenType::False},
                    {"Plus", TokenType::Plus},
                    {"Minus", TokenType::Minus},
                    {"Multiply", TokenType::Multiply},
                    {"Divide", TokenType::Divide},
                    {"Set", TokenType::Set},
                    {"PlusPlus", TokenType::PlusPlus},
                    {"MinusMinus", TokenType::MinusMinus},
                    {"Equals", TokenType::Equals},
                    {"PlusEquals", TokenType::PlusEquals},
                    {"MinusEquals", TokenType::MinusEquals},
            };

    auto it = map.find(name);
    if (it != map.end())
        return it->second;
    return TokenType::Unknown;
}
