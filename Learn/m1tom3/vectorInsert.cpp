#include <iostream>
#include <vector>

int main(){
    std::vector<int> vec = {10, 20, 30, 40, 50};

    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }

    std::cout << std::endl;

    vec.insert(vec.begin() + 1, 25);

    for (int i = 0; i < vec.size(); i++){
        std::cout << vec[i] << " ";
    }

    std::cout << std::endl;

    vec.erase(vec.begin() + 2);

    for (int i = 0; i < vec.size(); ++i){
        std::cout << vec[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}