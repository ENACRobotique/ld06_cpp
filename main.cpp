#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>

#include <unistd.h>

#include <iostream>
#include <thread>


#include "lidar_data.pb.h"


int main(int argc, char** argv){

  // Initialize eCAL and create a protobuf publisher
  eCAL::Initialize(argc, argv, "ld06_driver");
  eCAL::protobuf::CPublisher<enac::Lidar> publisher("lidar_data");





  // Infinite loop (using eCAL::Ok() will enable us to gracefully shutdown the
  // Process from another application)
  while (eCAL::Ok()){


    // Create a protobuf message object
    enac::Lidar lidar_msg;
    for (int i=359; i>=0; i--){
        lidar_msg.add_angles(i);
        lidar_msg.add_distances(i);
        lidar_msg.add_quality(200);
    }

    // Send the message
    publisher.Send(lidar_msg);
    std::cout << "Sent message!" << std::endl << std::endl;

    sleep(1);  
  }

  // finalize eCAL API
  eCAL::Finalize();
}