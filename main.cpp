#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <regex>

using namespace std;

void reverseStr(string& str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

void printStack(vector<char> stack)
{
    cout << "Current stack: ";
    for (auto& entry : stack) cout << entry << " ";
    cout << "\n\n";
}

// This function is used to find the proper production rule, called in main 
string production_rule(char column, char row)
{
    if (row == 'E' && column == 'a') return "TQ";
    if (row == 'E' && column == '(') return "TQ";

    if (row == 'Q' && column == '+') return "+TQ";
    if (row == 'Q' && column == '-') return "-TQ";
    if (row == 'Q' && column == ')') return "ɛ";
    if (row == 'Q' && column == '$') return "ɛ";

    if (row == 'T' && column == 'a') return "FR";
    if (row == 'T' && column == '(') return "FR";

    if (row == 'R' && column == '+') return "ɛ";
    if (row == 'R' && column == '-') return "ɛ";
    if (row == 'R' && column == '*') return "*FR";
    if (row == 'R' && column == '/') return "/FR";
    if (row == 'R' && column == ')') return "ɛ";
    if (row == 'R' && column == '$') return "ɛ";

    if (row == 'F' && column == 'a') return "a";
    if (row == 'F' && column == '(') return "(E)";

    return "";
}

bool pushToStack(vector<char>& stack, string toReverse)
{
    reverseStr(toReverse);
    string reversed = toReverse;
    
    bool pushedBackAtLeastOne = false;
    for (auto& c : reversed)
    {
        pushedBackAtLeastOne = true;
        stack.push_back(c);
    }
    
    if (pushedBackAtLeastOne) return true;
    else return false;
}

int main() 
{
    string inputString;
    char state;
    bool accepted = true;
    vector<char> stack;

    // Stack will have $ E as it's initial elements.
    stack.push_back('$');
    stack.push_back('E');


    // user inputString.
    cout << "Enter string" << endl;
    cin >> inputString;

	// Remove all spaces from the input string
    remove(inputString.begin(), inputString.end(), ' ');

    bool isGoodInput = true;
    bool isValidInput = true;
    // make sure input exists
    if (inputString.empty()) isGoodInput = false;

    // Try to match all lexing cases at the start of the inputString.
    smatch inputMatch;
    regex validCharsToUseRegex("[+|*|-|\/|(|)|a|$]*");
    if (regex_search(inputString, inputMatch, validCharsToUseRegex))
    {
        if (inputMatch.length() == inputString.length()) isValidInput = true;
        else isValidInput = false;
    }

    if (!isValidInput) isGoodInput = false;

    if (inputString.back() != '$') isGoodInput = false;

    // If not good, display stack
    if (isGoodInput == false)
    {
        printStack(stack);
        cout << "string not accepted.\n ";
        return 0;
    }

    //prints out the current stack.
    printStack(stack);
    while(state != '$')
    {
        state = stack.back();
        char input = inputString[0];

        if (state == 'e') // 'e' is used in place of ε due to "multi character character constant" error
        {
            cout << "Popping from stack: ε" << endl;
            stack.pop_back();
            printStack(stack);
        } 

        // Checking non terminals
        else if (state == 'a' || state == '+' || state == '-' ||
                state == '*' || state == '/'||state == '(' || state == ')') 
        {
            if (state == input) 
            {
                {
                    cout << "Popping from stack: " << stack.back() << endl;
                    stack.pop_back();
                    printStack(stack);
                    inputString.erase(0, 1);
                    cout << "Input: " << inputString << endl;
                }
            }
            else 
            {
                cout << "Rejected." << endl;
                accepted = false;
                break;
            }
        }

        // checking terminals
        else if (state == 'E' || state == 'T' || state == 'Q' || state == 'R' || state == 'F') 
        {
            if (production_rule(input, state) != "" || (!(state == 'F' && input == 'a'))) 
            {
                cout << "Popping from stack: " << stack.back() << endl;
                stack.pop_back();
                printStack(stack);
                if (!(pushToStack(stack, production_rule(input, state)))) 
                {
                    accepted = false;
                    break;
                }
            }
            else 
            {
                cout << "Rejected." << endl;
                accepted = false;
                break;
            }
        }

    } 

    if (accepted) 
        cout << "Input is accepted.\n";
    else 
        cout << "Input is rejected.\n";
        
    return 0;
}
