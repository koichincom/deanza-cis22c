#include <iostream>
using namespace std;

int main()
{
    int arr[5]; // 固定サイズの配列（5要素）

    // 配列に値を代入
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    // 配列の要素にアクセス
    cout << arr[2] << endl; // 出力: 30

    return 0;
}

/* 
    基本的にサイズの変更が不可能　
    連続しているメモリを利用しているため削除や挿入も無理
*/