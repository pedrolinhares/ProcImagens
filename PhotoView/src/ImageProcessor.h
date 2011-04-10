#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

class QImage;

class ImageProcessor {
	public:
		ImageProcessor();
		QImage* createGrayScaleImage (const QImage*);	
		QImage* nearestNeighborMethod(const QImage*, int, int);
		QImage* binarizeImage (const QImage*, int);
		QImage* applySobelFilter(const QImage*);
	private:
		int maskGX[3][3];
		int maskGY[3][3];
};

#endif //endif IMAGE_PROCESSOR_H


