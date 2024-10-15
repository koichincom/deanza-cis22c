#include <iostream>
#include <unordered_map>

int main()
{
    // ハッシュテーブル（unordered_mapを使用）
    std::unordered_map<std::string, int> hashTable;

    // 要素を追加
    hashTable["apple"] = 10;
    hashTable["banana"] = 20;
    hashTable["orange"] = 30;

    // 要素にアクセス
    std::cout << "Apple: " << hashTable["apple"] << std::endl;   // 出力: 10
    std::cout << "Banana: " << hashTable["banana"] << std::endl; // 出力: 20

    return 0;
}
