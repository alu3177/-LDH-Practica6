
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/XmlOutputter.h>
#include"GrafoTest.h"

using namespace CppUnit;

int main( int argc, char **argv){
    TestResult controller;
    TestResultCollector results;
    TextUi::TestRunner runner;
    std::ofstream xmlout ("logs/cppunit/testResults.xml");
    XmlOutputter xmlOutputter (&results, xmlout);
    
    controller.addListener(&results);
    vector<Test* > suiteOfTests = GrafoTest::suite()->getTests();
    for (unsigned int i = 0; i < suiteOfTests.size(); runner.addTest( suiteOfTests[i++] ));
    runner.run(controller);
    xmlOutputter.write();
    return 0;
}
