#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <string>
#include <stdexcept>

class ExpressionParser
{
public:
    static double evaluate(
        const std::string& expression,
        double x
    );

private:
    static void expect(char expected);
    static std::string expr;
    static size_t pos;
    static double xValue;

    static double parseExpression();
    static double parseTerm();
    static double parseFactor();
    static double parsePrimary();

    static char currentChar();
    static void skipSpaces();
};

#endif
