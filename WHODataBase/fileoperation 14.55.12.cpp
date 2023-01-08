#include "assignment_4.h"

covidDB::covidDB(int m)
{
    v = vector<vector<cvsdata>>(m);
    this->m = m;
}

int covidDB::hash(string country)
{
    int sum = 0;
    
    for (int i = 0; i < country.length(); i++)
    {
        char temp = country.at(i);
        char c = int(temp);
        sum += (i * c);
    }
    return sum % 17;
}

bool covidDB::add(cvsdata entry)
{
    bool check;
    bool oldDate = true;
    
    int index = hash(entry.getCountry());
    
    vector<string> Date = split(entry.getDate(), '/');
    
    int Day = stoi(Date[1]);
    int Month = stoi(Date[0]);
    int Year = stoi(Date[2]);
    
    for (int j = 0; j < v[index].size(); j++)
    {
        if (v[index][j].getCountry() == entry.getCountry())
        {
            vector<string> checkerDate = split(v[index][j].getDate(), '/');
            
            int checkMonth = stoi(checkerDate[0]);
            int checkDay = stoi(checkerDate[1]);
            int checkYear = stoi(checkerDate[2]);
            
            if (oldDate != false)
            {
                if (Year >= checkYear)
                {
                    if (Month == checkMonth)
                    {
                        if (Day > checkDay)
                        {
                            v[index][j].setDate(entry.getDate());
                            v[index][j].setCases(entry.getCases());
                            v[index][j].setDeaths(entry.getDeaths());
                            
                            check = true;
                            return check;
                        }
                    }
                    else if (Month > checkMonth)
                    {
                        if (Day >= checkDay)
                        {
                            v[index][j].setDate(entry.getDate());
                            v[index][j].setCases(entry.getCases());
                            v[index][j].setDeaths(entry.getDeaths());
                            
                            check = true;
                            return check;
                        }
                    }
                }
                oldDate = false;
                return false;
            }
        }
    }
    int hashIndex = hash(entry.getCountry());
    v[hashIndex].push_back(entry);

    check = true;
    return check;
}

cvsdata covidDB::get(string country)
{
    int i = hash(country);

    for (int j = 0; j < v[i].size(); j++)
    {
        if (v[i][j].getCountry() == country)
        {
            return v[i][j];
        }
    }
    return cvsdata("0", "0", 0, 0);
}

void  covidDB::remove(string country)
{
    int i = hash(country);
    
    for (int j = 0; j < v[i].size(); j++)
    {
        if (v[i][j].getCountry() == country)
        {
            v[i].erase(v[i].begin() + j);
            cout << country << " is deleted!" << endl;
            return;
        }
    }
    cout << "No Entry: " << country << " in hash table!";
}

void  covidDB::display()
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            cout << " -> " << v[i][j].toString();
            cout << endl;
        }
    }
}

void covidDB::readFile()
{
    vector<cvsdata> recordList;

    ifstream file("WHO-COVID-Data.csv");

    if (file.is_open())
    {
        string line;

        while (getline(file, line))
        {

            vector<string> result = split(line, ',');

            cvsdata oneEntry = cvsdata(result[0], result[1], stoi(result[2]), stoi(result[3]));

            recordList.push_back(oneEntry);
        }
    }
    vector<cvsdata> allEntries;
    combine(recordList, allEntries);
    
    for (int i = 0; i < allEntries.size(); i++)
    {
        v[hash(allEntries[i].getCountry())].push_back(allEntries[i]);
    }
}

void covidDB::combine(vector<cvsdata> & recordList, vector<cvsdata> & allEntries)
{
    int sumCases = 0;
    int sumDeaths = 0;

    for (int i = 0; i < recordList.size(); i++)
    {
        if (i != recordList.size()-1)
        {
            sumCases += recordList[i].getCases();
            sumDeaths += recordList[i].getDeaths();

            string name = recordList[i].getCountry();
            string nameCheck = recordList[i + 1].getCountry();

            if (name != nameCheck)
            {
                string latestDate = recordList[i].getDate();
                
                cvsdata dataEntry("", "", 0, 0);
                
                dataEntry.setDate(latestDate);
                dataEntry.setCountry(name);
                
                dataEntry.setCases(sumCases);
                dataEntry.setDeaths(sumDeaths);
                
                allEntries.push_back(dataEntry);
                
                sumCases = 0;
                sumDeaths = 0;
            }
        }
        else
        {
            sumCases += recordList[i].getCases();
            sumDeaths += recordList[i].getDeaths();
            
            string name = recordList[i].getCountry();
            string latestDate = recordList[i].getDate();
            
            cvsdata dataEntry("", "", 0, 0);
            
            dataEntry.setDate(latestDate);
            dataEntry.setCountry(name);
            
            dataEntry.setCases(sumCases);
            dataEntry.setDeaths(sumDeaths);
            
            allEntries.push_back(dataEntry);
        }
    }
}

vector<string> covidDB::split(string str, char del)
{
    vector<string> result;
    string temp = "";
    
    for (int i = 0; i < (int)str.size(); i++)
    {
        if (str[i] != del)
        {
            temp += str[i];
        }
        else
        {
            result.push_back(temp);
            temp = "";
        }
    }
    result.push_back(temp);
    return result;
}

cvsdata::cvsdata(string date, string country, int cases, int deaths)
{
    this->date = date;
    this->country = country;
    this->cases = cases;
    this->deaths = deaths;
}

string cvsdata::getDate()
{
    return date;
}
string cvsdata::getCountry()
{
    return country;
}

int cvsdata::getCases()
{
    return cases;
}
int cvsdata::getDeaths()
{
    return deaths;
}

string cvsdata::toString()
{
    return date + " " + country + " " + to_string(cases) + " " + to_string(deaths);
}

void cvsdata::setDate(string date)
{
    this->date = date;
}
void cvsdata::setCountry(string country)
{
    this->country = country;
}

void cvsdata::setCases(int newCases)
{
    this->cases += newCases;
}
void cvsdata::setDeaths(int newDeaths)
{
    this->deaths += newDeaths;
}
