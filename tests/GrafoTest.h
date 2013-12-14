/* 
 * File:   GrafoTest.h
 * Author: aladaris
 *
 * Created on 14 de diciembre de 2013, 19:41
 */

#ifndef GRAFOTEST_H
#define	GRAFOTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include "../lib/grafo.h"

using namespace std;
using namespace CppUnit;

class GrafoTest : public TestFixture{
private:
    const unsigned NOERROR = 0;
    const unsigned UERROR = 65000;
    string goodFileName = "grafos/grafo1.gr";
    string badFileName = "noexisto.gr";
//    unsigned goodN;
//    unsigned badN;
//    unsigned goodM;
//    unsigned badM;
    Grafo* goodGrafo;
    Grafo* badGrafo;
    
public:
    static CppUnit::Test *suite(){
        TestSuite *suiteOfTests = new TestSuite( "Grafo Tests" );
        suiteOfTests->addTest( new TestCaller<GrafoTest>(
                                       "testConstructor",
                                       &GrafoTest::testConstructor) );
        return suiteOfTests;
    }
    void setUp(){

    }
    
    void tearDown(){
        
    }

    
    void testConstructor(){
        int fileStatus = NOERROR;
        goodGrafo = new Grafo(goodFileName.c_str(), fileStatus);
        CPPUNIT_ASSERT(fileStatus == NOERROR);
        badGrafo = new Grafo(badFileName.c_str(), fileStatus);
        CPPUNIT_ASSERT(fileStatus == UERROR);
    }
};

#endif	/* GRAFOTEST_H */

