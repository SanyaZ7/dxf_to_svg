#ifndef DXF_FILTER_H_INCLUDED
#define DXF_FILTER_H_INCLUDED

#include "data_vectrors.h"
#include "stats.hpp"

class dxf_filter : public DL_CreationAdapter//, public data_vectors
{
    public:
    ~dxf_filter()
    {
        DL_BlockData_vector.clear();
    }
    dxf_filter *dxf_filter=this;
    dxf_handler_funcions func_bit_flags={0};
    vector<DL_BlockData> DL_BlockData_vector;
    vector<data_vectors> DL_Block; ///данные в блоках
    data_vectors common;
    char *is_block=nullptr; ///название блока, если не равно нулю
    //int number_of_vertex_in_polyline=0; ///

    void processCodeValuePair(unsigned int groupCode, const std::string& groupValue);
    void endSection();
    void addLayer(const DL_LayerData& data);
    void addLinetype(const DL_LinetypeData& data);
    void addLinetypeDash(double length);
    void addBlock(const DL_BlockData& data);///++
    void endBlock();
    void addTextStyle(const DL_StyleData& data);
    void addPoint(const DL_PointData& data);
    void addLine(const DL_LineData& data); ///++
    void addXLine(const DL_XLineData& data);
    void addRay(const DL_RayData& data);

    void addArc(const DL_ArcData& arcdata);
    void addCircle(const DL_CircleData& circle);
    void addEllipse(const DL_EllipseData& ellipse);

    void addPolyline(const DL_PolylineData& polyline);
    void addVertex(const DL_VertexData& vertex);

    void addSpline(const DL_SplineData& spline);
    void addControlPoint(const DL_ControlPointData& control_point);
    void addFitPoint(const DL_FitPointData& fitpoint);
    void addKnot(const DL_KnotData& knot);

    void addInsert(const DL_InsertData& data);

    void addTrace(const DL_TraceData& data);
    void add3dFace(const DL_3dFaceData& data);
    void addSolid(const DL_SolidData& data);

    void addMText(const DL_MTextData& data);
    void addMTextChunk(const std::string& text);
    void addText(const DL_TextData& data);
    void addArcAlignedText(const DL_ArcAlignedTextData& data);
    void addAttribute(const DL_AttributeData& data);

    void addDimAlign(const DL_DimensionData& data, const DL_DimAlignedData& edata);
    void addDimLinear(const DL_DimensionData& data, const DL_DimLinearData& edata);
    void addDimRadial(const DL_DimensionData& data, const DL_DimRadialData& edata);
    void addDimDiametric(const DL_DimensionData& data, const DL_DimDiametricData& edata);
    void addDimAngular(const DL_DimensionData& data, const DL_DimAngularData& edata);
    void addDimAngular3P(const DL_DimensionData& data, const DL_DimAngular3PData& edata);
    void addDimOrdinate(const DL_DimensionData& data, const DL_DimOrdinateData& edata);
    void addLeader(const DL_LeaderData& data);
    void addLeaderVertex(const DL_LeaderVertexData& data);

    void addHatch(const DL_HatchData& data);

    void addImage(const DL_ImageData& data);
    void linkImage(const DL_ImageDefData& data);
    void addHatchLoop(const DL_HatchLoopData& data);
    void addHatchEdge(const DL_HatchEdgeData& data);

    void addXRecord(const std::string& handle);
    void addXRecordString(int code, const std::string& value);
    void addXRecordReal(int code, double value);
    void addXRecordInt(int code, int value);
    void addXRecordBool(int code, bool value);

    void addXDataApp(const std::string& appId);
    void addXDataString(int code, const std::string& value);
    void addXDataReal(int code, double value);
    void addXDataInt(int code, int value);

    void addDictionary(const DL_DictionaryData& data);
    void addDictionaryEntry(const DL_DictionaryEntryData& data);

    void endEntity();

    void addComment(const std::string& comment);

    void setVariableVector(const std::string& key,  double v1, double v2, double v3, int code);
    void setVariableString(const std::string& key, const std::string& value, int code);
    void setVariableInt(const std::string& key, int value, int code);
    void setVariableDouble(const std::string& key, double value, int code);

    void endSequence();
};


#endif // DXF_FILTER_H_INCLUDED
