#include "Calcultor.h"
//input function edit needed
//������ �ùٸ���, �ʿ���� ��ȣ Ȥ�� ������ ������, ��︮�� input���� �����ϴ� ������ �ʿ�

int main() {
	CalTree cal;
	cal.GetInput("  1+        2*3");
	cal.UploadInputToTree();
	cal.PrintAll();
	return 0;
}