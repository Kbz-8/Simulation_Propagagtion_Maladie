#include "map.hpp"

Map::Map(int width, int height)
{
    _width = width;
    _height = height;

    /* ========================================= Mise en place de la simulation ========================================= */

    clearTabular();

    _daysPassed = 0;

    _sicks = 1;
    _vaccinated_chance = 0.2;
	_mortality = 0.9;
	_contagiousness = 0.2;
	_time_before_death = 20;
	_time_before_cure = 40;

    std::vector<Person> tempo;   // Tableau temporraire pour remplir le tableau principal
	tempo.clear();

	for(int i = 0; i < 355; i++)
	{
		for(int j = 0; j < 197; j++)
			tempo.push_back(Person(_vaccinated_chance, _mortality)); // On remplis le tablau temporaire de gens

		_TableauPersonnes.push_back(tempo); // On transfère les données du tableau temporaire vers le tableau principal
		tempo.clear();
	}

	int x = 0;
	int y = 0;
    // Boucle pour placer aléatoirement le nombre initial de malade sur la map
	for(int i = 0; i < _sicks; i++)
	{
		x = math::randint(0, _TableauPersonnes.size());
		y = math::randint(0, _TableauPersonnes.front().size());

		while(_TableauPersonnes[x][y]._type == SICK)
		{
			x = math::randint(0, _TableauPersonnes.size());
            y = math::randint(0, _TableauPersonnes.front().size());
		}

		setPerson(x, y, SICK);
	}

	/* ========================================= Mise en place du VBO ========================================= */

    float vertices[8] = {
        0, 0,
        0, 5,               // Tableau contenant les coordonnées des sommets au sein d'un carré
        5, 5,               // Ce tableau sera passé au VBO (voir documentation si dessous pour savoir ce q'un VBO est)
        5, 0
    };

    for(int i = 0; i < sizeof(vertices); i++)
        _vertices.push_back(vertices[i]);   // Transfère des coordonnées des sommets du tableau temporaire vers le tableau dynamique
                                            // dont le VBO a besoin
    LoadVBO();  // Génération du VBO
}

void Map::LoadVBO()
{
    /*
     *  ============================================== DOCUMENTATION ==================================================
     *
     *   Un VBO (Vertex Buffer Object) est un moyen de rendu consistant à allouer une partie de la mémoire de la carte
     *   vidéo pour y stocker les informations de rendu (coordonées des sommets, couleurs, textures, normales...) sans
     *   avoir besoin de passer par la RAM ce qui permet une vitesse d'execution plus élevée car l'information voyage
     *   moins au sein de la machine.
     *
     *   Les autres moyens de rendu possibles avec OpenGL sont le Direct, les Display List, les VAOs et les VBOs/IBOs.
     *   Seuls les VBOs, VAOs, et VBOs/IBOs ne passent pas par la RAM avant d'atteindre la carte graphique.
     *
     *   Pour ma simulation, j'utilise des VBOs car ils sont simple d'utilisation et que je n'ai pas besoin de plus.
     *
     */

    if(glIsBuffer(_vboID) == GL_TRUE) glDeleteBuffers(1, &_vboID); // Destruction d'un éventuel ancien VBO

    glGenBuffers(1, &_vboID); // Génération de l'ID
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);  // Verrouillage du VBO
    glBufferData(GL_ARRAY_BUFFER, _vertices.size(), 0, GL_STATIC_DRAW);   // Allocation de la mémoire vidéo
    glBufferSubData(GL_ARRAY_BUFFER, 0, _vertices.size(), &_vertices[0]); // Transfert des données de sommets
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Déverrouillage du VBO

    if(glIsBuffer(_vboID) != GL_TRUE)   // Si le VBO ne s'est pas généré on envoi un message d'erreur
        std::cout << "Erreur lors de la création d'un VBO " << std::string(reinterpret_cast<GUTtext>(glewGetErrorString(glIsBuffer(_vboID)))) << std::endl;
}

void Map::updateColor(int x, int y)
{
    switch(_TableauPersonnes[x][y]._type)
    {
        case HEALTHY: glColor3f(0, 1, 0);    break;
        case VACCINATED: glColor3f(0, 0, 1); break;
        case SICK: glColor3f(1, 0, 0);       break;
        case DEAD: glColor3f(0, 0, 0);       break;

        default: break;
    }
}

void Map::renderPerson(int x, int y)
{
    updateColor(x, y);
    glPushMatrix();     // On sauvegarde l'ancienne matrice d'affichage et on en met une nouvelle
                        // qui est neutre

    glTranslatef(x * 5, y * 5, 0.0f); // Déplace le carré dans la nouvelle matrice et donc à l'écran

    glDrawArrays(GL_QUADS, 0, 4); // Dessine les informations contenues dans le VBO

    glPopMatrix();      // Remet l'ancienne matrice pour éviter que les prochains carrés soient affectés par la modification de matrice
}

void Map::renderPopulation()
{
    updateMap();

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glEnableClientState(GL_VERTEX_ARRAY);  // Activation de la capacité de rendu pour le VBO
    glVertexPointer(2, GL_FLOAT, 0, 0);    // Passage des informations sur les coordonnées des sommets (stockées dans le VBO)

    for(int i = 0; i < _TableauPersonnes.size(); i++)
	{
        for(int j = 0; j < _TableauPersonnes.front().size(); j++)
			renderPerson(i, j);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(0, _vboID);
}

void Map::updateMap()
{
    for(int i = 0; i < _TableauPersonnes.size(); i++)
	{
		for(int j = 0; j < _TableauPersonnes.front().size(); j++)
		{
			if(getPerson(i, j)._type == HEALTHY)
				updateHealthy(i, j);
			if(getPerson(i, j)._type == SICK)
				updateSick(i, j);
		}
	}
	_daysPassed++;

	updateNewSick();
}

void Map::updateHealthy(int x, int y)
{
    bool is_sick = false;
	if(getPerson(x - 1, y - 1)._type == SICK && !getPerson(x - 1, y - 1)._firstDaySick)
        is_sick = math::rand_probability(_contagiousness);

	if(getPerson(x - 1, y)._type == SICK && !getPerson(x - 1, y)._firstDaySick)
        is_sick = math::rand_probability(_contagiousness);

	if(getPerson(x - 1, y + 1)._type == SICK && !getPerson(x - 1, y + 1)._firstDaySick)
        is_sick = math::rand_probability(_contagiousness);

	if(getPerson(x, y - 1)._type == SICK && !getPerson(x, y - 1)._firstDaySick)
        is_sick = math::rand_probability(_contagiousness);

	if(getPerson(x, y + 1)._type == SICK && !getPerson(x, y + 1)._firstDaySick)
        is_sick = math::rand_probability(_contagiousness);

	if(getPerson(x + 1, y - 1)._type == SICK && !getPerson(x + 1, y - 1)._firstDaySick)
        is_sick = math::rand_probability(_contagiousness);

	if(getPerson(x + 1, y)._type == SICK && !getPerson(x + 1, y)._firstDaySick)
        is_sick = math::rand_probability(_contagiousness);

	if(getPerson(x + 1, y + 1)._type == SICK && !getPerson(x + 1, y + 1)._firstDaySick)
        is_sick = math::rand_probability(_contagiousness);

	if(is_sick)
	{
		setPerson(x, y, SICK);
		_TableauPersonnes[x][y]._firstDaySick = true;
	}
}

void Map::updateNewSick()
{
    for(int i = 0; i < _TableauPersonnes.size(); i++)
	{
		for(int j = 0; j < _TableauPersonnes.front().size(); j++)
			_TableauPersonnes[i][j]._firstDaySick = false;
	}
}

void Map::updateSick(int x, int y)
{
    _TableauPersonnes[x][y]._daysSick++;

	if(_TableauPersonnes[x][y]._resistant)
	{
		if(_TableauPersonnes[x][y]._daysSick == _time_before_cure)
			setPerson(x, y, VACCINATED);
	}
	else
	{
		if(_TableauPersonnes[x][y]._daysSick == _time_before_death)
			setPerson(x, y, DEAD);
	}
}

void Map::clearTabular()
{
    _TableauPersonnes.clear();
}

bool Map::security(int x, int y)
{
    if(x < _TableauPersonnes.size() && x >= 0 && y < _TableauPersonnes.front().size() && y >= 0) //sécurité contre le segmentation fault
        return true;
    return false;
}

Person Map::getPerson(int x, int y)
{
    if(x < _TableauPersonnes.size() && x >= 0 && y < _TableauPersonnes.front().size() && y >= 0) //sécurité contre le segmentation fault
        return _TableauPersonnes[x][y];
    return NULLPERSON;
}

void Map::setPerson(int x, int y, enum TYPE SET)
{
    if(x < _TableauPersonnes.size() && x >= 0 && y < _TableauPersonnes.front().size() && y >= 0) //sécurité contre le segmentation fault
        _TableauPersonnes[x][y]._type = SET;
}

Map::~Map()
{
    if(glIsBuffer(_vboID) == GL_TRUE)
        glDeleteBuffers(1, &_vboID);  // On le libère

    std::cout << "Map libérée" << std::endl;
}
