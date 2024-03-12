/**
 * @file Assert.h
 * @brief 
 * @version 0.1
 * @date 2024-03-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_UTILS_INC_ASSERT_H_
#define DEV_UTILS_INC_ASSERT_H_

#include <assert.h>
#include <cstddef>

#define STM32_ASSERT(cond_)\
    assert(cond_)

#define ASSERT_STRUCT_SIZE(struct_type, expected_size) \
    static_assert(sizeof(struct_type) == expected_size, \
    "Struct size mismatch. The member order may have been modified.");

#define ASSERT_MEMBER_OFFSET(struct_type, member_name, expected_offset) \
    static_assert(offsetof(struct_type, member_name) == expected_offset, \
        "Member offset mismatch. The member order may have been modified.");

#endif  // DEV_UTILS_INC_ASSERT_H_
