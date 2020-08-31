#ifndef DATA_FILE_H
#define DATA_FILE_H

#include <string>
#include <vector>
#include <list>

class Data_File
{
    public:

        void add_column(std::string& column_name);
        void remove_column();


        int columns_number(); //return columns counts
        int columns_number(std::string& column_name); // return founded column index
        void display_columns(); // display all header
        void display_columns_name(int& name); // display name of one column by name


        void add_row(std::string& row_data);
        int rows_number();
        void display_rows();
        bool find_and_display_rows(std::string& text);
        bool find_and_display_rows(std::string& text, uint8_t& number_found, std::list<std::string>::iterator& it_l);
        void find_and_remove_rows(std::string& text);
        bool sort_rows_by_column_name(std::string& column_name);


        bool save_data_file(std::string& file_name);
        bool open_data_file(std::string& file_name); // load of header and all data from file
        void display_data_file(std::string& file_name);


        Data_File();
        virtual ~Data_File();

    protected:

    private:

        const std::string HEADER="!@#";

        std::vector<std::string> data_header;
        std::list<std::string> data;
};

#endif // DATA_FILE_H
