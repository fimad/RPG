#include <cxxtest/TestSuite.h>
#include "resources/DirectoryProvider.hpp"
#include "resources/ResourceDefs.hpp"
#include "resources/Path.hpp"

class DirectoryProviderTestSuite : public CxxTest::TestSuite{
  private:
    DirectoryProvider provider;
    string txtFile;
  public:
    DirectoryProviderTestSuite() : 
      provider("../../") //from the build directory, this will point to the root of the project's source
    {}

    void setUp(){
      txtFile = "tests/resources/test_directory_provider.txt";
    }
    void tearDown(){
    }

    void test_provides_valid(){
      TS_ASSERT(provider.provides( Path(txtFile) ));
    }

    void test_provides_invalid(){
      TS_ASSERT(!provider.provides( Path(txtFile+".NOPE") ));
    }

    void test_read_valid(){
      string data;
      TS_ASSERT_THROWS_NOTHING( data=provider.getBuffer(Path(txtFile)) );
      TS_ASSERT_EQUALS(data,"This is a test of the emergency broadcast system!\n");
    }

    void test_read_invalid(){
      TS_ASSERT_THROWS( provider.getBuffer(Path(txtFile+".NOPE")), NoSuchPathException);
    }
};

