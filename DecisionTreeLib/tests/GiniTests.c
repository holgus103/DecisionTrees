/*
 * File:   GiniTests.c
 * Author: holgus103
 *
 * Created on Jul 4, 2017, 2:30:34 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

/*
 * CUnit Test Suite
 */


void PerformTest(double expected, int* data, int count, int classes, char* testName){
	double res = CalculateGiniForSet(data, count, classes);
	printf("%s : %s\n", testName, res == expected ? "passed" : "FAILED" );
	CU_ASSERT_DOUBLE_EQUAL(res, expected, 0);
}


void EqualSplitTest(){
	int arr1[2] = {0, 1};
	PerformTest(0.5, arr1, 2, 2, "EqualSplitTest");
}

void ZeroClassTest(){
	int arr1[] = {0, 0};
	PerformTest(0, arr1, 2, 2, "ZeroClassTest");
}

void OneClassTest(){
	int arr1[] = {1, 1, 1, 1};
	PerformTest(0, arr1, 4, 2, "OneClassTest");
}
//
//void TwoElementsSplitOnLastAttributeTest(){
//	int labels[] = {1, 0};
//	double* arr[2];
//	double row1[] = {0.0, 1.0, 2.0};
//	double row2[] =	{0.0, 1.0, 0.0};
//	arr[0] = row2;
//	arr[1] = row1;
//
//	TreeNode* node = malloc(sizeof(TreeNode));
//	AssertEqualDouble(4, node->attributeIndex, 0, "TwoElementsSplitOnLastAttributeTest");
//	AssertEqualDouble(0, node->left->data == NULL, 0, "TwoElementsSplitOnLastAttributeTest");
//
//}

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test1() {
    CU_ASSERT(2 * 2 == 4);
}

void test2() {
    CU_ASSERT(2 * 2 == 5);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("GiniTests", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "EqualSplitTest", EqualSplitTest)) ||
        (NULL == CU_add_test(pSuite, "ZeroClassTest", ZeroClassTest)) ||
        (NULL == CU_add_test(pSuite, "OneClassTest", OneClassTest))
       ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
