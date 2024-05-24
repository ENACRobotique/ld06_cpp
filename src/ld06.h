#pragma once
#include <inttypes.h>
#include <stddef.h>

#define POINT_PER_PACK 12 
#define HEADER 0x54 
#define LD06_NB_POINTS 500

typedef struct  __attribute__((packed)) { 
uint16_t distance; 
uint8_t intensity; 
} LidarPointStructDef; 


typedef struct  __attribute__((packed)) { 
uint8_t           header; 
uint8_t           ver_len; 
uint16_t          speed; 
uint16_t          start_angle; 
LidarPointStructDef point[POINT_PER_PACK]; 
uint16_t          end_angle; 
uint16_t          timestamp; 
uint8_t           crc8; 
}LiDARFrameTypeDef;

enum RxState{
    PERDU,
    ATTENTE_LEN,
    RX_DATA
};


class LD06
{
private:
    LiDARFrameTypeDef lidar_packet;
    LidarPointStructDef points[LD06_NB_POINTS];
    uint16_t angles[LD06_NB_POINTS];
    size_t nb_points;
    size_t packet_index;
    RxState rx_state;
    
    void handle_data();

public:
    LD06();


    int feed(uint8_t* buffer, size_t len);
};

