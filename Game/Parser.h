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
    std::string prepod;
    std::string fon;
    std::string music;
    int button_count;
    std::vector <std::pair<std::wstring, int>> buttons;
    std::string sys;
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
        while (std::getline(file, line)) {
            std::istringstream iss(line);

            nowScene newline;

            //iss >> newline.id;
            std::string time_id;
            std::getline(iss, time_id, '\t');
            newline.id = std::stoi(time_id);

            std::string text;
            std::getline(iss, text, '\t');
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            newline.text = converter.from_bytes(text);
            
            std::getline(iss, newline.prepod, '\t');
            std::getline(iss, newline.fon, '\t');
            std::getline(iss, newline.music, '\t');
            std::string time_button_count;
            std::getline(iss, time_button_count, '\t');
            newline.button_count = std::stoi(time_button_count);

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
            std::getline(iss, newline.sys, '\t');
            
             
            /*
            nowScene newLine;
            std::string elem;
            int numelem = 0;
            while (iss >> elem) {
                switch(numelem){
                    case 0: newLine.id = std::stoi(elem);
                    case 1: newLine.id = std::stoi(elem);
                    case 0: newLine.id = std::stoi(elem);
                    case 0: newLine.id = std::stoi(elem);
                    case 0: newLine.id = std::stoi(elem);
                    case 0: newLine.id = std::stoi(elem);
                }
            }
            */

            SceneMap[newline.id] = newline;
        }
        file.close();
    }
    nowScene get(int id=0){
        return SceneMap[id];
    }
};


#endif //MGBI_BOMONKA_PARSER_H
