#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 312349 //해싱 테이블의 크기 = 소수

typedef struct ListNode{
   int line_num;
   struct ListNode *link;
}ListNode;

ListNode *hash_table[TABLE_SIZE]; // 전역변수 hash table!




int hash_function(char *key)
{
   unsigned long long int hash_index = 0;
   while (*key)
      hash_index = 31 * hash_index + *key++; // 연산자 우선순위에 의해 key++ (다음문자) 후 key 실행 ++은 후위연산이므로 처음은 그냥뽑아냄

   hash_index = hash_index % TABLE_SIZE;
   return (int)hash_index;
}

void hash_chaining(int hash_idx, int line_num){

   if (hash_table[hash_idx] != NULL){
      ListNode *temp = hash_table[hash_idx];
      ListNode *create_node;
      while (temp->link != NULL){
         temp = temp->link; // 찾은 idx 에서 chaining 하러 올라감
      }

      create_node = (ListNode*)malloc(sizeof(ListNode)); //올라가고 다시 malloc
      create_node->line_num = line_num;
      create_node->link = NULL;
      temp->link = create_node;
   }
   else{
      hash_table[hash_idx] = (ListNode*)malloc(sizeof(ListNode)); //올라가고 다시 malloc
      hash_table[hash_idx]->line_num = line_num;
      hash_table[hash_idx]->link = NULL;
   }
}

void search_hash(char* string){
   int hash_idx = hash_function(string);
   ListNode *temp = hash_table[hash_idx];
   if (hash_table[hash_idx] == NULL){
      printf("문자열에 없는 단어입니다! \n");
      return;
   }
   while (temp->link != NULL){
      printf("%d \n", temp->line_num);
      temp = temp->link;
   }
   printf("%d \n", temp->line_num);
}

void readfile(){
   FILE* fp;
   char* string;
   char buf[256] = { 0 };
   int line_cnt = 1;

   fp = fopen("./book_5MB.txt", "r");
   if (fp == NULL){
      printf("파일이 안보이네요!\n");
      return;
   }
   else{
      while (1){
         if (fgets(buf, 256, fp) == NULL){
            break;
         }
         string = strtok(buf, " ,./<>?`1234567890-=|~/n!@#$%%^&*()_+:;\"'{}[]\\\"");
         while (string != NULL){
            // printf(" %s\n", string);
            // printf(" %d\n", line_cnt);
            hash_chaining(hash_function(string), line_cnt);
            string = strtok(NULL, " ,./<>?`1234567890-=|~/n!@#$%%^&*()_+:;\"'{}[]\\\"");
         }
         line_cnt++;
         printf("현재 %d 줄을 읽고 있습니다. \n", line_cnt);
      }
      fclose(fp);
   }
}


int main(void){
   clock_t start_time, end_time;
   char word[50] = { 0 };
   readfile();
   while (1){
      printf("검색 원하는 단어 입력 : ");
      scanf("%s", word);
      start_time = clock();
      search_hash(word);
      end_time = clock();
      printf("Time : %lf\n",
         ((double)(end_time - start_time)) / CLOCKS_PER_SEC);
      printf("\n");
   }

   system("pause");
}