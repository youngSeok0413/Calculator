#pragma once
#include <iostream>
#include <Windows.h>

#include <string>
#include <vector>
#include <stack>

#include "Operator.h"

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
	bool whetherDividedIntoZero;

public:
	CalTree() {
		DataSet dts = {TYPE::FORMULA, -1, -1, false};
		Node* newNode = new Node{dts, nullptr, std::vector<Node*>()};
		root = newNode;
		location = root;
		std::string formula;
		std::string end;

		//calculator 주의 사항을 잘 적어줄 것
		std::cout << 
			"지원하는 연산은 사칙 연산 및 괄호입니다.\n"
			"숫자와 지원하는 연산자, 띄어쓰기, 등호를 제외한 다른 문자를 넣을 경우 계산을 할 수 없습니다.\n"
			"음수 표기 혹은 양수 표기를 지원하지 않습니다. 따라서 음수를 표현 하고자 할 경우 (0-n) 꼴로 표기해주시길 바랍니다.\n"
			<< std::endl;
		std::cout << "수식을 입력하여 주십시오." << std::endl;

		while (1) {
			if (end.size() == 1) {
				if (end.back() == 'q') {
					break;
				}
				else
					end.clear();
			}

			std::cin >> formula;

			GetInput(formula);
			UploadInputToTree();
			ConvertToPostfixFromRoot();
			GetTheResult();
			std::cout << std::endl;
			std::cout << "그만 두시려면 q를 누르고, 그렇지 않으면 아무키나 누르시오. : ";
			std::cin >> end;
			std::cout << std::endl;

			Impl_ClearAll(root);
			root = new Node{ dts, nullptr, std::vector<Node*>() };
			location = root;
			formula.clear();

			Sleep(500);
		}
	}
	void GetInput(const std::string& userInput);

	void UploadInputToTree();
	void AddOperandNode(std::string::iterator& iter);
	void AddOperatorNode(std::string::iterator& iter);
	void AddFormulaNode(std::string::iterator& iter);

	void ConvertToPostfixFromRoot();
	void GetTheResult();
	//void PrintAll();
	//void PrintVector();

private:
	void Impl_FilterInput();
	void Impl_EraseThings(std::string::iterator& iter);
	bool Impl_WhetherWrongOperator(std::string::iterator& iter);
	bool Impl_WhetherBucketsUsedUnProperly(std::stack<char>& stack,std::string::iterator& iter);
	bool Impl_WhetherBucketsUsedUnProperlyFinalCheck(std::stack<char>& stack);
	bool Impl_WhetherOperatorOverlapped(std::string::iterator& iter);
	void Impl_AddEqual();

	void Impl_AddNewNode(DataSet& ds);

	bool Impl_WhetherOperand(std::string::iterator& iter);

	void Impl_OperandToString(std::string::iterator& iter);
	long double Impl_StringToLongDouble();

	void Impl_OpenBucket(std::string::iterator& iter);
	void Impl_CloseBucket(std::string::iterator& iter);

	void Impl_ConvertToPostfix(Node* here);

	void Impl_ConfirmFormula(Node* formNode);

	void Impl_ClearAll(Node* here);
	//void Impl_PrintAll(Node* here);
	//void Impl_PrintVector(std::vector<Node*>& vec);
};