#ifndef TEMPLATES_H
#define TEMPLATES_H


#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::numeric_limits;
using std::streamsize;

namespace Templates
{
        template <class TYP>
            static void insert_user_data(string question,TYP& zmienna, string error)
            {
            cout<<question<<endl;
                while(!(cin>>zmienna)&&cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout<<error<<endl;
                }
            }
}

#endif // TEMPLATES_H
