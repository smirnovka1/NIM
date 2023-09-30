#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

vector<int> rocks_num = {3, 4, 5};
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
    cout << "ДВА ИГРОКА ПО ОЧЕРЕДИ ЗАБИРАЮТ ОДИН ИЛИ НЕСКОЛЬКО КАМНЕЙ" << endl
         << "ИЗ ЛЮБОГО РЯДА. НЕ РАЗРЕШАЕТСЯ ЗА ОДИН ХОД БРАТЬ ФИШКИ ИЗ НЕСКОЛЬКИХ РЯДОВ." << endl
         << "ВЫИГРЫВАЕТ ТОТ, КТО ПОСЛЕДНИЙ ВОЗЬМЁТ ФИШКУ" << endl << endl;
}

int nim_sum()
{
    int nim = 0;
    for (int i = 0; i < rocks_num.size(); i++)
    {
        nim = nim ^ rocks_num[i];
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
    cout << "ТЕКУЩЕЕ КОЛИЧЕСТВО КАМНЕЙ В КУЧАХ" << endl << "1.   " << string(rocks_num[0], '#') <<
         "   (" << rocks_num[0] << ")" << endl << "2.   " << string(rocks_num[1], '#') << "   (" <<
         rocks_num[1] << ")" << endl << "3.   " << string(rocks_num[2], '#') << "   (" << rocks_num[2] << ")"
         << endl << endl;
}

bool game_ended()
{
    for (int i = 0; i < rocks_num.size(); i++)
    {
        if (rocks_num[i] > 0)
        {
            return false;
        }
    }
    return true;
}

void player_move()
{
    vector<int> good_rows;
    for(int i = 0; i < rocks_num.size(); i++){
        if (rocks_num[i] != 0)
            good_rows.push_back(i+1);
        else{
            good_rows.push_back(0);
        }
    }

    string row_number;
    char *char_row_number;
    cout << "Введите номер кучи, из которой хотите взять камни.\n";
    while (cin) {
        cin >> row_number;
        if (row_number.size() == 1) {
            char_row_number = new char[row_number.length() + 1];
            strcpy(char_row_number, row_number.c_str());
            if ((char_row_number[0] > '0') and (char_row_number[0] <= '9') and (count(good_rows.begin(), good_rows.end(), char_row_number[0] - '0'))) {
                break;
            }
        }
        cout << "Неправильный ввод, попробуйте ещё раз" << endl;
    }
    int res_row_number = char_row_number[0] - '0';

    string rocks_number;
    char *char_rocks_number;
    cout << "Введите количество камней, которое хотите взять.\n";
    while (cin) {
        cin >> rocks_number;
        if (rocks_number.size() == 1) {
            char_rocks_number = new char[rocks_number.length() + 1];
            strcpy(char_rocks_number, rocks_number.c_str());
            int resc = char_rocks_number[0] - '0';
            if ((char_rocks_number[0] > '0') and (char_rocks_number[0] <= '9') and (rocks_num[res_row_number - 1] >= resc)) {
                break;
            }
        }
        cout << "Неправильный ввод, попробуйте ещё раз" << endl;
    }
    int res_rocks_number = char_rocks_number[0] - '0';

    rocks_num[res_row_number - 1] -= res_rocks_number;
}

void ai_move()
{
    int nim_s = nim_sum();
    int i = 0;
    if (nim_s == 0)
    {
        while (rocks_num[i] == 0)
        {
            i++;
        }
        int rand_num = generate_rand_num(rocks_num[i]);
        cout << "Я забираю " << rand_num << " камень(камней) из кучи номер # "<< i+1 << ".\n";
        rocks_num[i] -= rand_num;
    }
    else
    {
        while(((rocks_num[i] ^ nim_s) >= rocks_num[i]) && (i < rocks_num.size()))
        {
            i++;
        }
        cout << "Я забираю " << rocks_num[i] - (rocks_num[i] ^ nim_s) << " камень(камней) из кучи # " << i + 1 << ".\n";
        rocks_num[i] = (rocks_num[i] ^ nim_s);
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
        cout << "УРА ПОБЕДА!" << endl;
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