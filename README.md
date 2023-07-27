#Meanshift Clustering Algorithm
This repository contains implementations of the Meanshift clustering algorithm in three different versions: sequential, parallel using Array of Structures (AoS), and parallel using Structure of Arrays (SoA) with OpenMP.

#What is Meanshift Clustering?
Meanshift is a popular unsupervised learning algorithm used for clustering data points in a high-dimensional feature space. It aims to find the modes or centroids of a probability density function, which effectively represent the clusters in the data.

#Implementations
1. Sequential Version
The sequential version of the Meanshift algorithm is implemented in C++. It follows the basic principles of the algorithm and iteratively shifts data points towards the direction of the maximum increase in density. The main loop performs clustering until convergence.

2. Parallel Version using Array of Structures (AoS)
The parallel version of the Meanshift algorithm using Array of Structures (AoS) is implemented in C++ with the help of OpenMP. This approach uses parallelism to speed up the computation of the clustering process. The points are organized in an array of structures, and multiple threads work on different points simultaneously to achieve parallel processing.

3. Parallel Version using Structure of Arrays (SoA)
The parallel version of the Meanshift algorithm using Structure of Arrays (SoA) is another approach implemented in C++ with OpenMP. In this implementation, data points are organized into separate arrays based on attributes, and each thread works on a specific attribute independently. This can provide better performance in certain scenarios, especially for large datasets and optimized memory access.

#How to Use
To run the implementations, you need to compile the C++ code with OpenMP support. Make sure you have a compatible C++ compiler and OpenMP installed on your system.

Sequential Version: Compile the MeanshiftSequential.cpp file and run the executable. It will perform the clustering sequentially.

Parallel Version using AoS: Compile the MeanshiftOpenMP_AoS.cpp file with OpenMP support and run the executable. It will utilize multiple threads to achieve parallel processing.

Parallel Version using SoA: Compile the MeanshiftOpenMP_SoA.cpp file with OpenMP support and run the executable. It will use a different approach for parallelization with SoA data structure.

#Dataset
You can provide your own dataset in a CSV file format, where each row represents a data point with its features. The code will read the dataset from the CSV file and perform the clustering accordingly.

#Contributing
Contributions to this repository are welcome! If you find any issues, have suggestions for improvements, or want to add more parallelization techniques, feel free to open a pull request.

#Acknowledgments
The implementation of the Meanshift algorithm is inspired by academic papers and existing implementations. We acknowledge the contributions of researchers in the field and the resources available online that have been used to develop this project.
