#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

vector<int> rows_num = {3, 4, 5};
int current_move;

void start();
int nim_sum();
int generate_rand_num(int x);
void choose_game();
void show_pieces();
bool game_ended();
void player_move();
void ai_move();
void new_move();
void win();

int main()
{
    start();
    show_pieces();
    choose_game();

    char game_t;
    cin >> game_t;

    if (game_t == 'Y' || game_t == 'y')
        current_move = 1;
    else
        current_move = 0;

    while (!game_ended()) {
        new_move();
    }
    win();

}


void start()
{
    cout << string(10, '#') << string(10, ' ') << "ИГРА НИМ" << string(10, ' ') <<
         string(10, '#') << endl << endl;
    cout << "ПРАВИЛА ИГРЫ:" << endl;
    cout << "ДВА ИГРОКА ПО ОЧЕРЕДИ ЗАБИРАЮТ ОДНУ ИЛИ НЕСКОЛЬКО ФИШЕК" << endl
         << "ИЗ ЛЮБОГО РЯДА. НЕ РАЗРЕШАЕТСЯ ЗА ОДИН ХОД БРАТЬ ФИШКИ ИЗ НЕСКОЛЬКИХ РЯДОВ." << endl
         << "ВЫИГРЫВАЕТ ТОТ, КТО ПОСЛЕДНИЙ ВОЗЬМЁТ ФИШКУ" << endl << endl;
}

int nim_sum()
{
    int nim = 0;
    for (int i = 0; i < rows_num.size(); i++)
    {
        nim = nim ^ rows_num[i];
    }
    return nim;
}

int generate_rand_num(int x)
{
    return rand() % x + 1;
}

void choose_game()
{
    cout << "ЕСЛИ ХОТИТЕ ХОДИТЬ ПЕРВЫМ - ВВЕДИТЕ 'y' ИЛИ 'Y'" << endl <<
         "В ИНОМ СЛУЧАЕ ВЫ БУДЕТЕ ХОДИТЬ ВТОРЫМ" << endl << endl;
}

void show_pieces()
{
    cout << "ТЕКУЩЕЕ КОЛИЧЕСТВО КАМНЕЙ В КУЧАХ" << endl << "1.   " << string(rows_num[0], '#') <<
         "   (" << rows_num[0] << ")" << endl << "2.   " << string(rows_num[1], '#') << "   (" <<
         rows_num[1] << ")" << endl << "3.   " << string(rows_num[2], '#') << "   (" << rows_num[2] << ")"
         << endl << endl;
}

bool game_ended()
{
    for (int i = 0; i < rows_num.size(); i++)
    {
        if (rows_num[i] > 0)
        {
            return false;
        }
    }
    return true;
}

void player_move()
{
    vector<int> good_rows;
    for(int i = 0; i<rows_num.size(); i++){
        if (rows_num[i] != 0)
            good_rows.push_back(i+1);
        else{
            good_rows.push_back(0);
        }
    }

    string num;
    char *char_num;
    cout << "Введите номер кучи, из которой хотите взять камни.\n";
    while (cin) {
        cin >> num;
        if (num.size() == 1) {
            char_num = new char[num.length() + 1];
            strcpy(char_num, num.c_str());
            if ((char_num[0] > '0') and (char_num[0] <= '9') and (count(good_rows.begin(),good_rows.end(),char_num[0]-'0'))) {
                break;
            }
        }
        cout << "Неправильный ввод, попробуйте ещё раз" << endl;
    }
    int resnum = char_num[0] - '0';

    string count1;
    char *char_count;
    cout << "Введите количество камней, которое хотите взять.\n";
    while (cin) {
        cin >> count1;
        if (count1.size() == 1) {
            char_count = new char[count1.length() + 1];
            strcpy(char_count, count1.c_str());
            int resc = char_count[0] - '0';
            if ((char_count[0] > '0') and (char_count[0] <= '9') and (rows_num[resnum-1] >= resc)) {
                break;
            }
        }
        cout << "Неправильный ввод, попробуйте ещё раз" << endl;
    }
    int rescount = char_count[0] - '0';

    rows_num[resnum-1] -= rescount;
}

void ai_move()
{
    int nim = nim_sum();
    int i = 0;
    if (nim == 0)
    {
        while (rows_num[i] == 0)
        {
            i++;
        }
        int rand_num = generate_rand_num(rows_num[i]);
        cout << "Я забираю " << rand_num << " камень(камней) из кучи номер # "<< i+1 << ".\n";
        rows_num[i] -= rand_num;
    }
    else
    {
        while(((rows_num[i] ^ nim) >= rows_num[i]) && (i < rows_num.size()))
        {
            i++;
        }
        cout << "Я забираю "<< rows_num[i] - (rows_num[i] ^ nim) << " камней из кучи # "<< i+1 << ".\n";
        rows_num[i] = (rows_num[i] ^ nim);
    }
}

void new_move()
{
    show_pieces();
    if (current_move == 1)
    {
        player_move();
    }
    else
    {
        ai_move();
    }
    current_move = (current_move+1) % 2;
}

void win()
{
    if(current_move % 2 == 0) {
        cout << "УРА УРА УРА ПОБЕДА!" << endl;
        cout <<
             "░░░░░░░░░░░░░░░░░░░░\n"
             "░░░░░░░░░░░░░░░░░░░░\n"
             "░░░░░▄▀▀▀▄░░░░░░░░░\n"
             "▄███▀░◐░░░▌░░░░░░░░░\n"
             "░░░░▌░░░░░▐░░░░░░░░░\n"
             "░░░░▐░░░░░▐░░░░░░░░░\n"
             "░░░░▌░░░░░▐▄▄░░░░░░░\n"
             "░░░░▌░░░░▄▀▒▒▀▀▀▀▄\n"
             "░░░▐░░░░▐▒▒▒▒▒▒▒▒▀▀▄\n"
             "░░░▐░░░░▐▄▒▒▒▒▒▒▒▒▒▒▀▄\n"
             "░░░░▀▄░░░░▀▄▒▒▒▒▒▒▒▒▒▒▀▄\n"
             "░░░░░░▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▀▄\n"
             "░░░░░░░░░░░▌▌░▌▌░░░░░\n"
             "░░░░░░░░░░░▌▌░▌▌░░░░░\n"
             "░░░░░░░░░▄▄▌▌▄▌▌░░░░░" << endl;
    }
    else{
        cout << "YOU LOST" << endl;
    }
}