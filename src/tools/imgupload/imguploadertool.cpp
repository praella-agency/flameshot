// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#include "imguploadertool.h"
#include "src/tools/imgupload/storages/imgur/imguruploader.h"
#include "src/tools/droplr/droplruploader.h"
#include "src/utils/confighandler.h"

ImgUploaderTool::ImgUploaderTool(QObject* parent)
  : AbstractActionTool(parent)
{}

bool ImgUploaderTool::closeOnButtonPressed() const
{
    return true;
}

QIcon ImgUploaderTool::icon(const QColor& background, bool inEditor) const
{
    Q_UNUSED(inEditor);
    if(ConfigHandler().cloudImgur()) {
        return QIcon(iconPath(background) + "cloud-upload.svg");
    } else {
        return QIcon(iconPath(background) + "droplr.svg");
    }
}

QString ImgUploaderTool::name() const
{
    return tr("Image Uploader");
}

CaptureTool::Type ImgUploaderTool::type() const
{
    return CaptureTool::TYPE_IMAGEUPLOADER;
}

QString ImgUploaderTool::description() const
{
    if(ConfigHandler().cloudImgur()) {
        return tr("Upload the selection");
    } else {
        return tr("Upload the selection to Droplr");
    }
}

QWidget* ImgUploaderTool::widget()
{
    if(ConfigHandler().cloudImgur()) {
        return new ImgurUploader(capture);
    } else {
        return new DroplrUploader(capture);
    }
}

CaptureTool* ImgUploaderTool::copy(QObject* parent)
{
    return new ImgUploaderTool(parent);
}

void ImgUploaderTool::pressed(CaptureContext& context)
{
    emit requestAction(REQ_CLEAR_SELECTION);
    emit requestAction(REQ_CAPTURE_DONE_OK);
    context.request.addTask(CaptureRequest::UPLOAD);
    emit requestAction(REQ_CLOSE_GUI);
}
