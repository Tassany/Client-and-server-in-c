#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
using namespace std;

class ArquivoLog {
  double saldo;
  mutex m;

  public: 
  ArquivoLog(double d = 0);
  
  void monitor1( string c = {});
  void monitor2(string c = {});
};

ArquivoLog::ArquivoLog(double d) {
  saldo = d;
}

void ArquivoLog::monitor1( string c) {
  
  
  m.lock();
  
  fstream log("log.txt",ios::app);


  

  time_t current_time;
  char* c_time_string;

    /* Obtain current time. */
      time_t timer;
  struct tm *horarioLocal;

  time(&timer); // Obtem informações de data e hora
  horarioLocal = localtime(&timer); // Converte a hora atual para a hora local

  int dia = horarioLocal->tm_mday;
  int mes = horarioLocal->tm_mon + 1;
  int ano = horarioLocal->tm_year + 1900;

  int hora = horarioLocal->tm_hour;
  int min  = horarioLocal->tm_min;
  int sec  = horarioLocal->tm_sec;

  log << dia  << "/" << mes << "/" << ano << " - " << hora << ":" << min << " " << c << endl;
  
  m.unlock();
}

void ArquivoLog::monitor2(string c) {
  
  m.lock();
  
  fstream log("log2.txt",ios::app);



  time_t current_time;
  char* c_time_string;

    
      time_t timer;
  struct tm *horarioLocal;

  time(&timer); 
  horarioLocal = localtime(&timer); 
  //"06/04/2020 - 15:00 ABRACADABRA"
  int dia = horarioLocal->tm_mday;
  int mes = horarioLocal->tm_mon + 1;
  int ano = horarioLocal->tm_year + 1900;

  int hora = horarioLocal->tm_hour;
  int min  = horarioLocal->tm_min;
  int sec  = horarioLocal->tm_sec;

  log << dia  << "/" << mes << "/" << ano << " - " << hora << ":" << min << " "<< c << endl;
  //log << "Data: "    << dia  << "/" << mes << "/" << ano << endl;

  
  m.unlock();
}




int main() {

  ArquivoLog s1(0);
  cout <<"Digite oq quer enviar: \n";
  
  string C;
  cin>> C;
  thread t1(&ArquivoLog::monitor1, &s1, C);
  
  thread t2(&ArquivoLog::monitor1, &s1, C);
  thread t3(&ArquivoLog::monitor1, &s1, C);

  thread t4(&ArquivoLog::monitor1, &s1, C);
  thread t5(&ArquivoLog::monitor2, &s1,C);
  

  
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();

cout << "O arquivo log.txt possui: \n";
fstream log("log.txt",ios::in);
string strLine;

while (! log.eof() ) //enquanto end of file for false continua
    {
      getline(log, strLine); // como foi aberto em modo texto(padrão)
                             //e não binário(ios::bin) pega cada linha
      cout << strLine << endl;
    }
   

  log.close();
cout <<"--------------------------------------------------------";
  cout << "O arquivo log2.txt possui: \n";
fstream log2("log2.txt",ios::in);
string strLine2;

while (! log2.eof() ) //enquanto end of file for false continua
    {
      getline(log2, strLine2); // como foi aberto em modo texto(padrão)
                             //e não binário(ios::bin) pega cada linha
      cout << strLine2 << endl;
    }
   

  log2.close();
  return 0;
}