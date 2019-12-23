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
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
ConnectCommand::ConnectCommand(){
  this->numberOfArgs = 2;
}
ConnectCommand::ConnectCommand(const char *ipStr, string portStr) {
    this->numberOfArgs = 2;
    this->ip = ipStr;
    Expression *e;
    Interpreter *i1 = new Interpreter();
    e = i1->interpret(portStr);
    this->port = (int) e->calculate();
}

unsigned ConnectCommand::execute(vector<string> &cmd_vec, unordered_map<string, Var> &var_map) {
  string ipStr = vector1[1];
  string portStr = vector1[2];
  //std::thread t2(&ConnectCommand::ConnectStart, this);
  //t2.join();
  ConnectStart();
  return 1 + numberOfArgs;

}
void ConnectCommand::ConnectStart() {

  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    cerr << "could not create a socket" << endl;
    //return -1;
  }
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(this->ip);
  address.sin_port = htons(this->port);
  //memset(address.sin_zero, '\0', sizeof(address.sin_zero));

  int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
  if (is_connect == -1) {
    cerr << "Could not connect to host server" << endl;
   // return -2;
  } else {
    cout << "Client is now connected to server" << endl;
  }

  for (int i = 0; i < 10; ++i) {
    int is_sent = send(client_socket, "hi\n", strlen("hi\n"),0);
    if (is_sent == -1){
      cout <<"Error sending message" << endl;
    } else{
      cout << "hi message sent to server" << endl;
    }
  }

  close(client_socket);


}


