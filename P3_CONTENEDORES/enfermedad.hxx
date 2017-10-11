
/**
  @brief Constructor por defecto de la clase enfermedad
  */
enfermedad::enfermedad(){
   this->name="";
   this->ID="";
   this->database="";
}

/** @brief Constructor alternativo de la clase enfermedad
	@param[in] name Nombre de la enfermedad
	@param[in] ID ID unico de la enfermedad
	@param[in] database Base de datos que provee este ID
	*/
enfermedad::enfermedad(const string & name, const string & ID, const string & database){
   this->name=name;
   this->ID=ID;
   this->database=database;
}

/** @brief Getter database
	@return this->database
	*/
string enfermedad::getDatabase() const{
   return database;
 }

 /** @brief Getter ID
	@return this->ID
	*/
string enfermedad::getID() const{
   return ID;
 }

 /** @brief Getter name
	@return this->name
	*/
string enfermedad::getName() const{
   return name;
 }

 /** @brief Setter name
   @param[in] name Nombre a establecer
	*/
void enfermedad::setName(const string& name){
   this->name= name;
 }

  /** @brief Setter ID
   @param[in] ID ID a establecer
	*/
void enfermedad::setID(const string& ID){
   this->ID= ID;
 }

 /** @brief Setter database
   @param[in] database database a establecer
	*/
void enfermedad::setDatabase(const string& database){
   this->database= database;
 }

 /** @brief Comprueba si la enfermedad corresponde al string que le pasamos
   @param[in] str Nombre de una enfermedad a comprobar
   @return true si la enfermedad contiene al nombre, false si lo contrario
	*/
bool enfermedad::nameContains(const string& str) const{
   if(this->name.find(str) != -1)
      return true;

   return false;
}

 /** @brief Asigna la enfermedad suministrada a la actual
   @param[in] e Nombre de la enfermedad a asignar
   @return *this Enfermedad actual copiada
	*/
enfermedad& enfermedad::operator=(const enfermedad& e){
   if(*this != e){
      this->setName(e.getName());
      this->setID(e.getID());
      this->setDatabase(e.getDatabase());
   }

   return *this;
}

 /** @brief Compara ID de la enfermedad con la pasada
   @param[in] e Nombre de la enfermedad a comparar
   @return True si es igual, false si no lo es
	*/
bool enfermedad::operator==(const enfermedad & e) const{
   return this->getID() == e.getID();
}

 /** @brief Compara ID de la enfermedad con la pasada
   @param[in] e Nombre de la enfermedad a comparar
   @return True si no es igual, false si lo es
	*/
bool enfermedad::operator!=(const enfermedad & e) const{
   return this->getID() != e.getID();
}

 /** @brief Compara si la enfermedad es menor que la pasada
   @param[in] e Nombre de la enfermedad a comparar
   @return True si es menor, false si no lo es
	*/
bool enfermedad::operator<(const enfermedad & e) const{   //Orden alfabético por campo name.
   return getName() < e.getName();
}

 /** @brief Imprime por el flujo pasado una enfermedad
   @param[in] e Nombre de la enfermedad a imprimir
   @param[out] os Objeto stream por el que imprimir la enfermedad
   @return Devuelve el flujo
	*/
ostream& operator<< (ostream& os, const enfermedad & e){
   // @todo implementa esta funcion

   os <<
   "Nombre: " << e.getName() << "\n" <<
   "ID: " << e.getID() << "\n" <<
   "DataBase: " << e.getDatabase() << "\n";

   return os;
 }



