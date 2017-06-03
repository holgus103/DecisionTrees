#include <stdio.h>
#include <stdlib.h>
#include "DecisionTree.h"


void DisplaySplitValues(TreeNode* node){
	if(node == NULL) return;
	printf("Index: %d Value: %f\n", node->attributeIndex, node->attributeValue);
	DisplaySplitValues(node->left);
	DisplaySplitValues(node->right);
}

int main(){
	double res;
	double element1[] = {1.0, 0.0, 1.0, 2.0};
	double element2[] = {0.0, 0.0, 1.0, 0.0};
	double element3[] = {1.0, 0.0, 1.0, 3.0};
	double element4[] = {0.0, 0.0, 1.0, 4.0};
	double element5[] = {1.0, 1.0, 2.0, 3.0};
	double element6[] = {0.0, 3.0, 1.0, 2.0};
	double element7[] = {0.0, 4.0, 1.0, 2.0};
	double element8[] = {0.0, 5.0, 1.0, 2.0};
	double element9[] = {0.0, 6.0, 1.0, 2.0};
	double element0[] = {1.0, 1.0, 2.0, 4.0};
	double** arr = malloc(sizeof(double*)*10);
	arr[0] = element1;
	arr[1] = element2;
	arr[2] = element3;
	arr[3] = element4;
	arr[4] = element5;
	arr[5] = element6;
	arr[6] = element7;
	arr[7] = element8;
	arr[8] = element9;
	arr[9] = element0;
	TreeNode* node = malloc(sizeof(TreeNode));
	res = CalculateGiniForSet(arr, 2, 2);
	printf("Simple test: %s\n", res == 0.5 ? "true" : "false" );
	Split(node, arr, 10, 3, 2);
	DisplaySplitValues(node);
	DisposeTree(node);
	
}

