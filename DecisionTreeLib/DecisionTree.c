#include "DecisionTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEBUG


#ifdef DEBUG
void DisplayArray(
	double** elements,
	int count,
	int attributes
){
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
double CalculateGiniForSet(
	int* labels,
	int count,
	int classes
){
	printf("1");
	int i, j;
	double result = 0	;
	double proportion;
	int* counts = malloc(sizeof(int) * classes);
	// count classes
	for(j = 0; j < classes; j++){
		counts[j] = 0;
		for(i = 0; i < count ; i++){
			if(labels[i] == j){
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

void TrySplit(
	 int index, // index of split attribute
	 int value, // value split by
	 double** elements, // elements for the split
	 int* labels, // element labels
	 int elementsCount, // count of all elements
	 double** left, // output pointer to left array of objects
	 double** right, // output pointer to right array of objects
	 int* leftCount, // output count of left array objects
	 int* rightCount, // output count of right arary objects
 	 int* leftLabels, // left output array labels
 	 int* rightLabels // right output aray labels
 ){
	int k, r = 0, l = 0;
	for(k = 0; k < elementsCount; k++){
		if(elements[k][index] > value){
			// element is greater, add to right tree
			rightLabels[r] = labels[k];
			right[r] = elements[k];
			r++;
		}
		else{
			leftLabels[l] = labels[k];
			left[l] = elements[k];
			l++;
		}
	}
	(*rightCount) = r;
	(*leftCount) = l;
}

void Split(
	TreeNode* node,
	int attributesCount,
	int classCount
){
	#ifdef DEBUG
	//DisplayArray(elements, elementsCount, attributesCount);
	#endif
	double** left, ** right;
	int* leftLabels, * rightLabels;
	int bestIndex, 	i, j,	 leftCount, rightCount;
	double leftGini, rightGini, bestLeftGini, bestRightGini;
	double bestSplitValue, bestGini = 1.0, currentGini;
	left = malloc(sizeof(double*)* node->dataCount);
	right = malloc(sizeof(double*)* node->dataCount);
	leftLabels = malloc(sizeof(int)* node->dataCount);
	rightLabels = malloc(sizeof(int)* node->dataCount);
	// try split for every attribute
	for(i = 1; i < attributesCount + 1; i++){
			// try every attribute value
			for(j = 0; j < node->dataCount; j++){
				// clear left and right
				leftCount = rightCount = 0;
				memset(left, 0, sizeof(double*)*node->dataCount);
				// split objects by valuec
				TrySplit(i, node->data[j][i], node->data, node->classValues, node->dataCount, left, right, &leftCount, &rightCount, leftLabels, rightLabels);
				// calculate global split gini
				leftGini = CalculateGiniForSet(leftLabels, leftCount, classCount);
				rightGini = CalculateGiniForSet(rightLabels, rightCount, classCount);
				currentGini = leftGini + rightGini;
				if(currentGini < bestGini){
					bestGini = currentGini;
					bestLeftGini = leftGini;
					bestRightGini = rightGini;
					bestSplitValue = node->data[j][i];
					bestIndex = i;
				}
			}
	}
	#ifdef DEBUG
	printf("Found best split with attribute: %d, value: %f, Gini: %f\n", bestIndex, bestSplitValue, bestGini);
	#endif
	// split using best params
	rightCount = leftCount = 0;
	memset(left, 0, sizeof(double*)*node->dataCount);
	memset(right, 0, sizeof(double*)*node->dataCount);
	memset(leftLabels, 0, sizeof(double*)*node->dataCount);
	memset(rightLabels, 0, sizeof(double*)*node->dataCount);
	TrySplit(bestIndex, bestSplitValue, node->data, node->classValues, node->dataCount, left, right, &leftCount, &rightCount, leftLabels, rightLabels);
	// release current node
	free(node-> data);
	free(node->classValues);
	node->dataCount = 0;
	node->attributeValue = bestSplitValue;
	node->attributeIndex = bestIndex;
	node->left = malloc(sizeof(TreeNode));
	node->right = malloc(sizeof(TreeNode));
	// fill left node
	node->left->data = left;
	node->left->dataCount = leftCount;
	node->left->classValues = leftLabels;
	// fill right node
	node->right->data = right;
	node->right->dataCount = rightCount;
	node->right->classValues = rightLabels;
	// left node is still not fully separated
	if(bestLeftGini > 0){
		#ifdef DEBUG
		printf("splitting left with gini: %f\n", bestLeftGini);
		#endif
		Split(node->left, attributesCount, classCount);
	}
	// right node is still not fully separated
	if(bestRightGini > 0 && bestRightGini< 1){
		#ifdef DEBUG
		printf("splitting right with gini: %f\n", bestRightGini);
		#endif
		Split(node->right, attributesCount, classCount);
	}

}

void DisposeTree(
	TreeNode* node
){
	if(node == NULL) return;
	DisposeTree(node->left);
	DisposeTree(node->right);
	if(node->data){
		free(node->data);
	}
	free(node);
}
