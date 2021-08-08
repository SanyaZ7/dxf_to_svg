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
}line;

class svg_gen : public dxf_filter, public stats
{
    public:
    DL_Dxf dxf;

    string resulting_svg;
    svg_gen();
    void svg_generate(void);
    private:
    void generate_lines(double x_min, double y_max);
    void generate_arcs(double x_min, double y_max);
    void generate_circles(double x_min, double y_max);
    void generate_polyline(double x_min, double y_max);
    void generate_ellipse(double x_min, double y_max);
    void generate_spline(double x_min, double y_max);
    void spline_points_and_knots_degree2(vector<point> pt, vector<double> k, double x_min, double y_max);
    line dxf_min_max_values(double &x_min, double &x_max, double &y_min, double &y_max);
    string solve_quadratic_beizer(vector<point> pt);
};

#endif // SVG_GEN_H_INCLUDED
