#include <iostream>
#include <array>

int main()
{
    // std::arrayは固定長の配列を扱うクラステンプレート
    // 5つの要素を持つ配列arrを初期化
    std::array<int, 5> arr = {10, 20, 30, 40, 50};

    // 挿入する値（20の後に25を入れる）
    int insert_value = 25;

    // 後ろの要素をシフトして、挿入するスペースを作る処理
    // 配列の最後から2番目までの要素を1つ後ろにシフトする
    // arr[4] <- arr[3], arr[3] <- arr[2] という感じ
    for (int i = arr.size() - 1; i > 1; --i)
    {
        arr[i] = arr[i - 1]; // 1つ前の値を後ろにシフト
    }

    // シフト後、arr[1]の位置（2番目）に新しい値を挿入
    arr[1] = insert_value;

    // 配列の内容を表示する
    for (int i = 0; i < arr.size(); ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
