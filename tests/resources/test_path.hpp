#include <cxxtest/TestSuite.h>
#include <string>
#include "resources/Path.hpp"
#include "resources/ResourceDefs.hpp"
using namespace std;

class PathTestSuite : public CxxTest::TestSuite{
    Path path1;
    Path path2;
    Path path1_up;
  public:
    PathTestSuite():
        path1("quest/dog/root.qst")
      , path1_up("quest/dog")
      , path2("quest/cowboy/root.qst")
    {}

    void setUp(){
    }
    void tearDown(){
    }

    void test_tostring(){
      TS_ASSERT_EQUALS(path1.toString(),"quest/dog/root.qst")
    }

    void test_is_multilevel(){
      TS_ASSERT_EQUALS(path1.split().front(),"quest")
    }

    void test_equivalence(){
      Path path1_same("quest/dog/root.qst");
      TS_ASSERT_EQUALS(path1,path1_same);
    }

    void test_copy(){
      Path path1_copy = path1;
      TS_ASSERT_EQUALS(path1,path1_copy);
    }

    void test_up(){
      TS_ASSERT_EQUALS(path1.up(),path1_up);
    }

    void test_down_string(){
      TS_ASSERT_EQUALS(path1_up.down("root.qst"),path1);
    }

    void test_down_path(){
      TS_ASSERT_EQUALS(path1_up.down(Path("root.qst")),path1);
    }

    void test_matches(){
      TS_ASSERT(!path2.matches(path1))
      TS_ASSERT(path1.matches(path1))
    }

    void test_any_matches(){
      TS_ASSERT(path1.matches(path1_up/Path::Any))
      TS_ASSERT(Path::Any.matches(path1))
    }

    void test_invalid_name(){
      TS_ASSERT_THROWS(path1/"test/",InvalidPathComponentException)
    }
};

