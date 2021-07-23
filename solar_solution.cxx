#include <iostream>
#include <fstream>
#include <cmath>
//-------------------------------------
using namespace std;
//-------------------------------------
void read_data(ifstream& in, const int N, double* const M, double* const r, double* const v);

void step_v(double* const v, const double* const r, const double* const M, const int N,
            const double dt, const double G);

 void step_r(double* const r, const double* const v,
            const int N, const double dt);           

double energy(const double* const r, const double* const v,
              const double* const M, const int N,
              const double G);
//-------------------------------------
int main(){

    const string fname = "iv2.txt";

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

        step_v(v, r, M, N, 0.5*dt, G);
        step_r(r, v, N, dt);
        step_v(v, r, M, N, 0.5*dt, G);

        H = energy(r,v,M,N,G);

        t += dt;

        out << t << "\t";
        for(int i=0; i<N; i++)
            out << r[3*i] << "\t" << r[3*i+1] << "\t" << r[3*i+2] << "\t";
        out << "\t" << H/H0 <<  endl;
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
void step_v(double* const v, const double* const r, const double* const M, const int N,
            const double dt, const double G){

        // push v for dt
        for(int j = 0; j<N; j++){
            double Fx = 0;
            double Fy = 0;
            double Fz = 0;
            // Calculate force of body k on j
            for(int k=0; k<N; k++){
                if (k==j) continue;
                // Distance between k and j
                double dx = r[3*k]   - r[3*j];
                double dy = r[3*k+1] - r[3*j+1];
                double dz = r[3*k+2] - r[3*j+2];
                double dist = sqrt(dx*dx + dy*dy + dz*dz);
                double inv3 = 1.0/(dist*dist*dist);
                Fx += M[k] * dx * inv3;
                Fy += M[k] * dy * inv3;
                Fz += M[k] * dz * inv3;
            }
            Fx *= G;
            Fy *= G;
            Fz *= G;
            v[3*j]   += dt*Fx;
            v[3*j+1] += dt*Fy;
            v[3*j+2] += dt*Fz;
        }
}
//-------------------------------------
void step_r(double* const r, const double* const v,
            const int N, const double dt){

for(int j = 0; j<3*N; j++)
    r[j] += dt*v[j];
}
//-------------------------------------
double energy(const double* const r, const double* const v,
              const double* const M, const int N,
              const double G){
    double T=0;
    double U=0;
    for(int i=0; i<N; i++){
        T += 0.5 * M[i] * (v[3*i]*v[3*i] + v[3*i+1]*v[3*i+1] + v[3*i+2]*v[3*i+2]);
        double Vi=0;
        for(int j=0; j<N; j++){
            if (j==i) continue;
            double dx = r[3*i]  - r[3*j];
            double dy = r[3*i+1]- r[3*j+1];
            double dz = r[3*i+2]- r[3*j+2];
            double dist = sqrt(dx*dx + dy*dy + dz*dz);
            Vi += -M[j] / dist;
        }
        Vi *= G*M[i];
        U = U + Vi/2;
    }
    return T+U;
}