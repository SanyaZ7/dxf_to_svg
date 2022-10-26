
#include "dxf_filter.h"

data_vectors::~data_vectors()
{
    DL_LayerData_vector.clear();
    DL_LinetypeData_vector.clear();
    //LinetypeDash_vector.clear();


    DL_StyleData_vector.clear();
    //DL_PointData_vector.clear();
    DL_LineData_vector.clear();
    //DL_XLineData_vector.clear();
    //DL_RayData_vector.clear();

    DL_ArcData_vector.clear();
    DL_CircleData_vector.clear();
    DL_EllipseData_vector.clear();
    spline_points.clear();
    polyline_points.clear();
    spline_knots.clear();

    DL_PolylineData_vector.clear();
   // DL_VertexData_vector.clear();

    DL_SplineData_vector.clear();
   // DL_ControlPointData_vector.clear();
    //DL_FitPointData_vector.clear();
    //DL_KnotData_vector.clear();

    //DL_InsertData_vector.clear();

    //DL_MTextData_vector.clear();
    //MTextChunk_vector.clear();
    //DL_TextData_vector.clear();
    //DL_ArcAlignedTextData_vector.clear();
    //DL_AttributeData_vector.clear();
}
