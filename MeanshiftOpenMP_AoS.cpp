#include <cmath>
#include <fstream>
#include <chrono>
#include "PointAoS.h"
#include <omp.h>
#include<vector>
#include<iterator>
#include <sstream>
#include <iostream>


using namespace std;
using namespace std::chrono;


vector<Point> initalize_points(string fname);
void mean_shift(vector<Point> &points,vector<Point> &new_points, int lambda, bool &isShifting);
void draw_chart_gnu(vector<Point> &points);

int main() {
    auto start = std::chrono::system_clock::now();
    int num_threads;
    num_threads = 6;
    const string fname = "C:\\Progetti\\MeanShift\\datasets\\2D_data_10000.csv";
    int max_iterations = 10;
    int current_iterations = 0;
    int lambda = 1;
    omp_set_num_threads(num_threads);

    bool isShifting = true;

    vector<Point> points;
    vector<Point> new_points;
    vector<Point> new_pointsNonZero;

    points = initalize_points(fname);
    new_points = initalize_points(fname);

    while(current_iterations<max_iterations && isShifting==true) {
        current_iterations++;
        mean_shift(points, new_points,lambda, isShifting);
    }
    for(int i =0; i<points.size(); i++){
        if(new_points[i].get_coord_x()!=0){
            Point pt (new_points[i].get_coord_x(),new_points[i].get_coord_y());
            new_pointsNonZero.push_back(pt);

        }
    }


    auto end = std::chrono::system_clock::now();
    double duration = chrono::duration_cast<chrono::milliseconds>(end-start).count();

    string output;
    output = "AoS -- Nr Threads: " + std::to_string(num_threads) + " Total milliseconds: " + std::to_string(duration) + "\n";

    // Open the file in output mode
    std::ofstream outputFile("Result.txt", std::ios::app);

    // Check if the file was opened successfully
    if (outputFile.is_open())
    {
        // Write the string to the file
        outputFile << output;

        // Close the file
        outputFile.close();
    }

    // Save the new_pointsNonZero vector into a CSV file
    // string outputFileName;
    // outputFileName = "new_pointsNonZero.csv";
    // std::ofstream outputFile(outputFileName, std::ios::app);
    // unsigned long points_size = new_pointsNonZero.size();
    // if (outputFile.is_open())
    // {
    //     for (int j = 0; j < points_size; j++)
    //     {
    //         outputFile << new_pointsNonZero[j].get_coord_x() << "," << new_pointsNonZero[j].get_coord_y() << "\n";
    //     }
    //     outputFile.close();
    //     cout << "New points with non-zero coordinates saved to " << outputFileName << endl;
    // }
    // else
    // {
    //     cout << "Unable to open the output file " << outputFileName << endl;
    // }
    return 0;
}

vector <Point> initalize_points(string fname){
    //*****************************************************************************************************************
    //INITALIZAITONS
    //*****************************************************************************************************************
    vector<Point> points;
    vector<string>row;
    string line, column;
    vector<vector<string>> content;
    fstream file(fname, ios::in);
    //*****************************************************************************************************************
    //FILLS VECTOR OF POINTS RANDOMLY GENERATED
    //*****************************************************************************************************************


    if(file.is_open()){
        while(getline(file, line)){
            row.clear();
            stringstream str(line); //Reads the file
            while(getline(str, column, ',')){ //Takes each line and for each line each column
                row.push_back(column); //Push each column in a vector of rows
            }
            content.push_back((row)); //Push each row in a matrix

        }

    }
    int size = content.size();
    for (int i = 0; i < size; i++)
    {
        double coord_x = std::stod(content[i][0]);
        double coord_y = std::stod(content[i][1]);
        Point pt (coord_x,coord_y );
        points.push_back(pt);
    }
    return points;
}

void mean_shift(vector<Point> &points, vector<Point> &new_points, int lambda, bool &isShifting){

    isShifting = false;
    unsigned long points_size = points.size();
  
#pragma omp parallel firstprivate(points_size)
   {
#pragma  omp for schedule(static)
        for (int i = 0; i < points_size; i++) {
            float new_coord_x = 0.0;
            float new_coord_y = 0.0;
            float weight = 0.0;
            for (int j = 0; j < points_size; j++) {
                if (sqrt(pow(points[j].get_coord_x() - points[i].get_coord_x(), 2) +
                                pow(points[j].get_coord_y() - points[i].get_coord_y(), 2))<lambda){
                
                    isShifting = true;
                    new_coord_x += points[j].get_coord_x();
                    new_coord_y += points[j].get_coord_y();
                    weight += 1;
                }
                
            }
            if (weight != 0)
            {
                new_coord_x /= weight;
                new_coord_y /= weight;
            }
            else
            {
                // If weight is 0, set the new coordinates to the current point's coordinates
                new_coord_x = points[i].get_coord_x();
                new_coord_y = points[i].get_coord_y();
            }
            new_points[i] = Point(new_coord_x, new_coord_y);
    }

   }


}