#include "Calcultor.h"

//Public Functions
void CalTree::GetInput(const std::string& userInput) {
	input = userInput;
	std::cout << input << std::endl;
	Impl_FilterInput();
	std::cout << input << std::endl;
}

void CalTree::UploadInputToTree() {
	if (input.empty()) {
		std::cout << "No user input" << std::endl;
		return;
	}

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

void CalTree::ConvertToPostfixFromRoot() {
	Impl_ConvertToPostfix(root);
}

//Impl_Funcitons
//Input ��
void CalTree::Impl_FilterInput() {
	std::stack<char> stack;

	for (std::string::iterator iter = input.begin(); iter != input.end(); iter++) {
		if (Impl_WhetherWrongOperator(iter)) {
			std::cout << "User input has problem : not defined operator" << std::endl;
			input.clear();
			return;
		}

		if(Impl_WhetherBucketsUsedUnProperly(stack, iter)) {
			std::cout << "User input has problem : Bucket used unproperly" << std::endl;
			input.clear();
			return;
		}

	}
	
	if (Impl_WhetherBucketsUsedUnProperlyFinalCheck(stack)) {
		std::cout << "User input has problem : Bucket used unproperly" << std::endl;
		input.clear();
		return;
	}

	input.push_back(' ');
	for (std::string::iterator iter = input.begin(); iter != input.end();)
		Impl_EraseThings(iter);

	for (std::string::iterator iter = input.begin(); iter != input.end(); iter++) {
		if (Impl_WhetherOperatorOverlapped(iter)) {
			std::cout << "User input has problem : Operators are overlapped" << std::endl;
			input.clear();
			return;
		}
	}

	Impl_AddEqual();
}

//iterator�� ����Ʈ�� �پ��鼭 iter ���ϴ� �� ���
void CalTree::Impl_EraseThings(std::string::iterator& iter) {
	if (*iter == ' ') {
		input.erase(iter);
	}
	else if (*iter == '=') {
		input.erase(iter);
	}
	else {
		iter++;
	}
}

bool CalTree::Impl_WhetherWrongOperator(std::string::iterator& iter) {
	if (!Impl_WhetherOperand(iter)) {
		for (int i = 0; i < sizeof(OperatorType); i++)
			if (*iter == OperatorType[i])
				return false;
		return true;
	}
	return false;
}

bool CalTree::Impl_WhetherBucketsUsedUnProperly(std::stack<char>& stack, std::string::iterator& iter) {
	if (*iter == '(') {
		stack.push(*iter);
	}
	else if (*iter == ')') {
		if(!stack.empty()){
			if (stack.top() == '(')
				stack.pop();
		}
		else {
			stack.push(*iter);
		}
	}
	
	if (!stack.empty()) {
		if (stack.top() == ')')
			return true;
	}
		
	return false;
}

bool CalTree::Impl_WhetherBucketsUsedUnProperlyFinalCheck(std::stack<char>& stack) {
	if (stack.empty())
		return false;
	else 
		return true;
}

bool CalTree::Impl_WhetherOperatorOverlapped(std::string::iterator& iter) {
	if (iter == input.begin()) {
		if (Impl_WhetherOperand(iter));
		else if (*iter == '(');
		else return true;
	}
	else if(iter == input.end()-1) {
		if (Impl_WhetherOperand(iter));
		else if (*iter == ')');
		else return true;
	}
	else {
		if (*iter == '+') {
			std::string::iterator p = iter - 1;
			std::string::iterator n = iter + 1;

			if (*p == ')');
			else if (Impl_WhetherOperand(p));
			else return true;

			if (*n == '(');
			else if (Impl_WhetherOperand(n));
			else return true;
		}
		else if (*iter == '-') {
			std::string::iterator p = iter - 1;
			std::string::iterator n = iter + 1;

			if (*p == ')');
			else if (Impl_WhetherOperand(p));
			else return true;

			if (*n == '(');
			else if (Impl_WhetherOperand(n));
			else return true;
		}
		else if (*iter == '*') {
			std::string::iterator p = iter - 1;
			std::string::iterator n = iter + 1;

			if (*p == ')');
			else if (Impl_WhetherOperand(p));
			else return true;

			if (*n == '(');
			else if (Impl_WhetherOperand(n));
			else return true;
		}
		else if (*iter == '/') {
			std::string::iterator p = iter - 1;
			std::string::iterator n = iter + 1;

			if (*p == ')');
			else if (Impl_WhetherOperand(p));
			else return true;

			if (*n == '(');
			else if (Impl_WhetherOperand(n));
			else return true;
		}
		else if (*iter == '(') {
			std::string::iterator p = iter - 1;
			std::string::iterator n = iter + 1;

			if (Impl_WhetherOperand(p))
				return true;

			if (*n == '(');
			else if (Impl_WhetherOperand(n));
			else return true;
		}
		else if (*iter == ')') {
			std::string::iterator p = iter - 1;
			std::string::iterator n = iter + 1;

			if (*n == ')');
			else if (Impl_WhetherOperand(n));
			else return true;

			if (Impl_WhetherOperand(n))
				return true;
		}
	}

	return false;
}

void CalTree::Impl_AddEqual() {
	input.push_back('=');
}

//Tree��
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

void CalTree::Impl_ConvertToPostfix(Node* here) {
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

