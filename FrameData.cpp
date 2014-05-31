#include "FrameData.h"
#include <highgui/highgui.hpp>


const char *TrackingMethodStr[] = {"No Track", "SAD", "SSD"};


ShapeData::ShapeData()
    :computed(false), visible(true), manual(false)
{
}



FrameData::FrameData(cv::Mat frame)
    :frame(frame)
{
}

Shape::Shape()
{
    maxPoints = -1;
}

Shape::~Shape()
{
    for(int i = 0; i < shapeData.size(); i++)
        delete shapeData[i];
}

ShapeData *Shape::getData(int frame)
{
    while(frame >= shapeData.size())
        shapeData.push_back(new ShapeData());
    return shapeData[frame];
}

PointData::PointData()
{
    trackMethod = TrackingSSD;
    patchSize = cv::Size(20,20);
    winSize = cv::Size(50,50);
}

PointData *PointData::clone()
{
    PointData *p = new PointData();
    p->trackMethod = trackMethod;
    p->patchSize = patchSize;
    p->winSize = winSize;
    p->p = this->p;
}

PointData *Point::getData(int id)
{
    while(pointData.size() <= id)
        pointData.push_back(NULL);
    return pointData[id];
}

void Point::setData(int id, PointData *data)
{
    if(getData(id) != NULL)
        delete getData(id);
    pointData[id] = data;
}

Line::Line()
{
    p[0] = NULL;
    p[1] = NULL;
}

VideoData::VideoData()
{
    currentShape = NULL;
    currentLine = NULL;
    currentPoint = NULL;
}
