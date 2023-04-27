#include <iostream>
#include <string>
#include <algorithm> //https://www.digitalocean.com/community/tutorials/reverse-string-c-plus-plus
#include <queue> // https://www.programiz.com/cpp-programming/stack
using namespace std;


int main(){
    
    queue<string> stack_coll;
    queue<string> input_coll;
    queue<string> output_coll;


    string curr_stack_string = "";//for stack column 
    string curr_pro_rule;
    string input;
    string rev_prod;

    string og_input = ""; //will hold original user input

  
    char curr_stack_char;//char being compared
    char curr_input_char;//char being compared

    //start with user input strings
    cout << "input the string.\n";
    cin >> og_input; 
    input = og_input;// make a copy of string so you can save og for later 
    


            /*      these will be test strings 
                    og_input

                    (a +a )*a$
                    a*(a/a)$
                    a(a+a)$
            
            */  
                    
            //the next few comments will be assuming the input is (a +a )*a$        

    //get the length of strings to later use as index  
    int og_input_length = og_input.length(); 
   
    //load the stack columb with a $ and the first non terminal, push input, and push empty for output first row  
    stack_coll.push("$E");      input_coll.push(og_input);          output_coll.push(" ");
    
    //now that we have string we will use given Predictive parsing table to compare.
        //setting current variable to later be compared 
        curr_stack_string = stack_coll.back();
        curr_stack_char = curr_stack_string.back();   
        curr_input_char = input[0];

                //if there is a space in the first char of input then delete it 
                    if(input[0] == ' ' ){
                    input = input.erase(0,1); //erase the first char in the string 
                    curr_input_char = input[0]; 
                    }



     if (curr_stack_char != curr_input_char) //if the last stck char and first input are NOT equivelent execute 
     {
        //look for production rule
        curr_pro_rule = production_rule(curr_stack_char, curr_input_char);
        //push current production into output queue
        output_coll.push(curr_pro_rule);


        //replace last char in curr_stack_string with the production rule (in reverse)
        rev_prod = curr_pro_rule; //curr_pro_rule is reversed in next line and stored in rev_prod
         reverse(rev_prod.begin(), rev_prod.end());
                
                //now we replace the char in the curr_stack_string with the new production rule as long as its not epsilon 
                //since epsilon will be deleted i decided to leave it out and not push epsilon 
                     if (rev_prod != "ɛ"){
                        //replace char with production rule
                        curr_stack_string.erase(curr_stack_string.end()); //deletes the last char in current stack string 
                        curr_stack_string.append(rev_prod); //appends the reveresed production 
                        //push to the stack_coll queue 
                        stack_coll.push(curr_stack_string);
                        input_coll.push(input);
                    }
            

        //end  of if, continue chacking...
     }

        //reset the current chars so that we can re-evaluate 
        curr_stack_string = stack_coll.back();
        curr_stack_char = curr_stack_string.back();
        //curr_input_string = input_coll.back();
        curr_input_char = input[0];

     
     if ( (curr_stack_char == curr_input_char) ) //if the last stck char and first input are equivelent execute 
     {
            //checking for end 
            if ((curr_stack_char == '$') && (curr_input_char == '$'))
            {
                
                //display all queues, stack_coll, input_coll, output_coll------------------------------------------------------
                output_coll.push("string is accepted/valid\n");
                //can be done iterativley using for loops ------------------------------------------------------------------------
                
                return 0;
            }


        //delete last char from curr_stack_string, then push it into the stack queue 
        curr_stack_string.pop_back();
        stack_coll.push(curr_stack_string);

        //delete first char from input, then push it onto the input queue  
        input.erase(0,1);
        input_coll.push(input);
        //push a blank string into output queue 
        output_coll.push(" ");

        //end of if, continue checking....
     }

    
      //reset the current chars so that we can re-evaluate, this is done at top but we need to loop back --------------------------
      //loop until the curr_stack_char is $ and also equal to a curr_input_char of $

        

        //how do we check if it is not accepted? -------------------------------------------------------------------
        //also display all queues, stack_coll, input_coll, output_coll------------------------------------------------------
    



return 0;
};










//this function is used to find the proper production rule, called in main 
string production_rule(char y_column, char x_column)
{   string pro_rule;

        if(y_column == 'E'){ 
            pro_rule = "TQ";
            return pro_rule; 
        }
        //////////////////////////////////////////////
        if((y_column == 'Q') && (x_column == '+')){ 
            pro_rule = "+TQ";
            return pro_rule; 
        }
        
        if((y_column == 'Q') && (x_column == '-')){ 
            pro_rule = "-TQ";
            return pro_rule; 
        }

        if((y_column == 'Q') && (x_column == ')' )){ 
            pro_rule = "";//supposed to be ɛ but since it will be deleted i just didnt input it 
            return pro_rule; 
        }
        
        if((y_column == 'Q') && (x_column == '$' )){ 
            pro_rule = "";//supposed to be ɛ but since it will be deleted i just didnt input it 
            return pro_rule; 
        }
        /////////////////////////////////////////////
        if(y_column == 'T' ){ 
            pro_rule = "FR";
            return pro_rule; 
        }
        /////////////////////////////////////////////
        if((y_column == 'R') && (x_column == '+')){       
            pro_rule = "";//supposed to be ɛ but since it will be deleted i just didnt input it 
            return pro_rule; 
        }

        if((y_column == 'R') && (x_column == '-')){       
            pro_rule = "";//supposed to be ɛ but since it will be deleted i just didnt input it 
            return pro_rule; 
        }

        if((y_column == 'R') && (x_column == '*')){       
            pro_rule = "*FR";
            return pro_rule; 
        } 

         if((y_column == 'R') && (x_column == '/')){       
            pro_rule = "/FR";
            return pro_rule; 
        }

        if((y_column == 'R') && (x_column == ')')){       
            pro_rule = "";//supposed to be ɛ but since it will be deleted i just didnt input it 
            return pro_rule; 
        }

        if((y_column == 'R') && (x_column == '$')){       
            pro_rule = "";//supposed to be ɛ but since it will be deleted i just didnt input it 
            return pro_rule; 
        } 
        /////////////////////////////////////////////
        if((y_column == 'F') && (x_column == 'a')){       
            pro_rule = "a";
            return pro_rule; 
        } 

        if((y_column == 'F') && (x_column == '(')){       
            pro_rule = "(E)";
            return pro_rule; 
        }                      
}

