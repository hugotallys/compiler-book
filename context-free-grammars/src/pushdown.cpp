#include <map>
#include <vector>
#include <iostream>

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

void popRule(std::vector<char>& stack, std::string rule) {
    for (unsigned i = 0; i < rule.length(); i++) {
        stack.pop_back();
    }
}

void pushRule(std::vector<char>& stack, std::string rule) {
    std::cout << "Aborting thread, failed!" << std::endl;
    for (unsigned int i = 0; i < rule.length(); i++) {
        stack.push_back(rule[rule.length() - (1 + i)]);
    }
}

void printRule(std::string rule, char symbol) {
    std::cout << "Applying rule: " << symbol << " --> ";
    for (unsigned i = 0; i < rule.length(); i++) {
        std::cout << rule[i];
    }
    std::cout << std::endl;
}

void printStack(std::vector<char>& stack)
{
    std::cout << "Stack: ";
    for (unsigned i = 0; i < stack.size(); i++)
    {
        std::cout << "| " << stack[i] << ' ';
    }
    std::cout << std::endl;
}

bool isNonTerminal(char symbol) {
    if (symbol >= 'A' && symbol <= 'Z')
        return true;
    return false;
}

bool pushdown(std::vector<char>& stack, std::map<char, std::vector<std::string>>& rules, std::string input, unsigned pointer)
{
    std::cout << std::endl << "--- Input head: " << pointer << " ---" << std::endl << std::endl;
    printStack(stack);
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
    
    if (top == input[pointer]) {
        if (pushdown(stack, rules, input, pointer + 1))
            return true;
    }
    else if (isNonTerminal(top)) {
        for (unsigned int i = 0; i < rules[top].size(); i++) {
            printRule(rules[top][i], top);
            pushRule(stack, rules[top][i]);
            if (pushdown(stack, rules, input, pointer))
                return true;
            else {
                popRule(stack, rules[top][i]);
            }
        }
    }
    stack.push_back(top);
    return false;
}

int main(int argc, char const *argv[])
{
    std::vector<char> stack;
    std::map<char, std::vector<std::string>> rules;

    rules['S'] = getProductions("Zc");
    rules['Z'] = getProductions("ZA|A");
    rules['A'] = getProductions("aZb|ab");

    std::string input;

    std::cout << "Enter input string: ";
    std::cin >> input;

    stack.push_back('S');

    if ( pushdown(stack, rules, input, 0) )
        std::cout << "Accepted" << std::endl;
    else
        std::cout << "Rejected" << std::endl;

    return 0;
}

