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
	double *** split;
	res = CalculateGiniForSet(arr, 2, 2);
	printf("Simple test: %s\n", res == 0.5 ? "true" : "false" );
	split = Split(arr, 2, 3, 2);
	printf("left:");
	displayArray(split[0], 2, 3);
	printf("right:");
	displayArray(split[1], 2, 3);
	
	free(split[0]);
	free(split[1]);
	free(split);
}

