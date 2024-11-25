#pragma once
#pragma once
#include<iostream>
#include<vector> 
#include<cmath>   
#include"parameters.h" 
#include"functions.h"   

//forward propagation
float forward(float input[], float weights1[][2], float weights2[], float bias[]) {

    float a = 0.0f; // a is the first neuron in the hidden layer
    float b = 0.0f; // b is the second neuron in the hidden layer

    for (int i = 0; i < 2; i++) {
        a += input[i] * weights1[i][0];
    }
    a = sigmoidf(a + bias[0]);

    for (int i = 0; i < 2; i++) {
        b += input[i] * weights1[i][1];
    }
    b = sigmoidf(b + bias[1]);

    //returns the value of the output neuron which is 1 and only
    return sigmoidf(a * weights2[0] + b * weights2[1] + bias[2]);
}

//function that returns the loss of the output 
float lossf(float weights1[][2], float weights2[], float bias[]) {

    float loss = 0.0f;

    //forwards the data and calculates the loss 
    for (int i = 0; i < size; i++) {
        float input[2];
        input[0] = DATA[i][0];
        input[1] = DATA[i][1];
        float outp = forward(input, weights1, weights2, bias);
        float dif = outp - DATA[i][2];
        loss += dif * dif;
    }
    loss /= size;
    return loss;
}

//function that updates the models weights and biases
float updatem(float weights1[][2], float weights2[], float bias[]) {

    float l = lossf(weights1, weights2, bias);//calculates the loss with the original weights and biases 
    float w1[2][2];
    float w2[2];
    float b[3];

    for (int i = 0; i < 2; i++) {  //putting the original weights and biases in new arrays
        for (int j = 0; j < 2; j++) {
            w1[i][j] = weights1[i][j];
        }
    }
    for (int i = 0; i < 2; i++) {
        w2[i] = weights2[i];

    }
    for (int i = 0; i < 3; i++) {
        b[i] = bias[i];
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            float original1 = w1[i][j]; //saving the original value of the weight
            w1[i][j] += EPS;            //updating the weight
            float gradient = (lossf(w1, weights2, bias) - l) / EPS;//calculating the derivative of the updated weights using the deffinition of the derivative and using the original function - c
            w1[i][j] = original1;       //returning the original value of the weight
            weights1[i][j] -= LR * gradient;//updating the weight of the model
        }
    }
    //this is calculating the derivative of each weight and bias individualy and then updates them
    //doing this proccess for every weigth and bias

    for (int i = 0; i < 2; i++) {
        float original2 = w2[i];
        w2[i] += EPS;
        float gradient2 = (lossf(w1, w2, bias) - l) / EPS;
        w2[i] = original2;
        weights2[i] -= LR * gradient2;
    }

    for (int i = 0; i < 3; i++) {
        float original3 = b[i];
        float gradient3 = (lossf(w1, w2, b) - l) / EPS;
        b[i] = original3;
        bias[i] -= LR * EPS;
    }
    return l; // returning the loss of the 
}

//function that trains the model for a desired amount of time
float trainm(float weights1[][2], float weights2[], float bias[]) {

    float loss;
    //updating the model TRAINING amount of times 
    for (int i = 0; i < TRAINING; i++) {
        loss = updatem(weights1, weights2, bias);
        std::cout << "Lost:" << loss << "\n";    //displaying the loss after each update        
    }
    return loss;
}

//function that that starts the proccess from a new start with new values for the weights and biases
// in order to find the best values for the begining 
void new_start(float weights1[][2], float weights2[], float bias[], std::vector<float>& loss) {

    int n_file = 0;
    for (int i = 0; i < BEGININGS; i++) {
        float l = trainm(weights1, weights2, bias);
        loss.push_back(l);
        save_as_txt(++n_file, weights1, weights2, bias);
        init_parametres(weights1, weights2, bias);
    }
}

//function that forwards the data with the updated weights 
void test_model(float weights1[][2], float weights2[], float bias[], float accuracy[]) {
    int k = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            float inp[2];
            inp[0] = (float)i;
            inp[1] = (float)j;
            float outp = forward(inp, weights1, weights2, bias);
            std::cout << i << GATE << j << " = " << outp << std::endl;
            accuracy[k] = outp;
            k++;
        }
    }
}