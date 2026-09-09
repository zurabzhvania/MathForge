#include <calculus/SymbolicDifferentiation.h>

#include <regex>
#include <string>
#include <vector>
#include <sstream>

namespace
{
    std::vector<std::string> splitTerms(
        const std::string& expression
    )
    {
        std::vector<std::string> terms;

        std::string current;

        for (size_t i = 0; i < expression.size(); i++)
        {
            char c = expression[i];

            if ((c == '+' || c == '-') &&
                i != 0)
            {
                terms.push_back(current);
                current.clear();
            }

            current += c;
        }

        if (!current.empty())
        {
            terms.push_back(current);
        }

        return terms;
    }
}

std::string SymbolicDifferentiation::differentiate(
    const std::string& expression
)
{
    std::vector<std::string> terms =
        splitTerms(expression);

    std::string result;

    for (const auto& term : terms)
    {
        std::smatch match;

        std::regex powerPattern(
            R"(([+-]?\d*\.?\d*)\*?x\^(\d+))"
        );

        std::regex linearPattern(
            R"(([+-]?\d*\.?\d*)\*?x)"
        );

        std::regex constantPattern(
            R"(([+-]?\d+\.?\d*))"
        );

        if (std::regex_match(
                term,
                match,
                powerPattern))
        {
            std::string coefficientText =
                match[1];

            double coefficient = 1.0;

            if (coefficientText == "-")
            {
                coefficient = -1.0;
            }
            else if (!coefficientText.empty() &&
                     coefficientText != "+")
            {
                coefficient =
                    std::stod(coefficientText);
            }

            int power =
                std::stoi(match[2]);

            if (power == 0)
            {
                result += "0 + ";
                continue;
            }

            double newCoefficient =
                coefficient * power;

            int newPower =
                power - 1;

            if (newPower == 1)
            {
                result +=
                    std::to_string(newCoefficient)
                    + "*x + ";
            }
            else if (newPower == 0)
            {
                result +=
                    std::to_string(newCoefficient)
                    + " + ";
            }
            else
            {
                result +=
                    std::to_string(newCoefficient)
                    + "*x^"
                    + std::to_string(newPower)
                    + " + ";
            }
        }
        else if (std::regex_match(
                    term,
                    match,
                    linearPattern))
        {
            std::string coefficientText =
                match[1];

            double coefficient = 1.0;

            if (coefficientText == "-")
            {
                coefficient = -1.0;
            }
            else if (!coefficientText.empty() &&
                     coefficientText != "+")
            {
                coefficient =
                    std::stod(coefficientText);
            }

            result +=
                std::to_string(coefficient)
                + " + ";
        }
        else if (std::regex_match(
                    term,
                    match,
                    constantPattern))
        {
            result += "0 + ";
        }
        else
        {
            return
                "Symbolic differentiation not supported yet.";
        }
    }

    if (result.size() >= 3)
    {
        result.erase(result.size() - 3);
    }

    return result;
}
