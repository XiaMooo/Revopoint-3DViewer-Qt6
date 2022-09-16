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

#ifndef _CS_VIEWERWINDOW_H
#define _CS_VIEWERWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <cstypes.h>
#include <hpp/Processing.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { 
    class ViewerWindow; 
}
QT_END_NAMESPACE

class RenderWidget2D;
class QFileDialog;
class QTranslator;
class CameraInfoDialog;
class CSProgressBar;
class CSMessageBox;
class ViewerWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum STACK_WIDGET_PAGE_ID
    {
        PARASETTING_PAGE = 0,
        CAMERALIST_PAGE = 1,
        PAGE_COUNT
    };

    enum RENDER_PAGE_ID
    {
        RENDER_PAGE_2D = 0,
        RENDER_PAGE_3D = 1,
        RENDER_PAGE_COUNT
    };

    enum CS_LANGUAGE
    {
        LANGUAGE_EN = 0,
        LANGUAGE_ZH,
        LANGUAGE_COUNT
    };

    ViewerWindow(QWidget* parent = nullptr);
    ~ViewerWindow();
private slots:
    void onClickedModeSwitchButton();
    void onPageChanged(int idx);
    void onRenderPageChanged(int idx);
    void onCameraStateChanged(int state);
    void onOutput2DUpdated(OutputData2D outputData);
    void onOutput3DUpdated(cs::Pointcloud pointCloud, const QImage& image);
    void onRoiEditStateChanged(bool edit);
    void onRoiRectFUpdated(QRectF rect);
    void onShowCoordChanged(bool show, QPointF pos);
    void onShow3DTextureChanged(bool texture);
    void onShowStatusBarMessage(QString msg, int timeout);
    void onClickedExport(int cameraType);
    void onExportFinished(bool success);
private slots:
    // menu
    void onUpdateLanguage(QAction* action);
    void onTriggeredAbout(QAction* action);
    void onTriggeredRestartCamera();
    void onExportPointCloud();
    void onTriggeredInformation();
    void onTriggeredLogDir();
    void onAppExit();
private slots:
    void onTranslate();
    void onRemovedCurrentCamera(QString serial);
    void onConfirmCameraRemoved();
    void onRenderInitialized();
    void onAboutToQuit();
signals:
    void translateSignal(); 
    void renderInitialized();
private:
    void initWindow();
    void initConnections();
    void initRenderWidgets();
    void destoryRender2dWidgets();
    void initRenderConnections();
    void onLanguageChanged();
    void updateStatusBar(int state);
private:
    Ui::ViewerWindow* ui;
    QMap<int, RenderWidget2D*> render2dWidgets;
    CS_LANGUAGE language;
    QTranslator* translator;

    CameraInfoDialog* cameraInfoDialog;
    CSProgressBar* circleProgressBar;
    CSMessageBox* globalMessageBox;
};
#endif // _CS_VIEWERWINDOW_H