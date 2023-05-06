#pragma once

/** @brief Declares an interface to a basic color screen that supports drawing lines, text, and shapes.
 */
class Screen {
public:
    virtual void draw_line() = 0;
};
