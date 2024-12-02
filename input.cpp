#include <bits/stdc++.h>
#include <fstream>
using namespace std;

string AB; //ファイル名をAかBかを指定
int filenum; //ファイル名の番号

int n;  // 顧客数
int q;  // トラックの積載量
vector<int> coord_x, coord_y;   // 顧客のx座標，y座標
vector<int> luggage;            // 顧客の荷物量

vector<vector<int>> route;   // トラックの配送経路

void input(){
    cout << "入力するファイル名について" << endl;
    cout << "A or B ? :" << endl; cin >> AB;
    cout << "番号は ? :" << endl; cin >> filenum;
}