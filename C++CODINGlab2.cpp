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
bool there_pair_operators_and_even_num_of_operands(string str) {
	int char_num;
	int operand_counter = 0;
	bool there_pair_operators = false;
	for (int i = 0; i < str.length(); i++) {
		char_num = str[i];
		if (char(char_num) == '&' || char(char_num) == '=' || char(char_num) == '|') there_pair_operators = true;
		if (char(char_num) == '1') operand_counter++;
	}

	if (operand_counter == 0) return false;
	if (there_pair_operators) return operand_counter % 2 == 0;
	return false; 
}
bool there_unpair_operators_and_even_num_of_operators(string str) {
	int char_num;
	bool there_unpair_operators = false;
	//for (int i = 0; i < str.length(); i++)
	//{
	//	char_num = str[i];
	//	if (char(char_num) == '!') {}
	//}
	return there_unpair_operators;
}

string simplify(string str) {
	bool nothing_added = true;
	int char_num;
	string str_symb, f_str, operand = {"1"};
	for (int i = 0; i < str.length(); i++) {
		char_num = str[i];
		str_symb = str[i];
		if (!is_space(char_num) && !is_bracket(char_num)) {
			if ((is_letter(char_num) || is_number(char_num)) && nothing_added) { f_str.append(operand); nothing_added = false; }
			if (is_operator(char_num))
			{
				if (i!=0 && nothing_added && (str[i-1] != '&' || str[i - 1] != '|')) return {"0"};
				f_str.append(str_symb);
				nothing_added = true;
			}
		}

	}
	cout << f_str << endl;
	return f_str;
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
	string f_str;
	if (there_forbidden_operators(str)) return false;
	

	f_str = simplify(str);
	cout << f_str << endl;
	if (f_str[0] == '0') return false;
	if (!there_pair_operators_and_even_num_of_operands(f_str)) return false;
	//if (!there_unpair_operators_and_even_num_of_operators(f_str)) return false;

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
	while ((+ + p1 + + + + + 1 + 1 == !20) && (- - p - - - 1 == 18)) p--;
	cout << "EXPRESSION IS CORRECT";
	return true;
}

int main()
{
	bool statement_correct = true;
	string an_array;
	an_array = input();
	cout << an_array << "\n";
	//statement_correct = check_statement(an_array);
	std::cout << "identifiers: " << check_identifires(an_array) << endl;
	std::cout << "symbols: " << check_symbols(an_array) << endl;
	std::cout << "brackets: " << check_brackets(an_array) << endl;
	std::cout << "operators: " << check_operators(an_array) << endl;
	
	if (statement_correct) {
		std::cout << "\nStatement correct\n"; 
	}
	else {
		std::cout << "\nStatement incorrect\n";
	}
	test();
}

