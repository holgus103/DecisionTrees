#include <stdio.h>
#include "DecisionTree.h"

int main(){
	double res;
	int arr[] = {0, 1};
	res = CalculateGiniForSet(arr, 2, 2);
	printf("Simple test: %s", res == 0.5 ? "true" : "false" );
}
