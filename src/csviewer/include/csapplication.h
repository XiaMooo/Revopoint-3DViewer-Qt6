/*******************************************************************************
* This file is part of the 3DViewer
*
* Copyright 2022-2026 (C) Revopoint3D AS
* All rights reserved.
*
* Revopoint3D Software License, v1.0
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistribution of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2. Redistribution in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* 3. Neither the name of Revopoint3D AS nor the names of its contributors may be used
* to endorse or promote products derived from this software without specific
* prior written permission.
*
* 4. This software, with or without modification, must not be used with any
* other 3D camera than from Revopoint3D AS.
*
* 5. Any software provided in binary form under this license must not be
* reverse engineered, decompiled, modified and/or disassembled.
*
* THIS SOFTWARE IS PROVIDED BY REVOPOINT3D AS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL REVOPOINT3D AS OR CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Info:  https://www.revopoint3d.com
******************************************************************************/

#ifndef _CS_CSAPPLICATION_H
#define _CS_CSAPPLICATION_H
#include <QObject>
#include <QImage>
#include <memory>
#include <cstypes.h>
#include <hpp/Processing.hpp>

class DataExporter;

namespace cs {
    
class CameraThread;
class ProcessThread;
class Processor;
class ICSCamera;
class CSApplication : public QObject
{
    Q_OBJECT
public:
    static CSApplication* getInstance();
    ~CSApplication();
    void start();
    std::shared_ptr<ICSCamera> getCamera() const;
public slots:
    void onOutput2DUpdated(OutputData2D outputData, StreamData streamData);
    void onOutput3DUpdated(cs::Pointcloud pointCloud, const QImage& image, StreamData streamData);

    //export data
    void onExportPointCloud(QString filePath);
    void onExportDepthData(QString filePath);
    void onExportRgbData(QString filePath);
signals:
    void cameraListUpdated(const QStringList infoList);
    void connectCamera(QString serial);
    void disconnectCamera();
    void restartCamera();
    void startStream();
    void pausedStream();
    void resumeStream();
    void queryCameras();

    void cameraStateChanged(int state);
    void output2DUpdated(OutputData2D outputData);
    void output3DUpdated(cs::Pointcloud pointCloud, const QImage& image);
    void removedCurrentCamera(QString serial);

    void exportFinished(bool success);
    void exportStreamData(StreamData streamData, QImage image, QString filePath);
    void exportPointCloud(cs::Pointcloud pointCloud, QImage image, QString filePath);
private:
    CSApplication();    
    void initConnections();
    void disconnections();
private:
    std::shared_ptr<CameraThread> cameraThread;
    std::shared_ptr<Processor> processor;
    std::shared_ptr<ProcessThread> processThread;
    std::shared_ptr<DataExporter> dataExporter;
    
    // cached data
    //1. depth
    StreamData cachedDepthData;
    QImage cachedDepthImage;

    //2. rgb
    StreamData cachedRgbData;
    QImage cachedRgbImage;

    //3. point cloud
    cs::Pointcloud cachedPointcloud;
    QImage cachedTextureImage;
};
}

#endif // _CS_CSAPPLICATION_H