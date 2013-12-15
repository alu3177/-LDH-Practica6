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
    const int NOERROR = 0;
    const int UERROR = 65000;
    const string goodFileName = "grafos/grafo1.gr";
    const string badFileName = "noexisto.gr";
    int goodFileStatus = NOERROR;
    int badFileStatus = NOERROR;
    unsigned goodN = 6;
    //unsigned badN;
    unsigned goodM = 10;
    //unsigned badM;
    Grafo* goodGrafo;
    Grafo* badGrafo;
    
public:
    static TestSuite *suite(){
        TestSuite *suiteOfTests = new TestSuite( "Grafo Tests" );
        
        suiteOfTests->addTest( new TestCaller<GrafoTest>(
                                       "Test del Constructor",
                                       &GrafoTest::testConstructor) );
        
        suiteOfTests->addTest( new TestCaller<GrafoTest>(
                                       "Test métodos Getter",
                                       &GrafoTest::testGetters) );
        
        suiteOfTests->addTest( new TestCaller<GrafoTest>(
                                       "Test resultado algoritmo Dijkstra",
                                       &GrafoTest::testDijkstra) );
        
        return suiteOfTests;
    }
    void setUp(){
        goodGrafo = new Grafo(goodFileName.c_str(), goodFileStatus);
        badGrafo = new Grafo(badFileName.c_str(), badFileStatus);
    }
    
    void tearDown(){
        
    }

    
    void testConstructor(){
        CPPUNIT_ASSERT_EQUAL(goodFileStatus, NOERROR);
        CPPUNIT_ASSERT_EQUAL(badFileStatus, UERROR);
    }
    
    void testGetters(){
        CPPUNIT_ASSERT_EQUAL(goodGrafo->N(), goodN);
        CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_EQUAL(badGrafo->N(), goodN));
        CPPUNIT_ASSERT_EQUAL(goodGrafo->M(), goodM);
        CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_EQUAL(badGrafo->M(), goodM));
    }
    
    void testDijkstra(){
        const unsigned costos[] = {10, 15, 11, 20, 11};
        minpaths* dijResult = goodGrafo->Dijkstra(1);
        for (unsigned int i = 0; i < dijResult->size(); i++){
            //cout << costos[i] << ", " << dijResult->at(i).second << endl;  // DEBUG
            CPPUNIT_ASSERT_EQUAL(costos[i], dijResult->at(i).second);
        }
        
        
    }
    
};

#endif	/* GRAFOTEST_H */

