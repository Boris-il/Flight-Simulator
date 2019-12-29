//
// Created by boris on 20/12/2019.
//

#include "Command.h"
#include "CommandTypes.h"
#include "ex1.h"
#include <sys/socket.h>
//#include <bits/socket_type.h>
#include <iostream>
#include "CommandTypes.h"
#include "Singleton.h"
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

unsigned ConnectCommand::execute(vector<string>::iterator it, unordered_map<string, Var *> &var_map) {
  unsigned index = 0;
  string ipStr, portStr;
  string str = *(it + 1);
  auto pos = str.find(',');
  if (pos != string::npos) {
    ipStr = str.substr(1, pos - 2);
    portStr = str.substr(pos + 1, str.length() - pos);
  }

  const char *ipFinal = ipStr.data();
  // string portStr = *(it + 2);
  index = 1;
  int port;
  Expression *e;
  Interpreter *i1 = new Interpreter();
  e = i1->interpret(portStr);
  port = (int) e->calculate();
  //std::thread t2(&ConnectCommand::ConnectStart, this);
  //t2.join();
  //ConnectStart();


  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    cerr << "could not create a socket" << endl;
    //return -1;
  }
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(ipFinal);
  address.sin_port = htons(port);
  //memset(address.sin_zero, '\0', sizeof(address.sin_zero));

  int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
  if (is_connect == -1) {
    cerr << "Could not connect to host server" << endl;
    // return -2;
  } else {
    cout << "Client is now connected to server" << endl;
  }
  this->var_map = &var_map;
  this->client_socket = client_socket;
  //thread t2(ConnectCommand::setData,var_map,client_socket);
  thread t2([this] { setData(); });
  t2.detach();
  //std::thread t2(&ConnectCommand::setData, var_map, client_socket);

  // t2.join();

  /* for (int i = 0; i < 10; ++i) {
       int is_sent = send(client_socket, "hi\n", strlen("hi\n"), 0);
       if (is_sent == -1) {
           cout << "Error sending message" << endl;
       } else {
           cout << "hi message sent to server" << endl;
       }
   }*/

  //   close(client_socket);

  return index;
}

void ConnectCommand::setData() {
  string buffer;
  Singleton *s = Singleton::getInstance();
  while (!s->shouldStop) {
    unordered_map<string, Var *>::iterator it;
    for (it = var_map->begin(); it != var_map->end(); it++) {
      if (it->second->getBoundType() == 0) {
        if (it->second->getValue() != 0) {
          cout << it->second->getSim() << endl;
        }
        //buffer = "set " + it->second.getSim() + " " + to_string(it->second.getValue());
        // buffer = "set " + it->second->getSim() + " " + to_string(it->second->getValue()) + "\r\n";
        buffer.append("set ");
        buffer.append((it->second->getSim()));
        buffer.append(" ");
        buffer.append(to_string(it->second->getValue()));
        buffer.append("\r\n");
        char msg[buffer.length() + 1];
        strcpy(msg, buffer.c_str());
        int is_sent = send(client_socket, msg, strlen(msg), 0);
        if (is_sent == -1) {
          cout << "Error sending message of set" << endl;
        } else {
          //cout << "set message sent to server" << endl;
          cout << "set message : " << msg << endl;
        }
      }
    }
  }
}
