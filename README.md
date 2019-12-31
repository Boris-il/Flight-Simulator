## Welcome To Our FlightGear Simulator Interpreter!
**The following documentation refers to an ongoing project as part of our CS major in Bar Ilan University.** 


![cessna](https://i.redd.it/dgdfrctik7s11.jpg)


### Background


Our interpreter acts as a server-client application. It supports sending and receiving flight telemtry data with 
the open-source [FlightGear](https://www.flightgear.org/) Simulator, 
and can interpret piloting commands to make the aircraft fly, using dynamic `txt` file as an input.

Written in `C++`.


### Key Features
* Sending and Recieving data via socket connection.
* Multi-Threading implementation.
* Usage of C++ STL library.
* Usage of I/O libraries.
* Organized work using Github repository.

### Installation
FlightGear simulator can be downloaded [here](https://www.flightgear.org/download/). For Linux distribution, you can use terminal:
```
sudo add-apt-repository ppa:saiarcot895/flightgear

sudo apt-get update
```


### Authors
Yuval Machlev,
Boris Ilchenkov

BIU University, Israel.
