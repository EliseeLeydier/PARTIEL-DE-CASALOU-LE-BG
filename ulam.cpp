#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

template <typename T>
void affichTab (const vector<T> & tab){
    for (const T & val : tab)
        cout << val << '\t';
    cout << endl;
}

template <typename T>
void affichMat (const vector<vector<T>> & mat){
    for (const vector<T> & uneLigne : mat){
        for (const T & val : uneLigne)
            cout << val << '\t';
        cout << endl;
    }
}

vector<unsigned> generePremierPlusPetitQueV2 (const unsigned & N){
    vector<unsigned> nombresPremiers (N-1);
    for (size_t i (1); i < nombresPremiers.size(); ++i)
        nombresPremiers[i] = i +1;

    for (size_t i (1); i < N; ++i){
        if (nombresPremiers[i] == 0) continue;
        size_t j (i+nombresPremiers[i]);
        for (; j < nombresPremiers.size(); j += nombresPremiers[i])
            nombresPremiers[j] = 0;
    }
    size_t posAInsrer (2);
    for (size_t i (2); i < nombresPremiers.size(); ++i){
        if (nombresPremiers[i] != 0)
            nombresPremiers[posAInsrer++] = nombresPremiers[i];
    }
    nombresPremiers.resize(posAInsrer);
    nombresPremiers.erase(nombresPremiers.begin());
    return nombresPremiers;
}

void genereMatricEscargot (vector<vector<unsigned>> & mat){
    size_t i (mat.size()/2), j (mat.size()/2);
    unsigned numerTour (1), nombreAInserer (2);
    mat[i][j++] = 1;
    
    for (;nombreAInserer < mat.size() * mat.size();){
      //  ++j;
        //haut
        for (unsigned k (0); k < 2*numerTour; ++k){
            mat[i][j] = nombreAInserer++;
            --i;
        }
        ++i;
        --j;
        //gauche
        for (unsigned k (0); k < 2*numerTour; ++k){
            mat[i][j] = nombreAInserer++;
            --j;
        }
        ++i;
        ++j;
        //bas
        for (unsigned k (0); k < 2*numerTour; ++k){
            mat[i][j] = nombreAInserer++;
            ++i;
        }
        --i;
        ++j;
        //droite
        for (unsigned k (0); k < 2*numerTour; ++k){
            mat[i][j] = nombreAInserer++;
            ++j;
        }
    //    --j;
        ++numerTour;
    }
}

void genereMatricUlam (vector<vector<unsigned>> & mat,
                       const vector <unsigned> & nombresPremiers){

    for (vector<unsigned> & uneLigne : mat){
        for (unsigned & val : uneLigne){
            if (find (nombresPremiers.begin(), nombresPremiers.end(), val)
                    == nombresPremiers.end())
                val = 0;
        }

    }
}


template <typename T>
void affichMatUlam (const vector<vector<T>> & mat){
    for (const vector<T> & uneLigne : mat){
        for (const T & val : uneLigne)
           cout << (val == 0? ' ' : 'X') ;
        cout << endl;
    }
}

void UlamVersPPM(const vector<vector<unsigned>> & mat){
    ofstream ofs ("sortie2.ppm");
    ofs << "P3" << '\n';
    ofs << mat.size() << ' ' << mat.size() << '\n';
    ofs << "255" << '\n';
    const string noir ("0 0 255 ");
    const string blanc ("255 255 255 ");
    for (const vector<unsigned> & uneLigne : mat){
        for (const unsigned & val : uneLigne)
           ofs << (val == 0? blanc : noir) ;
        ofs << '\n';
    }
}

int main()
{
    //generePremierPlusPetitQue(100);
//    affichTab(generePremierPlusPetitQue(25));
//    affichTab(generePremierPlusPetitQueV2(25));
    unsigned taille (101);
//    cout << generePremierPlusPetitQueV2(taille*taille).size() << endl;
//cout << generePremierPlusPetitQue(taille*taille).size()<< endl;
    vector<unsigned> nombrePremiers = generePremierPlusPetitQueV2(taille*taille);

    vector <vector<unsigned>> mat (taille, vector<unsigned> (taille, 1));
    genereMatricEscargot(mat);
    genereMatricUlam (mat, nombrePremiers);
    //affichMatUlam (mat);
    UlamVersPPM(mat);
    return 0;
}
