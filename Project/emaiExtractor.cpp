#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <set>
using namespace std;

bool validChar(char c)
{
    if ( c >= 64 && c <= 90)
        return true;

    if ( c >= 97 && c <= 122)
        return true;

    if ( c >= 48 && c <= 57)
        return true;

    if ( c == 95 || c == 46)
        return true;

    return false;
}


string getName (string data, int i)
{
    string name;

    for (i; i >= 0; i--)
    {

        if (validChar(data[i]))
        {
            name = data[i] + name;
        }
        else
        {
            break;
        }
    }

    //validate
    int j = 0;
    while (name[j] == '.' || name[j] ==  '_' || (name[j] >= 48 && name[j] <= 57))
    {
        j++;
    }
    string new_name;
    int k = 0;
    if (j > 0)
    {
        while (name[j] != NULL )
        {
            new_name += name[j];
            j++;
        }
        name = new_name;
    }

    return name;
}


string get_country_domain(string data,int &i)
{
  return "";
}

string getDomain(string data, int &i, int len)
{
    i++;
    string domain;
    bool invl = false;
    int dot_count;

    while (i < len)
    {
        if (validChar(data[i]))
        {

            if ( data[i] == '.')
            {   dot_count ++;
                string host;
                int j = i + 1;
                int count = 0;
                //searching for character only
                if (dot_count == 2)
                {

                    host = get_country_domain(data, i);

                    invl = true;
                }
                else
                {
                    while ((data[j] >= 64 && data[j] <= 90) || (data[j] >= 97 && data[j] <= 122) )
                    {
                        if(count > 2)
                            break;

                        host += data[j];
                        j++;
                        count ++;

                    }
                }

                if (host[0] != NULL)
                    domain += '.'+host;
                invl = true;

                if (data[j] == '.')
                {
                    invl = false;
                }

                j--;
                i = j;


            }
            else
                domain += data[i];

        }
        else
            break;


        //increment the loop variable
        i++;

        //if there is an error inside inner loop and program should break
        if (invl)
            break;


    }
    if (domain[0] != NULL)
        i--;
    return domain;

}

bool validateName(string name)
{
    //if name string is empty
    if(name[0] == NULL)
        return false;

    bool CharFound = false;
    int i = 0;
    while (name[i] != NULL)
    {
        if ( (name[i] >= 97 && name[i] <= 122) || (name[i] >= 64 && name[i] <= 90))
            CharFound = true;
        i++;
    }

    return CharFound;
}

bool validateDomain(string domain)
{
    bool DotFound = false;
    int dot_count = 0;

    if (domain[0] == NULL)
        return false;

    int i = 0;
    while (domain[i] != NULL)
    {

        if (domain[i] == '.')
        {

            if (domain[i-1] == '.')
                return false;
            else
                DotFound = true;

        }
        i++;
    }

    return DotFound;
}






void  emailExtractor(string data)
{
    string name;
    string domain;
    string email;
    set <string, greater <string>> email_list;

    int i = 0;
    int len = data.length();

    while (i < len)
    {

        if (data[i] == '@')
        {
            name = getName (data, i - 1);
            domain = getDomain(data, i, len);
            email = name + '@' + domain;

            if (validateName(name) && validateDomain(domain))
                email_list.insert(email);
        }

        i++;
    }

    printf("\n\n=======================================================\n");
    printf("================ %d Emails found!!! ======================\n",email_list.size() );
    printf("===========================================================\n\n");


    i = 1;
    for (string s : email_list)
    {
        cout << i << ". "<<s <<endl;
        i++;
    }
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

bool file_exist(string file_name)
{
    ifstream file(file_name);

    if(file.is_open())
    {

        return true;
    }
    cout << "File Not Found !!" <<endl;
    return false;
}
int main()
{
    printf("=======================================================\n");
    printf("==== Enter a file name to extract email from there=====\n");
    printf("=======================================================\n\n");
    string data;
    //getline(cin, data);

    string file_name;
    do{
         file_name = get_file();
    }
    while(!file_exist(file_name));




    string line;
    ifstream file(file_name);


    if(file.is_open())
    {
        while (getline(file, line))
        {
            data +=' '+  line;
        }
        file.close();
    }


    emailExtractor(data);

    getch();


}
