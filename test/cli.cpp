# include <args.h>
# include <gtest/gtest.h>

TEST(CLI, args_parse) {
  int argc = 7;
  char* argv[] = {
    (char*)"./a.out",
    (char*)"-o",
    (char*)"output",
    (char*)"-I",
    (char*)"includePath",
    (char*)"-L",
    (char*)"libPath"
  };
  Args args = Args(argc, argv);
  ASSERT_EQ(args.output, "output");
  ASSERT_EQ(args.includePaths[0], "includePath");
  ASSERT_EQ(args.libPath, "libPath");
}