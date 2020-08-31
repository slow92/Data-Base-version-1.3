#ifndef MENU_INTERFACE_H
#define MENU_INTERFACE_H

#define BACKSPACE 8
#define TAB 9
#define ENTER 13
#define ESC 27
#define SPACE 32
#define UNKNOWN "empty"

class Menu_Interface
{
    public:
        Menu_Interface();
        virtual ~Menu_Interface();

        //FILE OPTIONS
        virtual void new_data_file_option()=0;
        virtual void display_files()=0;
        virtual void rename_data_file()=0;
        virtual void remove_data_file()=0;

        //DATA OPTIONS

        virtual void new_data()=0;
        virtual void display_all_data()=0;
        virtual void sort_by_options()=0;
        virtual void search_data()=0;
        virtual void edit_data()=0;
        virtual void remove_data()=0;


    protected:

    private:
};

#endif // MENU_INTERFACE_H
