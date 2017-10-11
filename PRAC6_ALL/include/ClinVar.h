/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClinVar.h
 * Author: juane
 *
 * Created on 21 de diciembre de 2016, 12:47
 */

#ifndef CLINVAR_H
#define CLINVAR_H

#include <string>
#include <set>
#include <list>
#include <map>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "mutacion.h"
#include "enfermedad.h"


typedef string IDgen;
typedef string IDmut;
typedef string IDenf;

using namespace std;
class ClinVar{
public:
    
    /* @brief iterador sobre mutaciones en orden creciente de cromosoma/posicion*/
    class iterator {
    private:
        friend class ClinVar;
        set<mutacion>::iterator it;
    public:
        const mutacion& operator*(); //const - no se puede modificar la mutacion y alterar el orden del set
        bool operator!=(const iterator& x) const;
        iterator& operator++();
        iterator operator++(int);
    };
    
    /* @brief iterador sobre enfermedades
    */
    typedef map<IDenf, enfermedad>::iterator enfermedad_iterator;
    
    /* @brief iterador sobre mutaciones considerando el orden creciente del ID del gen*/
    class gen_iterator {
    public:
        const mutacion& operator*(); //const - no se puede modificar la mutacion y alterar el orden del set
        bool operator!=(const gen_iterator& x) const;
        gen_iterator& operator++();
        gen_iterator operator++(int);
    private:
        friend class ClinVar;
        map<IDgen, list< set<mutacion>::iterator> >::iterator itmap;
        list<set<mutacion>::iterator>::iterator itlist;
        ClinVar *ptrclinvar;
    };
    
    //...
    void load(string nombreDB);
    void insert(const mutacion& x);
    bool erase(IDmut ID);
    iterator find_Mut (IDmut ID) const;
    enfermedad_iterator find_Enf(IDenf ID) ;
    
    vector<enfermedad> getEnfermedades(const mutacion& mut) ;
    list<IDenf> getEnfermedades(string keyword) const;
    set<IDmut> getMutacionesEnf(IDenf ID) const;
    set<IDmut> getMutacionesGen(IDgen ID) const;
    set<mutacion,ProbMutaciones> topKMutaciones(int k, string keyword);
    
    int countMut() const;
    int countGen() const;
    int countenfa() const;
    int countenf() const;
    
    /* Métodos relacionados con los iteradores */
    iterator begin();
    iterator end();
    iterator lower_bound(string cromosoma, unsigned int posicion);
    iterator upper_bound(string cromosoma, unsigned int posicion);
    enfermedad_iterator ebegin();
    enfermedad_iterator eend();
    gen_iterator gbegin();
    gen_iterator gend();
    //...
    /*bool ClinVar::erase(IDmut ID){
        mutacion aux;
        aux.setID(ID);
        mutDB.erase(aux);
        IDm_map.erase(ID);
    }*/
private:
    friend class iterator;
    friend class gen_iterator;
    set<mutacion> mutDB; //base de datos que contiene toda la información asociada a una mutacion
    unordered_map<IDmut,set<mutacion>::iterator> IDm_map; // Asocia IDmutacion con mutación
    map<IDgen, list<set<mutacion>::iterator> > gen_map; // Asocia genes con mutaciones
    map<IDenf,enfermedad> EnfDB; // Base de datos de enfermedades
    multimap<IDenf,set<mutacion>::iterator> IDenf_map; // Asocia enfermedad con mutaciones
};

#endif /*CLINVAR_H*/