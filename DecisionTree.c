#include "DecisionTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

double*** Split(double** elements, int elementsCount, int attributesCount, int classCount){
	double** left, ** right;
	double*** split = malloc(sizeof(double**) * 2);
	int bestIndex, 	i, j, k, leftCount, rightCount;
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
				// split objects by value
				for(k = 0; k < elementsCount; k++){
					if(elements[k][i] > elements[j][i]){
						// element is greater, add to right tree
						right[rightCount] = elements[k];
						rightCount++;
					}
					else{
						left[leftCount] = elements[k];
						leftCount++;
					}						
				}
				// calculate global split gini
				currentGini = CalculateGiniForSet(left, leftCount, classCount) + CalculateGiniForSet(right, rightCount, classCount);
				if(currentGini < bestGini){
					bestGini = currentGini;
					bestSplitValue = elements[j][i];
					bestIndex = i;
				}
			}
	}
	// split using best params
	rightCount = leftCount = 0;
	memset(left, 0, sizeof(double*)*elementsCount);	
	for(k = 0; k < elementsCount; k++){
		if(elements[k][bestIndex] > bestSplitValue){
			// element is greater, add to right tree
			right[rightCount] = elements[k];
			rightCount++;
		}
		else{
			left[leftCount] = elements[k];
			leftCount++;
		}						
	}
	split[0] = left;
	split[1] = right;
	return split;
}
