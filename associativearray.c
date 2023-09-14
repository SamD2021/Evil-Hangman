#include "associativearray.h"
/* #include "GENERIC_VECTOR.c" */
/* #include "my_string.c" */
#include "generic_vector.h"
#include "status.h"
#include <stdio.h>
#include <stdlib.h>

#define MyString_Version 1
#define Generic_version 0

typedef struct node{
    MY_STRING key;
    GENERIC_VECTOR hVector;
    /* int height; */
    struct node* left;
    struct node* right;
}Node;

typedef struct avl{
    Node* root;
}Associative_arr;

int max(int a, int b);
int height(Node* root);
void rotate_right(Node** ppNode);
void rotate_left(Node** ppNode);
int is_balanced(Node* root);
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);
void Tree_destroy(Node* pNode);
void tree_insert(Node **phRoot, MY_STRING hKey, GENERIC_VECTOR hVector);
void tree_print(Node* pNode);
void tree_inorder(Node *pNode);
Status node_destroy(Node *ppRoot);
Node** min_node(Node** ppNode);
Status tree_remove(Node **ppRoot, MY_STRING key);
GENERIC_VECTOR tree_search(Node *root, MY_STRING key);
GENERIC_VECTOR get_max_word_family(Node *pNode, Boolean ShowCheats);
GENERIC_VECTOR get_max_word_family_copy(Node *pNode, Boolean ShowCheats, GENERIC_VECTOR* phMaxVector);

ASSOCIATIVE_ARR associray_init_default(void){
    Associative_arr* pArr = (Associative_arr*)malloc(sizeof(Associative_arr));
    if(pArr == NULL){
        printf("Failed to alloc memory for associray init default");
        return NULL;
    }

    pArr->root = NULL;
    return pArr;
}

//SLR
void associray_insert(ASSOCIATIVE_ARR hArr, MY_STRING hWord, MY_STRING hKey){
    Associative_arr* pArr = (Associative_arr*)hArr;
    tree_insert(&(pArr->root), hKey,hWord);

}
//LRS
void associray_destroy(ASSOCIATIVE_ARR* phArr){
    Associative_arr* pArr = (Associative_arr*) *phArr;
    Tree_destroy(pArr->root);
    free(pArr);
    *phArr = NULL;

}

#if MyString_Version
void tree_insert(Node **phRoot, MY_STRING hKey, MY_STRING hWord) {
    /* int balance = 0; */
    if (*phRoot == NULL) {
        *phRoot = (Node *)malloc(sizeof(Node));
        if (*phRoot == NULL) {
          printf("failed to allocate memory for root node");
          return;
        }
        (*phRoot)->hVector = generic_vector_init_default(my_string_init_copy, my_string_destroy);
        if ((*phRoot)->hVector == NULL) {
          printf("failed to allocate memory for hVector at tree_insert\n");
          return;
        }
        (*phRoot)->key = my_string_init_copy(hKey);
        if ((*phRoot)->key == NULL) {
          printf("failed to allocate memory for key at tree_insert\n");
          return;
        }
        generic_vector_push_back((*phRoot)->hVector, hWord);
        (*phRoot)->left = NULL;
        (*phRoot)->right = NULL;
        /* (*phRoot)->height = 1; */
    } else if (my_string_compare(hKey, (*phRoot)->key) == 0) {
        generic_vector_push_back((*phRoot)->hVector, hWord);
        /* balance = is_balanced(*phRoot); */
    } else if (my_string_compare(hKey, (*phRoot)->key) < 0) {
        tree_insert(&((*phRoot)->left), hKey, hWord);
        /* balance = is_balanced(*phRoot); */
    } else if (my_string_compare(hKey, (*phRoot)->key) > 0) {
        tree_insert(&((*phRoot)->right), hKey, hWord);
        /* balance = is_balanced(*phRoot); */
    }
    /* if (balance > 1 && (my_string_compare(hKey, (*phRoot)->left->key) < 0)) { */
    /*     rotate_right(&(*phRoot)); */
    /* } */
    /* if (balance < -1 && (my_string_compare(hKey, (*phRoot)->right->key) > 0)) { */
    /*     rotate_left(&(*phRoot)); */
    /* } */
    /* if (balance > 1 && (my_string_compare(hKey, (*phRoot)->left->key) > 0)) { */
    /*     rotate_left(&((*phRoot)->left)); */
    /*     rotate_right(&(*phRoot)); */
    /* } */
    /* if (balance < -1 && (my_string_compare(hKey, (*phRoot)->right->key) < 0)) { */
    /*     rotate_right(&((*phRoot)->right)); */
    /*     rotate_left(&(*phRoot)); */
    /* } */
}

void Tree_destroy(Node* pNode){
    if(pNode != NULL){
        Tree_destroy(pNode->left);
        Tree_destroy(pNode->right);
        /* int i; */
        /* for (i = 0; i < pNode->hVector->size; i++) { */
        /*   pNode->hVector->destroy(&pNode->hVector->data[i]); */
        /* } */
        /* free(pNode->hVector->data); */
        /* free(pNode->hVector); */
        generic_vector_destroy(&pNode->hVector);
        my_string_destroy(&pNode->key);
        /* free(pNode->key->data); */
        /* free(pNode->key); */
        free(pNode);
    }
}
#endif
//Helper functions
//
#if Generic_version
void tree_insert(Node **phRoot, MY_STRING hKey, GENERIC_VECTOR hVector) {
    int balance = 0;
    if (*phRoot == NULL) {
        *phRoot = (Node *)malloc(sizeof(Node));
        if (*phRoot == NULL) {
          printf("failed to allocate memory for root node");
          return;
        }
        (*phRoot)->hVector = generic_vector_init_copy(hVector);
        if ((*phRoot)->hVector == NULL) {
          printf("failed to allocate memory for hVector at tree_insert\n");
          return;
        }
        (*phRoot)->key = my_string_init_copy(hKey);
        if ((*phRoot)->key == NULL) {
          printf("failed to allocate memory for key at tree_insert\n");
          return;
        }
        (*phRoot)->left = NULL;
        (*phRoot)->right = NULL;
        /* (*phRoot)->height = 1; */
    } else if (my_string_compare(hKey, (*phRoot)->key) == 0) {
        generic_vector_push_back((*phRoot)->hVector, hVector);
    } else if (my_string_compare(hKey, (*phRoot)->key) < 0) {
        tree_insert(&((*phRoot)->left), hKey, hVector);
        /* balance = is_balanced(*phRoot); */
    } else if (my_string_compare(hKey, (*phRoot)->key) > 0) {
        tree_insert(&((*phRoot)->right), hKey, hVector);
        /* balance = is_balanced(*phRoot); */
    }
    /* if (balance > 1 && (my_string_compare(hKey, (*phRoot)->left->key) < 0)) { */
    /*     rotate_right(&(*phRoot)); */
    /* } */
    /* if (balance < -1 && (my_string_compare(hKey, (*phRoot)->right->key) > 0)) { */
    /*     rotate_left(&(*phRoot)); */
    /* } */
    /* if (balance > 1 && (my_string_compare(hKey, (*phRoot)->left->key) > 0)) { */
    /*     rotate_left(&((*phRoot)->left)); */
    /*     rotate_right(&(*phRoot)); */
    /* } */
    /* if (balance < -1 && (my_string_compare(hKey, (*phRoot)->right->key) < 0)) { */
    /*     rotate_right(&((*phRoot)->right)); */
    /*     rotate_left(&(*phRoot)); */
    /* } */
}

void Tree_destroy(Node* pNode){
    if(pNode != NULL){
        Tree_destroy(pNode->left);
        Tree_destroy(pNode->right);
        /* int i; */
        /* for (i = 0; i < pNode->hVector->size; i++) { */
        /*   pNode->hVector->destroy(&pNode->hVector->data[i]); */
        /* } */
        /* free(pNode->hVector->data); */
        /* free(pNode->hVector); */
        generic_vector_destroy(&pNode->hVector);
        my_string_destroy(&pNode->key);
        /* free(pNode->key->data); */
        /* free(pNode->key); */
        free(pNode);
    }
}
#endif
int height(Node* root){
    if (root == NULL){
        return 0;
    }
    else{
        return 1 + max(height(root->left),height(root->right));
    }
}

int max(int a, int b){
    return (a>b) ? a : b;
}

int is_balanced(Node* root){
    if(root == NULL){
        return 0;
    }else{
        return height(root->left)-height(root->right);
    }
}

void rotate_right(Node** ppNode){
    Node* pNode = *ppNode;
    *ppNode = pNode->left;
    pNode->left = (*ppNode)->right;
    (*ppNode)->right = pNode;
}

void rotate_left(Node** ppNode){
    Node* pNode = *ppNode;
    *ppNode = pNode->right;
    pNode->right = (*ppNode)->left;
    (*ppNode)->left = pNode;
}

GENERIC_VECTOR associray_search(ASSOCIATIVE_ARR hArr, MY_STRING hKey){
    Associative_arr* pArr = (Associative_arr*) hArr;
    MY_STRING* pKey = (MY_STRING*) hKey;
    return tree_search(pArr->root, pKey);
}

GENERIC_VECTOR tree_search(Node *root, MY_STRING key) {
  if (root == NULL)
    return NULL;
  else {
    my_string_insertion(root->key, stdout);
    printf("\n");
    if (my_string_compare(key, root->key) == 0) {
      return root->hVector;
    }

    else if (my_string_compare(key, root->key) < 0)
      tree_search(root->left, key);
    else if (my_string_compare(key, root->key) > 0)
      tree_search(root->right, key);
    return NULL;
  }
}

Status associray_remove(ASSOCIATIVE_ARR hArr, MY_STRING hKey){
    Associative_arr* pArr = (Associative_arr*) hArr;
    MY_STRING* pKey = (MY_STRING*) hKey;
    return tree_remove(&pArr->root, pKey);
}

Status tree_remove(Node **ppRoot, MY_STRING key) {
  Node *temp;
  Node *pRoot = NULL;
  int balance;
  Node **ppMinSuccessor;
  pRoot = *ppRoot;
  if (pRoot == NULL)
    return FAILURE;
  else if (my_string_compare(key, pRoot->key) < 0)
    tree_remove(&pRoot->left, key);
  else if (my_string_compare(key, pRoot->key) > 0)
    tree_remove(&pRoot->right, key);
  else {                                               // has found
    if (pRoot->left == NULL && pRoot->right == NULL) { // No children
      node_destroy(pRoot);
      pRoot = NULL;
    } else if (pRoot->left && pRoot->right) {
      // has two children
      ppMinSuccessor = min_node(&pRoot->right);
      pRoot->hVector = (*ppMinSuccessor)->hVector;
      pRoot->key = (*ppMinSuccessor)->key;
      tree_remove(&pRoot->right, (*ppMinSuccessor)->key);

    } else {
      Node *child = (pRoot->left) ? pRoot->left : pRoot->right;
      Node *curr = pRoot;
      *ppRoot = child;
      node_destroy(curr);
    }
    balance = is_balanced(*ppRoot);
    if (balance > 1 && (my_string_compare(key, (*ppRoot)->left->key) < 0)) {
      rotate_right(&(*ppRoot));
    }
    if (balance < -1 && (my_string_compare(key, (*ppRoot)->right->key) > 0)) {
      rotate_left(&(*ppRoot));
    }
    if (balance > 1 && (my_string_compare(key, (*ppRoot)->left->key) > 0)) {
      rotate_left(&((*ppRoot)->left));
      rotate_right(&(*ppRoot));
    }
    if (balance < -1 && (my_string_compare(key, (*ppRoot)->right->key) < 0)) {
      rotate_right(&((*ppRoot)->right));
      rotate_left(&(*ppRoot));
    }
    return SUCCESS;
  }
  return FAILURE;
}

Status node_destroy(Node *ppRoot) {
  Node *pRoot = ppRoot;
  generic_vector_destroy(&pRoot->hVector);
  my_string_destroy(&pRoot->key);
  free(pRoot);
}

Node** min_node(Node** ppNode) {
    if ((*ppNode)->left == NULL) {
        return ppNode;
    } else {
        return min_node(&(*ppNode)->left);
    }
}
// SLR copy
void associray_print(ASSOCIATIVE_ARR hArr){
    Associative_arr* pArr = (Associative_arr*) hArr;
    tree_print(pArr->root);
}

void tree_print(Node *pNode) {
  if (pNode != NULL) {
    printf("%s\n",my_string_c_str(pNode->key));
    tree_print(pNode->left);
    tree_print(pNode->right);
  }
}

void associray_inorder(ASSOCIATIVE_ARR hArr){
    Associative_arr* pArr = (Associative_arr*) hArr;
    tree_inorder(pArr->root);
}

//LSR
void tree_inorder(Node *pNode) {
  if (pNode != NULL) {
    tree_inorder(pNode->left);
    my_string_insertion(pNode->key, stdout);
    printf("|%d remaining", generic_vector_get_size(pNode->hVector));
    printf("\n");
    tree_inorder(pNode->right);
  }
}

GENERIC_VECTOR associray_init_find_max(ASSOCIATIVE_ARR hArr,
                                       Boolean ShowCheats) {
  int i;
  Associative_arr *pArr = (Associative_arr *)hArr;
  if (pArr->root != NULL) {
    GENERIC_VECTOR newVectorCopy = NULL;
    GENERIC_VECTOR temp = NULL;
    newVectorCopy = generic_vector_init_default(my_string_init_copy, my_string_destroy);
    if (newVectorCopy == NULL) {
      printf("newVectorCopy was null");
      return NULL;
    }
    temp = get_max_word_family_copy(pArr->root, ShowCheats, &pArr->root->hVector);
    if (temp == NULL) {
      printf("Temp was null\n");
      return NULL;
    }
    //copy
    for(i = 0; i < generic_vector_get_size(temp); i++){
      generic_vector_push_back(newVectorCopy, *generic_vector_at(temp, i));
    }
    /* newVectorCopy = generic_vector_init_copy(temp); */
    return newVectorCopy;
  } else {
    printf("root was NULL");
    return NULL;
  }
}

GENERIC_VECTOR get_max_word_family(Node *pNode, Boolean ShowCheats){

  GENERIC_VECTOR phHoldVector = NULL;
  if(pNode != NULL){
    if(pNode->left != NULL){
      phHoldVector = get_max_word_family(pNode->left, ShowCheats);
      if(phHoldVector == NULL || generic_vector_get_size(phHoldVector) < generic_vector_get_size(pNode->hVector))
        phHoldVector = pNode->hVector;
    }
    if(pNode->right != NULL){
      phHoldVector = get_max_word_family(pNode->right, ShowCheats);
      if(phHoldVector == NULL || generic_vector_get_size(phHoldVector) < generic_vector_get_size(pNode->hVector))
        phHoldVector = pNode->hVector;
    }// if both equal null
    if(phHoldVector == NULL || generic_vector_get_size(phHoldVector) < generic_vector_get_size(pNode->hVector))
      phHoldVector = pNode->hVector;
  }
  if(ShowCheats){ // display our cheats or useful for testing
    printf("%s|%d\n",my_string_c_str(pNode->key), generic_vector_get_size(pNode->hVector));
    /* printf("\n"); */
    /* printf("|%d\n", generic_vector_get_size(pNode->hVector)); */
  }
  return phHoldVector;
}

GENERIC_VECTOR get_max_word_family_copy(Node *pNode, Boolean ShowCheats, GENERIC_VECTOR* phMaxVector){
  GENERIC_VECTOR hCurrentMax = NULL;
  if(phMaxVector != NULL)
      hCurrentMax = *phMaxVector;
  //SLR
  if(pNode != NULL){
    if(generic_vector_get_size(hCurrentMax) <= generic_vector_get_size(pNode->hVector))
      hCurrentMax = pNode->hVector;
    if(pNode->left != NULL){
      hCurrentMax = get_max_word_family_copy(pNode->left, ShowCheats, &hCurrentMax);
    }
    if(pNode->right != NULL){
      hCurrentMax = get_max_word_family_copy(pNode->right, ShowCheats, &hCurrentMax);
    }// if both equal null
  }
  if(ShowCheats){ // display our cheats or useful for testing
    printf("%s|%d\n",my_string_c_str(pNode->key), generic_vector_get_size(pNode->hVector));
    /* printf("\n"); */
    /* printf("|%d\n", generic_vector_get_size(pNode->hVector)); */
  }
  return hCurrentMax;
}
