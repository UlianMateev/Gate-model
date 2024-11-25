#pragma once
#pragma once 
#include<iostream> 
#include<vector>                             
#include<ctime>    
#include<random>  
#include <fstream>    
#include <sstream> 

//function that generates random floats between [0 ; 1]
float rand_float() {
    return (float)rand() / (float)RAND_MAX;
}

//function that generates random values for the weights and biases
void init_parametres(float weights1[][2], float weights2[], float bias[]) {

    srand(time(0));

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            weights1[i][j] = rand_float() * 10 - 5;//with this modification the values will be bigger
        }                                          //and may take negative values too
    }

    for (int i = 0; i < 2; i++) {
        weights2[i] = rand_float() * 10 - 5;
    }

    for (int i = 0; i < 3; i++) {
        bias[i] = rand_float() * 10 - 5;
    }
}

//returns the sigmoid function of a float
float sigmoidf(float x) {
    return 1.f / (1.f + expf(-x));
}

//function that saves the weights and biases in a text file
void save_as_txt(int changeIndex, float weights1[][2], float weights2[], float bias[]) {
    // Dynamically generate a filename using the change index
    std::stringstream filename;
    filename << "weights_biases" << changeIndex << ".txt";

    // Open the file for writing 
    std::ofstream outfile(filename.str());

    if (!outfile) {
        std::cerr << "Error opening file: " << filename.str() << std::endl;
        return;
    }
    // Write the 2D array to the file
    outfile << "Weights 1 :\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            outfile << weights1[i][j] << " ";
        }
        outfile << std::endl;  // Newline after each row of the 2D array  
    }
    // Write the first 1D array to the file
    outfile << "Weights 2 :\n";
    for (int i = 0; i < 2; ++i) {
        outfile << weights2[i] << " ";
    }
    outfile << std::endl;  // Newline after 1D array 1

    outfile << "Bias :\n";
    // Write the second 1D array to the file
    for (int i = 0; i < 3; ++i) {
        outfile << bias[i] << " ";
    }
    outfile << std::endl;  // Newline after 1D array 2
    // Close the file
    outfile.close();
}

//function that displays which begnining had the lowest loss and in which text file are the weights and biases
void best_start(std::vector<float>& loss) {

    //searching for the lowest element in the loss vector
    auto n = std::min_element(loss.begin(), loss.end());
    auto min_indx = std::distance(loss.begin(), n); //the index of this element

    std::cout << "Min loss is at index :" << min_indx << " | min loss :" << loss[min_indx] << std::endl;
    std::cout << "*Search for file #:" << min_indx + 1 << std::endl;

    for (int i = 0; i < loss.size(); i++) {
        std::cout << "Loss[" << i << "] = " << loss[i] << std::endl;
    }
}

//function that displays the accuracy of the model in % 
void accuracy(float accuracy[]) {

    float sum = 0.0f;
    for (int i = 0; i < 4; i++) {
        float a = (1 - abs(accuracy[i] - DATA[i][2])) * 100;
        std::cout << "Accuracy:" << a << "%" << std::endl;
        sum += a;
    }
    std::cout << "\nAverage accuracy of the whole model:" << sum / 4 << "%" << std::endl;
}
