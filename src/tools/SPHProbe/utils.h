#ifndef SRC_TOOLS_UTILS_H
#define SRC_TOOLS_UTILS_H
#include <fstream>
#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace blast = boost::numeric::ublas;

std::vector<double> readRow(std::string row);
std::vector<std::vector<double> > readVector(std::istream &is);
blast::matrix<double> readMatrix(const std::string& filename );
#endif //SRC_TOOLS_UTILS_H