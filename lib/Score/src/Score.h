#pragma once

// Side/Player: home or away
enum Side
{
    Home = 0,
    Away = 1
};

// Ping-pong score. Adding or taking away points from players, resetting score for next game...
class Score
{
private:
    int homePoints;           // how many points has the player with controls (this device)
    int awayPoints;           // how many points has the other player
    Side serveCurrent;        // who is serving next
    Side serveStarted = Away; // who served first
    bool isOver;              // is the game over

    // calculates who serves next based on who served first and the number of points played
    void calcWhoServesNext();
    // calculates is the game over
    void calcIsGameOver();

public:
    Score();
    // resetting score to 0:0 and changing who serves first
    void reset();

    // one player won the point
    void pointWon(Side side);
    // the point is taken away from one player
    void pointRetracted(Side side);

    // points for home player
    int getHomePoints() { return homePoints; }
    // points for away player
    int getAwayPoints() { return awayPoints; }
    // which side/player serves next
    Side getServe() { return serveCurrent; }
    // is the game over
    bool isGameOver() { return isOver; }

};
