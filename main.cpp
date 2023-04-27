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

  
    char last_stack_char;//char being compared
    char first_input_char;//char being compared

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
                    
                   

    
   
    //load the stack columb with a $ and the first non terminal, push input, and push empty for output first row  
    stack_coll.push("$E");      input_coll.push(og_input);          output_coll.push(" ");
    
    //now that we have string we will use given Predictive parsing table to compare.
        //setting current variable to later be compared 
while(1){      
       
        //assign the last_stack_char and first_input_char so that we can evaluate
        curr_stack_string = stack_coll.back();
        last_stack_char = curr_stack_string.back();   
        first_input_char = input[0];

                //if there is a space in the first char of input then delete it 
                    if(input[0] == ' ' ){
                    input = input.erase(0,1); //erase the first char in the string 
                    first_input_char = input[0]; 
                    }



     if (last_stack_char != first_input_char) //if the last stck char and first input are NOT equivelent execute 
     {
        //look for production rule
        curr_pro_rule = production_rule(last_stack_char, first_input_char);
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
                        input_coll.push(input);}
                     
                     if (rev_prod == "ɛ"){ // if we have ɛ then we delete last_stack_char in stack and put the string back on 
                        curr_stack_string.erase(curr_stack_string.end());
                        stack_coll.push(curr_stack_string);
                        input_coll.push(input);
                     }
            

        
     }//end  of if, continue chacking...




        //reassign the last_stack_char and first_input_char so that we can re-evaluate
        curr_stack_string = stack_coll.back();
        last_stack_char = curr_stack_string.back();
        first_input_char = input[0];

     




     if ( (last_stack_char == first_input_char) ) //if the last stck char and first input are equivelent execute 
     {
            
            if ((last_stack_char == '$') && (first_input_char == '$'))//checking for end/ accepted 
            {                
                display_all(stack_coll,input_coll,output_coll);//display all queues, stack_coll, input_coll, output_coll
                cout << "string is accepted/valid\n";
                return 0; //ends the loop 
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

    



        

        //need to still check if not accepted. -------------------------------------------------------------------
        
        //if not accepted display contents of queue, end the loop-----------------------------------------
                //display_all(stack_coll,input_coll,output_coll);
                //cout << "string not accepted.\n ";
    




//loop back to the top, untul not accepted or accepted 
 //reassign the last_stack_char and first_input_char so that we can re-evaluate, this is done at top of the loop
} //end of while loop

return 0;
};//end of main 




//this function taks in the queues and displays them, executes when you know if string is accepted or not accepted and 
//we want to pisplay the data 
void display_all(queue<string> stack_coll, queue<string> input_coll, queue<string> output_coll){

    queue<string> s = stack_coll; //make a copy, so we can display each queue 
    queue<string> i = input_coll;
    queue<string> o = output_coll;

    while (!s.empty()) ///all queues shoudl be equal in size so you should just have to check length of 1
    {
        cout << s.front() << "   |   " << i.front() << "   |   " << o.front() << "   |   " << endl;  
        
        s.pop(); i.pop(); o.pop(); //clear the first items in the queue, then repreat.

    }

}










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

