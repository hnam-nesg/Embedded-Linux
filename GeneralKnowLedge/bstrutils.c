#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "strutils.h"

void str_reverse(char *s){

	int n = strlen(s);
	for(int i=0; i<n/2; i++){
		int tmp = s[i];
		s[i] = s[n-i-1];
		s[n-i-1] = tmp;
	}
}

void str_trim(char *s){
	int start = 0;
	int end = strlen(s) - 1;
	while(isspace((unsigned char)s[start])) start++;
	while(end >= start && isspace((unsigned char)s[end])) end--;
	s[end+1] = '\0';
	memmove(s, s+start, end - start + 2);
}

int str_to_int(char *s){
	return atoi(s);
}
