#ifndef IO_H
#define IO_H

#include "FrameData.h"

void loadVideo(VideoData *video, const char *filename);
void load(VideoData *video, const char *filename);
void save(VideoData *video, const char *filename);

#endif // IO_H
