#include "menu.hpp"

extern GameTexts *texts;

Menu::Menu(int width, int height): gut::sdl::Input()
{
    _width = width;
    _height = height;

    if(TTF_Init() == -1) // Initialisation de SDL_TTF pour les textes
        gut::sdl::MessageBox::reportMessage(FATAL_ERROR, texts->getText("InitTTF"), SDL_GetError());

    font = TTF_OpenFont("includes/GUT/GL_old/text/font/font_1.ttf", height/36);

    _title = new gut::gl2::Text(font, WHITE);
    _title->Init(texts->getText("Title"));

    _sickNumberText = new gut::gl2::Text(font, WHITE);
    _vaccinated_chanceText = new gut::gl2::Text(font, WHITE);
    _mortalityText = new gut::gl2::Text(font, WHITE);
    _contagiousness_chanceText = new gut::gl2::Text(font, WHITE);
    _time_before_deathText = new gut::gl2::Text(font, WHITE);
    _time_before_cureText = new gut::gl2::Text(font, WHITE);

    _sickNumberText->Init(texts->getText("SickNumberEntry"));
    _vaccinated_chanceText->Init(texts->getText("VaccinatedEntry"));
    _mortalityText->Init(texts->getText("MortalityEntry"));
    _contagiousness_chanceText->Init(texts->getText("ContagiousnessEntry"));
    _time_before_deathText->Init(texts->getText("TimeDeathEntry"));
    _time_before_cureText->Init(texts->getText("TimeCureEntry"));

    _reset = new gut::gl2::Button((width*80)/100, (height*75)/100, 200, 50, texts->getText("ResetButton").c_str(), font);
    _enter = new gut::gl2::Button((width*80)/100, ((height*75)/100) - 50 - 6, 200, 50, texts->getText("GoButton").c_str(), font);
    _quit = new gut::gl2::Button((width*80)/100, ((height*75)/100) + 50 + 5, 200, 50, texts->getText("QuitButton").c_str(), font);

    _sickNumberEntry =            new Entry(INTEGER, (width*20)/100, (height*10)/100, 300, 50, font);
    _vaccinated_chanceEntry =     new Entry(PERCENT, (width*20)/100, (height*20)/100, 300, 50, font);
    _mortalityEntry =             new Entry(PERCENT, (width*20)/100, (height*30)/100, 300, 50, font);
    _contagiousness_chanceEntry = new Entry(PERCENT, (width*20)/100, (height*40)/100, 300, 50, font);
    _time_before_deathEntry =     new Entry(INTEGER, (width*20)/100, (height*50)/100, 300, 50, font);
    _time_before_cureEntry =      new Entry(INTEGER, (width*20)/100, (height*60)/100, 300, 50, font);

    std::cout << "Menu initialisé" << std::endl;
}

void Menu::updateMenu(Map &MAP)
{
    _enter->updateButton(getX(), getY(), getBoutonSouris(1), getBoutonSouris(1, UP));
    _quit->updateButton(getX(), getY(), getBoutonSouris(1), getBoutonSouris(1, UP));
    _reset->updateButton(getX(), getY(), getBoutonSouris(1), getBoutonSouris(1, UP));
    if(_enter->getActivation() || _reset->getActivation())
    {
        _go = true;
        activateTextInput(false);
        if((MAP._sicksNumber == 0 && MAP._daysPassed == 0) || _reset->getActivation())
            MAP.restart();
    }
    if(_quit->getActivation() || (!_go && getTouche(SDL_SCANCODE_ESCAPE, UP)))
        _end = true;

    _sickNumberEntry->updateEntry(*this);
    _vaccinated_chanceEntry->updateEntry(*this);
    _mortalityEntry->updateEntry(*this);
    _contagiousness_chanceEntry->updateEntry(*this);
    _time_before_deathEntry->updateEntry(*this);
    _time_before_cureEntry->updateEntry(*this);

    MAP._mortality = _mortalityEntry->_percent;
    MAP._sicks = _sickNumberEntry->_integer;
    MAP._contagiousness = _contagiousness_chanceEntry->_percent;
    MAP._vaccinated_chance = _vaccinated_chanceEntry->_percent;
    MAP._time_before_death = _time_before_deathEntry->_integer;
    MAP._time_before_cure = _time_before_cureEntry->_integer;
}


void Menu::renderMenu(gut::gl2::Shader &main)
{
    main.setBool("isTexture", false);
    _enter->renderButton();
    _quit->renderButton();
    _reset->renderButton();

    _sickNumberEntry->renderEntry();
    _vaccinated_chanceEntry->renderEntry();
    _mortalityEntry->renderEntry();
    _contagiousness_chanceEntry->renderEntry();
    _time_before_deathEntry->renderEntry();
    _time_before_cureEntry->renderEntry();

    main.setBool("isTexture", true);
    _title->render(_width/2 - (_title->_surf_wid.front()/2), 20);
    _enter->updateTexte();
    _quit->updateTexte();
    _reset->updateTexte();

    _vaccinated_chanceEntry->renderTexte();
    _sickNumberEntry->renderTexte();
    _mortalityEntry->renderTexte();
    _contagiousness_chanceEntry->renderTexte();
    _time_before_deathEntry->renderTexte();
    _time_before_cureEntry->renderTexte();

    _sickNumberText->render(_sickNumberEntry->_pos_x - _sickNumberText->_surf_wid[0] - 10, _sickNumberEntry->_pos_y + (_sickNumberEntry->_pos_h/2 - _sickNumberText->_surf_hei[0]/2));
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
            _quit,
            _reset,
            _sickNumberEntry,
            _vaccinated_chanceEntry,
            _mortalityEntry,
            _contagiousness_chanceEntry,
            _time_before_deathEntry,
            _time_before_cureEntry,
            _sickNumberText,
            _vaccinated_chanceText,
            _mortalityText,
            _contagiousness_chanceText,
            _time_before_deathText,
            _time_before_cureText;

    std::cout << "Menu libéré" << std::endl;
}
