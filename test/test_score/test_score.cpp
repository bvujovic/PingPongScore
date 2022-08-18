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

void helper_test_score(Score &score, int home, int away)
{
    TEST_ASSERT_EQUAL(home, score.getHomePoints());
    TEST_ASSERT_EQUAL(away, score.getAwayPoints());
}

void helper_test_score(Score &score, int home, int away, Side serve)
{
    helper_test_score(score, home, away);
    TEST_ASSERT_EQUAL(serve, score.getServe());
}

void test_score_basics()
{
    Score score;
    helper_test_score(score, 0, 0, Home);
    score.pointWon(Home);
    helper_test_score(score, 1, 0, Home);
    score.pointWon(Home);
    score.pointWon(Home);
    helper_test_score(score, 3, 0, Away);
    score.pointWon(Away);
    score.pointWon(Away);
    helper_test_score(score, 3, 2, Home);
}

void test_change_serve()
{
    Score score;
    TEST_ASSERT_EQUAL(Home, score.getServe());
    score.changeServe();
    TEST_ASSERT_EQUAL(Away, score.getServe());
    score.changeServe();
    TEST_ASSERT_EQUAL(Home, score.getServe());
}

void test_change_serve2()
{
    Score score;
    TEST_ASSERT_EQUAL(Home, score.getServe());
    score.changeServe();
    TEST_ASSERT_EQUAL(Away, score.getServe());
    score.pointWon(Home);
    TEST_ASSERT_EQUAL(Away, score.getServe());
}

void test_score_basics_away_serve()
{
    Score score;
    score.changeServe();
    helper_test_score(score, 0, 0, Away);
    score.pointWon(Home);
    helper_test_score(score, 1, 0, Away);
    score.pointWon(Home);
    score.pointWon(Home);
    helper_test_score(score, 3, 0, Home);
    score.pointWon(Away);
    score.pointWon(Away);
    helper_test_score(score, 3, 2, Away);
}

void helper_multi_points(Score &score, Side side, int points)
{
    for (size_t i = 0; i < points; i++)
        score.pointWon(side);
}

void test_score_advanced()
{
    Score score;
    helper_test_score(score, 0, 0, Home);
    helper_multi_points(score, Home, 10);
    helper_test_score(score, 10, 0, Away);
    helper_multi_points(score, Away, 10);
    helper_test_score(score, 10, 10, Home);

    score.pointWon(Home);
    helper_test_score(score, 11, 10, Away);
    score.pointWon(Away);
    helper_test_score(score, 11, 11, Home);
    score.pointWon(Away);
    helper_test_score(score, 11, 12, Away);
}

// da li je mec dobijen: ko prvi dodje do 11, a protivnik ima 9 ili manje
void test_match_over1()
{
    Score score;
    TEST_ASSERT_FALSE(score.isMatchOver());
    helper_multi_points(score, Home, 10);
    TEST_ASSERT_FALSE(score.isMatchOver());
    helper_multi_points(score, Home, 1);
    TEST_ASSERT_TRUE(score.isMatchOver());

    score.reset();

    helper_test_score(score, 0, 0, Away);
    TEST_ASSERT_FALSE(score.isMatchOver());
    helper_multi_points(score, Home, 9);
    TEST_ASSERT_FALSE(score.isMatchOver());
    helper_multi_points(score, Away, 10);
    TEST_ASSERT_FALSE(score.isMatchOver());
    helper_multi_points(score, Away, 1);
    TEST_ASSERT_TRUE(score.isMatchOver());
}

// da li je mec dobijen: igranje na razliku
void test_match_over2()
{
    Score score;
    helper_test_score(score, 0, 0, Home);
    helper_multi_points(score, Home, 10);
    helper_test_score(score, 10, 0);
    helper_multi_points(score, Away, 10);
    helper_test_score(score, 10, 10);
    score.pointWon(Home);
    TEST_ASSERT_FALSE(score.isMatchOver());
    score.pointWon(Away);
    score.pointWon(Away);
    TEST_ASSERT_FALSE(score.isMatchOver());
    score.pointWon(Away);
    TEST_ASSERT_TRUE(score.isMatchOver());
}

// B
// void test_undoLastPoint()
// {
//     Score score;
//     score.undoLastPoint();
//     helper_test_score(score, 0, 0, Home);
//     score.pointWon(Away);
//     helper_test_score(score, 0, 1, Home);
//     score.undoLastPoint();
//     helper_test_score(score, 0, 0, Home);
//     score.pointWon(Away);
//     score.pointWon(Away);
//     helper_test_score(score, 0, 2, Away);
// }

void test_pointRetracted()
{
    Score score;
    score.pointRetracted(Home);
    helper_test_score(score, 0, 0, Home);
    score.pointWon(Away);
    helper_test_score(score, 0, 1, Home);
    score.pointRetracted(Away);
    helper_test_score(score, 0, 0, Home);
    score.pointWon(Away);
    score.pointWon(Away);
    helper_test_score(score, 0, 2, Away);
    score.pointRetracted(Away);
    helper_test_score(score, 0, 1, Home);
    score.pointRetracted(Home);
    helper_test_score(score, 0, 1, Home);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_init);
    RUN_TEST(test_score_basics);
    RUN_TEST(test_change_serve);
    RUN_TEST(test_change_serve2);
    RUN_TEST(test_score_basics_away_serve);
    RUN_TEST(test_score_advanced);
    RUN_TEST(test_match_over1);
    RUN_TEST(test_match_over2);
    RUN_TEST(test_pointRetracted);
    UNITY_END();
}