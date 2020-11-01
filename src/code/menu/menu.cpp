#include "menu.hpp"

Menu::Menu(int width, int height)
{
    _width = width;
    _height = height;

    _title = new Text("src/code/text/font/font_1.ttf", 30, WHITE);
    _title->Init("SIMULATION");

    _test = new Text("src/code/text/font/font_1.ttf", 15, WHITE);

    _enter = new Button((width*80)/100, (height*80)/100, 200, 50, "Go", "src/code/text/font/font_1.ttf", height/36);

    SDL_StartTextInput();
}

void Menu::updateMenu(Input& input)
{
    _enter->update(input.getX(), input.getY(), input.getBoutonSouris(1), input.getBoutonSouris(1, UP));
    if(_enter->getActivation())
    {
        SDL_StopTextInput();
        _go = true;
    }

    _test->free_texture();
    _test->Init(input.getTextEntry());
}

void Menu::renderMenu(Shader &main)
{
    main.setBool("isTexture", false);
    _enter->renderButton();

    main.setBool("isTexture", true);
    _title->render(_width/2 - (_title->_surf_wid.front()/2), 20);
    _enter->updateTexte(_width, _height);
    _test->render(10, 10);
}

Menu::~Menu()
{
    delete _title;
    delete _enter;
    delete _test;
}
