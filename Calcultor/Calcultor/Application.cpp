#include "Calcultor.h"
//input function edit needed
//수식이 올바른지, 필요없는 기호 혹은 공백이 들어갔는지, 어울리는 input으로 가공하는 과정이 필요 => 했고 
//계층별로 vector list 확인하는 함수 + 실제 연산 들어갈것 + division zero 있는 경우 오류 처리

int main() {
	CalTree cal;
	cal.GetInput(" 1+  ( 4+3)");

	return 0;
}