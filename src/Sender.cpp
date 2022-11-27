#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include "AccessControl.hh"
#include "Port.hh"
#include "Scene.hh"
#include "Sender.hh"


using namespace std;



/*!
 * \brief Wysyła napis do poprzez gniazdo sieciowe.
 *
 * Wysyła napis do poprzez gniazdo sieciowe.
 * \param[in] Sk2Server - deskryptor gniazda sieciowego, poprzez które 
 *                        ma zostać wysłany napis w sensie języka C.
 * \param[in] sMesg - zawiera napis, który ma zostać wysłany poprzez
 *                    gniazdo sieciowe.
 */






/*!
 * \brief Ilość stanów każdego z obiektów.
 *
 * Ilość stanów każdego z obiektów.
 * Podział na kolejne stany obiektów wykorzystywany jest
 * do animacji ruchu obiektów.
 */
#define STATES_NUMBER   5

/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 1
 * i obrazujących jego ruch.
 */
const char* Cmds4Obj1[STATES_NUMBER] = {
  "Cube  2 2.5 1.1  0 0 0  0 0 0  0 0 255\n",
  "Cube  2 2.5 1.1  0 0 1   5 0 0  0 0 255\n",
  "Cube  2 2.5 1.1  0 0 2  10 0 0  0 0 255\n",
  "Cube  2 2.5 1.1  0 0 2  15 0 0  0 0 255\n",
  "Cube  2 2.5 1.1  0 0 2  20 0 0  0 0 255\n"
 };


/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 2
 * i obrazujących jego ruch.
 */
const char* Cmds4Obj2[STATES_NUMBER] = {
  "Cube  2 2.5 1.1  2.5 5 5   0 0 0  105 0 255\n",
  "Cube  2 2.5 1.1  2.0 5 5   0 0 0  105 0 255\n",
  "Cube  2 2.5 1.1  1.5 5 5   0 0 0  105 0 255\n",
  "Cube  2 2.5 1.1  1.0 5 5   0 0 0  105 0 255\n",
  "Cube  2 2.5 1.1  0.5 5 5   0 0 0  105 0 255\n"
 };

/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 3
 * i obrazujących jego ruch.
 */
const char* Cmds4Obj3[STATES_NUMBER] = {
  "Cube  3 2.5 1.1 -3.5 -1 -3  0 0 0  10 0 255\n",
  "Cube  3 2.5 1.1 -3.5 -1 -3  5 5 0  10 0 255\n",
  "Cube  3 2.5 1.1 -3.5 -1 -3  10 0 0  10 0 255\n",
  "Cube  3 2.5 1.1 -3.5 -1 -3  15 0 0  10 0 255\n",
  "Cube  3 2.5 1.1 -3.5 -1 -3  20 0 0  10 0 255\n"  
 };
Sender::~Sender()
{
    close(_Socket);
}


int Sender::Send(const char *sMesg)
{
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);
  while ((IlWyslanych = write(_Socket,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}


   void Sender::Watching_and_Sending() {
     while (ShouldCountinueLooping()) {
       if (!_pScn->IsChanged())  { usleep(10000); continue; }
       _pScn->LockAccess();
       
       //------- Przeglądanie tej kolekcji to uproszczony przykład
       
       Send("Clear\n"); // To jest konieczne, aby usunąć wcześniejsze obiekty.
       cout << "Clear\n";
       for (auto const &iterator : _pScn->getMobileObjects()) {
                                     // Ta instrukcja to tylko uproszczony przykład
	 //cout << rObj.GetStateDesc();
        // Send(_Socket,rObj.GetStateDesc()); // Tu musi zostać wywołanie odpowiedniej
                                           // metody/funkcji gerującej polecenia dla serwera.
       
       Send("Display\n"); // To jest konieczne, aby zobaczyć zmiany
       cout << "Display\n";
       
       _pScn->CancelChange();
       _pScn->UnlockAccess();
     }
     }
   }
   


bool Sender::OpenConnection()
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  _Socket = socket(AF_INET,SOCK_STREAM,0);

  if (_Socket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(_Socket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }
  return true;
}




/*!
 * \brief Przykład wykonywania pojedynczej operacji z animacją.
 *
 * Przykład wykonywania pojedynczej operacji z animacją.
 * \param[in] pObj - wskaźnik na obiekt, dla którego ma być wykonana dana operacja
 *                   zmiany jego stanu.
 * \param[in] pAccCtrl - wskaźnik na obiekt, poprzez który przekazywana jest informacja
 *                   o zmianie na scenie, zaś w trakcie dokonywania zmianay
 *                   zamykany jest dostęp do całej sceny.
 * \retval true - w tym przypadku zawsze zwracana jest wartość \p true.
 */





