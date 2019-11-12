#include "xml.h"

xml::xml()
{

  this->arena = new Arena();
}
xml::~xml()
{

  delete this->arena;
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
    this->vel_jogador = atof(str.c_str());
  }

  if (inputFiles->Attribute("velTiro"))
  {
    str = inputFiles->Attribute("velTiro");
    this->vel_tiro = atof(str.c_str());
  }

  this->caminho_arena = caminho + "/" + nome + '.' + tipo;
}

Arena *xml::readSVG()
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

      Circulo *circ = new Circulo(cx, cy, raio, fill);

      this->arena->addCirculo(circ);
      
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
        
        Linha* li = new Linha(x1, y1, x2, y2, str);
        
        this->arena->addLinha(li);

      }
    }
    inputFiles = inputFiles->NextSiblingElement();
  }

  return this->arena;

}
