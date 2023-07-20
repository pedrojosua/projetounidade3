#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include "Sculptor.h"


using namespace std;

//ALOCACAO DA MATRIZ 3D
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx; 
    ny = _ny; 
    nz = _nz;
    r = 1;
    g = 1; 
    b = 1;
    // Alocação dinâmica da matriz 3d
    v = new Voxel**[nx];
     for (int i =0; i<nx; i++){
      v[i] = new Voxel*[ny];

        for (int j =0; j<ny; j++){
       v[i][j]= new Voxel[nz];
      }
    }
}

  //DESTRUTOR DA CLASSE

Sculptor::~Sculptor(){
    for(int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){    
            delete[] v[i][j];
        }
    }
    for (int i=0; i <nx; i++){
        delete[] v[i];
    }

    delete[] v;
    //Resetando coordenadas
   int nx = 0; 
   int ny = 0; 
   int nz = 0;
}

  //CORES
  void Sculptor::setColor(float r, float g, float b, float alpha){
	
    Sculptor::r = r; 
    Sculptor::g = g; 
    Sculptor::b = b; 
    Sculptor::a = alpha;
      }
  //INSERIR VOXEL:
  void Sculptor::putVoxel(int x, int y, int z){
   
    v[x][y][z].show = true; 
    //Repassa as propriedades dos voxels
    v[x][y][z].r = r; 
    v[x][y][z].g = g; 
    v[x][y][z].b = b;
    v[x][y][z].a = a;    

      }
  //REMOVER VOXEL:
  void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].show = false;
      }
  //INSERIR BLOCO DE VOXEL:
    void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    //Define uma sequencia de voxel
	for(int x = x0; x<x1; x++){
       for (int y = y0; y<y1; y++){
           for (int z = z0; z<z1; z++){
               v[x][y][z].show = true;
               v[x][y][z].r = r;
               v[x][y][z].g = g;
               v[x][y][z].b = b;
               v[x][y][z].a = a;
           }
       }
    }  
}

 //REMOVER BLOCO DE VOXEL:

  void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
  	
	//Desativa uma sequencia de voxel
    for(int x = x0; x<x1; x++){
       for (int y = y0; y<y1; y++){
           for (int z = z0; z<z1; z++){
               v[x][y][z].show = false;
           }
       }
    }  
}
//INSERIR ESFERA:
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
  
//Recebe as coordenadas e o raio da esfera
  int i, j, k;
  
  for( i = -radius; i<=radius; i++){ 
      for(j = -radius; j<=radius; j++){
          for(k = -radius; k<=radius; k++){
         
            if ((i*i+j*j+k*k) < radius*radius){
              putVoxel(i+xcenter,j+ycenter,k+zcenter); 
            }
          }
        }
      }
    }
//REMOVER ESFERA:
 void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
  int i, j, k;
	
  for(i = -radius; i<radius; i++){
      for(j = -radius; j<radius; j++){
          for(k = -radius; k<radius; k++){
            if((i*i+j*j+k*k) < radius*radius){
              cutVoxel(i+xcenter,j+ycenter,k+zcenter);
            }
          }
        }
    }
 }
  //INSERIR ELIPSOIDE:
  void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
  
   //recebe as coordenadas das dimensões e coordenadas do centro
   float aux_x, aux_y, aux_z;
   int x, y, z;

    for ( x = 0; x < nx; x++){
        for ( y = 0; y < ny; y++){
            for ( z = 0; z < nz; z++){
            aux_x = ((float)(x-xcenter)*(float)(x-xcenter))/(rx * rx);
            aux_y = ((float)(y-ycenter)*(float)(y-ycenter))/(ry * ry);
            aux_z = ((float)(z-zcenter)*(float)(z-zcenter))/(rz * rz);
//calculo da elipsoide
            if ((aux_x + aux_y + aux_z) < 1){
                putVoxel(x,y,z);
              }
            }
          }
        }
      }

//REMOVER ELIPSOIDE:
  void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){

   double aux_x, aux_y, aux_z;
   int x, y, z;
   
    for ( x = 0; x < nx; x++){
        for ( y = 0; y < ny; y++){
            for ( z = 0; z < nz; z++){
            aux_x = ((float)(x-xcenter)*(float)(x-xcenter))/(rx * rx);
            aux_y = ((float)(y-ycenter)*(float)(y-ycenter))/(ry * ry);
            aux_z = ((float)(z-zcenter)*(float)(z-zcenter))/(rz * rz);

            if ((aux_x + aux_y + aux_z) < 1){
                cutVoxel(x,y,z);
            }
            }
        }
    }
}

  //FORMAR ARQUIVO OFF:
  void Sculptor::writeOFF(const char *filename){
    int n_Voxel = 0;
    int vert;
    int  i, j, k, a, b, c; //auxiliares
    float valor = 0.5;
    std::ofstream fout;
    fout.open(filename);
    if (fout.is_open()){
        fout<<"OFF\n"; //Define off na primeira linha

        // Percorre todas as dimensoes verificando os voxel em exibiçao
        for (i = 0; i < nx; i++){
            for (j = 0; j <ny; j++){
                for (k = 0; k <nz; k++){
                    if(v[i][j][k].show == true){
                    n_Voxel++; //Quantidade de voxels ativos
                    }
                }
            }
        }
        fout <<n_Voxel * 8<<" "<<n_Voxel * 6 << " " << "0" << "\n"; 
        // exibe a quantidade total de vertices, faces e arestas

        //Pecorre as posições a, b, c e exibe as coordenadas do voxel
        //No primeiro voxel o fix será o valor de referencia
        for (a = 0; a < nx; a++){
            for (b = 0; b < ny; b++){
                for (c = 0; c < nz; c++){
                    if(v[a][b][c].show == true){
                        fout << a - valor << " " << b + valor << " " << c - valor << "\n" << flush;
                        fout << a - valor << " " << b - valor << " " << c - valor << "\n" << flush;
                        fout << a + valor << " " << b - valor << " " << c - valor << "\n" << flush;
                        fout << a + valor << " " << b + valor << " " << c - valor << "\n" << flush;
                        fout << a - valor << " " << b + valor << " " << c + valor << "\n" << flush;
                        fout << a - valor << " " << b - valor << " " << c + valor << "\n" << flush;
                        fout << a + valor << " " << b - valor << " " << c + valor << "\n" << flush;
                        fout << a + valor << " " << b + valor << " " << c + valor << "\n" << flush;
                    }
                }
            }
        }
           n_Voxel = 0; //Reseta a quantidade de voxel

          fout << std::fixed;
          fout << std::setprecision(2);
         // Verifica os voxel ativos e exibe as linhas com numeros de faces e as combinacoes que exibem a face
        for (a= 0; a<nx; a++){
            for (b = 0; b<ny; b++){
                for (c= 0; c<nz; c++){
                    if(v[a][b][c].show == true){
                    vert = n_Voxel * 8;
                    fout << fixed;

                  
      
                    fout << "4" << " " << 0+vert << " " << 3+vert << " " << 2+vert << " " << 1+vert << " ";
                    //exibindo propriedades do voxel:
                    fout << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

                    fout << "4" << " " << 4+vert << " " << 5+vert << " " << 6+vert << " " << 7+vert << " ";
                    fout << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

                    fout << "4" << " " << 0+vert << " " << 1+vert << " " << 5+vert << " " << 4+vert << " ";
                    fout << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

                    fout << "4" << " " << 0+vert << " " << 4+vert << " " << 7+vert << " " << 3+vert << " ";
                    fout << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

                    fout << "4" << " " << 3+vert << " " << 7+vert << " " << 6+vert << " " << 2+vert << " ";
                    fout << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

                    fout << "4" << " " << 1+vert << " " << 2+vert << " " << 6+vert << " " << 5+vert << " ";
                    fout << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

                    n_Voxel++; //incrementa o num de voxels
                    }
                }
            }
        }
    }
    else{
    cout << "Erro ao abrir arquivo de texto."; 
    }
    
    fout.close();
}