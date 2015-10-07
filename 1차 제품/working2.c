//AVL 트리를 이용한 단어검색기

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

/*	연습을 위한 코드
void print_data(AVL *tree) {
if (tree == NULL) return;
if (tree) {
print_data(tree->left);
printf("%s, %d\n", tree->key, tree->line_num);
print_data(tree->right);
}
}
*/

void search_data(AVL *tree, char *chh) {
	time_t ctime;

	if (tree == NULL) return;
	/* 단어단위 검색
	if (!strcmp((tree)->key, chh)) {
		printf("%s, %d\n", tree->key, tree->line_num);
		search_data(tree->left, chh);
		search_data(tree->right, chh);
	}
	*/

	//패턴단위 검색
	if (NULL != strstr((tree)->key, chh)) {
		printf("%s, %d\n", tree->key, tree->line_num);
		search_data(tree->left, chh);
		search_data(tree->right, chh);
	}

	else {
		search_data(tree->left, chh);
		search_data(tree->right, chh);
	}
}



AVL * text_read() {
	FILE *fp = NULL;
	AVL *tree = NULL;
	char ch, array[50] = { 0 };
	int i = 0;
	fp = fopen("book_50KB.txt", "r");

	printf("Searching text FILE : book_50KB.txt\n");

	while (EOF != (ch = fgetc(fp))) {

		//printf("%c", ch);

		if (('a' <= ch && ch <= 'z') || ('0' <= ch && ch <= '9')) {
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

int main() {
	char chh[50];

	printf("검색하고자 하는 단어 입력 : ");
	gets(chh);
	fflush(stdin);

	search_data(text_read(), chh);

	return 0;
}