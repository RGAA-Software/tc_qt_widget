#pragma once

#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QBitmap>
#include <QPixmap>

#include <memory>
#include <mutex>

namespace sk {
	class Data;
	class Context;
	class WallpaperLocalEntity;
	class WallpaperPackLoader;
}

class RoundImageDisplay : public QLabel {
	Q_OBJECT
public:

	RoundImageDisplay(const QString& path, int width, int height, int radius, QWidget * parent = nullptr);
    RoundImageDisplay(const QPixmap& pixmap, int radius, QWidget * parent = nullptr);
	~RoundImageDisplay() override;

	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

	void UpdateImage(std::shared_ptr<sk::Context> ctx, std::shared_ptr<sk::WallpaperPackLoader> loader, std::shared_ptr<sk::WallpaperLocalEntity> entity);

private:
	QBitmap mask;
	QPixmap pixmap;
	QPixmap placeholder;
	int radius;

    std::mutex pixmap_mutex_;

};