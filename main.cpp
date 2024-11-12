// ИСТ-213 Егорова Д. А.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

using namespace std;

char menu_input, sort_menu_input, review_menu_input; // переменные для выбора в меню
vector<vector<string>> movies; // хранение данных про фильмы
vector<vector<string>> reviews; // хранение данных про отзывы
vector<int> k; //сохранение идентификаторов при поиске и написании отзыва

// Функция главного меню
void menu() {
    cout << "Что вы хотите сделать?" << endl
        << "0 - Выйти из программы" << endl
        << "1 - Показать все фильмы" << endl
        << "2 - Сортировать фильм по ..." << endl
        << "3 - Рандомный фильм" << endl
        << "4 - Поиск" << endl
        << "5 - Показать отзывы" << endl
        << "Введите число: ";

    cin >> menu_input;
}

// функция меню сортировки
void sort_menu() {
    cout << "Сортировать фильм по" << endl
        << "0 - Назад" << endl
        << "1 - Названию" << endl
        << "2 - Году выпуска" << endl
        << "3 - Оценке" << endl
        << "Введите число: ";

    cin >> sort_menu_input;
}

// меню для отзыва
void review_menu() {
    cout << "Хотите оставить отзыв фильму?" << endl
        << "0 - Нет" << endl
        << "1 - Да" << endl
        << "Введите число: ";

    cin >> review_menu_input;
}


// функция открытия файлов
vector<vector<string>> open_data(string file_name) {
    ifstream file(file_name); // открываем файл

    if (file) { // проверка открытия файла
        string line; // переменная для одной строки, в одной строке - один фильм/отзыв и вся информация про него
        while (getline(file, line)) { // считываем строки
            vector<string> info; // вектор для всех элементов одной строки
            string delimiter = " | "; // разделитель

            size_t pos = 0; // позиция в еще не раздленной строке
            string token; // переменная одного элемента
            while ((pos = line.find(delimiter)) != string::npos) { // ищем позицию нахождения разделителя до конца строки
                token = line.substr(0, pos); // выделяем из строки значения от начала до позиции нахождения разделителя
                info.push_back(token); //добавляем в вектор найденный элемент
                line.erase(0, pos + delimiter.length()); // удаляем то, что нашли и записали
            }
            info.push_back(line);
            if (file_name == "movies.txt") { // если функция вызывалась для фильмов,
                movies.push_back(info);      // то добавляем данные в вектор с фильмами
            }
            else if (file_name == "reviews.txt") { // если для отзывов
                reviews.push_back(info);           // то - в вектор с отзывами
            }
        }
        file.close(); // закрываем файл

        if (file_name == "movies.txt") {
            return movies;
        }
        else if (file_name == "reviews.txt") {
            return reviews;
        }
    }
    else {
        cout << "Ошибка открытия файла с данными!";
    }
}

// функция вывода данных
void print(vector<vector<string>> vec_name) {
    for (int i = 0; i < vec_name.size(); i++) {
        cout << setw(2) << left << i + 1 << " | "; // номер элемента
        for (int j = 0; j < vec_name[i].size(); j++) {
            if  (j == 0) cout << setw(35) << left << vec_name[i][j] << " | ";
            else if (vec_name[i].size() == 2 and j == 1) cout << vec_name[i][j];
            else if (j == 1) cout << setw(4) << left << vec_name[i][j] << " | ";
            else if (j == 2) cout << setw(20) << left << vec_name[i][j] << " | ";
            else if (j == 3) cout << setw(30) << left << vec_name[i][j] << " | ";
            else if (j == 4) cout << setw(3) << left << vec_name[i][j];
        }
        cout << endl;
    }
}

// функция сортировки фильмов
void sorting(char sortBy) {
    if (sortBy == '1') {
        sort(movies.begin(), movies.end(), [](const vector<string>& a, const vector<string>& b) { // сортировка от начала до конца двумерного массива, сравниваем два одномерных массива и n-ый элемент в этом массиве
            return a[0] < b[0]; // сортировка фильмов по нулевому элементу, т.е. названию
        });
    }
    else if (sortBy == '2') {
        sort(movies.begin(), movies.end(), [](const vector<string>& a, const vector<string>& b) {
            return a[1] > b[1]; // сортировка фильмов по первому элементу, т.е. году выпсука
        });
    }
    else if (sortBy == '3') {
        sort(movies.begin(), movies.end(), [](const vector<string>& a, const vector<string>& b) {
            return a[4] > b[4]; //сортировка фильмов по четвертому элементу, т.е. рейтингу
        });
    }
}

//функция рандомного фильма
void random_movie() {
    srand(time(NULL));
    int x;
    x = rand() % movies.size(); // генерируем рандомное число в пределах кол-ва фильмов

    for (int i = 0; i < movies[i].size(); i++) { // вывод х-той строки
        cout << movies[x][i] << " | ";
    }
    cout << endl;
}

// ввод отзыва
void review_input(int movie_id) {
    string review;
    getline(cin >> ws, review); // ввод с клавиатуры отзыва, ввод заканивается при нажатии enter
    ofstream reviews_file("reviews.txt", ios::app); // открытие файла без перезаписывания
    reviews_file << movies[movie_id][0] << ", "  << review << endl; // запись отзыва в отдельный файл с разделителем
}

// функция поиска
vector<int> finder(string request) {
    k.clear();
    for (int i = 0; i < movies.size(); i++) {
        for (int j = 0; j < 5; j++) {
            if (movies[i][j].find(request) != string::npos) { // ищем введенный пользователем текст
                cout << k.size() + 1<< " | ";
                for (int l = 0; l < 5; l++) {
                    cout << movies[i][l] << " | "; // и выводим всю строку, которой нашелся введенный текст
                }
                cout << endl;
                k.push_back(i); // сохраняем номер фильма в списке для того, чтобы потом при написании отзыва узнать название фильма
            }
        }
    }

    return k;
}

int main() {
    // локализация консоли
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int i, j, l, select_movie; // переменные для циклов for и для выбора фильма при поиске и написании отзыва
    string request; // переменная для поиска фильма

    open_data("movies.txt"); // открываем файл с фильмами
    open_data("reviews.txt"); // и отзывами
    menu();

    while (menu_input != '0') { // пока пользователь не введет 0 в главном меню программа бесконечно выполняется
        switch(menu_input) {
            case '1':
                system("cls");

                sorting('1');
                print(movies); // вывод всех фильмов отсортированных по алфавиту

                system("pause");
                system("cls");
                menu();
                break;
            case '2':
                system("cls");
                sort_menu(); // меню для выбора по какому параметру сортировать фильмы

                switch(sort_menu_input) {
                    case '0':
                        system("cls");
                        break;
                    case '1':
                        system("cls");
                        sorting('1'); // сортировка по названию, т.е. по первому элементу двумерного массива
                        print(movies);
                        break;
                    case '2':
                        system("cls");
                        sorting('2'); // сортировка по году выпуска, т.е. по второму элементу двумерного массива
                        print(movies);
                        break;
                    case '3':
                        system("cls");
                        sorting('3'); // сортировка по рейтингу, т.е. по последнему элементу двумерного массива
                        print(movies);
                        break;
                    default:
                        system("cls");
                        cout << "Введите корректные данные" << endl;
                        system("pause");
                        system("cls");
                        sort_menu();
                        break;
                }

                system("pause");
                system("cls");
                menu();
                break;
            case '3':
                system("cls");

                cout << "Ваш рандомный фильм: " << endl;
                random_movie(); // вывод рандомного фильма

                system("pause");
                system("cls");
                menu();
                break;
            case '4':
                system("cls");

                cout << "Напишите, что вы хотите найти? (Название, год, режиссер, жанр)" << endl;
                cin >> request;

                k = finder(request);

                if (k.size() == 0) {
                    cout << "По вышему запросу " << request << " ничего не найдено" << endl;
                }
                else {
                    review_menu(); // написание отзыва
                    switch(review_menu_input) {
                        case '1':
                            cout << "Выберите фильм из списка сверху: ";
                            cin >> select_movie;

                            cout << "Вы выбрали фильм: " << movies[k[select_movie - 1]][0] << endl
                                << "Напишите свой отзыв про фильм: ";
                            review_input(k[select_movie - 1]);

                            system("cls");
                            cout << "Спасибо за ваш отзыв" << endl;

                            system("pause");
                            system("cls");
                            break;
                        default:
                            system("cls");
                            cout << "Введите корректные данные" << endl;
                            system("pause");
                            system("cls");
                            break;
                    }
                }

                system("pause");
                system("cls");
                menu();
                break;
            case '5':
                system("cls");
                print(reviews); // вывод всех отзывов

                system("pause");
                system("cls");
                menu();
                break;
            default:
                system("cls");
                cout << "Введите корректные данные" << endl;

                system("pause");
                system("cls");
                menu();
                break;
        }
    }
return 0;
}
