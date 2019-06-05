#include <SFML/Graphics.hpp>
#include <time.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstdlib>
#include<memory>

#include "TheGame.h"
#include "TheGame.cpp"

//--UNIT TESTS CATCH---------------------
/*#define CATCH_CONFIG_MAIN
#include "catch.hpp"
*/

using namespace std;

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20



int main()
{

    srand(time(NULL));

    sf::RenderWindow window (sf::VideoMode(308, 676), "Te-Tris");

    sf::Texture t1, t2, t3, t4;
    t1.loadFromFile("images/field10x20.jpg");
    t2.loadFromFile("images/tilesfinal.png");
    t3.loadFromFile("images/busted_kadrowane.jpg");
    t4.loadFromFile("images/Result_308.jpg");
    sf::Sprite background(t1);
    sf::Sprite blocks(t2);
    sf::Sprite busted(t3);
    sf::Sprite result(t4);

    //!--------SHARED POINTER-------------------------///
    shared_ptr< TheGame<int> > theGame = make_shared<TheGame<int> >();

    sf::Clock clock;
    float time;


    int localBlockSymbolCounter=1;
    int loopCounter=0;


    theGame->push_backFifo(nullptr, 4, 0, localBlockSymbolCounter, localBlockSymbolCounter);
    ++localBlockSymbolCounter;
    float tmpDelay;


    while (window.isOpen() && !theGame->get_gameOver() ){

        //--------------WYSYLANIE NOWEGO KLOCKA----------------------/////

        if( theGame->get_sendNewBlock() )
        {
           theGame->push_backFifo(nullptr, 4, 0, localBlockSymbolCounter, localBlockSymbolCounter);
           theGame->pop_backFifo();
              if( !theGame->doesCurrentBlockFit() )
                theGame->set_gameOver( true );

                ++localBlockSymbolCounter;
            localBlockSymbolCounter=localBlockSymbolCounter%7;
            theGame->set_sendNewBlock(false);
        }

        if(loopCounter>100000){
            loopCounter=0;
            theGame->increase_speed();
        }

        tmpDelay=theGame->get_delay();
        time = clock.getElapsedTime().asSeconds();
        clock.restart();
        theGame->increase_timer(time);

        sf::Event event;
        bool isDelayIncreased=false;

//----------------------STEROWANIE------------------------////
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Escape)
                    window.close();

                else if (event.key.code == sf::Keyboard::Up)
                    theGame->rotate_currentBlock();
                else if (event.key.code == sf::Keyboard::Left)
                    theGame->move_currentBlock(theGame->get_currentFirstCageLocationx() - 1,
                                              theGame->get_currentFirstCageLocationy());
                else if (event.key.code == sf::Keyboard::Right)
                    theGame->move_currentBlock(theGame->get_currentFirstCageLocationx() + 1,
                                              theGame->get_currentFirstCageLocationy());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                isDelayIncreased=theGame->increase_delay();
            else theGame->set_delay<float>(tmpDelay);

        }

//-------------------------PRZESUWANIE W DOL -> TIMER --------------------------------

            if( ( theGame->get_timer() ) > ( theGame->get_delay() ) )
            {
                theGame->move_currentBlock(theGame->get_currentFirstCageLocationx(), theGame->get_currentFirstCageLocationy()+1);
                theGame->reset_timer();
            }

            theGame->add_currentBlock_to_field();
            theGame->checkField();

            //----------------RYSOWANIE---------------------------------------------

            window.clear(sf::Color::White);
            window.draw(background);

            //-------------------JUZ ULOZONE KLOCKI--------------------------------
        for (int i=0; i<FIELD_WIDTH; ++i) {
            for (int j=0; j<FIELD_HEIGHT; ++j) {
                if(Tetromino::get_field_values(i,j)==1){
                    blocks.setTextureRect(sf::IntRect(theGame->get_fieldColorsValues(i,j)* 30.75, 0, 30.75, 34));
                    blocks.setPosition(i*30.75, j*34);
                    window.draw(blocks);
                }
            }
        }


            //-------------AKTUALNY KLOCEK-------------------
       for (int i=0; i<TETROMINO_TAB_SIZE; ++i) {
            for (int j=0; j<TETROMINO_TAB_SIZE; ++j) {
                if( theGame->get_currentBlock_shape_values(i,j)==1 ) {
                    blocks.setTextureRect(sf::IntRect(localBlockSymbolCounter * 30.75, 0, 30.75, 34));
                    blocks.setPosition( theGame->get_currentFirstCageLocationx()*30.75+i*30.75, theGame->get_currentFirstCageLocationy()*34+j*34);
                    window.draw(blocks);
                }
            }
        }

            theGame->set_delay<float>(tmpDelay);
            ++loopCounter;
            window.display();

    }
    //----------RANKING GRACZY----------------------------

    fstream resultFile;

    resultFile.open("ranking.txt", ios::out | ios::app );
    if(resultFile.good() == true) {
        resultFile << theGame->get_result() << endl;
        resultFile.close();
    }

    int tabResultsInt[100]={-1};
    int nrTabResults = 99;
    resultFile.open("ranking.txt", ios::in | ios::out );
    if(resultFile.good() == true) {
        for (int i = 0; i < 100; ++i)
            resultFile >> tabResultsInt[i];
        sort(tabResultsInt, tabResultsInt + nrTabResults + 1, greater<int>());
        resultFile.close();
        resultFile.clear();
    }

    resultFile.open("ranking.txt", ios::out );
    if(resultFile.good() == true){
        for(int i=0; i<nrTabResults; ++i) {
            if (tabResultsInt[i] > 0)
                resultFile<< tabResultsInt[i] << endl;
        }
        resultFile.close();
    }


    //-----------------WYSWIETLANIE GAME OVER--------------------------
    sf::Event event2;
    sf::Text resultText;
    sf::Font font;
    resultText.setString( to_string(theGame->get_result() ) );
    font.loadFromFile("images/arial.ttf");
    resultText.setFont(font);
    resultText.setCharacterSize( 70 );
    resultText.setFillColor( sf::Color::Red );
    resultText.setStyle( sf::Text::Style::Bold );


    while (window.isOpen() && theGame->get_gameOver() ) {
        window.clear(sf::Color::White);
        window.draw(busted);
        result.setPosition( 0,361);
        window.draw(result);
        resultText.setPosition( 110, 540);
        window.draw(resultText);
        window.display();

        while (window.pollEvent(event2)) {
            if (event2.type == sf::Event::KeyPressed && event2.key.code == sf::Keyboard::Escape)
                window.close();
        }
    }
    return 0;
}