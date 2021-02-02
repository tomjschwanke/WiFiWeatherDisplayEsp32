// All animation frames

uint8_t empty = 0b00000000;

uint8_t load[12][8]        =   { 
  {0b00000000, 0b00000000, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b00000100, 0b00001100, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b00011100, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00111100, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100000, 0b00111000, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00000000, 0b00100000, 0b00100000, 0b00110000, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00100000, 0b00100000, 0b00100000, 0b00100000, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00110000, 0b00100000, 0b00100000, 0b00000000, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00111000, 0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00111100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00011100, 0b00000100, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00001100, 0b00000100, 0b00000100, 0b00000000, 0b00000000, 0b00000000}
};

uint8_t clearDay[3][8]     =   { 
  {0b00000000, 0b00000000, 0b00011000, 0b00111100, 0b00111100, 0b00011000, 0b00000000, 0b00000000},
  {0b00000000, 0b01000010, 0b00011000, 0b00111100, 0b00111100, 0b00011000, 0b01000010, 0b00000000},
  {0b10010001, 0b01000010, 0b00011000, 0b00111100, 0b00111100, 0b00011000, 0b01000010, 0b10001001}
};

uint8_t clearNight[2][8]   =   { 
  {0b00000000, 0b00001000, 0b10000001, 0b10000001, 0b11000011, 0b11111111, 0b01111110, 0b00111100},
  {0b00001000, 0b00011100, 0b10001001, 0b10000001, 0b11000011, 0b11111111, 0b01111110, 0b00111100}
};

uint8_t moderateRain[3][8] =   { 
  {0b00001100, 0b00011110, 0b00111110, 0b00011111, 0b01011111, 0b00011111, 0b10011110, 0b00001100},
  {0b00001100, 0b00011110, 0b01011110, 0b00011111, 0b10011111, 0b00011111, 0b00111110, 0b00001100},
  {0b00001100, 0b00011110, 0b10011110, 0b00011111, 0b00111111, 0b00011111, 0b01011110, 0b00001100}
};

uint8_t heavyRain[3][8]    =   { 
  {0b10001100, 0b01011110, 0b00111110, 0b01011111, 0b10011111, 0b00111111 , 0b01011110, 0b10001100},
  {0b00101100, 0b10011110, 0b01011110, 0b10011111, 0b00111111, 0b01011111 , 0b10011110, 0b00101100},
  {0b01001100, 0b00111110, 0b10011110, 0b00111111, 0b01011111, 0b10011111,  0b00111110, 0b01001100}
};

uint8_t lightning[3][8]  =   { 
  {0b00001100, 0b00011110, 0b00011110, 0b00011111, 0b00011111, 0b00011111, 0b00011110, 0b00001100},
  {0b00001100, 0b00011110, 0b10111110, 0b01011111, 0b00011111, 0b00011111, 0b00011110, 0b00001100},
  {0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111}
};

uint8_t snowfall[2][8]   =   { 
  {0b10011001, 0b01011010, 0b00100100, 0b11011011, 0b11011011, 0b00100100, 0b01011010, 0b10011001},
  {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}
};

uint8_t heavySnowfall[4][8] =  { 
  {0b10011001, 0b01011010, 0b00100100, 0b11011011, 0b11011011, 0b00100100, 0b01011010, 0b10011001},
  {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00000000, 0b11011111, 0b11011111, 0b00000000, 0b00000000, 0b00000000},
  {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}
};

uint8_t notFound[2][8]   =   { 
  {0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00011000, 0b00100100, 0b01000010, 0b10000001},
  {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}
};

uint8_t scatteredClouds[16] = {0b00001100, 0b00011110, 0b00011110, 0b00011111, 0b00011111, 0b00011111, 0b00011110, 0b00001100, 0b00000000, 0b01100000, 0b11110000, 0b11110000, 0b11111000, 0b11111000, 0b11110000, 0b01100000};
uint8_t fewClouds[16]       = {0b00000100, 0b00000110, 0b00000110, 0b00000100, 0b00000000, 0b00010000, 0b00011000, 0b00011000, 0b00011000, 0b00010000, 0b00000000, 0b00100000, 0b01110000, 0b01110000, 0b01110000, 0b00100000};
uint8_t brokenClouds[16]    = {0b01000010, 0b11100111, 0b11100111, 0b11100111, 0b01000010, 0b00010000, 0b00111001, 0b10111011, 0b10111001, 0b00010000, 0b01000010, 0b11100111, 0b11100111, 0b11100111, 0b01000010, 0b00000000};
uint8_t fog[16]             = {0b01000100, 0b01000100, 0b01010001, 0b01010101, 0b00010101, 0b01010101, 0b01010101, 0b00010000, 0b01000100, 0b01000100, 0b01010001, 0b01010101, 0b00010101, 0b01010101, 0b01010101, 0b00010000};

uint8_t numUnderHundred[10][3] = {
  {0b00111110, 0b00100010, 0b00111110},
  {0b00000000, 0b00111110, 0b00000000},
  {0b00111010, 0b00101010, 0b00101110},
  {0b00101010, 0b00101010, 0b00111110},
  {0b00001110, 0b00001000, 0b00111110},
  {0b00101110, 0b00101010, 0b00111010},
  {0b00111110, 0b00101010, 0b00111010},
  {0b00000010, 0b00000010, 0b00111110},
  {0b00111110, 0b00101010, 0b00111110},
  {0b00001110, 0b00001010, 0b00111110},
};

uint8_t numOverHundred[10][3]  = {
  {0b11111000, 0b10001000, 0b11111001},
  {0b00000000, 0b11111000, 0b00000001},
  {0b11101000, 0b10101000, 0b10111001},
  {0b10101000, 0b10101000, 0b11111001},
  {0b00111000, 0b00100000, 0b11111001},
  {0b10111000, 0b10101000, 0b11101001},
  {0b11111000, 0b10101000, 0b11101001},
  {0b00001000, 0b00001000, 0b11111001},
  {0b11111000, 0b10101000, 0b11111001},
  {0b00111000, 0b00101000, 0b11111001}
};

uint8_t hundredOnes[5]  = {0b00000111, 0b00000000, 0b00000111, 0b00000101, 0b00000111};
uint8_t hundredTeens[5] = {0b00000111, 0b00000000, 0b00000000, 0b00000111, 0b00000000};
uint8_t maxHumidity[8]  = {0b00001111, 0b00000000, 0b00001111, 0b00001001, 0b00001111, 0b11110000, 0b10010000, 0b11110000};

uint8_t HU[8] = {0b00111110, 0b00001000, 0b00111110, 0b00000000, 0b00100100, 0b00010000, 0b00001000, 0b00100100};

uint8_t sandclock[8] = {0b00000000, 0b00000000, 0b11100111, 0b11011001, 0b11011001, 0b11100111, 0b00000000, 0b00000000};
uint8_t wrench[8]    = {0b01000001, 0b11100010, 0b01110100, 0b00111000, 0b00011100, 0b01101111, 0b11100101, 0b01000110};

uint8_t wifi[15][8] = {
  { 0b11101000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11101000 },
  { 0b11101000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11101000 }, 
  { 0b11101000, 0b00000000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11101000 }, 
  { 0b11101000, 0b00000000, 0b00000000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b11101000 }, 
  { 0b11101000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000000, 0b00000000, 0b11101000 }, 
  { 0b11101000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000000, 0b11101000 }, 
  { 0b11101000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b11101000 }, 
  { 0b11101000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11101000 }, 
  { 0b11101000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b11101000 }, 
  { 0b11101000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000000, 0b11101000 }, 
  { 0b11101000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000000, 0b00000000, 0b11101000 }, 
  { 0b11101000, 0b00000000, 0b00000000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b11101000 }, 
  { 0b11101000, 0b00000000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11101000 }, 
  { 0b11101000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11101000 }, 
  { 0b11101000, 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b11101000 } 
};

uint8_t download[1][8] = {{0b00010000, 0b00110000, 0b01111111, 0b11111111, 0b01111111, 0b00110000, 0b00010000, 0b00000000}};

uint8_t reqData[7][8] = {
  {0b11101000,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b11101000},
  {0b11101000,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b00000000,0b11101000},
  {0b11101000,0b00001000,0b00001000,0b00001000,0b00001000,0b00000000,0b00001000,0b11101000},
  {0b11101000,0b00001000,0b00001000,0b00001000,0b00000000,0b00001000,0b00001000,0b11101000},
  {0b11101000,0b00001000,0b00001000,0b00000000,0b00001000,0b00001000,0b00001000,0b11101000},
  {0b11101000,0b00001000,0b00000000,0b00001000,0b00001000,0b00001000,0b00001000,0b11101000},
  {0b11101000,0b00000000,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b11101000}
};

uint8_t progressAni[21][8] = {
  {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
  {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000010,0b00000000},
  {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000110,0b00000000},
  {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00001110,0b00000000},
  {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00011110,0b00000000},
  {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00111110,0b00000000},
  {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b01111110,0b00000000},
  {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b00000000,0b00000000,0b00000000,0b01000000,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b00000000,0b00000000,0b01000000,0b01000000,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b00000000,0b01000000,0b01000000,0b01000000,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b01000000,0b01000000,0b01000000,0b01000000,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b01100000,0b01000000,0b01000000,0b01000000,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b01110000,0b01000000,0b01000000,0b01000000,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b01111000,0b01000000,0b01000000,0b01000000,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b01111100,0b01000000,0b01000000,0b01000000,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b01111110,0b01000000,0b01000000,0b01000000,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b01111110,0b01000010,0b01000000,0b01000000,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b01111110,0b01000010,0b01000010,0b01000000,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b01111110,0b01000010,0b01000010,0b01000010,0b01000000,0b01111110,0b00000000},
  {0b00000000,0b01111110,0b01000010,0b01000010,0b01000010,0b01000010,0b01111110,0b00000000}
};
