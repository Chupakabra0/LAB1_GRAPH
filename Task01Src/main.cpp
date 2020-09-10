/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/* 
* File:   main.cpp
* Author: KnightDanila
*
* Created on 4 июня 2019 г., 16:21
*/

#include <iostream>                                     // для стандартных потоков ввода-вывода
#include <windows.h>                                    // для локализации конслои
#include <numbers>										// для pi, слава богу, они добавили это в C++20
#include <cmath>                                        // для функции sin

#include "libs\GL_AL\glew.h"
#include "libs\GL_AL\glfw3.h"

// OpenGL
#define GLUT_DISABLE_ATEXIT_HACK
//#define GLFW_DLL
//#define GLEW_STATIC


#pragma comment(lib, "libs\\GL_AL\\glfw3.lib")
#pragma comment(lib, "libs\\GL_AL\\glut32.lib")
#pragma comment(lib, "libs\\GL_AL\\alut.lib")
#pragma comment(lib, "libs\\GL_AL\\glew32.lib")
#pragma comment(lib, "libs\\GL_AL\\glew32s.lib")

// VS2013+ - bugfix - Thanks Bolsunov Dmitry
#pragma comment(lib, "msvcrt.lib")
#pragma comment(lib, "msvcmrt.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

using namespace std;

template <typename T>
auto Println(const T i, ostream& out = cout) -> void {
    out << i << endl;
}

auto ArgsEcho(const int argc, char** argv) -> void {
    Println("____ARGS____");
    if (!argc) {
        Println("NO ARGS");
    }
    else {
        for (auto i = 0; i < argc; i++) {
            Println(argv[i]);
        }
    }
    Println("____________\n");
}
/*
* 
*/

auto main(const int argc, char** argv) -> int {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    ArgsEcho(argc, argv);
    Println("Hello OpenGL");

    if (!glfwInit()) {
        Println("Ошибка при инициализации GLFW\n", cerr);
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x Сглаживание
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Мы хотим использовать OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    
    // Открыть окно и создать в нем контекст OpenGL
    // (В сопроводительном исходном коде эта переменная является глобальной)
    auto* window = glfwCreateWindow( 640, 480, "Lesson 01", nullptr, nullptr);
    if (!window) {
        Println("Невозможно открыть окно GLFW. Если у вас Intel GPU, то он не поддерживает версию 3.3. Попробуйте версию уроков для OpenGL 2.1.", std::cerr);
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Инициализируем GLEW
    glewExperimental = true; // Флаг необходим в Core-режиме OpenGL
    if (glewInit() != GLEW_OK) {
        Println("Невозможно инициализировать GLEW", std::cerr);
        return -1;
    }

    // Включим режим отслеживания нажатия клавиш, для проверки ниже
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    auto colorRgb = 0.f;
	
    // Проверяем нажатие клавиши Escape или закрытие окна
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        // Пока что ничего не выводим. Это будет в уроке 2.
        glClearColor(GLclampf(sin(colorRgb * numbers::pi / 180.f)), GLclampf(abs(cos(colorRgb * numbers::pi / 180.f))),
                    GLclampf(abs(sin(colorRgb * numbers::pi / 180.f))) + GLclampf(cos(colorRgb * numbers::pi / 180.f)), GLclampf(1.0f));
        glClear(GL_COLOR_BUFFER_BIT);
        // Сбрасываем буферы
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Увеличиваем цвет 
        colorRgb <= 180.f ? colorRgb += 0.1f : colorRgb = 0.f;
    } 
    

    glfwTerminate();
    return EXIT_SUCCESS;
}