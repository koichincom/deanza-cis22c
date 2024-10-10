/* 
    LinedListは各要素nodeが次のnodeへのポインタptrを持つデータ構造
    メモリ内で要素が連続していないため、動的にデータを追加、削除できる

    シングルリンクリスト：次へのポインタ
    ダブルリンクリスト：前後にポインタ


*/

#include <iostream> // 標準入力出力ライブラリ
using namespace std;

// クラス Node は、リンクリストの各ノードを表すクラスです。
// 各ノードは「データ部分」と「次のノードへのポインタ」を持ちます。
class Node
{
public:
    int data;   // ノードが保持するデータ
    Node *next; // 次のノードへのポインタ
};

// リンクリストの最後に新しいノードを追加する関数
// head_ref: リストの先頭ノード（head）へのポインタのポインタ
// new_data: 新しく追加するデータ
void append(Node **head_ref, int new_data)
{
    // 1. 新しいノードのためにメモリを確保します
    Node *new_node = new Node();

    // 2. 新しいノードにデータをセットし、次のノードはないので NULL に設定
    new_node->data = new_data;
    new_node->next = NULL;

    // 3. リストが空の場合（head が NULL の場合）、新しいノードをリストの先頭に設定します
    if (*head_ref == NULL)
    {
        *head_ref = new_node; // head を新しいノードに設定
        return;               // 処理を終了
    }

    // 4. すでにノードがある場合、リストの最後まで移動して新しいノードを追加します
    Node *last = *head_ref; // リストの先頭からスタート

    // 5. リストの終端まで繰り返し（次のノードが NULL になるまでループ）
    while (last->next != NULL)
    {
        last = last->next; // 次のノードに移動
    }

    // 6. 最後のノードの次に、新しいノードを接続
    last->next = new_node;
}

// リンクリスト内のすべてのノードのデータを表示する関数
// node: リストの先頭ノードへのポインタ
void printList(Node *node)
{
    // 1. 現在のノードが NULL でない限りループ
    while (node != NULL)
    {
        cout << node->data << " "; // 現在のノードのデータを表示
        node = node->next;         // 次のノードに移動
    }
    cout << endl; // 改行して出力を見やすくします
}

// メイン関数: プログラムのエントリーポイント
int main()
{
    // 1. リストの最初は空なので、head を NULL に初期化
    Node *head = NULL;

    // 2. リストにデータを追加
    append(&head, 1); // 1を持つノードをリストに追加
    append(&head, 2); // 2を持つノードをリストに追加
    append(&head, 3); // 3を持つノードをリストに追加

    // 3. リストの内容を表示
    cout << "Linked List の内容: ";
    printList(head); // 1 2 3 と出力されるはず

    return 0;
}
