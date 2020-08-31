#ifndef SYSTEM_FILE_H
#define SYSTEM_FILE_H

//singleton class

#include<string>
#include<list>
#include<fstream>


using std::string;
using std::list;
using std::fstream;

class System_File
{
    public:

       static System_File& get_singleton()
        {
            static System_File singleton;
            return singleton;
        }

        bool open_config_file();

        bool save_config_file();

        bool check_file_list(); // check if files from the configuration file can be opened, if not, file list is updated

        bool update_config_file(string& file_name); // add or remove file_name in configuration file and sort file list

        bool remove_all_data_files();

        bool display_files();

        bool compare_file_list(string& file_name);

        const string get_configuration_file_name();

        const string get_administrator_password();




    protected:

    private:

        System_File();
        System_File(const System_File&){}
        ~System_File(){}

        const string CONFIG_FILE="config.txt";
        const string PASSWORD="administrator";

        list<string> file_list;
};

#endif // SYSTEM_FILE_H
