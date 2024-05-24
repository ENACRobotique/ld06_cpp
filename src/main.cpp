#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>
#include "serialib/serialib.h"
#include <unistd.h>
#include <inttypes.h>
#include <iostream>
#include <thread>

#include "lidar_data.pb.h"


//serialib: https://github.com/imabot2/serialib
//

int main(int argc, char** argv){

  if(argc < 2) {
    std::cout << "Please specify serial port" << std::endl;
    return -1;
  }
  // Serial object
  serialib serial;

  // Connection to serial port
  char errorOpening = serial.openDevice(argv[1], 230400);
  if (errorOpening!=1) return errorOpening;

  
  // Initialize eCAL and create a protobuf publisher
  eCAL::Initialize(argc, argv, "ld06_driver");
  eCAL::protobuf::CPublisher<enac::Lidar> publisher("lidar_data");





  // Infinite loop (using eCAL::Ok() will enable us to gracefully shutdown the
  // Process from another application)
  while (eCAL::Ok()){
    uint8_t c;
    int ret = serial.readChar((char*)&c);
    if(ret == 1) {
      printf("read 0x%X\n", c);
    } else {
      printf("error reading byte: %d\n", ret);
    }

    /*
    enac::Lidar lidar_msg;
    for (int i=359; i>=0; i--){
        lidar_msg.add_angles(i);
        lidar_msg.add_distances(i);
        lidar_msg.add_quality(200);
    }
    // Send the message
    publisher.Send(lidar_msg);
    std::cout << "Sent message!" << std::endl << std::endl;
    */

  }

  // finalize eCAL API
  eCAL::Finalize();
}
