#include "IO.h"
#include <QDebug>
#include <QtXml>
#include <QMessageBox>

void loadVideo(VideoData *video, const char *filename)
{
    video->videoFile = filename;
    cv::VideoCapture cap(filename);
    if ( !cap.isOpened() )
    {
        qDebug() << "can't open video!!!";
        return ;
    }
    video->fps = cap.get(CV_CAP_PROP_FPS);

    cv::Mat frame;
    for(int i = 0; cap.read(frame); i++)
        video->listFrames.push_back(FrameData(frame.clone()));
}

void load(VideoData *video, const char *filename)
{
    video->listFrames.clear();
    video->listPoints.clear();
    video->listShapes.clear();
    QFile fichier(filename);
    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(NULL, "QXSRExample::parseXML", "Couldn't open xml", QMessageBox::Ok);
        return;
    }
    QDomDocument doc;
    if(!doc.setContent(&fichier))
    {
        return;
    }
    QDomElement root = doc.firstChildElement("root");

    QDomElement videoElement = root.firstChildElement("video");
    loadVideo(video, videoElement.attribute("src").toStdString().c_str());

    QDomElement listPointsElement = root.firstChildElement("points");
    QDomNodeList pointsList = listPointsElement.elementsByTagName("point");
    for(int i = 0; i < pointsList.size(); i++)
    {
        QDomElement pointElement = pointsList.at(i).toElement();
        Point *p = new Point();
        QDomNodeList dataList = pointElement.elementsByTagName("data");
        for(int j = 0; j < dataList.size(); j++)
        {
            QDomElement dataElement = dataList.at(j).toElement();
            PointData *data = new PointData();
            bool ok;
            int id = dataElement.attribute("id").toInt(&ok);
            if(ok)
                p->setData(id, data);
            float x = dataElement.attribute("x").toFloat(&ok);
            if(ok)
                data->p.x = x;
            float y = dataElement.attribute("y").toFloat(&ok);
            if(ok)
                data->p.y = y;
        }
        video->listPoints.push_back(p);
    }
    fichier.close();
}

void save(VideoData *video, const char *filename)
{
    QDomDocument doc;
    QDomProcessingInstruction instr = doc.createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");
    doc.appendChild(instr);

    QDomElement rootNode = doc.createElement("root");
    doc.appendChild(rootNode);

    QDomElement videoElement = doc.createElement("video");
    videoElement.setAttribute("src", video->videoFile.c_str());
    rootNode.appendChild(videoElement);

    QDomElement listPointsElement = doc.createElement("points");
    for(int i = 0; i < video->listPoints.size(); i++)
    {
        QDomElement pointElement = doc.createElement("point");
        for(int j = 0; j < video->listPoints[i]->pointData.size(); j++)
        {
            PointData *data = video->listPoints[i]->pointData[j];
            if(data != NULL)
            {
                QDomElement dataElement = doc.createElement("data");
                dataElement.setAttribute("id", j);
                dataElement.setAttribute("x", data->p.x);
                dataElement.setAttribute("y", data->p.y);
                pointElement.appendChild(dataElement);
            }
        }
        listPointsElement.appendChild(pointElement);
    }
    rootNode.appendChild(listPointsElement);
    QFile fichier(filename);
    if(!fichier.open(QIODevice::WriteOnly))
    {
        fichier.close();
        QMessageBox::critical(NULL,"Erreur","Impossible d'écrire dans le document XML");
        return;
    }
    QTextStream stream(&fichier);
    stream << doc;
    fichier.close();
}
