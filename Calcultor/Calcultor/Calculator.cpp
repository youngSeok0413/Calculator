#include "Calcultor.h"

//public
CalTree::CalTree() {
	root = new Node{ {TYPE::FORMULA, -1, 0, false}, nullptr, std::vector<node_addr>()};
	location = root;
}

void CalTree::FormulaInput(const std::string& formula) {
}

void CalTree::OperatorInput(char oper) {
	Impl_OperatorInput(root, oper);
}

void CalTree::OperandInput(const std::string& operand){
	Impl_OperandInput(root, operand);
}

//private
void CalTree::Impl_OperatorInput(node_addr nowLoc, char oper){
	Data data = { TYPE::OPERAND, oper, -1, true };
	node_addr newNode = new node{ data, nowLoc, std::vector<node_addr>() };

	location->next.push_back(newNode);
}

void CalTree::Impl_OperandInput(node_addr nowLoc, const std::string& operand){
	long double num = Impl_StrToLDouble(operand);

	Data data = { TYPE::OPERAND, -1, num, true };
	node_addr newNode = new node{ data, nowLoc, std::vector<node_addr>() };

	location->next.push_back(newNode);
}

long double CalTree::Impl_StrToLDouble(const std::string& operand) {
	const char* str = operand.c_str();
	char* endPtr;
	long double num = strtold(str, &endPtr);
	std::cout << num << std::endl;
	return num;
}

void CalTree::Impl_FormulaInput(node_addr nowLoc, const std::string& formula) {
	Data data = {TYPE::FORMULA, -1, -1, false};
	node_addr newNode = new node{data, nowLoc, std::vector<node_addr>()};
}

