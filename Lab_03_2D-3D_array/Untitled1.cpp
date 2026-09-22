#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int marks[6][4] = {
        {78, 85, 90, 88},
        {92, 76, 84, 91},
        {69, 88, 79, 82},
        {85, 94, 91, 87},
        {73, 81, 86, 75},
        {89, 79, 93, 90}
    };

    string subjects[4] = {
        "English", "Mathematics", "Programming", "AI"
    };

    int totals[6] = {0};

    cout << "Student Marks Table:\n\n";

    cout << setw(10) << "Student";

    for (int j = 0; j < 4; j++)
    {
        cout << setw(15) << subjects[j];
    }

    cout << setw(10) << "Total"
         << setw(12) << "Average" << endl;

    for (int i = 0; i < 6; i++)
    {
        cout << setw(10) << i + 1;

        for (int j = 0; j < 4; j++)
        {
            cout << setw(15) << marks[i][j];
            totals[i] += marks[i][j];
        }

        double average = totals[i] / 4.0;

        cout << setw(10) << totals[i]
             << setw(12) << fixed << setprecision(2)
             << average << endl;
    }

    cout << "\nHighest Marks in Each Subject:\n";

    for (int j = 0; j < 4; j++)
    {
        int highest = marks[0][j];

        for (int i = 1; i < 6; i++)
        {
            if (marks[i][j] > highest)
            {
                highest = marks[i][j];
            }
        }

        cout << subjects[j] << ": " << highest << endl;
    }

    int highestTotal = totals[0];
    int highestStudent = 0;

    for (int i = 1; i < 6; i++)
    {
        if (totals[i] > highestTotal)
        {
            highestTotal = totals[i];
            highestStudent = i;
        }
    }

    cout << "\nStudent with Highest Total Marks: Student "
         << highestStudent + 1 << endl;

    cout << "Highest Total: " << highestTotal << endl;

    return 0;
}
