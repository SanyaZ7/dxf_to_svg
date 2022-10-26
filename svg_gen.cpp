
#include "svg_gen.h"
#include <fstream>
#include <cmath>
#include <stdio.h>
#include "dxf_manipulate.h"
using namespace std;

char standard_header[]=
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<svg xmlns=\"http://www.w3.org/2000/svg\"  \
viewBox=\"0.0 0.0 %f %f\" preserveAspectRatio=\"xMidYMid meet\" \
version=\"1.1\">\n\t<link xmlns=\"http://www.w3.org/1999/xhtml\" rel=\"stylesheet\" \
href=\"svg_style.css\" type=\"text/css\"/>\n  <desc>Produce by Acme CAD Converter</desc>\n";

svg_gen::svg_gen()
{

}



string svg_gen::solve_quadratic_beizer(vector<point> pt)
{
    if(pt.size()>=4)
    {
        string res;
        char pair[32]={0};
        snprintf(pair,31,"%.3f,%.3f ", pt[0].x, pt[0].y);
        res.append(pair);
        int i=0;
        start:
        double Px=2*pt[i+1].x-0.5*(pt[i].x+pt[i+2].x);
        double Py=2*pt[i+1].y-0.5*(pt[i].y+pt[i+2].y);
        res=res+'Q';
        memset(pair, 0, 32);
        snprintf(pair,31,"%.3f,%.3f ", Px, Py);
        res.append(pair);
        memset(pair, 0, 32);
        snprintf(pair,31,"%.3f,%.3f ", pt[i+2].x, pt[i+2].y);
        res.append(pair);
        if(pt.size()>i+4) {i=i+2; goto start;}
        else
        {   i=i+3;
                while(i<pt.size())
                {
                    memset(pair, 0, 32);
                    snprintf(pair,31,"L%.3f,%.3f ", pt[i].x, pt[i].y);
                    res.append(pair);
                    ++i;
                }
        }
        return res;
    }
    else
    {
        string res="";
        return res;
    }
}

//#define replaceall
/*std::string s = "example string";
  std::replace( s.begin(), s.end(), 'x', 'y'); // replace all 'x' to 'y'*/

void svg_gen::generate_polyline(data_vectors vec,double x_min, double y_max)
{
    /*
	<polyline stroke="red" stroke-width="3px" fill="black"
  points=" 50,80 140,80 80,100 180,100 160,85 160,115 180,100" />*/
  vector<point> pair;
    int i=vec.polyline_points.size()-1;
    for(;i>=0;--i)
    {
        int j=vec.polyline_points[i].size()-1;
        string res="<polyline points=\"";
        for(;j>=0; --j)
        {
            point pt=vec.polyline_points[i][j];
            char buf[32]={0};
            snprintf(buf,31,"%.3f,%.3f ", pt.x-x_min, y_max-pt.y);
            //pair.emplace_back(pt);
            res.append(buf);
        }
        res.append("\"/>");
        this->resulting_svg=this->resulting_svg+res;
    }
}

void svg_gen::generate_lines(data_vectors vec, double x_min, double y_max)
{
    int size=(int) vec.DL_LineData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_LineData *data=&(vec.DL_LineData_vector[i]);
        string x1 = to_string(data->x1-x_min);
        string x2 = to_string(data->x2-x_min);
        string y1 = to_string(y_max-data->y1);
        string y2 = to_string(y_max-data->y2);
        string path="<path d=\"Mx1 y1Lx2 y2\"";
        path.replace(path.find("x1"), 2, x1.c_str());
        path.replace(path.find("x2"), 2, x2.c_str());
        path.replace(path.find("y1"), 2, y1.c_str());
        path.replace(path.find("y2"), 2, y2.c_str());
        this->resulting_svg=this->resulting_svg+path;
        this->resulting_svg.append("/>\n");
    }
}

void svg_gen::generate_arcs(data_vectors vec, double x_min, double y_max)
{
    int size=(int) vec.DL_ArcData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_ArcData *data=&(vec.DL_ArcData_vector[i]);
        double sigma1=data->angle1*0.0175;
        double sigma2=data->angle2*0.0175;
        double R=data->radius;
        double x1=data->cx+R*cos(sigma1)-x_min;
        double y1=y_max-data->cy-R*sin(sigma1);//296.926-
        double x2=data->cx+R*cos(sigma2)-x_min;
        double y2=y_max-data->cy-R*sin(sigma2);//296.926-
        char str[80]={0};
        //string path="<path d=\"Mx1 y1 A r r 1 0 0 x2 y2\"";
        if(snprintf(str, 80, "<path d=\"M%.3f %.3f A %.3f %.3f 0 0 0  %.3f %.3f\"/>\n", x1, y1, R, R, x2, y2)>79)
        {
            cerr<<"Превышение максимальной длины строки в path arc"<<endl;
        }
        this->resulting_svg.append(str);
    }
}

void svg_gen::generate_circles(data_vectors vec, double x_min, double y_max)
{
    int size=(int) vec.DL_CircleData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_CircleData *data=&(vec.DL_CircleData_vector[i]);
        char str[64]={0};
        if(snprintf(str, 64, "<circle cx=\"%.3f\" cy=\"%.3f\" r=\"%.3f\"/>\n", data->cx-x_min, y_max-data->cy, data->radius)>63)
        {
            cerr<<"Превышение максимальной длины строки в circle"<<endl;
        }
        this->resulting_svg.append(str);
    }
}

void svg_gen::generate_ellipse(data_vectors vec, double x_min, double y_max)
{
    int size=(int) vec.DL_EllipseData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_EllipseData *data=&(vec.DL_EllipseData_vector[i]);
        double c=sqrt(pow(data->mx,2)+pow(data->my,2));
        double k=data->ratio;
        double a=sqrt(pow(c,2)/(1-pow(k,2)));
        double b=k*a;
        double angle1=data->angle1;
        double angle2=data->angle2;
        double cx=data->cx;
        double cy=data->cy;
        double mx=data->mx;
        double my=data->my;
        double angle=atan(my/mx);
        printf("k=%f, angle1=%f, angle2=%f, angle=%f,cx=%f, cy=%f, mx=%f, my=%f\n", k, angle1*180/M_PI, angle2*180/M_PI, angle*180/M_PI, cx, cy, mx, my);
        double min=angle1<angle2 ? angle1 : angle2;
        double max=angle1>angle2 ? angle1 : angle2;
        if(min<0.01&&max>6.27&&data->my<0.001)
        {
            char str[64]= {0};
           // double angle = atan(data->mx/data->my);
            ///<path d="M mx,my A rx,ry x-axis-rotation large-arc-flag, sweep-flag x,y" />
            if(snprintf(str, 63, "<ellipse cx=\"%.3f\" cy=\"%.3f\" rx=\"%.3f\" ry=\"%.3f\"/>\n", data->cx-x_min, y_max-data->cy, a, k*a)>63)
            {
                cerr<<"Превышение максимальной длины строки в ellipse"<<endl;
            }
            this->resulting_svg.append(str);
        }
        else
        {
            int count_vertex=64;
            double alpha_array[count_vertex];
            double x[count_vertex];
            double y[count_vertex];
            string res="<polyline points=\"";
            for(int i=0;i<count_vertex;i++)
            {
                if(angle>0.001)
                {
                    if(max<6.28&&min>0.001)
                    {
                        if(angle1<angle2)
                        alpha_array[i]=i*((max-min)/((double)count_vertex))+min;
                        else
                        alpha_array[i]=i*((2*M_PI-(max-min))/((double)count_vertex))-(max-min)-angle;
                    }
                    else alpha_array[i]=i*((2.0*M_PI)/((double)count_vertex))-angle;
                    double xr=a*cos(alpha_array[i]);
                    double yr=b*sin(alpha_array[i]);
                    x[i]=xr*cos(angle)-yr*sin(angle)+cx;
                    y[i]=xr*sin(angle)+yr*cos(angle)+cy;
                }
                else if(angle<=0.001)
                {
                    alpha_array[i]=i*(2.0*M_PI/((double)count_vertex));
                    x[i]=(a*cos(alpha_array[i])+cx);
                    y[i]=(b*sin(alpha_array[i])+cy);
                }
                char buf[32]={0};
                snprintf(buf,31,"%.3f,%.3f ", x[i]-x_min, y_max-y[i]);
                res.append(buf);
            }
            ///замкнуть на начало
            if(min<0.001&&max>6.28)
            {
                char buf[32]= {0};
                snprintf(buf,31,"%.3f,%.3f ", x[0]-x_min, y_max-y[0]);
                res.append(buf);
            }
            res.append("\"/>");
            this->resulting_svg=this->resulting_svg+res;
        }
    }
}

class spline_koeff
{
public:
    double b1;
    double b2;
    double b3;
    int n=0;
    void coeffs(double t, vector<point> pt, vector<double> k);
};

void spline_koeff::coeffs(double t,vector<point> pt, vector<double> k)
{
    #define k2 k[n+1]
    #define k3 k[n+2]
    #define k4 k[n+3]
    #define k5 k[n+4]
    if(k2-k4!=0&&k3-k4!=0&&k3-k5!=0&&n<(int)pt.size())
    {
        b1=pow(k4-t,2)/(-k4+k2)/(-k4+k3);
        b2=-(t*t*k2+k2*k3*k5+k2*k3*k4-k4*k2*k5-2*t*k3*k2-k4*t*t+2*t*k4*k5-t*t*k5+t*t*k3-k3*k4*k5)/(-k4+k2)/(-k4+k3)/(-k5+k3);
        b3=pow(-t+k3,2)/(-k4+k3)/(-k5+k3);
    }
    else
    {b1=0;b2=0;b3=0;}
}

void svg_gen::spline_points_and_knots_degree2(vector<point> pt, vector<double> k, double x_min, double y_max)
{
        point pt1, pt2;
        string res="<path d=\"M";
        double t=0;
        vector<point> pair;
    spline_koeff b123;
    for(int j=3; j<(int)k.size()-2; ++j)
    {
        double ink=(k[j]-k[j-1])/10;
        b123.n=j-3;
        t=k[j-1];
        int i=0;
        while(i<10)
        {
            b123.coeffs(t, pt, k);
            #define b1 b123.b1
            #define b2 b123.b2
            #define b3 b123.b3
            #define n b123.n
            pt1.x=b1*pt[n].x+b2*pt[n+1].x+b3*pt[n+2].x;
            pt1.y=b1*pt[n].y+b2*pt[n+1].y+b3*pt[n+2].y;
            t=t+ink;
            b123.coeffs(t, pt, k);
            pt2.x=b1*pt[n].x+b2*pt[n+1].x+b3*pt[n+2].x;
            pt2.y=b1*pt[n].y+b2*pt[n+1].y+b3*pt[n+2].y;
            t=t-ink;
            char buf[72]= {0};
            snprintf(buf,71,"%.3f,%.3f %.3f,%.3f ", pt1.x-x_min, y_max-pt1.y, pt2.x-x_min, y_max-pt2.y);
            point pt={pt1.x-x_min, y_max-pt1.y};
            pair.emplace_back(pt);
            if(i==9)
            {
                point pt={pt2.x-x_min, y_max-pt2.y};
                pair.emplace_back(pt);
            }
            //res.append(buf);
            t=t+ink;
            ++i;
        }
    }
    res=res+solve_quadratic_beizer(pair);
    res.append("\"/>\n");
    this->resulting_svg=this->resulting_svg+res;

}

#define MAX(x,y) (x>y?x:y)
#define MIN(x,y) (x<y?x:y)

void svg_gen::generate_spline(data_vectors vec, double x_min, double y_max)
{
    int size=(int) vec.spline_knots.size();
    for(int i=0; i<size; ++i)
    {
        if(vec.DL_SplineData_vector[i].degree==2)
            spline_points_and_knots_degree2(vec.spline_points[i], vec.spline_knots[i], x_min, y_max);
            else
            {
                int i=vec.spline_points.size()-1;
                for(; i>=0; --i)
                {
                    int j=vec.spline_points[i].size()-1;
                    string res="<polyline points=\"";
                    for(; j>=0; --j)
                    {
                        point pt=vec.spline_points[i][j];
                        char buf[32]= {0};
                        snprintf(buf,31,"%.3f,%.3f ", pt.x-x_min, y_max-pt.y);
                        res.append(buf);
                    }
                    res.append("\"/>");
                    this->resulting_svg=this->resulting_svg+res;
                }
            }
    }
}

range svg_gen::min_max_values(data_vectors vec, double &x_min, double &x_max, double &y_min, double &y_max)
{
    x_max=-10000, x_min=10000, y_max=-10000, y_min=10000;
    ///тут нужно определить габариты
    ///обход полилиний
    int i=vec.polyline_points.size()-1;
    for(; i>=0; --i)
    {
        int j=vec.polyline_points[i].size()-1;
        for(; j>=0; --j)
        {
            point pt=vec.polyline_points[i][j];
            if(pt.x<x_min) x_min=pt.x;
            if(pt.x>x_max) x_max=pt.x;
            if(pt.y<y_min) y_min=pt.y;
            if(pt.y>y_max) y_max=pt.y;
        }
    }
    ///обход линий
    int size=(int) vec.DL_LineData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_LineData &data=vec.DL_LineData_vector[i];
        if(data.x1<x_min) x_min=data.x1;
        if(data.x2<x_min) x_min=data.x2;
        if(data.x1>x_max) x_max=data.x1;
        if(data.x2>x_max) x_max=data.x2;

        if(data.y1<y_min) y_min=data.y1;
        if(data.y2<y_min) y_min=data.y2;
        if(data.y1>y_max) y_max=data.y1;
        if(data.y2>y_max) y_max=data.y2;
    }
    ///обход дуг
    size=(int) vec.DL_ArcData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_ArcData *data=&(vec.DL_ArcData_vector[i]);
        double delta_x_max=0,delta_x_min=0,delta_y_max=0,delta_y_min=0;

        double R=data->radius;
        double sigma1=data->angle1*0.0175;  ///углы в радианах
        double sigma2=data->angle2*0.0175;
        #define m_0_90(angle) ((angle>=0&&angle<=M_PI/2) ? true : false)
        #define m_90_180(angle) ((angle>=M_PI/2&&angle<=M_PI) ? true : false)
        #define m_180_270(angle) ((angle>=M_PI&&angle<=(3*M_PI/2)) ? true : false)
        #define m_270_360(angle) ((angle>=(3*M_PI/2)&&angle<=(2*M_PI)) ? true : false)
        if(m_0_90(sigma1)&&m_270_360(sigma2))
        {delta_x_min=-R;delta_y_min=-R;delta_y_max=R; goto end;}
        if(m_90_180(sigma1)&&m_270_360(sigma2))
        {delta_x_min=-R;delta_y_min=-R; goto end;}
        if(m_180_270(sigma1)&&m_270_360(sigma2))
        {delta_y_min=-R; goto end;}

        if(m_90_180(sigma1)&&m_0_90(sigma2))
        {delta_x_min=-R;delta_y_min=-R;delta_x_max=R; goto end;}
        if(m_180_270(sigma1)&&m_0_90(sigma2))
        {delta_y_min=-R;delta_x_max=R; goto end;}
        if(m_270_360(sigma1)&&m_0_90(sigma2))
        {delta_x_max=R; goto end;}

        if(m_180_270(sigma1)&&m_90_180(sigma2))
        {delta_y_max=R;delta_y_min=-R;delta_x_max=R; goto end;}
        if(m_270_360(sigma1)&&m_90_180(sigma2))
        {delta_y_max=R;delta_x_max=R; goto end;}
        if(m_0_90(sigma1)&&m_90_180(sigma2))
        {delta_y_max=R; goto end;}

        if(m_270_360(sigma1)&&m_180_270(sigma2))
        {delta_y_max=R;delta_x_min=-R;delta_x_max=R; goto end;}
        if(m_0_90(sigma1)&&m_180_270(sigma2))
        {delta_y_max=R;delta_x_min=-R; goto end;}
        if(m_90_180(sigma1)&&m_180_270(sigma2))
        {delta_x_min=-R;}
        end:
        if(delta_x_max==0){delta_x_max=MAX(R*cos(sigma1),R*cos(sigma2));}
        if(delta_x_min==0){delta_x_min=MIN(R*cos(sigma1),R*cos(sigma2));}
        if(delta_y_max==0){delta_y_max=MAX(R*sin(sigma1),R*sin(sigma2));}
        if(delta_y_min==0){delta_y_min=MIN(R*sin(sigma1),R*sin(sigma2));}

        if(data->cx+delta_x_min<x_min) x_min=data->cx+delta_x_min;
        if(data->cx+delta_x_max>x_max) x_max=data->cx+delta_x_max;

        if(data->cy+delta_y_min<y_min) y_min=data->cy+delta_y_min;
        if(data->cy+delta_y_max>y_max) y_max=data->cy+delta_y_max;
    }
    ///обход окружностей
    size=(int) vec.DL_CircleData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_CircleData *data=&(vec.DL_CircleData_vector[i]);
        double r=data->radius;
        if(data->cx-r<x_min) x_min=data->cx-r;
        if(data->cx+r>x_max) x_max=data->cx+r;

        if(data->cy-r<y_min) y_min=data->cy-r;
        if(data->cy+r>y_max) y_max=data->cy+r;
    }
    ///обход эллипсов
    size=(int) vec.DL_EllipseData_vector.size();
    for(int i = 0; i < size; i++)
    {
        DL_EllipseData *data=&(vec.DL_EllipseData_vector[i]);
        double c=sqrt(pow(data->mx,2)+pow(data->my,2));
        double k=data->ratio;
        double a=sqrt(pow(c,2)/(1-pow(k,2)));
        double b=k*a;
        double angle1=data->angle1;
        double angle2=data->angle2;
        double cx=data->cx;
        double cy=data->cy;
        double mx=data->mx;
        double my=data->my;
        double angle=atan(my/mx);
        double min=angle1<angle2 ? angle1 : angle2;
        double max=angle1>angle2 ? angle1 : angle2;
        if(min<0.001&&max>6.28&&data->my<0.001)
        {
            if(cx-a<x_min) x_min=cx-a;
            if(cx+a>x_max) x_max=cx+a;
            if(cy-k*a<y_min) y_min=cy-k*a;
            if(cy+k*a>y_max) y_max=cy+k*a;
        }
        else
        {
            int count_vertex=64;
            double alpha_array[count_vertex];
            double x[count_vertex];
            double y[count_vertex];
            for(int i=0;i<count_vertex;i++)
            {
                if(angle>0.001)
                {
                    if(max<6.28&&min>0.001)
                    alpha_array[i]=i*((max-min)/((double)count_vertex))+min;
                    else alpha_array[i]=i*((2.0*M_PI)/((double)count_vertex))-angle;
                    double xr=a*cos(alpha_array[i]);
                    double yr=b*sin(alpha_array[i]);
                    x[i]=xr*cos(angle)-yr*sin(angle)+cx;
                    y[i]=xr*sin(angle)+yr*cos(angle)+cy;
                    if(x[i]<x_min) x_min=x[i];
                    if(x[i]>x_max) x_max=x[i];
                    if(y[i]<y_min) y_min=y[i];
                    if(y[i]>y_max) y_max=y[i];
                }
                else if(angle<=0.001)
                {
                    alpha_array[i]=i*(2.0*M_PI/((double)count_vertex));
                    x[i]=(a*cos(alpha_array[i])+cx);
                    y[i]=(b*sin(alpha_array[i])+cy);
                    if(x[i]<x_min) x_min=x[i];
                    if(x[i]>x_max) x_max=x[i];
                    if(y[i]<y_min) y_min=y[i];
                    if(y[i]>y_max) y_max=y[i];
                }
            }
        }
    }
    ///обход сплайнов
    size=(int) vec.spline_points.size();
    int j=0;i=0;
    for(; i<size; ++i)
    {   j=0;
        int size2=(int) vec.spline_points[i].size();
        for(; j<size2;++j)
        {
            double x=vec.spline_points[i][j].x;
            double y=vec.spline_points[i][j].y;
            if(x<x_min) x_min=x;
            if(x>x_max) x_max=x;
            if(y<y_min) y_min=y;
            if(y>y_max) y_max=y;
        }
    }
    range dxf_size;
    dxf_size.min_.x=x_min;
    dxf_size.max_.x=x_max;
    dxf_size.min_.y=y_min;
    dxf_size.max_.y=y_max;
    dxf_range=dxf_size; ///копирование в класс
    return dxf_size;
}

void svg_gen::min_max_values(data_vectors vec)
{
    double x_max=-10000, x_min=10000, y_max=-10000, y_min=10000;
    min_max_values(vec, x_min,x_max,y_min,y_max);
}

void svg_gen::svg_generate(char *filename)
{
    double x_min,x_max,y_min,y_max;
    min_max_values(common, x_min,x_max,y_min,y_max);

    char result[sizeof(standard_header)+64];
    sprintf(result,standard_header,x_max-x_min,y_max-y_min,x_max-x_min,y_max-y_min);

    this->resulting_svg.append(result);
    this->resulting_svg.append("<g fill=\"none\" stroke=\"black\" stroke-width=\"2.5\">");
    generate_lines(common, x_min, y_max);
    generate_arcs(common, x_min, y_max);
    generate_circles(common, x_min, y_max);
    generate_polyline(common, x_min, y_max);
    generate_ellipse(common, x_min, y_max);
    generate_spline(common, x_min,y_max);
    this->resulting_svg.append("</g>\n");
    this->resulting_svg.append("</svg>");

    dxf_manipulate dxf(this);
    dxf.rotate_dxf(this->common ,199);
    dxf.dxf_write(nullptr);

    ofstream test_svg;
    test_svg.open(filename);
    test_svg<<this->resulting_svg;
    test_svg.close();
}

