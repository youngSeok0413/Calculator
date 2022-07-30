#include "Calcultor.h"

//public
CalTree::CalTree() {
	root = new Node{ {TYPE::FORMULA, -1, 0, false}, nullptr, std::vector<node_addr>()};
	location = root;
}

void CalTree::Input(const std::string& input) {}

void CalTree::OperatorInput(char oper) {
	Impl_OperatorInput(oper);
}

void CalTree::OperandInput(const std::string& operand){
	Impl_OperandInput(operand);
}

void CalTree::FormulaInput(const std::string& formula){}

//private
void CalTree::Impl_OperatorInput(char oper){
	Data data = { TYPE::OPERAND, oper, -1, true };
	node_addr newNode = new node{ data, location, std::vector<node_addr>() };

	location->next.push_back(newNode);
}

void CalTree::Impl_OperandInput(const std::string& operand){
	long double num = Impl_StrToLDouble(operand);

	Data data = { TYPE::OPERAND, -1, num, true };
	node_addr newNode = new node{ data, location, std::vector<node_addr>() };

	location->next.push_back(newNode);
}

long double CalTree::Impl_StrToLDouble(const std::string& operand){
	std::stack<char> stack;
	std::queue<char> queue;

	bool lessThanOne = false;
	long double digit = 1;
	long double num = 0;

	for (int i = 0; i < operand.size(); i++) {
		if (operand[i] == '.') {
			lessThanOne = true;
		}
		else if(lessThanOne){
			queue.push(operand[i] - '0');
		}
		else{
			stack.push(operand[i] - '0');
		}
	}

	while(!stack.empty()){
		num += digit * (long double)stack.top();
		stack.pop();
		digit *= 10;
	}

	digit = 0.1;

	while (!queue.empty()) {
		num += digit * (long double)queue.front();
		queue.pop();
		digit *= 0.1;
	}

	std::cout << num << std::endl;

	return num;
}