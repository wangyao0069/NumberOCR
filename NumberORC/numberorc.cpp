#include "numberorc.h"

NumberORC::NumberORC(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	//unable buttons
	ui.pushButton_pre->setEnabled(false);
	ui.pushButton_next->setEnabled(false);
	ui.pushButton_recognization->setEnabled(false);
	ui.label_1->hide();
	ui.label_2->hide();
	ui.label_3->hide();

	for (int i = 0; i < NUM; i++)
	{
		image[i] = NULL;
	}

	connect(ui.pushButton_openfiles, SIGNAL(clicked()),
		this, SLOT(OpenFiles()));
	connect(ui.pushButton_pre, SIGNAL(clicked()),
		this, SLOT(PreImage()));
	connect(ui.pushButton_next, SIGNAL(clicked()),
		this, SLOT(NextImage()));
	connect(ui.pushButton_openfiles, SIGNAL(clicked()),
		this, SLOT(Recognition()));

	ui.label_main->installEventFilter(this);
}

NumberORC::~NumberORC()
{
	for (int i = 0; i < NUM; i++)
	{
		if (image[i] != NULL)
		{
			delete image[i];
			image[i] = NULL;
		}
	}
}

bool NumberORC::eventFilter(QObject *obj, QEvent *e)
{
	if (obj == ui.label_main)
	{
		if (e->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent* me = dynamic_cast<QMouseEvent*>(e);
			imagesInfo.x_s = me->x();
			imagesInfo.y_s = me->y();
			int width = ui.label_main->width();
			int height = ui.label_main->height();

			if (height > imagesInfo.height)
			{
				int y = me->y() - (height - imagesInfo.height)/2;
				imagesInfo.y_s = y < 0 ? 0 : y;	
			}
			imagesInfo.y_s = imagesInfo.y_s>imagesInfo.height?imagesInfo.height:imagesInfo.y_s;
			imagesInfo.x_s = imagesInfo.x_s>imagesInfo.width?imagesInfo.width:imagesInfo.x_s;

			this->statusLabel.setText(QString("press%1   %2   label width:%3   %4    image width %5   %6")
				.arg(imagesInfo.x_s).arg(imagesInfo.y_s).arg(width).arg(height).arg(imagesInfo.width).arg(imagesInfo.height));
			ui.statusBar->addWidget(&(this->statusLabel));
		}
		if (e->type() == QEvent::MouseMove )
		{
			QMouseEvent* me = dynamic_cast<QMouseEvent*>(e);
			imagesInfo.x_e = me->x();
			imagesInfo.y_e = me->y();
			int width = ui.label_main->width();
			int height = ui.label_main->height();
			if (height > imagesInfo.height)
			{
				int y = me->y() - (height - imagesInfo.height)/2;
				imagesInfo.y_e = y < 0 ? 0 : y;	
			}
			if ((imagesInfo.x_e-imagesInfo.x_s)%4 == 0 || (imagesInfo.y_e-imagesInfo.y_s)/4 == 0)
			{
				DrawImageRect();
			}
			imagesInfo.y_e = imagesInfo.y_e>imagesInfo.height?imagesInfo.height:imagesInfo.y_e;
			imagesInfo.x_e = imagesInfo.x_e>imagesInfo.width?imagesInfo.width:imagesInfo.x_e;
		}
		if (e->type() == QEvent::MouseButtonRelease )
		{
			QMouseEvent* me = dynamic_cast<QMouseEvent*>(e);
			imagesInfo.x_e = me->x();
			imagesInfo.y_e = me->y();
			int width = ui.label_main->width();
			int height = ui.label_main->height();
			if (height > imagesInfo.height)
			{
				int y = me->y() - (height - imagesInfo.height)/2;
				imagesInfo.y_e = y < 0 ? 0 : y;	
			}
			imagesInfo.y_e = imagesInfo.y_e>imagesInfo.height?imagesInfo.height:imagesInfo.y_e;
			imagesInfo.x_e = imagesInfo.x_e>imagesInfo.width?imagesInfo.width:imagesInfo.x_e;

			this->statusLabel.setText(QString("release"));
			ui.statusBar->addWidget(&(this->statusLabel));
		}
	}
	return QMainWindow::eventFilter(obj, e);
}

void NumberORC::DrawImageRect()
{
	QImage* curImg = image[imagesInfo.cur];
	imagesInfo.width = ui.groupBox_view->width();
	imagesInfo.height = int(imagesInfo.width*1.0*curImg->height()/curImg->width());
	QSize picSize(imagesInfo.width, imagesInfo.height);
	QImage tmp = curImg->scaled(picSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	QColor red(255, 0, 0);  
	for (int i = imagesInfo.x_s; i < imagesInfo.x_e; i += 2)
	{
		tmp.setPixel(i, imagesInfo.y_e, red.rgba());
		tmp.setPixel(i, imagesInfo.y_s, red.rgba());
	}
	for (int i = imagesInfo.y_s; i < imagesInfo.y_e; i += 2)
	{
		tmp.setPixel(imagesInfo.x_e, i, red.rgba());
		tmp.setPixel(imagesInfo.x_s, i, red.rgba());
	}
	ui.label_main->setPixmap(QPixmap::fromImage(tmp));
	ui.pushButton_recognization->setEnabled(true);
}

void NumberORC::OpenFiles()
{
	//when open files, reset images
	for (int i = 0; i < NUM; i++)
	{
		if (image[i] != NULL)
		{
			delete image[i];
			image[i] = NULL;
		}
	}
	QFileDialog::Options options;
	QString selectedFilter;
	QString openFilesPath = "/";
	files = QFileDialog::getOpenFileNames(
		this, tr("QFileDialog::getOpenFileNames()"),
		"/",
		tr("Image Files (*.png *.jpg);;All Files (*)"),
		&selectedFilter,
		options);
	if (files.count()) {
		imagesInfo.cur = 0;
		imagesInfo.count = files.count();

		this->statusLabel.setText(QString("total %1 images, current %2 image").arg(files.count()).arg(1));
		ui.statusBar->addWidget(&(this->statusLabel));
		this->LoadImages();
	}
}

void NumberORC::LoadImages()
{
	//first reload images
	if (image[0] == NULL)
	{
		int size = NUM < files.count() ? NUM : files.count();
		imagesInfo.start = 0;
		imagesInfo.end = size;
		for (int i = 0; i < size; i++)
		{
			image[i] = new QImage(files[i]);
			if (imagesInfo.count != 1)
			{
				LoadThumbnail(i);
			}
		}
		ui.pushButton_next->setEnabled(true);
	}

	//show current image;
	QImage* curImg = image[imagesInfo.cur];
	imagesInfo.width = ui.groupBox_view->width();
	imagesInfo.height = int(imagesInfo.width*1.0*curImg->height()/curImg->width());
	QSize picSize(imagesInfo.width, imagesInfo.height);
	ui.label_main->setPixmap(QPixmap::fromImage(curImg->scaled(picSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
	ui.pushButton_recognization->setEnabled(true);

	//reset roi start point and end point
	imagesInfo.x_s = -1;
	imagesInfo.y_s = -1;
	imagesInfo.x_e = -1;
	imagesInfo.y_e = -1;
}

void NumberORC::LoadThumbnail(int index)
{
	int width = ui.scrollArea->width()/3;
	int height = width;//int(width*1.0*ui.label_1->height()/ui.label_1->width());
	QSize picSize(width, height);
	switch (index)
	{
	case 0:
		ui.label_1->setPixmap(QPixmap::fromImage(image[index]->scaled(picSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
		ui.label_1->show();
		if (index == imagesInfo.cur)
		{
			ui.label_1->setStyleSheet("border:2px solid red");
		} else {
			ui.label_1->setStyleSheet("");
		}
		break;
	case 1:
		ui.label_2->setPixmap(QPixmap::fromImage(image[index]->scaled(picSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
		ui.label_2->show();
		if (index == imagesInfo.cur)
		{
			ui.label_2->setStyleSheet("border:2px solid red");
		} else {
			ui.label_2->setStyleSheet("");
		}
		break;
	case 2:
		ui.label_3->setPixmap(QPixmap::fromImage(image[index]->scaled(picSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
		ui.label_3->show();
		if (index == imagesInfo.cur)
		{
			ui.label_3->setStyleSheet("border:2px solid red");
		} else {
			ui.label_3->setStyleSheet("");
		}
		break;

	}
	//ui.label_1->setPixmap(QPixmap::fromImage(image[index]->scaled(picSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
}

void NumberORC::PreImage()
{
	if (imagesInfo.start > 0)
	{
		for (int i = NUM-1; i > 0; i--)
		{
			if (i == NUM-1 && image[i] != NULL)
			{
				delete image[i];
				image[i] = NULL;
			}
			image[i] = image[i-1];
		}
		imagesInfo.end--;
		//imagesInfo.cur--;
		imagesInfo.start--;
		image[0] = new QImage(files[imagesInfo.start]);
	} else if (imagesInfo.cur > 0)
	{
		imagesInfo.cur--;
	}
	for (int i = 0; i < imagesInfo.count; i++)
	{
		LoadThumbnail(i);
	}

	LoadImages();

	if (imagesInfo.start+imagesInfo.cur == 0)
	{
		ui.pushButton_pre->setEnabled(false);
	} else {
		ui.pushButton_pre->setEnabled(true);
	}
	ui.pushButton_next->setEnabled(true);

	this->statusLabel.setText(QString("total %1 images, current %2 image").arg(files.count()).arg(imagesInfo.start+imagesInfo.cur+1));
	ui.statusBar->addWidget(&(this->statusLabel));
}

void NumberORC::NextImage()
{
	if (imagesInfo.end < imagesInfo.count)
	{
		for (int i = 0; i < NUM-1; i++)
		{
			if (i == 0 && image[i] != NULL)
			{
				delete image[i];
				image[i] = NULL;
			}
			image[i] = image[i+1];
		}
		imagesInfo.start++;
		imagesInfo.end++;
		//imagesInfo.cur;
		image[NUM-1] = new QImage(files[imagesInfo.end-1]);
	} else if (imagesInfo.cur < NUM-1)
	{
		imagesInfo.cur++;
	}
	for (int i = 0; i < imagesInfo.count; i++)
	{
		LoadThumbnail(i);
	}

	LoadImages();

	if (imagesInfo.start+imagesInfo.cur == imagesInfo.count-1)
	{
		ui.pushButton_next->setEnabled(false);

	} else {
		ui.pushButton_next->setEnabled(true);
	}
	ui.pushButton_pre->setEnabled(true);

	this->statusLabel.setText(QString("total %1 images, current %2 image").arg(files.count()).arg(imagesInfo.start+imagesInfo.cur+1));
	ui.statusBar->addWidget(&(this->statusLabel));

}

void NumberORC::Recognition()
{
	if (imagesInfo.x_e == -1 ||
		imagesInfo.x_s == -1 ||
		imagesInfo.y_e == -1 ||
		imagesInfo.y_s == -1)
	{
		QSize picSize(imagesInfo.width, imagesInfo.height);
		roi = &image[imagesInfo.cur]->scaled(picSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	} else {
		QSize picSize(imagesInfo.width, imagesInfo.height);
		roi = &image[imagesInfo.cur]->scaled(picSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)
			.copy(imagesInfo.x_s, imagesInfo.y_s, (imagesInfo.x_e-imagesInfo.x_s), (imagesInfo.y_e-imagesInfo.y_s));
	}

	IplImage* img = QImageToIplImage(roi);





	delete img;
	img = NULL;
}

IplImage *QImageToIplImage(const QImage * qImage)  
{  
	int width = qImage->width();  
	int height = qImage->height();  
	CvSize Size;  
	Size.height = height;  
	Size.width = width;  
	IplImage *IplImageBuffer = cvCreateImage(Size, IPL_DEPTH_8U, 3);  
	for (int y = 0; y < height; ++y)  
	{  
		for (int x = 0; x < width; ++x)  
		{  
			QRgb rgb = qImage->pixel(x, y);  
			cvSet2D(IplImageBuffer, y, x, CV_RGB(qRed(rgb), qGreen(rgb), qBlue(rgb)));  
		}  
	}  

	return IplImageBuffer;  
}