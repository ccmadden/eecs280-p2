#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
    Matrix *mat = new Matrix;
    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(mat, 3, 5);
    Matrix_fill(mat, value);
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
    }
    delete mat;  // delete the Matrix
}

TEST(test_matrix_basic) {
    Matrix *mat = new Matrix;
    Matrix_init(mat, 5, 5);

    ASSERT_EQUAL(Matrix_width(mat), 5);
    ASSERT_EQUAL(Matrix_height(mat), 5);

    Matrix_fill(mat, 0);

    int *ptr = Matrix_at(mat, 2, 3);
    ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
    ASSERT_EQUAL(Matrix_column(mat, ptr), 3);
    ASSERT_EQUAL(*ptr, 0);
    *ptr = 42;

    const int *cptr = Matrix_at(mat, 2, 3);
    ASSERT_EQUAL(*cptr, 42);

    Matrix_fill_border(mat, 2);
    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 2);

    ASSERT_EQUAL(Matrix_max(mat), 42);

    delete mat;
}

TEST(test_matrix_print) {
    Matrix *mat1 = new Matrix;
    Matrix_init(mat1, 1, 1);
    *Matrix_at(mat1, 0, 0) = 42;
    ostringstream expected;
    expected << "1 1\n"
             << "42 \n";
    ostringstream actual;
    Matrix_print(mat1, actual);
    ASSERT_EQUAL(expected.str(), actual.str());
    delete mat1;
}

TEST(test_matrix_width_basic) {
    Matrix *mat2 = new Matrix;
    Matrix_init(mat2, 3, 4);
    int width = 3;
    ASSERT_EQUAL(width, Matrix_width(mat2));
    delete mat2;
}
TEST(test_matrix_height_basic) {
    Matrix *mat3 = new Matrix;
    Matrix_init(mat3, 3, 4);
    int height = 4;
    ASSERT_EQUAL(height, Matrix_height(mat3));
    delete mat3;
}

TEST(test_matrix_row_basic) {
    Matrix *mat4 = new Matrix;
    Matrix_init(mat4, 5, 6);
    int expected = 3;
    ASSERT_EQUAL(expected, Matrix_row(mat4, Matrix_at(mat4, 3, 4)));
    delete mat4;
}

TEST(test_matrix_column_basic) {
    Matrix *mat5 = new Matrix;
    Matrix_init(mat5, 5, 6);
    int expected = 4;
    ASSERT_EQUAL(expected, Matrix_column(mat5, Matrix_at(mat5, 3, 4)));
    delete mat5;
}

TEST(test_fill_boarder_basic) {
    Matrix *mat6 = new Matrix;  // create a Matrix in dynamic memory
    const int value = 75;
    Matrix_init(mat6, 6, 9);
    Matrix_fill_border(mat6, value);
    ASSERT_EQUAL(*Matrix_at(mat6, 0, 0), value);
    delete mat6;  // delete the Matrix
}

TEST(test_matrix_max_basic) {
    Matrix *mat7 = new Matrix;
    Matrix_init(mat7, 6, 7);
    Matrix_fill(mat7, 8);
    int *ptr = Matrix_at(mat7, 4, 4);
    ASSERT_EQUAL(*ptr, 8);
    *ptr = 67;
    ASSERT_EQUAL(Matrix_max(mat7), 67);
    delete mat7;
}

TEST(test_matrix_max_neg_num) {
    Matrix *mat8 = new Matrix;
    Matrix_init(mat8, 6, 7);
    Matrix_fill(mat8, -10);
    int *ptr = Matrix_at(mat8, 5, 5);
    ASSERT_EQUAL(*ptr, -10);
    *ptr = -3;
    ASSERT_EQUAL(Matrix_max(mat8), -3);
    delete mat8;
}

TEST(test_matrix_col_min_value) {
    Matrix *mat9 = new Matrix;
    Matrix_init(mat9, 5, 4);
    int row = 3;
    int col_start = 1;
    int col_end = 4;
    int *ptr1 = Matrix_at(mat9, 3, 1);
    *ptr1 = 4;
    int *ptr2 = Matrix_at(mat9, 3, 2);
    *ptr2 = 9;
    int *ptr3 = Matrix_at(mat9, 3, 3);
    *ptr3 = 2;
    int *ptr4 = Matrix_at(mat9, 3, 4);
    *ptr4 = 8;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat9, row, col_start, col_end)
    , 3);
    delete mat9;
}

TEST(test_matrix_min_value_in_row_basic) {
    Matrix *mat10 = new Matrix;
    Matrix_init(mat10, 9, 9);
    int row = 2;
    int col_start = 3;
    int col_end = 7;
    int *ptr4 = Matrix_at(mat10, 2, 3);
    *ptr4 = 10;
    int *ptr5 = Matrix_at(mat10, 2, 4);
    *ptr5 = 4;
    int *ptr1 = Matrix_at(mat10, 2, 5);
    *ptr1 = 4;
    int *ptr2 = Matrix_at(mat10, 2, 6);
    *ptr2 = 2;
    int *ptr3 = Matrix_at(mat10, 2, 7);
    *ptr3 = 8;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat10, row, col_start, col_end), 2);
    delete mat10;
}

TEST(test_matrix_col_of_min_value_multiple_min) {
    Matrix *mat11 = new Matrix;
    Matrix_init(mat11, 9, 9);
    Matrix_fill(mat11, 3);
    int row = 2;
    int col_start = 5;
    int col_end = 8;
    int *ptr1 = Matrix_at(mat11, 2, 5);
    *ptr1 = -12;
    int *ptr2 = Matrix_at(mat11, 2, 6);
    *ptr2 = -12;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat11, row, col_start, col_end)
    , 5);
    delete mat11;
}

TEST(test_matrix_at_basic) {
    Matrix *mat12 = new Matrix;
    Matrix_init(mat12, 8, 7);
    Matrix_fill(mat12, 8);
    ASSERT_EQUAL(*Matrix_at(mat12, 2, 4), 8);
    delete mat12;
}

TEST(test_marix_fill_boarder_basic) {
    Matrix *mat13 = new Matrix;
    Matrix_init(mat13, 3, 3);
    int value1 = 29;
    Matrix_fill_border(mat13, value1);
    Matrix_fill(mat13, 12);

    Matrix *mat14 = new Matrix;
    Matrix_init(mat14, 3, 3);
    int *ptr1 = Matrix_at(mat14, 0, 0);
    *ptr1 = value1;
    int *ptr2 = Matrix_at(mat14, 0, 1);
    *ptr2 = value1;
    int *ptr3 = Matrix_at(mat14, 0, 2);
    *ptr3 = value1;
    int *ptr4 = Matrix_at(mat14, 1, 0);
    *ptr4 = value1;
    int *ptr5 = Matrix_at(mat14, 1, 1);
    *ptr5 = 12;
    int *ptr6 = Matrix_at(mat14, 1, 2);
    *ptr6 = value1;
    int *ptr7 = Matrix_at(mat14, 2, 0);
    *ptr7 = value1;
    int *ptr8 = Matrix_at(mat14, 2, 1);
    *ptr8 = value1;
    int *ptr9 = Matrix_at(mat14, 2, 2);
    *ptr9 = value1;

    Matrix_equal(mat13, mat14);
    delete mat13;
    delete mat14;
}

TEST(test_matrix_max_1x1) {
    Matrix *mat15 = new Matrix;
    Matrix_init(mat15, 1, 1);
    int *ptr1 = Matrix_at(mat15, 0, 0);
    *ptr1 = 9;
    ASSERT_EQUAL(Matrix_max(mat15), 9);
    delete mat15;
}

TEST(test_matrix_fill_1x1) {
    Matrix *mat16 = new Matrix;
    Matrix_init(mat16, 1, 1);
    int *ptr1 = Matrix_at(mat16, 0, 0);
    *ptr1 = 8;

    Matrix *mat17 = new Matrix;
    Matrix_init(mat17, 1, 1);
    Matrix_fill(mat17, 8);

    Matrix_equal(mat16, mat17);
    delete mat16;
    delete mat17;
}

TEST(test_matrix_fill_and_fill_boarder_1x1) {
    Matrix *mat18 = new Matrix;
    Matrix_init(mat18, 1, 1);
    Matrix_fill(mat18, 4);

    Matrix *mat19 = new Matrix;
    Matrix_init(mat19, 1, 1);
    Matrix_fill_border(mat19, 4);
    Matrix_equal(mat18, mat19);

    delete mat18;
    delete mat19;
}

TEST(test_matrix_narrow) {
    Matrix *mat20 = new Matrix;
    Matrix_init(mat20, 1, 10);
    Matrix_fill(mat20, 4);

    Matrix *mat21 = new Matrix;
    Matrix_init(mat21, 1, 10);
    Matrix_fill_border(mat21, 4);
    Matrix_equal(mat20, mat21);

    delete mat20;
    delete mat21;
}

TEST(test_matrix_at_const) {
    Matrix *mat21 = new Matrix;
    Matrix_init(mat21, 8, 8);
    const int x = 8;
    Matrix_fill(mat21, x);
    ASSERT_EQUAL(*Matrix_at(mat21, 2, 2), x);
    delete mat21;
}

TEST(test_matrix_min_row_1x1) {
    Matrix *mat22 = new Matrix;
    Matrix_init(mat22, 1, 1);
    Matrix_fill(mat22, 3);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat22, 0, 0, 1), 3);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat22, 0, 0, 1), Matrix_max(mat22));
    delete mat22;
}

TEST(test_min_col_1x1) {
    Matrix *mat23 = new Matrix;
    Matrix_init(mat23, 1, 1);
    Matrix_fill(mat23, 8);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat23, 0, 0, 1), 0);
    delete mat23;
}

TEST(test_matrix_min_in_row_exclusive) {
    Matrix *mat24 = new Matrix;
    Matrix_init(mat24, 9, 9);
    int row = 2;
    int col_start = 3;
    int col_end = 7;
    int *ptr4 = Matrix_at(mat24, 2, 3);
    *ptr4 = 10;
    int *ptr5 = Matrix_at(mat24, 2, 4);
    *ptr5 = 4;
    int *ptr1 = Matrix_at(mat24, 2, 5);
    *ptr1 = 4;
    int *ptr2 = Matrix_at(mat24, 2, 6);
    *ptr2 = 2;
    int *ptr3 = Matrix_at(mat24, 2, 7);
    *ptr3 = 0;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat24, row, col_start, col_end), 2);
    delete mat24;
}

TEST(test_matrix_fill_and_fill_border_2x2) {
    Matrix *mat25 = new Matrix;
    Matrix_init(mat25, 2, 2);
    Matrix_fill(mat25, 4);

    Matrix *mat26 = new Matrix;
    Matrix_init(mat26, 2, 2);
    Matrix_fill_border(mat26, 4);
    Matrix_equal(mat26, mat25);

    delete mat25;
    delete mat26;
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN()  // Do NOT put a semicolon here
