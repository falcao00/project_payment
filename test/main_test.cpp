#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../payment/transactions.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
