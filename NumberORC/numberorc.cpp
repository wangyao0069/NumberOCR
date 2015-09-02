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
			this->statusLabel.setText(QString("press%1   %2").arg(me->x()).arg(me->y()));
			ui.statusBar->addWidget(&(this->statusLabel));
		}
		if (e->type() == QEvent::MouseButtonRelease ) //ÆÁ±ÎMouseButtonReleaseºÍMouseMoveÊÂ¼þ
		{
			this->statusLabel.setText(QString("release"));
			ui.statusBar->addWidget(&(this->statusLabel));
		}
		else
		{

		}
	}
	return QMainWindow::eventFilter(obj, e);
}

void NumberORC::OpenFiles()
{
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
	QImage* curImg = image[imagesInfo.cur];
	//image.load(files[imagesInfo.start+index]) ;

	int width = ui.groupBox_view->width();
	int height = int(width*1.0*curImg->height()/curImg->width());
	QSize picSize(width, height);
	ui.label_main->setPixmap(QPixmap::fromImage(curImg->scaled(picSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
	//.scaled(picSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)
	//img.scaled(800, 600).scaled(200, 150, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ui.pushButton_recognization->setEnabled(true);
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

}