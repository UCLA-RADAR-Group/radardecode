#ifndef ALFASHMH
#define ALFASHMH

typedef struct { /* alfa monitor structure to be broadcasted */
  float bias_voltages[126];
  float other_voltages[25];
 
  float vacuum;
  float motor_position; /* motor position */
  unsigned char first_bias;
  unsigned char second_bias;
  unsigned char status;
  unsigned char calohi;

  unsigned char motor_status; /* motor moving ? */
  unsigned char fill[3];
} ALFASHM;
#endif
