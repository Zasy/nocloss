/*********************************************************************************
 *
 * File name:		defination.h
 * Class name:		N/A
 * Version:			1.0
 *
 * Software:		Optical Thermal Effect Modeling Platform
 * Authors:			Yaoyao Ye, Zhehui Wang, Jiang Xu, Xiaowen Wu, Xuan Wang, Mahdi Nikdast, Zhe Wang, and Luan Duong
 *					
 * Website:			http://www.ece.ust.hk/~eexu
 *
 * The copyright information of this program can be found in the file COPYRIGHT.
 *
 *********************************************************************************/
#ifndef defination
#define defination

#include <complex> 
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;

#define PI 3.1415926

//////////////////////////////////////////////////////////////////////
//    "parameter.txt" gives parameters used in the thermal modeling //
//////////////////////////////////////////////////////////////////////

//Initial the lambda_MR_0_new
double lambda_MR_0_new;  //lambda_MR_0 for test
double row_MR;	//the temeprature-dependent wavelength shift of MR, in nm per degree

double T_0;	//room temperature
double lambda_VCSEL_0;	//VCSEL wavelength at room temperature
double row_VCSEL; //the temeprature-dependent wavelength shift of VCSEL, in nm per degree
double delta;
double lambda_b;
double L_crossing = 0.12;
double lambda_VCSEL_new(double T) {
	return (lambda_VCSEL_0 + row_VCSEL*(T - T_0));//on-chip VCSEL, the wavelength at temperature T, increases linearly with temperature
}

double lambda_MR_new(double T){
	return (lambda_MR_0_new + row_MR*(T - T_0));
}

double lambda_MR_parking(double T){
	return (lambda_MR_0_new + lambda_b + row_MR*(T - T_0));
}

// new test for delta
double Delta_lambda_new(double T_src, double T_mid){
	return (lambda_VCSEL_new(T_src) - lambda_MR_new(T_mid));
}

double Delta_lambda_parking(double T_src, double T_mid){
	return (lambda_VCSEL_new(T_src) - lambda_MR_parking(T_mid));
}

//new test for l_sw
double L_SW_new(double T_src, double T_mid){
	return (10 * log10(1 + pow(Delta_lambda_new(T_src, T_mid)/delta, 2)));
}

double L_SW_active(double T_src, double T_mid){
	return (10 * log10(1 + pow(Delta_lambda_new(T_src, T_mid) / delta, 2)));
}

double L_SW_parking(double T_src, double T_mid){
	return (10 * log10(1 + pow(delta / Delta_lambda_parking(T_src, T_mid), 2)));
}



double chip_temp[] = {
	47.4059, 40.7129, 44.7921, 48.6436, 44.9505, 45.4851, 47.505, 41.6238, 42.6535, 46.7921, 44.703, 43.6337, 42.8911, 46.4851, 45.2277, 46.9307, 48.2475, 42.505, 49.1287, 44.6634, 41.1881, 43.1188, 44.9802, 41.9109, 48.7327, 44.9406, 47.3861, 49.3861, 41.3663, 48.5644, 45.9406, 42.703, 46.8515, 42.505, 48.7327, 45.7426, 49.3267, 40.2871, 41.5743, 48.5149, 43.3465, 44.4554, 40.703, 46.1683, 48.9307, 49.7624, 43.8218, 48.8218, 42.5842, 41.0198, 45.8515, 48.9307, 40.7921, 46.3861, 46.5941, 45.7129, 42.5743, 49.0792, 43.1188, 42.4653, 40.4851, 46.703, 47.3366, 44.2079, 42.9109, 40.7921, 44.7327, 40.2772, 41.9901, 47.2871
};

int crossing_number[5][5] = {
	{ 0, 4, 0, 2, 2 },
	{ 4, 0, 6, 0, 6 },
	{ 4, 4, 0, 4, 0 },
	{ 2, 3, 4, 0, 6 },
	{ 4, 2, 3, 4, 0 } };

int active_number[5][5] = { { 0, 1, 1, 1, 1 },
{ 1, 0, 0, 1, 1 },
{ 1, 0, 0, 1, 1 },
{ 1, 1, 1, 0, 0 },
{ 1, 1, 1, 0, 0 } };

int passive_number[5][5] = { { 0, 3, 0, 2, 2 },
{ 2, 0, 6, 1, 4 },
{ 3, 6, 0, 4, 0 },
{ 0, 2, 4, 0, 6 },
{ 3, 4, 2, 6, 0 } };







#endif
