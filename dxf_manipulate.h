#ifndef DXF_MANIPULATE_H_INCLUDED
#define DXF_MANIPULATE_H_INCLUDED
#include "svg_gen.h"

class dxf_manipulate
{
    public:
    dxf_manipulate(svg_gen *svg);
    svg_gen *svg=NULL; ///чтобы можно было подцепить без прямого наследования
    void rotate_dxf(data_vectors vec, double angle);//0-360
    void dxf_write(char* filename_with_path);
    void mirror_x(void);
    void mirror_y(void);
    private:
    void normalize_dxf(void); ///чтобы dxf встало в координаты x=0, y=0
    void normalize_all_lines(void);
    void normalize_all_arcs(void);
    void normalize_all_circles(void);
    void normalize_all_polylines(void);
    void normalize_all_ellipses(void);
    void normalize_all_splines(void);

    void write_all_lines(data_vectors vec, DL_Dxf* dxf, DL_WriterA* dw, char *layername, bool need_normalize);
    void write_all_arcs(data_vectors vec, DL_Dxf* dxf, DL_WriterA* dw, char *layername, bool need_normalize);
    void write_all_cirles(data_vectors vec, DL_Dxf* dxf, DL_WriterA* dw, char *layername, bool need_normalize);
    void write_all_polylines(data_vectors vec, DL_Dxf* dxf, DL_WriterA* dw, char *layername, bool need_normalize);
    void write_all_ellipses(data_vectors vec, DL_Dxf* dxf, DL_WriterA* dw, char *layername, bool need_normalize);
    void write_all_splines(data_vectors vec, DL_Dxf* dxf, DL_WriterA* dw, char *layername, bool need_normalize);
    point rotate_point(double x, double y, double cx, double cy, double angle);
    void rotate_all_lines(data_vectors vec, double cx, double cy, double angle);
    void rotate_all_arcs(data_vectors vec, double cx, double cy, double angle);
    void rotate_all_circles(data_vectors vec, double cx, double cy, double angle);
    void rotate_all_polylines(data_vectors vec, double cx, double cy, double angle);
    void rotate_all_ellipses(data_vectors vec, double cx, double cy, double angle);
    void rotate_all_splines(data_vectors vec, double cx, double cy, double angle);


};


#endif // DXF_MANIPULATE_H_INCLUDED
