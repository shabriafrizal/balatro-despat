#pragma once

/**
 * Tracks accumulated score against the current blind's required score.
 * In Balatro, each hand you play adds to your accumulated score;
 * when it meets or exceeds the required score, the blind is cleared.
 */
class BlindRule
{
public:
    void setRequiredScore(int score);
    int getRequiredScore() const;

    /** Add a hand's score to the accumulated total */
    void addScore(int score);

    /** Get total score accumulated this blind */
    int getAccumulatedScore() const;

    /** Returns true if accumulatedScore >= requiredScore */
    bool isBlindCleared() const;

    /** Reset accumulated score and required score for a new blind */
    void reset();

private:
    int requiredScore = 0;
    int accumulatedScore = 0;
};