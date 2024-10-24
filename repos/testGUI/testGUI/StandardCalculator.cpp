#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <cctype>
#include "StandardCalculator.h"
#include <stdexcept>
#include <sstream>
#include <cmath>

using namespace std;

bool isOperator(char c)
{
    return ((c == '*') or (c == '/') or (c == '+') or (c == '-'));
}

bool isIncompleteExpression(const string& input)
{
    if (input.empty()) {
        return false;
    }
    char lastChar = input.back();
    return isOperator(lastChar);
}

double CalculateExpression(const string& input)
{
    if (input.empty()) {
        return 0;
    }

    if (isIncompleteExpression(input)) 
    {
        return numeric_limits<double>::quiet_NaN();
    }
    vector<vector<string>> tokens;

    //Tokenization
    for (size_t i = 0; i < input.size(); i++)
    { 
		char c = input[i];
		if (c == ' ')
		{
			continue;
		}
		else if (isdigit(c) or (c == '-' and (i == 0 or input[i - 1] == '('))) // check if the number is negative
		{
			int counter = 0;
			int dot_counter = 0;
			string number = string(1, c);

			for (size_t j = i + 1; j < input.size(); j++) //Checking for multi-digit numbers
			{
				if (isdigit(input[j]))
				{
					number += input[j];
					counter++;
				}
				else if (input[j] == '.') // check for floating point
				{
					if (dot_counter == 0)
					{
						number += input[j];
						dot_counter++;
						counter++;
					}
					else
					{
                        return numeric_limits<double>::quiet_NaN(); // error if multiple dots are found
						break;
					}
				}
				else
				{
					dot_counter = 0;
					break;

				}
			}
			i += counter;
			tokens.push_back({ number, "number" }); // Add number to tokens

		}
		else if (isOperator(c))
		{
            if (!tokens.empty() && tokens.back()[1] == "operator")
            {
                return numeric_limits<double>::quiet_NaN();
            }
			tokens.push_back({ string(1, c), "operator" }); // Add operator to tokens
		}
		else if (c == '(' or c == ')')
		{
			tokens.push_back({ string(1, c), "parenthesis" }); // Add parenthesis to tokens
		}
        else
        {
            return numeric_limits<double>::quiet_NaN();
        }
    }

    //Operator precedences
    struct Operator {
        int precedence;
    };

    unordered_map<char, Operator> operatorPrecedence = {
        {'+', {1}},
        {'-', {1}},
        {'*', {2}},
		{'/', {2}}
    };

    queue<vector<string>> RPN;
    stack<string> operators;

    //The Shunting Algorithm
    for (size_t i = 0; i < tokens.size(); i++)
    {
        if (tokens[i][1] == "number")
        {
			RPN.push(tokens[i]); // Add number to RPN queue
        }
        else if (tokens[i][1] == "operator")
        {
            if (operators.empty())
            {
                operators.push(tokens[i][0]);
            }
            else 
            {
				while (!operators.empty() && operatorPrecedence[operators.top()[0]].precedence >= operatorPrecedence[tokens[i][0][0]].precedence) // Double checking that the operator is not empty and comparing precedences
                {
                    RPN.push({ operators.top(), "operator" });
                    operators.pop();
                }
                operators.push(tokens[i][0]);
            }
        }
        else if (tokens[i][0] == '(')
        {
            operators.push(tokens[i][0]);
        }
        else if (tokens[i][0] == ')')
        {
            while (operators.top() != '(')
            {
                RPN.push({ operators.top(), "operator" });
                operators.pop();
            }
            operators.pop();
        }
    }
    while (!operators.empty())
    {
        RPN.push({ operators.top(), "operator" }); // add remaining operators to RPN queue
        operators.pop();
    }
    
    //Calculating RPN
    stack<double> output;
    while (!RPN.empty())
    {
        string token = RPN.front()[0];
        RPN.pop();
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1))
        {
            output.push(stod(token));
        }
        else if (isOperator(token[0]))
        {
            double first = output.top();
            output.pop();
            double second = output.top(); 
            output.pop(); 

			if (isnan(first) or (isnan(second))) 
            { 
                return numeric_limits<double>::quiet_NaN(); // check for NaN
            }
            else if (token == '+')  { output.push(first + second); }
            else if (token == '-')  { output.push(second - first); }
            else if (token == '*')  { output.push(first * second); }
            else if (token == '/')
            { 
                if (first == 0)
                {
					return numeric_limits<double>::quiet_NaN();
                }
                else 
                {
                    output.push(second / first); 
                }
            }
        }
    }
    if (!output.empty())
    {
        double result = output.top();
        return result;
    }
}