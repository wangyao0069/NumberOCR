#ifndef NUMBERORC_H
#define NUMBERORC_H

#include <QWidget>
#include <QtGui/QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QFileDialog>
#include <QMouseEvent>

#include "ui_numberorc.h"
#include<opencv2/opencv.hpp>

#define NUM 3

typedef struct {
	int start;
	int end;
	int cur;
	int count;

	int x_s;
	int y_s;
	int x_e;
	int y_e;

	int width;
	int height;
} ImagesInfo;

class NumberORC : public QMainWindow
{
	Q_OBJECT

public:
	NumberORC(QWidget *parent = 0, Qt::WFlags flags = 0);
	~NumberORC();
protected:
	bool eventFilter(QObject *obj, QEvent *e);
	private slots:
		void OpenFiles();
		void PreImage();
		void NextImage();
		void Recognition();
private:
	void LoadImages();
	void DrawImageRect();
	void LoadThumbnail(int index);
	IplImage *QImageToIplImage(const QImage * qImage);
private:
	Ui::NumberORCClass ui;

	QStringList files;
	ImagesInfo imagesInfo;
	QImage* image[NUM];
	QImage* roi;
	QLabel statusLabel;
};

#endif // NUMBERORC_H
