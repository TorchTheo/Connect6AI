//
//  Reversi.cpp
//  ReversiClient
//
//  Created by ganjun on 2018/3/6.
//  Copyright © 2018年 ganjun. All rights reserved.
//

#include "Reversi.h"
#include <iostream>
#include<string>
#include <time.h>
#include <fstream>
#include <algorithm>

#define random(x) (rand()%x)
#define ROWS 19
#define COLS 19
#define ROUNDS 3

struct Point {
    int x, y, score;
};

string type1[2] = {"000000", "111111"};//六连100000
string type2[2] = {"0000000", "1111111"};//长连100000
string type3_1[2] = {"X00000X", "X11111X"};//活五128
string type3_2[2] = {"X0000X0", "X1111X1"};
string type3_3[2] = {"X0X000X0", "X1X111X1"};
string type3_4[2] = {"0XX000XX0", "1XX111XX1"};
string type4_1[2] = {"100000", "011111"};//眠五31
string type4_2[2] = {"0000X0", "1111X1"};
string type4_3[2] = {"0X000X0", "1X111X1"};
string type4_4[2] = {"0X00X00", "1X11X11"};
string type5[2] = {"1000001", "0111110"};//死五0
string type6[2] = {"X0000X", "X1111X"};//活四1024
string type7_1[2] = {"X00X00", "X11X11"};//眠四512
string type7_2[2] = {"00X0X0", "11X1X1"};
string type7_3[2] = {"10000", "01111"};
string type8_1[2] = {"100001", "011110"};//死四0
string type8_2[2] = {"10000X1", "01111X0"};
string type9_1[2] = {"X0X00X", "X1X11X"};//活三256
string type9_2[2] = {"X000X", "X111X"};
string type10_1[2] = {"1X000XX", "0X111XX"};//朦胧三32
string type10_2[2] = {"1XX000XX1", "0XX111XX0"};
string type10_3[2] = {"10X0X0X", "01X1X1X"};
string type11_1[2] = {"1X000XX1", "0X111XX0"};//眠三32
string type11_2[2] = {"10X0X0XX1", "01X1X1XX0"};
string type11_3[2] = {"1000XXX", "0111XXX"};
string type12_1[2] = {"1000XX1", "0111XX0"};//死三0
string type12_2[2] = {"10001", "01110"};
string type12_3[2] = {"1000X1", "0111X0"};
string type13_1[2] = {"XX00XX", "XX11XX"};//活二16
string type13_2[2] = {"XX0X0XX", "XX1X1XX"};
string type13_3[2] = {"0XX0", "1XX1"};
string type14_1[2] = {"0XXXX0", "1XXXX1"};//眠二3
string type14_2[2] = {"10XX0XX", "01XX1XX"};
string type14_3[2] = {"1X00XX", "0X11XX"};
string type15_1[2] = {"100XXX1", "011XXX0"};//死二0
string type15_2[2] = {"100X1", "011X0"};
string type15_3[2] = {"1001", "0110"};

int matchType(const string &s, const string &type) {
    string t = type;
    string t_rev = type;
    int num = 0;
    for (size_t i = 0; (i = s.find(t, i)) != std::string::npos; num++, i++);
    reverse(t_rev.begin(), t_rev.end());
    if (t != t_rev)
        for (size_t i = 0; (i = s.find(t, i)) != std::string::npos; num++, i++);
    return num;
};

bool canLazi(int board[19][19], int x, int y) {
    if (x >= 0 && x < 19 && y >= 0 && y < 19 && board[x][y] == EMPTY)
        return true;
    return false;
}

int evalRow(string row, int color) {
    int typeNum[15];
    memset(typeNum, 0, sizeof typeNum);
    typeNum[0] += matchType(row, type1[color]);
    typeNum[1] += matchType(row, type2[color]);
    typeNum[2] += matchType(row, type3_1[color]);
    typeNum[2] += matchType(row, type3_2[color]);
    typeNum[2] += matchType(row, type3_3[color]);
    typeNum[2] += matchType(row, type3_4[color]);
    typeNum[3] += matchType(row, type4_1[color]);
    typeNum[3] += matchType(row, type4_2[color]);
    typeNum[3] += matchType(row, type4_3[color]);
    typeNum[3] += matchType(row, type4_4[color]);
    typeNum[4] += matchType(row, type5[color]);
    typeNum[5] += matchType(row, type6[color]);
    typeNum[6] += matchType(row, type7_1[color]);
    typeNum[6] += matchType(row, type7_2[color]);
    typeNum[6] += matchType(row, type7_3[color]);
    typeNum[7] += matchType(row, type8_1[color]);
    typeNum[7] += matchType(row, type8_2[color]);
    typeNum[8] += matchType(row, type9_1[color]);
    typeNum[8] += matchType(row, type9_2[color]);
    typeNum[9] += matchType(row, type10_1[color]);
    typeNum[9] += matchType(row, type10_2[color]);
    typeNum[9] += matchType(row, type10_3[color]);
    typeNum[10] += matchType(row, type11_1[color]);
    typeNum[10] += matchType(row, type11_2[color]);
    typeNum[10] += matchType(row, type11_3[color]);
    typeNum[11] += matchType(row, type12_1[color]);
    typeNum[11] += matchType(row, type12_2[color]);
    typeNum[11] += matchType(row, type12_3[color]);
    typeNum[12] += matchType(row, type13_1[color]);
    typeNum[12] += matchType(row, type13_2[color]);
    typeNum[12] += matchType(row, type13_3[color]);
    typeNum[13] += matchType(row, type14_1[color]);
    typeNum[13] += matchType(row, type14_2[color]);
    typeNum[13] += matchType(row, type14_3[color]);
    typeNum[14] += matchType(row, type15_1[color]);
    typeNum[14] += matchType(row, type15_2[color]);
    typeNum[14] += matchType(row, type15_3[color]);
    int result =
            typeNum[0] * 100000000 + typeNum[1] * 100000000 + typeNum[2] * 1280 + typeNum[3] * 310 + typeNum[5] * 10240
            + typeNum[6] * 5120 + typeNum[8] * 2560 + typeNum[9] * 320 + typeNum[10] * 320 + typeNum[12] * 160
            + typeNum[13] * 30;
    result = result ? result : 1;
    return result;
}

bool check(int x, int y, int board[19][19]) {//判断四周是否有棋子
    for (int i = x - 1; i <= x + 1; i++) {
        if (i < 0)
            continue;
        if (i >= 19)
            break;
        for (int j = y - 1; j <= y + 1; j++) {
            if (j < 0)
                continue;
            if (j >= 19)
                break;
            if (board[i][j] != EMPTY)
                return true;
        }
    }
    return false;
}

int evalHor(int board[19][19], int color, int x, int y) {
    string row;
    for (int i = 0; i < 19; i++) {
        if (board[x][i] == BLACK)
            row.push_back('0');
        else if (board[x][i] == WHITE)
            row.push_back('1');
        else
            row.push_back('X');
    }
    return evalRow(row, color);
}

int evalVer(int board[19][19], int color, int x, int y) {
    string row;
    for (int i = 0; i < 19; i++) {
        if (board[i][y] == BLACK)
            row.push_back('0');
        else if (board[i][y] == WHITE)
            row.push_back('1');
        else
            row.push_back('X');
    }
    return evalRow(row, color);
}

int evalOblique1(int board[19][19], int color, int x, int y) {
    string row;
    if (x + y < 19)
        for (int i = x + y; i >= 0; i--) {
            if (board[x + y - i][i] == BLACK)
                row.push_back('0');
            else if (board[x + y - i][i] == WHITE)
                row.push_back('1');
            else
                row.push_back('X');
        }
    else
        for (int i = x + y - 18; i < 19; i++) {
            if (board[i][18 - (i - (x + y - 18))] == BLACK)
                row.push_back('0');
            else if (board[i][18 - (i - (x + y - 18))] == WHITE)
                row.push_back('1');
            else
                row.push_back('X');
        }
    return evalRow(row, color);
}

int evalOblique2(int board[19][19], int color, int x, int y) {
    string row;
    if (x >= y)
        for (int i = x - y; i < 19; i++) {
            if (board[i][i - (x - y)] == BLACK)
                row.push_back('0');
            else if (board[i][i - (x - y)] == WHITE)
                row.push_back('1');
            else
                row.push_back('X');
        }
    else
        for (int i = y - x; i < 19; i++) {
            if (board[i - (y - x)][i] == BLACK)
                row.push_back('0');
            else if (board[i - (y - x)][i] == WHITE)
                row.push_back('1');
            else
                row.push_back('X');
        }
    return evalRow(row, color);
}

int evalPoint(int board[19][19], int color, int x, int y) {
    int result = 0;
    int tempBoard[19][19];
    for (int i = 0; i < 19; i++)
        for (int j = 0; j < 19; j++)
            tempBoard[i][j] = board[i][j];
    tempBoard[x][y] = color;
//    result +=(evalHor(tempBoard, color, x, y) + evalVer(tempBoard, color, x, y) + evalOblique1(tempBoard, color, x, y) +
//             evalOblique2(tempBoard, color, x, y));
    result += evalHor(tempBoard, color, x, y) * 4;
    result += evalVer(tempBoard, color, x, y) * 4;
    result += evalOblique1(tempBoard, color, x, y) * 4;
    result += evalOblique2(tempBoard, color, x, y) * 4;
    tempBoard[x][y] = 1 - color;
    result += evalHor(tempBoard, 1 - color, x, y) * 3;
    result += evalVer(tempBoard, 1 - color, x, y) * 3;
    result += evalOblique1(tempBoard, 1 - color, x, y) * 3;
    result += evalOblique2(tempBoard, 1 - color, x, y) * 3;
//    grade[x][y] = result;
    return result;
}

bool cmp(Point p1, Point p2) {
    return p1.score > p2.score;
}

pair<pair<int, int>, pair<int, int>> search(int board[19][19], int color) {
    Point first_points[361], second_points[361], first_point{}, second_point{};
    first_point.score = 0;
    second_point.score = 0;
    int tempBoard[19][19];
    for (int i = 0; i < 19; i++)
        for (int j = 0; j < 19; j++)
            tempBoard[i][j] = board[i][j];
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            first_points[i * 19 + j].x = i;
            first_points[i * 19 + j].y = j;
            first_points[i * 19 + j].score = -1000000;
        }
    }
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (board[i][j] == EMPTY && check(i, j, board))
                first_points[i * 19 + j].score = evalPoint(board, color, i, j);
        }
    }
    sort(first_points, first_points + 361, cmp);
    for (int k = 0; k < 3; k++) {
        int x = first_points[k].x;
        int y = first_points[k].y;
        tempBoard[x][y] = color;
        for (int i = 0; i < 19; i++)
            for (int j = 0; j < 19; j++) {
                second_points[i * 19 + j].x = i;
                second_points[i * 19 + j].y = j;
                second_points[i * 19 + j].score = -1000000;
            }
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                if (tempBoard[i][j] == EMPTY && check(i, j, tempBoard))
                    second_points[i * 19 + j].score = evalPoint(tempBoard, color, i, j);
            }
        }
        sort(second_points, second_points + 361, cmp);
        if (first_points[k].score + second_points[0].score > first_point.score + second_point.score) {
            first_point = first_points[k];
            second_point = second_points[0];
        }
        tempBoard[x][y] = EMPTY;
    }
    return make_pair(make_pair(first_point.x, first_point.y), make_pair(second_point.x, second_point.y));
}

Reversi::Reversi() {
    client_socket = ClientSocket();
    oppositeColor = ownColor = -1;
    for (int i = 0; i < 19; i++)
        for (int j = 0; j < 19; j++)
            Board[i][j] = EMPTY;
    Board[9][9] = WHITE;
}

Reversi::~Reversi() {};

/*
 send id and password to server by socket
 rtn != 0 represents socket transfer error
 */
void Reversi::authorize(const char *id, const char *pass) {
    client_socket.connectServer();
    std::cout << "Authorize " << id << std::endl;
    char msgBuf[BUFSIZE];
    memset(msgBuf, 0, BUFSIZE);
    msgBuf[0] = 'A';
    memcpy(&msgBuf[1], id, 9);
    memcpy(&msgBuf[10], pass, 6);
    int rtn = client_socket.sendMsg(msgBuf);
    if (rtn != 0) printf("Authorized Failed!\n");
}

// 用户id输入，服务器上需要有对应的账号密码：对应文件 players-0.txt
void Reversi::gameStart() {
    struct tm *t;
    time_t tt;
    time(&tt);
    t = localtime(&tt);
    string s = to_string(t->tm_year + 1900) + "-" + to_string(t->tm_mon + 1) + "-" + to_string(t->tm_mday) + "-" +
               to_string(t->tm_hour) + ":" + to_string(t->tm_min) + ":" + to_string(t->tm_sec);
    system(("if [ ! -d \"db\" ];then mkdir " + s + "ChessBoard; fi").c_str());
//    system(("cd " + s + "ChessBoard;").c_str());
    char id[12] = {0}, passwd[10] = {0};
    //char id[12] = "111111110", passwd[10] = "123456";
    printf("ID: %s\n", id);
    scanf("%s", id);
    printf("PASSWD: %s\n", passwd);
    scanf("%s", passwd);

    authorize(id, passwd);

    printf("Game Start!\n");

    for (int round = 0; round < ROUNDS; round++) {
        for (int i = 0; i < 19; i++)
            for (int j = 0; j < 19; j++)
                Board[i][j] = EMPTY;
        Board[9][9] = WHITE;
        roundStart(round);
        oneRound(round, s);
        roundOver(round);
//        saveChessBoard(s, round);
    }
    gameOver();
    client_socket.close();
}

void Reversi::gameOver() {
    printf("Game Over!\n");
}

// 发一次消息，走哪一步，等两个消息，1.自己的步数行不行 2. 对面走了哪一步
void Reversi::roundStart(int round) {
    printf("Round %d Ready Start!\n", round);

    // first time receive msg from server
    int rtn = client_socket.recvMsg();
    if (rtn != 0) return;
    if (strlen(client_socket.getRecvMsg()) < 2)
        printf("Authorize Failed!\n");
    else
        printf("Round start received msg %s\n", client_socket.getRecvMsg());
    switch (client_socket.getRecvMsg()[1]) {
        // this client : black chessman
        case 'B':
            ownColor = 0;
            oppositeColor = 1;
            rtn = client_socket.sendMsg("BB");
            printf("Send BB -> rtn: %d\n", rtn);
            if (rtn != 0) return;
            break;
        case 'W':
            ownColor = 1;
            oppositeColor = 0;
            rtn = client_socket.sendMsg("BW");
            printf("Send BW -> rtn: %d\n", rtn);
            if (rtn != 0) return;
            break;
        default:
            printf("Authorized Failed!\n");
            break;
    }
}

void Reversi::oneRound(int round, string s) {
    int STEP = 1;
    switch (ownColor) {
        case 0:
            while (STEP < 10000) {

                pair<pair<int, int>, pair<int, int>> chess = step();                        // take action, send message

                // lazi only excute after server's message confirm  in observe function
                generateOneStepMessage(chess.first.first, chess.first.second,
                                       chess.second.first, chess.second.second);


                if (observe() >= 1) break;     // receive RET Code

                if (observe() >= 1) break;    // see white move
                STEP++;
                saveChessBoard(s, round);
            }
            printf("One Round End\n");
            break;
        case 1:
            while (STEP < 10000) {

                if (observe() >= 1) break;    // see black move

                pair<pair<int, int>, pair<int, int>> chess = step();                        // take action, send message
                // lazi only excute after server's message confirm  in observe function
                generateOneStepMessage(chess.first.first, chess.first.second,
                                       chess.second.first, chess.second.second);


                if (observe() >= 1) break;     // receive RET Code
                // saveChessBoard();
                STEP++;
                saveChessBoard(s, round);
            }
            printf("One Round End\n");
            break;

        default:
            break;
    }
}

void Reversi::roundOver(int round) {
    printf("Round %d Over!\n", round);
    // reset initializer

    ownColor = oppositeColor = -1;
}

int Reversi::observe() {
    int rtn = 0;
    int recvrtn = client_socket.recvMsg();
    if (recvrtn != 0) return 1;
    printf("receive msg %s\n", client_socket.getRecvMsg());
    switch (client_socket.getRecvMsg()[0]) {
        case 'R': {
            switch (client_socket.getRecvMsg()[1]) {
                case 'Y':   // valid step
                    switch (client_socket.getRecvMsg()[2]) {
                        case 'P':   // update chessboard
                        {
                            int desRow1 =
                                    (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
                            int desCol1 =
                                    (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
                            int desRow2 =
                                    (client_socket.getRecvMsg()[7] - '0') * 10 + client_socket.getRecvMsg()[8] - '0';
                            int desCol2 =
                                    (client_socket.getRecvMsg()[9] - '0') * 10 + client_socket.getRecvMsg()[10] - '0';
                            int color = (client_socket.getRecvMsg()[11] - '0');
                            //你应该在这里处理desRow和desCol，推荐使用函数
                            handleMessage(desRow1, desCol1, desRow2, desCol2, color);

                            printf("a valid step of : (%d %d) (%d %d)\n", desRow1, desCol1, desRow2, desCol2);
                            break;
                        }
                        case 'N':   // R0N: enemy wrong step
                        {
                            //
                            printf("a true judgement of no step\n");
                            break;
                        }
                    }

                    break;
                case 'W':
                    // invalid step
                    switch (client_socket.getRecvMsg()[2]) {
                        case 'P': {
                            int desRow1 =
                                    (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
                            int desCol1 =
                                    (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
                            int desRow2 =
                                    (client_socket.getRecvMsg()[7] - '0') * 10 + client_socket.getRecvMsg()[8] - '0';
                            int desCol2 =
                                    (client_socket.getRecvMsg()[9] - '0') * 10 + client_socket.getRecvMsg()[10] - '0';
                            int color = (client_socket.getRecvMsg()[11] - '0');
                            printf("Invalid step , server random a true step of : (%d %d) (%d %d)\n", desRow1, desCol1,
                                   desRow2, desCol2);
                            //你应该在这里处理desRow和desCol，推荐使用函数
                            handleMessage(desRow1, desCol1, desRow2, desCol2, color);
                            break;
                        }
                        case 'N': {
                            printf("a wrong judgement of no step\n");
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                case '1':

                    printf("Error -1: Msg format error!\n");
                    rtn = -1;
                    break;
                case '2':

                    printf("Error -2: Corrdinate error!\n");
                    rtn = -2;
                    break;
                case '4':

                    printf("Error -4: Invalid step!\n");
                    rtn = -4;
                    break;
                default:

                    printf("Error -5: Other error!\n");
                    rtn = -5;
                    break;
            }
            break;
        }
        case 'E': {
            switch (client_socket.getRecvMsg()[1]) {
                case '0':
                    // game over
                    rtn = 2;
                    break;
                case '1':
                    // round over
                    rtn = 1;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
    return rtn;
}

void Reversi::generateOneStepMessage(int row1, int col1, int row2, int col2) {
    char msg[BUFSIZE];
    memset(msg, 0, sizeof(msg));

    //put row and col in the message
    msg[0] = 'S';
    msg[1] = 'P';
    msg[2] = '0' + row1 / 10;
    msg[3] = '0' + row1 % 10;
    msg[4] = '0' + col1 / 10;
    msg[5] = '0' + col1 % 10;
    msg[6] = '0' + row2 / 10;
    msg[7] = '0' + row2 % 10;
    msg[8] = '0' + col2 / 10;
    msg[9] = '0' + col2 % 10;
    msg[10] = '\0';

    //print
    printf("generate one step at possition (%2d,%2d,%2d,%2d) : %s\n", row1, col1, row2, col2, msg);


    client_socket.sendMsg(msg);
}

/*-------------------------last three function--------------------------------
 * step : find a good position to lazi your chess.
 * saveChessBoard : save the chess board now.
 * handleMessage: handle the message from server.
 */

pair<pair<int, int>, pair<int, int>> Reversi::step() {
    //此处写算法
//    int r1 = rand() % 19;
//    int c1 = rand() % 19;
//    int r2 = rand() % 19;
//    int c2 = rand() % 19;
//    pair<int, int> step1 = make_pair(r1, c1);
//    pair<int, int> step2 = make_pair(r2, c2);
//    return make_pair(step1, step2);
    return search(Board, ownColor);
}

void Reversi::saveChessBoard(string s, int round) {
    ofstream ofs(s + "ChessBoard/round" + to_string(round) + ".txt", ios::app);
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (Board[i][j] == BLACK)
//                ofs<<"● ";
                ofs << "☻ ";
            else if (Board[i][j] == WHITE)
//                ofs<<"○ ";
                ofs << "☺ ";
            else
                ofs << "X  ";
        }
        ofs << endl;
    }
    ofs << endl << endl << endl;
}

void Reversi::handleMessage(int row1, int col1, int row2, int col2, int color) {
    if (color == ownColor)
        cout << "You have lazi " + string(ownColor ? "white" : "black") + " chesses on (" << row1 << ", " << col1
             << ") and (" << row2 << ", " << col2 << ")\n";
    else
        cout << "Your enemy have lazi " + string(!ownColor ? "white" : "black") + " chesses on (" << row1 << ", "
             << col1 << ") and (" << row2 << ", " << col2 << ")\n";
    Board[row1][col1] = color;
    Board[row2][col2] = color;
}
