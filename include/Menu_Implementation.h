#ifndef MENU_IMPLEMENTATION_H
#define MENU_IMPLEMENTATION_H

#include "Menu_Interface.h"
#include "System_File.h"
#include "Data_File.h"


class Menu_Implementation : public Menu_Interface
{
    public:

        static Menu_Implementation& get_singleton();

        virtual void new_data_file_option();
        virtual void display_files();
        virtual void rename_data_file();
        virtual void remove_data_file();

        //DATA OPTIONS

        virtual void new_data();
        virtual void display_all_data();
        virtual void sort_by_options();
        virtual void search_data();
        virtual void edit_data();
        virtual void remove_data();

    protected:

    private:
        System_File& singleConfig;
        //System_File singleConfig;

        Menu_Implementation();
        Menu_Implementation(const Menu_Implementation&);
        virtual ~Menu_Implementation();
};

#endif // MENU_IMPLEMENTATION_H
