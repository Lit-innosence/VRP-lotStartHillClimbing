// input.hpp
#ifndef INPUT_H
#define INPUT_H

#include <bits/stdc++.h>
#include <fstream>
#include "input.h"
#include "variable.h"
using namespace std;

string AB; //ファイル名をAかBかを指定
string filenum1,filenum2; //ファイル名の番号
string filename; //ファイル名を格納


void input(){
    /*cout << "入力するファイル名について" << endl;
    cout << "A or B ?  :  "; cin >> AB;
    cout << "nの次の番号は ?  :  "; cin >> filenum1;
    cout << "kの次の番号は ?  :  "; cin >> filenum2;
    filename = AB + "-n" + filenum1 + "-k" + filenum2 + ".vrp";*/

    cout << "入力するファイル名は？："; cin >> filename;

    ifstream file("./../DataFiles/" + filename); //ファイルを開く

    if(!file.is_open()){ //ファイルが正常に開けなったとき
        cerr << "ファイルが正しく開けませんでした．どんまーーーーい ^_^" << endl;
        cerr << "そんなファイル名無いんじゃないの？？バカで草" << endl;
        cerr << "ねぇ悔しい？？ねぇねぇ！！！" << endl;
        cerr << "クッッッッッッソワロタwwwwwwwwwwwwwwwwwwww" << endl;
        exit(1);
    }

    string line;
    int i = 0;
    //1行目(顧客数と重量制限)
    while(getline(file,line)){
        stringstream ss(line);
        if(!(ss >> n >> q)) {
            ss >> n;
        }
        break;
    }
    //2行目以降
    while(getline(file,line)){
        stringstream ss(line);
        int i,x,y,l;
        if(!(ss >> i >> x >> y >> l)) break;

        coord_x.push_back(x);
        coord_y.push_back(y);
        luggage.push_back(l);
    }

    file.close(); //ファイルを閉じる


    //デバッグ用
    /*
    cout << "入力するファイル名  :  " << filename << endl;
    cout << "n: " << n << ", q: " << q << endl;
    for (int i = 0; i<coord_x.size(); i++) {
        cout << "coord_x[" << i << "]: " << coord_x.at(i)
        << ", coord_y[" << i << "]: " << coord_y.at(i)
        << ", luggage[" << i << "]: " << luggage.at(i) << endl;
    }
    */
}

#endif // INPUT_H