#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

// The predictive parsing table
// "Empty" means the cell is NULL
const char* parsingTable[5][8] = {"TQ", "Empty", "Empty", "Empty", "Empty", "TQ", "Empty", "Empty",
                            "Empty", "+TQ", "-TQ", "Empty", "Empty", "Empty", "", "",
                            "FR", "Empty", "Empty", "Empty", "Empty", "FR", "Empty", "Empty",
                            "Empty", "", "", "*FR", "/FR", "Empty", "", "",
                            "a", "Empty", "Empty", "Empty", "Empty", "(E)", "Empty", "Empty"};

string getTableRowColumn(char topStack, char read); 

// Print the stack
void printStack(stack<char> Stack) {
    if (Stack.empty()) {
        return;
    }

    char temp = Stack.top();

    Stack.pop();

    printStack(Stack);

    cout << temp << " ";

    Stack.push(temp);
}

// Trace the given input string
void trace(string input){
    // Boolean that is true if input string is accepted, and false it not.
    bool accepted = false;
    stack<char> Stack;

    // Push dollar sign and the first non-terminal from production rules
    Stack.push('$');
    Stack.push('E');

    string initialString = input;
    
    // Iterate over input string until string is accepted or rejected
    while (!accepted){
        char read = input[0];
        char topStack = Stack.top();
        Stack.pop();

        // If the top of the stack and input symbol match
        if (read == topStack){
        
            cout << "\n\nMatch!\n";
            cout << "Top of stack '" << topStack << "' matches input character '" << read << "'\n";

            // Accept if dollar signs match
            if (topStack == '$' & read == '$'){
                cout << "ACCEPT\n\n";
                accepted = true;
                break;
            }

            cout << "Stack: ";
            printStack(Stack);
            cout << topStack;
            cout << "\t\tInput string: ";
            for (int i = 0; i < input.length(); i++){
                cout << input[i];
            }
            cout << endl;

            // Remove front char from input string
            input.erase(0, 1);
        
            char topStack = Stack.top();
            char read = input[0];
            
            
        } else {

            // Get the correct cell from the parsing table
            string cell = getTableRowColumn(topStack, read);
            
            // If the cell is empty we reject the input string
            if (cell == "Empty"){
                cout << "\n\nERROR!" << endl;
                cout << "Stack: ";
                printStack(Stack);
                cout << topStack;
                cout << "\t\tInput string: ";
                for (int i = 0; i < input.length(); i++){
                    cout << input[i];
                }
                cout << endl;
                cout << "Stack letter '"<< topStack << "' on input symbol '" << read << "'" << endl;
                cout << "\nBlank cell. Input string " << initialString << " rejected." << endl << endl;
                accepted = true;

            // Push the symbols to the stack
            } else {
                reverse(cell.begin(), cell.end());
                for (int i = 0; i < cell.length(); i++){
                    Stack.push(cell[i]);
                }
        
                
            }
        }  
    }
    
}

// Return the row and column numbers to later get cells from predictive parsing table
string getTableRowColumn(char topStack, char read){
    int row, column;
   

    // Get row number from stack letter
    if (topStack == 'E') row = 0;
    if (topStack == 'Q') row = 1;
    if (topStack == 'T') row = 2;
    if (topStack == 'R') row = 3;
    if (topStack == 'F') row = 4;

    // Get column number from input symbol
    if (read == 'a') column = 0;
    if (read == '+') column = 1;
    if (read == '-') column = 2;
    if (read == '*') column = 3;
    if (read == '/') column = 4;
    if (read == '(') column = 5;
    if (read == ')') column = 6;
    if (read == '$') column = 7;
    if (read == 'E') column = 0;

    
    return parsingTable[row][column];

}


int main(){

    vector<string> inputs = {"(a+a)*a$", "a*(a/a)$", "a(a+a)$"};

    for (int i = 0; i < inputs.size(); i++){
        cout << "\n\n\n\n--------------------- Input string: " << inputs[i] << " ---------------------";
        trace(inputs[i]);

    }

    return 0;

}

