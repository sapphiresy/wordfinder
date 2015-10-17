#define _CRT_SECURE_NO_WARNNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 312349 //해싱 테이블의 크기 = 소수

int hash_function(char *key)
{
	unsigned long long int hash_index = 0;
	while (*key)
		hash_index = 31 * hash_index + *key++; // 연산자 우선순위에 의해 key++ (다음문자) 후 key 실행 ++은 후위연산이므로 처음은 그냥뽑아냄

	hash_index = hash_index % TABLE_SIZE;
	return (int)hash_index;
}
void printindex(char* string){
	int hash_idx = hash_function(string);
	printf("%d", hash_idx);
}

int main(void){

	char word[50] = { 0 };
	while (1){
		printf("검색 원하는 단어 입력 : ");
		scanf("%s", word);
		printindex(word);
		printf("\n");
	}

	system("pause");
}