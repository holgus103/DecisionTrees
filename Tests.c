#include <stdio.h>
#include "DecisionTree.h"

int main(){
	double res;
	double element1[] = {0.0, 0.0, 1.0, 2.0};
	double element2[] = {1.0, 1.0, 2.0, 3.0};
	double* arr[] = { element1, element2};
	double *** split;
	res = CalculateGiniForSet(arr, 2, 2);
	printf("Simple test: %s", res == 0.5 ? "true" : "false" );
	split = Split(arr, 2, 3, 2);
	print("Left %d", sizeof(split[0])
}
