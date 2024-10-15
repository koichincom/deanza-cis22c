#include <iostream>
#include <algorithm>

int main()
{
    int arr[] = {30, 10, 20, 40};

    // 配列をソート（昇順）
    std::sort(arr, arr + 4);

    // ソートされた配列を出力
    for (int i = 0; i < 4; i++)
    {
        std::cout << arr[i] << " "; // 出力: 10 20 30 40
    }

    return 0;
}
