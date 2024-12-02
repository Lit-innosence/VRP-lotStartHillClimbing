#include <bits/stdc++.h>
#include <fstream>
using namespace std;

string AB; //ファイル名をAかBかを指定
string filenum1,filenum2; //ファイル名の番号
string filename; //ファイル名を格納

int n;  // 顧客数
int q;  // トラックの積載量
vector<int> coord_x, coord_y;   // 顧客のx座標，y座標
vector<int> luggage;            // 顧客の荷物量

vector<vector<int>> route;   // トラックの配送経路

void input(){
    cout << "入力するファイル名について" << endl;
    cout << "A or B ?  :  "; cin >> AB;
    cout << "nの次の番号は ?  :  "; cin >> filenum1;
    cout << "kの次の番号は ?  :  "; cin >> filenum2;

    filename = AB + "-n" + filenum1 + "-k" + filenum2 + ".vrp";

    ifstream file(filename); //ファイルを開く

    if(!file.is_open()){ //ファイルが正常に開けなったとき
        cerr << "ファイルが正しく開けませんでした．どんまーーーーい ^_^" << endl;
        return 1;
    }

    string line;
    //1行目(顧客数と重量制限)
    while(getline(file,line)){
        stringstream ss(line);
        ss >> n >> q;
    }
    //2行目以降
    int i = 0;
    while(getline(file,line)){
        stringstream ss(line);
        int x,y,l;
        ss >> x >> y >> l;

        coord_x.push_back(x);
        coord_y.push_back(y);
        luggage.push_back(l);

        i++;
    }

    file.close(); //ファイルを閉じる

    //デバッグ用
    cout << "n: " << n << ", q: " << q << endl;
    for (int i = 0; i<coord_x.size(); i++) {
        cout << "coord_x[" << i << "]: " << coord_x.at(i) 
        << ", coord_y[" << i << "]: " << coord_y.at(i) 
        << ", luggage[" << i << "]: " << luggage.at(i) << endl;
    }
}