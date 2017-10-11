#include <iostream>
#include <string>

using namespace std;
int main() {
	int n_personas, i=0;
	int pos_f;
	
	cout << "Cantidad de gente: \n";
	cin >> n_personas;
	cin.ignore(256, '\n');
	string nombres[n_personas], aux;

	for (int j=0; j<n_personas; j++)
		getline(cin, nombres[j], '\n');
		
	while(i<n_personas){
		if((nombres[i].find("Soy "))!=-1 ){
			aux= nombres[i].substr(4, nombres[i].size());
			cout << "Hola, " << aux << endl;
			
		}
		i++;
	}
}
 
 
 
 
