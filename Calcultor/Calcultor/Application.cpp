#include "Calcultor.h"

int main() {
	CalTree cal;
	
	cal.GetInput("1.2+3+(4*5+(6+7))");
	cal.UploadInputToTree();
	cal.PrintAll();

	return 0;
}