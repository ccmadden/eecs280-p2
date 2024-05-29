#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.

TEST(test_image_basic) {
  Pixel red = {255, 0, 0};
  Pixel green = {0, 255, 0};
  Image *img = new Image;
  Image_init(img, 3, 4);

  ASSERT_EQUAL(Image_width(img), 3);
  ASSERT_EQUAL(Image_height(img), 4);

  Image_fill(img, red);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 2), red));

  Image_set_pixel(img, 0, 0, green);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), green));

  delete img;
}

TEST(test_image_from_and_to_stream) {
  Image *img = new Image;

  // A very poorly behaved input PPM.
  string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);

  // Should be well behaved when you print it though!
  string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct);

  delete img;
}

TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}
TEST(image_get_pixel_basic){
  Image *img1 = new Image;
  Image_init(img1, 8, 8);
  int row = 5;
  int col = 5;
  Pixel pix = {0, 255, 0};
  Image_set_pixel(img1, row, col, pix);
  Pixel_equal(pix, Image_get_pixel(img1, row, col));
  delete img1;
  
}

TEST (test_image_fill_basic){
  Image *img2 = new Image;
  Image_init(img2, 2, 2);
  const Pixel red = {255, 0, 0};
 
  Image_set_pixel(img2, 0, 0, red);
  Image_set_pixel(img2, 0, 1, red);
  Image_set_pixel(img2, 1, 0, red);
  Image_set_pixel(img2, 1, 1, red);

  Image *img3 = new Image;
  Image_init(img3, 2, 2);
  Image_fill(img3, red);

  Image_equal(img2, img3);
  delete img2;
  delete img3;
}

TEST (test_image_width){
  Image *img3 = new Image;
  Image_init(img3, 6, 7);
  ASSERT_EQUAL(Image_width(img3), 6);
  delete img3;
}
TEST (test_image_height){
  Image *img4 = new Image;
  Image_init(img4, 6, 7);
  ASSERT_EQUAL(Image_height(img4), 7);
  delete img4;
}

TEST (test_image_fill_1x1_a){
  Image *img5 = new Image;
  const Pixel blue = {0, 0, 255};
  Image_init(img5, 1, 1);
  Image_set_pixel(img5, 0, 0, blue);

  Image *img6 = new Image;
  Image_init(img6, 1, 1);
  Image_fill(img6, blue);

  Image_equal(img5, img6);
  delete img5;
  delete img6;
}


TEST(test_image_width_basic){ 
  Image *img7 = new Image;
  Image_init(img7, 3, 4);
  int width = 3;

  ASSERT_EQUAL(width, Image_width(img7));
  delete img7;
}

TEST(test_image_height_basic){ 
  Image *img8 = new Image;
  Image_init(img8, 3, 4);
  int height = 4;

  ASSERT_EQUAL(height, Image_height(img8));
  delete img8;
}

TEST(test_image_set_pixel_basic) { 
  Image *img9 = new Image;
  Image_init(img9, 5, 5);
  const Pixel blue = {0, 0, 255};

  Image_set_pixel(img9, 3, 2, blue);
  Pixel_equal(blue, Image_get_pixel(img9, 3, 2));
  delete img9;
}

TEST(test_image_fill_1x1_b) { 
  Image *img10 = new Image;
  Image_init(img10, 1, 1);
  const Pixel green = {0, 255, 0};
 
  Image_set_pixel(img10, 0, 0, green);

  Image *img11 = new Image;
  Image_init(img11, 1, 1);
  Image_fill(img11, green);

  Image_equal(img11, img10);
  delete img10;
  delete img11;
}

TEST (img_height_and_width_1x1){
  Image *img12 = new Image;
  Image_init(img12, 1, 1);
  ASSERT_EQUAL(Image_height(img12), 1);
  ASSERT_EQUAL(Image_width(img12), 1);
  ASSERT_EQUAL(Image_height(img12), Image_width(img12));
  delete img12;
}

TEST(test_print_basic_1x1) {
  Image *img = new Image; // create an Image in dynamic memory
  const Pixel white = {255, 255, 255};
  Image_init(img, 1, 1);
  Image_set_pixel(img, 0, 0, white);
  // Capture our output
  ostringstream s;
  Image_print(img, s);
  // Correct output
  ostringstream correct;
  correct << "P3\n1 1\n255\n";
  correct << "255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}




// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
