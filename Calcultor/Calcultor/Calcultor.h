#pragma once
#include <iostream>

#include <string>
#include <vector>

enum TYPE :int {
	OPERATOR = 0,
	OPERAND = 1,
	FORMULA = 2
};

struct DataSet {
	TYPE type;
	char func;
	long double operand;
	bool confirmed;
};

struct Node {
	DataSet Data;
	Node* Prev;
	std::vector<Node*> Next;
};

class CalTree {
private:
	Node* root;
	Node* location;
	std::string input;
	std::string strToNum;
	
public:
	CalTree() {
		DataSet dts = {TYPE::FORMULA, -1, -1, false};
		Node* newNode = new Node{dts, nullptr, std::vector<Node*>()};
		root = newNode;
		location = root;
	}
	void GetInput(const std::string& userInput);

	void UploadInputToTree();
	void AddOperandNode(std::string::iterator& iter);
	void AddOperatorNode(std::string::iterator& iter);
	void AddFormulaNode(std::string::iterator& iter);

	void PrintAll();

private:
	void Impl_AddNewNode(DataSet& ds);

	bool Impl_WhetherOperand(std::string::iterator& iter);

	void Impl_OperandToString(std::string::iterator& iter);
	long double Impl_StringToLongDouble();

	void Impl_OpenBucket(std::string::iterator& iter);
	void Impl_CloseBucket(std::string::iterator& iter);

	void Impl_PrintAll(Node* here);
};