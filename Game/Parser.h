//
// Created by Yaroslav on 21.05.2024.
//


#ifndef MGBI_BOMONKA_PARSER_H
#define MGBI_BOMONKA_PARSER_H

#include <string>
#include <vector>

struct nowScene
{
    int id;
    std::wstring text;
    std::wstring name;
    int prepod;
    int fon;
    std::string music;
    int button_count;
    std::vector <std::pair<std::wstring, int>> buttons;
    int sys;
};
class parser{
private:
    std::map<int, nowScene> SceneMap;
public:
    void load(){
        std::string info;
        std::ifstream file(path_to_game + R"(\resources\parse.txt)");
        if(!file.is_open()){
            std::cerr << "Error open parser file!" << std::endl;
        }
        std::string line;
        int numlines = 0;
        while (std::getline(file, line)) {
            std::istringstream iss(line);

            nowScene newline;

            // (id)   SYS   FON   PREPOD   Music   BUT-Count   NAME   TEXT   BUTTONS
            
            //iss >> newline.id;
            std::string time_id;
            //std::getline(iss, time_id, '\t');
            newline.id = numlines;//std::stoi(time_id);
            numlines++;

            std::string time_sys;
            std::getline(iss, time_sys, '\t');
            newline.sys = std::stoi(time_sys);
            
            std::string time_fon;
            std::getline(iss, time_fon, '\t');
            newline.fon = std::stoi(time_fon);

            std::string time_prepod;
            std::getline(iss, time_prepod, '\t');
            newline.prepod = std::stoi(time_prepod);

            std::getline(iss, newline.music, '\t');

            std::string time_button_count;
            std::getline(iss, time_button_count, '\t');
            newline.button_count = std::stoi(time_button_count);

            std::string name;
            std::getline(iss, name, '\t');
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            if(name != ""){
                newline.name = converter.from_bytes(name);
            }
            else if(newline.id > 0){newline.name = SceneMap[newline.id-1].name;}
            
            std::string text;
            std::getline(iss, text, '\t');
            newline.text = converter.from_bytes(text);

            for(int i = 0; i < newline.button_count; i++){
                std::string convert_text;
                std::getline(iss, convert_text, '\t');
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

                std::string time_buttons;
                std::getline(iss, time_buttons, '\t');
                std::pair<std::wstring, int> button_info;
                button_info.first = converter.from_bytes(convert_text);
                button_info.second = std::stoi(time_buttons);
                newline.buttons.push_back(button_info);
            }

            SceneMap[newline.id] = newline;
        }
        file.close();
    }
    nowScene get(int id=0){
        return SceneMap[id];
    }
};


#endif //MGBI_BOMONKA_PARSER_H
