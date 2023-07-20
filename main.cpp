#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
#include "Sculptor.h"
#include "FiguraGeometrica.h"
#include "PutBox.h"
#include "CutBox.h"
#include "PutVoxel.h"
#include "CutVoxel.h"
#include "PutSphere.h"
#include "CutSphere.h"
#include "PutEllipsoid.h"
#include "CutEllipsoid.h"

int main(){
  Sculptor *s;
  int nx, ny, nz;
  int x,y,z;
  int x0, x1, y0, y1, z0, z1;
  int xcenter, ycenter, zcenter,radius;
  int rx, ry, rz;
  float r, g, b, a;
  std::vector<FiguraGeometrica*>f;
  std::ifstream fin;
  std::string str;
  fin.open("stars.txt");
  //fin.open("teste.txt"); //para abrir o teste .off tem que colocar um comentario no stars.txt
  if(!fin.is_open()){
    std::exit(0);
  }

  // processa o arquivo enquanto houver linhas
  // para ler
  while(fin.good()){
    fin >> str;
    if(!fin.good()){
      break;
    }
    if(str.compare("dim")==0){
      fin >> nx >> ny >> nz;
      std::cout << nx << "x" << ny << "x" << nz;
      std::cout << std::endl;
      s = new Sculptor(nx, ny, nz);

    } else if(str.compare("putbox")==0){
      std::cout << "PutBox" << std::endl;
      fin >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
      fin >> r >> g >>  b >> a;
      f.push_back(new PutBox(x0, x1,y0, y1,z0, z1,r,g,b,a));

    } else if(str.compare("cutbox")==0){
      fin >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
       f.push_back(new CutBox(x0, x1, y0, y1, z0, z1));
    }
    else if(str.compare("putvoxel")==0){
      fin >> x >> y >> z;
      fin >> r >> g >>  b >> a;
       f.push_back(new PutVoxel(x,y,z,r, g, b, a));
    }

    else if(str.compare("cutvoxel")==0){
      fin >> x >> y >> z;
      fin >> r >> g >>  b >> a;
       f.push_back(new CutVoxel(x,y,z));
    }

     else if(str.compare("putsphere")==0){
        std::cout << "PutSphere"<< std::endl;
      fin >> xcenter >> ycenter >> zcenter >> radius;
      fin >> r >> g >> b >> a;
       f.push_back(new PutSphere(xcenter,ycenter,zcenter,radius,r,g,b,a));
    }

       else if(str.compare("cutsphere")==0){
      fin >> xcenter >> ycenter >> zcenter >> radius;
       f.push_back(new CutSphere(xcenter,ycenter,zcenter,radius));
    }
    
  else if(str.compare("putellipsoid")==0){
      std::cout<<"PutEllipsoid"<<std::endl;
      fin >> xcenter >> ycenter >> zcenter;
      fin >> rx >> ry >> rz;
      fin >> r >> g >>  b >> a;
       f.push_back(new PutEllipsoid(xcenter,ycenter,zcenter,rx, ry, rz, r, g, b, a));
    }
    else if(str.compare("cutellipsoid")==0){
      fin >> xcenter >> ycenter >> zcenter;
      fin >> rx >> ry >> rz;
       f.push_back(new CutEllipsoid(xcenter,ycenter,zcenter,rx,ry,rz));
    }
    
  }
  for(int i=0; i<(int)f.size(); i++){
    std::cout << "draw\n";
    f[i]->draw(*s);
  }
    
   s->writeOFF("stars.off");
   //s->writeOFF("teste.off");
    
  for(int i=0; i<(int)f.size(); i++){
    delete f[i];
  }
   delete s;

    std::cout<<"Fim";


  return 0;
}