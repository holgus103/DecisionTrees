cc -Wall -c DecisionTree.h  DecisionTree.c -ggdb
ar -cvq libDecisionTree.a DecisionTree.o
cc -o Tests.out Tests.c libDecisionTree.a -ggdb
rm DecisionTree.o
