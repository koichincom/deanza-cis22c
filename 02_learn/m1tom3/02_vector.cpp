#include <iostream>
#include <vector> // 動的配列

int main()
{
    std::vector<int> vec; // 拡張可能な配列

    // 要素を追加
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // 要素にアクセス
    std::cout << vec[1] << std::endl; // 出力: 20

    // サイズを超えても自動的に拡張される
    vec.push_back(40);
    vec.push_back(50);

    return 0;
}

/*
    サイズは自動的に変更されるが、特に中央や先頭に挿入するコストが高い
    vectorはどうしても連続性があるため、1つを入れると1つをずらす必要があるから
*/