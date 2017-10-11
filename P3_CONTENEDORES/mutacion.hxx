/** @brief fichero de implementacion de la clase mutacion
/** @brief fichero de implementacion de la clase mutacion

*/

 /** @brief Constructor por defecto de la clase mutación
 */
mutacion::mutacion(){
   this->ID="";
   this->chr="";
   this->pos=0;
   this->common=false;
}

/**
  @brief Constructor copia, recibe una mutación y se copia de esta
  @param[in] m Mutacion a copiar
  */
mutacion::mutacion(const mutacion& m){
   this->ID=m.ID;
   this->chr=m.chr;
   this->pos=m.pos;
   this->common=m.common;
   this->ref_alt=m.ref_alt;
   this->genes=m.genes;
   this->caf= m.caf;
   this->enfermedades= m.enfermedades;
   this->clnsig= m.clnsig;
}

/** @brief Constructor alternativo: recibe un string del cual obtiene toda la informacion de la mutacion.
  @param[in] str Cadena de texto de la que sacar mutacion.
  */
mutacion::mutacion(const string& str){
   int pos_i=0, pos_f=0, aux_int=0, i=0;
   string aux_str, aux_str2;
   float fl;

   /*Numero de cromosoma*/
   pos_f= str.find('\t');

   aux_str= str.substr(0, pos_f);
   this->chr= aux_str;

   /*Posicion*/
   pos_i= pos_f+1;
   pos_f= str.find('\t', pos_i);
   aux_int= atoi(str.substr(pos_i, pos_f-pos_i).c_str());
   this->pos=aux_int;

   /*ID*/
   pos_i= pos_f+1;
   pos_f= str.find('\t', pos_i);
   aux_str= str.substr(pos_i, pos_f-pos_i);
   this->ID= aux_str;

   /*REF*/
   pos_i= pos_f+1;
   pos_f= str.find('\t', pos_i);
   aux_str= str.substr(pos_i, pos_f-pos_i);
   mutacion::ref_alt.push_back(aux_str);

   /*ALT*/
   pos_i= pos_f+1;
   pos_f= str.find('\t', pos_i);
   aux_str= str.substr(pos_i, pos_f-pos_i);

   //separamos posibles campos de alt
   pos_f= aux_str.find(',', 0);
   if(pos_f != -1){
      pos_i= 0;
      do{
         aux_str2= aux_str.substr(pos_i, pos_f-pos_i);
         pos_i= pos_f+1;
         this->ref_alt.push_back(aux_str2);
         pos_f= aux_str.find(',', pos_i);
      }while(pos_f != -1);

      aux_str2= aux_str.substr(pos_i, aux_str.size()-pos_i);
      this->ref_alt.push_back(aux_str2);
   }
   else{
      aux_str2= aux_str.substr(0, aux_str.size());
      this->ref_alt.push_back(aux_str2);
   }

   /*INFORMACION ADICIONAL DE CADA MUTACION*/
   /*GENES*/
   pos_i= pos_f+1;
   pos_i= str.find("GENEINFO=");
   if(pos_i!=-1){
      pos_i+=9;
      pos_f= str.find(';', pos_i);
      aux_str= str.substr(pos_i, pos_f-pos_i);
   }
   else
      aux_str= "";

   //FALTA AÑADIR AL VECTOR DE STRING CORRECTAMENTE
   mutacion::genes.push_back(aux_str);
//cout << aux_str << endl;

   /*CAF*/
   pos_i= str.find("CAF=");
   if(pos_i!=-1){
      pos_i+=4;
      pos_f= str.find(';', pos_i);
      aux_str= str.substr(pos_i, pos_f+1-pos_i);
   }
   else
      aux_str= "";

   //Separamos los posibles campos de caf
   if(!aux_str.empty()){
      pos_f= aux_str.find(',', 0);  //Obtendrá siempre una separacion por coma

      pos_i=0;
      do{
         aux_str2= aux_str.substr(pos_i, pos_f);
         pos_i= pos_f+1;
         fl=strtof(aux_str2.c_str(), 0);
         this->caf.push_back(fl);
         pos_f= aux_str.find(',', pos_i);
      }while(pos_f != -1);

      aux_str2= aux_str.substr(pos_i, aux_str.size()-1);
      fl=strtof(aux_str2.c_str(), 0);
      this->caf.push_back(fl);
   }

   /*COMMON*/
pos_i= str.find("COMMON=");
   if(pos_i!=-1){
      pos_i+=7;
      aux_str= str.substr(pos_i, 1);
      mutacion::common=aux_str.c_str();
   }
   else
      mutacion::common= false;

   /*ENFERMEDADES*/
   /*Dentro de la clase mutacion todavia, almacenamos en el vector clnsig*/
   pos_i= str.find("CLNSIG=")+7;
   pos_f= str.find(';', pos_i);
   aux_str= str.substr(pos_i, pos_f-pos_i);

   //Separamos todos los campos posibles de clnsig y los metemos en el vector

   pos_f= aux_str.find('|', 0);
   if(pos_f == -1)
      pos_f= aux_str.find(',', 0);
   if(pos_f != -1){
      pos_i=0;
      do{
         aux_str2= aux_str.substr(pos_i, pos_f);
         pos_i= pos_f+1;
         aux_int=atoi(aux_str2.c_str());
         this->clnsig.push_back(aux_int);
         pos_f= aux_str.find('|', pos_i);
         if(pos_f == -1)
            pos_f= aux_str.find(',', pos_i);
      }while(pos_f != -1);

      aux_str2= aux_str.substr(pos_i, aux_str.size());
      aux_int=atoi(aux_str2.c_str());
      this->clnsig.push_back(aux_int);
   }
   else{
      aux_int=atoi(aux_str.c_str());
      this->clnsig.push_back(aux_int);
   }

   enfermedad aux_e;   //creamos enfermedad auxiliar

   //Nombre de la enfermedad//
   pos_i= str.find("CLNDBN=")+7;
   pos_f= str.find(';', pos_i);
   aux_str= str.substr(pos_i, pos_f-pos_i);

   //separamos cada posible campo de clndbn(nombre enfermedad)
   pos_f= aux_str.find('|', 0);
   if(pos_f == -1)
      pos_f= aux_str.find(',', 0);
   if(pos_f != -1){
      pos_i=0;
      do{
         aux_str2= aux_str.substr(pos_i, pos_f-pos_i);
         pos_i= pos_f+1;
         aux_e.setName(aux_str2);
         this->enfermedades.push_back(aux_e);
         pos_f= aux_str.find('|', pos_i);
         if(pos_f == -1)
            pos_f= aux_str.find(',', pos_i);
      }while(pos_f != -1);

      aux_str2= aux_str.substr(pos_i, aux_str.size());
      aux_e.setName(aux_str2);
      this->enfermedades.push_back(aux_e);
   }
   else{
      aux_e.setName(aux_str);
      this->enfermedades.push_back(aux_e);
   }

   //Tenemos ya el nº de enfermedades con sus nombres en el vector, falta añadir sus ID y sus bases de datos.///

   //ID de la enfermedad//
   pos_i= str.find("CLNDSDBID=")+10;
   pos_f= str.find(';', pos_i);
   aux_str= str.substr(pos_i, pos_f-pos_i);

   pos_f= aux_str.find('|', 0);
   if(pos_f == -1)
      pos_f= aux_str.find(',', 0);
   if(pos_f != -1){
      pos_i=0;
      for(i=0; i<this->enfermedades.size()-1 && pos_f != -1; i++){
         aux_str2= aux_str.substr(pos_i, pos_f-pos_i);
         pos_i= pos_f+1;
         enfermedades[i].setID(aux_str2);
         pos_f= aux_str.find('|', pos_i);
         if(pos_f == -1)
            pos_f= aux_str.find(',', pos_i);
      }
      aux_str2= aux_str.substr(pos_i, aux_str.size());
      enfermedades[i].setID(aux_str2);
   }
   else
      enfermedades[0].setID(aux_str);


   //Base de datos de la enfermedad//
   pos_i= str.find("CLNDSDB=")+8;
   pos_f= str.find(';', pos_i);
   aux_str= str.substr(pos_i, pos_f-pos_i);

   pos_f= aux_str.find('|', 0);
   if(pos_f == -1)
      pos_f= aux_str.find(',', 0);
   if(pos_f != -1){
      pos_i=0;
      for(i=0; i<this->enfermedades.size()-1 && pos_f != -1; i++){
         aux_str2= aux_str.substr(pos_i, pos_f-pos_i);
         pos_i= pos_f+1;
         enfermedades[i].setDatabase(aux_str2);
         pos_f= aux_str.find('|', pos_i);
         if(pos_f == -1)
            pos_f= aux_str.find(',', pos_i);
      }
      aux_str2= aux_str.substr(pos_i, aux_str.size());
      enfermedades[i].setDatabase(aux_str2);
   }
   else
      enfermedades[0].setDatabase(aux_str);
}

/** @brief Sobrecarga del operador de salida: imprime por el flujo pasado una mutacion con toda su informacion.
   @param[out] os Descriptor del flujo de salida
   @param[in] m Mutacion a imprimir
   @return Devuelve el flujo de salida
  */
ostream& operator<< (ostream& os, const mutacion& m){
   int i;
   vector<string> aux_str;
   vector<float> aux_float;
   vector<int> aux_int;
   vector<enfermedad> aux_enf;

   os << "Nº cromosoma: " << m.getChr() <<endl <<   //imprimir cromosoma
   "Posicion: "<< m.getPos() << endl<<       //imprimir posicion
   "ID: "<< m.getID() << endl <<             //imprimir ID

   //imprimir el vector ref_alt
   "ref_alt: "<< endl;
   aux_str= m.getRef_alt();

   os << "[";
   for(i=0; i<aux_str.size(); i++){
      os << aux_str[i];
      if(i+1!=aux_str.size())
         os << ", ";
   }
   os << "]\n";

   //imprimir genes
   os << "genes:\n";
   aux_str= m.getGenes();

   os << "[";
   for(i=0; i<aux_str.size(); i++){
      os << aux_str[i];
      if(i+1!=aux_str.size())
         os << ", ";
   }
   os << "]\n";

   //imprimir caf
   os << "caf:\n";
   aux_float= m.getCaf();

   os << "[";
   for(i=0; i<aux_float.size(); i++){
      os << aux_float[i];
      if(i+1!=aux_float.size())
         os << ", ";
   }
   os << "]\n";

   os << "Comun: "<< m.getCommon() << endl;   //Imprimir common

   //imprimir clnsig
   os <<"clnsig: "<< endl;
   aux_int= m.getClnsig();

   os << "[";
   for(i=0; i<aux_int.size(); i++){
      os << aux_int[i];
      if(i+1!=aux_int.size())
         os << ", ";
   }
   os << "]\n";

   //imprimir enfermedades
   os <<"Enfermedades: \n";
   aux_enf= m.getEnfermedades();
   os << "[";
   for(i=0; i<aux_enf.size(); i++){
      os << aux_enf[i];
      if(i+1!=aux_enf.size())
         os << ", ";
   }
   os << "]\n\n\n";

   return os;
}

/** @brief Sobrecarga del operador ==
  *@param[in] m Mutacion a comparar
  * @return True si son iguales, false si no lo son
  */
bool mutacion::operator==(const mutacion& m){
   return getID() == m.getID();
}


/** @brief Sobrecarga operador =
  *  @param[in] m Mutacion a asignar
  * @return this
  */
mutacion& mutacion::operator=(const mutacion& m){
   if(!(*this == m)){
      this->setID(m.getID());
      this->setChr(m.getChr());
      this->setPos(m.getPos());
      this->setRef_alt(m.getRef_alt());
      this->setGenes(m.getGenes());
      this->setCommon(m.getCommon());
      this->setCaf(m.getCaf());
      this->setEnfermedades(m.getEnfermedades());
      this->setClnsig(m.getClnsig());
   }
   return *this;
}


  /**
  @brief Sobrecarga del operador <: compara el campo chr de cada mutacion siendo los numeros menores que las cadenas
  y las cadenas de un caracter menores que las de dos. Si tienen el mismo cromosoma comparamos las dos posiciones.

@param[in]  m objeto mutación
  @return true en caso de ser menor a la pasada, false en caso contrario
	*/
bool mutacion::operator<(const mutacion & m) const{
  ///El orden viene determinado por Chr y pos. El primer criterio es el número de cromosoma. El orden para el número de cromosoma se rige por "1"<"2"<"3"<->->-><"22"<"X"<"Y"<"MT". Dos mutaciones del mismo cromosoma deben ordenarse según su posición, de menor posición a mayor (orden natural de enteros)->
  if(getChr()=="MT"){             //en caso de que sea MT
      if(m.getChr()!="MT")
         return false;
  }
  else if(getChr()>="X"){           //en caso de que sea X, Y
     //cout << getChr() << "\n";
     if(m.getChr()=="MT")       //si el que comparamos es MT, es menor el this
        return true;
     else if(m.getChr()!=getChr())
        return getChr()<m.getChr();
  }
  else{                          //en caso de que sea numero
      if(m.getChr()>="MT"){
         //cout << m.getChr() << "\n";
         return true;
      }
      else{
            //cout << m.getChr() << "\n";
        if(atoi(getChr().c_str())!=atoi(m.getChr().c_str()))
            return atoi(getChr().c_str())<atoi(m.getChr().c_str());
        }
  }

   return getPos() < m.getPos();
}

/** @brief Getter ID
  *sort(this->vm.begin(), this->vm.end());
  * @return ID
  */
string mutacion::getID() const
{
   return ID;
}


/** @brief Getter vector clnsig
  *
  * @return Vector int clnsig
  */
const vector<int>& mutacion::getClnsig() const
{
   return clnsig;
}

/** @brief Getter vector enfermedades
  *
  * @return Vector enfermedad enfermedades
  */
const vector<enfermedad>& mutacion::getEnfermedades() const
{
   return enfermedades;
}

/** @brief Getter vector caf
  *
  * @return Vector float caf
  */
const vector<float>& mutacion::getCaf() const
{
   return caf;
}

/** @brief Getter comun
  *
  * @return True si es comun, false si no lo es
  */
bool mutacion::getCommon() const
{
   return common;
}

/** @brief Getter genes
  *
  * @return Vector string genes
  */
const vector<string>& mutacion::getGenes() const
{
   return genes;
}

/** @brief Getter vector ref_alt
  *
  * @return Vector string ref_alt
  */
const vector<string>& mutacion::getRef_alt() const
{
   return ref_alt;

}

/** @brief Getter posicion
  *
  * @return Posicion en el cromosoma
  */
unsigned int mutacion::getPos() const
{
   return pos;
}

/** @brief Getter chr
  *
  * @return Nombre del cromosoma
  */
string mutacion::getChr() const
{
   return chr;
}


/** @brief Setter clnsig
  *@param[in] clnsig Vector de int a establecer
  */
void mutacion::setClnsig(const std::vector<int>& clnsig)
{
   this->clnsig= clnsig;
}

/** @brief Setter enfermedades
  *@param[in] enfermedades Vector de enfermedades a establecer
  */
void mutacion::setEnfermedades(const std::vector<enfermedad>& enfermedades)
{
   this->enfermedades= enfermedades;
}

/** @brief Setter cad
  *@param[in] caf Vector de float a establecer
  */
void mutacion::setCaf(const std::vector<float>& caf)
{
   this->caf= caf;
}

/** @brief Setter common
  *@param[in] common Bool a establecer
  */
void mutacion::setCommon(const bool& common)
{
   this->common= common;
}

/** @brief Setter genes
  *@param[in] genes Vector de string a establecer
  */
void mutacion::setGenes(const std::vector<string>& genes)
{
   this->genes= genes;
}

/** @brief Setter ref_alt
  *@param[in] ref_alt Vector de string a establecer
  */
void mutacion::setRef_alt(const std::vector<string>& ref_alt)
{
   this->ref_alt= ref_alt;
}

/** @brief Setter posicion
  *@param[in] pos Posicion a establecer
  */
void mutacion::setPos(const unsigned int& pos)
{

   this->pos= pos;
}

/** @brief Setter cromosoma
  *@param[in] chr Cromosoma a establecer
  */
void mutacion::setChr(const string& chr)
{
   this->chr= chr;
}

/** @brief Setter ID
  *@param[in] id ID unico a establecer
  */
void mutacion::setID(const string& id)
{
 this->ID= id;
}








