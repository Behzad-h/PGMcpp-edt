/*
 *  PGMcpp : PRIMED Grid Modelling (in C++)
 *
 *  Anthony Truelove MASc, P.Eng.
 *  email:  gears1763@tutanota.com
 *  github: gears1763-2
 *
 *  See license terms
 *
 */


///
/// \file Interpolator.h
///
/// \brief Header file for the Interpolator class.
///


#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

// std and third-party
#include "std_includes.h"
#include "../third_party/fast-cpp-csv-parser/csv.h"


///
/// \struct InterpolatorStruct1D
///
/// \brief A struct which holds two parallel vectors for use in 1D interpolation.
///

struct InterpolatorStruct1D {
    int n_points = 0; ///< The number of data points in each parallel vector
    
    std::vector<double> x_vec = {}; ///< A vector of independent data.
    
    double min_x = 0; ///< The minimum (i.e., first) element of x_vec.
    double max_x = 0; ///< The maximum (i.e., last) element of x_vec.
    
    std::vector<double> y_vec = {}; ///< A vector of dependent data.
};


///
/// \struct InterpolatorStruct2D
///
/// \brief A struct which holds two parallel vectors and a matrix for use in 2D 
///     interpolation.
///

struct InterpolatorStruct2D {
    int n_rows = 0; ///< The number of rows in the matrix (also the length of y_vec)
    int n_cols = 0; ///< The number of cols in the matrix (also the length of x_vec)
    
    std::vector<double> x_vec = {}; ///< A vector of independent data (columns).
    
    double min_x = 0; ///< The minimum (i.e., first) element of x_vec.
    double max_x = 0; ///< The maximum (i.e., last) element of x_vec.
    
    std::vector<double> y_vec = {}; ///< A vector of independent data (rows).
    
    double min_y = 0; ///< The minimum (i.e., first) element of y_vec.
    double max_y = 0; ///< The maximum (i.e., last) element of y_vec.
    
    std::vector<std::vector<double>> z_matrix = {}; ///< A matrix of dependent data.
};


///
/// \class Interpolator
///
/// \brief A class which contains interpolation data and functionality. Intended to
///     serve as a component of the Production and Storage hierarchies.
///

class Interpolator {
    private:
        //  1. attributes
        //...
        
        
        //  2. methods
        void __checkDataKey1D(int);
        void __checkDataKey2D(int);
        
        void __checkBounds1D(int, double);
        void __checkBounds2D(int, double, double);
        
        void __throwReadError(std::string, int);
        
        bool __isNonNumeric(std::string);
        
        int __getInterpolationIndex(double, std::vector<double>*);
        
        std::vector<std::string> __splitCommaSeparatedString(
            std::string,
            std::string = "||"
        );
        
        std::vector<std::vector<std::string>> __getDataStringMatrix(std::string);
        
        void __readData1D(int, std::string);
        void __readData2D(int, std::string);
        
        
    public:
        //  1. attributes
        std::map<int, InterpolatorStruct1D> interp_map_1D; ///< A map <int, InterpolatorStruct1D> of given 1D interpolation data.
        std::map<int, std::string> path_map_1D; ///< A map <int, string> of the paths (either relative or absolute) to the given 1D interpolation data.
        
        std::map<int, InterpolatorStruct2D> interp_map_2D; ///< A map <int, InterpolatorStruct2D> of given 2D interpolation data.
        std::map<int, std::string> path_map_2D; ///< A map <int, string> of the paths (either relative or absolute) to the given 2D interpolation data.
        
        
        //  2. methods
        Interpolator(void);
        
        void addData1D(int, std::string);
        void addData2D(int, std::string);
        
        double interp1D(int, double);
        double interp2D(int, double, double);
        
        ~Interpolator(void);
        
};  /* Interpolator */


#endif  /* INTERPOLATOR_H */
