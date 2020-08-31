#include "System_File.h"

#include <fstream>
#include <iostream>

#include <list>
#include <algorithm>
#include <string>

using std::fstream;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::for_each;
using std::remove;

//######################################

System_File::System_File()
{
    if(!open_config_file())
    {
        cout<<"Not found configuration file"<<endl;
        save_config_file();
        cout<<"Configuration file created"<<endl;
        system("pause");
    }// configuration file initialization
    display_files();
    while(!check_file_list());
    save_config_file();
}




bool System_File::open_config_file()
{

    ifstream file(CONFIG_FILE.c_str());
    if(!file.good())
    {
        cout<<"Error in system file. Open configuration file failed"<<endl;
        return false;
    }
    file_list.clear();
    string line;
    while(getline(file, line))
    {
        file_list.push_back(line);
    }
    file.close();

    return true;
}

bool System_File::save_config_file()
{
    remove(CONFIG_FILE.c_str());
    ofstream file(CONFIG_FILE.c_str());
    if(!file.good())
    {
        cout<<"Error in system file. Save file failed"<<endl;
        return false;
    }

    if(!file_list.empty()) for_each(file_list.begin(),file_list.end(),[&file](string& n){file<<n<<endl;});
    file.close();

    return true;
} //save_config_file saving file list in system.config file

bool System_File::check_file_list()
{
    if(file_list.empty()) return true;
    ifstream file;
    string name;
    for(auto it=file_list.begin();it!=file_list.end();it++)
    {
        name=*it;
        file.open(name.c_str());
        if(!file.good())
        {
            cout<<*it<<" file not found"<<endl;
            file_list.erase(it);
            return false;
        }
        else
        {
            file.close();
        }
    }

    return true;
}

bool System_File::update_config_file(string& file_name)
{
    if(file_name==CONFIG_FILE) return true;
    open_config_file();

    if(!compare_file_list(file_name))
    {
        file_list.push_back(file_name);
    }
    else
    {
        for(auto it=file_list.begin();it!=file_list.end();)
        {
            if(file_name==*it)
            {
                file_list.erase(it);
                break;
            }
        }
    }

    file_list.sort([](string& a, string& b){return a<b;});

        if(save_config_file())
            return true;
    return false;
}

bool System_File::remove_all_data_files()
{
    for_each(file_list.begin(),file_list.end(),[](string& file_name){remove(file_name.c_str());});
    file_list.clear();
    return true;
}


bool System_File::display_files()
{
    if(!file_list.empty())
    {
        for_each(file_list.begin(),file_list.end(), [](string& n){cout<<n<<endl;});
        return true;
    }
    else
    {
        cout<<"No files!"<<endl;
        return false;
    }
}

bool System_File::compare_file_list(string& name_file)
{
    for(auto x: file_list)
    {
        if(name_file==x) return true;
    }
    return false;
}

const string System_File::get_configuration_file_name()
{
    return CONFIG_FILE;
}

const string System_File::get_administrator_password()
{
    return PASSWORD;
}
