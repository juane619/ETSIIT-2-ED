#include "mutacion.h"
#include "enfermedad.h"
#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <functional>

using namespace std;

	/** @brief lee un fichero de mutaciones, linea a linea
	@param[in] s nombre del fichero
  @param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
	@return true si la lectura ha sido correcta, false en caso contrario
	*/
template <typename T, typename CMP>
bool load(conjunto<T, CMP > &cm, const string & s) {
 ifstream fe;
 string cadena;

 cout << "Abrimos "<< s << endl;
 fe.open(s.c_str(), ifstream::in);
 if (fe.fail()){
   cerr << "Error al abrir el fichero " << s << endl;
 }
 else {
    //leo la cabecera del fichero (líneas que comienzan con #)
    do{
      getline(fe,cadena,'\n');
    }while (cadena.find("#")==0 && !fe.eof());

    //leo la tabla de mutaciones, una línea cada vez
    while ( !fe.eof()){
        // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
        mutacion mut = mutacion(cadena);
        // Insertar mutación en el conjunto
        cm.insert(mut);
        getline(fe,cadena,'\n');
    }
    //sort(cm.begin(), cm.end());
    fe.close();
    return true;
  } // else
  fe.close();
  return false;
 }


int main(int argc, char *argv[]){
    /*
    conjunto<mutacion,less<mutacion> >::iterator it;
    conjunto<mutacion,less<mutacion> > conjuntoMutacionesCre;
    load(conjuntoMutacionesCre, "clinvar.vcf");
     cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<<conjuntoMutacionesCre.size()<<endl;
     
     for(it=conjuntoMutacionesCre.begin(); it!=conjuntoMutacionesCre.end(); it++)
        cout << *it << "\n";
    */
    /*
    conjunto<mutacion,greater<mutacion> >::iterator it;
    conjunto<mutacion,greater<mutacion> > conjuntoMutacionesDec;
    load(conjuntoMutacionesDec, "clinvar.vcf");
    cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<<conjuntoMutacionesDec.size()<<endl;
    
    for(it=conjuntoMutacionesDec.begin(); it!=conjuntoMutacionesDec.end(); it++)
        cout << *it << "\n";
    */
    /*
    conjunto<enfermedad,greater<enfermedad> >::iterator it;
    conjunto<enfermedad,greater<enfermedad> > conjuntoEnfermedadDec;
    
    string prueba_enfermedades= "1	1806503	rs752746786	A	G	.	.	RS=752746786;RSPOS=1806503;dbSNPBuildID=144;SSR=0;SAO=0;VP=0x050000400a05000002000100;GENEINFO=GNB1:2782;WGT=1;VC=SNV;NSM;REF;U5;ASP;CLNALLE=1,-1;CLNHGVS=NC_000001.11:g.1806503A>G,NC_000001.11:g.1806503A>T;CLNSRC=OMIM_Allelic_Variant,OMIM_Allelic_Variant;CLNORIGIN=35,34;CLNSRCID=139380.0002,139380.0003;CLNSIG=0|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5,5|5|5|5|5|5|5|5|5|5|5|5|5;CLNDSDB=MedGen|MedGen:Orphanet|MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|MedGen:OMIM|MedGen:OMIM,Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|MedGen:OMIM|Gene:MedGen:OMIM:SNOMED_CT;CLNDSDBID=C0950123|C0008925:ORPHA2014|C0013421|HP:0001510:CN001379|HP:0000821:C2750951|HP:0009062:C1970931|HP:0001249:C1843367|HP:0200049:CN117790|HP:0002376:C1836830|HP:0011198:CN166927|HP:0002474:C1847610|HP:0001508:C0231246|HP:0001263:CN001157|HP:0001510:CN001379|HP:0002540:C0560046|HP:0002509:C1838391|HP:0010841:CN116575|HP:0001252:CN001147|HP:0000639:C1963184|HP:0001250:C1959629|HP:0000486:C0038379|CN236792:616973|C0026986:614286,HP:0100704:CN117595|HP:0001508:C0231246|HP:0011968:C0232466|HP:0002384:CN002165|HP:0001263:CN001157|HP:0001510:CN001379|HP:0008947:CN007871|HP:0002509:C1838391|HP:0010841:CN116575|HP:0001252:CN001147|HP:0001250:C1959629|CN236792:616973|100310785:C0023449:613065:91857003;CLNDBN=Inborn_genetic_diseases|Cleft_palate|Dystonia|Growth_delay|Hypothyroidism|Infantile_axial_hypotonia|Intellectual_disability|Upper_limb_hypertonia|Developmental_regression|EEG_with_generalized_epileptiform_discharges|Expressive_language_delay|Failure_to_thrive|Global_developmental_delay|Growth_delay|Inability_to_walk|Limb_hypertonia|Multifocal_epileptiform_discharges|Muscular_hypotonia|Nystagmus|Seizures|Strabismus|Mental_retardation\x2c_autosomal_dominant_42|Myelodysplastic_syndrome,Cortical_visual_impairment|Failure_to_thrive|Feeding_difficulties|Focal_seizures_with_impairment_of_consciousness_or_awareness|Global_developmental_delay|Growth_delay|Infantile_muscular_hypotonia|Limb_hypertonia|Multifocal_epileptiform_discharges|Muscular_hypotonia|Seizures|Mental_retardation\x2c_autosomal_dominant_42|Acute_lymphoid_leukemia;CLNREVSTAT=single|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria,no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria;CLNACC=RCV000190738.1|RCV000208571.1|RCV000208571.1|RCV000208571.1|RCV000208571.1|RCV000208571.1|RCV000208571.1|RCV000208571.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000225179.2|RCV000225295.2,RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000225195.2|RCV000225283.2";
    mutacion prueba=mutacion(prueba_enfermedades);
    vector<enfermedad> enfermedades= prueba.getEnfermedades();
    
    for(int i=0; i<enfermedades.size(); i++)
         conjuntoEnfermedadDec.insert(enfermedades[i]);
    
     for(it=conjuntoEnfermedadDec.begin(); it!=conjuntoEnfermedadDec.end(); it++)
        cout << *it << "\n";
    */
    /*
    conjunto<enfermedad,less<enfermedad> >::iterator it;
    conjunto<enfermedad,less<enfermedad> > conjuntoEnfermedadCre;
    
    string prueba_enfermedades= "1	1806503	rs752746786	A	G	.	.	RS=752746786;RSPOS=1806503;dbSNPBuildID=144;SSR=0;SAO=0;VP=0x050000400a05000002000100;GENEINFO=GNB1:2782;WGT=1;VC=SNV;NSM;REF;U5;ASP;CLNALLE=1,-1;CLNHGVS=NC_000001.11:g.1806503A>G,NC_000001.11:g.1806503A>T;CLNSRC=OMIM_Allelic_Variant,OMIM_Allelic_Variant;CLNORIGIN=35,34;CLNSRCID=139380.0002,139380.0003;CLNSIG=0|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5|5,5|5|5|5|5|5|5|5|5|5|5|5|5;CLNDSDB=MedGen|MedGen:Orphanet|MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|MedGen:OMIM|MedGen:OMIM,Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|MedGen:OMIM|Gene:MedGen:OMIM:SNOMED_CT;CLNDSDBID=C0950123|C0008925:ORPHA2014|C0013421|HP:0001510:CN001379|HP:0000821:C2750951|HP:0009062:C1970931|HP:0001249:C1843367|HP:0200049:CN117790|HP:0002376:C1836830|HP:0011198:CN166927|HP:0002474:C1847610|HP:0001508:C0231246|HP:0001263:CN001157|HP:0001510:CN001379|HP:0002540:C0560046|HP:0002509:C1838391|HP:0010841:CN116575|HP:0001252:CN001147|HP:0000639:C1963184|HP:0001250:C1959629|HP:0000486:C0038379|CN236792:616973|C0026986:614286,HP:0100704:CN117595|HP:0001508:C0231246|HP:0011968:C0232466|HP:0002384:CN002165|HP:0001263:CN001157|HP:0001510:CN001379|HP:0008947:CN007871|HP:0002509:C1838391|HP:0010841:CN116575|HP:0001252:CN001147|HP:0001250:C1959629|CN236792:616973|100310785:C0023449:613065:91857003;CLNDBN=Inborn_genetic_diseases|Cleft_palate|Dystonia|Growth_delay|Hypothyroidism|Infantile_axial_hypotonia|Intellectual_disability|Upper_limb_hypertonia|Developmental_regression|EEG_with_generalized_epileptiform_discharges|Expressive_language_delay|Failure_to_thrive|Global_developmental_delay|Growth_delay|Inability_to_walk|Limb_hypertonia|Multifocal_epileptiform_discharges|Muscular_hypotonia|Nystagmus|Seizures|Strabismus|Mental_retardation\x2c_autosomal_dominant_42|Myelodysplastic_syndrome,Cortical_visual_impairment|Failure_to_thrive|Feeding_difficulties|Focal_seizures_with_impairment_of_consciousness_or_awareness|Global_developmental_delay|Growth_delay|Infantile_muscular_hypotonia|Limb_hypertonia|Multifocal_epileptiform_discharges|Muscular_hypotonia|Seizures|Mental_retardation\x2c_autosomal_dominant_42|Acute_lymphoid_leukemia;CLNREVSTAT=single|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria,no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria;CLNACC=RCV000190738.1|RCV000208571.1|RCV000208571.1|RCV000208571.1|RCV000208571.1|RCV000208571.1|RCV000208571.1|RCV000208571.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000210259.1|RCV000225179.2|RCV000225295.2,RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000210280.1|RCV000225195.2|RCV000225283.2";
    mutacion prueba=mutacion(prueba_enfermedades);
    vector<enfermedad> enfermedades= prueba.getEnfermedades();
    
    for(int i=0; i<enfermedades.size(); i++)
         conjuntoEnfermedadCre.insert(enfermedades[i]);
    
     for(it=conjuntoEnfermedadCre.begin(); it!=conjuntoEnfermedadCre.end(); it++)
        cout << *it << "\n";
    */
    /*
    conjunto<mutacion,ComparacionPorIDCre >::iterator it;
    conjunto<mutacion,ComparacionPorIDCre> conjuntoMutacionesIDCre;
    load(conjuntoMutacionesIDCre, "clinvar.vcf");
    cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<<conjuntoMutacionesIDCre.size()<<endl;
    
        for(it=conjuntoMutacionesIDCre.begin(); it!=conjuntoMutacionesIDCre.end(); it++)
        cout << *it << "\n";
    */
    
    conjunto<mutacion,ComparacionPorIDDec >::iterator it;
    conjunto<mutacion,ComparacionPorIDDec > conjuntoMutacionesIDDec;
    load(conjuntoMutacionesIDDec, "clinvar.vcf");
    cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<<conjuntoMutacionesIDDec.size()<<endl;
    
    for(it=conjuntoMutacionesIDDec.begin(); it!=conjuntoMutacionesIDDec.end(); it++)
        cout << *it << "\n";
    
    
   
   return 0;
}
