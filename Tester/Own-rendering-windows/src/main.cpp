#include <iostream>

#include "Sprite.hpp"
#include "RenderWindow.hpp"

int main()
{
    tester::RenderWindow win(200, 200, "Titre");
    tester::VertexArray vrt(4);
    tester::Event event;
    tester::Image img;
    tester::Sprite sprt;

    img.load("test.bmp");
    sprt.setImage(img);
    vrt.setType(tester::VertexArray::Type::polygone);
    vrt[0].pos = tester::Point2<float>{ 10, 10 };
    vrt[1].pos = tester::Point2<float>{ 50, 10 };
    vrt[2].pos = tester::Point2<float>{ 50, 50 };
    vrt[3].pos = tester::Point2<float>{ 10, 50 };
    while (win.isOpen()) {
        while (win.pollEvent(event)) {
        }
        win.clear({ 255, 0, 0 });
        //win.draw(vrt);
        win.draw(sprt);
        win.display();
    }
    return 0;
}