#include <app/ExpressionParser.h>

#include <cctype>
#include <cmath>
#include <string>
#include <stdexcept>

std::string ExpressionParser::expr = "";
size_t ExpressionParser::pos = 0;
double ExpressionParser::xValue = 0;

double ExpressionParser::evaluate(
    const std::string& expression,
    double x
)
{
    expr = expression;
    pos = 0;
    xValue = x;

    double result =
        parseExpression();

    skipSpaces();

    if (currentChar() != '\0')
    {
        throw std::runtime_error(
            "Unexpected character: " +
            std::string(1, currentChar())
        );
    }

    return result;
}

char ExpressionParser::currentChar()
{
    if (pos >= expr.length())
    {
        return '\0';
    }

    return expr[pos];
}

void ExpressionParser::skipSpaces()
{
    while (std::isspace(currentChar()))
    {
        pos++;
    }
}

void ExpressionParser::expect(char expected)
{
    skipSpaces();

    if (currentChar() != expected)
    {
        throw std::runtime_error(
            "Expected character: " +
            std::string(1, expected)
        );
    }

    pos++;
}

double ExpressionParser::parseExpression()
{
    double value =
        parseTerm();

    while (true)
    {
        skipSpaces();

        char op = currentChar();

        if (op != '+' &&
            op != '-')
        {
            break;
        }

        pos++;

        double right =
            parseTerm();

        if (op == '+')
        {
            value += right;
        }
        else
        {
            value -= right;
        }
    }

    return value;
}

double ExpressionParser::parseTerm()
{
    double value =
        parseFactor();

    while (true)
    {
        skipSpaces();

        char op = currentChar();

        if (op != '*' &&
            op != '/')
        {
            break;
        }

        pos++;

        double right =
            parseFactor();

        if (op == '*')
        {
            value *= right;
        }
        else
        {
            value /= right;
        }
    }

    return value;
}

double ExpressionParser::parseFactor()
{
    double value =
        parsePrimary();

    skipSpaces();

    if (currentChar() == '^')
    {
        pos++;

        double exponent =
            parseFactor();

        value =
            std::pow(value, exponent);
    }

    return value;
}

double ExpressionParser::parsePrimary()
{
    skipSpaces();

    if (currentChar() == '(')
    {
        pos++;

        double value =
            parseExpression();

        skipSpaces();

        expect(')');

        return value;
    }

    if (currentChar() == '-')
    {
        pos++;

        return -parsePrimary();
    }

    if (std::isalpha(currentChar()))
    {
        std::string identifier;

        while (std::isalpha(currentChar()))
        {
            identifier += currentChar();
            pos++;
        }

        if (identifier == "x")
        {
            return xValue;
        }
        if (identifier == "pi")
        {
        return M_PI;
        }

        if (identifier == "e")
        {
        return M_E;
        }         

        skipSpaces();

        expect('(');

        double argument =
            parseExpression();

        skipSpaces();

        expect(')');

        if (identifier == "sqrt")
        {
            return std::sqrt(argument);
        }

        if (identifier == "sin")
        {
            return std::sin(argument);
        }

        if (identifier == "cos")
        {
            return std::cos(argument);
        }

        if (identifier == "tan")
        {
            return std::tan(argument);
        }

        if (identifier == "abs")
        {
            return std::abs(argument);
        }

        if (identifier == "exp")
        {
            return std::exp(argument);
        }

        if (identifier == "log")
        {
            return std::log(argument);
        }

        throw std::runtime_error(
            "Unknown function: " + identifier
        );
    }

    std::string number;

    while (std::isdigit(currentChar()) ||
           currentChar() == '.')
    {
        number += currentChar();
        pos++;
    }

    if (number.empty())
    {
        throw std::runtime_error(
            "Invalid expression"
        );
    }

    return std::stod(number);
}
