
/**
 * @file Nmer.h
 * @brief TDA Nmer
 *   Representa un conjunto de Nmer subsecuencias de tamaño 1 hasta N que se pueden obtener a partir de una cadena de ADN
 * @author alumno
 * @bug Por espeficicar
 */
#ifndef __NMER_H
#define __NMER_H

#include <string>
#include <set>
#include <unordered_map>
#include "ktree.h"


using namespace std;



class Nmer {
public:
    typedef unsigned int size_type;

    /** @brief Constructor primitivo .
        Crea un Nmer de longitud maxima 0, con el valor ('-',0) en la raíz
     */
    Nmer();

    /** @brief lectura fichero serializado
     * @param nombre_fichero fichero serializado con extension .srl
     *
     * Genera a partir del fichero el ktree que contiene todos los kmers asociados a una cadena de ADN
     *
     * La cadena original viene descrita en el fichero serializado
     */
    bool loadSerialized(const string & nombre_fichero);


    /** @brief Imprime los Nmers
     * @todo Debemos de implementar este método de forma que nos garantizemos que se imprimen todos los Nmers.
     */
    void list_Nmer() const;


    /** @brief Máxima longitud de los Nmers almacenados
     */
    unsigned int length()const;


    /** @brief Número de Nmers almacenados
     */
    size_type size() const;

    /** @brief Operador de asignacion
     */
    Nmer& operator=(const Nmer& a);

    /** @brief Devuelve el Nmer (subarbol) asociado a un prefijo. Por ejemplo, si adn es
 "ACT", devuelve el Nmer que representa todas las subcadenas que empiezan por "ACT" (ACT*)
     */
    Nmer Prefix(string adn);

    /** @brief  Se devuelve un Nmer donde para cada nodo (representa una
 secuencia) se computa la suma de las frecuencias en *this y en referencia,
     */
    //Nmer union(const Nmer ref);

    /** @brief   Devuelve true si la cadena adn est� representada en el
 �rbol.
     */
    bool containString(const string adn) const;

    /** @brief   Devuelve true si cada nodo de *this est� tambi�n
 representado en reference, es decir, si todas las secuencias representadas en el �rbol de *this est�n tambi�n
 incluidas en reference. False en otro caso.
     */
    bool included(const Nmer reference) const;

    /*___________________________________________________
                     METODOS MAS IMPORTANTES
     ____________________________________________________*/

    /** @brief    Construir Nmer a partir de cadena de ADN
     */
    void sequenceADN(unsigned int tama, const string &adn);

    
    /** @brief Functor para convertir un string en un pair<char,int>
     * se utiliza en loadSerialized
     */
    class OrdenCre {
    public:
        bool operator()(const pair<string, int> &p1, const pair<string, int> &p2) const{
            return p1.second <= p2.second;
        }
    };
    
    /** @brief Functor para convertir un string en un pair<char,int>
     * se utiliza en loadSerialized
     */
    class OrdenDecre {
    public:

        bool operator()(const pair<string, int> &p1, const pair<string, int> &p2) const{
            return p2.second <= p1.second;
        }
    };
    
    /** @brief     devuelve la lista de todas las subcadenas
 (no prefijo) que aparecen menos de threshold veces en el Nmer ordenadas en orden creciente de frecuencia
     */
    set<pair<string, int>, OrdenCre > rareNmer(int threshold);

    /** @brief    Devuelve la lista de las cadenas de
 longitud mayor posible (no prefijo) que aparecen m�s de threshold veces en el Nmer, ordenadas en orden
 decreciente de frecuencia    
     */
    set<pair<string, int>, OrdenDecre > commonNmer(int threshold);

    /** @brief     Devuelve el conjunto de Nmers de longitud exacta l.
     */
    set<pair<string, int>, OrdenCre > level(int l);
    
    
    /*_________________________________________________________
     * Métodos auxiliares necearios para algunos de los demas
    ___________________________________________________________*/
    void secNode(ktree<pair<char, int>, 4>::const_node n, int threshold, set<pair<string, int>, Nmer::OrdenCre > &devo);
    
    void secNodeCommon(ktree<pair<char, int>, 4>::const_node n, int threshold, set<pair<string, int>, Nmer::OrdenDecre > &devo);
    
    void rankDec(ktree<pair<char, int>, 4>::const_node n, set<pair<string, int>, Nmer::OrdenDecre > &devo) const;
    
    unordered_map<string, int> getPosRank() const;
    
    /** @brief   Distancia entre dos Nmer
     */
    float Distance(const Nmer & x);

private:
    ktree<pair<char, int>, 4> el_Nmer; // subsecuencias 
    unsigned int max_long; // Mayor longitud de la cadena representada, esto es, el nivel máximo del árbol

    void insertar_cadena(const string & cadena);
    
    int ind_nodo(char c){
        switch(toupper(c)){
            case 'A':
                return 0;
            case 'G':
                return 1;
            case 'C':
                return 2;
            case 'T':
                return 3;
            default:
                return -1;
        }
    }
    
    /** @brief Comprueba si s2 es prefijo de s1
     */
    bool is_prefijo(const string& a, const string& b) {
        if (a.size() > b.size()) {
            return a.substr(0, b.size()) == b;
        } else {
            return b.substr(0, a.size()) == a;
        }
    }

    /** @brief Functor para convertir un string en un pair<char,int>
     * se utiliza en loadSerialized
     */
    class String2Base {
    public:

        pair<char, int> operator()(const string & cad) {
            pair<char, int> salida;
            salida.first = cad[0];
            salida.second = std::stoi(cad.substr(1));
            return salida;
        }
    };
    
    
    

    /** @brief Functor para convertir un pair<char,int> en un string 
     * Necesario para serializar un Nmer.
     */
    class Base2String {
    public:

        string operator()(const pair<char, int> & x) {
            string salida = string(1, x.first) + " " + std::to_string(x.second);
            return salida;
        }
    };
};



#endif
