#pragma once
#include<string>  
//in this file you can change the parameters in your desire
//and optimise for the best performance

#define EPS (float)1e-5  //used in calculating the derivatives
#define LR (float)1e-1   //learning rate
#define TRAINING 10000   //how much times the model will be updated after going through all the data
#define BEGININGS 3     //starting the proccess from the start with new weights and biases in order to find the best starting parameters
#define DATA nand_train   //changing the training data 
static const std::string GATE = " NAND ";   //changing the training data 

//training data for different gates
float or_train[][3] = { {0, 0, 0},
                        {1, 0, 1},
                        {0, 1, 1},
                        {1, 1, 1}
};
float and_train[][3] = { {0, 0, 0},
                         {1, 0, 0},
                         {0, 1, 0},
                         {1, 1, 1}
};
float nand_train[][3] = { {0, 0, 1},
                         {1, 0, 1},
                         {0, 1, 1},
                         {1, 1, 0}
};
float xor_train[][3] = { {0.f, 0.f, 0.f},
                         {1.f, 0.f, 1.f},
                         {0.f, 1.f, 1.f},
                         {1.f, 1.f, 0.f}
};

const int size = sizeof(or_train) / sizeof(or_train[0]);//size of the training data