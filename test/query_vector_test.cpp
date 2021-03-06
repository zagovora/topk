#include "query_vector.h"
#include "gtest/gtest.h"


TEST(qvTest, pyramideSizeTest) {
    vec col = vec {1,2,3,4,5,6,7};
    size_t compressionBlockRows = 3;
    const size_t compressionLevels = 2;
    QueryVector qv = QueryVector(col, compressionBlockRows , compressionLevels);


    // the pyramide has 3 levels
    ASSERT_EQ(3, qv.getQueryPyramide().size());

    // 7 rows @ level 0
    ASSERT_EQ(7, qv.getQueryPyramide()[0].size());

    // ceil(7/3) = 3 rows @ level 1
    ASSERT_EQ(3, qv.getQueryPyramide()[1].size());

    // ceil(ceil(7/3)/3) = 1  cols @ level 2
    ASSERT_EQ(1, qv.getQueryPyramide()[2].size());
}

TEST(qvTest, pyramideContentTest) {
    vec col = vec {1,2,3,4};
    size_t compressionBlockRows = 3;
    const size_t compressionLevels = 2;
    QueryVector qv = QueryVector(col, compressionBlockRows , compressionLevels);

    // the pyramide at level 0
    // 1
    // 2
    // 3
    // 4
    ASSERT_EQ(1, qv.getQueryPyramide()[0][0]);
    ASSERT_EQ(2, qv.getQueryPyramide()[0][1]);
    ASSERT_EQ(3, qv.getQueryPyramide()[0][2]);
    ASSERT_EQ(4, qv.getQueryPyramide()[0][3]);

    // the pyramide at level 1
    // 6
    // 4
    ASSERT_EQ(6, qv.getQueryPyramide()[1][0]);
    ASSERT_EQ(4, qv.getQueryPyramide()[1][1]);

    // the pyramide at level 2
    // 10
    ASSERT_EQ(10, qv.getQueryPyramide()[2][0]);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

