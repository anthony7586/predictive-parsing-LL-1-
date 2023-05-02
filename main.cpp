#include <iostream>
#include <string>
#include <algorithm> //https://www.digitalocean.com/community/tutorials/reverse-string-c-plus-plus
#include <queue> // https://www.programiz.com/cpp-programming/stack
#include <regex>

using namespace std;


// This function taks in the queues and displays them, executes when you know if string is accepted or not accepted and 
// we want to display the data 
void display_all(queue<string> stack_col, queue<string> input_col, queue<string> output_col)
{
    queue<string> s = stack_col; //make a copy, so we can display each queue 
    queue<string> i = input_col;
    queue<string> o = output_col;

    // All queues shoudl be equal in size so you should just have to check length of 1
    while (!s.empty())
    {
        cout << s.front() << "   |   " << i.front() << "   |   " << o.front() << "   |   " << endl;

        s.pop(); i.pop(); o.pop(); //clear the first items in the queue, then repreat.

    }

}

// This function is used to find the proper production rule, called in main 
string production_rule(char y_column, char x_row)
{
    string pro_rule;

    if (y_column == 'E')
    {
        pro_rule = "TQ";
        return pro_rule;
    }

    if ((y_column == 'Q') && (x_row == '+'))
    {
        pro_rule = "+TQ";
        return pro_rule;
    }

    if ((y_column == 'Q') && (x_row == '-'))
    {
        pro_rule = "-TQ";
        return pro_rule;
    }

    if ((y_column == 'Q') && (x_row == ')'))
    {
        pro_rule = "";//supposed to be ɛ but since it will be deleted i just didnt input it 
        return pro_rule;
    }

    if ((y_column == 'Q') && (x_row == '$'))
    {
        pro_rule = "";//supposed to be ɛ but since it will be deleted i just didnt input it 
        return pro_rule;
    }

    if (y_column == 'T')
    {
        pro_rule = "FR";
        return pro_rule;
    }

    if ((y_column == 'R') && (x_row == '+'))
    {
        pro_rule = "";//supposed to be ɛ but since it will be deleted i just didnt input it 
        return pro_rule;
    }

    if ((y_column == 'R') && (x_row == '-'))
    {
        pro_rule = "";//supposed to be ɛ but since it will be deleted i just didnt input it 
        return pro_rule;
    }

    if ((y_column == 'R') && (x_row == '*'))
    {
        pro_rule = "*FR";
        return pro_rule;
    }

    if ((y_column == 'R') && (x_row == '/'))
    {
        pro_rule = "/FR";
        return pro_rule;
    }

    if ((y_column == 'R') && (x_row == ')'))
    {
        pro_rule = "";//supposed to be ɛ but since it will be deleted i just didnt input it 
        return pro_rule;
    }

    if ((y_column == 'R') && (x_row == '$'))
    {
        pro_rule = "";//supposed to be ɛ but since it will be deleted i just didnt input it 
        return pro_rule;
    }

    if ((y_column == 'F') && (x_row == 'a'))
    {
        pro_rule = "a";
        return pro_rule;
    }

    if ((y_column == 'F') && (x_row == '('))
    {
        pro_rule = "(E)";
        return pro_rule;
    }

    return "not found";
}

int main()
{
    queue<string> stack_col;
    queue<string> input_col;
    queue<string> output_col;

    string cur_stack_string = "";   //for stack column 
    string cur_pro_rule;
    string input;
    string rev_prod;

    string og_input = "";           //will hold original user input

    char last_stack_char;           //char being compared
    char first_input_char;          //char being compared
    const int MAX_LENGTH = 50;

    // Start with user input strings
    cout << "input the string.\n";
    cin >> og_input; 
    input = og_input;               // make a copy of string so you can save og for later 

    /*      these will be test strings 
            og_input

            (a+a)*a$
            a*(a/a)$
            a(a+a)$
    */
   
    // :oad the stack columb with a $ and the first non terminal, push input, and push empty for output first row  

    stack_col.push("$E");      input_col.push(og_input);          output_col.push(" ");
    
    // Remove all spaces from the input string
    remove(input.begin(), input.end(), ' ');

    // Now that we have string we will use given Predictive parsing table to compare.
    // setting curent variable to later be compared 
    while(1)
    {
        // Assign the last_stack_char and first_input_char so that we can evaluate
        cur_stack_string = stack_col.back();
        last_stack_char = cur_stack_string.back();   
        first_input_char = input[0];


         // CHECK IF INPUT CAN BE PARSED  ==============================================
        bool isGoodInput = true;
        bool isValidInput = true;
        // make sure input exists
        if (input.empty()) isGoodInput = false;

        // Try to match all lexing cases at the start of the input.
        smatch inputMatch;
        regex validCharsToUseRegex("[+|*|-|\/|(|)|a|$]*");
        if (regex_search(input, inputMatch, validCharsToUseRegex))
        {
            if (inputMatch.length() == input.length()) isValidInput = true;
            else isValidInput = false;
        }

        if (!isValidInput) isGoodInput = false;

        if (input.back() != '$') isGoodInput = false;

        // If not good, display contents of queue
        if (isGoodInput == false)
        {
            display_all(stack_col, input_col, output_col);
            cout << "string not accepted.\n ";
            return 0;
        }

        if (last_stack_char != first_input_char) //if the last stck char and first input are NOT equivelent execute 
        {
            // Look for production rule and push curent production into output queue
            cur_pro_rule = production_rule(last_stack_char, first_input_char);
            output_col.push(cur_pro_rule);

            // Replace last char in cur_stack_string with the production rule (in reverse)
            // cur_pro_rule is reversed in next line and stored in rev_prod
            rev_prod = cur_pro_rule;
            reverse(rev_prod.begin(), rev_prod.end());

            // Now we replace the char in the cur_stack_string with the new production rule as long as its not epsilon 
            // since epsilon will be deleted i decided to leave it out and not push epsilon 
            if (rev_prod != "ɛ")
            {
                // Replace char with production rule
                cur_stack_string.erase(cur_stack_string.end()); //deletes the last char in curent stack string 
                cur_stack_string.append(rev_prod); //appends the reveresed production 
                // Push to the stack_col queue 
                stack_col.push(cur_stack_string);
                input_col.push(input);
            }

            // If we have 'ɛ' then we delete last_stack_char in stack and put the string back on 
            if (rev_prod == "ɛ")
            { 
                cur_stack_string.erase(cur_stack_string.end());
                stack_col.push(cur_stack_string);
                input_col.push(input);
            }
        }

        // Reassign the last_stack_char and first_input_char so that we can re-evaluate
        cur_stack_string = stack_col.back();
        last_stack_char = cur_stack_string.back();
        first_input_char = input[0];

        // If the last stack char and first input are equivelent execute
        if (last_stack_char == first_input_char) 
        {     
            // When the last stack char and first input are both $, then display all the contents...
            if ((last_stack_char == '$') && (first_input_char == '$'))
            {                
                display_all(stack_col, input_col, output_col); //display all queues, stack_col, input_col, output_col
                cout << "string is accepted/valid\n";
                return 0; //ends the loop 
            }

            // Delete last char from cur_stack_string, then push it into the stack queue 
            cur_stack_string.pop_back();
            stack_col.push(cur_stack_string);
            // Delete first char from input, then push it onto the input queue  
            input.erase(0,1);
            input_col.push(input);
            // Push a blank string into output queue 
            output_col.push(" ");
        }

        // Need to still check if 'not accepted'. -------------------------------------------------------------------

        // If not accepted display contents of queue, end the loop-----------------------------------------
            //display_all(stack_col,input_col,output_col);
            //cout << "string not accepted.\n ";

        // Loop back to the top, until not accepted or accepted 
        // Reassign the last_stack_char and first_input_char so that we can re-evaluate, this is done at top of the loop
    }

    return 0;
};