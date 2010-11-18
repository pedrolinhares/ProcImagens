#include "ImageProcessor.h"
#include <QtGui>

QImage* ImageProcessor::createGrayScaleImage (const QImage* image) {
    if (image != 0) {
		QImage *grayImage = new QImage(image->width(), image->height(),
							QImage::Format_RGB32);
		QRgb value, aux;
		value = qRgb(189,149,39);
		int red, green, blue, grey;
		
		for(int i = 0; i < image->width(); ++i)
			for (int j = 0; j  < image->height(); ++j) {
				aux = image->pixel (i, j);
				red   = qRed (aux);
				green = qGreen (aux);
				blue  =  qBlue (aux);
	
				//Obter cor tom cinza a partir do RGB do pixel
				grey = red * 0.3 + green * 0.59 + blue * 0.11;
				value = qRgb(grey, grey, grey);
				grayImage->setPixel(i, j, value);
			}
		return grayImage;	
	} else
		return 0;
}

QImage* ImageProcessor::nearestNeighborMethod (const QImage* image, 
												int newWidth, int newHeight) {

	if (image->isNull()) 
		return 0;
	else {
		QImage *scaledImage = new QImage (newWidth, newHeight, 
										  QImage::Format_RGB32);
		double x_ratio = (double)image->width() / newWidth;  //newWidth e newHeight != 0
		double y_ratio = (double)image->height() / newHeight;
		QRgb value;
		
		for (int i = 0; i < newWidth; ++i)
			for (int j = 0; j < newHeight; ++j) {
				value = image->pixel ((int)(i * x_ratio), (int)(j * y_ratio));
				scaledImage->setPixel (i, j, value);
			}
		return scaledImage;
	}
}

QImage* ImageProcessor::binarizeImage (const QImage* image, int limiar) {
	if (image->isNull())
		return 0;
	QImage *binIm = createGrayScaleImage(image);
	
	QRgb aux, value;
	int red;
	for (int i = 0; i < binIm->width(); i++)
		for (int j = 0; j < binIm->height(); j++) {
				aux = binIm->pixel (i, j);
				red   = qRed (aux);
				if (red < limiar) {
					value = qRgb(0, 0, 0);
					binIm->setPixel(i, j, value);
				} else {
					value = qRgb(255, 255, 255);
					binIm->setPixel(i, j, value);
				}
		}
	return binIm;
}
