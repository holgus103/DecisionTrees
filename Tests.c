#include <stdio.h>
#include "DecisionTree.h"

int main(){
	double res;
	int element1[] = {0, 0, 1, 2};
	int element2[] = {1, 1, 2, 3};
	int* arr[] = { element1, element2};
	res = CalculateGiniForSet(arr, 2, 2);
	printf("Simple test: %s", res == 0.5 ? "true" : "false" );
}
