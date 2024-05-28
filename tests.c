#include "tests.h"
#include "lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

bool example_test() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a))
    ASSERT_CC_OK(cc_array_add(a, (void*) 1))
    ASSERT_EQ(1, cc_array_size(a))
    void *get_result;
    ASSERT_CC_OK(cc_array_get_at(a, 0, &get_result))
    ASSERT_EQ(1, (int) get_result);
    ASSERT_EQ(cc_array_get_at(a,1,&get_result), CC_ERR_OUT_OF_RANGE);
    ASSERT_EQ(cc_array_get_at(a, 2, &get_result), CC_ERR_OUT_OF_RANGE);

    cc_array_destroy(a);
    return true;
}

bool cc_array_get_last_test(){
    CC_Array* a;
    cc_array_new(&a);
    ASSERT_EQ(0,cc_array_size(a));
    void* get_result;
    ASSERT_EQ(CC_ERR_VALUE_NOT_FOUND,cc_array_get_last(a, &get_result));

    cc_array_add(a,(void*)1);
    cc_array_get_last(a,&get_result);
    ASSERT_EQ(1,(int)get_result);


    cc_array_add(a,(void*)2);
    cc_array_get_last(a,&get_result);
    ASSERT_EQ(2, (int)get_result);


    return true;
}

bool cc_array_replace_at_test(){
    CC_Array* a;
    cc_array_new(&a);
    cc_array_add(a,(void*)1);
    ASSERT_EQ(CC_ERR_OUT_OF_RANGE,cc_array_replace_at(a,(void*)1,2,NULL)); 
}

bool cc_array_replace_at_test2(){
    CC_Array* a;
    cc_array_new(&a);
    cc_array_add(a,(void*)1);
    ASSERT_EQ(CC_ERR_OUT_OF_RANGE,cc_array_replace_at(a,(void*)1,1,NULL)); 
}

bool cc_array_add_at_greater(){
    CC_Array* a;
    cc_array_new(&a);
    ASSERT_EQ(CC_ERR_OUT_OF_RANGE,cc_array_add_at(a,(void*)1,1));
}

bool cc_array_add_at_eq(){
    CC_Array* a;
    cc_array_new(&a);
    ASSERT_EQ(CC_ERR_OUT_OF_RANGE,cc_array_add_at(a,(void*)1,0));
}

bool cc_array_add_full_capacity_test() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));

    for (int i = 1; i <= 10; i++) {
        ASSERT_CC_OK(cc_array_add(a, (void*)(intptr_t)i));
    }
    ASSERT_EQ(10, cc_array_size(a));

    ASSERT_CC_OK(cc_array_add(a, (void*)11));
    ASSERT_EQ(11, cc_array_size(a));
    void* get_result;
    ASSERT_CC_OK(cc_array_get_at(a, 10, &get_result));
    ASSERT_EQ(11, (int)(intptr_t)get_result);

    cc_array_destroy(a);
    return true;
}

bool cc_array_add_after_expand_test() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));

    for (int i = 1; i <= 15; i++) {
        ASSERT_CC_OK(cc_array_add(a, (void*)(intptr_t)i));
    }
    ASSERT_EQ(15, cc_array_size(a));
    void* get_result;
    for (int i = 0; i < 15; i++) {
        ASSERT_CC_OK(cc_array_get_at(a, i, &get_result));
        ASSERT_EQ(i + 1, (int)(intptr_t)get_result);
    }

    cc_array_destroy(a);
    return true;
}

bool cc_array_swap_within_bounds_test() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));

    for (int i = 1; i <= 5; i++) {
        ASSERT_CC_OK(cc_array_add(a, (void*)(intptr_t)i));
    }

    ASSERT_EQ(CC_OK, cc_array_swap_at(a, 1, 3));

    void* get_result;
    ASSERT_CC_OK(cc_array_get_at(a, 1, &get_result));
    ASSERT_EQ(4, (intptr_t)get_result);
    ASSERT_CC_OK(cc_array_get_at(a, 3, &get_result));
    ASSERT_EQ(2, (intptr_t)get_result);

    cc_array_destroy(a);
    return true;
}

bool cc_array_swap_out_of_bounds_lower_test() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));

    for (int i = 1; i <= 5; i++) {
        ASSERT_CC_OK(cc_array_add(a, (void*)(intptr_t)i));
    }

    ASSERT_EQ(CC_ERR_OUT_OF_RANGE, cc_array_swap_at(a, -1, 3));

    ASSERT_EQ(CC_ERR_OUT_OF_RANGE, cc_array_swap_at(a, 1, -1));

    cc_array_destroy(a);
    return true;
}

bool cc_array_swap_out_of_bounds_upper_test() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));

    for (int i = 1; i <= 5; i++) {
        ASSERT_CC_OK(cc_array_add(a, (void*)(intptr_t)i));
    }

    ASSERT_EQ(CC_ERR_OUT_OF_RANGE, cc_array_swap_at(a, 5, 6));

    ASSERT_EQ(CC_ERR_OUT_OF_RANGE, cc_array_swap_at(a, 4, 5));

    cc_array_destroy(a);
    return true;
}

bool cc_array_swap_index1_equal_size_test() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));

    for (int i = 1; i <= 5; i++) {
        ASSERT_CC_OK(cc_array_add(a, (void*)(intptr_t)i));
    }

    ASSERT_EQ(CC_ERR_OUT_OF_RANGE, cc_array_swap_at(a, 5, 3));

    cc_array_destroy(a);
    return true;
}

bool cc_array_remove_index_of_out_of_range_test() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));

    for (int i = 1; i <= 5; i++) {
        ASSERT_CC_OK(cc_array_add(a, (void*)(intptr_t)i));
    }

    void* out;
    ASSERT_EQ(CC_ERR_VALUE_NOT_FOUND, cc_array_remove(a, (void*)(intptr_t)6, &out));

    cc_array_destroy(a);
    return true;
}

bool cc_array_remove_index_of_other_status_test() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));

    for (int i = 1; i <= 5; i++) {
        ASSERT_CC_OK(cc_array_add(a, (void*)(intptr_t)i));
    }

    void* out;
    ASSERT_EQ(CC_OK, cc_array_remove(a, (void*)(intptr_t)3, &out));

    cc_array_destroy(a);
    return true;
}

bool cc_array_remove_index_not_last_test() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));

    for (int i = 1; i <= 5; i++) {
        ASSERT_CC_OK(cc_array_add(a, (void*)(intptr_t)i));
    }

    void* out;
    ASSERT_EQ(CC_OK, cc_array_remove(a, (void*)(intptr_t)3, &out));

    cc_array_destroy(a);
    return true;
}





test_t TESTS[] = {
    &example_test,
    &cc_array_get_last_test,
    &cc_array_replace_at_test,
    &cc_array_replace_at_test2,
    &cc_array_add_at_greater,
    &cc_array_add_at_eq,
    &cc_array_add_full_capacity_test,
    &cc_array_add_after_expand_test,
    &cc_array_swap_within_bounds_test,
    &cc_array_swap_out_of_bounds_lower_test,
    &cc_array_swap_out_of_bounds_upper_test,
    &cc_array_swap_index1_equal_size_test,
    &cc_array_remove_index_of_out_of_range_test,
    &cc_array_remove_index_of_other_status_test,
    


    NULL
};
