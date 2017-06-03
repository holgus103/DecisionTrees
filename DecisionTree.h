#define DEBUG
#ifndef DecisionTrees_H
typedef struct a {
	double** data;
	int* classValues;
	int attributeIndex;
	double attributeValue;
	struct a* left;
	struct a* right;
} TreeNode;
#ifdef DEBUG
void DisplayArray(double** elements, int count, int attributesCount);
#endif
double CalculateGiniForSet(double** elements, int count, int classes);
void TrySplit(int index, int value, double** elements, int elementsCount, double** left, double** right, int* leftCount, int* rightCount);
void Split(TreeNode* node, double** elements, int elementsCount, int attributesCount, int classCount);
void DisposeTree(TreeNode* node);
#endif
