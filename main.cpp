#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

// Reverses a string
void reverseString(std::string& str) {
    int length = str.length();
    for (int i = 0; i < length / 2; i++)
        std::swap(str[i], str[length - i - 1]);
}

// Prints the contents of the stack
void printStack(const std::vector<char>& stack) {
    std::cout << "Current stack: ";
    for (const auto& entry : stack)
        std::cout << entry << " ";
    std::cout << "\n\n";
}

// Find the production rule based on column and row values
std::string findProductionRule(char column, char row) {
    if (row == 'E' && column == 'a')
        return "TQ";
    if (row == 'E' && column == '(')
        return "TQ";
    if (row == 'Q' && column == '+')
        return "+TQ";
    if (row == 'Q' && column == '-')
        return "-TQ";
    if (row == 'Q' && column == ')')
        return "e";
    if (row == 'Q' && column == '$')
        return "e";
    if (row == 'T' && column == 'a')
        return "FR";
    if (row == 'T' && column == '(')
        return "FR";
    if (row == 'R' && column == '+')
        return "e";
    if (row == 'R' && column == '-')
        return "e";
    if (row == 'R' && column == '*')
        return "*FR";
    if (row == 'R' && column == '/')
        return "/FR";
    if (row == 'R' && column == ')')
        return "e";
    if (row == 'R' && column == '$')
        return "e";
    if (row == 'F' && column == 'a')
        return "a";
    if (row == 'F' && column == '(')
        return "(E)";

    return "";
}

// Push a reversed string to the stack
bool pushToStack(std::vector<char>& stack, const std::string& toReverse) {
    std::string reversed = toReverse;
    reverseString(reversed);

    bool pushedAtLeastOne = false;
    for (const auto& c : reversed) {
        pushedAtLeastOne = true;
        std::cout << "Instering in stack: " << c << std::endl;
        stack.push_back(c);
    }

    return pushedAtLeastOne;
}

// Remove all spaces from a given string
std::string removeSpaces(const std::string& str) {
    std::string result = str;
    result.erase(remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

int main() {
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

    bool isGoodInput = true;
    bool isValidInput = true;

    // Check if input exists
    if (inputString.empty())
        isGoodInput = false;

    if (inputString.back() != '$')
    {
        std::cout << "String does not end with a $. Invalid\n";
        return 0;
    }

    // Validate input against regular expression pattern
    std::regex validCharsToUseRegex("[+*-/()a$]*");
    if (!std::regex_match(inputString, validCharsToUseRegex))
        isValidInput = false;

    if (!isValidInput)
        isGoodInput = false;

    // If input is not valid, display the stack and exit
    if (!isGoodInput) {
        printStack(stack);
        std::cout << "String is not a valid regular expression.\n";
        return 0;
    }

    // Print out the current stack
    printStack(stack);
    do {
        curState = stack.back();
        char input = inputString[0];

        if (curState == 'e') {
            std::cout << "Removing from stack: ε" << std::endl;
            stack.pop_back();
            printStack(stack);
        }

        // Checking non-terminals
        else if (curState == 'a' || curState == '+' || curState == '-' ||
            curState == '*' || curState == '/' || curState == '(' || curState == ')') {
            if (curState == input) {
                std::cout << "Removing from stack: " << stack.back() << std::endl;
                stack.pop_back();
                printStack(stack);
                inputString.erase(0, 1);
                std::cout << "Input: " << inputString << std::endl;
            }
            else {
                std::cout << "Rejected." << std::endl;
                accepted = false;
                break;
            }
        }

        // Checking terminals
        else if (curState == 'E' || curState == 'T' || curState == 'Q' || curState == 'R' || curState == 'F') {
            std::string production = findProductionRule(input, curState);
            if (!production.empty() || (!(curState == 'F' && input == 'a'))) {
                std::cout << "Removing from stack: " << stack.back() << std::endl;
                stack.pop_back();
                printStack(stack);
                if (!pushToStack(stack, production)) {
                    accepted = false;
                    break;
                }
            }
            else {
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