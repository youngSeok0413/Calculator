#include "Calcultor.h"

void CalTree::GetInput(const std::string& userInput) {
	input = userInput;
	input.push_back('=');
	std::cout << input << std::endl;
}

void CalTree::UploadInputToTree() {
	for (std::string::iterator iter = input.begin(); iter != input.end(); iter++) {
		AddOperatorNode(iter);
		AddOperandNode(iter);
		AddFormulaNode(iter);
	}
}

void CalTree::AddOperatorNode(std::string::iterator& iter) {
	if (!Impl_WhetherOperand(iter)){
		if (*iter == '(')
			return;
		if (*iter == ')')
			return;
		if (*iter == '=')
			return;
		DataSet ds = DataSet{ TYPE::OPERATOR, *iter, -1, true };
		Impl_AddNewNode(ds);
	}
}

void CalTree::AddOperandNode(std::string::iterator& iter) {
	if (Impl_WhetherOperand(iter)) {
		if (Impl_WhetherOperand(++iter)) {
			Impl_OperandToString(--iter);
		}
		else {
			Impl_OperandToString(--iter);
			DataSet ds = {TYPE::OPERAND, -1, Impl_StringToLongDouble(), true};
			Impl_AddNewNode(ds);
			strToNum.clear();
		}
	}
}

void CalTree::AddFormulaNode(std::string::iterator& iter) {
	Impl_OpenBucket(iter);
	Impl_CloseBucket(iter);
}

void CalTree::PrintAll() {
	Impl_PrintAll(root);
}

void CalTree::Impl_AddNewNode(DataSet& ds){
	Node* newNode = new Node{ ds, location, std::vector<Node*>()};
	location->Next.push_back(newNode);
}

bool CalTree::Impl_WhetherOperand(std::string::iterator& iter) {
	if (*iter == '0')
		return true;
	else if (*iter == '1')
		return true;
	else if (*iter == '2')
		return true;
	else if (*iter == '3')
		return true;
	else if (*iter == '4')
		return true;
	else if (*iter == '5')
		return true;
	else if (*iter == '6')
		return true;
	else if (*iter == '7')
		return true;
	else if (*iter == '8')
		return true;
	else if (*iter == '9')
		return true;
	else if (*iter == '.')
		return true;
	else
		return false;
}

void CalTree::Impl_OperandToString(std::string::iterator& iter){
	strToNum.push_back(*iter);
}

long double CalTree::Impl_StringToLongDouble(){
	const char* str = strToNum.c_str();
	char* end;
	return strtold(str, &end);
}

void CalTree::Impl_OpenBucket(std::string::iterator& iter) {
	if (*iter == '(') {
		DataSet ds = DataSet{TYPE::FORMULA, -1, -1, false};
		Impl_AddNewNode(ds);
		location = location->Next.back();
	}
}

void CalTree::Impl_CloseBucket(std::string::iterator& iter) {
	if (*iter == ')') {
		location = location->Prev;
	}
}

void CalTree::Impl_PrintAll(Node* here) {
	if (!here) {
		std::cout << "Empty" << std::endl;
		return;
	}
	if (here->Next.empty()) {
		if (here->Data.type == TYPE::OPERATOR) {
			std::cout << "Operator : " << here->Data.func << std::endl;
		}
		else if (here->Data.type == TYPE::OPERAND) {
			std::cout << "Operand : " << here->Data.operand << std::endl;
		}
		else if (here->Data.type == TYPE::FORMULA) {
			std::cout << "Formula : " << here->Data.operand << " confirmed : " << (here->Data.confirmed ? "0" : "x") << (here == root ? " root" : "") << std::endl;
		}
	}
	else {
		for (int i = 0; i < here->Next.size(); i++)
			Impl_PrintAll(here->Next[i]);

		if (here->Data.type == TYPE::OPERATOR) {
			std::cout << "Operator : " << here->Data.func << std::endl;
		}
		else if (here->Data.type == TYPE::OPERAND) {
			std::cout << "Operand : " << here->Data.operand << std::endl;
		}
		else if (here->Data.type == TYPE::FORMULA) {
			std::cout << "Formula : " << here->Data.operand << " confirmed : " << (here->Data.confirmed ? "0" : "x") << (here == root ? " root" : "") << std::endl;
		}
	}
}

