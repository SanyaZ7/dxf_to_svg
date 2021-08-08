
#include "stats.hpp"
#include <stdio.h>

void stats::evaluate_dxf_stats(dxf_handler_funcions flags)
{
    if(flags.processCodeValuePair==1){++processCodeValuePair_count;}
    if(flags.endSection==1){++endSection_count;}
    if(flags.addLayer==1){++addLayer_count;}
    if(flags.addLinetype==1){++addLinetype_count;}
    if(flags.addLinetypeDash==1){++addLinetypeDash_count;}
    if(flags.addBlock==1){++addBlock_count;}
    if(flags.endBlock==1){++endBlock_count;}
    if(flags.addTextStyle==1){++addTextStyle_count;}
    if(flags.addPoint==1){++addPoint_count;}
    if(flags.addLine==1){++addLine_count;}
    if(flags.addXLine==1){++addXLine_count;}
    if(flags.addRay==1){++addRay_count;}
    if(flags.addArc==1){++addArc_count;}
    if(flags.addCircle==1){++addCircle_count;}
    if(flags.addEllipse==1){++addEllipse_count;}
    if(flags.addPolyline==1){++addPolyline_count;}
    if(flags.addVertex==1){++addVertex_count;}
    if(flags.addSpline==1){++addSpline_count;}
    if(flags.addControlPoint==1){++addControlPoint_count;}
    if(flags.addFitPoint==1){++addFitPoint_count;}
    if(flags.addKnot==1){++addKnot_count;}
    if(flags.addInsert==1){++addInsert_count;}
    if(flags.addTrace==1){++addTrace_count;}
    if(flags.add3dFace==1){++add3dFace_count;}
    if(flags.addSolid==1){++addSolid_count;}
    if(flags.addMText==1){++addMText_count;}
    if(flags.addMTextChunk==1){++addMTextChunk_count;}
    if(flags.addText==1){++addText_count;}
    if(flags.addArcAlignedText==1){++addArcAlignedText_count;}
    if(flags.addAttribute==1){++addAttribute_count;}
    if(flags.addDimAlign==1){++addDimAlign_count;}
    if(flags.addDimLinear==1){++addDimLinear_count;}
    if(flags.addDimRadial==1){++addDimRadial_count;}
    if(flags.addDimDiametric==1){++addDimDiametric_count;}
    if(flags.addDimAngular==1){++addDimAngular_count;}
    if(flags.addDimAngular3P==1){++addDimAngular3P_count;}
    if(flags.addLeader==1){++addLeader_count;}
    if(flags.addLeaderVertex==1){++addLeaderVertex_count;}
    if(flags.addHatch==1){++addHatch_count;}
    if(flags.addImage==1){++addImage_count;}
    if(flags.linkImage==1){++linkImage_count;}
    if(flags.addHatchLoop==1){++addHatchLoop_count;}
    if(flags.addHatchEdge==1){++addHatchEdge_count;}
    if(flags.addXRecord==1){++addXRecord_count;}
    if(flags.addXRecordString==1){++addXRecordString_count;}
    if(flags.addXRecordReal==1){++addXRecordReal_count;}
    if(flags.addXRecordInt==1){++addXRecordInt_count;}
    if(flags.addXRecordBool==1){++addXRecordBool_count;}
    if(flags.addXDataApp==1){++addXDataApp_count;}
    if(flags.addXDataString==1){++addXDataString_count;}
    if(flags.addXDataReal==1){++addXDataReal_count;}
    if(flags.addXDataInt==1){++addXDataInt_count;}
    if(flags.addDictionary==1){++addDictionary_count;}
    if(flags.addDictionaryEntry==1){++addDictionaryEntry_count;}
    if(flags.endEntity==1){++endEntity_count;}
    if(flags.addComment==1){++addComment_count;}
    if(flags.setVariableVector==1){++setVariableVector_count;}
    if(flags.setVariableString==1){++setVariableString_count;}
    if(flags.setVariableInt==1){++setVariableInt_count;}
    if(flags.setVariableDouble==1){++setVariableDouble_count;}
    if(flags.endSequence==1){++endSequence_count;}
}

void stats::print_stat(void)
{
    printf("processCodeValuePair_count=%d\n", processCodeValuePair_count);
    printf("endSection_count=%d\n", endSection_count);
    printf("addLayer_count=%d\n", addLayer_count);
    printf("addLinetype_count=%d\n", addLinetype_count);
    printf("addLinetypeDash_count=%d\n", addLinetypeDash_count);
    printf("addBlock_count=%d\n", addBlock_count);
    printf("endBlock_count=%d\n", endBlock_count);
    printf("addTextStyle_count=%d\n", addTextStyle_count);
    printf("addPoint_count=%d\n", addPoint_count);
    printf("addLine_count=%d\n", addLine_count);
    printf("addXLine_count=%d\n", addXLine_count);
    printf("addRay_count=%d\n", addRay_count);
    printf("addArc_count=%d\n", addArc_count);
    printf("addCircle_count=%d\n", addCircle_count);
    printf("addEllipse_count=%d\n", addEllipse_count);
    printf("addPolyline_count=%d\n", addPolyline_count);
    printf("addVertex_count=%d\n", addVertex_count);
    printf("addSpline_count=%d\n", addSpline_count);
    printf("addControlPoint_count=%d\n", addControlPoint_count);
    printf("addFitPoint_count=%d\n", addFitPoint_count);
    printf("addInsert_count=%d\n", addInsert_count);
    printf("addTrace_count=%d\n", addTrace_count);
    printf("add3dFace_count=%d\n", add3dFace_count);
    printf("addSolid_count=%d\n", addSolid_count);
    printf("addMText_count=%d\n", addMText_count);
    printf("addMTextChunk_count=%d\n", addMTextChunk_count);
    printf("addText_count=%d\n", addText_count);
    printf("addArcAlignedText_count=%d\n", addArcAlignedText_count);
    printf("addAttribute_count=%d\n", addAttribute_count);
    printf("addDimAlign_count=%d\n", addDimAlign_count);
    printf("addDimLinear_count=%d\n", addDimLinear_count);
    printf("addDimRadial_count=%d\n", addDimRadial_count);
    printf("addDimDiametric_count=%d\n", addDimDiametric_count);
    printf("addDimAngular_count=%d\n", addDimAngular_count);
    printf("addDimAngular3P_count=%d\n", addDimAngular3P_count);
    printf("addLeader_count=%d\n", addLeader_count);
    printf("addLeaderVertex_count=%d\n", addLeaderVertex_count);
    printf("addHatch_count=%d\n", addHatch_count);
    printf("addImage_count=%d\n", addImage_count);
    printf("linkImage_count=%d\n", linkImage_count);
    printf("addHatchLoop_count=%d\n", addHatchLoop_count);
    printf("addHatchEdge_count=%d\n", addHatchEdge_count);
    printf("addXRecord_count=%d\n", addXRecord_count);
    printf("addXRecordString_count=%d\n", addXRecordString_count);
    printf("addXRecordReal_count=%d\n", addXRecordReal_count);
    printf("addXRecordInt_count=%d\n", addXRecordInt_count);
    printf("addXRecordBool_count=%d\n", addXRecordBool_count);
    printf("addXDataApp_count=%d\n", addXDataApp_count);
    printf("addXDataString_count=%d\n", addXDataString_count);
    printf("addXDataReal_count=%d\n", addXDataReal_count);
    printf("addXDataInt_count=%d\n", addXDataInt_count);
    printf("addDictionary_count=%d\n", addDictionary_count);
    printf("addDictionaryEntry_count=%d\n", addDictionaryEntry_count);
    printf("endEntity_count=%d\n", endEntity_count);
    printf("addComment_count=%d\n", addComment_count);
    printf("setVariableVector_count=%d\n", setVariableVector_count);
    printf("setVariableString_count=%d\n", setVariableString_count);
    printf("setVariableInt_count=%d\n", setVariableInt_count);
    printf("setVariableDouble_count=%d\n", setVariableDouble_count);
    printf("endSequence_count=%d\n", endSequence_count);

}

