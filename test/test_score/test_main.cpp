//* https://piolabs.com/blog/insights/unit-testing-part-1.html

#include <unity.h>
#include "Score.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_init()
{
    Score score;
    TEST_ASSERT_EQUAL(0, score.getHomePoints());
    TEST_ASSERT_EQUAL(0, score.getAwayPoints());
    TEST_ASSERT_EQUAL(Home, score.getServe());
}

void helper_test_score(Score &score, int home, int away, Side serve)
{
    TEST_ASSERT_EQUAL(home, score.getHomePoints());
    TEST_ASSERT_EQUAL(away, score.getAwayPoints());
    TEST_ASSERT_EQUAL(serve, score.getServe());
}

void test_score_basics()
{
    Score score;
    score.pointWon(Home);
    helper_test_score(score, 1, 0, Home);
    score.pointWon(Home);
    score.pointWon(Home);
    helper_test_score(score, 3, 0, Away);
    score.pointWon(Away);
    score.pointWon(Away);
    helper_test_score(score, 3, 2, Home);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_init);
    RUN_TEST(test_score_basics);
    UNITY_END();
}