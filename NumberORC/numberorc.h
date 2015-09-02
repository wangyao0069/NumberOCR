#ifndef NUMBERORC_H
#define NUMBERORC_H

#include <QWidget>
#include <QtGui/QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QFileDialog>
#include <QMouseEvent>

#include "ui_numberorc.h"

#define NUM 3

typedef struct {
	int start;
	int end;
	int cur;
	int count;
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
	void LoadThumbnail(int index);
private:
	Ui::NumberORCClass ui;

	QStringList files;
	ImagesInfo imagesInfo;
	QImage* image[NUM];

	QLabel statusLabel;
};

#endif // NUMBERORC_H
