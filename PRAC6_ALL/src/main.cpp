/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: juane
 *
 * Created on 21 de diciembre de 2016, 16:19
 */

#include <cstdlib>
#include <iostream>
#include "ClinVar.h"

using namespace std;

int main(int argc, char** argv) {
    ClinVar cl_prueba;
    
    //cl_prueba.load("C:/Users/juane/Escritorio/clinvar_20160831.vcf");
    cl_prueba.load("/home/juane/Escritorio/Enlace hacia Dropbox/2AGI/Estructuras de datos/PRACTICAS/PRACTICA6/prac6w/clinvar/datos/clinvar_20160831.vcf");
    cout << cl_prueba.countMut() << endl;
    
    cl_prueba.erase("rs672601312");
    /*OBTENER MUTACIONES ORDENADAS POR ID/POSICION*/
    for(ClinVar::iterator it=cl_prueba.begin(); it!= cl_prueba.end(); it++){
        cout << *it << "\n";
    }
    
    
    
    /*OBTENER MUTACIONES ORDENADAS POR GEN*/
    /*cout << cl_prueba.countGen() << endl;
    
    for(ClinVar::gen_iterator it_g=cl_prueba.gbegin(); it_g!= cl_prueba.gend(); it_g++){
        cout << *it_g << "\n";
    }
    
    /*ACCESO EFICIENTE A MUTACIONES POR ID*/
    /*cout << *cl_prueba.find_Mut("rs781514122");
    
    /*RECUPERAR MUTACIONES QUE AFECTAN A UN GEN*/
    /*set<IDmut> muts_gen= cl_prueba.getMutacionesGen("SLC25A22:79751");
    for(set<IDmut>::const_iterator s_it= muts_gen.begin(); s_it!=muts_gen.end(); s_it++)
        cout << *s_it << endl;
    
    /*Obtener las enfermedades que hay en la base de datos.*/
    /*for(ClinVar::enfermedad_iterator it_enf=cl_prueba.ebegin(); it_enf!= cl_prueba.eend(); it_enf++){
        cout << it_enf->second.getName() << "\n";
    }
    
    /*Dado un identiﬁcador de enfermedad, identiﬁcar las mutaciones que están asociadas con la enfermedad. Si
una enfermedad no dispone de identiﬁcador, puede ser ignorada.*/
    /*set<IDmut> muts_enf= cl_prueba.getMutacionesEnf("C0270855:609304:1935:44423001");
    for(set<IDmut>::const_iterator s_it= muts_enf.begin(); s_it!=muts_enf.end(); s_it++)
        cout << *s_it << endl;
    
    /*Consultar todas las enfermedades que contienen un determinado término en su nombre (por ejemplo, "can-
cer" o "prostate_cancer").*/
    /*list<IDenf> l_enf= cl_prueba.getEnfermedades("Mental_retardation");
    for(list<IDenf>::iterator it=l_enf.begin(); it!=l_enf.end(); it++)
        cout << *it << endl;
    
    /* Obtener enfermedades asociadas a una mutacion*/
    /*vector<enfermedad> enf_asociadas;
    string m="22	28694073	rs540635787	G	A	.	.	RS=540635787;RSPOS=28694073;dbSNPBuildID=142;SSR=0;SAO=1;VP=0x050060000a05000026100100;GENEINFO=CHEK2:11200;WGT=1;VC=SNV;PM;NSM;REF;ASP;KGPhase3;LSD;CLNALLE=1,-1;CLNHGVS=NC_000022.11:g.28694073G>A,NC_000022.11:g.28694073G>T;CLNSRC=.,.;CLNORIGIN=1,1;CLNSRCID=.,.;CLNSIG=0|0|0|4|4|4|4,0|0;CLNDSDB=MedGen:SNOMED_CT|MedGen:OMIM:SNOMED_CT|MedGen|MedGen:OMIM:SNOMED_CT|MedGen:OMIM:SNOMED_CT|MedGen:OMIM:SNOMED_CT|MedGen:OMIM:SNOMED_CT,MedGen|MedGen:OMIM:ORPHA;CLNDSDBID=C0027672:699346009|C0346153:114480:254843006|CN169374|C0699790:114500:269533000|C0346153:114480:254843006|C0684249:211980:187875007|C0376358:176807:399068003,CN169374|C3280492:614327:289539;CLNDBN=Hereditary_cancer-predisposing_syndrome|Familial_cancer_of_breast|not_specified|Carcinoma_of_colon|Familial_cancer_of_breast|Lung_cancer|Malignant_tumor_of_prostate,not_specified|Tumor_susceptibility_linked_to_germline_BAP1_mutations;CLNREVSTAT=single|single|single|no_criteria|no_criteria|no_criteria|no_criteria,single|single;CLNACC=RCV000115999.5|RCV000206044.2|RCV000212462.1|RCV000234795.1|RCV000234795.1|RCV000234795.1|RCV000234795.1,RCV000213121.1|RCV000219946.1;CAF=0.9998,0.0001997;COMMON=0";
    mutacion mut_p=m;
    enf_asociadas= cl_prueba.getEnfermedades(mut_p);
    
    for(int i=0; i<enf_asociadas.size(); i++)
        cout << enf_asociadas.at(i).getName() << endl;
    */
    
    /*Dado un determinado término para el nombre de una enfermedad (ejemplo, "cancer" o "prostate_cancer"),
obtener la secuencia ordenada de las K mutaciones que con mayor probabilidad estan relacionadas (son
causantes) de la misma.*/
    /*
    set<mutacion,ProbMutaciones> set_prob=cl_prueba.topKMutaciones(10, "not_specified");
    for(set<mutacion,ProbMutaciones>::const_iterator set_p_it= set_prob.begin(); set_p_it!=set_prob.end(); set_p_it++)
        cout << *set_p_it << endl;
    */
    return 0;
}

