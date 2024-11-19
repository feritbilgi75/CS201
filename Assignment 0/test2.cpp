#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//--------------------------------------------------------------------
#include "GradeBook.h"
//--------------------------------------------------------------------

TEST(initGradeBook, initGradeBook) {
    string inputFile = BASE;
    inputFile += "/output2.txt";
    ifstream file( inputFile );
    string expectedOutput = "";
    string line;
    while ( getline( file, line ) ) {
        expectedOutput = expectedOutput + line + "\n";
    }
    stringstream ss;
    auto buffer = cout.rdbuf( ss.rdbuf() );

//--TEST CODE STARTS HERE---------------------------------------------
    GradeBook gb1;
    cout << endl;

    gb1.setCourseNo( 50 );
    cout << endl;

    gb1.setCourseNo( 201 );
    cout << endl;

    gb1.displayMessage();
    cout << endl;

    gb1.determineCourseAverage();
    cout << endl;

    gb1.findGradeDistribution();
    cout << endl;
//--TEST CODE ENDS HERE-----------------------------------------------

    string testOutput = ss.str();
    EXPECT_EQ( testOutput, expectedOutput );
    cout.rdbuf( buffer );
}

int main( int argc, char** argv ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
