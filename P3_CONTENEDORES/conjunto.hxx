/** @brief fichero de implementacion de la clase conjunto

*/

conjunto::conjunto(){

}

//CONSTRUCTOR COPIA
conjunto::conjunto(const conjunto& con){
   this->vm= con.vm;
   //size_type= con.size_type;
   //this->value_type= con.value_type;
}


//METODOS FIND
pair<conjunto::value_type,bool>  conjunto::find (const str & chr, const unsigned int & pos) const{
  pair<conjunto::value_type,bool> par;
  mutacion m;
  par.first = m;
  par.second = false;

  for(conjunto::const_iterator it = this->cbegin(); it < this->cend(); it++)
    if(it->getChr() == chr && it->getPos() == pos){
      par.first = *it;
      par.second = true;
    }

  return par;
}

pair<conjunto::value_type,bool>  conjunto::find (const str & ID) const{
  pair<conjunto::value_type,bool> par;
  mutacion m;
  par.first = m;
  par.second = false;

  for(conjunto::const_iterator it = this->cbegin(); it < this->cend(); it++)
    if(it->getID() == ID){
      par.first = *it;
      par.second = true;
    }

  return par;
}

pair<conjunto::value_type,bool>  conjunto::find (const conjunto::value_type & e) const{
  pair<conjunto::value_type,bool> par;
  par.first = e;
  par.second = false;

  for(conjunto::const_iterator it = this->cbegin(); it < this->cend(); it++)
    if(it->getID() == e.getID()){
      par.first = *it;
      par.second = true;
    }

  return par;
}

//METODOS COUNT
conjunto::size_type conjunto::count (const str & chr, const unsigned int & pos) const{
  for(conjunto::const_iterator it = this->cbegin(); it < this->cend(); it++)
    if(it->getChr() == chr && it->getPos() == pos)
      return true;

  return false;
}

conjunto::size_type conjunto::count (const str & ID) const{
   for(conjunto::const_iterator it = this->cbegin(); it < this->cend(); it++)
    if(it->getID() == ID)
      return 1;

   return 0;
}

conjunto::size_type conjunto::count (const conjunto::value_type & e) const{
  for(conjunto::const_iterator it = this->cbegin(); it < this->cend(); it++)
    if(it->getID() == e.getID())
      return 1;

 return 0;
}

//METODO INSERT
bool conjunto::insert(const conjunto::value_type & e){
    conjunto::const_iterator it=this->begin();

        if(this->size()>0){
            if(binary_search(this->begin(), this->end(), e) ){
                mutacion m(e);
                it= this->lower_bound(e);
                if(it->getID()==e.getID()){
                    cout << "REPETIDA!\n";
					return 0;
            	}
            }
            if(e<*(this->vm.end()-1)){
                it= this->lower_bound(e);
                this->vm.insert(it, e);
            }
            else{
                this->vm.insert(this->end(), e);
            }
        }
        else
            this->vm.insert(it, e);

    return true;
}

//METODOS ERASE
bool conjunto::erase(const str & chr, const unsigned int & pos){
  bool encontrado = false;
  for(conjunto::iterator it = this->begin(); it < this->end() && !encontrado; it++)
    if(it->getChr() == chr && it->getPos() == pos){
      this->vm.erase(it);
      return 1;
    }

    return 0;
}

bool conjunto::erase(const string & ID){
  bool encontrado = false;
  for(conjunto::iterator it = this->begin(); it <= this->end() && !encontrado; it++)
    if(it->getID() == ID){
      vm.erase(it);
      return 1;
    }

    return 0;
}

bool conjunto::erase(const conjunto::value_type & e){
  bool encontrado = false;

  for(conjunto::iterator it = this->begin(); it <= this->end() && !encontrado; it++)
    if(it->getID() == e.getID()){
      vm.erase(it);
      return 1;
    }

    return 0;
}

//METODO CLEAR
void conjunto::clear(){
   vm.clear();
}

//METODO SIZE
conjunto::size_type conjunto::size() const{
   return this->vm.size();
}


//METODO EMPTY
bool conjunto::empty() const{
   return !vm.size();
}

//FALTA OPERATOR =
conjunto& conjunto::operator=(const conjunto & org){
        conjunto c_aux;
        c_aux.vm= org.vm;
        return c_aux;
}

//METODO BEGIN
conjunto::iterator conjunto::begin(){
   return this->vm.begin();
}

//METODO CBEGIN
conjunto::const_iterator conjunto::cbegin() const{
   return this->vm.cbegin();
}

//METODO END
conjunto::iterator conjunto::end(){
   return vm.end();
}

//METODO CEND
conjunto::const_iterator conjunto::cend() const{
   return vm.cend();
}

//METODOS LOWER_BOUND
conjunto::const_iterator conjunto::lower_bound (const str & chr, const unsigned int & pos) const{
    conjunto::const_iterator it;
    mutacion m_aux;
    m_aux.setChr(chr);
    m_aux.setPos(pos);

    for(it=this->cbegin(); it!=this->cend(); it++){
        //cout << *it;
        if(!(*it<m_aux))
            return it;
    }
    return this->cend()-1;
}

conjunto::const_iterator conjunto::lower_bound (const conjunto::value_type & e) const{
    conjunto::const_iterator it;

    for(it=this->cbegin(); it!=this->cend(); it++){
        //cout << *it;
        if(!(*it<e))
            return it;
    }
    return this->vm.cend()-1;
}


//METODOS UPPER BOUND
conjunto::const_iterator conjunto::upper_bound (const str & chr, const unsigned int & pos) const{
    conjunto::const_iterator it;
    mutacion m_aux;
    m_aux.setChr(chr);
    m_aux.setPos(pos);

    for(it=this->cbegin(); it!=this->cend(); it++){
        //cout << *it;
        if(m_aux<*it)
            return it;
    }
    return this->vm.cend();
}

conjunto::const_iterator conjunto::upper_bound (const conjunto::value_type & e) const{
    conjunto::const_iterator it;

    for(it=this->cbegin(); it!=this->cend(); it++){
        //cout << *it;
        if(e<*it)
            return it;
    }
    return this->vm.cend();
}

//INVARIANTE DE REPRESENTACION
bool conjunto::cheq_rep() const{
  int i,j;
  bool encontrado=false;
  vector<string> val_chr={"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "X", "Y", "MT"};

  //Buscamos si el cromosoma coincide con alguno de los validos y si la posicion es mayor de cero
  for(i=0; i<vm.size(); i++){
      mutacion m_aux=vm[i];
      for(j=0; j<val_chr.size() && !encontrado; j++){
         if(m_aux.getChr()==val_chr[j])
            encontrado=true;
      }
      if(m_aux.getPos()<=0)
         return 0;
  }
  if(!encontrado)
      return 0;

  //Ahora comprobamos que estan todos en orden
  for(i=0; i<vm.size(); i++){
      for(j=0; j<val_chr.size()-1; j++){
         if(vm[i].getChr()==vm[i+1].getChr()){
            if(vm[i].getPos()>=vm[i+1].getPos())
               return 0;
         }
         else{
            if(vm[i].getChr() >= vm[i+1].getChr())
               return 0;
         }
      }
  }

  return true;
}


//OPEREADOR DE SALIDA SOBRECARGADO
ostream& operator<< (ostream& os, const conjunto& c){
   //Imprimir todo el conjunto de mutaciones

   for(conjunto::const_iterator it=c.cbegin(); it<c.cend(); it++){
      os << *it;
      if((it+1)!=c.cend())
         os << ", ";
   }
   os << "\n";

   return os;
}














