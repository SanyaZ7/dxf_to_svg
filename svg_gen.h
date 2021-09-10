#ifndef SVG_GEN_H_INCLUDED
#define SVG_GEN_H_INCLUDED

#include "dxf_filter.h"
#include <dl_dxf.h>

#include <string>

using namespace std;
typedef struct
{
    point min_;
    point max_;
}range;

class svg_gen : public dxf_filter, public stats
{
    public:
    range dxf_range={{100000,100000},{-100000,-100000}};
    DL_Dxf dxf;
    string resulting_svg;
    svg_gen();
    void svg_generate(char *filename);
    range min_max_values(data_vectors vec, double &x_min, double &x_max, double &y_min, double &y_max);
    void min_max_values(data_vectors vec);
    private:
    void generate_lines(data_vectors vec, double x_min, double y_max);
    void generate_arcs(data_vectors vec, double x_min, double y_max);
    void generate_circles(data_vectors vec, double x_min, double y_max);
    void generate_polyline(data_vectors vec, double x_min, double y_max);
    void generate_ellipse(data_vectors vec, double x_min, double y_max);
    void generate_spline(data_vectors vec, double x_min, double y_max);
    void spline_points_and_knots_degree2(vector<point> pt, vector<double> k, double x_min, double y_max);
    string solve_quadratic_beizer(vector<point> pt);
};

#endif // SVG_GEN_H_INCLUDED
