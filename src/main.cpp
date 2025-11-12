#include "lexer.h"
#include "token.h"
#include "libraries.h"

int main(int argc, char** argv)
{
    Lexer::loadKeyWords("../config/keywords.json");

    std::ifstream input("../examples/Hello.arcx");
    std::stringstream buffer;
    buffer << input.rdbuf();
    Lexer lexer(buffer.str());
    while (true)
    {
        Token t = lexer.nextToken();
        if (t.type == TokenType::Eof) break;
        std::cout << "token: ";
        switch (t.type)
        {
            // Keywords
            case TokenType::Display: std::cout << "DISPLAY"; break;
            case TokenType::Group: std::cout << "GROUP"; break;
            case TokenType::Return: std::cout << "RETURN"; break;
            case TokenType::Break: std::cout << "BREAK"; break;
            case TokenType::If: std::cout << "IF"; break;
            case TokenType::While: std::cout << "WHILE"; break;

            // Types
            case TokenType::Int: std::cout << "TYPE_INTEGER"; break;
            case TokenType::Str: std::cout << "TYPE_STRING"; break;
            case TokenType::Bool: std::cout << "TYPE_BOOLEAN"; break;
            case TokenType::Arr: std::cout << "TYPE_ARRAY"; break;
            case TokenType::Float: std::cout << "TYPE_FLOAT"; break;

            // Punctuation
            case TokenType::Semicolon: std::cout << "SEMICOLON"; break;
            case TokenType::Colon: std::cout << "COLON"; break;
            case TokenType::CurlyOpen: std::cout << "OPEN_CURLY"; break;
            case TokenType::CurlyClose: std::cout << "CLOSE_CURLY"; break;
            case TokenType::Open: std::cout << "OPEN"; break;
            case TokenType::Close: std::cout << "CLOSE"; break;
            case TokenType::SquareOpen: std::cout << "OPEN_SQUARE"; break;
            case TokenType::SquareClose: std::cout << "CLOSE_SQUARE"; break;

            // Operators
            case TokenType::Plus: std::cout << "PLUS"; break;
            case TokenType::Minus: std::cout << "MINUS"; break;
            case TokenType::Multiply: std::cout << "MULTIPLY"; break;
            case TokenType::Divide: std::cout << "DIVIDE"; break;
            case TokenType::Set: std::cout << "SET"; break;
            case TokenType::PlusPlus: std::cout << "INCREMENT"; break;
            case TokenType::MinusMinus: std::cout << "DECREMENT"; break;
            case TokenType::Equals: std::cout << "EQUALS"; break;
            case TokenType::PlusEquals: std::cout << "PLUS_EQUALS"; break;
            case TokenType::MinusEquals: std::cout << "MINUS_EQUALS"; break;

            case TokenType::String: std::cout << "STRING"; break;
            case TokenType::True: std::cout << "TRUE"; break;
            case TokenType::False: std::cout << "FALSE"; break;
            case TokenType::Number: std::cout << "NUMBER"; break;

            case TokenType::Identifier: std::cout << "IDENTIFIER"; break;
            default: std::cout << "UNKNOWN"; break;
        }
        std::cout << " (" << t.value << ")\n";
    }
    return 0;
}
