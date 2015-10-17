#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)
#define max(a, b)  (((a) > (b)) ? (a) : (b))

int line_num = 1;

struct Node {
	char key[50];
	int line_num;
	struct Node *left;
	struct Node *right;
};
typedef struct Node AVL;

AVL *GetNode() {
	AVL *tmp = (AVL*)malloc(sizeof(AVL));
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}

void add_data(AVL **tree, char *k, int n) {
	if (*tree == NULL) {
		*tree = GetNode();
		strcpy((*tree)->key, k);
		(*tree)->line_num = n;
		return;
	}

	else if ((*tree)->key[0] < k[0]) {
		add_data(&(*tree)->right, k, n);
	}

	else if ((*tree)->key[0] >= k[0]) {
		add_data(&(*tree)->left, k, n);
	}
}

//void print_data(AVL *tree) {
//	if (tree == NULL) return;
//	if (tree) {
//	print_data(tree->left);
//	printf("%s, %d\n", tree->key, tree->line_num);
//	print_data(tree->right);
//	}
//}

void search_data(AVL *tree, char *chh, int op_ls, int op_wp) {

	time_t ctime;

	if (tree == NULL) return;
	
	//word
	if (op_wp == 0) {
		if (!strcmp((tree)->key, chh)) {
			printf("%s, %d\n", tree->key, tree->line_num);
			search_data(tree->left, chh, op_ls, op_wp);
			search_data(tree->right, chh, op_ls, op_wp);
		}
	}
	
	//pattern
	else if (op_wp == 1) {
		if (NULL != strstr((tree)->key, chh)) {
			printf("%s, %d\n", tree->key, tree->line_num);
			search_data(tree->left, chh, op_ls, op_wp);
			search_data(tree->right, chh, op_ls, op_wp);
		}
	}
	else {
		search_data(tree->left, chh, op_ls, op_wp);
		search_data(tree->right, chh, op_ls, op_wp);
	}

}

AVL * text_read() {
	FILE *fp = NULL;
	AVL *tree = NULL;
	char ch, array[50] = { 0 };
	int i = 0;
	fp = fopen("./book_50KB.txt", "r");

	printf("Searching text FILE : book_50KB.txt\n");

	while (EOF != (ch = fgetc(fp))) {

		//printf("%c", ch);

		if ('a' <= ch && ch <= 'z') {
			array[i] = ch;
			i++;
		}

		else if ('A' <= ch && ch <= 'Z') {
			ch += 32;
			array[i] = ch;
			i++;
		}

		else{
			if (i < 3) {
				for (i = 0; i < 50; i++) {
					array[i] = 0;
				}
				i = 0;
			}
			else {
				add_data(&tree, array, line_num);
				for (i = 0; i < 50; i++) {
					array[i] = 0;
				}
				i = 0;
			}

			if (ch == '\n') {
				line_num++;
			}
		}
	}


	fclose(fp);
	return tree;
}

int main(){
	char chh[50];
	int op_ls;
	int op_wp;

	printf("대소문자를 구분하지 않으면 0, 구분하면 1을 입력하시오. ");
	scanf("%d", &op_ls);
	printf("단어단위로 검색하려면 0, 패턴단위로 검색하려면 1을 입력하시오. ");
	scanf("%d", &op_wp);

	printf("검색단어 입력: \n");
	gets(chh);
	//fflush(stdin);
	while( getchar() != '\n' );

	search_data(text_read(), chh, op_ls, op_wp);

	return 0;
}