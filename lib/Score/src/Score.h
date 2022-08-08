#pragma once

enum Side
{
    Home = 0,
    Away = 1
};

// Ping-pong score.
class Score
{
private:
    int homePoints;           // how many points has the person with controls (this device)
    int awayPoints;           // how many points has the other person
    Side lastPointWon;        // who won last point
    Side serveCurrent;        // who is serving next
    Side serveStarted = Away; // who served first
    bool isOver;              // is match over

public:
    Score();
    void reset();
    void changeServe();

    void pointWon(Side side);
    void undoLastPoint();

    int getHomePoints() { return homePoints; }
    int getAwayPoints() { return awayPoints; }
    Side getServe() { return serveCurrent; }
    bool isMatchOver() { return isOver; }

private:
    void calcWhoServesNext();

};
