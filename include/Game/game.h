//
// Created by SvCat on 17.02.2024.
//

#ifndef GAME_H
#define GAME_H

#if !defined(__glad_h_)
#include <glad/glad.h>
#endif
#if !defined(_glfw3_h_)
#include <GLFW/glfw3.h>
#endif
#if !defined(SHADER_H)
#include "shader_s.h"
#include "stb_image.h"
#endif
#if !defined(FTHEADER_H_)
#include <ft2build.h>
#include FT_FREETYPE_H
#endif
#if !defined(_GLIBCXX_MAP)
#include <map>
#endif
#if !defined(_GLIBCXX_IOSTREAM)
#include <iostream>
#endif
#if !defined(_GLIBCXX_FILESYSTEM)
#include <filesystem>
#endif
#include "g-truc-glm-33b0eb9/glm/gtc/matrix_transform.hpp"
#include "g-truc-glm-33b0eb9/glm/gtc/type_ptr.hpp"





struct Character {
    unsigned int TextureID; // ID текстуры глифа
    glm::ivec2   Size;      // размер глифа
    glm::ivec2   Bearing;   // смещение от линии шрифта до верхнего/левого угла глифа
    unsigned int Advance;   // смещение до следующего глифа
};

class Glifs{
private:

    std::map<unsigned int, Character> Characters;
    FT_Library ft{};
    unsigned int size_glif = 5000;

    bool initFREETYPE(){
        if (FT_Init_FreeType(&ft)){
            std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            return false;
        }
        std::string font_name = R"(C:\Windows\Fonts\Arial.ttf)";
        if (font_name.empty()){
            std::cerr << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
            return false;
        }
        FT_Face face;
        if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
            std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return false;
        }
        FT_Set_Pixel_Sizes(face, 0, 48);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        load_glifs(face);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        return true;
    }

    void load_glif(FT_Face &face, unsigned int index){
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );

        // Задаем для текстуры необходимые опции
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Теперь сохраняем символ для последующего использования
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<unsigned int, Character>(index, character));
    }

    void load_glifs(FT_Face &face){
        for (unsigned int c = 0; c < size_glif; c++){
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cerr << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            load_glif(face, c);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
public:
    Glifs(){
        if (!initFREETYPE()) return;
    }
    Character get(short index){
        return Characters[index];
    }
};

class Game{
private:
    int WIDTH = 1920;
    int HEIGHT = 1080;
    bool FULLSCREEN = true;
    GLFWwindow* window = nullptr;
    unsigned int VAO = 0, VBO = 0;
    std::filesystem::path Path = std::filesystem::current_path().parent_path();

    static void initGLFW(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }

    static bool initGLAD(){
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }
        return true;
    }

    bool create_window(){
        if (FULLSCREEN)
            window = glfwCreateWindow(WIDTH, HEIGHT, "Выживание в Бомомнке", glfwGetPrimaryMonitor(), nullptr);
        else
            window = glfwCreateWindow(WIDTH, HEIGHT, "Выживание в Бомонке", nullptr, nullptr);
        if (window == nullptr){
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(window);
        if (!initGLAD()){
            std::cerr << "Failed to initialize GLAD" << std::endl;
            glfwTerminate();
            return false;
        }
        return true;
    }

    static void set_OPENGL(){
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    [[nodiscard]] Shader set_shader() const{
        Shader shader((Path.string() + R"(\resources\shaders\text_vs.glsl)").c_str(), (Path.string() + R"(\resources\shaders\text_fs.glsl)").c_str());
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WIDTH), 0.0f, static_cast<float>(HEIGHT));
        shader.use();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        return shader;
    }

    void initVAO_VBO(){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    static void processInput(GLFWwindow* window){
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void RenderText(Shader shader, std::basic_string<wchar_t> text, float x, float y, float scale, glm::vec3 color, Glifs gl) const{
        // Активируем соответствующее состояние рендеринга
        shader.use();
        glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);
        // Перебираем все символы
        for (int i = 0; i < text.length(); ++i){
            Character ch = gl.get(text[i]);
            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

            // Обновляем VBO для каждого символа
            float vertices[6][4] = {
                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos,     ypos,       0.0f, 1.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },

                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },
                    { xpos + w, ypos + h,   1.0f, 0.0f }
            };

            // Рендерим текстуру глифа на прямоугольник
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);

            // Обновляем содержимое памяти VBO
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // обязательно используйте glBufferSubData, а не glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // Рендер прямоугольника
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // Теперь производим смещение для отображения следующего глифа (обратите внимание, что данное смещение измеряется в единицах, составляющих 1/64 пикселя)
            x += (ch.Advance >> 6) * scale; // битовый сдвиг на 6 разрядов, чтобы получить значение в пикселях (2^6 = 64 (разделите количество 1/64-х пикселей на 64, чтобы получить количество пикселей))
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void main_loop(Shader shader){
        Glifs gl;
        while (!glfwWindowShouldClose(window))
        {
            // Обработка ввода
            processInput(window);

            // Рендер
            glClearColor(0.2f, 0.2f, 0.4f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            std::basic_string<wchar_t> text1 = L"блять!!!";
            std::basic_string<wchar_t> text2 = L"Аладин лучший";
            RenderText(shader, text1, 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f), gl);
            RenderText(shader, text2, 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), gl);

            // glfw: обмен содержимым front- и back- буферов. Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glfwTerminate();
    }

    void execute(const std::string& var, int val){
        if (var == "WIDTH"){ WIDTH = val; return;}
        if (var == "HEIGHT"){ HEIGHT = val; return;}
        if (var == "FULLSCREEN"){ FULLSCREEN = (bool)val; return;}
    }

    bool load_settings(){
        try {
            std::ifstream file((Path.string() + R"(\resources\settings)").c_str());
            std::string var; int val;
            while (!file.eof()) {
                file >> var >> val;
                execute(var, val);
            }
        }catch (...){
            return false;
        }
        return true;
    }

public:
    Game(){
        if (!load_settings()) return;
        initGLFW();
        if (!create_window()) return;
        set_OPENGL();
        Shader shader = set_shader();
        initVAO_VBO();
        main_loop(shader);
    }
};


#endif
