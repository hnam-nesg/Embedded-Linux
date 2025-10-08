#include <stdio.h>
#include "strutils.h"

int main(){
	
	char text[100] = "   LE HOAI NAM     ";
	
	printf("Chuoi ban dau:%s\n", text);

	str_reverse(text);
	printf("Chuoi dao nguoc:%s\n", text);
	
	str_trim(text);
	printf("Chuoi da cat khoang trang:%s\n", text);

	printf("Chuoi so \"1234\" chuyen thanh so nguyen %d\n",str_to_int("1234"));

	return 0;
}
