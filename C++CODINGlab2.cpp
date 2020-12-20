#include <iostream>
#include <fstream>
#include <string>

// Написать программу, определяющую корректность условия цикла while, содержащего 
// только арифметические и логические операции.
using namespace std;

// ARITHMETIC OPERATORS: 
//      +	Addition	   x + y	
//      -   Subtraction	   x - y
//      *   Multiplication x * y
//      /   Division	   x / y
//      %   Modulus        x % y
//      ++	Increment	   ++x || x++
//      --	Decrement      --x || x--
// LOGICAL OPERATORS:
//		&&	Logical and	   x < 5 &&  x < 10
//		|| 	Logical or	   x < 5 || x < 4
//		!	Logical not    !(x < 5 && x < 10)

string input() {
	string an_array;
	string line;
	ifstream file("input.txt");
	if (file.is_open())
	{
		while (getline(file, line))
		{
			an_array += line;
		}
	}
	line.erase();
	file.close();
	return an_array;
}

bool is_space(int symb) {
	return symb == 32;
}
bool is_bracket(int symb) {
	return symb == 40 || symb == 41;
}
bool is_number(int symb) {
	return 48 <= symb && symb <= 57;
}
bool is_letter(int symb) {
	return 65 <= symb && symb <= 90 || 97 <= symb && symb <= 122;
}
bool is_underscore(int symb) {
	return symb == 95;
}
bool is_operator(int symb) {
	return symb == 33 || symb == 38 || symb == 42 || symb == 43 || symb == 45 || symb == 47;
}
bool is_forbidden_operator(int symb) {
	return symb == 94 || symb == 93 || symb == 91 || symb == 126 || symb == 62 || symb == 60 || symb == 46 || symb == 61;
}

bool identifiers_cant_stay_together(int char_1, int char_2) {

	if (is_number(char_1) && is_letter(char_2)) return true;
	if (is_number(char_1) && is_underscore(char_2)) return true;
	return false;
}
bool char_num_not_valid(int char_num) {
	if (char_num == 33 || char_num == 34 || char_num == 0 || char_num == 94 || char_num == 32 ||
		(char_num > 36 && char_num < 58) ||
		(char_num > 58 && char_num < 64) ||
		(char_num > 64 && char_num < 94) ||
		(char_num > 94 && char_num < 127))
		return false;
	else
		return true;
}
bool there_forbidden_operators(string str) {
	int char_num;
	int and_counter = 0;
	int equal_counter = 0;
	int or_counter = 0;
	for (int i = 0; i < str.length(); i++) {
		char_num = str[i];
		if (is_forbidden_operator(char_num)) { return true; }
		if (char(char_num) == '&') and_counter++;
		if (char(char_num) == '=') equal_counter++;
		if (char(char_num) == '|') or_counter++;
	}

	return !(and_counter % 2 == 0 && equal_counter % 2 == 0 && or_counter % 2 == 0);

}
bool there_wrong_used_unary_operators(string str) {
	int i;
	for (i = 0; i < str.length() - 1; i++) {
		if (str[i] == '!' && (is_space(str[i+1]))) return true;
	}
	return false;

}

string replace(string char1, string char2, string str) {
	int pos;
	for (pos = 0; pos < str.length(); pos++)
	{
		if (char1.length() == 2 && str[pos] == char1[0] && str[pos + 1] == char1[1]) str.replace(pos, 2, char2);
		
		if (char1.length() == 1 && str[pos] == char1[0]) str.replace(pos, 1, char2);
		
	}
	return str;
}

int count(char char1, string str) {
	int symbol;
	int symbol1 = char1;
	int c = 0;
	for (int i = 0; i < str.length(); i++) {
		symbol = str[i];
		if (symbol == symbol1)
			c++;
	}
	return c;
}

bool simplify(string str) 
{
	bool flag = true;
	int operands = 0;
	int operators = 0;

	str = replace("++", "", str);
	str = replace("--", "", str);
	str = replace("!", "", str);
	str = replace("(", "", str);
	str = replace(")", "", str);
	str = replace("&&", "+", str);
	str = replace("-", "+", str);
	str = replace("//", "+", str);
	str = replace("*", "+", str);
	str = replace("||", "+", str);
	str = replace("%", "+", str);
	operators = count('+', str);
	str = replace("+", " ", str);

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ' && flag)
		{
			operands += 1;
			flag = false;
		}
		if (!flag && str[i] == ' ') flag = true;
	}
	cout << "operands_quantity: " << operands << endl;
	cout << "operators_quantity: " << operators << endl;
	return operands - 1 == operators;
}

int count_operators(string str) {
	int counter = 0;
	int char_num;
	for (int i = 0; i < str.length(); i++)
	{
		char_num = str[i];
		if (is_operator(str[i])) counter++;
	}
	return counter;
}
int count_operands(string str) {
	int counter = 0;
	bool flag = false;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != '+' && str[i] != ' ' && !flag)
		{
			counter++;
			flag = true;
		}
		if (str[i] == '+' || str[i] == ' ')
		{
			flag = false;
		}


	}
	return counter;
}
bool operands_quantity_correct(string chunk_of_code) {
	int operands_quantity = count_operands(chunk_of_code);
	int operators_quantity = count_operators(chunk_of_code);
	// cout << operands_quantity << endl; количество плюсов
	// cout << operators_quantity << endl; количество операндов
	return operands_quantity == operators_quantity + 1;
}

bool check_symbols(string str) {
	int char_num;
	for (int i = 0; i < str.length(); i++)
	{
		char_num = str[i];
		if (char_num_not_valid(char_num)) { cout << "FORBIDDEN CHARCHATER: " << char(char_num) << " ASCII NUMBER: " << char_num << " "; return false; }

	}
	return true;
}
bool check_identifires(string str) {
	int char_num, next_char_num;
	for (int i = 0; i < str.length(); i++)
	{
		char_num = str[i];
		next_char_num = str[i + 1];
		if (identifiers_cant_stay_together(char_num, next_char_num))
		{
			cout << "WRONG IDENTIFIER: " << char(char_num) << char(next_char_num) << endl;
			return false;
		}
	}
	return true;
}
bool check_brackets(string str) {
	int open_brackets_counter = 0;
	int close_brackets_counter = 0;
	int char_num;
	for (int i = 0; i < str.length(); i++) {
		char_num = str[i];
		if (char_num == 40) open_brackets_counter += 1;
		if (char_num == 41) close_brackets_counter += 1;
	}
	return open_brackets_counter == close_brackets_counter;
}
bool check_operators(string str) {
	bool f_str;
	int operands = 0, operations = 0;
	bool fb_operators = there_forbidden_operators(str);
	bool wrng_unary_operators = there_wrong_used_unary_operators(str);
	bool wrng_quantity_oprtrs_oprnds = !operands_quantity_correct(str);

	cout << "there is forbidden operators:" << fb_operators << endl;
	if (fb_operators) return false;
	// TODO: check unary operators
	cout << "there is wrong unary operators:" << wrng_unary_operators << endl;
	if (wrng_unary_operators) return false;

	// TODO: simplify str to operands and binary operations
	// TODO: calculate quantity of operands and operations. If str is correct then operands - 1 == operations
	wrng_quantity_oprtrs_oprnds = simplify(str);
	cout << "there is wrong quantity of operators or operands:" << wrng_unary_operators << endl;
	if (!wrng_quantity_oprtrs_oprnds) return false;

	return true;

}

bool check_statement(string str) {
	return check_symbols(str)
		&& check_identifires(str)
		&& check_brackets(str)
		&& check_operators(str);
}

bool test()
{

	int p1 = 0, p = 19;
	while ((p1++ + 1 + 1) && (p - 1)) p--;
	return true;
}

int main()
{
	bool statement_correct = true;
	string an_array;
	an_array = input();
	cout << an_array << "\n";
	statement_correct = check_identifires(an_array);
	cout << "identifiers: " << statement_correct << endl;
	statement_correct = check_symbols(an_array);
	cout << "symbols: " << statement_correct << endl;
	statement_correct = check_brackets(an_array);
	cout << "brackets: " << statement_correct << endl;
	statement_correct = check_operators(an_array);
	cout << "operators: " << statement_correct << endl;
	
	if (statement_correct) {
		std::cout << "\nStatement correct\n"; 
	}
	else {
		std::cout << "\nStatement incorrect\n";
	}
	test();
}

