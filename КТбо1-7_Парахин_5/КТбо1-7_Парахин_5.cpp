/*
МОП ЭВМ ИКТИБ ЮФУ
Программирование и основы теории алгоритмов 2
Парахин А.О. КТбо1-7
Индивидуальное задание №1 Вариант 5
ХХ.03.2023
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

// Структура для хранения таблицы переходов автомата.
typedef struct {
    int condition_num;          // Номер состояния автомата.
    map <char,int> transitions; // Хранит символы алфавита и состояния, в которые автомат перейдет по каждому символу.
    bool condition_allow;       // Статус состояния (допускающее или не допускающее).
} Cell;

// Функция инициализации таблицы переходов.
// Функция открывает файл, создаёт вектор структур (vector <Cell>)
// и в цикле записывает в него таблицу переходов автомата.
// 
// Входные данные: 
//      file - название файла, откуда будут браться данные для заполнения таблицы переходов.
// Выходные данные: 
//      table - заполненная таблица переходов в виде вектора структур (vector <Cell>).
vector <Cell> table_init(string file);

// Функция проверки вводимой строки на корректность.
// Функция проверяет введенное пользователем слово на соответствие алфавиту автомата,
// проходя по каждому символу входной строки и проверяя, соответствует ли такой символ алфавиту автомата.
// 
// Входные данные: 
//      str - строка, которую нужно проверить на корректность.
// Выходные данные:
//      answer - true, если слово соответствует алфавиту автомата, false, если не соответствует.
bool check_input(string& str);

// Функция реализации обработки одного символа входного слова.
// Функция получает нынешнее состояние автомата и в зависимости от поступающего символа строки, 
// возвращает следующее состояние, обращаясь к поступившей таблице переходов автомата 
// (реализует переход из одного состояния автомата в другое).
// 
// Входные данные: 
//      condition - нынешнее состояние автомата.
//      letter - поступающий символ входного слова.
//      table - заполненная таблица переходов автомата. 
// Выходные данные: 
//      table[condition].transitions[letter] - следующее состояние автомата.
int transition(int condition, char letter, vector <Cell>& table);

int main()
{
    setlocale(LC_ALL, "Russian");

    // input string
    string input_str;
    bool flag = true;
    //

    // transition table initialization
    vector <Cell> table;
    table = table_init("table.txt");
    //

    do {
        cout << "---------------------------------------------------" << endl;
        cout << "Введите входное слово: ";
        cin >> input_str;
        flag = check_input(input_str);

        if (flag) {

            int condition = 0, prev_con;
            char c = input_str[0];

            for (int i = 1; c != '\0'; i++) {

                prev_con = condition;
                condition = transition(condition, c, table);

                cout << endl << c << " q" << prev_con << " ->" << " q" << condition;

                c = input_str[i];
            }
            cout << endl << endl;

            if (table[condition].condition_allow == 1) {   // accepting state
                cout << "Yes" << endl;
            }
            else if (table[condition].condition_allow == 0) {
                cout << "No" << endl;                      // disallowable state
            }
            cout << "---------------------------------------------------" << endl;
            cout << "\nХотите ввести новое слово или завершить работу программы?\n1 - Ввести новое слово\n2 - Завершить работу программы" << endl;
        }
        else {
            cout << endl << "Вы ввели неправильную (несоответствующую алфавиту автомата) строку (Алфавит автомата: 0-9, +, -).\nХотите ввести входное слово заново или выйти из программы? \n1 - Ввести входное слово заново\n2 - Выйти из программы" << endl;
        }
        
        // Break or continue
        int oper = 0;
        cin >> oper;

        if (oper == 1) {
            flag = true;
        }
        else if (oper == 2) {
            flag = false;
            cout << endl << "Вы завершили работу программы.";
        }
        else {
            flag = false;
            cout << endl << "Ошибка ввода, такой операции нет (есть только 1 и 2). Программа остановлена.";
        }
        //

        cout << endl;
    } while (flag == 1);

    return 0;
}

vector <Cell> table_init(string file) {
    ifstream fin(file);
    int table_size;
    fin >> table_size;
    vector <Cell> table(table_size);

    int path1, path2, path3;
    for (int i = 0; i < table_size; i++) {
        fin >> table[i].condition_num >> path1 >> path2 >> path3 >> table[i].condition_allow;
        table[i].transitions['0'] = path1;

        table[i].transitions['1'] = path2;
        table[i].transitions['2'] = path2;
        table[i].transitions['3'] = path2;
        table[i].transitions['4'] = path2;
        table[i].transitions['5'] = path2;
        table[i].transitions['6'] = path2;
        table[i].transitions['7'] = path2;
        table[i].transitions['8'] = path2;
        table[i].transitions['9'] = path2;

        table[i].transitions['+'] = path3;
        table[i].transitions['-'] = path3;
    }

    return table;
}

bool check_input(string &str) {
    bool answer = true;
    char c = str[0];

    for (int i = 1; c != '\0'; i++) {
        if (!((c >= '0' && c <= '9') || (c == '+') || (c == '-'))) {
            answer = false;
        }
        c = str[i];
    }

    return answer;
}

int transition(int condition, char letter, vector <Cell>& table) {
    return table[condition].transitions[letter];
}