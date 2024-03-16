#include "round_img_display.h"

#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QDebug>
#include <QImage>
#include <QPainterPath>

#include "core/cxx_code_base/log.h"
#include "core/cxx_code_base/file_ext.h"
#include "core/cxx_code_base/data.h"
#include "core/cxx_code_base/file.h"
#include "src/wallpaper/wallpaper_local_entity.h"
#include "wallpaper-loader/wallpaper_pack_loader.h"
#include "resource/resource_loader.h"
#include "cxx_code_base/image.h"
#include "src/context.h"

using namespace sk;

RoundImageDisplay::RoundImageDisplay(const QString& path, int width, int height, int radius, QWidget* parent) : QLabel(parent) {
	setFixedSize(width, height);
    this->radius = radius;
    placeholder = QPixmap(":/images/resources/ic_cover.jpg");
}

RoundImageDisplay::RoundImageDisplay(const QPixmap& pixmap, int radius, QWidget * parent) : QLabel(parent) {
    this->radius = radius;
    this->pixmap = pixmap;
}

RoundImageDisplay::~RoundImageDisplay() {

}

void RoundImageDisplay::UpdateImage(std::shared_ptr<Context> ctx, std::shared_ptr <sk::WallpaperPackLoader> loader, std::shared_ptr<sk::WallpaperLocalEntity> entity) {
    ctx->PostHeavyTask([=]() {
        //LOGI("wallpaper cover path : {0}", entity->wp_cover_path);
        bool exist = FileExt::Exist(entity->wp_cover_path);

        std::lock_guard<std::mutex> guard(pixmap_mutex_);

        if (exist) {
            pixmap = QPixmap(entity->wp_cover_path.c_str());
            if (this->width() > 0 && this->height() > 0) {
                pixmap = pixmap.scaled(this->width(), this->height(), Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);
            }
        }
        else {
            //LOGI("Load from skwp.. {0} ", entity->wp_gl_pack != nullptr);
            auto pack = loader->LoadWallpaperPack(entity->wp_res_path);
            if (pack && !pack->info_component().preview().empty()) {
                auto& data =pack->info_component().preview();
                
                auto dd = Data::From(data);
                ImagePtr img = ResourceLoader::LoadCompressedImageAsRaw(dd, ImageType::kJpg, false);
                if (img && img->data) {
                    auto image = QImage((const uchar*)img->data->CStr(), img->width, img->height, img->width*img->channels, QImage::Format::Format_RGB888);
                    pixmap = QPixmap::fromImage(image);
                    if (this->width() > 0 && this->height() > 0) {
                        pixmap = pixmap.scaled(this->width(), this->height(), Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
                    }
                }
            }
            else {
                if (!placeholder.isNull() && (placeholder.width() != this->width() || placeholder.height() != this->height())) {
                    placeholder = placeholder.scaled(this->width(), this->height(), Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
                }
                pixmap = placeholder;
            }
        }

        QMetaObject::invokeMethod(this, [=]() {
            //repaint();
            this->update();
        });
    });
}

void RoundImageDisplay::resizeEvent(QResizeEvent* event) {
    auto size = event->size();
    mask = QBitmap(size);
    //qDebug() << "size :" << size;
}

void RoundImageDisplay::paintEvent(QPaintEvent* event) { 
	QLabel::paintEvent(event);
    QPainter painter(this);

    std::lock_guard<std::mutex> guard(pixmap_mutex_);

    if (!pixmap.isNull() && painter.isActive()) {
        painter.setRenderHints(QPainter::Antialiasing, true);
        painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
        QPainterPath path;
        path.addRoundedRect(mask.rect(), radius, radius);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, pixmap);
    }
    else {
        painter.setBrush(QBrush(QColor(0x33, 0x33, 0x33)));
        painter.drawRoundedRect(0, 0, mask.width(), mask.height(), radius, radius);
    }

}                                                                       