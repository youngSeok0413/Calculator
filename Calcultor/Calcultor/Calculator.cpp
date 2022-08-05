#include "Calcultor.h"

//Public Functions
std::string CalTree::GetKeyBoardInput() {
	std::string formula;
	std::getline(std::cin, formula);
	return formula;
}

void CalTree::GetInput(const std::string& userInput) {
	input = userInput;
	Impl_FilterInput();
	std::cout << "User Input : " << input << std::endl;
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

//void CalTree::PrintAll() {
//	Impl_PrintAll(root);
//}
//
//void CalTree::PrintVector() {
//	Impl_PrintVector(root->Next);
//}

void CalTree::ConvertToPostfixFromRoot() {
	Impl_ConvertToPostfix(root);
}

void CalTree::GetTheResult() {
	Impl_ConfirmFormula(root);

	if (whetherDividedIntoZero) {
		std::cout << "Error : Divided int zero" << std::endl;
	}
	else {
		std::cout << "Answer : " << root->Data.operand << std::endl;
	}
}

void CalTree::Initialize() {
	Impl_ClearAll(root);
	DataSet dts = { TYPE::FORMULA, -1, -1, false };
	Node* newNode = new Node{ dts, nullptr, std::vector<Node*>() };
	root = newNode;
	location = root;
}

void CalTree::CalculatorOperating() {
	while (1) {
		GetInput(GetKeyBoardInput());
		UploadInputToTree();
		ConvertToPostfixFromRoot();
		GetTheResult();
		Initialize();

		std::cout << "q를 누르면 종료됩니다. : ";
		if (GetKeyBoardInput() == "q") {
			break;
		}

		std::cout << std::endl;
	}
}

//Impl_Funcitons
//Input 단
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

	if (input.size() < 3) {
		if (*(input.begin()) == '+')
			input.insert(input.begin(), '0');
		if (*(input.begin()) == '-')
			input.insert(input.begin(), '0');
	}
	else {
		bool whehterCloseToggle = false;
		for (std::string::iterator iter = input.begin(); iter != input.end(); iter++) {
			if (iter == input.begin()) {
				if (*iter == '+') {
					input.insert(iter, '0');
					input.insert(iter, '(');
					iter = iter + 2;
					whehterCloseToggle = true;
				}
				else if (*iter == '-') {
					input.insert(iter, '0');
					input.insert(iter, '(');
					iter = iter + 2;
					whehterCloseToggle = true;
				}
			}
			else if (iter == input.end() - 1) {
				if (whehterCloseToggle) {
					input.push_back(')');
					whehterCloseToggle = false;
				}
			}
			else {
				if (!Impl_WhetherOperand(iter)) {
					if (whehterCloseToggle) {
						input.insert(iter, ')');
						whehterCloseToggle = false;
						iter++;
					}
					else {
						if (*iter == '+') {
							std::string::iterator p = iter - 1;
							std::string::iterator n = iter + 1;
							if (!Impl_WhetherOperand(p) && (*p != ')')) {
								if (Impl_WhetherOperand(n)) {
									input.insert(iter, '0');
									input.insert(iter, '(');
									iter = iter + 2;
									whehterCloseToggle = true;
								}
							}
						}
						else if (*iter == '-') {
							std::string::iterator p = iter - 1;
							std::string::iterator n = iter + 1;
							if (!Impl_WhetherOperand(p) && (*p != ')')) {
								if (Impl_WhetherOperand(n)) {
									input.insert(iter, '0');
									input.insert(iter, '(');
									iter = iter + 2;
									whehterCloseToggle = true;
								}
							}
						}
					}
				}
			}
		}
	}

	Impl_AddEqual();
}

//iterator가 리스트가 줄어들면서 iter 변하는 것 고려
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
		std::string::iterator n = iter + 1;

		if (Impl_WhetherOperand(iter));
		else if ('+'){
			if (!Impl_WhetherOperand(n))
				return true;
		}
		else if ('-'){
			if (!Impl_WhetherOperand(n))
				return true;
		}
		else if (*iter == '(') {
			if (*n == ')')
				return true;
		}
		else return true;
	}
	else if(iter == input.end()-1) {
		std::string::iterator p = iter - 1;

		if (Impl_WhetherOperand(iter));
		else if (*iter == ')') {
			if (*p == '(')
				return true;
		}
		else return true;
	}
	else {
		if (*iter == '+') {
			std::string::iterator n = iter + 1;

			if (*n == '(');
			else if (*n == '+');
			else if (*n == '-');
			else if (Impl_WhetherOperand(n));
			else return true;
		}
		else if (*iter == '-') {
			std::string::iterator n = iter + 1;

			if (*n == '(');
			else if (*n == '+');
			else if (*n == '-');
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
			else if (*n == '+');
			else if (*n == '-');
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
			else if (*n == '+');
			else if (*n == '-');
			else if (Impl_WhetherOperand(n));
			else return true;
		}
		else if (*iter == '(') {
			std::string::iterator p = iter - 1;
			std::string::iterator n = iter + 1;

			if (Impl_WhetherOperand(p))
				return true;

			if (*n == '(');
			else if (*n == '+');
			else if (*n == '-');
			else if (Impl_WhetherOperand(n));
			else return true;
		}
		else if (*iter == ')') {
			std::string::iterator p = iter - 1;
			std::string::iterator n = iter + 1;

			if (*p == ')');
			if (Impl_WhetherOperand(p));
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

//Tree단
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
	if (!here) {
		return;
	}
	else if (here->Next.empty()) {
		return;
	}
	else {
		std::stack<Node*> stack;
		std::vector<Node*> sorted;

		for (std::vector<Node*>::iterator iter = here->Next.begin(); iter != here->Next.end(); iter++) {
			if((*iter)->Data.type == TYPE::OPERAND){
				Node* it = *iter;
				sorted.push_back(it);
			}
			else if ((*iter)->Data.type == TYPE::OPERATOR) {
				if ((*iter)->Data.func == '+') {
					while (!stack.empty()) {
						sorted.push_back(stack.top());
						stack.pop();
					}
					stack.push(*iter);
				}
				else if ((*iter)->Data.func == '-') {
					while (!stack.empty()) {
						sorted.push_back(stack.top());
						stack.pop();
					}
					stack.push(*iter);
				}
				else if ((*iter)->Data.func == '*') {
					if (!stack.empty()) {
						if (stack.top()->Data.func == '+') {
							stack.push(*iter);
						}
						else if (stack.top()->Data.func == '-') {
							stack.push(*iter);
						}
						else if (stack.top()->Data.func == '*') {
							while (!stack.empty()) {
								sorted.push_back(stack.top());
								stack.pop();
							}
							stack.push(*iter);
						}
						else if (stack.top()->Data.func == '/') {
							while (!stack.empty()) {
								sorted.push_back(stack.top());
								stack.pop();
							}
							stack.push(*iter);
						}
					}
					else {
						stack.push(*iter);
					}
				}
				else if ((*iter)->Data.func == '/') {
					if (!stack.empty()) {
						if (stack.top()->Data.func == '+') {
							stack.push(*iter);
						}
						else if (stack.top()->Data.func == '-') {
							stack.push(*iter);
						}
						else if (stack.top()->Data.func == '*') {
							while (!stack.empty()) {
								sorted.push_back(stack.top());
								stack.pop();
							}
							stack.push(*iter);
						}
						else if (stack.top()->Data.func == '/') {
							while (!stack.empty()) {
								sorted.push_back(stack.top());
								stack.pop();
							}
							stack.push(*iter);
						}
					}
					else {
						stack.push(*iter);
					}
				}
			}
			else if ((*iter)->Data.type == TYPE::FORMULA) {
				Impl_ConvertToPostfix(*iter);
				Node* it = *iter;
				sorted.push_back(it);
			}
		}

		while (!stack.empty()) {
			sorted.push_back(stack.top());
			stack.pop();
		}

		here->Next.clear();
		here->Next.assign(sorted.begin(), sorted.end());
	}
}

void CalTree::Impl_ConfirmFormula(Node* formNode){
	if (!formNode) {
		return;
	}
	else if (formNode->Data.type == TYPE::FORMULA) {
		if (!(formNode->Data.confirmed)) {
			if (formNode->Next.empty()) {
				formNode->Data.operand = 0;
				formNode->Data.confirmed = true;
			}
			else {
				std::stack<long double> stack;

				for (std::vector<Node*>::iterator iter = formNode->Next.begin(); iter != formNode->Next.end(); iter++) {
					if ((*iter)->Data.type == TYPE::OPERAND) {
						stack.push((*iter)->Data.operand);
					}
					else if((*iter)->Data.type == TYPE::OPERATOR){
						if ((*iter)->Data.func == '+') {
							long double b = stack.top();
							stack.pop();
							long double a = stack.top();
							stack.pop();
							stack.push(Plus(a,b));
						}
						else if ((*iter)->Data.func == '-') {
							long double b = stack.top();
							stack.pop();
							long double a = stack.top();
							stack.pop();
							stack.push(Minus(a, b));
						}
						else if ((*iter)->Data.func == '*') {
							long double b = stack.top();
							stack.pop();
							long double a = stack.top();
							stack.pop();
							stack.push(Multiple(a, b));
						}
						else if ((*iter)->Data.func == '/') {
							long double b = stack.top();
							stack.pop();
							long double a = stack.top();
							stack.pop();
							stack.push(Division(a, b));
							if (stack.top() == 0) {
								whetherDividedIntoZero = true;
							}
						}
					}
					else if((*iter)->Data.type == TYPE::FORMULA) {
						if (!((*iter)->Data.confirmed))
							Impl_ConfirmFormula(*iter);
						stack.push((*iter)->Data.operand);
					}
				}

				formNode->Data.operand = stack.top();
				formNode->Data.confirmed = true;
			}
		}
	}
}

void CalTree::Impl_ClearAll(Node* here) {
	if (!here) {
		return;
	}
	if(here->Next.empty()){
		delete here;
	}
	else {
		for (std::vector<Node*>::iterator iter = here->Next.begin(); 
			iter != here->Next.end(); iter++) {
			if ((*iter)->Data.type == TYPE::FORMULA)
				Impl_ClearAll(*iter);
			else
				delete* iter;
		}

		delete here;
	}
}

//void CalTree::Impl_PrintAll(Node* here) {
//	if (!here) {
//		std::cout << "Empty" << std::endl;
//		return;
//	}
//	if (here->Next.empty()) {
//		if (here->Data.type == TYPE::OPERATOR) {
//			std::cout << "Operator : " << here->Data.func << std::endl;
//		}
//		else if (here->Data.type == TYPE::OPERAND) {
//			std::cout << "Operand : " << here->Data.operand << std::endl;
//		}
//		else if (here->Data.type == TYPE::FORMULA) {
//			std::cout << "Formula : " << here->Data.operand << " confirmed : " << (here->Data.confirmed ? "0" : "x") << (here == root ? " root" : "") << std::endl;
//		}
//	}
//	else {
//		for (int i = 0; i < here->Next.size(); i++)
//			Impl_PrintAll(here->Next[i]);
//
//		if (here->Data.type == TYPE::OPERATOR) {
//			std::cout << "Operator : " << here->Data.func << std::endl;
//		}
//		else if (here->Data.type == TYPE::OPERAND) {
//			std::cout << "Operand : " << here->Data.operand << std::endl;
//		}
//		else if (here->Data.type == TYPE::FORMULA) {
//			std::cout << "Formula : " << here->Data.operand << " confirmed : " << (here->Data.confirmed ? "0" : "x") << (here == root ? " root" : "") << std::endl;
//		}
//	}
//}
//
//void CalTree::Impl_PrintVector(std::vector<Node*>& vec) {
//	for (std::vector<Node*>::iterator iter = vec.begin(); iter < vec.end(); iter++) {
//		if ((*iter)->Data.type == TYPE::OPERATOR) {
//			std::cout << "Operator : " << (*iter)->Data.func << std::endl;
//		}
//		else if ((*iter)->Data.type == TYPE::OPERAND) {
//			std::cout << "Operand : " << (*iter)->Data.operand << std::endl;
//		}
//		else if ((*iter)->Data.type == TYPE::FORMULA) {
//			std::cout << "Formula : " << (*iter)->Data.operand << " confirmed : " << ((*iter)->Data.confirmed ? "0" : "x") << std::endl;
//		}
//	}
//}

