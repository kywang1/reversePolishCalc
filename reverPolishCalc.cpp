#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>
#include <string>
#include <cstring>
#include <cmath>
#define space "    "

using namespace std;
stack<float> myStack; //stack for storing part 1
stack<string> stringStack; //stack for storing everything needed in part 2
int numberOfIndents = 0; // keep track of indents needed for part 2

int checkForOperand(string op){ //return 0 if operand, else return -1
	if(op == "+" || op == "-" ||op == "*" ||op == "/" ||op == "^" || op == "<" || op == ">"){
		return 0;
	}
	return -1;
}

int checkStackSize(){
	if(myStack.size() < 2){
		return -1;
	}
	else{
		return 0;
	}
}

int checkStackSizeFloorAndCeiling(){
	if(myStack.size() < 1){
		return -1;
	}
	else{
		return 0;
	}
}

//https://stackoverflow.com/questions/19678572/how-to-validate-that-there-are-only-digits-in-a-string
bool is_digits(const std::string &str) {
    return str.find_first_not_of("0123456789.") == std::string::npos;
}

void printOp(int indents){ //recursive function to print out part2

	if(indents > 0){ //check if indents needed, if it is print them all out
		for(int i = 0 ; i < indents ; i++){
			cout << space;
		}
	}

	if(checkForOperand(stringStack.top()) == 0){ //is an operator
		cout << "(" << stringStack.top() << endl;

		if(stringStack.top() == "<" || stringStack.top() == ">"){
			stringStack.pop();
			numberOfIndents++; //increase indents for printing out other operands or operators
			printOp(numberOfIndents);
		}
		else{
			stringStack.pop();
			numberOfIndents++; //increase indents for printing out other operands or operators
			printOp(numberOfIndents);
			printOp(numberOfIndents);
		}

		
		numberOfIndents--; //decrease numberOfIndents after returning from recursive function
		if(indents > 0){ //check if indents needed, if it is print them all out
			for(int i = 0 ; i < indents ; i++){
				cout << space;
			}
		}
		cout << ")" << endl;
	}
	else{ //is an operand
		cout << stringStack.top() << endl;
		stringStack.pop();
	}
}

void operandOperation(string op){
	double newVal;
	newVal = myStack.top();
	myStack.pop();
	if(op.compare("+") == 0){
		newVal += myStack.top();
	}
	else if(op.compare("-") == 0){
		newVal -= myStack.top();
	}
	else if(op.compare("*") == 0){
		newVal *= myStack.top();
	}
	else if(op.compare("/") == 0){
		newVal /= myStack.top();
	}
	else if(op.compare("^") == 0){
		newVal = pow(newVal,myStack.top());
	}
	else{
		cout << "Operand not supported" << endl;
	}
	
	myStack.pop();
	myStack.push(newVal);
}

void operandOperation2(string op){
	double newVal;
	newVal = myStack.top();
	myStack.pop();
	if(op.compare("<") == 0){
		newVal = floor(newVal);
	}
	else if(op.compare(">") == 0){
		newVal = ceil(newVal);
	}

	myStack.push(newVal);
}

int main(int argc, const char * argv[]){
	string operand;
	string argument;
	double number;
	int temp;
	string::size_type sz;

	if(argv[1]){
		argument = argv[1];
	}

	while(1){
		getline(cin,operand);
		if(operand.empty()){
			if(myStack.size() == 1){
				if(argument == "-l"){
					printOp(numberOfIndents);
					return 0;
				}
				else{
					cout << myStack.top() << endl;
					return 0;
				}
			}
			else{
				cout << "Error: Invalid number of inputs!" << endl;
			}
			break;
		}

		if(checkForOperand(operand) == -1){ //not an operand, check for operator validity

			try{ //convert to double  if input is not an operand
				number = stod(operand,&sz);
			}
			catch(exception &err){ //if invalid input throw error
				cout << "Error: Invalid input " << "'" << operand << "'" << "!" << endl;
				return 0;
			}

			if(!is_digits(operand)){
				cout << "Error: Invalid input " << "'" << operand << "'" << "!" << endl;
				return 0;
			}

			stringStack.push(operand);
			myStack.push(number);
		}
		else{
			//handle operand, perform algorithm
			if(operand.compare("+") == 0){
				if(checkStackSize() == 0){
					operandOperation(operand);
					stringStack.push(operand);
				}
				else{
					cout << "Error: Invalid number of operands!" << endl;
					break;
				}
			}
			else if(operand.compare("-") == 0){
				if(checkStackSize() == 0){
					operandOperation(operand);
					stringStack.push(operand);
				}
				else{
					cout << "Error: Invalid number of operands!" << endl;
					break;
				}
			}
			else if(operand.compare("*") == 0){
				if(checkStackSize() == 0){
					operandOperation(operand);
					stringStack.push(operand);
				}
				else{
					cout << "Error: Invalid number of operands!" << endl;
					break;
				}
			}
			else if(operand.compare("/") == 0){
				if(checkStackSize() == 0){
					operandOperation(operand);
					stringStack.push(operand);
				}
				else{
					cout << "Error: Invalid number of operands!" << endl;
					break;
				}
			}
			else if(operand.compare("^") == 0){
				if(checkStackSize() == 0){
					operandOperation(operand);
					stringStack.push(operand);
				}
				else{
					cout << "Error: Invalid number of operands!" << endl;
					break;
				}
			}
			else if(operand.compare("<") == 0){
				if(checkStackSizeFloorAndCeiling() == 0){
					operandOperation2(operand);
					stringStack.push(operand);
				}
				else{
					cout << "Error: Invalid number of operands!" << endl;
					break;
				}
			}
			else if(operand.compare(">") == 0){
				if(checkStackSizeFloorAndCeiling() == 0){
					operandOperation2(operand);
					stringStack.push(operand);
				}
				else{
					cout << "Error: Invalid number of operands!" << endl;
					break;
				}
			}
			else{
				cout << "Error: Operator not supported" << endl;
			}
		}
	}

	return 0;
}

