#include "FrameData.h"
#include "IO.h"
#include <QDebug>

int main()
{
    VideoData video;
    load(&video, "test/test.xml");

    for(int frame = 0; frame < video.listFrames.size(); frame++)
    {
        cv::Mat img = video.listFrames[frame].frame.clone();
        for(int i = 0; i < video.listPoints.size(); i++)
        {
            Point *p = video.listPoints[i];
            PointData *data = p->getData(frame);
            if(data != NULL)
            {
                cv::circle(img, data->p, 4, cv::Scalar(255,255,255), 2);
                cv::circle(img, data->p, 6, cv::Scalar(0,0,0), 1);
            }
        }
        cv::imshow("video", img);
        if(cv::waitKey(0) == 1048603)
            return 0;
    }
    return 0;
}
