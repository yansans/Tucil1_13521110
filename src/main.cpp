#include <limits>
#include <chrono>
#include "lib.cpp"

// Menu utama dari aplikasi 
// output yang mungkin hanya 1 untuk input manual atau 2 untuk rando
int menu(){
    std::string input;
    std::cout << "Selamat datang ke Make It 24 Solver!" << '\n';
    std::cout << "Menu:" << '\n';
    std::cout << "1. Memasukkan kartu sendiri" << '\n';
    std::cout << "2. Mendapatkan kartu secara random" << '\n';

    while(true){
        std::cout << "Pilihan menu: ";
        std::cin >> input;
        if(input == "1") {
            return 1;
        } else if (input == "2"){
            return 2;
        } else {
            std::cout << "Menu tidak dikenal. Silahkan coba lagi" << '\n';
        }
    }
}

int main(){

    TwentyFour game;
    int input = menu();

    input == 1 ? game.newGame() : game.randomGame();

    auto start = std::chrono::high_resolution_clock::now();
    game.resultGame();
    auto end = std::chrono::high_resolution_clock::now();

    auto exec_time_m = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    auto exec_time_p = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

    if(exec_time_m == 0){
        std::cout << "Waktu eksekusi algoritma: " << exec_time_p << " microsecond" << '\n';
    } else {
        std::cout << "Waktu eksekusi algoritma: " << exec_time_m << " millisecond" << '\n';
    }

    game.endGame(exec_time_m, exec_time_p);

    return 0;
}