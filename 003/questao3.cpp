#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
using namespace std;

class a {
int fila;
mutex m;

  public: 
  a(int f);
  
  void imprimeDocumento( string c = {});
  void cancelaDocumento(string c = {});
  int getTamanhoFila();
};

a::a(int f) {
  fila = f;
}

void a::cancelaDocumento( string c) {
  
  m.lock();
    //cancela documento;
  m.unlock();
}

void a::imprimeDocumento(string c) {
  
  m.lock();
c = "documento.txt";
cout << "O arquivo documento.txt possui: \n";
fstream documento(c,ios::in);
string strLine;

while (! documento.eof() ) 
    {
      getline(documento, strLine); 
                             
      cout << strLine << endl;
    }
   

  documento.close();
  
  m.unlock();
}

int a::getTamanhoFila() {
  return fila;
}




int main() {

  a s1(0);
  string C;
  cout <<"Digite o nome do documento: \n";
  cin>>C;
  

  thread t1(&a::imprimeDocumento, &s1, C);
  thread t2(&a::imprimeDocumento, &s1, C);

  
  t1.join();
  t2.join();



  return 0;
}