#include <iostream>
#include <vector>
#include <chrono>
#include "Point.cpp"
#include <fstream>
#include <cmath>

using namespace std;
using namespace std::chrono;


vector<Point> initalize_points(int num_point);
void mean_shift(vector<Point> &points,vector<Point> &centroids, int lambda, bool &isShifting);
void draw_chart_gnu(vector<Point> &points);

int main() {

    auto start = std::chrono::system_clock::now();
    int max_iterations = 20;
    int num_points = 100;
    int current_iterations = 0;
    int lambda = 1;
    bool isShifting = true;
    vector<Point> points;
    vector<Point> centroids;
    points = initalize_points(num_points);

    while(current_iterations<max_iterations && isShifting==true) {
        current_iterations++;
        mean_shift(points, centroids,lambda, isShifting);
    }

    try{
        printf("Drawing the chart...\n");
        draw_chart_gnu(points);
    }catch(int e){
        printf("Chart not available, gnuplot not found");
    }

    auto end = std::chrono::system_clock::now();
    double duration = chrono::duration_cast<chrono::milliseconds>(end-start).count();


    ofstream outfile;
    outfile.open("../Results/Results.txt", fstream::app);
    outfile<<"Num points: "<<num_points<<endl<<"Num clusters: "<<num_cluster<<endl<<"Num iterations: "<<num_iterations<<endl<<"Num threads: "<<num_threads<<endl<<"Total milliseconds: "<<duration<<endl;
    outfile.close();
    return 0;
}

vector <Point> initalize_points(int num_point){
    //*****************************************************************************************************************
    //INITALIZAITONS
    //*****************************************************************************************************************
    vector<Point> points;

    //*****************************************************************************************************************
    //FILLS VECTOR OF POINTS RANDOMLY GENERATED
    //*****************************************************************************************************************
    const string fname ="../datasets/data_100000.csv";
    vector<string>row;
    string line, column;
    vector<vector<string>> content;
    fstream file(fname, ios::in);
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
    for(int i=0;i<num_point; i++){
        double coord_x = std::stod(content[i][0]);
        double coord_y = std::stod(content[i][1]);
        Point pt (coord_x,coord_y );
        points.push_back(pt);

    }
    return points;
}

void mean_shift(vector<Point> &points, vector<Point> &centroids, int lambda, bool &isShifting){

    unsigned long points_size = points.size();
    double distance;
    for (int i = 0; i < points_size; i++) {
        float new_coord_x = 0.0;
        float new_coord_y = 0.0;
        float weight = 0.0;

        for (int j = 0; j < points_size; j++) {
            distance = sqrt( pow(points[j].get_coord_x()-points[j].get_coord_y(),2)+pow(points[i].get_coord_x()-points[i].get_coord_y(),2));
            if(distance<lambda){
                isShifting = true;
                new_coord_x += points[j].get_coord_x();
                new_coord_y += points[j].get_coord_y();
                weight += 1;
            }
        }
        new_coord_x /= weight;
        new_coord_y /= weight;
        centroids[i].set_coord_x(new_coord_x);
        centroids[i].set_coord_y(new_coord_y);
        }


}

//Draw point plot with gnuplot
void draw_chart_gnu(vector<Point> &points){

    ofstream outfile("data.txt");

    for(int i = 0; i < points.size(); i++){

        Point point = points[i];
        outfile << point.get_coord_x() << " " << point.get_coord_y()  << std::endl;

    }

    outfile.close();
    system("gnuplot -p -e \"plot 'data.txt' using 1:2:3 with points palette notitle\"");
    remove("data.txt");

}
