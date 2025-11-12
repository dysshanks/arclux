#ifndef ARCLUX_TOKEN_H
#define ARCLUX_TOKEN_H

#pragma once
#include "libraries.h"

enum class TokenType
{
    // Keywords
    Display,
    Group,
    Return,
    Break,
    If,
    While,

    // Types
    Int,
    Str,
    Bool,
    Arr,
    Float,

    // Punctuation
    True,
    False,
    Semicolon,
    Colon,
    CurlyOpen,
    CurlyClose,
    Open,
    Close,
    SquareOpen,
    SquareClose,

    // Operators
    Plus,
    Minus,
    Multiply,
    Divide,
    Set,
    PlusPlus,
    MinusMinus,
    Equals,
    PlusEquals,
    MinusEquals,

    Number,
    String,
    Identifier,
    Eof,
    Unknown
};


struct Token
{
    TokenType type;
    std::string value;
};

TokenType tokenTypeFromString(const std::string &name);
#endif //ARCLUX_TOKEN_H
