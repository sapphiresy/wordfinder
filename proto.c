#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define MAX_WORD_SIZE 50

int i=0; //Iterator

int max(int a, int b) {return a>b ? a : b;} //height 비교시 사용

/* stack은 필요 없는듯..
// ****** NODE STACK_ START! ******
typedef struct StackNode { //단어 중첩시 line 수를 기억하기 위한 stack
  int item;  //line 수
  struct StackNode *link;
} StackNode;

typedef struct { //top
  StackNode *top;
} LinkedStackType;

void stack_init(LinkedStackType *s){s->top = NULL;}
int stack_is_empty(LinkedStackType *s){return (s->top == NULL);}

void stack_push(LinkedStackType *s, int item){
  StackNode *temp=(StackNode *)malloc(sizeof(StackNode));
  if( temp == NULL ){
    fprintf(stderr, "메모리 할당 에러\n");
    return;
  }else{
    temp->item = item;
    temp->link = s->top;
    s->top = temp;
  }
}

stack_pop(LinkedStackType *s){
  if(stack_is_empty(s)){
    fprintf(stderr, "Stack is empty!\n");
    exit(1);
  }else{
    StackNode *temp = s->top;
    int item = temp->item;
    s->top = s->top->link;
    free(temp);
    return item;
  }
}
// ****** NODE STACK_ END! ******

*/



// ****** Array Linked list START ******
// Tree 안의 Node에 중복된 line number 저장할 LineNode

typedef struct LineNode{
  int data[10]; // line number 저장용
  struct LineNode *link;
} LineNode;

void insert_LineNode(LineNode **phead, LineNode *p, LineNode *new_node){ // head pointer, new node
  if( *phead == NULL){ //공백 리스트인 경우
    new_node->link = NULL;
    *phead = new_node;
  }
  else if(p == NULL){ //p가 NULL 이면 첫 번째 노드로 삽입
    new_node->link = *phead;
    *phead = new_node;
  }
  else{
      new_node->link = p->link;
      p->link = new_node;
  }
}

void display_LineNode(LineNode *head){
  LineNode *p = head;
  while(p != NULL){
    for(i=0 ; i<10 ; i++ ){
      if(data[i]){ // 배열값이 NULL 인지 확인
        printf("%d line\n",p->data[i] );
      }else{break;}
    }
    p = p->link;
  }
  printf("\n");
}

// ******  Array Linked list END******


// ****** TREE NODE_ START! (AVL) ******
typedef struct AvlNode{
  char word[MAX_WORD_SIZE];
  struct TreeNode *left, *right, *LineNode; //single linked list(array[10])
} AvlNode;
//ROTATE Function
AvlNode* rotate_LL(AvlNode *parent){
  AvlNode *child = parent->left_child;
  parent->left_child = child->right_child;
  child->right_child = parent;
  return child;
}

AvlNode* rotate_RR(AvlNode *parent){
  AvlNode *child = parent->right_child;
  parent->right_child = child->left_child;
  child->left_child = parent;
  return child;
}

AvlNode* rotate_RL(AvlNode *parent){
  AvlNode *child = parent->right_child;
  parent->right_child = rotate_LL(child);
  return rotate_RR(parent);
}

AvlNode* rotate_LR(AvlNode *parent){
  AvlNode *child = parent->left_child;
  parent->left_child = rotate_RR(child);
  return rotate_LL(parent);
}

//return height and height different
int get_height(AvlNode *node){
  int height=0;
  if(node != NULL) height = 1 + max(get_height(node->left_child),get_height(node->right_child));
  return height;
}

int get_height_diff(AvlNode *node){
  if (node == NULL) return 0;
  return get_height(node->left_child) - get_height(node->right_child);
}

//balancing
AvlNode* rebalance(AvlNode **node){
  int height_diff = get_height_diff(*node);
  if( height_diff > 1){
    if(get_height_diff((*node)->left_child) > 0)
      *node = rotate_LL(*node);
    else
      *node = rotate_LR(*node);
  }
  else if(height_diff<-1){
    if(get_height_diff((*node)->right_child) < 0)
      *node = rotate_RR(*node);
    else
      *node = rotate_RL(*node);
  }
  return *node;
}

//insertion
AvlNode* avl_add(AvlNode **root, int new_key, int new_linenum ){ //key value 와 line number를 둘다 받음
  if(*root == NULL){
    *root = (AvlNode *)malloc(sizeof(AvlNode));
    if(*root == NULL){
      fprintf(stderr, "메모리 할당 에러\n", );
      exit(1)
    }
    (*root)->data = new_key;
    (*root)->left_child = (*root)->right_child = NULL;
  }

  else if(new_key < (*root)->data){
    (*root)->left_child = avl_add(&((*root)->left_child),new_key);
    *root = rebalance(root);
  }

  else if(new_key > (*root)->data){
    (*root)->right_child = avl_add(&((*root)->right_child),new_key);
    *root = rebalance(root);
  }

  else{
  /*  fprintf(stderr, "중복된 키 에러\n", ); key 중복시 만들어야 할 부분? Tree Node 에 Linked array 쌓는곳으로 보내기! */
    (*root)->LineNode //for문이나 while으로 돌려!

    exit(1)
  }
  return(1);
}

//search
AvlNode* avl_search(AvlNode *node, int key){
  if(node == NULL) return NULL;
  printf("%d", node->data);
  if( key == node->data ) return node;
  else if(key < node->data)
    return avl_search(node->left_child, key);
  else
    return avl_search(node->right_child, key);
}

// ****** TREE NODE_ END! ******

int main (void){

 }
