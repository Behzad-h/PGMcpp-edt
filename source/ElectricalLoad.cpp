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
/// \file ElectricalLoad.cpp
///
/// \brief Implementation file for the ElectricalLoad class.
///
/// A class which contains time and electrical load data. Intended to serve as a
/// component class of Model.
///


#include "../header/ElectricalLoad.h"


// ======== PUBLIC ================================================================== //

// ---------------------------------------------------------------------------------- //

///
/// \fn ElectricalLoad :: ElectricalLoad(void)
///
/// \brief Constructor (dummy) for the ElectricalLoad class.
///

ElectricalLoad :: ElectricalLoad(void)
{
    return;
}   /* ElectricalLoad() */

// ---------------------------------------------------------------------------------- //



// ---------------------------------------------------------------------------------- //

///
/// \fn ElectricalLoad :: ElectricalLoad(std::string path_2_electrical_load_time_series)
///
/// \brief Constructor (intended) for the ElectricalLoad class.
///
/// \param path_2_electrical_load_time_series A string defining the path (either
///     relative or absolute) to the given electrical load time series.
///

ElectricalLoad :: ElectricalLoad(std::string path_2_electrical_load_time_series)
{
    this->readLoadData(path_2_electrical_load_time_series);
    
    return;
}   /* ElectricalLoad() */

// ---------------------------------------------------------------------------------- //


// ---------------------------------------------------------------------------------- //

///
/// \fn void ElectricalLoad :: readLoadData(std::string path_2_electrical_load_time_series)
///
/// \brief Method to read electrical load data into an already existing ElectricalLoad
///     object. Clears and overwrites any existing attribute values.
///
/// \param path_2_electrical_load_time_series A string defining the path (either
///     relative or absolute) to the given electrical load time series.
///

void ElectricalLoad :: readLoadData(std::string path_2_electrical_load_time_series)
{
    //  1. clear
    this->clear();
    
    //  2. init CSV reader, record path
    io::CSVReader<2> CSV(path_2_electrical_load_time_series);
    
    CSV.read_header(
        io::ignore_extra_column,
        "Time (since start of data) [hrs]",
        "Electrical Load [kW]"
    );
    
    this->path_2_electrical_load_time_series = path_2_electrical_load_time_series;
    
    //  3. read in time and load data, increment n_points, track min and max load
    double time_hrs = 0;
    double load_kW = 0;
    double load_sum_kW = 0;
    
    this->n_points = 0;
    
    this->min_load_kW = std::numeric_limits<double>::infinity();
    this->max_load_kW = -1 * std::numeric_limits<double>::infinity();
    
    while (CSV.read_row(time_hrs, load_kW)) {
        this->time_vec_hrs.push_back(time_hrs);
        this->load_vec_kW.push_back(load_kW);
        
        load_sum_kW += load_kW;
        
        this->n_points++;
        
        if (this->min_load_kW > load_kW) {
            this->min_load_kW = load_kW;
        }
        
        if (this->max_load_kW < load_kW) {
            this->max_load_kW = load_kW;
        }
    }
    
    //  4. compute mean load
    this->mean_load_kW = load_sum_kW / this->n_points;
    
    //  5. set number of years (assuming 8,760 hours per year)
    this->n_years = this->time_vec_hrs[this->n_points - 1] / 8760;
    
    //  6. populate dt_vec_hrs
    this->dt_vec_hrs.resize(n_points, 0);
    
    for (int i = 0; i < n_points; i++) {
        if (i == n_points - 1) {
            this->dt_vec_hrs[i] = this->dt_vec_hrs[i - 1];
        }
        
        else {
            double dt_hrs = this->time_vec_hrs[i + 1] - this->time_vec_hrs[i];
            
            this->dt_vec_hrs[i] = dt_hrs;
        }
    }
    
    return;
}   /* readLoadData() */

// ---------------------------------------------------------------------------------- //


// ---------------------------------------------------------------------------------- //

///
/// \fn void ElectricalLoad :: clear(void)
///
/// \brief Method to clear all attributes of the ElectricalLoad object.
///

void ElectricalLoad :: clear(void)
{
    this->n_points = 0;
    this->n_years = 0;
    this->min_load_kW = 0;
    this->mean_load_kW = 0;
    this->max_load_kW = 0;
    
    this->path_2_electrical_load_time_series.clear();
    this->time_vec_hrs.clear();
    this->dt_vec_hrs.clear();
    this->load_vec_kW.clear();
    
    return;
}   /* clear() */

// ---------------------------------------------------------------------------------- //


// ---------------------------------------------------------------------------------- //

///
/// \fn ElectricalLoad :: ~ElectricalLoad(void)
///
/// \brief Destructor for the ElectricalLoad class.
///

ElectricalLoad :: ~ElectricalLoad(void)
{
    this->clear();
    return;
}   /* ~ElectricalLoad() */

// ---------------------------------------------------------------------------------- //

// ======== END PUBLIC ============================================================== //
