// ���-213 ������� �. �.

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

char menu_input, sort_menu_input, review_menu_input; // ���������� ��� ������ � ����
vector<vector<string>> movies; // �������� ������ ��� ������
vector<vector<string>> reviews; // �������� ������ ��� ������
vector<int> k; //���������� ��������������� ��� ������ � ��������� ������

// ������� �������� ����
void menu() {
    cout << "��� �� ������ �������?" << endl
        << "0 - ����� �� ���������" << endl
        << "1 - �������� ��� ������" << endl
        << "2 - ����������� ����� �� ..." << endl
        << "3 - ��������� �����" << endl
        << "4 - �����" << endl
        << "5 - �������� ������" << endl
        << "������� �����: ";

    cin >> menu_input;
}

// ������� ���� ����������
void sort_menu() {
    cout << "����������� ����� ��" << endl
        << "0 - �����" << endl
        << "1 - ��������" << endl
        << "2 - ���� �������" << endl
        << "3 - ������" << endl
        << "������� �����: ";

    cin >> sort_menu_input;
}

// ���� ��� ������
void review_menu() {
    cout << "������ �������� ����� ������?" << endl
        << "0 - ���" << endl
        << "1 - ��" << endl
        << "������� �����: ";

    cin >> review_menu_input;
}


// ������� �������� ������
vector<vector<string>> open_data(string file_name) {
    ifstream file(file_name); // ��������� ����

    if (file) { // �������� �������� �����
        string line; // ���������� ��� ����� ������, � ����� ������ - ���� �����/����� � ��� ���������� ��� ����
        while (getline(file, line)) { // ��������� ������
            vector<string> info; // ������ ��� ���� ��������� ����� ������
            string delimiter = " | "; // �����������

            size_t pos = 0; // ������� � ��� �� ���������� ������
            string token; // ���������� ������ ��������
            while ((pos = line.find(delimiter)) != string::npos) { // ���� ������� ���������� ����������� �� ����� ������
                token = line.substr(0, pos); // �������� �� ������ �������� �� ������ �� ������� ���������� �����������
                info.push_back(token); //��������� � ������ ��������� �������
                line.erase(0, pos + delimiter.length()); // ������� ��, ��� ����� � ��������
            }
            info.push_back(line);
            if (file_name == "movies.txt") { // ���� ������� ���������� ��� �������,
                movies.push_back(info);      // �� ��������� ������ � ������ � ��������
            }
            else if (file_name == "reviews.txt") { // ���� ��� �������
                reviews.push_back(info);           // �� - � ������ � ��������
            }
        }
        file.close(); // ��������� ����

        if (file_name == "movies.txt") {
            return movies;
        }
        else if (file_name == "reviews.txt") {
            return reviews;
        }
    }
    else {
        cout << "������ �������� ����� � �������!";
    }
}

// ������� ������ ������
void print(vector<vector<string>> vec_name) {
    for (int i = 0; i < vec_name.size(); i++) {
        cout << setw(2) << left << i + 1 << " | "; // ����� ��������
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

// ������� ���������� �������
void sorting(char sortBy) {
    if (sortBy == '1') {
        sort(movies.begin(), movies.end(), [](const vector<string>& a, const vector<string>& b) { // ���������� �� ������ �� ����� ���������� �������, ���������� ��� ���������� ������� � n-�� ������� � ���� �������
            return a[0] < b[0]; // ���������� ������� �� �������� ��������, �.�. ��������
        });
    }
    else if (sortBy == '2') {
        sort(movies.begin(), movies.end(), [](const vector<string>& a, const vector<string>& b) {
            return a[1] > b[1]; // ���������� ������� �� ������� ��������, �.�. ���� �������
        });
    }
    else if (sortBy == '3') {
        sort(movies.begin(), movies.end(), [](const vector<string>& a, const vector<string>& b) {
            return a[4] > b[4]; //���������� ������� �� ���������� ��������, �.�. ��������
        });
    }
}

//������� ���������� ������
void random_movie() {
    srand(time(NULL));
    int x;
    x = rand() % movies.size(); // ���������� ��������� ����� � �������� ���-�� �������

    for (int i = 0; i < movies[i].size(); i++) { // ����� �-��� ������
        cout << movies[x][i] << " | ";
    }
    cout << endl;
}

// ���� ������
void review_input(int movie_id) {
    string review;
    getline(cin >> ws, review); // ���� � ���������� ������, ���� ������������ ��� ������� enter
    ofstream reviews_file("reviews.txt", ios::app); // �������� ����� ��� ���������������
    reviews_file << movies[movie_id][0] << ", "  << review << endl; // ������ ������ � ��������� ���� � ������������
}

// ������� ������
vector<int> finder(string request) {
    k.clear();
    for (int i = 0; i < movies.size(); i++) {
        for (int j = 0; j < 5; j++) {
            if (movies[i][j].find(request) != string::npos) { // ���� ��������� ������������� �����
                cout << k.size() + 1<< " | ";
                for (int l = 0; l < 5; l++) {
                    cout << movies[i][l] << " | "; // � ������� ��� ������, ������� ������� ��������� �����
                }
                cout << endl;
                k.push_back(i); // ��������� ����� ������ � ������ ��� ����, ����� ����� ��� ��������� ������ ������ �������� ������
            }
        }
    }

    return k;
}

int main() {
    // ����������� �������
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int i, j, l, select_movie; // ���������� ��� ������ for � ��� ������ ������ ��� ������ � ��������� ������
    string request; // ���������� ��� ������ ������

    open_data("movies.txt"); // ��������� ���� � ��������
    open_data("reviews.txt"); // � ��������
    menu();

    while (menu_input != '0') { // ���� ������������ �� ������ 0 � ������� ���� ��������� ���������� �����������
        switch(menu_input) {
            case '1':
                system("cls");

                sorting('1');
                print(movies); // ����� ���� ������� ��������������� �� ��������

                system("pause");
                system("cls");
                menu();
                break;
            case '2':
                system("cls");
                sort_menu(); // ���� ��� ������ �� ������ ��������� ����������� ������

                switch(sort_menu_input) {
                    case '0':
                        system("cls");
                        break;
                    case '1':
                        system("cls");
                        sorting('1'); // ���������� �� ��������, �.�. �� ������� �������� ���������� �������
                        print(movies);
                        break;
                    case '2':
                        system("cls");
                        sorting('2'); // ���������� �� ���� �������, �.�. �� ������� �������� ���������� �������
                        print(movies);
                        break;
                    case '3':
                        system("cls");
                        sorting('3'); // ���������� �� ��������, �.�. �� ���������� �������� ���������� �������
                        print(movies);
                        break;
                    default:
                        system("cls");
                        cout << "������� ���������� ������" << endl;
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

                cout << "��� ��������� �����: " << endl;
                random_movie(); // ����� ���������� ������

                system("pause");
                system("cls");
                menu();
                break;
            case '4':
                system("cls");

                cout << "��������, ��� �� ������ �����? (��������, ���, ��������, ����)" << endl;
                cin >> request;

                k = finder(request);

                if (k.size() == 0) {
                    cout << "�� ������ ������� " << request << " ������ �� �������" << endl;
                }
                else {
                    review_menu(); // ��������� ������
                    switch(review_menu_input) {
                        case '1':
                            cout << "�������� ����� �� ������ ������: ";
                            cin >> select_movie;

                            cout << "�� ������� �����: " << movies[k[select_movie - 1]][0] << endl
                                << "�������� ���� ����� ��� �����: ";
                            review_input(k[select_movie - 1]);

                            system("cls");
                            cout << "������� �� ��� �����" << endl;

                            system("pause");
                            system("cls");
                            break;
                        default:
                            system("cls");
                            cout << "������� ���������� ������" << endl;
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
                print(reviews); // ����� ���� �������

                system("pause");
                system("cls");
                menu();
                break;
            default:
                system("cls");
                cout << "������� ���������� ������" << endl;

                system("pause");
                system("cls");
                menu();
                break;
        }
    }
return 0;
}
