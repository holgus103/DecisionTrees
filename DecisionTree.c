#include "DecisionTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#define DEBUG


#ifdef DEBUG
void DisplayArray(double** elements, int count, int attributes){
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
#endif
double CalculateGiniForSet(double** elements, int count, int classes){
	int i, j;
	double result = 0;
	double proportion;
	int* counts = malloc(sizeof(int) * classes); 
	
	// count classes
	for(j = 0; j < classes; j++){
		counts[j] = 0;
		for(i = 0; i < count ; i++){
			if(elements[i][0] == j){
				counts[j] += 1;
			}
		}
	}
	// calculate and sum up all Gini values
	for(i = 0; i < classes; i++){
		proportion = counts[i]/(double)count;
		result += proportion * (1.0 - proportion);
	}
	free(counts);
	return result;
}

void TrySplit(int index, int value, double** elements, int elementsCount, double** left, double** right, int* leftCount, int* rightCount){
	int k;
	for(k = 0; k < elementsCount; k++){
		if(elements[k][index] > value){
			// element is greater, add to right tree
			right[(*rightCount)] = elements[k];
			(*rightCount)++;
		}
		else{
			left[(*leftCount)] = elements[k];
			(*leftCount)++;
		}						
	}
}

void Split(TreeNode* node, double** elements, int elementsCount, int attributesCount, int classCount){
	#ifdef DEBUG
	//DisplayArray(elements, elementsCount, attributesCount);
	#endif
	double** left, ** right;
	int bestIndex, 	i, j, k, leftCount, rightCount;
	double leftGini, rightGini, bestLeftGini, bestRightGini;
	double bestSplitValue, bestGini = 1.0, currentGini;
	left = malloc(sizeof(double*)* elementsCount);
	right = malloc(sizeof(double*)* elementsCount);
	// try split for every attribute
	for(i = 1; i < attributesCount + 1; i++){
			// try every attribute value
			for(j = 0; j < elementsCount; j++){
				// clear left and right
				leftCount = rightCount = 0;
				memset(left, 0, sizeof(double*)*elementsCount);
				// split objects by valuec
				TrySplit(i, elements[j][i], elements, elementsCount, left, right, &leftCount, &rightCount);
				// calculate global split gini
				leftGini = CalculateGiniForSet(left, leftCount, classCount);
				rightGini = CalculateGiniForSet(right, rightCount, classCount);
				currentGini = leftGini + rightGini;
				if(currentGini < bestGini){
					bestGini = currentGini;
					bestLeftGini = leftGini;
					bestRightGini = rightGini;
					bestSplitValue = elements[j][i];
					bestIndex = i;
				}
			}
	}
	#ifdef DEBUG
	printf("Found best split with attribute: %d, value: %f, Gini: %f\n", bestIndex, bestSplitValue, bestGini); 
	#endif
	// split using best params
	rightCount = leftCount = 0;
	memset(left, 0, sizeof(double*)*elementsCount);	
	TrySplit(bestIndex, bestSplitValue, elements, elementsCount, left, right, &leftCount, &rightCount);
	free(elements);
	node->attributeValue = bestSplitValue;
	node->attributeIndex = bestIndex;
	node->left = malloc(sizeof(TreeNode));
	node->right = malloc(sizeof(TreeNode));
	// left node
	if(bestLeftGini > 0 && bestLeftGini< 1){
		#ifdef DEBUG
		printf("splitting left with gini: %f\n", bestLeftGini);
		#endif
		Split(node->left, left, leftCount, attributesCount, classCount); 
	}
	else{
		// no recurrency will be triggered so save the result
		node->left->data = left;
	}
	// right node
	if(bestRightGini > 0 && bestRightGini< 1){
		#ifdef DEBUG
		printf("splitting right with gini: %f\n", bestRightGini);
		#endif
		Split(node->right, right, leftCount, attributesCount, classCount); 
	}
	else{
		// no recurrency will be triggered so save the result
		node-> right->data = right;
	}
}

void DisposeTree(TreeNode* node){
	if(node == NULL) return;
	DisposeTree(node->left);
	DisposeTree(node->right);
	if(node->data){
		free(node->data);
	}
	free(node);
}

