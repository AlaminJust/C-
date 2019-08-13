#include<bits/stdc++.h>

using namespace std;
#define ll long long

char text[100];
int min(int a, int b){
	int res = a;
	if(b < a)
		res = b;
	return res;
}

void findLongestPalindromicString(){
    int C = 1 , R = 2 , i = 0 , iMirror , maxLPSLength = 0 , maxLPSCenterPosition = 0 , start = -1 , end = -1 , diff = -1;
	int N = strlen(text);
	if(N == 0)
		return;
	N = 2*N + 1;
	int L[N];
	L[0] = 0;
	L[1] = 1;

	for (i = 2; i < N; i++){
		iMirror = 2*C-i;
		L[i] = 0;
		diff = R - i;

		if(diff > 0)
			L[i] = min(L[iMirror], diff);

		while ( ((i + L[i]) < N && (i - L[i]) > 0) && ( ((i + L[i] + 1) % 2 == 0) || (text[(i + L[i] + 1)/2] == text[(i - L[i] - 1)/2] ))){
			L[i]++;
		}

		if(L[i] > maxLPSLength){
			maxLPSLength = L[i];
			maxLPSCenterPosition = i;
		}

		if (i + L[i] > R){
			C = i;
			R = i + L[i];
		}
	}
	start = (maxLPSCenterPosition - maxLPSLength)/2;
	end = start + maxLPSLength - 1;
	printf("LPS of string is %s : ", text);
	for(i=start; i<=end; i++)
		printf("%c", text[i]);
	printf("\n");
}

int main(int argc, char *argv[])
{

	strcpy(text, "babcbabcbaccba");
	findLongestPalindromicString();

	strcpy(text, "abaaba");
	findLongestPalindromicString();

	strcpy(text, "abababa");
	findLongestPalindromicString();

	strcpy(text, "abcbabcbabcba");
	findLongestPalindromicString();

	strcpy(text, "forgeeksskeegfor");
	findLongestPalindromicString();

	strcpy(text, "caba");
	findLongestPalindromicString();

	strcpy(text, "abacdfgdcaba");
	findLongestPalindromicString();

	strcpy(text, "abacdfgdcabba");
	findLongestPalindromicString();

	strcpy(text, "abacdedcaba");
	findLongestPalindromicString();

	return 0;
}

