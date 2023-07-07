#include <iostream>

#include "RenderWindow.hpp"

int main()
{
    tester::RenderWindow win(800, 600, "Titre");
    tester::Pixel pxl{ tester::Color{ 255, 255, 255, 255}, tester::Point2<uint32_t>{ 10, 10 } };
    tester::Event event;

    while (true) {
        while (win.pollEvent(event)) {
        }
        win.clear();
        win.draw(&pxl, 1, tester::Vertex::Type::Pixel);
    }
    return 0;
}