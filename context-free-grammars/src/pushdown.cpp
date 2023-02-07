#include <map>
#include <vector>
#include <iostream>

/*
    S --> Zc
    Z --> ZA | A
    A --> aZb | ab
*/

std::vector<char> stack;

std::vector<std::string> getProductions(std::string expression)
{
    std::vector<std::string> prod;
    std::string temp = "";

    for (unsigned i = 0; i < expression.length(); i++)
    {
        if (expression[i] == '|')
        {
            prod.push_back(temp);
            temp = "";
        }
        else
        {
            temp += expression[i];
        }
    }
    prod.push_back(temp);

    return prod;
}

void printStack()
{
    std::cout << "Stack: ";
    for (unsigned i = 0; i < stack.size(); i++)
    {
        std::cout << stack[i];
    }
    std::cout << std::endl;
}

bool isNonTerminal(char symbol) {
    if (symbol >= 'A' && symbol <= 'Z')
        return true;
    return false;
}

void popRule(std::string rule, unsigned *pointer) {
    for (unsigned i = 0; i < rule.length(); i++) {
        if (!isNonTerminal(stack.back())) {
            *pointer = *pointer - 1;
        }
        stack.pop_back();
    }
}

void printRule(std::string rule, char symbol) {
    std::cout << "Chose rule: " << symbol << " --> ";
    for (unsigned i = 0; i < rule.length(); i++) {
        std::cout << rule[i];
    }
    std::cout << std::endl;
}

void pushRule(std::string rule) {
    // std::cout << "Rule length: " << rule.length() << std::endl;
    for (unsigned int i = 0; i < rule.length(); i++) {
        // std::cout << "Pushing symbol " << rule[rule.length() - (1 + i)] << " to the stack" << std::endl;
        stack.push_back(rule[rule.length() - (1 + i)]);
    }
}

bool pushdown(std::map<char, std::vector<std::string>> rules, std::string input, unsigned pointer)
{   
    std::cout << "---" << std::endl;
    printStack();
    if (stack.size() == 0)
    {
        if (pointer == input.length())
            return true;
        else
            return false;
    } else if (stack.size() > input.length())
        return false;

    char top = stack.back();
    stack.pop_back();
    
    if (top == input[pointer])
        return pushdown(rules, input, pointer + 1);
    else if (isNonTerminal(top)) {
        for (unsigned int i = 0; i < rules[top].size(); i++) {
            printRule(rules[top][i], top);
            pushRule(rules[top][i]);
            if (pushdown(rules, input, pointer))
                return true;
            else {
                std::cout << "Popping rule from stack [failed]!" << std::endl;
                popRule(rules[top][i], &pointer);
            }
        }
        stack.push_back(top);
    }
    return false;
}

int main(int argc, char const *argv[])
{
    std::map<char, std::vector<std::string>> rules;

    rules['S'] = getProductions("Zc");
    rules['Z'] = getProductions("ZA|A");
    rules['A'] = getProductions("aZb|ab");

    std::string input;

    std::cout << "Enter input string: ";
    std::cin >> input;

    stack.push_back('S');

    if ( pushdown(rules, input, 0) )
        std::cout << "Accepted" << std::endl;
    else
        std::cout << "Rejected" << std::endl;

    return 0;
}

