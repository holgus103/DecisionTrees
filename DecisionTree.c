#include "DecisionTree.h"
#include <stdlib.h>

double CalculateGiniForSet(int* elements, int count, int classes){
	int i, j;
	double result = 0;
	double proportion;
	int* counts = malloc(sizeof(int) * classes); 
	
	// count classes
	for(j = 0; j < classes; j++){
		counts[j] = 0;
		for(i = 0; i < count ; i++){
			if(elements[i] == j){
				counts[j] += 1;
			}
		}
	}
	for(i = 0; i < classes; i++){
		proportion = counts[i]/(double)count;
		result += proportion * (1.0 - proportion);
	}
	free(counts);
	return result;
}



