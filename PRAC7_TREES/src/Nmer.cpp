#include "Nmer.h"

#include <fstream>
#include <stack>
#include <set>
#include <unordered_map>
#include <cmath>

std::ostream& operator<<(ostream & s, const pair<char, int> & par) {
    s << par.first << " " << par.second;
    return s;
}

void recorrido_preorden(ktree<pair<char, int>, 4>::const_node n) {
    if (!n.null()) {
        stack<char> st;
        typename ktree<pair<char, int>, 4>::const_node aux(n);

        /*OBTENEMOS LA SECUENCIA COMPLETA DEL NODO: 
         * Con un node aux, recorremos desde cada nodo hacia su padre. 
         * Metemos en una pila cada etiqueta.first(char) para despues imprimir dicha pila, ya que si no saldrian al revés*
         * */
        while (!aux.parent().null()) {
            //cout << aux.operator*().first << "";
            st.push(aux.operator*().first);
            aux = aux.parent();
        }
        while (!st.empty()) {
            cout << st.top();
            st.pop();
        }
        cout << " " << n.operator*().second << endl;

        typename ktree<pair<char, int>, 4>::const_node::child_iterator ini = n.begin();
        typename ktree<pair<char, int>, 4>::const_node::child_iterator fin = n.end();
        while (ini != fin) {
            recorrido_preorden(*ini);
            ++ini;
        }
    }
}

Nmer::Nmer() {
    max_long = 0;
    el_Nmer = ktree<pair<char, int>, 4>(pair<char, int>('-', 0));
}

bool Nmer::loadSerialized(const string & fichero) {
    string cadena;
    ifstream fe;
    pair<char, int> nulo('x', -1);
    Nmer::String2Base stb;

    fe.open(fichero.c_str(), ifstream::in);
    if (fe.fail()) {
        cerr << "Error al abrir el fichero " << fichero << endl;
    } else {
        //leo la cabecera del fichero (líneas que comienzan con #)
        do {
            getline(fe, cadena, '\n');
        } while (cadena.find("#") == 0 && !fe.eof());
        // leemos Nmer_length
        max_long = std::stoi(cadena);
        // leemos cadena serializada
        getline(fe, cadena, '\n');
        el_Nmer.deserialize(cadena, nulo, ';', stb);
        fe.close();
        return true;
    } // else
    fe.close();
    return false;
}

void Nmer::list_Nmer() const {
    // implmenentar el recorrido en preorden para el ktree de forma que nos devuelva los Nmers completos y no sólo el nodo.
    recorrido_preorden(el_Nmer.root());
}

unsigned int Nmer::length() const {
    return max_long;
}

Nmer::size_type Nmer::size() const {
    return el_Nmer.size() - 1;
}

/*___________________________________________________
                    METODOS MAS IMPORTANTES
    ____________________________________________________*/


void Nmer::sequenceADN(unsigned int tama, const string& adn) {
    string subcadena = "";
    el_Nmer = ktree<pair<char, int>, 4>(pair<char, int>('-', 0));

    for (int i = 0; i < adn.size(); i++) {
        subcadena = adn.substr(i, tama);
        insertar_cadena(subcadena);
    }
}

void Nmer::insertar_cadena(const string& cadena) {
    int indice = 0, i = 0;
    ktree<pair<char, int>, 4>::node n_act(el_Nmer.root());

    for (i; i < cadena.size(); i++) {
        indice = ind_nodo(cadena[i]); //indice del nodo en el nivel i+1
        if (!n_act.k_child(indice).null()) {
            n_act.k_child(indice).operator*().second++;
        } else {
            const pair<char, int> e(cadena[i], 1);
            el_Nmer.insert_k_child(n_act, indice, e);
        }

        n_act = n_act.k_child(indice);
    }
}

void Nmer::secNode(ktree<pair<char, int>, 4>::const_node n, int threshold, set<pair<string, int>, Nmer::OrdenCre > &dev) {
    bool insertar = true, seguir = true;

    if (!n.null()) {
        pair<string, int> aux_pair;
        stack<char> st;
        ktree<pair<char, int>, 4>::const_node aux_node(n);


        /*OBTENEMOS LA SECUENCIA COMPLETA DEL NODO: 
         * Con un node aux, recorremos desde cada nodo hacia su padre. 
         * Metemos en una pila cada etiqueta.first(char) para despues imprimir dicha pila, ya que si no saldrian al revés*
         * */
        while (!aux_node.parent().null()) {
            //cout << aux.operator*().first << "";
            st.push(aux_node.operator*().first);
            aux_node = aux_node.parent();
        }
        while (!st.empty()) {
            //cout << st.top();
            aux_pair.first.push_back(st.top());
            st.pop();
        }
        aux_pair.second = n.operator*().second;

        if (aux_pair.second <= threshold) {
            if (!dev.empty()) {
                for (set<pair<string, int> >::iterator it = dev.begin(); it != dev.end() && seguir; ++it) {

                    if (is_prefijo(it->first, aux_pair.first)) {
                        insertar = false;
                        seguir = false;
                    }

                    if (is_prefijo(aux_pair.first, it->first)) {
                        dev.erase(it);
                        insertar = false;
                        seguir = false;
                    }
                }

            }

            if (insertar)
                dev.insert(aux_pair);
        }

        ktree<pair<char, int>, 4>::const_node::child_iterator ini = n.begin();
        ktree<pair<char, int>, 4>::const_node::child_iterator fin = n.end();
        while (ini != fin) {
            //cout << ini.operator *().operator *().first << " " << ini.operator *().operator *().second << endl;
            secNode(*ini, threshold, dev);
            ++ini;
        }
    }
}

void Nmer::secNodeCommon(ktree<pair<char, int>, 4>::const_node n, int threshold, set<pair<string, int>, Nmer::OrdenDecre > &devi) {
    bool insertar = true, seguir = true;

    if (!n.null()) {
        pair<string, int> aux_pair;
        stack<char> st;
        ktree<pair<char, int>, 4>::const_node aux_node(n);


        /*OBTENEMOS LA SECUENCIA COMPLETA DEL NODO: 
         * Con un node aux, recorremos desde cada nodo hacia su padre. 
         * Metemos en una pila cada etiqueta.first(char) para despues imprimir dicha pila, ya que si no saldrian al revés*
         * */
        while (!aux_node.parent().null()) {
            //cout << aux.operator*().first << "";
            st.push(aux_node.operator*().first);
            aux_node = aux_node.parent();
        }
        while (!st.empty()) {
            //cout << st.top();
            aux_pair.first.push_back(st.top());
            st.pop();
        }
        aux_pair.second = n.operator*().second;

        if (aux_pair.second > threshold) {
            if (!devi.empty()) {
                for (set<pair<string, int> >::iterator it = devi.begin(); it != devi.end() && seguir; ++it) {

                    if (is_prefijo(it->first, aux_pair.first)) {
                        insertar = false;
                        seguir = false;
                    }

                    if (is_prefijo(aux_pair.first, it->first)) {
                        devi.erase(it);
                        insertar = false;
                        seguir = false;
                    }
                }

            }

            if (insertar)
                devi.insert(aux_pair);
        }

        ktree<pair<char, int>, 4>::const_node::child_iterator ini = n.begin();
        ktree<pair<char, int>, 4>::const_node::child_iterator fin = n.end();
        while (ini != fin) {
            //cout << ini.operator *().operator *().first << " " << ini.operator *().operator *().second << endl;
            secNodeCommon(*ini, threshold, devi);
            ++ini;
        }
    }
}

set<pair<string, int>, Nmer::OrdenCre > Nmer::rareNmer(int threshold) {
    set<pair<string, int>, Nmer::OrdenCre> dev;

    secNode(el_Nmer.root(), threshold, dev);

    return dev;
}

set<pair<string, int>, Nmer::OrdenDecre> Nmer::commonNmer(int threshold) {
    set<pair<string, int>, Nmer::OrdenDecre> dev;

    secNodeCommon(el_Nmer.root(), threshold, dev);

    return dev;
}

set<pair<string, int>, Nmer::OrdenCre> Nmer::level(int l) {
    set<pair<string, int>, Nmer::OrdenCre> dev;

    secNode(el_Nmer.root(), l, dev);

    for (set<pair<string, int> >::iterator it = dev.begin(); it != dev.end(); ++it)
        if ((signed int) it->first.size() != l)
            dev.erase(it);
}

void Nmer::rankDec(ktree<pair<char, int>, 4>::const_node n, set<pair<string, int>, Nmer::OrdenDecre > &devo) const {
    if (!n.null()) {
        pair<string, int> aux_pair;
        stack<char> st;
        ktree<pair<char, int>, 4>::const_node aux_node(n);

        /*OBTENEMOS LA SECUENCIA COMPLETA DEL NODO: 
         * Con un node aux, recorremos desde cada nodo hacia su padre. 
         * Metemos en una pila cada etiqueta.first(char) para despues imprimir dicha pila, ya que si no saldrian al revés*
         * */
        while (!aux_node.parent().null()) {
            //cout << aux.operator*().first << "";
            st.push(aux_node.operator*().first);
            aux_node = aux_node.parent();
        }
        while (!st.empty()) {
            //cout << st.top();
            aux_pair.first.push_back(st.top());
            st.pop();
        }
        aux_pair.second = n.operator*().second;

        devo.insert(aux_pair);

        ktree<pair<char, int>, 4>::const_node::child_iterator ini = n.begin();
        ktree<pair<char, int>, 4>::const_node::child_iterator fin = n.end();
        while (ini != fin) {
            rankDec(*ini, devo);
            ++ini;
        }
    }
}

unordered_map<string, int> Nmer::getPosRank() const {
    unordered_map<string, int> deva;
    set<pair<string, int>, Nmer::OrdenDecre> aux;

    rankDec(el_Nmer.root(), aux);

    int ind = 1;
    for (auto it = aux.cbegin(); it != aux.cend(); ++it) {
        if (it->second > 0) {
            deva[it->first] = ind++;
        }
    }

    return deva;
}

float Nmer::Distance(const Nmer& y) {
    unordered_map<string, int> posRankingX = getPosRank();
    unordered_map<string, int> posRankingY = y.getPosRank();

//    for (auto it = posRankingX.begin(); it != posRankingX.end(); ++it)
//        cout << it->first << " " << it->second << endl;
//    cout << endl;
//    for (auto it = posRankingY.begin(); it != posRankingY.end(); ++it)
//        cout << it->first << " " << it->second << endl;
//    cout << posRankingX.size() << " " << posRankingY.size() << endl;

    int posx, posy;
    float valor;
    unordered_map<string, int>::iterator ity;

    int maximo = max(posRankingX.size(), posRankingY.size());
    float dist = 0;

    for (auto itx = posRankingX.cbegin(); itx != posRankingX.cend(); ++itx) {
        valor = 1;
        ity = posRankingY.find(itx->first);
        
        if (ity != posRankingY.end()){
            posx = itx->second;
            posy = ity->second;
            valor = 1.0 * abs(posx - posy) / maximo;
        }

        dist += valor;
    }
    return dist / posRankingX.size();
}






