#include <iostream>
#include <string>
#include <set>
#include <ctime>
#include <fstream>

#define N 4 // number of card per game
#define M 4 // number of operator 

class TwentyFour {
    private:
        std::string cards[N];
        int cardsValues[N];
        std::string operators[M] = {" + ", " - ", " * ", " / "};
        std::set <std::string> results;

        // Mengubah sebuah kartu (string) menjadi nilai yang sesuai (int)
        // contoh "A" -> 1
        int toValue(std::string s){
            if (s == "10") return 10;
            char c = s[0];
            if (c >= '2' && c <= '9') return c - 48;
            else if (c == 'a' || c == 'A') return 1;
            else if (c == 'j' || c == 'J') return 11;
            else if (c == 'q' || c == 'Q') return 12;
            else if (c == 'k' || c == 'K') return 13;
            return -999;
        }

        // Mengubah sebuah nilai (int) menjadi kartu yang sesuai (string)
        // contoh 13 -> "K"
        std::string toCard(int val){
            if (val > 0 && val < 11) return std::to_string(val);
            else {
                if (val == 11) return "J";
                else if (val == 12) return "Q";
                else return "K";
            };
        }

        // Memeriksa apakah input string yang diterima sesuai dengan kartu yang mungkin
        bool validate(std::string s){
            if (s == "10") return true;
            if (s.length() > 1) return false;

            char c = s[0];
            if (c >= '2' && c <= '9') return true;
            else if (c == 'a' || c == 'A') return true;
            else if (c == 'j' || c == 'J') return true;
            else if (c == 'q' || c == 'Q') return true;
            else if (c == 'k' || c == 'K') return true;

            else return false;
        }

        // Memeriksa semua kartu yang dimainkan
        bool checkCard(){
            bool valid = false;

            while (!valid) {
            for (auto &card: cards){
                if (!validate(card)){
                    std::cout << "Masukan tidak valid" << '\n';
                    return false;
                } else {
                    valid = true;
                }
            }
            }
            return valid;
        }

        // Melakukan input kartu dari user
        bool inputCard(){
            std::cout << "Masukan 4 kartu yang akan dihitung : " << '\n';

            for(auto &card: cards){
                std::cin >> card;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            return checkCard();
        }

        // Meng-output nilai dari kartu yang dimainkan
        void printValues(){
            for (auto value: cardsValues) {
                std::cout << value << " ";
            }
            std::cout << '\n';
        }

        // Meng-output kartu yang dimainkan
        void printCards(){
            for (auto card: cards){
                std::cout << card << " ";
            }
            std::cout << '\n';
        }

        // Menghitung semua kemungkinan yang menghasilkan nilai 24
        void calculate(){
            
            // loop for all possible combination of card
            for (int i = 0; i < N ; i++){
            for (int j = 0; j < N; j++){
                if (i == j) continue;
            for (int k = 0; k < N; k++){
                if (k == i || k == j) continue;
            for (int l = 0; l < N; l++){
                if (l == i || l == j || l == k) continue; 
                
                // loop for three out of four operation
                for (int m = 0; m < M; m++){
                for (int n = 0; n < M; n++){
                for (int o = 0; o < M; o++){ 

                    std::string op1 = operators[m];
                    std::string op2 = operators[n];
                    std::string op3 = operators[o];

                    std::string term1;
                    std::string term2;
                    std::string result;

                    int a = cardsValues[i];
                    int b = cardsValues[j];
                    int c = cardsValues[k];
                    int d = cardsValues[l];

                    float sum;
                    float sum1, sum2;
                    
                    // ((a op1 b) op2 c) op3 d
                    sum = a;
                    if (m == 0) sum += + b;
                    else if (m == 1) sum -= b;
                    else if (m == 2) sum *= b;
                    else if (m == 3) sum /= (float)b;

                    if (n == 0) sum += c;
                    else if (n == 1) sum -= c;
                    else if (n == 2) sum *= c;
                    else if (n == 3) sum /= (float)c;
                       
                    if (o == 0) sum += d;
                    else if (o == 1) sum -= d;
                    else if (o == 2) sum *= d;
                    else if (o == 3) sum /= (float)d;

                    if (sum == 24) {
                        term1 = "(" + std::to_string(a) + op1 + std::to_string(b) + ")";
                        term2 = "(" + term1 + op2 + std::to_string(c) + ")";
                        result = term2 + op3 + std::to_string(d);
                        results.insert(result);
                    }

                    // (a op1 (b op2 c)) op3 d
                    if (n == 0) sum1 = b + c;
                    else if (n == 1) sum1 = b - c;
                    else if (n == 2) sum1 = b * c;
                    else if (n == 3) sum1 = b / (float)c;

                    if (m == 0) sum = a + sum1;
                    else if (m == 1) sum = a - sum1;
                    else if (m == 2) sum = a * sum1;
                    else if (m == 3) sum = a / (float)sum1;

                    if (o == 0) sum += d;
                    else if (o == 1) sum -= d;
                    else if (o == 2) sum *= d;
                    else if (o == 3) sum /= (float)d;

                    if (sum == 24) {
                        term1 = "(" + std::to_string(a) + op1 + "(" + std::to_string(b) + op2 + std::to_string(c) + "))";
                        result = term1 + op3 + std::to_string(d);
                        results.insert(result);
                    }
                    
                    // a op1 ((b op2 c) op3 d)
                    if (n == 0) sum1 = b + c;
                    else if (n == 1) sum1 = b - c;
                    else if (n == 2) sum1 = b * c;
                    else if (n == 3) sum1 = b / (float)c;

                    if (o == 0) sum = sum1 + d;
                    else if (o == 1) sum = sum1 - d;
                    else if (o == 2) sum = sum1 * d;
                    else if (o == 3) sum = sum1 / (float)d;

                    if (m == 0) sum = a + sum;
                    else if (m == 1) sum = a - sum;
                    else if (m == 2) sum = a * sum;
                    else if (m == 3) sum = a / (float)sum;

                    if (sum == 24) {
                        term1 = "(" + std::to_string(b) + op2 + std::to_string(c) + ")";
                        term2 = "(" + term1 + op3 + std::to_string(d) + ")";
                        result = std::to_string(a) + op1 + term2;
                        results.insert(result);
                    }

                    // a op1 (b op2 (c op3 d))
                    if (o == 0) sum1 = c + d;
                    else if (o == 1) sum1 = c - d;
                    else if (o == 2) sum1 = c * d;
                    else if (o == 3) sum1 = c / (float)d;

                    if (n == 0) sum2 = b + sum1;
                    else if (n == 1) sum2 = b - sum1;
                    else if (n == 2) sum2 = b * sum1;
                    else if (n == 3) sum2 = b / (float)sum1;

                    if (m == 0) sum = a + sum2;
                    else if (m == 1) sum = a - sum2;
                    else if (m == 2) sum = a * sum2;
                    else if (m == 3) sum = a / (float)sum2;

                    if (sum == 24) {
                        term1 = "(" + std::to_string(b) + op2 + "(" + std::to_string(c) + op3 + std::to_string(d) + "))";
                        result = std::to_string(a) + op1 + term1;
                        results.insert(result);
                    }

                    
                    // (a op1 b) op2 (c op3 d)
                    if (m == 0) sum1 = a + b;
                    else if (m == 1) sum1 = a - b;
                    else if (m == 2) sum1 = a * b;
                    else if (m == 3) sum1 = a / (float)b;
                        
                    if (o == 0) sum2 = c + d;
                    else if (o == 1) sum2 = c - d;
                    else if (o == 2) sum2 = c * d;
                    else if (o == 3) sum2 = c / (float)d;

                    if (n == 0) sum = sum1 + sum2;
                    else if (n == 1) sum = sum1 - sum2;
                    else if (n == 2) sum = sum1 * sum2;
                    else if (n == 3) sum = sum1 / (float)sum2;


                    if (sum == 24) {
                        term1 = "(" + std::to_string(a) + op1 + std::to_string(b) + ")";
                        term2 = "(" + std::to_string(c) + op3 + std::to_string(d) + ")";
                        result = term1 + op2 + term2 ;
                        results.insert(result);
                    }

                }
                }
            }
            }
            }
        }
        }
        }
    
        // Meng-output jumlah solusi dan solusi yang ditemukan
        void printResult(){
            if (results.size() == 0){
                std::cout << "Tidak ditemukan solusi" << '\n';
            } else {
                std::cout <<  results.size() << " solusi ditemukan" << '\n';
                for (auto result: results){
                    std::cout << result << '\n';
                }
            }
        }

        // Menanyakan user apakah hasil ingin disimpan
        int savePrompt(){
            std::cout << "Apakah ingin menyimpan solusi? [y/N]" << '\n';
            char input;
            std::cin >> input;
            if (input == 'Y' || input == 'y') return 1;
            else return 0;
        }

        // Menyimpan solusi ke dalam file yang ditentukan user
        void writeToFile(long long time_m, long long time_p){
            std::ofstream file;
            std::string filename;

            std::cout << "Masukan nama file yang akan disimpan" << '\n';
            std::cin >> filename;

            file.open(filename + ".txt");
            for (auto card: cards){
                file << card << " ";
            } 
            file << '\n';
            if (results.size() == 0){
                file << "Tidak ditemukan solusi" << '\n';
            } else {
                file <<  results.size() << " solusi ditemukan" << '\n';
                for (auto result: results){
                    file << result << '\n';
                }
            }
            if(time_m == 0){
                file << "Waktu eksekusi algoritma: " << time_p << " microsecond" << '\n';
            } else {
                file << "Waktu eksekusi algoritma: " << time_m << " millisecond" << '\n';
            }

            file.close();
        }

    public:
        // Menginisiasi game 24 dengan input dari user
        void newGame(){
            while(!inputCard());

            for (int i = 0; i < N; i++) {
                cardsValues[i] = toValue(cards[i]);
            }
        }

        // Menginisiasi game 24 dengan kartu random
        void randomGame(){
            srand ( time(NULL) );
            for (int i = 0; i < N; i++) {
                cardsValues[i] = rand() % 13 + 1;
            }
            for (int i = 0; i < N; i++) {
                cards[i] = toCard(cardsValues[i]);
            }
            std::cout << "Kartu random: " << '\n';
            printCards();
        }

        // Menghasilkan solusi yang ditemukan
        void resultGame(){
            calculate();
            printResult();
        }

        // Mengakhiri game dengan save prompt
        void endGame(long long time_m, long long time_p){
            if(savePrompt()) writeToFile(time_m, time_p);
        }
};