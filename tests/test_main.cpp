#include <gtest/gtest.h>
#include "Stud.h"
#include "Mylib.h"
#include "Zmogus.h"

class StudentasTest : public ::testing::Test {
protected:
    Studentas student;

    void SetUp() override {
        student.setVardas("John");
        student.setPavarde("Doe");
    }
};

// Test name and surname setting and retrieval
TEST_F(StudentasTest, NameAndSurnameTest) {
    EXPECT_STREQ(student.getVardas(), "John");
    EXPECT_STREQ(student.getPavarde(), "Doe");
}

// Test calculateMediana with vector<int>
TEST_F(StudentasTest, CalculateMedianaVector) {
    std::vector<int> grades{7, 8, 5, 10, 6};
    double mediana = student.calculateMediana(grades);
    EXPECT_DOUBLE_EQ(mediana, 7.0);
}


TEST_F(StudentasTest, CalculateMedianaList) {
    std::list<int> grades{7, 8, 5, 10, 6};
    double mediana = student.calculateMediana(grades);
    EXPECT_DOUBLE_EQ(mediana, 7.0);
}

// Test calculateMediana with an empty container
TEST_F(StudentasTest, CalculateMedianaEmpty) {
    std::vector<int> emptyGrades;
    double mediana = student.calculateMediana(emptyGrades);
    EXPECT_DOUBLE_EQ(mediana, 0.0);
}


// cmake ..
// cmake --build .
// ctest -C Debug arba Release
