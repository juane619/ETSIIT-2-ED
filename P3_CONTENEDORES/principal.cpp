#include "mutacion.h"
#include "enfermedad.h"
#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

	/** @brief lee un fichero de mutaciones, linea a linea
	@param[in] s nombre del fichero
  @param[in,out] conjuntoMutaciones objeto tipo conjunto sobre el que se almacenan las mutaciones
	@return true si la lectura ha sido correcta, false en caso contrario
	*/

bool load(conjunto &  conjuntoMutaciones, const string & s) {
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
        //cout << "leo:: "<< cadena << endl;
        // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
        mutacion mut = mutacion(cadena);
        // Insertar mutación en el conjunto
        conjuntoMutaciones.insert(mut);
        getline(fe,cadena,'\n');
    }
    //sort(conjuntoMutaciones.begin(), conjuntoMutaciones.end());
    fe.close();
    return true;
  } // else
  fe.close();
  return false;
 }


int main(int argc, char *argv[]){
    pair<conjunto::value_type,bool> busq_aux;
	conjunto conjuntoMutaciones;
    string query_str;
	//mutacion pr=mutacion("MT	15990	rs199474699	C	T	.	.	RS=199474699;RSPOS=15990;dbSNPBuildID=136;SSR=0;SAO=1;VP=0x050060000005000002110100;WGT=1;VC=SNV;PM;ASP;LSD;OM;CLNALLE=1;CLNHGVS=NC_012920.1:m.15990C>T;CLNSRC=OMIM_Allelic_Variant;CLNORIGIN=1;CLNSRCID=590075.0001;CLNSIG=5;CLNDSDB=MedGen;CLNDSDBID=C0026848;CLNDBN=Myopathy;CLNREVSTAT=no_criteria;CLNACC=RCV000010183.2");
    //mutacion pr2=mutacion("19	10984271	rs375884151	C	T	.	.	RS=375884151;RSPOS=10984271;dbSNPBuildID=138;SSR=0;SAO=0;VP=0x050000000305040026000100;GENEINFO=SMARCA4:6597;WGT=1;VC=SNV;REF;SYN;ASP;VLD;KGPhase3;CLNALLE=1;CLNHGVS=NC_000019.10:g.10984271C>T;CLNSRC=.;CLNORIGIN=1;CLNSRCID=.;CLNSIG=0|2;CLNDSDB=MedGen|MedGen:OMIM;CLNDSDBID=CN169374|C2750074:613325;CLNDBN=not_specified|Rhabdoid_tumor_predisposition_syndrome_2;CLNREVSTAT=single|single;CLNACC=RCV000192439.1|RCV000204385.1;CAF=0.998,0.001997;COMMON=1");
	//Cargar las mutaciones en vectorSNPs
    //if(conjuntoMutaciones.insert(pr))
    	//cout << "INSERTADA"<<endl;
    	
	//if(conjuntoMutaciones.insert(pr2))
    	//cout << "INSERTADA"<<endl;
	load(conjuntoMutaciones, "clinvar.vcf");

    //Imprimir número de elementos almacenados en conjuntoMutaciones
    cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<<conjuntoMutaciones.size()<<endl;
    
    mutacion x,y;

  x.setPos(0);
  x.setChr("1");
  
  y.setPos(0);
  y.setChr("MT");
  
  cout << "En rango "<< conjuntoMutaciones.lower_bound(y)-conjuntoMutaciones.lower_bound(x)<< "pos inicio "<< conjuntoMutaciones.lower_bound(x)-conjuntoMutaciones.begin() << " pos fin "<< conjuntoMutaciones.lower_bound(y)-conjuntoMutaciones.begin()<< endl;
    
	//cout << *conjuntoMutaciones.begin() << *(conjuntoMutaciones.end()-1) << "\n";
    
    cout << conjuntoMutaciones.lower_bound("2", 1)-conjuntoMutaciones.begin();
    	
    //cout << *conjuntoMutaciones.upper_bound("1", 1022260);
	//Imprimir cuántas mutaciones están asociadas al cromosoma 1:
    cout << "\nMutaciones asociadas a Chr 1: "<< conjuntoMutaciones.lower_bound("2", 1)-conjuntoMutaciones.begin()<< "\n\n";

    /**@todo ¿Existe la mutación con ID "rs147165522"? Imprimir la mutación y las enfermedades asociadas */
	cout << "Existe la mutacion con ID rs147165522?: \n";
	busq_aux= conjuntoMutaciones.find("rs147165522");
	if(busq_aux.second)
		cout << busq_aux.first;
	else
		cout << "No existe la mutacion.\n";

    /**@todo ¿Existe la mutación en chr/pos "14"/67769578? Imprimir la mutación y las enfermedades asociadas */
	cout << "Existe la mutacion chr/pos 14/67769578?: \n";
	busq_aux= conjuntoMutaciones.find("14", 67769578);
	if(busq_aux.second)
		cout << busq_aux.first;
	else
		cout << "No existe la mutacion.\n";

    /**@todo ¿Cómo podríamos calcular el número de mutaciones del cromosoma 3? (utiliza lower_bound / upper_bound) */
	cout << "\nMutaciones asociadas a Chr 3: "<< conjuntoMutaciones.lower_bound("4", 1)-conjuntoMutaciones.upper_bound("3", 1)<< "\n\n";

    /**@todo Analiza la eficiencia teórica y empírica de las operaciones find, insert y erase */

   return 0;
}
