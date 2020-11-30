#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;


bool assign_char_found(string data, int i)
{
    if (data[i+1] == ':' || data[i-1] == ':' || data[i+1] == '=' || data[i-1] == '=')
        return true;
    else
        return false;
}

bool divide_char_found(string data, int i, int j)
{

    if ( (data[i+1] == '<' && data[j] == '>')
        || data[i+1] == '}' || data[j] == '}' || data[i+1] == '{' || data[j] == '{'
        || data[i+1] == ';' || data[j] == ';')
        return true;
    else
        return false;
}
void minify(string &data)
{
    string new_data;
    int i = 0;
    while (data[i] != NULL)
    {
        //case 1
        if (data[i] == '\"')
        {
            while (data[i] != '\"')
            {

                if (data[i] == ' ' || assign_char_found(data, i))
                {

                    i++;
                    continue;
                }
                new_data+=data[i];
                i++;
            }

        }
        //case 2
        else if (data[i] == '\'')
        {
            while (data[i] != '\'')
            {
                new_data+=data[i];
                i++;
            }

        }
        //case 3
        else if (data[i] == ' ')
        {
            int j = i-1; // store after space value lie " >   < "
            while (data[i] == ' ')
                i++;
            i--;

            if ( assign_char_found(data, i) || divide_char_found(data, i, j))
            {
                i++;
                continue;
            }

        }
        //case 4
        else if (data[i] == '/' && data[i+1] == '*')
        {

            i+= 2;
            start:
                if (data[i] == '*')
                {
                    if (data[i+1] == '/')
                    {
                        i+=2;
                        continue;
                    }
                    else
                    {
                        i++;
                        goto start;
                    }
                }
                else
                {
                    i++;
                     goto start;
                }

        }
        new_data += data[i];
        i++;
    }

    cout << new_data;

}

string get_file()
{
    string file_name;
    cout << "Enter File name: ";
    cin >> file_name;

    bool dot_found = false;
    for (char c : file_name)
    {
        if (c == '.')
        {
            dot_found = true;
            break;
        }
    }

    if (!dot_found)
        file_name += ".txt";

    return file_name;
}

bool isSingleComment(string line)
{
    int i = 0;
    while (line[i] == ' ')
        i++;

    if (line[i] == '/' && line[i+1] == '/')
        return true;
    else
        return false;
}
bool fileExist(string file_name)
{
    ifstream file(file_name);

    if (file.is_open())
        return true;
    else
        return false;
}

int main()
{
    string file_name;
    do
    {
        file_name = get_file();
    }
    while (!fileExist(file_name));


    // main work start

    ifstream file(file_name);
    string data;
    string line;

    while (getline(file, line))
    {
        if (!isSingleComment(line))
        {

            data+=line+ ' ';
        }

    }

    minify(data);

}
