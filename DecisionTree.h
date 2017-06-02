#ifndef DecisionTrees_H
double CalculateGiniForSet(double** elements, int count, int classes);
double*** Split(double** elements, int elementsCount, int attributesCount, int classCount);
#endif
