#include "Operator.h"

long double Plus(long double a, long double b) {
	return a + b;
}

long double Minus(long double a, long double b){
	return a - b;
}

long double Multiple(long double a, long double b){
	return a * b;
}

long double Division(long double a, long double b){
	return b == 0 ? 0 : a / b;
}