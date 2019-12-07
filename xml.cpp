#include "xml.h"

xml::xml()
{
  this->arena_config = new config();
}
xml::~xml()
{
  delete this->arena_config;
}

void xml::readXML(char *caminho_config)
{

  string str, nome, tipo, caminho;
  string file_name = strcat(caminho_config, "/config.xml");

  TiXmlDocument doc(file_name.c_str());

  if (doc.LoadFile() != true)
  {
    cout << "Caminho para o arquivo config.xml invalido" << endl;
    exit(0);
  }

  TiXmlElement *inputFiles;

  inputFiles = doc.FirstChildElement("aplicacao")->FirstChildElement("arquivoDaArena")->FirstChildElement("nome");
  nome = inputFiles->GetText();

  inputFiles = doc.FirstChildElement("aplicacao")->FirstChildElement("arquivoDaArena")->FirstChildElement("tipo");
  tipo = inputFiles->GetText();

  inputFiles = doc.FirstChildElement("aplicacao")->FirstChildElement("arquivoDaArena")->FirstChildElement("caminho");
  caminho = inputFiles->GetText();

  inputFiles = doc.FirstChildElement("aplicacao")->FirstChildElement("jogador");

  if (inputFiles->Attribute("vel"))
  {
    str = inputFiles->Attribute("vel");
    this->arena_config->player_speed = atof(str.c_str());
  }
  if (inputFiles->Attribute("velTiro"))
  {
    str = inputFiles->Attribute("velTiro");
    this->arena_config->bullet_player_speed = atof(str.c_str());
  }

  inputFiles = doc.FirstChildElement("aplicacao")->FirstChildElement("inimigo");

  if (inputFiles->Attribute("freqTiro"))
  {
    str = inputFiles->Attribute("freqTiro");
    this->arena_config->fire_frequency = atof(str.c_str());
  }
  if (inputFiles->Attribute("vel"))
  {
    str = inputFiles->Attribute("vel");
    this->arena_config->enemie_speed = atof(str.c_str());
  }
  if (inputFiles->Attribute("velTiro"))
  {
    str = inputFiles->Attribute("velTiro");
    this->arena_config->bullet_enemy_speed = atof(str.c_str());
  }
  this->caminho_arena = caminho + "/" + nome + '.' + tipo;
}

config *xml::readSVG()
{
  string fill, str;
  double cx, cy, raio, x1, x2, y1, y2;
  int id;

  TiXmlDocument doc(this->caminho_arena.c_str());

  if (doc.LoadFile() != true)
  {
    cout << "Caminho para o arquivo SVG invalido" << endl;
    exit(0);
  }

  TiXmlElement *inputFiles;
  inputFiles = doc.FirstChildElement("svg")->FirstChildElement("circle");

  while (inputFiles)
  {
    if (inputFiles->Attribute("cx"))
    {
      str = inputFiles->Attribute("cx");
      cx = atof(str.c_str());

      str = inputFiles->Attribute("cy");
      cy = atof(str.c_str());

      str = inputFiles->Attribute("r");
      raio = atof(str.c_str());

      str = inputFiles->Attribute("id");
      id = atoi(str.c_str());

      fill = inputFiles->Attribute("fill");

      circle *circ = new circle(cx, cy, raio, fill);

      this->arena_config->addCircle(circ);
    }
    else
    {
      inputFiles = doc.FirstChildElement("svg")->FirstChildElement("line");
      if (inputFiles->Attribute("x1"))
      {
        str = inputFiles->Attribute("x1");
        x1 = atof(str.c_str());

        str = inputFiles->Attribute("y1");
        y1 = atof(str.c_str());

        str = inputFiles->Attribute("x2");
        x2 = atof(str.c_str());

        str = inputFiles->Attribute("y2");
        y2 = atof(str.c_str());

        str = inputFiles->Attribute("style");

        line *li = new line(x1, y1, x2, y2, str);

        this->arena_config->addLine(li);
      }
    }

    inputFiles = inputFiles->NextSiblingElement();
  }

  return this->arena_config;
}
