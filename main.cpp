#include <conio.h>

//FILES in project
#include "Menu.h" //namespace // independent
//#include "Templates.h" // namespace // independent
//#include "Menu_Interface.h" // pure virtual class // independent
#include "Menu_Implementation.h" // singleton class, public Menu_Interface // depend on System_File, Data_File
//#include "System_File.h" // singleton class // independent
//#include "Data_File.h" // class // independent

using namespace std;
using namespace Menu;

typedef unsigned char uchar;


int main()
{
    Menu_Implementation& singleMenu=Menu_Implementation::get_singleton();

    uchar selection;

        do
        {
            display_menu();
            selection=getch();

            if(selection=='1') // FILE OPTIONS
            {
                uchar selection2;
                do
                {
                    system("cls");
                    display_file_option();
                    selection2=getch();

                    if(selection2=='1') singleMenu.new_data_file_option(); //New file
                    else if(selection2=='2') singleMenu.display_files(); //Display file list
                    else if(selection2=='3') singleMenu.rename_data_file(); //Rename File
                    else if(selection2=='4') singleMenu.remove_data_file(); //Remove Data File

                }while(selection2!=ESC);
            } //File option

            else if(selection=='2') // DATA OPTIONS
            {
                uchar selection2;
                do
                {
                    system("cls");
                    display_data_option();
                    selection2=getch();

                    if(selection2=='1') singleMenu.new_data(); //New Data in file
                    else if(selection2=='2') singleMenu.display_all_data(); //Display all data in data file
                    else if(selection2=='3') singleMenu.sort_by_options(); //Sort by column name in data file
                    else if(selection2=='4') singleMenu.search_data(); //search data in data file
                    else if(selection2=='5') singleMenu.edit_data(); //edit data in data file
                    else if(selection2=='6') singleMenu.remove_data(); //remove data in data file

                }while(selection2!=ESC);
            } //Data option

            system("cls");
        }while(selection!=ESC);

    return 0;
}
