#pragma once
#include "../include/npy.hpp"// https://github.com/llohse/libnpy
#include "structPoint.hpp"     // implementation of Point structure
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * Saves clustering results to a CSV file.
 * 
 * @param _resultPath Path to the output CSV file.
 * @param _points Vector of Point objects representing the data points.
 * @param _centroids Vector of Point objects representing the centroids.
 * @param _with_coordinates If true, coordinates of each point are included in the output.
 */
void save_result_to_csv(const std::string& _resultPath, const std::vector<Point>& _points, const std::vector<Point>& _centroids, bool _with_coordinates);

/**
 * Saves clustering results to a TXT file.
 * 
 * @param _resultPath Path to the output TXT file.
 * @param _points Vector of Point objects representing the data points.
 * @param _centroids Vector of Point objects representing the centroids.
 * @param _with_coordinates If true, coordinates of each point are included in the output. Defaults to false.
 * 
 * @return void
 */
void save_result_to_txt(const std::string& _resultPath, const std::vector<Point>& _points, const std::vector<Point>& _centroids, bool _with_coordinates);

/**
 * Saves clustering results to an NPY file.
 * 
 * @param _resultPath Path to the output NPY file.
 * @param _points Vector of Point objects representing the data points.
 * @param _centroids Vector of Point objects representing the centroids.
 * @param _with_coordinates If true, coordinates of each point are included in the output.
 */
void save_result_to_npy(const std::string& _resultPath, const std::vector<Point>& _points, const std::vector<Point>& _centroids, bool _with_coordinates);

/**
 * Saves centroids to a CSV file.
 * 
 * @param _resultPath Path to the output CSV file.
 * @param _centroids Vector of Point objects representing the centroids.
 */
void save_centroids_to_csv(const std::string& _resultPath, const std::vector<Point>& _centroids);

/**
 * Saves centroids to an NPY file.
 * 
 * @param _resultPath Path to the output NPY file.
 * @param _centroids Vector of Point objects representing the centroids.
 */
void save_centroids_to_npy(const std::string& _resultPath, const std::vector<Point>& _centroids);

/**
 * Saves centroids to a TXT file.
 * 
 * @param _resultPath Path to the output TXT file.
 * @param _centroids Vector of Point objects representing the centroids.
 */
void save_centroids_to_txt(const std::string& _resultPath, const std::vector<Point>& _centroids);

/**
 * Determines the file type based on its extension and calls the appropriate function to save clustering results.
 * 
 * @param _resultPath Path to the output file.
 * @param _points Vector of Point objects representing the data points.
 * @param _centroids Vector of Point objects representing the centroids.
 * @param _with_coordinates If true, coordinates of each point are included in the output. Defaults to false.
 */
void save_result(const std::string& _resultPath, const std::vector<Point>& _points, const std::vector<Point>& _centroids, bool _with_coordinates);

/**
 * Determines the file type based on its extension and calls the appropriate function to save centroids.
 * 
 * @param _resultPath Path to the output file.
 * @param _centroids Vector of Point objects representing the centroids.
 */
void save_centroids(std::string _resultPath, const std::vector<Point>& _centroids);


void save_result(const std::string& _resultPath, const std::vector<Point>& _points, const std::vector<Point>& _centroids, bool _with_coordinates = false)
{
    // Determine the file type based on its extension
    std::string extension = _resultPath.substr(_resultPath.size() - 4);
    if (extension == ".csv") { save_result_to_csv(_resultPath, _points, _centroids, _with_coordinates); }
    else if (extension == ".txt") { save_result_to_txt(_resultPath, _points, _centroids, _with_coordinates); }
    else if (extension == ".npy") { save_result_to_npy(_resultPath, _points, _centroids, _with_coordinates); }

    else
    {
        std::cout << "File type for result not supported" << std::endl;
        std::cout << "Supported file types: csv, npy, txt" << std::endl;
        exit(1);
    }
}

void save_centroids(std::string _resultPath, const std::vector<Point>& _centroids)
{
    // Determine the file type based on its extension
    std::string extension = _resultPath.substr(_resultPath.size() - 4);

    std::cout << "Writing centroids...";

    // Write data to a CSV file
    if (extension == ".csv") { save_centroids_to_csv(_resultPath, _centroids); }
    else if (extension == ".npy") { save_centroids_to_npy(_resultPath, _centroids); }
    else if (extension == ".txt") { save_centroids_to_txt(_resultPath, _centroids); }
    else
    {
        std::cout << "File type for clusters not supported" << std::endl;
        std::cout << "Supported file types: csv, npy, txt" << std::endl;
        exit(1);
    }
    std::cout << "done" << std::endl;
}

void save_result_to_csv(const std::string& _resultPath, const std::vector<Point>& _points, const std::vector<Point>& _centroids, bool _with_coordinates = false)
{
    std::ofstream file(_resultPath);
    if (!file.is_open())
    {
        std::cout << "Saving error" << std::endl;
        exit(1);
    }
    // with coordinates
    if (_with_coordinates)
    {
        // save headers
        file << "cluster_id,distance,";
        for (int i = 0; i < _points[0].coords.size(); i++)
        {
            file << "x" << i << ",";
        }
        file << std::endl;

        // save data
        for (int i = 0; i < _points.size(); i++)
        {
            file << _points[i].cluster_id << "," << _points[i].distance << ",";
            for (int j = 0; j < _points[i].coords.size(); j++)
            {
                file << _points[i].coords[j] << ",";
            }
            file << std::endl;
        }
        file.close();
    }
    // without coordinates
    else
    {
        // save headers
        file << "cluster_id,distance" << std::endl;

        // save data
        for (int i = 0; i < _points.size(); i++)
        {
            file << _points[i].cluster_id << "," << _points[i].distance << std::endl;
        }
        file.close();
    }
}

void save_centroids_to_csv(const std::string& _resultPath, const std::vector<Point>& _centroids)
{
    std::ofstream file(_resultPath);
    if (!file.is_open())
    {
        std::cout << "Saving error" << std::endl;
        exit(1);
    }
    // save headers
    file << "cluster_id,distance,";
    for (int i = 0; i < _centroids[0].coords.size(); i++)
    {
        file << "x" << i << ",";
    }
    file << std::endl;

    // save data
    for (int i = 0; i < _centroids.size(); i++)
    {
        file << _centroids[i].cluster_id << "," << _centroids[i].distance << ",";
        for (int j = 0; j < _centroids[i].coords.size(); j++)
        {
            file << _centroids[i].coords[j] << ",";
        }
        file << std::endl;
    }
    file.close();
}

void save_result_to_txt(const std::string& _resultPath, const std::vector<Point>& _points, const std::vector<Point>& _centroids, bool _with_coordinates = false)
{
    if (_with_coordinates)
    {
        // open file
        std::ofstream file(_resultPath);
        if (!file.is_open())
        {
            std::cout << "Saving error" << std::endl;
            exit(1);
        }
        // save headers
        file << "cluster_id,distance,";
        for (int i = 0; i < _points[0].coords.size(); i++)
        {
            file << "x" << i << ",";
        }
        file << std::endl;

        // save data
        for (int i = 0; i < _points.size(); i++)
        {
            file << _points[i].cluster_id << "," << _points[i].distance << ",";
            for (int j = 0; j < _points[i].coords.size(); j++)
            {
                file << _points[i].coords[j] << ",";
            }
            file << std::endl;
        }
        file.close();
    }
    // without coordinates
    else
    {
        // open file
        std::ofstream file(_resultPath);
        if (!file.is_open())
        {
            std::cout << "Saving error" << std::endl;
            exit(1);
        }
        // save headers
        file << "cluster_id,distance" << std::endl;

        // save data
        for (int i = 0; i < _points.size(); i++)
        {
            file << _points[i].cluster_id << "," << _points[i].distance << std::endl;
        }
        file.close();
    }
}

void save_centroids_to_txt(const std::string& _resultPath, const std::vector<Point>& _centroids)
{
    // open file
    std::ofstream file(_resultPath);
    if (!file.is_open())
    {
        std::cout << "Saving error" << std::endl;
        exit(1);
    }

    // save headers
    file << "cluster_id,distance,";
    for (int i = 0; i < _centroids[0].coords.size(); i++)
    {
        file << "x" << i << ",";
    }
    file << std::endl;

    // save data
    for (int i = 0; i < _centroids.size(); i++)
    {
        file << _centroids[i].cluster_id << "," << _centroids[i].distance << ",";
        for (int j = 0; j < _centroids[i].coords.size(); j++)
        {
            file << _centroids[i].coords[j] << ",";
        }
        file << std::endl;
    }
    file.close();
}

void save_result_to_npy(const std::string& _resultPath, const std::vector<Point>& _points, const std::vector<Point>& _centroids, bool _with_coordinates = false)
{
    // with coordinates
    if (_with_coordinates)
    {
        // open file
        npy::npy_data file = npy::read_npy<double>(_resultPath);
        for (int i = 0; i < _centroids.size(); i++)
        {
            file.data[i * file.shape[1] + 0] = _centroids[i].cluster_id;
            file.data[i * file.shape[1] + 1] = _centroids[i].distance;
            for (int j = 0; j < _centroids[i].coords.size(); j++)
            {
                file.data[i * file.shape[1] + 2 + j] = _centroids[i].coords[j];
            }
        }
        npy::write_npy(_resultPath, file);
    }
    // without coordinates
    else
    {
        // open file
        npy::npy_data file = npy::read_npy<double>(_resultPath);

        // save data without headers
        for (int i = 0; i < _centroids.size(); i++)
        {
            file.data[i * file.shape[1] + 0] = _centroids[i].cluster_id;
            file.data[i * file.shape[1] + 1] = _centroids[i].distance;
        }
        npy::write_npy(_resultPath, file);
    }
}

void save_centroids_to_npy(const std::string& _resultPath, const std::vector<Point>& _centroids)
{
    // open file
    npy::npy_data file = npy::read_npy<double>(_resultPath);
    // save data
    for (int i = 0; i < _centroids.size(); i++)
    {
        file.data[i * file.shape[1] + 0] = _centroids[i].cluster_id;
        file.data[i * file.shape[1] + 1] = _centroids[i].distance;
        for (int j = 0; j < _centroids[i].coords.size(); j++)
        {
            file.data[i * file.shape[1] + j + 2] = _centroids[i].coords[j];
        }
    }
    npy::write_npy(_resultPath, file);
}