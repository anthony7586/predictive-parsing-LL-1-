#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <map>

// Reverses a string
std::string reverseString(const std::string& str)
{
    std::string reversed = str;
    int length = reversed.length();
    for (int i = 0; i < length / 2; i++)
        std::swap(reversed[i], reversed[length - i - 1]);
    return reversed;
}

// Remove all spaces from a given string
std::string removeSpaces(const std::string& str)
{
    std::string result = str;
    result.erase(remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

// Prints the contents of the stack
void printStack(const std::vector<char>& stack)
{
    std::cout << "Current stack: ";
    for (const auto& entry : stack)
        std::cout << entry << " ";
    std::cout << "\n\n";
}

// Find the production rule based on column and row values
std::string findProductionRule(char column, char row)
{
    // Use a map to define our production rules
    std::map<std::pair<char, char>, std::string> rules =
    {
        {{'E', 'a'}, "TQ"},
        {{'E', '('}, "TQ"},
        {{'Q', '+'}, "+TQ"},
        {{'Q', '-'}, "-TQ"},
        {{'Q', ')'}, "e"},
        {{'Q', '$'}, "e"},
        {{'T', 'a'}, "FR"},
        {{'T', '('}, "FR"},
        {{'R', '+'}, "e"},
        {{'R', '-'}, "e"},
        {{'R', '*'}, "*FR"},
        {{'R', '/'}, "/FR"},
        {{'R', ')'}, "e"},
        {{'R', '$'}, "e"},
        {{'F', 'a'}, "a"},
        {{'F', '('}, "(E)"}
    };

    // Find the rule we need and return it
    auto it = rules.find({ row, column });
    if (it != rules.end())
        return it->second;
    else
        return "";
}

// Push a reversed string to the stack
bool pushToStack(std::vector<char>& stack, const std::string& toReverse)
{
    std::string reversed(toReverse.rbegin(), toReverse.rend());
    for (const auto& c : reversed)
    {
        std::cout << "Inserting in stack: " << c << std::endl;
        stack.push_back(c);
    }
    return !reversed.empty();
}

// Ensure it's not empty, ends with a '$', and matches the valid chars regex
bool validateInputString(const std::string& str)
{
    // Check if input is empty
    if (str.empty())
    {
        std::cout << "Empty string. Invalid input.\n";
        return false;
    }

    // Check if the string ends with '$'
    if (str.back() != '$')
    {
        std::cout << "Warning: String does not end with '$'.\n";
    }

    // Remove all spaces from the string
    std::string trimmed = removeSpaces(str);

    // Validate input against regular expression pattern
    std::regex validCharsToUseRegex("[+*-/()a$]*");
    if (!std::regex_match(trimmed, validCharsToUseRegex))
    {
        std::cout << "Invalid characters found in the input string.\n";
        return false;
    }

    return true;
}

int main() 
{
    std::string inputString;
    char curState;
    bool accepted = true;
    std::vector<char> stack;

    // Initialize the stack with $ E as its initial elements.
    stack.push_back('$');
    stack.push_back('E');
    curState = stack.back();

    // User input
    std::cout << "Enter a string: ";
    std::cin >> inputString;

    // Validate input string
    if (!validateInputString(inputString))
    {
        printStack(stack);
        std::cout << "String is not a valid regular expression.\n";
        return 0;
    }

    // Print out the current stack
    printStack(stack);
    do 
    {
        curState = stack.back();
        char input = inputString[0];

        if (curState == 'e') 
        {
            std::cout << "Removing from stack: ε" << std::endl;
            stack.pop_back();
            printStack(stack);
        }

        // Checking non-terminals
        else if (curState == 'a' || curState == '+' || curState == '-' || curState == '*' || curState == '/' || curState == '(' || curState == ')') 
        {
            if (curState == input) 
            {
                std::cout << "Removing from stack: " << stack.back() << std::endl;
                stack.pop_back();
                printStack(stack);
                inputString.erase(0, 1);
                std::cout << "Input: " << inputString << std::endl;
            }
            else 
            {
                std::cout << "Rejected." << std::endl;
                accepted = false;
                break;
            }
        }

        // Checking terminals
        else if (curState == 'E' || curState == 'T' || curState == 'Q' || curState == 'R' || curState == 'F') 
        {
            std::string production = findProductionRule(input, curState);

            // Ensure production is valid...
            if (!production.empty() || (!(curState == 'F' && input == 'a'))) 
            {
                std::cout << "Removing from stack: " << stack.back() << std::endl;
                stack.pop_back();
                printStack(stack);
                if (!pushToStack(stack, production)) 
                {
                    accepted = false;
                    break;
                }
            }
            else
            {
                std::cout << "Rejected." << std::endl;
                accepted = false;
                break;
            }
        }

    } while (curState != '$');

    // Finalize the output
    if (accepted)
        std::cout << "Input is accepted/ valid.\n";
    else
        std::cout << "Input is not accepted/ In valid.\n";

    return 0;
}