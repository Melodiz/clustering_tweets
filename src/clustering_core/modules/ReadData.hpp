#include "../include/npy.hpp"// https://github.com/llohse/libnpy
#include "structPoint.hpp"     // implementation of Point structure
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<Point> read_data(std::string path);
std::vector<Point> read_from_csv(std::string path);
std::vector<Point> read_from_txt(std::string path);
std::vector<Point> read_from_npy(std::string path);
std::vector<Point> read_data(std::string path)
{
    // Determine the file type based on its extension
    std::string extension = path.substr(path.size() - 4);

    std::cout << "Reading data...";

    if (extension == ".csv") { return read_from_csv(path); }
    if (extension == ".txt") { return read_from_txt(path); }
    if (extension == ".npy") { return read_from_npy(path); }

    else
    {
        std::cout << "File type for row points not supported" << std::endl;
        std::cout << "Supported file types: csv, npy, txt" << std::endl;
        exit(1);
    }
    std::cout << "done" << std::endl;
}

std::vector<Point> read_from_csv(std::string path)
{
    std::vector<Point> points;
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cout << "File " << path << " not found" << std::endl;
        exit(1);
    }
    std::string line;
    std::getline(file, line);// Skip the header line

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<double> values;
        std::string value;
        while (std::getline(iss, value, ','))
        {
            values.push_back(std::stod(value));
        }
        points.push_back(Point(values));// Assuming Point constructor can take a vector<double> for N-dimensional points
    }
    file.close();
    return points;
}

std::vector<Point> read_from_txt(std::string path)
{
    std::vector<Point> points;
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cout << "File " << path << " not found" << std::endl;
        exit(1);
    }
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<double> values;
        std::string value;
        while (std::getline(iss, value, ','))
        {
            values.push_back(std::stod(value));
        }
        points.push_back(Point(values));// Assuming Point constructor can take a vector<double> for N-dimensional points
    }
    file.close();
    return points;
}

std::vector<Point> read_from_npy(std::string path)
{
    std::vector<Point> points;
    npy::npy_data file = npy::read_npy<double>(path);

    for (int i = 0; i < file.shape[0]; i++)
    {
        std::vector<double> values;
        for (int j = 0; j < file.shape[1]; j++)
        {
            values.push_back(file.data[i * file.shape[1] + j]);
        }
        points.push_back(Point(values));// Assuming Point constructor can take a vector<double> for N-dimensional points
    }
    return points;
}
