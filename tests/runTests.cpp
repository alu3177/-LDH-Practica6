
#include <cppunit/ui/text/TestRunner.h>
#include"GrafoTest.h"

using namespace CppUnit;

int main( int argc, char **argv){
    TextUi::TestRunner runner;
    runner.addTest( GrafoTest::suite() );
    runner.run();
    return 0;
}
