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

#ifndef _CS_CAMERAPROXY_H
#define _CS_CAMERAPROXY_H

#include "icscamera.h"
#include "cscameraapi.h"
#include "cameraparaid.h"

#include <QReadWriteLock>
#include <QPointF>

namespace cs {

class CS_CAMERA_EXPORT CameraProxy : public ICSCamera
{
    Q_OBJECT
    Q_PROPERTY(bool showDepthCoord READ getShowDepthCoord WRITE setShowDepthCoord NOTIFY showDepthCoordChanged)
    Q_PROPERTY(QPointF showDepthCoordPos READ getShowDepthCoordPos WRITE setShowDepthCoordPos NOTIFY showDepthCoordPosChanged)
    Q_PROPERTY(bool showRender3D READ getShowRender3D WRITE setShowRender3D NOTIFY showRender3DChanged)
    Q_PROPERTY(bool show3DWithTexture READ getShow3DWithTexture WRITE setShow3DWithTexture NOTIFY show3DWithTextureChanged)
public:
    CameraProxy();
    ~CameraProxy();

    void getCameraPara(parameter::CAMERA_PARA_ID paraId, QVariant& value) override;
    void setCameraPara(parameter::CAMERA_PARA_ID paraId, QVariant value) override;
    void getCameraParaRange(parameter::CAMERA_PARA_ID paraId, QVariant& min, QVariant& max, QVariant& step) override;
    void getCameraParaItems(parameter::CAMERA_PARA_ID paraId, QList<QPair<QString, QVariant>>& list) override;

    bool disconnectCamera() override;
    bool reconnectCamera() override;

    bool startStream() override;
    bool stopStream() override;
    bool restartStream()override;
    bool restartCamera() override;
    bool pauseStream() override;
    bool resumeStream() override;
    bool softTrigger() override;

    void bindCamera(ICSCamera* camera);
    void unBindCamera();
    CSCameraInfo getCameraInfo() const override;
    int getCameraState() const override;

    bool getShowDepthCoord() const;
    void setShowDepthCoord(bool show);
    QPointF getShowDepthCoordPos() const;
    void setShowDepthCoordPos(QPointF pos);
    bool getShowRender3D() const;
    void setShowRender3D(bool show);
    bool getShow3DWithTexture() const;
    void setShow3DWithTexture(bool with);
signals:
    void showDepthCoordChanged(bool show);
    void showDepthCoordPosChanged(QPointF pos);
    void showRender3DChanged(bool show);
    void show3DWithTextureChanged(bool with);
private:
    ICSCamera* csCamera = nullptr;
    mutable QReadWriteLock lock;
    bool showDepthCoord;
    QPointF showDepthCoordPos;
    bool showRender3D;
    bool show3DWithTexture;
};
}

#endif // _CS_CAMERAPROXY_H