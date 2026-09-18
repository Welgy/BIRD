
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
using namespace std;

bool kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}

char getch_nonblock() {
    return getchar();
}

int main()
{
    string head = "/|O>O|\\";
    int Y = 0, jump = 0, X = 16;
    bool stop = false;
    srand(time(0));
    int prohodY  = rand() % 19;
    prohodY += 3;
    int prohodX = 96;
    vector <int> vprohodY = {prohodY};
    vector <int> vprohodX = {prohodX};
    while(stop == false){
        if(Y == 23){
            stop = true;
        }
        cout << "\033[2J\033[H" << flush;
        if (kbhit() == true) {
        char key = getch_nonblock();
        if (key == ' ') jump = 5;
        }
        if(jump > 0){
            Y--;
            jump--;
        }
        else {
            Y++;
        }
        if(Y < 0){
            Y = 0;
        }
        for(int i = 0; i < vprohodX.size(); i++){
            vprohodX[i]--;
        }
         if(vprohodX.back() == 60){
                prohodY  = rand() % 19;
                prohodY += 3;
                vprohodY.push_back(prohodY);
                vprohodX.push_back(96);
            }
            if(vprohodX[0] == -4){
                vprohodX.erase(vprohodX.begin());
                vprohodY.erase(vprohodY.begin());
            }
        for(int i = 0; i < 25; i++){
            for(int j = 0; j < 100; j++){
                if(i == 24){
                    cout << "-";
                }
                if(Y == i && j == 15){
                    cout << head;
                    j += 6;
                }
                else {
                    bool flag = false;
                     for(size_t k = 0; k < vprohodX.size(); k++){
                    if(vprohodY[k] - 4 > i || vprohodY[k] + 4 < i){
                    if(vprohodX[k] - 3 <= j && vprohodX[k] + 3 >= j && i != 24){
                        flag = true;
                        if(Y == i && X - 3 <= j && X + 3 >= j){
                            stop = true;
                        }
                    }
                }
            }
            if(flag == true){
                cout << "O";
            }
            else cout << " ";
                }
                }
            cout << "\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return 0;
}