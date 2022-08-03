#pragma once

const char OperatorType[] = {
	'+', //add
	'-', //minus
	'/',//division
	'*',//multiple
	'=', //equal
	' ', //space 
	'(', //head bucket
	')' //tail bucket
};

//operator : postfix sorted(b = first pop, a = second pop)
long double Plus(long double a, long double b);
long double Minus(long double a, long double b);
long double Multiple(long double a, long double b);
long double Division(long double a, long double b);