//
// Created by SvCat on 12.02.2024.
//

#ifndef BLACK_HOLE_GLAD_H
#define BLACK_HOLE_GLAD_H

#include <GLFW/glfw3.h>

namespace gl {
    typedef void (*t1)(GLclampf, GLclampf, GLclampf, GLclampf);

    t1 glClearColor = (t1) glfwGetProcAddress("glClearColor");

    typedef void (*t2)(GLbitfield);

    t2 glClear = (t2) glfwGetProcAddress("glClear");
}

#endif //BLACK_HOLE_GLAD_H
