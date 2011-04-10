#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ImageProcessor.h"

class QPushButton;
class QMenu;
class QAction;
class QImage;
class QLabel;

class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        MainWindow();
    
    private slots:
        bool openFileChooser();
		void toGrayScale();
		void applySobelFilter();
		void resizeImageDialog();
		void resizeImage();
		void restoreOriginalIm();
		void binarImDialog();
		void binarizeImage();
		void setWidthValue (int);
		void setHeightValue (int);
		void setChosenMethod (int);
		void enableBinButton (const QString& text);

    private:
        void createActions();
        void createMenus();
        bool loadImage (const QString&);
        
        QMenu			*fileMenu;
        QMenu			*imageMenu;
        QAction			*openAction;
        QAction			*closeAction;
        QAction			*RGBtoGreyAction;
        QAction			*imageSizeAction;
        QAction			*restoreOriginalImAction;
        QAction			*binarImAction;
        QAction			*sobelImAction;
        QImage			*image;
        QImage			*originalIm;
        QLabel			*imageLabel;
		ImageProcessor  *imageProcessor;
		QPushButton		*binOkButton;
		int				chosenMethod;
		int				newWidth;
		int				newHeight;
		int				limiar;
};

#endif
