#define DEBUG
#ifndef DecisionTrees_H
typedef struct a {
	double** data;
	int dataCount;
	int* classValues;
	int attributeIndex;
	double attributeValue;
	struct a* left;
	struct a* right;
} TreeNode;
#ifdef DEBUG
void DisplayArray(
	double** elements,
	int count,
	int attributesCount
);

#endif
double CalculateGiniForSet(
	int* labels,
	int count,
	int classes
);
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
);

void Split(
	TreeNode* node,
	int attributesCount,
	int classCount
);

void DisposeTree(
	TreeNode* node
);
#endif
