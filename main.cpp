#include <iostream>

using namespace std;

const string days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const int epoch[3] = {1, 1, 2020};
const int epochDayIndex = 2;
const string epochDay = days[epochDayIndex];

bool checkDate(int day, int month, int year);
int calculateDays(int *date);
string getDay(string dayStr, string monthStr, string yearStr);

int main()
{

    while (true)
    {
        string day, month, year;
        cout << "Please enter a date:" << endl;
        cout << "Day: ";
        cin >> day;
        cout << "Month: ";
        cin >> month;
        cout << "Year: ";
        cin >> year;

        string weekDay = getDay(day, month, year);
        if (weekDay == "")
        {
            cout << "The date entered is invalid. Please try again." << endl
                 << endl;
        }
        else
        {
            cout << "\n\nThe week day on " << day << "/" << month << "/" << year << " was:\n";
            cout << weekDay << endl
                 << endl;
        }

        string c;
        cout << "Press any key to continue, and E to exit." << endl;
        cin >> c;

        if (c[0] == 'e' || c[0] == 'E')
        {
            break;
        }
    }
    return 0;
}

bool checkDate(int day, int month, int year)
{
    bool isValid;

    isValid = year > 0;
    if (isValid)
    {
        isValid = month > 0 && month < 13;
        if (isValid)
        {
            if (month == 2)
            {
                if (!(year % 4))
                {
                    isValid = day > 0 && day < 30;
                }
                else
                {
                    isValid = day > 0 && day < 29;
                }
            }
            else
            {
                if (month < 7)
                {
                    if (month % 2 == 0)
                    {
                        isValid = day > 0 && day < 31;
                    }
                    else
                    {
                        isValid = day > 0 && day < 32;
                    }
                }
                else if (month > 6)
                {
                    if (month % 2 == 0)
                    {
                        isValid = day > 0 && day < 32;
                    }
                    else
                    {
                        isValid = day > 0 && day < 31;
                    }
                }
            }
        }
    }
    return isValid;
}

int calculateDays(int *date)
{
    long unsigned int totalDays = 0;
    int diffYear = date[2] - epoch[2];
    int diffMonth = date[1] - epoch[1];
    int diffDay = date[0] - epoch[0];
    if (diffYear >= 0)
    {
        if (diffYear > 0)
        {
            int leapYears = diffYear / 4;
            leapYears += (diffYear % 4) ? 1 : 0;
            totalDays = 365 * diffYear + leapYears;
        }
        if (diffMonth > 0)
        {
            totalDays += ((diffMonth / 2 * 1) + (diffMonth % 2 ? 1 : 0) + (diffMonth * 30));
            if (diffMonth > 7)
            {
                totalDays += (diffMonth - 7) % 2 ? 1 : 0;
            }
            if (diffMonth > 1)
            {
                totalDays -= 2;
                if (!(date[2] % 4))
                    totalDays += 1;
            }
        }
        totalDays += diffDay;
    }
    else if (diffYear < 0)
    {
        if (diffYear < -1)
        {
            int leapYears = (diffYear + 1) / 4;
            totalDays = 365 * (diffYear + 1) * -1 - leapYears;
        }
        diffMonth = 11 - diffMonth;
        if (diffMonth > 0)
        {
            totalDays += ((diffMonth / 2 * 1) + (diffMonth % 2 ? 1 : 0) + (diffMonth * 30));
            if (diffMonth > 5)
            {
                totalDays += (diffMonth - 7) % 2 ? 1 : 0;
            }
            if (diffMonth > 10)
            {
                totalDays -= 2;
                if (!(date[2] % 4))
                    totalDays += 1;
            }
        }
        int daysInMonth;
        if (date[1] == 2)
        {
            daysInMonth = (date[2] % 4) ? 28 : 29;
        }
        else
        {
            if (date[1] < 8)
            {
                daysInMonth = date[1] % 2 ? 31 : 30;
            }
            else if (date[1] > 7)
            {
                daysInMonth = date[1] % 2 ? 30 : 31;
            }
        }
        totalDays += daysInMonth - diffDay;
    }

    return totalDays;
}

string getDay(string dayStr, string monthStr, string yearStr)
{
    try
    {
        int day = stoi(dayStr);
        int month = stoi(monthStr);
        int year = stoi(yearStr);
        if (checkDate(day, month, year))
        {
            int date[3] = {day, month, year};
            int totalDays = calculateDays(date);
            if (date[2] >= epoch[2])
            {
                int dayIndex = totalDays % 7 + epochDayIndex;
                if (dayIndex >= 7)
                {
                    dayIndex = dayIndex - 7;
                }
                return days[dayIndex];
            }
            else
            {
                int dayIndex = epochDayIndex - totalDays % 7;
                if (dayIndex < 0)
                {
                    dayIndex = 7 + dayIndex;
                }
                return days[dayIndex];
            }
        }
    }
    catch (...)
    {
    }
    return "";
}
