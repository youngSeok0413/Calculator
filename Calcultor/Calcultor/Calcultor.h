#pragma once
#include <string>
#include <vector>
#include <stack>
#include <queue>

#include <algorithm>

#include <iostream>

enum TYPE :int {
	OPERAND = 0,
	OPERATOR = 1,
	FORMULA = -1
};

struct Data {
	TYPE type;
	char func;
	long double op;
	bool whetherResultOut;
};

struct Node {
	Data data;
	Node* prev;
	std::vector<Node*> next;
};

class CalTree{

private:
	using node = Node;
	using node_addr = Node*;

private:
	node_addr root;
	node_addr location;
public:
	CalTree();

	void Input(const std::string& input);
	void OperatorInput(const char oper);
	void OperandInput(const std::string& operand);
	void FormulaInput(const std::string& formula);

private:
	void Impl_OperatorInput(char oper);
	void Impl_OperandInput(const std::string& operand);

	long double Impl_StrToLDouble(const std::string& operand);
};