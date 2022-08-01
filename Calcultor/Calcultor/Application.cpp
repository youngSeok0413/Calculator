#include "Calcultor.h"

int main() {
	CalTree cal;
	
	cal.GetInput("++12+424+123-");
	cal.UploadInputToTree();

	return 0;
}