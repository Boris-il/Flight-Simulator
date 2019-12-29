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
#include "Singleton.h"

unsigned OpenServerCommand::execute(vector<string>::iterator it_vec, unordered_map<string, Var *> &var_map) {
  unsigned index = 0;
  Expression *e;
  Interpreter *i1 = new Interpreter();
  string portStr = *(it_vec + 1);
  e = i1->interpret(portStr);
  int port = (int) e->calculate();
  index = 1;

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
    close(socketfd);
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
  vector<pair<string, float>> sim_value_vect = initXml();
  unordered_map<string, string> sim_varName = buildSimNameMap(var_map);
  this->var_map = &var_map;
  this->sim_value_vect = sim_value_vect;
  this->client_socket = client_socket;
  this->sim_varName = sim_varName;
  //thread t1(OpenServerCommand::receiveData,var_map,sim_value_vect,sim_varName,client_socket);
  thread t1([this] { receiveData(); });
  t1.detach();
  //t1.join();
  // thread t1(&OpenServerCommand::receiveData, var_map, sim_value_vect, client_socket, sim_varName);
  //receiveData();

/*
    while (x == 1) {
        char buffer[1024] = {0};
        int valread = read(client_socket, buffer, 1024);
        cout << buffer << endl;
        if (buffer[0] == 'S') {
            x = 0;
        }
    }*/
  // close(socketfd);

  return index;
}

vector<pair<string, float>> OpenServerCommand::initXml() {
  vector<pair<string, float>> sim_value_vect;
  string line;
  // map<string, float> sim_Vars;
  fstream in;
  in.open("/usr/share/games/flightgear/Protocol/generic_small.xml", ios::in);
  if (!in.is_open()) {
    cout << "open file fails" << endl;
  } else {
    while (getline(in, line)) {
      string::iterator end_pos = remove(line.begin(), line.end(), ' ');
      line.erase(end_pos, line.end());
      if (line.rfind("<node>", 0) == 0) {
        string sim = line.substr(6, line.length() - 14);
        //todo this map is not in order of the XML because it sorts it alphabetically (not good). Maybe we should use vector?
        sim_value_vect.push_back(make_pair(sim, 0));
        //   sim_Vars[sim] = 0;
      }

    }
  }
  if (sim_value_vect.size() != 36) {
    cout << "bad xml input, vector size is:%d" << sim_value_vect.size() << endl;
  }
  return sim_value_vect;

}

void OpenServerCommand::receiveData() {
  Singleton *s = Singleton::getInstance();
  while (!s->shouldStop) {
    //todo lock
    char line[1024] = {0};
    int valread = read(client_socket, line, 1024);

    std::vector<double> vect;

    std::stringstream ss(line);
    float i;

    while (ss >> i) {
      vect.push_back(i);

      if (ss.peek() == ',')
        ss.ignore();
    }

    for (int i = 0; i < sim_value_vect.size(); ++i) {
      sim_varName = buildSimNameMap(*var_map);
      if (sim_varName.find(sim_value_vect[i].first) == sim_varName.end()) {
        continue;
      }
      if (var_map->find(sim_varName.find(sim_value_vect[i].first)->second) == var_map->end()) {
        continue;
      }
      if ((var_map->find(sim_varName.find(sim_value_vect[i].first)->second)->second->getValue()
          != sim_value_vect[i].second)
          && ((var_map->find(sim_varName.find(sim_value_vect[i].first)->second)->second->getBoundType()) == 1)) {
        var_map->find(sim_varName.find(sim_value_vect[i].first)->second)->second->setValue(sim_value_vect[i].second);
      }
    }

    for (std::size_t i = 0; i < vect.size(); i++) {
      cout << vect[i];
      if (i < vect.size() - 1) {
        cout << ",";
      }
    }
    cout << endl;

//    //todo unlock
//  }

    sim_varName = buildSimNameMap(*var_map);
  }
}
unordered_map<string, string> OpenServerCommand::buildSimNameMap(unordered_map<string, Var *> &map) {
  unordered_map<string, string> sim_name_map;
  unordered_map<string, Var *>::iterator it;
  for (it = map.begin(); it != map.end(); it++) {
    sim_name_map[it->second->getSim()] = it->second->getName();
  }
  return sim_name_map;
}

