#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

class QImage;

class ImageProcessor {
	public:
		QImage* createGrayScaleImage (const QImage*);	
		QImage* nearestNeighborMethod(const QImage*, int, int);
		QImage* binarizeImage (const QImage*, int);
};

#endif //endif IMAGE_PROCESSOR_H


