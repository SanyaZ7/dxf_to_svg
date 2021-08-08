#ifndef DATA_VECTRORS_H_INCLUDED
#define DATA_VECTRORS_H_INCLUDED

#include <string>
using namespace std;

#include <dl_creationadapter.h>

typedef struct
{
    unsigned int groupCode;
    string groupValue;
}CodeValuePair;
typedef struct
{
    double x;
    double y;
} point;

class data_vectors
{
    public:
    ~data_vectors();
    bool is_block=false; ///нужно для того, чтобы создать std::map таблицу с типом и номером примитивов, входящих в блок
    int number_of_vertex_in_polyline=0;
    int number_of_vertex_in_spline=0;
    int number_of_knots_in_spline=0;
    int spline_degree=0;
    vector<vector<point>> polyline_matrix;
    vector<vector<point>> spline_points;
    vector<vector<double>> spline_knots;
    vector<DL_SplineData> splines;
    vector<DL_LayerData> DL_LayerData_vector;
    vector<DL_LinetypeData> DL_LinetypeData_vector;
    //vector<double> LinetypeDash_vector;
    vector<DL_BlockData> DL_BlockData_vector;

    vector<DL_StyleData> DL_StyleData_vector;
    //vector<DL_PointData> DL_PointData_vector;
    vector<DL_LineData> DL_LineData_vector;
    //vector<DL_XLineData> DL_XLineData_vector;
    //vector<DL_RayData> DL_RayData_vector;

    vector<DL_ArcData> DL_ArcData_vector;
    vector<DL_CircleData> DL_CircleData_vector;
    vector<DL_EllipseData> DL_EllipseData_vector;

    //vector<DL_PolylineData> DL_PolylineData_vector;
    //vector<DL_VertexData> DL_VertexData_vector;

    //vector<DL_SplineData> DL_SplineData_vector;
    //vector<DL_ControlPointData> DL_ControlPointData_vector;
    //vector<DL_FitPointData> DL_FitPointData_vector;
    //vector<DL_KnotData> DL_KnotData_vector;

    //vector<DL_InsertData> DL_InsertData_vector;

    //vector<DL_MTextData> DL_MTextData_vector;
    //vector<string> MTextChunk_vector;
    //vector<DL_TextData> DL_TextData_vector;
    //vector<DL_ArcAlignedTextData> DL_ArcAlignedTextData_vector;
    //vector<DL_AttributeData> DL_AttributeData_vector;
   // vector<string> str;
};


#endif // DATA_VECTRORS_H_INCLUDED
