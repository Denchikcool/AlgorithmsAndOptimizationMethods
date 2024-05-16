#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int N = 0;
int M = 0;

class Fraction {
private:
    //печатать матрицу
    void printMatrix(vector<vector<pair<long long, long long>>> matrix)
    {
        for (int i = 0; i < M + 3; i++) cout << "-------";
        cout << endl;
        for (int i = 0; i < N; i++)
        {
            for (int j = 1; j < M + 1; j++)
                cout << matrix[i][j].first << "\t";
            cout << "|\t" << matrix[i][0].first << "\t|" << endl;
        }
        for (int i = 0; i < M + 3; i++) cout << "-------";
        cout << endl;
    }

    //фулл таблица 
    void printSimplexTableCO(vector<vector<pair<long long, long long>>> matrix, vector<pair<long long, long long>> CO)
    {
        for (int i = 0; i < M + 2; i++) cout << "---------";
        cout << endl;

        cout << "\t\t";
        for (int i = 0; i < M; i++) cout << "x" << i + 1 << "\t";
        cout << "CO    |\n";

        for (int i = 0; i < M + 2; i++) cout << "---------";
        cout << endl;

        for (int i = 0; i < N + 2; i++)
        {
            if (i < N)
            {
                for (int j = 1; j < M + 1; j++)
                    if (matrix[i][j].first == 1 && matrix[i][j].second == 1)
                    {
                        int fl = 0;
                        for (int k = 0; k < N + 2; k++)
                            if (matrix[k][j].first != 0)
                                fl++;
                        if (fl == 1)
                            cout << "x" << j << "\t";
                    }
            }
            else if (i == N)
                cout << "Z\t";
            else
                cout << "M\t";

            for (int j = 0; j < M + 1; j++)
            {
                cout << matrix[i][j].first;
                if (matrix[i][j].second != 1 && matrix[i][j].first != 0)
                    cout << "/" << matrix[i][j].second;
                cout << "\t";
            }

            if (i < N)
            {
                if (CO[i].first >= 0 && CO[i].second > 0)
                {
                    cout << CO[i].first;
                    if (CO[i].second != 1)
                        cout << "/" << CO[i].second;
                }
                else
                    cout << "--";
            }
            cout << "    |";
            cout << endl;
        }
        for (int i = 0; i < M + 2; i++) cout << "---------";
        cout << endl << endl;
    }

    //без М строки
    void printSimplexTable(vector<vector<pair<long long, long long>>> matrix, vector<pair<long long, long long>> CO)
    {
        for (int i = 0; i < M + 2; i++) cout << "---------";
        cout << endl;

        cout << "\t\t";
        for (int i = 0; i < M; i++) cout << "x" << i + 1 << "\t";
        cout << "CO    |\n";

        for (int i = 0; i < M + 2; i++) cout << "---------";
        cout << endl;

        for (int i = 0; i < N + 1; i++)
        {
            if (i < N)
            {
                for (int j = 1; j < M + 1; j++)
                    if (matrix[i][j].first == 1 && matrix[i][j].second == 1)
                    {
                        int fl = 0;
                        for (int k = 0; k < N + 1; k++)
                            if (matrix[k][j].first != 0)
                                fl++;
                        if (fl == 1)
                            cout << "x" << j << "\t";
                    }
            }
            else
                cout << "Z\t";

            for (int j = 0; j < M + 1; j++)
            {
                cout << matrix[i][j].first;
                if (matrix[i][j].second != 1 && matrix[i][j].first != 0)
                    cout << "/" << matrix[i][j].second;
                cout << "\t";
            }

            if (i < N)
            {
                if (CO[i].first > 0 && CO[i].second > 0)
                {
                    cout << CO[i].first;
                    if (CO[i].second != 1)
                        cout << "/" << CO[i].second;
                }
                else
                    cout << "--";
            }
            cout << "    |";
            cout << endl;
        }
        for (int i = 0; i < M + 2; i++) cout << "---------";
        cout << endl << endl;
    }

    //вывод когда в М строке все 0 (перед завершением алгоритма)
    void printSimplexTableBeforeFinishABM(vector<vector<pair<long long, long long>>> matrix)
    {
        for (int i = 0; i < M + 2; i++) cout << "---------";
        cout << endl;

        cout << "\t\t";
        for (int i = 0; i < M; i++) cout << "x" << i + 1 << "\t";
        cout << "     |\n";

        for (int i = 0; i < M + 2; i++) cout << "---------";
        cout << endl;

        for (int i = 0; i < N + 2; i++)
        {
            if (i < N)
            {
                for (int j = 1; j < M + 1; j++)
                    if (matrix[i][j].first == 1 && matrix[i][j].second == 1)
                    {
                        int fl = 0;
                        for (int k = 0; k < N + 2; k++)
                            if (matrix[k][j].first != 0)
                                fl++;
                        if (fl == 1)
                            cout << "x" << j << "\t";
                    }
            }
            else if (i == N)
                cout << "Z\t";
            else
                cout << "M\t";

            for (int j = 0; j < M + 1; j++)
            {
                cout << matrix[i][j].first;
                if (matrix[i][j].second != 1 && matrix[i][j].first != 0)
                    cout << "/" << matrix[i][j].second;
                cout << "\t";
            }
            cout << "     |";
            cout << endl;
        }
        for (int i = 0; i < M + 2; i++) cout << "---------";
        cout << endl << endl;
    }

    //вывод матрицы конечной
    void printSimplexTableBeforeFinishMethod(vector<vector<pair<long long, long long>>> matrix)
    {
        for (int i = 0; i < M + 2; i++) cout << "---------";
        cout << endl;

        cout << "\t\t";
        for (int i = 0; i < M; i++) cout << "x" << i + 1 << "\t";
        cout << "     |\n";

        for (int i = 0; i < M + 2; i++) cout << "---------";
        cout << endl;

        for (int i = 0; i < N + 1; i++)
        {
            if (i < N)
            {
                for (int j = 1; j < M + 1; j++)
                    if (matrix[i][j].first == 1 && matrix[i][j].second == 1)
                    {
                        int fl = 0;
                        for (int k = 0; k < N + 1; k++)
                            if (matrix[k][j].first != 0)
                                fl++;
                        if (fl == 1)
                            cout << "x" << j << "\t";
                    }
            }
            else
                cout << "Z\t";

            for (int j = 0; j < M + 1; j++)
            {
                cout << matrix[i][j].first;
                if (matrix[i][j].second != 1 && matrix[i][j].first != 0)
                    cout << "/" << matrix[i][j].second;
                cout << "\t";
            }
            cout << "     |";
            cout << endl;
        }
        for (int i = 0; i < M + 2; i++) cout << "---------";
        cout << endl << endl;
    }

    //проверка является ли столбец базисным(1 единица и все остальные 0)
    bool basis(vector<vector<pair<long long, long long>>> matrix, int index)
    {
        int fl = 0;

        for (int i = 0; i < N; i++)
            if (matrix[i][index].first == 1)
                fl++;
            else if (matrix[i][index].first != 0)
                return false;

        if (fl == 1)
            return true;
        else
            return false;
    }

    //добавить искусственные базисы и М строка добавляется в матрицу
    void makeAB(vector<vector<pair<long long, long long>>>& matrix, vector<int>& Z, vector<pair<long long, long long>>& MString)
    {
        vector<int> index;

        for (int i = 1; i < M + 1; i++)
            if (basis(matrix, i))
            {
                for (int j = 0; j < N; j++)
                    if (matrix[j][i].first == 1)
                    {
                        index.push_back(j);
                        if (Z[i] != 0)
                        {
                            for (int k = 0; k < M + 1; k++)
                            {
                                matrix[N][k].first += matrix[j][k].first * Z[i];
                                if (k != i)
                                    if (k != 0)
                                        Z[k] -= matrix[j][k].first * Z[i];
                                    else
                                        Z[k] += matrix[j][k].first * Z[i];
                            }
                            matrix[N][i].first = 0;
                            Z[i] = 0;
                        }
                    }
            }

        for (int i = 0; i < M + 1; i++)
            MString.push_back({ 0, 1 });

        int s = index.size();
        for (int i = 0; i < N - s; i++, M++)
        {
            int fl = 0;
            for (int j = 0; j < N + 1; j++)
            {
                auto iter = matrix[j].cend();
                auto result{ find(index.begin(), index.end(), j) };
                if (result == index.end() && fl == 0)
                {
                    fl++;
                    bas++;
                    index.push_back(j);
                    matrix[j].insert(iter, { 1, 1 });
                    MString.push_back({ 0, 1 });
                    for (int k = 0; k < M + 1; k++)
                    {
                        MString[k].first -= matrix[j][k].first;
                        MString[k].second = 1;
                    }
                }
                else
                    matrix[j].insert(iter, { 0, 1 });
            }
        }

        matrix.push_back(MString);

        printMatrix(matrix);
    }

    //сокращение дробей
    void reduction(long long& fir, long long& sec)
    {
        long long min, div;
        div = 1;
        while (1)
        {
            if (fir % 2 == 0 && sec % 2 == 0)
            {
                fir /= 2;
                sec /= 2;
            }
            else
                break;
        }

        if (abs(fir) > abs(sec))
            min = abs(sec);
        else
            min = abs(fir);

        while (div < min)
        {
            div += 2;
            if (fir % div == 0 && sec % div == 0)
            {
                fir /= div;
                sec /= div;
                min /= div;
                div = 1;
            }
        }
    }

    //вычислять элементы в новой матрице
    void rectangle_method(int y, int x, int i, int j, vector<vector<pair<long long, long long>>>& matrix)
    {
        if (matrix[y][x].first == 0)
            return;
        if (matrix[i][j].first == 0) {
            matrix[i][j].second = 1;
        }
        pair<long long, long long> tmp;
        tmp.first = matrix[y][j].first * matrix[i][x].first;
        tmp.second = matrix[y][j].second * matrix[i][x].second;
        reduction(tmp.first, tmp.second);
        tmp.first *= matrix[y][x].second;
        tmp.second *= matrix[y][x].first;
        reduction(tmp.first, tmp.second);
        if (tmp.second < 0)
        {
            tmp.second *= -1;
            tmp.first *= -1;
        }
        int t = matrix[i][j].second * tmp.second;
        matrix[i][j].first *= t / matrix[i][j].second;
        matrix[i][j].second = t;
        tmp.first *= t / tmp.second;
        tmp.second = t;
        matrix[i][j].first -= tmp.first;
        reduction(matrix[i][j].first, matrix[i][j].second);
        if (matrix[i][j].second < 0)
        {
            matrix[i][j].second *= -1;
            matrix[i][j].first *= -1;
        }
    }

    //поделить строчку на данный элемент и столбец занулить (элемент сделать равным 1)
    void makeCross(int y, int x, vector<vector<pair<long long, long long>>>& matrix)
    {
        if (matrix[y][x].first == 0)
            return;
        for (int i = 0; i < M + 1; i++)
            if (i != x)
            {
                matrix[y][i].second *= matrix[y][x].first;
                if (matrix[y][i].second < 0)
                {
                    matrix[y][i].second *= -1;
                    matrix[y][i].first *= -1;
                }
                matrix[y][i].first *= matrix[y][x].second;
                reduction(matrix[y][i].first, matrix[y][i].second);
            }
        for (int i = 0; i < N + 1; i++)
        {
            matrix[i][x].first = 0;
            matrix[i][x].second = 1;
        }
        matrix[y][x].first = 1;
        matrix[y][x].second = 1;
    }

    //является ли строчка М пустой (закончился ли метод?)
    bool ifMStringIsOver(vector<vector<pair<long long, long long>>> matrix)
    {
        for (int i = 0; i < M + 1; i++)
            if (matrix[N + 1][i].first != 0)
                return true;
        return false;
    }

    //является ли решение конечным? (все ли переменные Z положительные)
    bool ifZStringIsPositive(vector<vector<pair<long long, long long>>> matrix)
    {
        for (int i = 1; i < M + 1; i++)
            if (matrix[N][i].first < 0)
                return false;
        return true;
    }

    //бесконечное число решений (когда строка М нулевая и в строке Z где 0 перемнные содержат различные значения
    //тогда в этом столбце выбираем ведущий элемент (неотрицательный), строится ещё таблица, и потом создается запись с лямбда
    void infinity(vector<vector<pair<long long, long long>>> matrix, int col)
    {
        vector<pair<long long, long long>> X1, X2;
        int row = 0;
        float min = 1000000;

        for (int i = 0; i < M; i++)
            if (basis(matrix, i + 1))
            {
                for (int j = 0; j < N; j++)
                    if (matrix[j][i + 1].first == 1)
                        X1.push_back({ matrix[j][0].first, matrix[j][0].second });
            }
            else
                X1.push_back({ 0,1 });

        vector<pair<long long, long long>> CO;
        for (int i = 0; i < N; i++)
        {
            CO.push_back({ matrix[i][0].first * matrix[i][col].second, matrix[i][0].second * matrix[i][col].first });
            if (CO[i].first < 0 || CO[i].second < 0) continue;
            if (CO[i].first != 0 && CO[i].second != 0)
                reduction(CO[i].first, CO[i].second);
            if (CO[i].first > 0 && CO[i].second > 0 && min > (float)CO[i].first / CO[i].second)
            {
                min = (float)CO[i].first / CO[i].second;
                row = i;
            }
        }

        printSimplexTable(matrix, CO);

        for (int i = 0; i < N + 1; i++)
            for (int j = 0; j < M + 1; j++)
                if (i != row && j != col)
                    rectangle_method(row, col, i, j, matrix);

        makeCross(row, col, matrix);

        printSimplexTableBeforeFinishMethod(matrix);

        for (int i = 0; i < M; i++)
            if (basis(matrix, i + 1))
            {
                for (int j = 0; j < N; j++)
                    if (matrix[j][i + 1].first == 1)
                        X2.push_back({ matrix[j][0].first, matrix[j][0].second });
            }
            else
                X2.push_back({ 0,1 });

        cout << "\nX* = (1-l) * (";
        for (int i = 0; i < M; i++)
        {
            cout << X1[i].first;
            if (X1[i].second != 1 && X1[i].first != 0)
                cout << "/" << X1[i].second;
            if (i != M - 1)
                cout << ";";
        }
        cout << ") + l * (";
        for (int i = 0; i < M; i++)
        {
            cout << X2[i].first;
            if (X2[i].second != 1 && X2[i].first != 0)
                cout << "/" << X2[i].second;
            if (i != M - 1)
                cout << ";";
        }
        cout << ") = (";
        for (int i = 0; i < M; i++)
        {
            long long tmp = X1[i].second * X2[i].second;
            X1[i].first *= tmp / X1[i].second;
            X2[i].first *= tmp / X2[i].second;
            X1[i].second = X2[i].second = tmp;
            X2[i].first -= X1[i].first;
            reduction(X1[i].first, X1[i].second);
            reduction(X2[i].first, X2[i].second);
            if (X2[i].first == 0)
                cout << X1[i].first;
            else if (X1[i].first != 0)
                cout << X1[i].first;
            if (X1[i].second != 1 && X1[i].first != 0)
                cout << "/" << X1[i].second;
            if (X2[i].first != 0)
            {
                if (X2[i].first > 0 && X1[i].first != 0)
                    cout << "+";
                cout << X2[i].first;
                if (X2[i].second != 1 && X2[i].first != 0)
                    cout << "/" << X2[i].second;
                cout << "l";
            }
            if (i != M - 1)
                cout << ";";
        }
        cout << ")\n";
    }

    //бесконечное или конечное число решений
    void answer(vector<vector<pair<long long, long long>>> matrix, vector<int> Z)
    {
        vector <long long> z{ 0,1 };

        for (int i = 0; i < M; i++)
            if (matrix[N][i + 1].first == 0)
                if (!basis(matrix, i + 1))
                {
                    infinity(matrix, i + 1);
                    return;
                }

        printSimplexTableBeforeFinishMethod(matrix);

        cout << "\nZ = ";
        if (Z[0] != 0)
        {
            z[0] += Z[0];
            cout << Z[0] << " ";
        }

        for (int i = 1; i < M + 1; i++)
            if (Z[i] != 0)
            {
                if (i != 1 && Z[i] > 0)
                    cout << " + ";
                if (basis(matrix, i))
                {
                    for (int j = 0; j < N; j++)
                        if (matrix[j][i].first == 1)
                        {
                            cout << Z[i] << "*" << matrix[j][0].first;
                            if (matrix[j][0].second != 1)
                                cout << "/" << matrix[j][0].second;
                            cout << " ";
                            z[0] *= matrix[j][0].second;
                            z[1] *= matrix[j][0].second;
                            z[0] += Z[i] * matrix[j][0].first;
                            reduction(z[0], z[1]);
                        }
                }
                else
                    cout << Z[i] << "*0 ";
            }
        cout << "= " << z[0];
        if (z[1] != 1)
            cout << "/" << z[1];
    }

public:
    int bas = 0;
    //чтение файла, Z строка, инициализация
    Fraction(vector<vector<pair<long long, long long>>>& matrix, vector<int>& Z, vector<pair<long long, long long>>& MString)
    {
        ifstream in("input.txt");
        int defaultM;
        string MinMax;
        if (in.is_open())
        {
            in >> N;
            in >> M;
            defaultM = M;
            string num;
            vector<pair<int, int>> zero;
            for (int i = 0; i < N + 1; i++)
            {
                vector<pair<long long, long long>> tmp;
                for (int j = 0; j < M; j++)
                {
                    in >> num;
                    tmp.push_back({ stoi(num), 1 });
                }
                in >> num;
                if (num == ">")
                {
                    zero.push_back({ -i, 1 });
                }
                else if (num == "<")
                {
                    zero.push_back({ i, 1 });
                }
                in >> num;
                auto iter = tmp.cbegin();
                tmp.insert(iter, { stoi(num), 1 });
                matrix.push_back(tmp);
            }
            in >> MinMax;
            in.close();

            for (int i = 0; i < zero.size(); i++, M++)
            {
                for (int j = 0; j < N + 1; j++)
                {
                    auto iter = matrix[j].cend();
                    if (zero[i].first == j)
                        matrix[j].insert(iter, { zero[i].second, 1 });
                    else
                        matrix[j].insert(iter, { 0, 1 });
                }
            }
        }

        for (int i = 0; i < N; i++)
            if (matrix[i][0].first < 0)
                for (int j = 0; j < M + 1; j++)
                    matrix[i][j].first *= -1;

        if (MinMax == "max")
        {
            for (int i = 1; i < M + 1; i++)
                matrix[N][i].first *= -1;
        }

        int fl = 0;
        cout << "Z = ";
        for (int i = 0; i < M + 1; i++)
        {
            if (MinMax == "max")
                Z.push_back(-matrix[N][i].first);
            else Z.push_back(matrix[N][i].first);
            if (Z[i] != 0)
            {
                if (i == 0)
                    cout << Z[i] << " ";
                else
                {
                    if (Z[i] > 0 && fl != 0)
                        cout << " + ";
                    if (Z[i] == -1)
                        cout << "-";
                    else
                        if (Z[i] != 1)
                            cout << Z[i] << "*";
                    cout << "x" << i << " ";
                }
                fl++;
            }
        }
        cout << "-> " << MinMax;

        cout << endl << endl;

        vector<int> zTemp;
        if (MinMax == "min")
            for (int i = 0; i < Z.size(); i++) zTemp.push_back(-Z[i]);

        if (MinMax == "min")
            for (int i = 0; i < Z.size(); i++) Z[i] = -Z[i];

        printMatrix(matrix);

        makeAB(matrix, Z, MString);


        fl = 0;
        if (MinMax == "min") cout << "-Z = ";
        else cout << "Z = ";
        if (MinMax == "max")
        {
            for (int i = 0; i < Z.size(); i++)
                if (Z[i] != 0)
                {
                    if (i == 0)
                        cout << Z[i] << " ";
                    else
                    {
                        if (Z[i] > 0 && fl != 0)
                            cout << " + ";
                        if (Z[i] == -1)
                            cout << "-";
                        else
                            if (Z[i] != 1)
                                cout << Z[i] << "*";
                        cout << "x" << i << " ";
                    }
                    fl++;
                }
        }
        else
        {
            for (int i = 0; i < zTemp.size(); i++)
                if (zTemp[i] != 0)
                {
                    if (i == 0)
                        cout << zTemp[i] << " ";
                    else
                    {
                        if (zTemp[i] > 0 && fl != 0)
                            cout << " + ";
                        if (zTemp[i] == -1)
                            cout << "-";
                        else
                            if (zTemp[i] != 1)
                                cout << zTemp[i] << "*";
                        cout << "x" << i << " ";
                    }
                    fl++;
                }
        }

        if (MinMax == "min") for (int i = 0; i < Z.size(); i++) Z[i] = -Z[i];


        cout << "- M(";
        for (int i = defaultM; i < M; i++)
        {
            if (i == M - 1) cout << "x" << i + 1;
            else cout << "x" << i + 1 << " + ";
        }
        cout << ")";
        cout << " -> " << "max" << "\n\n";

    }


    void metod(vector<vector<pair<long long, long long>>>& matrix, vector<int> Z)
    {
        vector<pair<long long, long long>> CO(N);

        while (1)
        {
            float min = 0;
            int col = -1, row = -1;

            //искусственный базис
            if (!ifMStringIsOver(matrix))
            {
                printSimplexTableBeforeFinishABM(matrix);
                matrix.pop_back();
                break;
            }

            for (int i = 1; i < M + 1; i++)
                if (min > (float)matrix[N + 1][i].first / matrix[N + 1][i].second)
                {
                    min = (float)matrix[N + 1][i].first / matrix[N + 1][i].second;
                    col = i;
                }

            if (col == -1)
            {
                printSimplexTableBeforeFinishABM(matrix);
                cout << "No solution: the system of constraints of the original problem is inconsistent.\n";
                return;
            }

            min = 1000000;
            for (int i = 0; i < N; i++)
            {
                CO[i].first = matrix[i][0].first * matrix[i][col].second;
                CO[i].second = matrix[i][0].second * matrix[i][col].first;
                if (CO[i].first < 0 || CO[i].second < 0) continue;
                reduction(CO[i].first, CO[i].second);
                if (min > (float)CO[i].first / CO[i].second && (float)CO[i].first / CO[i].second >= 0)
                {
                    min = (float)CO[i].first / CO[i].second;
                    row = i;
                }
            }

            printSimplexTableCO(matrix, CO);

            for (int i = 0; i < N + 2; i++)
                for (int j = 0; j < M + 1; j++)
                    if (i != row && j != col)
                        rectangle_method(row, col, i, j, matrix);

            makeCross(row, col, matrix);
            matrix[N + 1][col].first = 0;
            matrix[N + 1][col].second = 1;

            for (int i = M + 1 - bas; i < M + 1; i++)
                if (!basis(matrix, i))
                {
                    for (int j = 0; j < N + 2; j++)
                    {
                        auto iter = matrix[j].cbegin();
                        matrix[j].erase(iter + i);
                    }
                    M--;
                    bas--;
                }
        }
        //симпликс
        while (!ifZStringIsPositive(matrix))
        {
            float min = 0;
            int col = -1, row = -1;

            for (int i = 1; i < M + 1; i++)
                if (min > (float)matrix[N][i].first / matrix[N][i].second)
                {
                    min = (float)matrix[N][i].first / matrix[N][i].second;
                    col = i;
                }

            //не можем найти столбец
            if (col == -1)
            {
                cout << "No solution: the system of constraints of the original problem is inconsistent.\n";
                return;
            }

            min = 1000000;
            for (int i = 0; i < N; i++)
            {
                CO[i].first = matrix[i][0].first * matrix[i][col].second;
                CO[i].second = matrix[i][0].second * matrix[i][col].first;
                reduction(CO[i].first, CO[i].second);
                if (min > (float)CO[i].first / CO[i].second && (float)CO[i].first / CO[i].second > 0)
                {
                    min = (float)CO[i].first / CO[i].second;
                    row = i;
                }
            }

            printSimplexTable(matrix, CO);
            //строчку не можем найти
            if (row == -1)
            {
                cout << "No solutions: the system is not limited.";
                return;
            }

            for (int i = 0; i < N + 1; i++)
                for (int j = 0; j < M + 1; j++)
                    if (i != row && j != col)
                        rectangle_method(row, col, i, j, matrix);

            makeCross(row, col, matrix);
        }

        answer(matrix, Z);
    }
};

int main()
{
    vector<vector<pair<long long, long long>>> matrix;
    vector<int> Z;
    vector<pair<long long, long long>> MString;

    Fraction solution(matrix, Z, MString);

    solution.metod(matrix, Z);

    return 0;
}
