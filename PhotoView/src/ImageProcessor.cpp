#include "ImageProcessor.h"
#include <QtGui>

ImageProcessor::ImageProcessor() {
	//Mascara GX
	maskGX[0][0] = -1; maskGX[0][1] = 0; maskGX[0][2] = 1;
	maskGX[1][0] = -2; maskGX[1][1] = 0; maskGX[1][2] = 2;
	maskGX[2][0] = -1; maskGX[2][1] = 0; maskGX[2][2] = 1;
	
	//Mascara GY
	maskGY[0][0] =  1; maskGY[0][1] =  2; maskGY[0][2] =  1;
	maskGY[1][0] =  0; maskGY[1][1] =  0; maskGY[1][2] =  0;
	maskGY[2][0] = -1; maskGY[2][1] = -2; maskGY[2][2] = -1;	
}

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

QImage* ImageProcessor::applySobelFilter(const QImage* image) {
	QImage* returnImg= new QImage (image->width(), image->height(),
							  QImage::Format_RGB32);
	
	double sumX, sumY, sum;
	QRgb pixel;
	
	//multiplica pro GX
	for (int i = 0; i < image->width(); i++) {
		for (int j = 0; j < image->height(); j++) {
			sumX = 0;
			sumY = 0;
			
			//limites da imagem
			if (i == 0 || i == image->width() - 1)
				sum = 0;
			else if (j == 0 || i == image->height() - 1)
				sum = 0;
			
			else {
				//multiplicar pelas mascaras aqui..
				for (int I = -1; I <= 1; I++) {
					for (int J = -1; J <= 1; J++) {
						int piX = J + j;
						int piY = I + i;
						
						pixel = image->pixel(piX, piY);
						int R = qRed (pixel);
						int G = qGreen (pixel);
						int B = qBlue (pixel);
						
						int cinza = (R + G + B) / 3;
						
						sumX = sumX + (cinza) * maskGX[J + 1][I + 1];
						sumY = sumY + (cinza) * maskGY[J + 1][I + 1];
					}
				}
				sum = abs(sumX) + abs(sumY);
			}
			if (sum > 255) 
				sum = 255;
			if (sum < 0)
				sum = 0;
			
			int newPixel = (255 - (unsigned char)(sum));
			pixel = qRgb(newPixel, newPixel, newPixel);
			returnImg->setPixel (j, i, pixel);
		}
	}
	return returnImg;
}





