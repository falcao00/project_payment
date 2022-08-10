cmake_minimum_required(VERSION 3.22.1)

project(project_payment)

add_executable(${PROJECT_NAME} 
                ./payment/transactions.c
                ./payment/accountFunctions.c
                ./test/main_test.cpp
                ./test/payment_test.cpp)

add_subdirectory(payment)
add_subdirectory(test)

target_link_libraries(${PROJECT_NAME} payment test gtest gtest_main)