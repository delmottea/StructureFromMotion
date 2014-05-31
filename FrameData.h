#ifndef FRAMEDATA_H
#define FRAMEDATA_H

#include <opencv.hpp>

enum TrackingMethod
{
    NoTracking,
    TrackingSAD,
    TrackingSSD,
    TrackingMethodCount
};

class PlanarTracker;

extern const char *TrackingMethodStr[];

//one frame of the sequence
class FrameData
{
public:
    cv::Mat frame;

    FrameData(cv::Mat frame);
};

//point values at one frame
class PointData
{
public:
    cv::Point2f p;//position of the point
    TrackingMethod trackMethod;
    cv::Size patchSize;
    cv::Size winSize;

    PointData();
    PointData *clone();
};

class Point
{
public:
    std::vector<PointData*> pointData; //point values at each frame, NULL if not computed at a frame

    PointData *getData(int id);
    void setData(int id, PointData *data);
};

class Line
{
public:
    Point *p[2];//ptr to the 2 points of the line

    Line();
};

class ShapeData
{
public:
    std::vector<Point*> vertex;//list of the points that define the shape
    bool manual;//true if the shape has been manually defined
    bool visible;
    bool computed;//true if the shape has been computed (tracked or manually defined)
    cv::Mat homography;//homography from the first frame
    std::vector<cv::Rect> listPatch;
    PlanarTracker *matcher;

    ShapeData();
};

class Shape
{
public:
    std::vector<ShapeData*> shapeData;//shapeData for each frame
    int maxPoints;

    Shape();
    ~Shape();
    ShapeData *getData(int frame);
};

class VideoData
{
public:
    std::string videoFile;
    std::vector<FrameData> listFrames;
    std::vector<Shape*> listShapes;
    std::vector<Point*> listPoints;
    std::vector<Line*> listLines;
    double fps;
    Shape *currentShape;
    Line *currentLine;
    Point *currentPoint;
    int currentFrame;

    VideoData();
};

#endif // FRAMEDATA_H
