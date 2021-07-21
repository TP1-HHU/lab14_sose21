#include <iostream>
#include <fstream>
#include <cmath>
//-------------------------------------
using namespace std;
//-------------------------------------
void read_data(ifstream& in, const int N, double* const M, double* const r, double* const v);

//-------------------------------------
int main(){

    const string fname = "iv.txt";

    ofstream out("data");
    ifstream in(fname);

    int N; in >> N;
    
    double* const M = new double[N];
    double* const r = new double[3*N];
    double* const v = new double[3*N];
    
    read_data(in, N, M, r, v);

    in.close();

    const double G = 2.9592208286e-4; 

    double tEnd = 365*100;  // in days
    double dt = 1; // in days
    double t = 0;
    double H;

    int Nt = int(tEnd/dt+0.5);
    dt = tEnd/Nt;

    double H0 = energy(r,v,M,N,G);

    for(int i = 0; i < Nt; i++){


       
    }

    out.close();

    delete[] M;
    delete[] r;
    delete[] v;

}
//-------------------------------------
void read_data(ifstream& in, const int N, double* const M, double* const r, double* const v){
    // Read masses, in kg
    for(int i=0; i<N; i++){
        in >> M[i];
    }
    double Msun = M[0];
    // Normalize to mass of sun
    for(int i=0; i<N; i++){
         M[i] /= Msun;
    }

    // Read initial positions (x,y,z), in AU
    for(int i=0; i<N; i++){
        in >> r[3*i];
        in >> r[3*i+1];
        in >> r[3*i+2];
    }
    // Read initial positions (vx,vy,vz), in AU/d
    for(int i=0; i<N; i++){
        in >> v[3*i];
        in >> v[3*i+1];
        in >> v[3*i+2];
    }
}
//-------------------------------------
