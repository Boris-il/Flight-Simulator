//
// Created by boris on 20/12/2019.
//

#include <sys/socket.h>
//#include <bits/socket_type.h>
#include <iostream>
#include "ex1.h"
#include "CommandTypes.h"
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <sstream>
#include <fstream>
#include "algorithm"

unsigned OpenServerCommand::execute(vector<string>::iterator it_vec, unordered_map<string, Var> &var_map) {
    unsigned index = 0;
    Expression *e;
    Interpreter *i1 = new Interpreter();
    string portStr = *(it_vec + 2);
    e = i1->interpret(portStr);
    int port = (int) e->calculate();
    index = 2;

    //std::thread t1(&OpenServerCommand::startSocket, this);
    //t1.join();
    //startSocket();
    cout << "starting socket" << endl;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        cerr << "could not create a socket" << endl;
        //return -1;
    }
  //close(socketfd);
  sockaddr_in address{};
  address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
  if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    cerr << "Could not bind the socket to an IP" << endl;
    //return -2;
  }
  if (listen(socketfd, 5) == -1) {
    cerr << "Error during listening command" << endl;
    // return -3;
  }

  int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
  if (client_socket == -1) {
    cerr << "Error accepting client" << endl;
    //return -4;
  }
  map<string, double> sim_Vars = initXml();

  int x = 1;
  while (x==1){
    char line[1024] = {0};
    int valread = read(client_socket, line, 1024);

    std::vector<double> vect;

    std::stringstream ss(line);

    for (int i; ss >> i;) {
      vect.push_back(i);
      if (ss.peek() == ',')
        ss.ignore();
    }

    map<string, double >::iterator it;
    int indexOfVector=0;
    for (it = sim_Vars.begin(); it != sim_Vars.end(); it++)
    {
      it->second = vect[indexOfVector];
      if ((var_map.find(it->first) != var_map.end()) && (var_map.find(it->first)->second.m_isBound)) {
        var_map.find(it->first)->second.setValue(it->second);
      }
        indexOfVector++;
    }
    //update var_map using sim_vars



    //  for (std::size_t i = 0; i < vect.size(); i++)
    //  std::cout << vect[i] << std::endl;
  }

/*
    while (x == 1) {
        char buffer[1024] = {0};
        int valread = read(client_socket, buffer, 1024);
        cout << buffer << endl;
        if (buffer[0] == 'S') {
            x = 0;
        }
    }*/
  close(socketfd);

    return index;
}

map<string, double> OpenServerCommand::initXml() {
    string line;
    map<string, double> sim_Vars;
    fstream in;
    in.open("/usr/share/games/flightgear/Protocol/generic_small.xml", ios::in);
    if (!in.is_open()) {
        cout << "open file fails" << endl;
    } else {
        while (getline(in, line)) {
            string::iterator end_pos = remove(line.begin(), line.end(), ' ');
            line.erase(end_pos, line.end());
      if (line.rfind("<node>", 0) == 0){
        string sim = line.substr(6, line.length()-13);
        sim_Vars[sim] = 0;
      }

    }
  }
  if (sim_Vars.size() != 36){
    cout << "bad xml input, map size is:%d" << sim_Vars.size() << endl;
  }
  return sim_Vars;

}


