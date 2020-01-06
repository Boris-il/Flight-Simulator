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

unsigned OpenServerCommand::execute(vector<string>::iterator it_vec) {
  //Singleton *s = Singleton::getInstance();
  unsigned index = 0;
  Expression *e;
  Interpreter *i1 = new Interpreter();
  string portStr = *(it_vec + 1);
  e = i1->interpret(portStr);
  this->port = (int) e->calculate();
  index = 1;

  thread t0([this] { startSocket(); });
  t0.join();

  vector<pair<string, float>> sim_value_vect1 = initXml();  //create vector by the sims in XML file.
  unordered_map<string, string> sim_varName1 = buildSimNameMap();  //create map of sim and name of vars.
  this->sim_value_vect = sim_value_vect1;
  this->sim_varName = sim_varName1;
  thread t1([this] { receiveData(); });
  t1.detach();

  return index;
}

vector<pair<string, float>> OpenServerCommand::initXml() {
  vector<pair<string, float>> sim_value_vect2;
  string line;
  fstream in;
  in.open("/usr/share/games/flightgear/Protocol/generic_small.xml", ios::in);
  if (!in.is_open()) {
    cout << "open file fails" << endl;
  } else {
    while (getline(in, line)) { //run over XML file.
      string::iterator end_pos = remove(line.begin(), line.end(), ' ');
      line.erase(end_pos, line.end());
      if (line.rfind("<node>", 0) == 0) { //sim path in <node> tag.
        string sim = line.substr(6, line.length() - 14);
        //todo this map is not in order of the XML because it sorts it alphabetically (not good). Maybe we should use vector?
        sim_value_vect2.push_back(make_pair(sim, 0));
      }

    }
  }
  /*if (sim_value_vect2.size() != 36) {
    cout << "bad xml input, vector size is:%d" << sim_value_vect2.size() << endl;
  }*/
  return sim_value_vect2;

}

void OpenServerCommand::receiveData() {

  Singleton *s = Singleton::getInstance();
  s->socketNumber1 = client_socket;
  string buffer = "";
  while (!s->shouldStop) {
    std::vector<float> vect;
    //todo lock
    char line[1024] = {0}; //1,1,1,1,1,1,1\n1,1,1,1
    read(client_socket, line, 1024);
    string buffer2 = line;
    buffer = buffer + buffer2;
    string firstN = buffer.substr(0, buffer.find("\n"));
    string secondN = buffer.substr(buffer.find("\n") + 1, buffer.length());

    std::stringstream ss(firstN);
    float i;

    while (ss >> i) { //ignor commas and push to vector.
      vect.push_back(i);

      if (ss.peek() == ',')
        ss.ignore();
    }

    for (unsigned long k = 0; k < sim_value_vect.size(); ++k) {
      sim_varName = buildSimNameMap(); //update map
      string sim = sim_value_vect[k].first;
      string varName;
      float value = vect[k];
      auto it = sim_varName.find(sim_value_vect[k].first);
      if (it != sim_varName.end()) {
        varName = it->second;
      }

      if (sim_varName.find(sim) == sim_varName.end()) { //non-exist element
        continue;
      }
      if (s->var_map.find(varName) == s->var_map.end()) { //non-exist element
        continue;
      }
      if (s->var_map.find(varName)->second->hasValue == false) {
        s->var_map.find(varName)->second->setValue(value);
        /*if (value < 0) {
            value = -value;
        }*/
        string str = varName + "=" + to_string(value);
        s->m_inter->setVariables(str);

      } else if ((s->var_map.find(varName)->second->getValue() != value)
          && ((s->var_map.find(varName)->second->getBoundType()) == 1)) {
        s->var_map.find(varName)->second->setValue(value);
//        if (value < 0) {
//          value = -value;
//        }
        string str = varName + "=" + to_string(value);
        s->m_inter->setVariables(str);
      }
    }
    //print values
    /*for (std::size_t i = 0; i < vect.size(); i++) { // print all values.
      cout << vect[i];
       if (i < vect.size() - 1) {
         cout << ",";
       }
     }
      cout << endl;*/

//    //todo unlock
//  }

    sim_varName = buildSimNameMap();
    buffer = secondN;
  }
}
unordered_map<string, string> OpenServerCommand::buildSimNameMap() {
  Singleton *s = Singleton::getInstance();
  unordered_map<string, string> sim_name_map;
  unordered_map<string, Var *>::iterator it;
  for (it = s->var_map.begin(); it != s->var_map.end(); it++) {
    sim_name_map[it->second->getSim()] = it->second->getName();
  }
  return sim_name_map;
}
void OpenServerCommand::startSocket() {
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

  int client_socket1 = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
  if (client_socket1 == -1) {
    cerr << "Error accepting client" << endl;
    //return -4;
  }
  this->client_socket = client_socket1;

}

