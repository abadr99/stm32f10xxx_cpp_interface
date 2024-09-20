/**
 * @file Define.h
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-09-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once


#define INSTANTIATE_CONNECTION_CLASS(clazz)\
    template class clazz<ConnectionType::kForward_Bias>;\
    template class clazz<ConnectionType::kReverse_Bias>;

#define F_CPU (8000000U)

#define BUSY_WAIT(cond_, timeout_)\
    for (int i = 0 ; cond_ && i != timeout; ++i) { }

