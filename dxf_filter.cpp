#include "dxf_filter.h"
#include <iostream>

/**
     * Called for every code / value tuple of the DXF file. The complete DXF file
     * contents can be handled by the implemetation of this function.
     */
void dxf_filter::processCodeValuePair(unsigned int groupCode, const std::string& groupValue) {func_bit_flags.processCodeValuePair=1;}
///Called when a section (entity, table entry, etc.) is finished.
void dxf_filter::endSection() { func_bit_flags.endSection=1;}
///Called for every layer.
void dxf_filter::addLayer(const DL_LayerData& data)
{
    func_bit_flags.addLayer=1;
    if(is_block==nullptr) {common.DL_LayerData_vector.emplace_back(data);}
    else {data_vectors *last=&(DL_Block.back()); last->DL_LayerData_vector.emplace_back(data);}
}
///Called for every linetype
void dxf_filter::addLinetype(const DL_LinetypeData& data)
{
    func_bit_flags.addLinetype=1;
    if(is_block){data_vectors *last=&(DL_Block.back()); last->DL_LinetypeData_vector.emplace_back(data);}
    else {common.DL_LinetypeData_vector.emplace_back(data);}
    //printf("LinetypeData=%s\n", data.description.c_str());
    //printf("Linetypedata=%d\n", data.numberOfDashes);
    //printf("Pattern=%f\n", data.patternLength);
    //printf("name=%s\n", data.name.c_str());
    //printf("name=%s\n", data.description.c_str());
}

///Called for every dash in linetype pattern
void dxf_filter::addLinetypeDash(double length)
{   func_bit_flags.addLinetypeDash=1;
    ///назначение не изучено
    //LinetypeDash_vector.emplace_back(length);
    //printf("addLinetypeDash=%f\n", length);
}

/**
     * Called for every block. Note: all entities added after this
     * command go into this block until endBlock() is called.
    *
     * @see endBlock()
     */
void dxf_filter::addBlock(const DL_BlockData& data)
{
    func_bit_flags.addBlock=1;
    DL_BlockData_vector.emplace_back(data);
    is_block=(char*)data.name.c_str();
    data_vectors data_;
    DL_Block.emplace_back(data_);
}
/** Called to end the current block */
void dxf_filter::endBlock() { func_bit_flags.endBlock=1; is_block=nullptr;}
/** Called for every text style */
void dxf_filter::addTextStyle(const DL_StyleData& data)
{
    func_bit_flags.addTextStyle=1;
    if(is_block) ///если данные входят в блок
    {data_vectors *last=&DL_Block.back(); last->DL_StyleData_vector.emplace_back(data);}
    else{common.DL_StyleData_vector.emplace_back(data);}
}

/** Called for every point */
void dxf_filter::addPoint(const DL_PointData& data) {func_bit_flags.addPoint=1;}

void dxf_filter::addLine(const DL_LineData& data)
{
    func_bit_flags.addLine=1;
    if(is_block)
    {data_vectors *last=&DL_Block.back(); last->DL_LineData_vector.emplace_back(data);}
    else {common.DL_LineData_vector.emplace_back(data);}
}
/** Called for every xline */
void dxf_filter::addXLine(const DL_XLineData& data){func_bit_flags.addXLine=1;}
/** Called for every ray */
void dxf_filter::addRay(const DL_RayData& data) {func_bit_flags.addRay=1;}
/** Called for every Arc */
void dxf_filter::addArc(const DL_ArcData& arcdata)
{
    func_bit_flags.addArc=1;
    if(is_block){data_vectors *last=&DL_Block.back();last->DL_ArcData_vector.emplace_back(arcdata);}
    else {common.DL_ArcData_vector.emplace_back(arcdata);}
}

void dxf_filter::addCircle(const DL_CircleData& circle)
{
    func_bit_flags.addCircle=1;
    if(is_block){data_vectors *last=&DL_Block.back();last->DL_CircleData_vector.emplace_back(circle);}
    else {common.DL_CircleData_vector.emplace_back(circle);}
}

void dxf_filter::addEllipse(const DL_EllipseData& ellipse)
{
    func_bit_flags.addEllipse=1;
    if(is_block){data_vectors *last=&DL_Block.back();last->DL_EllipseData_vector.emplace_back(ellipse);}
    else{common.DL_EllipseData_vector.emplace_back(ellipse);}
}

/** Called for every polyline start */
void dxf_filter::addPolyline(const DL_PolylineData& polyline)
{
    func_bit_flags.addPolyline=1;
    if(is_block)
    {
        data_vectors *last=&DL_Block.back();
        last->DL_PolylineData_vector.emplace_back(polyline);
        vector<point> pt_vec;
        last->polyline_points.emplace_back(pt_vec);
    }
    else
    {
        common.DL_PolylineData_vector.emplace_back(polyline);
        vector<point> pt_vec;
        common.polyline_points.emplace_back(pt_vec);
    }
}

void dxf_filter::addVertex(const DL_VertexData& vertex)
{
    func_bit_flags.addVertex=1;
    if(is_block)
    {
        data_vectors *last=&DL_Block.back();
        point pt={vertex.x,vertex.y};
        last->polyline_points.back().emplace_back(pt);
    }
    else
    {
        point pt={vertex.x,vertex.y};
        common.polyline_points.back().emplace_back(pt);
    }
}

/// Called for every spline
void dxf_filter::addSpline(const DL_SplineData& spline)
{
    func_bit_flags.addSpline=1;
    if(is_block)
    {
        data_vectors *last=&DL_Block.back();
        last->DL_SplineData_vector.emplace_back(spline);
        vector<point> pt_vec;
        last->spline_points.emplace_back(pt_vec);
        vector<double> k;
        last->spline_knots.emplace_back(k);
    }
    else
    {
        common.DL_SplineData_vector.emplace_back(spline);
        vector<point> pt_vec;
        common.spline_points.emplace_back(pt_vec);
        vector<double> k;
        common.spline_knots.emplace_back(k);
    }
}

/// Called for every spline control point
void dxf_filter::addControlPoint(const DL_ControlPointData& control_point)
{
    func_bit_flags.addControlPoint=1;
    if(is_block)
    {
        data_vectors *last=&DL_Block.back();
        point pt={control_point.x, control_point.y};
        last->spline_points.back().emplace_back(pt);
    }
    else
    {
        point pt={control_point.x, control_point.y};
        common.spline_points.back().emplace_back(pt);
    }
}

/// Called for every spline fit point
void dxf_filter::addFitPoint(const DL_FitPointData& fitpoint) {func_bit_flags.addFitPoint=1;}
 /// Called for every spline knot value
void dxf_filter::addKnot(const DL_KnotData& knot)
{
    func_bit_flags.addKnot=1;
    if(is_block)
    {
        data_vectors *last=&DL_Block.back();
        last->spline_knots.back().emplace_back(knot.k);
    }
    else
    {
        common.spline_knots.back().emplace_back(knot.k);
    }
}

/** Called for every insert. */
void dxf_filter::addInsert(const DL_InsertData& data)
{
    func_bit_flags.addInsert=1;

}

/** Called for every trace start */
void dxf_filter::addTrace(const DL_TraceData& data) {func_bit_flags.addTrace=1;}

/** Called for every 3dface start */
void dxf_filter::add3dFace(const DL_3dFaceData& data){func_bit_flags.add3dFace=1;}

/** Called for every solid start */
void dxf_filter::addSolid(const DL_SolidData& data)
{
    func_bit_flags.addSolid=1;
    //printf("addSolid\n");
}

/** Called for every multi Text entity. */
void dxf_filter::addMText(const DL_MTextData& data)
{
    func_bit_flags.addMText=1;
    printf("addMText=%s\n", data.text.c_str());
}

/**
 * Called for additional text chunks for MTEXT entities.
 * The chunks come at 250 character in size each. Note that
 * those chunks come <b>before</b> the actual MTEXT entity.
 */
void dxf_filter::addMTextChunk(const std::string& text) {func_bit_flags.addMTextChunk=1;}

/** Called for every text entity. */
void dxf_filter::addText(const DL_TextData& data)
{
    func_bit_flags.addText=1;
    //printf("addText\n");
}

/// Called for every arc aligned text entity.
void dxf_filter::addArcAlignedText(const DL_ArcAlignedTextData& data){func_bit_flags.addArcAlignedText=1;}
/// Called for every block Attribute entity.
void dxf_filter::addAttribute(const DL_AttributeData& data){func_bit_flags.addAttribute=1;}
///Called for every aligned dimension entity.
void dxf_filter::addDimAlign(const DL_DimensionData& data, const DL_DimAlignedData& edata)
{
    printf("dimension_data_angle=%f\n", data.angle);
    printf("data.dpx=%f\n",data.dpx);
    printf("data.dpy=%f\n",data.dpy);
    printf("data.mpx=%f\n",data.mpx);
    printf("data.mpy=%f\n",data.mpy);
    printf("exp1=%f\n",edata.epx1);
    printf("exp2=%f\n",edata.epx2);
    printf("expy1=%f\n",edata.epy1);
    printf("expy2=%f\n",edata.epx2);
    cout<<"text="<<data.text<<endl;
    func_bit_flags.addDimAlign=1;
}
///Called for every linear or rotated dimension entity.
void dxf_filter::addDimLinear(const DL_DimensionData& data, const DL_DimLinearData& edata){func_bit_flags.addDimLinear=1;}
///Called for every radial dimension entity.
void dxf_filter::addDimRadial(const DL_DimensionData& data, const DL_DimRadialData& edata){func_bit_flags.addDimRadial=1;}
///Called for every diametric dimension entity.
void dxf_filter::addDimDiametric(const DL_DimensionData& data, const DL_DimDiametricData& edata){func_bit_flags.addDimDiametric=1;}
///Called for every angular dimension (2 lines version) entity.
void dxf_filter::addDimAngular(const DL_DimensionData& data, const DL_DimAngularData& edata){func_bit_flags.addDimAngular=1;}
///Called for every angular dimension (3 points version) entity.
void dxf_filter::addDimAngular3P(const DL_DimensionData& data, const DL_DimAngular3PData& edata){func_bit_flags.addDimAngular3P=1;}
///Called for every ordinate dimension entity.
void dxf_filter::addDimOrdinate(const DL_DimensionData& data, const DL_DimOrdinateData& edata){func_bit_flags.addDimOrdinate=1;}
///Called for every leader start.
void dxf_filter::addLeader(const DL_LeaderData& data){func_bit_flags.addLeader=1;}
///Called for every leader vertex
void dxf_filter::addLeaderVertex(const DL_LeaderVertexData& data){func_bit_flags.addLeaderVertex=1;}

/**
 * Called for every hatch entity.
 */
void dxf_filter::addHatch(const DL_HatchData& data)
{
    func_bit_flags.addHatch=1;
    //printf("addHatch\n");
}

/**
 * Called for every image entity.
 */
void dxf_filter::addImage(const DL_ImageData& data)
{
    func_bit_flags.addImage=1;
   // printf("addImage\n");
}

/**
 * Called for every image definition.
 */
void dxf_filter::linkImage(const DL_ImageDefData& data)
{
    func_bit_flags.linkImage=1;
    //printf("linkImage\n");
}

/**
 * Called for every hatch loop.
 */
void dxf_filter::addHatchLoop(const DL_HatchLoopData& data)
{
    func_bit_flags.addHatchLoop=1;
   // printf("addHatchLoop\n");
}

/**
 * Called for every hatch edge entity.
 */
void dxf_filter::addHatchEdge(const DL_HatchEdgeData& data)
{
    func_bit_flags.addHatchEdge=1;
   // printf("addHatchEdge\n");
}

/**
 * Called for every XRecord with the given handle.
 */
void dxf_filter::addXRecord(const std::string& handle)
{
    func_bit_flags.addXRecord=1;
   // printf("addXRecord\n");
}

/**
 * Called for XRecords of type string.
 */
void dxf_filter::addXRecordString(int code, const std::string& value)
{
    func_bit_flags.addXRecordString=1;
   // printf("addXRecordString\n");
}

/**
 * Called for XRecords of type double.
 */
void dxf_filter::addXRecordReal(int code, double value)
{
    func_bit_flags.addXRecordReal=1;
  //  printf("addXRecordReal\n");
}

/**
 * Called for XRecords of type int.
 */
void dxf_filter::addXRecordInt(int code, int value)
{
    func_bit_flags.addXRecordInt=1;
   // printf("addXRecordInt\n");
}

/**
 * Called for XRecords of type bool.
 */
void dxf_filter::addXRecordBool(int code, bool value)
{
    func_bit_flags.addXRecordBool=1;
   // printf("addXRecordBool\n");
}

/**
 * Called for every beginning of an XData section of the given application.
 */
void dxf_filter::addXDataApp(const std::string& appId)
{
    func_bit_flags.addXDataApp=1;
  //  printf("addXDataApp\n");
}

/**
 * Called for XData tuples.
 */
void dxf_filter::addXDataString(int code, const std::string& value)
{
    func_bit_flags.addXDataString=1;
   // printf("addXDataString\n");
}

/**
     * Called for XData tuples.
     */
void dxf_filter::addXDataReal(int code, double value)
{
    func_bit_flags.addXDataReal=1;
   // printf("addXDataReal\n");
}

/**
 * Called for XData tuples.
 */
void dxf_filter::addXDataInt(int code, int value)
{
    func_bit_flags.addXDataInt=1;
   // printf("addXDataInt\n");
}

/**
 * Called for dictionary objects.
 */
void dxf_filter::addDictionary(const DL_DictionaryData& data)
{
    func_bit_flags.addDictionary=1;
   // printf("addDictionary\n");
}

/**
 * Called for dictionary entries.
 */
void dxf_filter::addDictionaryEntry(const DL_DictionaryEntryData& data)
{
    func_bit_flags.addDictionaryEntry=1;
    //printf("addDictionaryEntry\n");
}

/**
 * Called after an entity has been completed.
 */
void dxf_filter::endEntity()
{
    func_bit_flags.endEntity=1;
    //printf("endEntity\n");
}

/**
 * Called for every comment in the DXF file (code 999).
 */
void dxf_filter::addComment(const std::string& comment)
{
    func_bit_flags.addComment=1;
    //printf("addComment"); cout<<comment<<endl;
}

/**
 * Called for every vector variable in the DXF file (e.g. "$EXTMIN").
 */
void dxf_filter::setVariableVector(const std::string& key,  double v1, double v2, double v3, int code)
{
    func_bit_flags.setVariableVector=1;
   // printf("setVariableVector\n");
}

/**
     * Called for every string variable in the DXF file (e.g. "$ACADVER").
     */
void dxf_filter::setVariableString(const std::string& key, const std::string& value, int code)
{
    func_bit_flags.setVariableString=1;
  //  printf("setVariableString\n");
}

/**
 * Called for every int variable in the DXF file (e.g. "$ACADMAINTVER").
 */
void dxf_filter::setVariableInt(const std::string& key, int value, int code)
{
    func_bit_flags.setVariableInt=1;
   // printf("setVariableInt\n");
}

/**
 * Called for every double variable in the DXF file (e.g. "$DIMEXO").
 */
void dxf_filter::setVariableDouble(const std::string& key, double value, int code)
{
    func_bit_flags.setVariableDouble=1;
   // printf("setVariableDouble\n");
}

/**
 * Called when a SEQEND occurs (when a POLYLINE or ATTRIB is done)
 */
void dxf_filter::endSequence()
{
    func_bit_flags.endSequence=1;
    //printf("endSequence\n");
}


