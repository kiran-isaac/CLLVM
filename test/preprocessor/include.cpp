#include <gtest/gtest.h>
#include <preprocessor/preprocessor.h>
#include <args.h>
#include <iostream>

using std::string, std::cout, std::endl;

// Will test relative path resolution later, for now just use the absolute path
static string test_files_dir = std::string(__FILE__).substr(
    0, std::string(__FILE__).find_last_of("/\\") + 1) + "test_files";

TEST(Include, searchPathForFile) {
  string test_files_include = test_files_dir + "/include";
  char *argv[] = {(char *)"./a.out", (char *)"-o",           (char *)"output",
                  (char *)"-I",      (char *)test_files_include.c_str(), (char *)"-L",
                  (char *)"libPath"};
  Args *args = new Args(7, argv);

  string result = searchIncludePathsForFile("test.h", args);

  // Test that it finds the file
  ASSERT_EQ(result, test_files_include + "/test.h");
}

TEST(Include, searchPathForStdio) {
  string test_files_include = test_files_dir + "/include";
  char *argv[] = {(char *)"./a.out", (char *)"-o",           (char *)"output",
                  (char *)"-I",      (char *)test_files_include.c_str(), (char *)"-L",
                  (char *)"libPath"};
  Args *args = new Args(7, argv);

  string result = searchIncludePathsForFile("stdio.h", args);

  // Test that it finds the file
  ASSERT_NE(result, "");
}