#include <stdio.h>
#include <stdlib.h>
#include "DecisionTree.h"

void displayArray(double** elements, int count, int attributes){
	int i, j;
	// foreach element
	for(i = 0; i < count; i++){
		//foreach attribute 
		for(j = 0; j < attributes + 1; j++){
			if(elements[i] != NULL){
				printf("%f ", elements[i][j]);
			}
		} 
		printf("\n");
	} 
}


int main(){
	double res;
	double element1[] = {0.0, 0.0, 1.0, 2.0};
	double element2[] = {1.0, 1.0, 2.0, 3.0};
	double* arr[] = { element1, element2};
	TreeNode* node = malloc(sizeof(TreeNode));
	res = CalculateGiniForSet(arr, 2, 2);
	printf("Simple test: %s\n", res == 0.5 ? "true" : "false" );
	Split(node, arr, 2, 3, 2);
	printf("left:");
	displayArray(node->left->data, 1, 3);
	printf("right:");
	displayArray(node->right->data, 1, 3);
	free(node);
	
}

