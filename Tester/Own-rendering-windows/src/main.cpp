#include <iostream>

#include "RenderWindow.hpp"

int main()
{
    tester::RenderWindow win(200, 200, "Titre");
    tester::Pixel pxl{ tester::Color{ 125, 125, 125 }, tester::Point2<uint32_t>{ 0, 0 } };
    tester::Vertex vrt(tester::Vertex::Type::polygone, 4);
    tester::Event event;

    vrt[0].pos = tester::Point2<uint32_t>{ 10, 10 };
    vrt[1].pos = tester::Point2<uint32_t>{ 50, 10 };
    vrt[2].pos = tester::Point2<uint32_t>{ 50, 50 };
    vrt[3].pos = tester::Point2<uint32_t>{ 10, 50 };
    while (true) {
        while (win.pollEvent(event)) {
        }
        win.clear({ 255, 0, 0 });
        for (uint32_t y = 1; y < 20; y++) {
            for (uint32_t x = 1; x < 20; x++) {
                pxl.pos = { x, y };
                win.draw(&pxl, 1, tester::Vertex::Type::pixel);
            }
        }
        win.draw(vrt);
        win.display();
    }
    return 0;
}