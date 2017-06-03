cc -Wall -c DecisionTree.c
ar -cvq libDecisionTree.a DecisionTree.o
cc -o Tests.out Tests.c libDecisionTree.a
rm DecisionTree.o
