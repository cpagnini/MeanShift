#include <cmath>
#include <fstream>
#include <chrono>
#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
#include "PointSoA.h"
#include <omp.h>


using namespace std;
using namespace std::chrono;

PointSoA initialize_points(const string &fname);
void mean_shift(PointSoA &points, PointSoA &new_points, int lambda, bool &isShifting);

int main()
{
    auto start = std::chrono::system_clock::now();
    int num_threads = 6;
    const string fname = "C:\\Progetti\\MeanShift\\datasets\\2D_data_100000.csv";
    int max_iterations = 10;
    int current_iterations = 0;
    int lambda = 1;
    omp_set_num_threads(num_threads);

    bool isShifting = true;

    PointSoA points = initialize_points(fname);
    PointSoA new_points(points.size);

    while (current_iterations < max_iterations && isShifting)
    {
        current_iterations++;
        mean_shift(points, new_points, lambda, isShifting);
        swap(points, new_points); // Swap the point arrays for the next iteration
    }

    auto end = std::chrono::system_clock::now();
    double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    string output;
    output = "SOA -Nr Threads: " + to_string(num_threads) + " Total milliseconds: " + to_string(duration) + "\n";

    // Open the file in output mode
    ofstream outputFile("Result.txt", ios::app);

    // Check if the file was opened successfully
    if (outputFile.is_open())
    {
        // Write the string to the file
        outputFile << output;

        // Close the file
        outputFile.close();
    }

    return 0;
}

PointSoA initialize_points(const string &fname)
{
    PointSoA points(0); // Initialize with 0 points

    // Read the CSV file
    ifstream file(fname);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream str(line);
            string column;
            getline(str, column, ',');
            double coord_x = stod(column);
            getline(str, column, ',');
            double coord_y = stod(column);
            points.x_coord.push_back(coord_x);
            points.y_coord.push_back(coord_y);
        }
        file.close();
    }

    points.size = points.x_coord.size();
    return points;
}

void mean_shift(PointSoA &points, PointSoA &new_points, int lambda, bool &isShifting)
{
    isShifting = false;

#pragma omp parallel for
    for (int i = 0; i < points.size; i++)
    {
        double new_coord_x = 0.0;
        double new_coord_y = 0.0;
        int weight = 0;

        for (int j = 0; j < points.size; j++)
        {
            double distance = sqrt(pow(points.x_coord[j] - points.x_coord[i], 2) +
                                   pow(points.y_coord[j] - points.y_coord[i], 2));
            if (distance < lambda)
            {
                isShifting = true;
                new_coord_x += points.x_coord[j];
                new_coord_y += points.y_coord[j];
                weight += 1;
            }
        }

        if (weight > 0)
        {
            //printf("%d",weight);
            new_coord_x /= weight;
            new_coord_y /= weight;
        }

        new_points.x_coord[i] = new_coord_x;
        new_points.y_coord[i] = new_coord_y;
    }
}

