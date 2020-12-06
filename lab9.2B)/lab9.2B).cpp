// lab9.2B).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std; 
enum Specialty { IT, IK, CA, KH, KB };
string strSpecialty[] = { "IT", "IK", "CA", "KH", "KB" };
struct Student 
{
    string prizv; 
    Specialty specialty;
    short unsigned kurs;
    short unsigned physics;
    short unsigned math;
    union
    {
        short unsigned programming;
        short unsigned methods;
        short unsigned pedagogika;
    };
};
void Create(Student* s, const int N);
void Print(Student* s, const int N);
double BestAverage(Student* s, const int N);
double GPA(Student* s, const int N);
void Sort(Student* s, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);
int BinSearch(Student* s, const int N, const string prizv, double avg, const int specialty, const int third_grade);
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N,
        MenuItem,
        found, 
        math_mark;
    double avg;
    string prizv;
    cout << "Enter the number of students:";
    cin >> N;
    Student* s = new Student[N];
    int menuItem;
    do {
        cout << "Choose action" << endl;
        cout << "[1] - enter data from the keyboard" << endl;
        cout << "[2] -data output to the screen" << endl;
        cout << "[3] - output of the highest average score of the percentage of students who received in physics" << char(34) << "4" << char(34) << "or" << char(34) << " 5 " << char(34) << endl;
        cout << "[4] - physical data ordering" << endl;
        cout << "[5] - index ordering and data output" << endl;
        cout << "[6] - binary search of the student" << endl;
        cout << "[0] - exit and exit of the program" << endl;
        cout << "Enter menu item:"; cin >> menuItem;
        switch (menuItem)
        {
        case 1:
            Create(s, N);
            cout << "Array created" << endl;
            break;
        case 2:
            Print(s, N);
            break;
        case 3:
            cout << "================================================================================" << endl;
            cout << "| Highest average score:" << fixed << setprecision(2) << BestAverage(s, N) << setw(51) << "|" << endl;
            cout << "| GPA " << char(34) << "4,5" << char(34) << " or " << char(34) << "4.5<" << char(34) << ": " << fixed << setw(6) << setprecision(2) << GPA(s, N) << "people" << setw(51) << "|" << endl;	cout << "=================================================================================================================" << endl;
            cout << "================================================================================" << endl;
            break;
        case 4:
            Sort(s, N);
            cout << "Array ordered" << endl;
            break;
        case 5:
            PrintIndexSorted(s, IndexSort(s, N), N);
            break;
        case 6:
            cout << "Enter search keys:" << endl;
            cin.get();
            cin.sync();
            cout << "last name:";
            getline(cin, prizv);
            /*cout << "average score (to two decimal places):";
            cin >> avg;
            cout << "third grade:"; cin >> third_grade;
            cout << endl;
            if ((found = BinSearch(s, N, prizv, avg, specialty, third_grade)) != -1)
                cout << "Student found in position" << found + 1 << endl;
            else
                cout << "No student found" << endl;*/
        break;
        case 0:
        break;
        default:
            cout << "Error! You entered an incorrect value!"
                "Enter the number - the number of the selected menu item" << endl;
        }
        cout << endl;
    } while (menuItem != 0);
    delete[] s;
}void Create(Student* s, const int N)
{
    int kurs, specialty;
    for (int i = 0; i < N; i++)
    {
        cout << "Student№" << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << "last name:"; getline(cin, s[i].prizv);
        cout << "course"; cin >> s[i].kurs;
        do
        {
            cout << "specialty (0 - Computer Science, 1 - Mathematics and Economics, 2 - Labor Training, 3 - Informatics, 4 - Physics and Informatics):";
            cin >> specialty;
        } while (specialty != 0 && specialty != 1 && specialty != 2 && specialty != 3 && specialty != 4);
        s[i].specialty = (Specialty)specialty;
        cout << "physics grade"; cin >> s[i].physics;
        cout << "grade in mathematics"; cin >> s[i].math;

        switch (specialty)
        {
        case 0:cout << "score from numerical programming:"; cin >> s[i].programming;
            break;
        case 3:
            cout << "numerical estimation:"; cin >> s[i].methods;
            break;
        case 1:
        case 2:
        case 4:
            cout << "assessment in pedagogy"; cin >> s[i].pedagogika;
            break;
        }
    }
}void Print(Student* s, const int N)
{
    cout << "================================================================================================================="
        << endl;
    cout << "| № | Surname | Course | Specialty | Physics | Mathematics | Programming | Numerical Methods | Pedagogy |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " "
            << "| " << setw(13) << left << s[i].prizv
            << "| " << setw(3) << right << s[i].kurs << "  "
            << "| " << setw(8) << right << strSpecialty[s[i].specialty] << "      "
            << "| " << setw(4) << right << s[i].physics << "   "
            << "| " << setw(6) << right << s[i].math << "     ";
        switch (s[i].specialty)
        {
        case 0:
        cout << "| " << setw(7) << right << s[i].programming << "       |" << setw(18) << "|" << setw(13) << "|" << endl;   
        break;   
        case 3:
        cout << "| " << setw(15) << "|" << setw(10) << right << s[i].methods << "       |" << setw(13) << "|" << endl;  
        break;     
        case 1:   
        case 2:   
        case 4:   
            cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << s[i].pedagogika << "     |" << endl;      
            break;
        }
    }
    cout << "=================================================================================================================" << endl;
}double BestAverage(Student* s, const int N)
{
    double best = 0;
    double F;
    double M;
    double I;
    double Meth;
    double Pedag;
     for (int i = 0; i < N; i++)
    {
        switch (s[i].specialty)
        {
        case 0:
            F = (s[i].physics) / N;
            M = (s[i].math) / N;
            I = (s[i].programming) / N;
            Meth = (s[i].methods) / N;
            Pedag = (s[i].pedagogika) / N;
            break;
        case 3:
            F = (s[i].physics) / N;
            M = (s[i].math) / N;
            I = (s[i].programming) / N;
            Meth = (s[i].methods) / N;
            Pedag = (s[i].pedagogika) / N;
            break;
        case 1:
        case 2:
        case 4:
            F = (s[i].physics) / N;
            M = (s[i].math) / N;
            I = (s[i].programming) / N;
            Meth = (s[i].methods) / N;
            Pedag = (s[i].pedagogika) / N;
            break;
        }
        if (F > M && F > I && F > Meth && F > Pedag)
            best = F;
        if (M > F && M > I && M > Meth && M > Pedag)
            best = M;
        if (I > F && I > M && I > Meth && I > Pedag)
            best = I;
        if (Meth > M && Meth > I && Meth > F && Meth > Pedag)
            best = Meth;
        if (Pedag > F && Pedag > I && Pedag > Meth && Pedag > M)
            best = Pedag;
    }
    return best;
}
double GPA(Student* s, const int N)
{
    int k = 0;
    double best;
    for (int i = 0; i < N; i++)
        if (best >= 4, 5)
            k++;
        else
            cout << "no >4.5";
    return  k / N;
}

void Sort(Student* s, const int N)
{
    Student tmp;
    double si1, si2;

    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            switch (s[i1].specialty)
            {
            case 0:
                si1 = (s[i1].physics + s[i1].math + s[i1].programming) / 3.;
                si2 = (s[i1 + 1].physics + s[i1 + 1].math + s[i1 + 1].programming) / 3.;
                if (
                    (si1 < si2)
                    || (si1 == si2 && s[i1].math < s[i1 + 1].math)
                    || (si1 == si2 && s[i1].math == s[i1 + 1].math && s[i1].prizv < s[i1 + 1].prizv)
                    )
                {
                    tmp = s[i1];
                    s[i1] = s[i1 + 1];
                    s[i1 + 1] = tmp;
                }
                break;
            case 3:
                si1 = (s[i1].physics + s[i1].math + s[i1].methods) / 3.;
                si2 = (s[i1 + 1].physics + s[i1 + 1].math + s[i1 + 1].methods) / 3.;
                if ((si1 > si2)
                    || (si1 == si2 && s[i1].math > s[i1 + 1].math)
                    || (si1 == si2 && s[i1].math == s[i1 + 1].math && s[i1].prizv > s[i1 + 1].prizv)
                    )
                {
                    tmp = s[i1];
                    s[i1] = s[i1 + 1];
                    s[i1 + 1] = tmp;
                }
                break;
            case 1:
            case 2:
            case 4:
                si1 = (s[i1].physics + s[i1].math + s[i1].pedagogika) / 3.;
                si2 = (s[i1 + 1].physics + s[i1 + 1].math + s[i1 + 1].pedagogika) / 3.;
                if (
                    (si1 > si2)
                    || (si1 == si2 && s[i1].math > s[i1 + 1].math)
                    || (si1 == si2 && s[i1].math == s[i1 + 1].math && s[i1].prizv > s[i1 + 1].prizv)
                    )
                {
                    tmp = s[i1];
                    s[i1] = s[i1 + 1];
                    s[i1 + 1] = tmp;
                }
                break;
            }
        }
}int* IndexSort(Student* s, const int N)
{
    int* I = new int[N];

    for (int i = 0; i < N; i++)
        I[i] = i;

    int i, j, value;
    int check_index, check_value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        switch (s[I[i]].specialty)
        {
        case KH:
            check_index = s[I[i]].programming;
            check_value = s[value].programming;
            break;
        case IT:
            check_index = s[I[i]].methods;
            check_value = s[value].methods;
            break;
        default:
            check_index = s[I[i]].pedagogika;
            check_value = s[value].pedagogika;

        }
        for (j = i - 1;
            j > 0 && ((s[I[j]].specialty > s[value].specialty)
                ||
                ((s[I[j]].specialty == s[value].specialty)
                    &&
                    (check_index > check_value))
                ||
                ((s[I[j]].specialty == s[value].specialty)
                    &&
                    (check_index == check_value)
                    &&
                    (s[I[j]].prizv < s[value].prizv)));
        j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}void PrintIndexSorted(Student* s, int* I, const int N)
{
    cout << "================================================================================================================="
        << endl;
    cout << " |#   | Surname   | Course   | Special | Physics | Mathematics | Programming | Numerical Methods | Pedagogy | "
        << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " "
            << "| " << setw(13) << left << s[I[i]].prizv
            << "| " << setw(3) << right << s[I[i]].kurs << "  "
            << "| " << setw(8) << right << strSpecialty[s[I[i]].specialty] << "      "
            << "| " << setw(4) << right << s[I[i]].physics << "   "
            << "| " << setw(6) << right << s[I[i]].math << "     ";
        switch (s[i].specialty)
        {
        case 0:
            cout << "| " << setw(7) << right << s[I[i]].programming << "       |" << setw(18) << "|" << setw(13) << "|" << endl;
            break;
        case 3:
            cout << "| " << setw(15) << "|" << setw(10) << right << s[I[i]].methods << "       |" << setw(13) << "|" << endl;
            break;
        case 1:
        case 2:
        case 4:
            cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << s[I[i]].pedagogika << "     |" << endl;
            break;
        }
    }
    cout << "================================================================================================================="
        << endl;
    cout << endl;
}int BinSearch(Student* s, const int N, const string prizv, double  avg, const int specialty, const int third_grade)
{
    int L = 0, R = N - 1, m, check;

    {
        m = (L + R) / 2;

        switch (s[m].specialty)
        {
        case KH:
            check = s[m].programming;
            break;
        case IT:
            check = s[m].methods;
            break;
        default:
            check = s[m].pedagogika;
        }

        if ((s[m].prizv == prizv
            &&
            s[m].specialty == specialty)
            &&
            (check == third_grade))
        {
            return 1;
        }

        if ((check < third_grade)
            ||
            (check == third_grade
                &&
                s[m].specialty < specialty)
            ||
            (check == third_grade
                &&
                s[m].specialty == specialty
                &&
                s[m].prizv > prizv))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
