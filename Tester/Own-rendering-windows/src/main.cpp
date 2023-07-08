#include <iostream>

#include "RenderWindow.hpp"

int main()
{
    tester::RenderWindow win(100, 100, "Titre");
    tester::Pixel pxl{ tester::Color{ 125, 125, 125 }, tester::Point2<uint32_t>{ 0, 0 } };
    tester::Vertex vrt(tester::Vertex::Type::line, 4);
    tester::Event event;

    vrt[0].pos = tester::Point2<uint32_t>{ 10, 10 };
    vrt[1].pos = tester::Point2<uint32_t>{ 100, 10 };
    vrt[2].pos = tester::Point2<uint32_t>{ 100, 100 };
    vrt[3].pos = tester::Point2<uint32_t>{ 10, 100 };
    while (true) {
        while (win.pollEvent(event)) {
        }
        win.clear();
        win.draw(&pxl, 1, tester::Vertex::Type::pixel);
        win.draw(vrt);
        win.display();
    }
    return 0;
}