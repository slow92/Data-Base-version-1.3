#include "Menu.h"

#include <iostream>

using std::cout;
using std::endl;


//#########################################

namespace Menu
{
    void display_menu()
    {
        cout<<"[1] File options"<<endl;
        cout<<"[2] Data options"<<endl;
        cout<<"[ESC] EXIT"<<endl;

    }

    void display_file_option()
    {
        cout<<"[1] New data file option"<<endl;
        cout<<"[2] Display files"<<endl;
        cout<<"[3] Rename data file"<<endl;
        cout<<"[4] Remove data file"<<endl;
        cout<<"[ESC] EXIT"<<endl;
    }

    void display_data_option()
    {
        cout<<"[1] New data"<<endl;
        cout<<"[2] Display all data"<<endl;
        cout<<"[3] Sort by options"<<endl;
        cout<<"[4] Search data"<<endl;
        cout<<"[5] Edit data"<<endl;
        cout<<"[6] Remove data"<<endl;
        cout<<"[ESC] EXIT"<<endl;
    }
}


