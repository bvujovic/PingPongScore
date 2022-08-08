#pragma once

enum Side
{
    Home = 0,
    Away = 1
};

class Score
{
private:
    int homePoints;
    int awayPoints;
    Side serveCurrent;
    Side serveStarted;

public:
    Score();
    void resetScore();
    void changeServe();

    void pointWon(Side side);
    // void undoLastPoint();

    int getHomePoints() { return homePoints; }
    int getAwayPoints() { return awayPoints; }
    Side getServe() { return serveCurrent; }

};
