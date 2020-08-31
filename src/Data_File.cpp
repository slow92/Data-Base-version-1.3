#include "Data_File.h"
#include <iostream>
#include <fstream>

#include <sstream>

#include <vector>
#include <list>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::fstream;
using std::for_each;
using std::stringstream;
using std::vector;
using std::list;

Data_File::Data_File()
{
    //ctor
}

Data_File::~Data_File()
{
    //dtor
}

void Data_File::add_column(string& column_name)
{
    data_header.push_back(column_name);
}

void Data_File::remove_column()
{
    data_header.pop_back();
}

void Data_File::add_row(string& row_data)
{
    data.push_back(row_data);
}

int Data_File::columns_number()
{
    return data_header.size();
}

int Data_File::columns_number(std::string& column_name)
{
    if(!data_header.empty())
    {
        auto column_index=data_header.size();
        for(auto x: data_header)
            {
                column_index--;
                if(column_name==x)
                {
                    column_index=data_header.size()-column_index-1;
                    return column_index;
                }
            }
    }
    cout<<"Incorrect column name"<<endl;
    return 0;
}

void Data_File::display_columns_name(int& name)
{
    cout<<data_header[name];
}

int Data_File::rows_number()
{
    return data.size();
}

void Data_File::display_columns()
{
    if(data_header.empty()) return;
    for_each(data_header.begin(),data_header.end(),[](string& column_name){cout<<column_name<<" ";});
    cout<<endl;
}

void Data_File::display_rows()
{
    if(data.empty()) return;
    for_each(data.begin(),data.end(),[](string& row){cout<<row<<endl;});
}

bool Data_File::find_and_display_rows(string& text)
{
    bool text_found_in_data=false;
    for(auto i: data)
    {
        if(i.find(text)!=string::npos)
        {
            cout<<i<<endl;
            if(text_found_in_data==false) text_found_in_data=true;
        }
    }
    return text_found_in_data;
}

bool Data_File::find_and_display_rows(string& text, uint8_t& number_found, list<string>::iterator& it_l)
{
    bool text_found_in_data=false;
    number_found=0;
    for(auto it=data.begin();it!=data.end();it++)
    {
        if(it->find(text)!=string::npos)
        {
            number_found++;
            if(number_found==1) it_l=it;
            cout<<*it<<endl;
            if(text_found_in_data==false) text_found_in_data=true;
        }
    }
    return text_found_in_data;
}

void Data_File::find_and_remove_rows(string& text)
{
    bool text_found_in_data;
    do
    {
        text_found_in_data=false;
        for(auto it=data.begin();it!=data.end();it++)
        {
            if(it->find(text)!=string::npos)
            {
                data.erase(it);
                text_found_in_data=true;
                break;
            }
        }
    }while(text_found_in_data);
}

bool Data_File::sort_rows_by_column_name(string& column_name)
{
    int column_index=columns_number(column_name);
    if(!column_index) return false;

    string buff=data_header[column_index];
    cout<<data_header[column_index]<<endl;

    data_header.erase(data_header.begin()+column_index);
    data_header.insert(data_header.begin(),buff);
    display_columns();

    vector<string> row;

    for(auto it=data.begin();it!=data.end();it++)
    {
        stringstream stream(*it);
        row.clear();
        while(stream>>buff)
        {
            row.push_back(buff);
        }
        buff=row[column_index];
        row.erase(row.begin()+column_index);
        row.insert(row.begin(),buff);
        it->clear();
        for(auto x: row)
        {
            *it+=x+" ";
        }
    }
    data.sort();

    return true;
}

bool Data_File::save_data_file(string& file_name)
{
    if(remove(file_name.c_str()) == 0 )
    {
        cout<<"File "<<file_name<<" is over written!"<<endl;
    }
    else cout<<"New file is created!"<<endl;

    ofstream file(file_name.c_str());
    if(file.good())
    {
        file<<HEADER<<file_name<<endl;
        for_each(data_header.begin(),data_header.end(),[&file](string& n){file<<n<<" ";});
        file<<endl;
        file<<HEADER<<endl;
        if(rows_number())
        {
            for_each(data.begin(),data.end(),[&file](string& n){file<<n<<endl;});
        }
        file.close();
    }
    else
    {
        cout<<"Error in data file. Save file failed"<<endl;
        return false;
    }

    return true;
} //save_data_file saving column and rows in data files

bool Data_File::open_data_file(string& file_name)
{
    ifstream file(file_name.c_str());
    string buff;
    if(file.good())
    {
        file>>buff;
        if(buff!=HEADER+file_name)
        {
            cout<<"HEADER file incorrect. Open file failed"<<endl;
            return false;
        }

        do
        {
            file>>buff;
            if(buff!=HEADER) data_header.push_back(buff);
        }while(buff!=HEADER && !file.eof());

        while(!file.eof())
        {
           getline(file,buff);
           if(!buff.empty()) data.push_back(buff);
        }
        //data.pop_back(); //last line in data (list) is empty
        file.close();
    }
    else
    {
        cout<<"Error in data file. Open file failed"<<endl;
        return false;
    }

    return true;
} // open data file with correct header

void Data_File::display_data_file(string& file_name)
{
    open_data_file(file_name);
    display_columns();
    display_rows();
}
