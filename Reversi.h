//
// Created by theo on 2021/5/12.
//

#ifndef PROJECT3_1__REVERSI_H
#define PROJECT3_1__REVERSI_H


//
//  Reversi.h
//  ReversiClient
//
//  Created by ganjun on 2018/3/6.
//  Copyright © 2018年 ganjun. All rights reserved.
//
#define BLACK 0
#define WHITE 1
#define EMPTY -1
#include <stdio.h>
#include "ClientSocket.h"

using namespace std;

class Reversi{
private:
    ClientSocket client_socket;
    int ownColor;
    int oppositeColor;
    char lastmsg[16];
    int Board[19][19];//
public:
    Reversi();
    ~Reversi();

    void authorize(const char *id , const char *pass);

    void gameStart();

    void gameOver();

    void roundStart(int round);

    void oneRound(int round, string s);

    void roundOver(int round);

    int observe();

    void putDown(int row1 , int col1, int row2, int col2);

    // according to chessman position (row , col) , generate one step message in order to send to server
    void generateOneStepMessage(int row1 , int col1, int row2, int col2);

    void noStep();

    pair<pair<int,int>,pair<int,int>> step();

    void saveChessBoard(string s, int round);

    void debug_lastmsg();

    void handleMessage(int row1, int col1, int row2, int col2, int color);
};




#endif //PROJECT3_1__REVERSI_H
