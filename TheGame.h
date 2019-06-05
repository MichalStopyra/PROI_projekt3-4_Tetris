//
// Created by michal on 13.05.19.
//

#ifndef THEGAME_H
#define THEGAME_H

#include "Tetromino.h"
#include "Node.h"
#include "FifoQueue.h"

template <typename T>
class TheGame {

private:
    FifoQueue fifoQueue;
    T result;
    bool gameOver;
    float timer;
    float delay;
    bool sendNewBlock;
    T fieldColors[FIELD_WIDTH*FIELD_HEIGHT];


public:

    TheGame(T=0, bool= false, float=0.0, float=0.3, bool=true);
    virtual ~TheGame();

    bool checkLine(int nrCheckedLine);
    //!funkcja checkline
    void checkField();
    void destroyField(int begginingDestroy, int endDestroy);
    void display();

    bool get_gameOver() const;
    void set_gameOver( bool gameOverValue );
    int get_result() const;
    float get_timer() const;
    float get_delay() const;

    template <typename F>
    void set_delay(F tmpDelay);

    void increase_timer(float timeValue);
    bool increase_delay();
    void decrease_delay();
    void increase_speed();
    void reset_delay();
    void reset_timer();
    void set_sendNewBlock(bool sendNewBlockValue);
    bool get_sendNewBlock();

    Tetromino get_currentBlock();


    void rotate_currentBlock();
    void move_currentBlock(int newFirstCageLocationx, int newFirstCageLocationy);
    void add_currentBlock_to_field();
    int get_currentFirstCageLocationx();
    int get_currentFirstCageLocationy();
    int get_currentBlockColorNumber();

    bool doesCurrentBlockFit();
    void push_backFifo(Node* pAfter, int FIRSTCAGELOCX, int FIRSTCAGELOCY, int blockSymbolCounter, int blockColorNumber);

    void draw_currentBlock();

    int get_currentBlock_shape_values(int i, int j);
    void pop_backFifo();

    int get_fieldColorsValues(int i, int j);

    bool stop_currentBlock();


};


#endif //THEGAME_H



