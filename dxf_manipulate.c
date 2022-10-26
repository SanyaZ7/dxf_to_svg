
#include "dxf_manipulate.h"
#include <math.h>

dxf_manipulate::dxf_manipulate(svg_gen *svg)
{
    this->svg=svg;
}

void dxf_manipulate::mirror_x(void)
{

}

void dxf_manipulate::mirror_y(void)
{

}

void dxf_manipulate::dxf_write(char* filename_with_path)
{
     DL_Dxf* dxf = new DL_Dxf();
    DL_Codes::version exportVersion = DL_Codes::AC1015;
    DL_WriterA* dw = dxf->out("myfile.dxf", exportVersion);
    if (dw==NULL) { printf("Cannot open file 'myfile.dxf' for writing.");}


    dxf->writeHeader(*dw);
    dw->sectionEnd();
    dw->sectionTables();
    dxf->writeVPort(*dw); //для версии R13

    dw->tableLinetypes(3);
    dxf->writeLinetype(*dw, DL_LinetypeData("BYBLOCK", "BYBLOCK", 0, 0, 0.0));
    dxf->writeLinetype(*dw, DL_LinetypeData("BYLAYER", "BYLAYER", 0, 0, 0.0));
    dxf->writeLinetype(*dw, DL_LinetypeData("CONTINUOUS", "Continuous", 0, 0, 0.0));
    dw->tableEnd();

    int numberOfLayers = 3;
    dw->tableLayers(numberOfLayers);

    dxf->writeLayer(*dw,
                   DL_LayerData("0", 0),
                   DL_Attributes(
                       std::string(""),      // leave empty
                       DL_Codes::blue,        // default color
                       10,                  // default width
                       "CONTINUOUS", 1.0));       // default line style

    dxf->writeLayer(*dw,
                   DL_LayerData("mainlayer", 0),
                   DL_Attributes(
                       std::string(""),
                       DL_Codes::green,
                       10,
                       "CONTINUOUS", 1.0));

    dxf->writeLayer(*dw,
                   DL_LayerData("anotherlayer", 0),
                   DL_Attributes(
                       std::string(""),
                       DL_Codes::cyan,
                       10,
                       "CONTINUOUS", 1.0));

    dw->tableEnd();

    dw->tableStyle(1);
    dxf->writeStyle(*dw, DL_StyleData("standard", 0, 2.5, 1.0, 0.0, 0, 2.5, "txt", ""));
    dw->tableEnd();

    dxf->writeView(*dw);
    dxf->writeUcs(*dw);

    dw->tableAppid(1);
    dxf->writeAppid(*dw, "ACAD");
    dw->tableEnd();

    dxf->writeDimStyle(*dw, 1, 1, 1, 1, 1);

    ///dxf->writeBlockRecord(*dw);
    ///dxf->writeBlockRecord(*dw, "myblock1");
    ///dxf->writeBlockRecord(*dw, "myblock2");
    ///dw->tableEnd();

    ///dw->sectionEnd();

    ///dw->sectionBlocks();
    ///dxf->writeBlock(*dw, DL_BlockData("*Model_Space", 0, 0.0, 0.0, 0.0));
    ///dxf->writeEndBlock(*dw, "*Model_Space");
    ///dxf->writeBlock(*dw, DL_BlockData("*Paper_Space", 0, 0.0, 0.0, 0.0));
    ///dxf->writeEndBlock(*dw, "*Paper_Space");
    ///dxf->writeBlock(*dw, DL_BlockData("*Paper_Space0", 0, 0.0, 0.0, 0.0));
    ///dxf->writeEndBlock(*dw, "*Paper_Space0");

    ///dxf->writeBlock(*dw, DL_BlockData("myblock1", 0, 0.0, 0.0, 0.0));
    // ...
    // write block entities e.g. with dxf->writeLine(), ..
    // ...
    ///dxf->writeEndBlock(*dw, "myblock1");

    //dxf->writeBlock(*dw, DL_BlockData("myblock2", 0, 0.0, 0.0, 0.0));
    // ...
    // write block entities e.g. with dxf->writeLine(), ..
    // ...
    //dxf->writeEndBlock(*dw, "myblock2");

    dw->sectionEnd();
    dw->sectionEntities();


        write_all_lines(svg->common, dxf,dw,"mainlayer", true);
        write_all_arcs(svg->common, dxf,dw,"mainlayer", true);
        write_all_cirles(svg->common, dxf,dw,"mainlayer", true);
        write_all_polylines(svg->common, dxf,dw,"mainlayer", true);
        write_all_ellipses(svg->common, dxf,dw,"mainlayer", true);
        write_all_splines(svg->common, dxf,dw,"mainlayer", true);


    dw->sectionEnd();

    dxf->writeObjects(*dw);
    dxf->writeObjectsEnd(*dw);

    dw->dxfEOF();
    dw->close();
    delete dw;
    delete dxf;
}

void dxf_manipulate::write_all_lines(data_vectors vec, DL_Dxf* dxf, DL_WriterA* dw, char *layername, bool need_normalize)
{
    int size=vec.DL_LineData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_LineData *data=&(vec.DL_LineData_vector[i]);
        if(need_normalize==false)
        dxf->writeLine( *dw, DL_LineData(data->x1, data->y1, data->z1, data->x2, data->y2, data->z2),
        DL_Attributes(layername, 256, -1, "BYLAYER", 1.0));
        else
        {
            svg->min_max_values(vec);
            double x_min=svg->dxf_range.min_.x;
            double y_min=svg->dxf_range.min_.y;
            dxf->writeLine(*dw, DL_LineData(data->x1-x_min, data->y1-y_min, data->z1, data->x2-x_min, data->y2-y_min, data->z2),
            DL_Attributes(layername, 256, -1, "BYLAYER", 1.0));
        }
    }
}

void dxf_manipulate::write_all_arcs(data_vectors vec, DL_Dxf* dxf, DL_WriterA* dw, char *layername, bool need_normalize)
{
    int size=vec.DL_ArcData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_ArcData *data=&(vec.DL_ArcData_vector[i]);
        if(need_normalize==false)
        dxf->writeArc(*dw,*data, DL_Attributes(layername, 256, -1, "BYLAYER", 1.0));
        else
        {
            svg->min_max_values(vec);
            double x_min=svg->dxf_range.min_.x;
            double y_min=svg->dxf_range.min_.y;
            dxf->writeArc(*dw,DL_ArcData(data->cx-x_min, data->cy-y_min, data->cz, data->radius, data->angle1, data->angle2),
            DL_Attributes(layername, 256, -1, "BYLAYER", 1.0));
        }
    }
}
void dxf_manipulate::write_all_cirles(data_vectors vec, DL_Dxf* dxf, DL_WriterA* dw, char *layername, bool need_normalize)
{
    int size=vec.DL_CircleData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_CircleData *data=&(vec.DL_CircleData_vector[i]);
        if(need_normalize==false)
        dxf->writeCircle(*dw,*data, DL_Attributes(layername, 256, -1, "BYLAYER", 1.0));
        else
        {
            svg->min_max_values(vec);
            double x_min=svg->dxf_range.min_.x;
            double y_min=svg->dxf_range.min_.y;
            dxf->writeCircle(*dw, DL_CircleData(data->cx-x_min, data->cy-y_min, data->cz, data->radius),
            DL_Attributes(layername, 256, -1, "BYLAYER", 1.0));
        }
    }
 }

void dxf_manipulate::write_all_polylines(data_vectors vec, DL_Dxf* dxf, DL_WriterA* dw, char *layername, bool need_normalize)
{
    int size=svg->common.polyline_points.size();
    for(int i=0;i<size;++i)
    {
        DL_PolylineData *data=&(vec.DL_PolylineData_vector[i]);
        dxf->writePolyline(*dw,*data, DL_Attributes(layername, 256, -1, "BYLAYER", 1.0));
        int size=data->number;
        for(int j=0;j<size;++j)
        {
            if(need_normalize==false)
            {
                point pt=vec.polyline_points[i][j];
                dxf->writeVertex(*dw, DL_VertexData(pt.x,pt.y,0,0));
            }
            else
            {
                svg->min_max_values(vec);
                point pt=svg->common.polyline_points[i][j];
                pt.x=pt.x-svg->dxf_range.min_.x;
                pt.y=pt.y-svg->dxf_range.min_.y;
                dxf->writeVertex(*dw, DL_VertexData(pt.x,pt.y,0,0));
            }
        }
    }
}
void dxf_manipulate::write_all_ellipses(data_vectors vec, DL_Dxf* dxf, DL_WriterA* dw, char *layername, bool need_normalize)
{
    int size=vec.DL_EllipseData_vector.size();
    for(int i=0;i<size;++i)
    {
        DL_EllipseData *data=&(vec.DL_EllipseData_vector[i]);
        if(need_normalize==false)
        dxf->writeEllipse(*dw,*data, DL_Attributes(layername, 256, -1, "BYLAYER", 1.0));
        else
        {
            svg->min_max_values(vec);
            double x_min=svg->dxf_range.min_.x;
            double y_min=svg->dxf_range.min_.y;
            data->cx=data->cx-x_min;
            data->cy=data->cy-y_min;
            dxf->writeEllipse(*dw,*data, DL_Attributes(layername, 256, -1, "BYLAYER", 1.0));
        }
    }
}

void dxf_manipulate::write_all_splines(data_vectors vec, DL_Dxf* dxf, DL_WriterA* dw, char *layername, bool need_normalize)
{
    int size=vec.DL_SplineData_vector.size();
    for(int i=0;i<size;++i)
    {
        DL_SplineData *data=&(vec.DL_SplineData_vector[i]);
        dxf->writePolyline(*dw, DL_PolylineData(data->nControl, 0,0,0,0), DL_Attributes(layername, 256, -1, "BYLAYER", 1.0));
        int size=data->nControl;
        for(int j=0;j<size;++j)
        {
            if(need_normalize==false)
            {
                point pt=vec.spline_points[i][j];
                dxf->writeVertex(*dw, DL_VertexData(pt.x,pt.y,0,0));
            }
            else
            {
                svg->min_max_values(vec);
                point pt=vec.spline_points[i][j];
                pt.x=pt.x-svg->dxf_range.min_.x;
                pt.y=pt.y-svg->dxf_range.min_.y;
                dxf->writeVertex(*dw, DL_VertexData(pt.x,pt.y,0,0));
            }
        }
    }
}

void dxf_manipulate::rotate_dxf(data_vectors vec, double angle)//0-360
{
    double cx=svg->dxf_range.max_.x*0.5;
    double cy=svg->dxf_range.max_.y*0.5;
    rotate_all_lines(vec, cx,cy, angle);
    rotate_all_circles(vec, cx,cy, angle);
    rotate_all_arcs(vec, cx, cy, angle);
    rotate_all_polylines(vec, cx, cy, angle);
    rotate_all_ellipses(vec, cx, cy, angle);
    rotate_all_splines(vec, cx, cy, angle);
}

point dxf_manipulate::rotate_point(double x, double y, double cx, double cy, double angle)
{
    point pt;
    double k=M_PI/180;
    pt.x=cx+(x-cx)*cos(angle*k)-(y-cy)*sin(angle*k);
    pt.y=cy+(x-cx)*sin(angle*k)+(y-cy)*cos(angle*k);
    return pt;
}

void dxf_manipulate::rotate_all_lines(data_vectors vec, double cx, double cy, double angle)
{
    int size=vec.DL_LineData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_LineData *data=&(vec.DL_LineData_vector[i]);
        point pt;
        pt=rotate_point(data->x1, data->y1, cx, cy, angle);
        data->x1=pt.x;
        data->y1=pt.y;
        pt=rotate_point(data->x2, data->y2, cx, cy, angle);
        data->x2=pt.x;
        data->y2=pt.y;
    }
}

void dxf_manipulate::rotate_all_arcs(data_vectors vec, double cx, double cy, double angle)
{
    int size=vec.DL_ArcData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_ArcData *data=&(vec.DL_ArcData_vector[i]);
        point pt;
        pt=rotate_point(data->cx, data->cy, cx, cy, angle);
        data->cx=pt.x;
        data->cy=pt.y;
        data->angle1=data->angle1+angle;
        data->angle2=data->angle2+angle;
    }
}

void dxf_manipulate::rotate_all_circles(data_vectors vec, double cx, double cy, double angle)
{
    int size=vec.DL_CircleData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_CircleData *data=&(vec.DL_CircleData_vector[i]);
        point pt;
        pt=rotate_point(data->cx, data->cy, cx, cy, angle);
        data->cx=pt.x;
        data->cy=pt.y;
    }
}

void dxf_manipulate::rotate_all_polylines(data_vectors vec, double cx, double cy, double angle)
{
    int size=vec.polyline_points.size();
    for(int i=0;i<size;++i)
    {
        DL_PolylineData *data=&(vec.DL_PolylineData_vector[i]);
        int size=data->number;
        for(int j=0;j<size;++j)
        {
            point pt=vec.polyline_points[i][j];
            point pt_new=rotate_point(pt.x, pt.y, cx, cy, angle);
            vec.polyline_points[i][j]=pt_new;
        }
    }
}

void dxf_manipulate::rotate_all_ellipses(data_vectors vec, double cx, double cy, double angle)
{
    int size=vec.DL_EllipseData_vector.size();
    for(int i=0;i<size;++i)
    {
        DL_EllipseData *data=&(vec.DL_EllipseData_vector[i]);
        point pt;
        pt=rotate_point(data->mx, data->my, 0, 0, angle);
        data->mx=pt.x;
        data->my=pt.y;
        pt=rotate_point(data->cx, data->cy, cx, cy, angle);
        data->cx=pt.x;
        data->cy=pt.y;
    }
}

void dxf_manipulate::rotate_all_splines(data_vectors vec, double cx, double cy, double angle)
{
    int size=vec.DL_SplineData_vector.size();
    for(int i=0;i<size;++i)
    {
        DL_SplineData *data=&(vec.DL_SplineData_vector[i]);
        int size=data->nControl;
        for(int j=0;j<size;++j)
        {
            point pt=vec.spline_points[i][j];
            point pt_new=rotate_point(pt.x, pt.y, cx, cy, angle);
            vec.spline_points[i][j]=pt_new;
        }
    }
}

void dxf_manipulate::normalize_dxf(void)
{
    //svg->min_max_values();
    normalize_all_lines();
    normalize_all_arcs();
    normalize_all_circles();
    normalize_all_polylines();
    normalize_all_ellipses();
    normalize_all_splines();
    //svg->min_max_values();
}

void dxf_manipulate::normalize_all_lines(void)
{
    int size=svg->common.DL_LineData_vector.size();
    double x_min=svg->dxf_range.min_.x;
    double y_min=svg->dxf_range.min_.y;
    for(int i = 0; i < size; i++)
    {
        DL_LineData& data=svg->common.DL_LineData_vector[i];
            data.x1=data.x1-x_min;
            data.x2=data.x2-x_min;
            data.y1=data.y1-y_min;
            data.y2=data.y2-y_min;
            //svg->DL_LineData_vector[i]=*data;
    }
}

void dxf_manipulate::normalize_all_arcs(void)
{

}

void dxf_manipulate::normalize_all_circles(void)
{

}

void dxf_manipulate::normalize_all_polylines(void)
{

}

void dxf_manipulate::normalize_all_ellipses(void)
{

}

void dxf_manipulate::normalize_all_splines(void)
{

}

