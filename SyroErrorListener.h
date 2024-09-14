#pragma once

#include "antlr4-runtime.h"
#include <iostream>

class SyroErrorListener : public antlr4::BaseErrorListener
{
public:
    bool hasErrors = false;

    virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol,
                             size_t line, size_t charPositionInLine, const std::string &msg,
                             std::exception_ptr e) override
    {
        hasErrors = true;
        std::cerr << "Error at line " << line << ":" << charPositionInLine << " - " << offendingSymbol->getText() << std::endl;
    }
};
