#include "Menu_Implementation.h"
#include "System_File.h"
#include "Data_File.h"
#include "Templates.h"

#include <iostream>
#include <conio.h>
#include <algorithm>

using namespace std;

Menu_Implementation::Menu_Implementation(): singleConfig(System_File::get_singleton())
{
    //ctor
}

Menu_Implementation::~Menu_Implementation()
{
    //dtor
}

Menu_Implementation& Menu_Implementation::get_singleton()
{
    static Menu_Implementation singleton;
    return singleton;
}

//############################################################################################################
//########################################### FILE OPTIONS ###################################################
//############################################################################################################

void Menu_Implementation::new_data_file_option()
{
    system("cls");
    string file_name,column_name;
    Data_File new_file;
    unsigned char buffor;

    do
    {
        new_file.display_columns();
        cout<<"Name of column: "<<new_file.columns_number()+1<<endl;
        cout<<column_name;
        buffor=getch();

        if(buffor!=BACKSPACE && buffor!=ENTER && buffor!=ESC)
        {
            if(buffor==SPACE || buffor==TAB)
            {
                buffor='_';
            }
            column_name+=buffor;
            system("cls");
        }
        else if(buffor==ENTER)
        {
            new_file.add_column(column_name);
            column_name.clear();
            system("cls");
        }
        else if(buffor==BACKSPACE)
        {
            if(column_name.empty() && (new_file.columns_number()))
            {
                new_file.remove_column();
                system("cls");
            }
            else
            {
                column_name.clear();
                system("cls");
            }
        }
    }while(buffor!=ESC); //ESC */

    do
    {
        Templates::insert_user_data<unsigned char>("Do you want to save the file? y/n",buffor,"");
    }while(!(buffor=='y' || buffor=='n'));

    if(buffor=='y')
    {
        Templates::insert_user_data<string>("Insert name of new file",file_name,"");
        new_file.save_data_file(file_name);
        if(!singleConfig.compare_file_list(file_name)) singleConfig.update_config_file(file_name);
    }
    system("pause");
}


void Menu_Implementation::display_files()
{
    system("cls");
    singleConfig.display_files();
    system("pause");
}


void Menu_Implementation::rename_data_file()
{
    system("cls");
    singleConfig.display_files();
    string file_name,new_file_name;
    Templates::insert_user_data<string>("Insert file to change name",file_name,"");
    if(!singleConfig.compare_file_list(file_name)) cout<<"Incorrect file name!"<<endl;
    else
    {
        Templates::insert_user_data<string>("Insert new file name",new_file_name,"");
        if(rename( file_name.c_str(), new_file_name.c_str() ) == 0 ) cout<<"File name changed"<<endl;
        else cout<<"Error: file name can't be changed!"<<endl;
        singleConfig.update_config_file(new_file_name);
        singleConfig.update_config_file(file_name);
    }
    system("pause");
}


void Menu_Implementation::remove_data_file()
{
    system("cls");
    singleConfig.display_files();
    string file_name;
    Templates::insert_user_data<string>("Insert file name to remove",file_name,"");
    if(file_name!=singleConfig.get_configuration_file_name())
    {
        if(!singleConfig.compare_file_list(file_name))
        {
            cout<<"File not found!"<<endl;
            system("pause");
            return;
        }
        if(remove(file_name.c_str()) == 0 )
        {
            cout<<"File "<<file_name<<" has been removed"<<endl;
        }
        else cout<<"No any files was not removed!"<<endl;
    }
    else
    {
        string password;
        system("cls");
        Templates::insert_user_data<string>("To remove configuration file and all data files, insert password:",password,"");
        if(password==singleConfig.get_administrator_password())
        {
            if(remove(file_name.c_str()) == 0 && singleConfig.remove_all_data_files() )
            {
                cout<<"File "<<file_name<<" has been removed"<<endl;
            }
            else cout<<"No any files was not removed!"<<endl;
        }
        else cout<<"Password incorrect!"<<endl;
    }

    singleConfig.update_config_file(file_name);

    system("Pause");
}

//############################################################################################################
//########################################### DATA OPTIONS ###################################################
//############################################################################################################

void Menu_Implementation::new_data()
{
    system("cls");
    string file_name;
    singleConfig.display_files();
    Templates::insert_user_data<string>("New data in file: ",file_name,"");
    if(!singleConfig.compare_file_list(file_name))
    {
        cout<<"Data file not found!"<<endl;
        system("pause");
        return;
    }
    Data_File data_file;
    data_file.open_data_file(file_name);

    unsigned char buffor;
    vector<string> row_data;
    string row_name,all_row;

    auto index(0);
    do
    {
        system("cls");
        for_each(row_data.begin(),row_data.end(),[](string& text){cout<<text<<" ";});
        cout<<endl;
        data_file.display_columns();
        data_file.display_columns_name(index);
        cout<<endl<<row_name<<endl;
        buffor=getch();

        if(buffor!=BACKSPACE && buffor!=ENTER && buffor!=ESC)
        {
            if(buffor==SPACE || buffor==TAB)
            {
                buffor='_';
            }
            row_name+=buffor;
        }

        else if(buffor==ENTER)
        {
            if(row_name.empty()) row_name=UNKNOWN;
            row_data.push_back(row_name);
            index++;

            if(index==data_file.columns_number())
            {
                for_each(row_data.begin(),row_data.end(),[&all_row](string& text){all_row+=text+" ";});
                data_file.add_row(all_row);
                data_file.save_data_file(file_name);
                row_data.clear();
                all_row.clear();
                index=0;
            }

            row_name.clear();
        }

        else if(buffor==BACKSPACE)
        {
            if(row_name.empty() && index)
            {
                row_data.pop_back();
                --index;
            }
            else
            {
                row_name.clear();
            }
        }

    }while(buffor!=ESC);
}


void Menu_Implementation::display_all_data()
{
    Data_File data_file;
    system("cls");
    singleConfig.display_files();
    string file_name;
    Templates::insert_user_data<string>("Display data in file: ",file_name,"");
    if(!singleConfig.compare_file_list(file_name))
    {
        cout<<"Data file not found!"<<endl;
        system("pause");
        return;
    }
    system("cls");
    data_file.display_data_file(file_name);
    system("pause");
}


void Menu_Implementation::sort_by_options()
{
    Data_File data_file;
    system("cls");
    singleConfig.display_files();
    string file_name, column_name;
    Templates::insert_user_data<string>("Insert file name to sort data: ",file_name,"");
    if(!singleConfig.compare_file_list(file_name))
    {
        cout<<"Data file not found!"<<endl;
        system("pause");
        return;
    }
    data_file.open_data_file(file_name);
    data_file.display_columns();
    Templates::insert_user_data<string>("Sort by column name: ",column_name,"");
    if(data_file.sort_rows_by_column_name(column_name))
        data_file.save_data_file(file_name);

    system("pause");
}


void Menu_Implementation::search_data()
{
    Data_File data_file;
    system("cls");
    singleConfig.display_files();
    string file_name, text;
    Templates::insert_user_data<string>("Insert file name to remove data: ",file_name,"");
    if(!singleConfig.compare_file_list(file_name))
    {
        cout<<"Data file not found!"<<endl;
        system("pause");
        return;
    }
    Templates::insert_user_data<string>("Find and display all rows: ",text,"");
    data_file.open_data_file(file_name);
    if(data_file.find_and_display_rows(text)==false) cout<<"Data not found"<<endl;
    system("pause");
    return;
}


void Menu_Implementation::edit_data()
{
    Data_File data_file;
    system("cls");
    singleConfig.display_files();
    string file_name,text;
    Templates::insert_user_data<string>("Insert file name to edit data: ",file_name,"");

    if(singleConfig.compare_file_list(file_name))
    {
        data_file.open_data_file(file_name);

        uint8_t number_found;
        list<string>::iterator it_l;
        Templates::insert_user_data<string>("Find data to edit ",text,"");
        if(data_file.find_and_display_rows(text,number_found,it_l)==false)
        {
            cout<<"Data not found"<<endl;
            system("pause");
            return;
        }
        else if(number_found!=1)
        {
            cout<<"Ambiguous data founded. Insert more information to find unambiguous data!"<<endl;
            system("pause");
            return;
        }
        else
        {
            unsigned char buffor;
            vector<string> row_data;
            string row_name,all_row;

            auto index(0);
            do
            {
                system("cls");
                for_each(row_data.begin(),row_data.end(),[](string& text){cout<<text<<" ";});
                cout<<endl;
                data_file.display_columns();
                data_file.find_and_display_rows(text);
                cout<<row_name<<endl;
                buffor=getch();

                if(buffor!=BACKSPACE && buffor!=ENTER && buffor!=ESC)
                {
                    if(buffor==SPACE || buffor==TAB)
                    {
                        buffor='_';
                    }
                    row_name+=buffor;
                }

                else if(buffor==ENTER)
                {
                    if(row_name.empty()) row_name=UNKNOWN;
                    row_data.push_back(row_name);
                    index++;

                    if(index==data_file.columns_number())
                    {
                        for_each(row_data.begin(),row_data.end(),[&all_row](string& text){all_row+=text+" ";});
                        *it_l=all_row;
                        data_file.save_data_file(file_name);
                        row_data.clear();
                        all_row.clear();
                        index=0;
                        break;
                    }

                    row_name.clear();
                }

                else if(buffor==BACKSPACE)
                {
                    if(row_name.empty() && index)
                    {
                        row_data.pop_back();
                        --index;
                    }
                    else
                    {
                        row_name.clear();
                    }
                }

            }while(buffor!=ESC);
        }

    }

    else
    {
        cout<<"Data file not found!"<<endl;
        system("pause");
        return;
    }
}


void Menu_Implementation::remove_data()
{
    Data_File data_file;
    system("cls");
    singleConfig.display_files();
    string file_name,text;
    Templates::insert_user_data<string>("Insert file name to remove data: ",file_name,"");

    if(singleConfig.compare_file_list(file_name))
    {
        Templates::insert_user_data<string>("Find and remove all rows: ",text,"");
        data_file.open_data_file(file_name);
        if(data_file.find_and_display_rows(text)==false)
        {
            cout<<"Data not found"<<endl;
            system("pause");
            return;
        }

        system("pause");
        unsigned char buffor;
        do
        {
            Templates::insert_user_data<unsigned char>("Do you want to remove all this data? y/n",buffor,"");
        }while(!(buffor=='y' || buffor=='n'));
        if(buffor=='n') return;
        else
        {
            data_file.find_and_remove_rows(text);
            data_file.save_data_file(file_name);
            cout<<"Data removed"<<endl;
        }
    }

    else
    {
        cout<<"Data file not found!"<<endl;
        system("pause");
        return;
    }
}
