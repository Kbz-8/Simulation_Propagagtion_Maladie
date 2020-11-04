#include "menu.hpp"

Menu::Menu(int width, int height): Input()
{
    _width = width;
    _height = height;

    GUTtext path = "includes/GUT/GL/text/font/font_1.ttf";
    int SIZE = height/36;

    _title = new Text(path, 30, WHITE);
    _title->Init("SIMULATION");

    _vaccinated_chanceText = new Text(path, SIZE, WHITE);
    _mortalityText = new Text(path, SIZE, WHITE);
    _contagiousness_chanceText = new Text(path, SIZE, WHITE);
    _time_before_deathText = new Text(path, SIZE, WHITE);
    _time_before_cureText = new Text(path, SIZE, WHITE);

    _vaccinated_chanceText->Init("Immunity/Vaccination");
    _mortalityText->Init("Mortality");
    _contagiousness_chanceText->Init("Contagiousness");
    _time_before_deathText->Init("Time before death");
    _time_before_cureText->Init("Time before cure");

    _test = new Text(path, 15, WHITE);

    _enter = new Button((width*80)/100, (height*80)/100, 200, 50, "Go", path, SIZE);

    _vaccinated_chanceEntry = new Entry(PERCENT, (width*20)/100, (height*20)/100, 300, 50, path, SIZE);
    _mortalityEntry = new Entry(PERCENT, (width*20)/100, (height*30)/100, 300, 50, path, SIZE);
    _contagiousness_chanceEntry = new Entry(PERCENT, (width*20)/100, (height*40)/100, 300, 50, path, SIZE);
    _time_before_deathEntry = new Entry(INTEGER, (width*20)/100, (height*50)/100, 300, 50, path, SIZE);
    _time_before_cureEntry = new Entry(INTEGER, (width*20)/100, (height*60)/100, 300, 50, path, SIZE);

    std::cout << "Menu initialisé" << std::endl;
}

void Menu::updateMenu(Map &MAP)
{
    _enter->updateButton(getX(), getY(), getBoutonSouris(1), getBoutonSouris(1, UP));
    if(_enter->getActivation())
    {
        _go = true;
        activateTextInput(false);
        MAP.restart();
    }
    _test->Init(getTextEntry());


    _vaccinated_chanceEntry->updateEntry(getX(), getY(), getBoutonSouris(1));
    if(_vaccinated_chanceEntry->_activate)
        _vaccinated_chanceEntry->updateTexte(*this);

    _mortalityEntry->updateEntry(getX(), getY(), getBoutonSouris(1));
    if(_mortalityEntry->_activate)
        _mortalityEntry->updateTexte(*this);

    _contagiousness_chanceEntry->updateEntry(getX(), getY(), getBoutonSouris(1));
    if(_contagiousness_chanceEntry->_activate)
        _contagiousness_chanceEntry->updateTexte(*this);

    _time_before_deathEntry->updateEntry(getX(), getY(), getBoutonSouris(1));
    if(_time_before_deathEntry->_activate)
        _time_before_deathEntry->updateTexte(*this);

    _time_before_cureEntry->updateEntry(getX(), getY(), getBoutonSouris(1));
    if(_time_before_cureEntry->_activate)
        _time_before_cureEntry->updateTexte(*this);

    MAP._mortality = _mortalityEntry->_percent;
    MAP._contagiousness = _contagiousness_chanceEntry->_percent;
    MAP._vaccinated_chance = _vaccinated_chanceEntry->_percent;
    MAP._time_before_death = _time_before_deathEntry->_integer;
    MAP._time_before_cure = _time_before_cureEntry->_integer;
}


void Menu::renderMenu(Shader &main)
{
    main.setBool("isTexture", false);
    _enter->renderButton();

    _vaccinated_chanceEntry->renderEntry();
    _mortalityEntry->renderEntry();
    _contagiousness_chanceEntry->renderEntry();
    _time_before_deathEntry->renderEntry();
    _time_before_cureEntry->renderEntry();

    main.setBool("isTexture", true);
    _title->render(_width/2 - (_title->_surf_wid.front()/2), 20);
    _enter->updateTexte();
    _test->render(10, 10);

    _vaccinated_chanceEntry->renderTexte();
    _mortalityEntry->renderTexte();
    _contagiousness_chanceEntry->renderTexte();
    _time_before_deathEntry->renderTexte();
    _time_before_cureEntry->renderTexte();

    _vaccinated_chanceText->render(_vaccinated_chanceEntry->_pos_x - _vaccinated_chanceText->_surf_wid[0] - 10, _vaccinated_chanceEntry->_pos_y + (_vaccinated_chanceEntry->_pos_h/2 - _vaccinated_chanceText->_surf_hei[0]/2));
    _mortalityText->render(_mortalityEntry->_pos_x - _mortalityText->_surf_wid[0] - 10, _mortalityEntry->_pos_y + (_mortalityEntry->_pos_h/2 - _mortalityText->_surf_hei[0]/2));
    _contagiousness_chanceText->render(_contagiousness_chanceEntry->_pos_x - _contagiousness_chanceText->_surf_wid[0] - 10, _contagiousness_chanceEntry->_pos_y + (_contagiousness_chanceEntry->_pos_h/2 - _contagiousness_chanceText->_surf_hei[0]/2));
    _time_before_deathText->render(_time_before_deathEntry->_pos_x - _time_before_deathText->_surf_wid[0] - 10, _time_before_deathEntry->_pos_y + (_time_before_deathEntry->_pos_h/2 - _time_before_deathText->_surf_hei[0]/2));
    _time_before_cureText->render(_time_before_cureEntry->_pos_x - _time_before_cureText->_surf_wid[0] - 10, _time_before_cureEntry->_pos_y + (_time_before_cureEntry->_pos_h/2 - _time_before_cureText->_surf_hei[0]/2));
}

Menu::~Menu()
{
    delete  _title,
            _enter,
            _test,
            _vaccinated_chanceEntry,
            _mortalityEntry,
            _contagiousness_chanceEntry,
            _time_before_deathEntry,
            _time_before_cureEntry,
            _vaccinated_chanceText,
            _mortalityText,
            _contagiousness_chanceText,
            _time_before_deathText,
            _time_before_cureText;
}
