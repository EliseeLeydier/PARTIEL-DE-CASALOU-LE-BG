#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cctype>

using namespace std;


vector<string> litUnFichier (const string & chemin)
{
    vector<string> toutesLesLignes;
    ifstream ifs (chemin);
    if (!ifs) {
        cout << "non" << endl;
        return toutesLesLignes;
    }
    string ligne;
    string uneLigne;
    for (;getline(ifs, uneLigne);)
        ligne = "";
        for(unsigned i = 0; i < uneLigne.size(); ++i){

            if(uneLigne[i] == ','){
                toutesLesLignes.push_back(ligne);
                ligne = "";
            }
            else{
                ligne.push_back(uneLigne[i]);
            }
        }

    return toutesLesLignes;
}

string to_lower(string str){
    for(unsigned i = 0; i < str.size(); ++i){
        str[i] = tolower(str[i]);
    }
    return str;
}


void creerMDP(vector<string> &dicoFR, vector<string> &vecPonctuation, string &mdp){
    while(mdp.size() < 30){
        unsigned indexe = rand() % (dicoFR.size() - 1);
        string mot = to_lower(dicoFR[indexe]);
        mot[0] = toupper(mot[0]);
        mdp += mot;
        mdp +=  to_string(rand() % 9);
        mdp += vecPonctuation[rand() % (vecPonctuation.size() - 1)];
    }
}

int main()
{
    srand(time(0));

    vector<string> dicoFR (litUnFichier("liste_francais.txt"));
    vector<string> vecPonctuation = {".", ",","_", "-", "?", "!"};
    string mdp;
    creerMDP(dicoFR, vecPonctuation, mdp);
    cout << mdp;

    return 0;
}
