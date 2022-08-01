#include "Calcultor.h"

void CalTree::GetInput(const std::string& userInput) {
	input = userInput;
	input.push_back(' ');
	std::cout << input << std::endl;
}

void CalTree::UploadInputToTree() {
	for (std::string::iterator iter = input.begin(); iter != input.end(); iter++) {
		AddOperatorNode(iter);
	}
}

void CalTree::AddOperatorNode(std::string::iterator& iter) {
	if (!Impl_WhetherOperand(iter)){
		DataSet ds = DataSet{ TYPE::OPERATOR, *iter, -1, true };
		Impl_AddNewNode(ds);
		std::cout << *iter << std::endl;
	}
}

void CalTree::AddOperandNode(std::string::iterator& iter) {
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