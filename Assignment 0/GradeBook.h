#ifndef GRADEBOOK_H
#define GRADEBOOK_H

class GradeBook {

public:
    GradeBook( const int no = 100 );

    void displayMessage( const int no ) const;
    void displayMessage() const;

    // sets the course number
    void setCourseNo( const int no );

    // returns the course number
    int getCourseNo() const;

    // sets the grades stored in the GradeBook object
    // the grades entered should be valid (in between 0 and 100)
    // all grades are reset to 0 if there is at least one invalid grade
    void setGrades( const int inGrades[] );

    // computes the average of grades
    void determineCourseAverage() const;

    // computes the letter grade distribution
    void findGradeDistribution() const;

    static const int numStudents = 10;  // fixed number of students

private:
    int courseNo;                       // course number
    int grades[ numStudents ];          // array that stores the grades
};

#endif // GRADEBOOK_H
