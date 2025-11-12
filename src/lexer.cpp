#include "lexer.h"

#include <utility>
#include "json.hpp"
#include "libraries.h"

using json = nlohmann::json;
static std::unordered_map<std::string, TokenType> keywords;

static inline std::string trim(const std::string &s)
{
    const char* whitespace = " \t\n\r\f\v";
    size_t start = s.find_first_not_of(whitespace);
    if (start == std::string::npos)
        return "";
    size_t end = s.find_last_not_of(whitespace);
    return s.substr(start, end - start + 1);
}
static std::string hexBytes(const std::string &s)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (unsigned char c : s) {
        oss << std::setw(2) << static_cast<int>(c) << " ";
    }
    return oss.str();
}

void Lexer::loadKeyWords(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "unable to open keyword library file: " << path << "\n";
        return;
    }
    {
        char bom[3] = {0};
        file.read(bom, 3);
        if (!(static_cast<unsigned char>(bom[0]) == 0xEF &&
              static_cast<unsigned char>(bom[1]) == 0xBB &&
              static_cast<unsigned char>(bom[2]) == 0xBF)) {
            file.seekg(0);
        }
    }
    json data;
    try {
        file >> data;
    } catch (const std::exception &e) {
        std::cerr << "Failed to parse JSON keywords: " << e.what() << "\n";
        file.close();
        return;
    }
    for (auto &[type, group] : data.items()) {
        for (auto &[key, value] : group.items()) {
            std::string tokenName = value["token"];
            std::string cleanKey = trim(key);
            keywords[cleanKey] = tokenTypeFromString(tokenName);
        }
    }
    file.close();
}

Lexer::Lexer(std::string src) : source(std::move(src)), pos(0) {}

char Lexer::peek() const
{
    if (pos >= source.size()) return '\0';
    return source[pos];
}

char Lexer::get()
{
    if (pos >= source.size()) return '\0';
    return source[pos++];
}

void Lexer::skipEmpty()
{
    while (std::isspace(static_cast<unsigned char>(peek()))) get();
}

Token Lexer::ReadString()
{
    get();
    std::string value;
    while (peek() != '"' && peek() != '\0')
    {
        value += get();
    }
    if (peek() == '"') get();
    return {TokenType::String, value};
}

Token Lexer::ReadIdentifier()
{
    std::string value;
    while (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '-' || peek() == '_')
    {
        value += get();
    }
    auto it = keywords.find(value);
    if (it != keywords.end())
    {
        return {it->second, value};
    }
    return {TokenType::Identifier, value};
}

Token Lexer::ReadNumber()
{
    std::string value;
    while (std::isdigit(static_cast<unsigned char>(peek())))
        value += get();
    return { TokenType::Number, value };
}

Token Lexer::ReadOperator()
{
    std::string value;
    const std::string allowed = "+-*/=%!<>";
    if (allowed.find(peek()) == std::string::npos)
        return { TokenType::Unknown, std::string(1, peek()) };

    while (allowed.find(peek()) != std::string::npos)
    {
        value += get();
        std::string lookahead = value + peek();
        if (keywords.find(lookahead) != keywords.end())
        {
            continue;
        } else
        {
            break;
        }
    }
    auto it = keywords.find(value);
    if (it != keywords.end())
        return { it->second, value };
    return { TokenType::Unknown, value };
}

Token Lexer::nextToken()
{
    skipEmpty();
    char c = peek();
    if (c == '\0') return { TokenType::Eof, "" };
    if (c == '"') return ReadString();
    if (std::isalpha(static_cast<unsigned char>(c))) return ReadIdentifier();
    if (std::isdigit(static_cast<unsigned char>(c))) return ReadNumber();

    if (std::ispunct(static_cast<unsigned char>(c)))
    {
        Token op = ReadOperator();
        if (op.type != TokenType::Unknown)
            return op;
        std::string symbol(1, get());
        auto it = keywords.find(symbol);
        if (it != keywords.end())
        {
            return { it->second, symbol };
        }

        return { TokenType::Unknown, symbol };
    }
    char consumed = get();
    return { TokenType::Unknown, std::string(1, consumed) };
}
