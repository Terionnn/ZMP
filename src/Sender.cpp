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
#define STATES_NUMBER 5

int Sender::Send(const char *sMesg)
{
    ssize_t IlWyslanych;
    ssize_t IlDoWyslania = (ssize_t)strlen(sMesg);
    while ((IlWyslanych = write(_Socket, sMesg, IlDoWyslania)) > 0)
    {
        IlDoWyslania -= IlWyslanych;
        sMesg += IlWyslanych;
    }
    if (IlWyslanych < 0)
    {
        cerr << "*** Blad przeslania napisu." << endl;
    }
    return 0;
}

void Sender::Watching_and_Sending()
{
    while (ShouldCountinueLooping())
    {
        if (!_pScn->IsChanged())
        {
            usleep(10000);
            continue;
        }
        _pScn->LockAccess();
        Send("Clear\n");
        cout << "Clear\n";
        for (auto const &iterator : _pScn->getMobileObjects())
        {
            Send("Display\n");
            cout << "Display\n";
            _pScn->CancelChange();
            _pScn->UnlockAccess();
        }
    }
}

bool Sender::OpenConnection()
{
    struct sockaddr_in DaneAdSerw;

    bzero((char *)&DaneAdSerw, sizeof(DaneAdSerw));

    DaneAdSerw.sin_family = AF_INET;
    DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
    DaneAdSerw.sin_port = htons(PORT);

    _Socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_Socket < 0)
    {
        cerr << "*** Blad otwarcia gniazda." << endl;
        return false;
    }

    if (connect(_Socket, (struct sockaddr *)&DaneAdSerw, sizeof(DaneAdSerw)) < 0)
    {
        cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
        return false;
    }
    return true;
}

Sender::~Sender()
{
    close(_Socket);
}
