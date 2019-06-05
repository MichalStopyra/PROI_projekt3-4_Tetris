//
// Created by michal on 13.05.19.
//

#include "TheGame.h"
#include <cmath>

#define FIELD_HEIGHT 20
#define FIELD_WIDTH 10
#define TETROMINO_TAB_SIZE 4

#define currentBlock this->fifoQueue.first->tetromino


template <typename T>
TheGame<T>::TheGame(T RESULT, bool GAMEOVER, float TIMER, float DELAY, bool SENDNEWBLOCK):
    result(RESULT), gameOver(GAMEOVER), timer(TIMER), delay(DELAY), sendNewBlock(SENDNEWBLOCK)
    {
        for(int i=0; i<FIELD_HEIGHT*FIELD_WIDTH; ++i)
            this->fieldColors[i]=9;//nie odpowiada zadnemu kolorowi
}
template <typename T>
TheGame<T>::~TheGame(){ }

template <typename T>
bool TheGame<T>::get_gameOver() const{
    return gameOver; }

template <typename T>
void TheGame<T>::set_gameOver( bool gameOverValue ) { gameOver = gameOverValue; }

template <typename T>
int TheGame<T>::get_result() const { return result; }

template <typename T>
float TheGame<T>::get_timer() const{
    return timer; }

template <typename T>
float TheGame<T>::get_delay() const{
    return delay; }

template <typename T>
void TheGame<T>::increase_timer(float timeValue){
    this->timer+=timeValue;
}

template <typename T>
bool TheGame<T>::increase_delay(){
    this->delay-=0.3;
    return true;
}

template <typename T>
void TheGame<T>::increase_speed() {
    this->delay-=0.07;
}

template <typename T>
void TheGame<T>::decrease_delay(){
    this->delay+=0.1;
}

template <typename T>
void TheGame<T>::reset_delay() {
    this->delay=0.3;
}

template <typename T>
template <typename F>
void TheGame<T>::set_delay(F tmpDelay) {
    this->delay=tmpDelay;
}

template <typename T>
void TheGame<T>::reset_timer(){
    this->timer=0.0;
}

template <typename T>
void TheGame<T>::set_sendNewBlock(bool sendNewBlockValue){
    this->sendNewBlock=sendNewBlockValue;
}

template <typename T>
bool TheGame<T>::get_sendNewBlock() {
    return sendNewBlock;
}

template <typename T>
Tetromino TheGame<T>::get_currentBlock() {
    return this->fifoQueue.last->tetromino;
}

template <typename T>
bool TheGame<T>::checkLine(int nrCheckedLine)
{
    bool isFull= true;
    for (int i=0; i<FIELD_WIDTH; ++i)
    {
        if (Tetromino::field[nrCheckedLine*FIELD_WIDTH+i]==0)
            isFull=false;
    }
    return isFull;
}


template <typename T>
void TheGame<T>::destroyField(int begginingDestroy, int endDestroy)
{
    int difference=begginingDestroy-endDestroy+1;
    int tmpTabField[FIELD_WIDTH*FIELD_HEIGHT]={0};

    for(int i=0; i<FIELD_WIDTH; ++i) {//kopiowanie tablicy i zerowanie oryginalnej
        for (int j = 0; j <= begginingDestroy; ++j) {
            tmpTabField[j*FIELD_WIDTH+i] = Tetromino::field[j*FIELD_WIDTH+i];
            Tetromino::field[j*FIELD_WIDTH+i] = 0;
        }
    }

    for(int j=difference; j<=begginingDestroy; ++j){
        for(int i=0; i<FIELD_WIDTH; ++i){
            Tetromino::field[j*FIELD_WIDTH+i]=tmpTabField[(j-difference)*FIELD_WIDTH+i];
        }
    }
}



template <typename T>
void TheGame<T>::checkField()
{
    int begginingDestroy;
    int endDestroy;
    int pointsMultiplier;
    for(int i=FIELD_HEIGHT-1; i>=0; --i)
    {
        if( TheGame::checkLine(i) )
        {
            pointsMultiplier=1;
            begginingDestroy=endDestroy=i;//Sprawdzanie linii, czy jest wiecej niz jedna
               while (TheGame::checkLine(i - 1) && i!=0) {
                   endDestroy = i - 1;
                   i = i - 1;
                   pointsMultiplier=pow(4, pointsMultiplier);
               }
           result+=100*pointsMultiplier;
           TheGame::destroyField(begginingDestroy, endDestroy);
        }
    }
}

template <typename T>
void TheGame<T>::rotate_currentBlock(){
    currentBlock.rotate_block();
}


template <typename T>
int TheGame<T>::get_currentFirstCageLocationx(){
    return currentBlock.firstCageLocationx;
}

template <typename T>
int TheGame<T>::get_currentFirstCageLocationy(){
    return currentBlock.firstCageLocationy;
}

template <typename T>
void TheGame<T>::move_currentBlock(int newFirstCageLocationx, int newFirstCageLocationy) {
    currentBlock.move_block(newFirstCageLocationx, newFirstCageLocationy);
}

template <typename T>
bool TheGame<T>::doesCurrentBlockFit() {
    return currentBlock.does_block_fit();
}

template <typename T>
void TheGame<T>::push_backFifo(Node* pAfter, int FIRSTCAGELOCX, int FIRSTCAGELOCY, int blockSymbolCounter, int blockColorNumber) {
    this->fifoQueue.pushBack(pAfter, FIRSTCAGELOCX, FIRSTCAGELOCY, blockSymbolCounter, blockColorNumber);
}


template <typename T>
int TheGame<T>::get_currentBlock_shape_values(int i, int j) {
    return currentBlock.shape[j*TETROMINO_TAB_SIZE+i];
}


template <typename T>
int TheGame<T>::get_currentBlockColorNumber() {
    return currentBlock.blockColorNumber;
}

template <typename T>
void TheGame<T>::pop_backFifo() {
    this->fifoQueue.popBack();
}

template <typename T>
int TheGame<T>::get_fieldColorsValues(int i, int j) {
    return fieldColors[j*FIELD_WIDTH+i];
}

template <typename T>
bool TheGame<T>::stop_currentBlock() {
    int tmpFirstCageLocationy = currentBlock.get_firstCageLocationy();
    move_currentBlock(currentBlock.get_firstCageLocationx(), currentBlock.get_firstCageLocationy() + 1);

    if (tmpFirstCageLocationy == (currentBlock.get_firstCageLocationy()) ) {
        return true;
    }
    else {
        move_currentBlock(currentBlock.get_firstCageLocationx(), tmpFirstCageLocationy);
        return false;
    }
}

template <typename T>
void TheGame<T>::add_currentBlock_to_field() {
    if( this->stop_currentBlock() ) {
        currentBlock.add_block_to_field();
        this->sendNewBlock = true;
    }


    //------zapisanie koloru klocka do fielda-------
    int blockInField;

    for (int py = 0; py < TETROMINO_TAB_SIZE; ++py) {
        for (int px = 0; px < TETROMINO_TAB_SIZE; ++px) {
            if (get_currentFirstCageLocationx() + px >= 0 && get_currentFirstCageLocationx() + px < FIELD_WIDTH) {
                if (get_currentFirstCageLocationy() + py >= 0 && get_currentFirstCageLocationy() + py < FIELD_HEIGHT && currentBlock.shape[py*TETROMINO_TAB_SIZE+px]==1   ) {
                    blockInField = (get_currentFirstCageLocationy() + py) * FIELD_WIDTH + (get_currentFirstCageLocationx() + px);
                    fieldColors[blockInField] = currentBlock.blockColorNumber+1;
                }

            }
        }
    }
}
