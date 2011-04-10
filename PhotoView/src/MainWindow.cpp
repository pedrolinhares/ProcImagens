#include <QtGui>
#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow() {
    createActions();
    createMenus();

	image = new QImage;
	originalIm = new QImage;
	imageProcessor = new ImageProcessor;

    QHBoxLayout *layout = new QHBoxLayout;

    imageLabel = new QLabel;
    imageLabel->setLayout(layout);
    imageLabel->setAlignment (Qt::AlignCenter);

    setCentralWidget (imageLabel);
    
    setWindowTitle ("Visualizador de Imagens");
    setGeometry (250, 200, 800, 600);
	setMaximumSize (800,600);
}

void MainWindow::createActions() {
    //open action
    openAction = new QAction (tr("&Abrir"), this);    
    openAction->setShortcut (tr("Ctrl+a"));
    openAction->setStatusTip (tr("Abrir imagem."));
    connect (openAction, SIGNAL(triggered()), this, SLOT(openFileChooser()));

    //close action
    closeAction = new QAction (tr("Fechar"), this);
    closeAction->setStatusTip (tr("Fechar o programa."));
    connect(closeAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    //RGB to Greyscale action
    RGBtoGreyAction = new QAction (tr("Tons de Cinza"), this);
    RGBtoGreyAction->setStatusTip (tr("Converter imagem para imagem em tons de cinza"));
	RGBtoGreyAction->setEnabled (false);
    connect(RGBtoGreyAction, SIGNAL(triggered()), this, SLOT(toGrayScale()));
	
    //image size action
    imageSizeAction = new QAction (tr("Tamanho da imagem"), this);
    imageSizeAction->setStatusTip (tr("Alterar o tamanho da imagem"));
	imageSizeAction->setEnabled (false);
    connect(imageSizeAction, SIGNAL(triggered()), this, SLOT(resizeImageDialog()));

	//Binarizar imagem Action
	binarImAction = new QAction (tr("Binarizar imagem"), this);
	binarImAction->setStatusTip (tr("Binariza a imagem segundo o limiar fornecido"));
	binarImAction->setEnabled (false);
	connect (binarImAction, SIGNAL(triggered()), this, SLOT(binarImDialog()));
	
	//Apply sobel filter imagem Action
	sobelImAction = new QAction (tr("filtro Sobel"), this);
	sobelImAction->setStatusTip (tr("Detectar bordas"));
	sobelImAction->setEnabled (false);
	connect (sobelImAction, SIGNAL(triggered()), this, SLOT(applySobelFilter()));
	

	//restore original Image Action
	restoreOriginalImAction = new QAction (tr("Restaurar Imagem Original"), this);
	restoreOriginalImAction->setStatusTip (tr("Restaura a imagem original"));
	restoreOriginalImAction->setEnabled (false);
	connect (restoreOriginalImAction, SIGNAL(triggered()), this, SLOT(restoreOriginalIm()));
}

void MainWindow::createMenus() {
   fileMenu = menuBar()->addMenu (tr("Arquivo"));
   fileMenu->addAction (openAction);
   fileMenu->addSeparator();
   fileMenu->addAction (closeAction);

    imageMenu = menuBar()->addMenu (tr("Imagem"));
    imageMenu->addAction (RGBtoGreyAction);
    imageMenu->addAction (imageSizeAction);
    imageMenu->addAction (binarImAction);
	imageMenu->addAction (sobelImAction);
	imageMenu->addSeparator();
    imageMenu->addAction (restoreOriginalImAction);
}

//private slot
bool MainWindow::openFileChooser() {
   QString imageName = QFileDialog::getOpenFileName (this, tr("Escolha a imagem:"), ".",
                                                    tr("JPG (*.jpg)\n"
                                                        "Todos (*)")); 
   if (imageName.isEmpty())
       return false;
    
    loadImage (imageName);
    return true;
}

//private slot
void MainWindow::toGrayScale() {
		image = imageProcessor->createGrayScaleImage (image);
		imageLabel->setPixmap (QPixmap::fromImage (*image));
}

//private slot
void MainWindow::resizeImageDialog() {
	QDialog *dialog = new QDialog (this);
	dialog->setWindowTitle (tr("Ajuste o tamanho da imagem"));
	
	QSpinBox *imageWidth = new QSpinBox;
	QSpinBox *imageHeight = new QSpinBox;
	
	imageWidth->setRange (0, 2000);
	imageHeight->setRange (0, 2000);
	
	//Conecta os sinais dos spinsbox aos slots 
	connect (imageWidth, SIGNAL(valueChanged(int)), this, SLOT(setWidthValue(int)));
	connect (imageHeight, SIGNAL(valueChanged(int)), this, SLOT(setHeightValue(int)));
	
	//inicializa os valores de width e height da imagem atual
	imageWidth->setValue (image->width());
	imageHeight->setValue (image->height());
	
	//Cria labels
	QLabel *widthLabel = new QLabel(tr("Largura: ")); 
	QLabel *heightLabel = new QLabel(tr("Altura: "));
	
	//Conecta o label com spinbox
	widthLabel->setBuddy (imageWidth);
	heightLabel->setBuddy (imageHeight);
	
	//cria botoes ok e cancelar
	QPushButton *okButton = new QPushButton(tr("Ok"));
	QPushButton *cancelButton = new QPushButton(tr("Cancelar"));
	
	connect (okButton, SIGNAL(clicked()), this, SLOT(resizeImage()));
	connect (okButton, SIGNAL(clicked()), dialog, SLOT(close()));
	connect (cancelButton, SIGNAL(clicked()), dialog, SLOT(close()));
	
	//cria o combobox para escolha do metodo a ser utilizado
	QComboBox *methodComboBox = new QComboBox;
	methodComboBox->addItem ("Vizinho mais proximo", 0);
	methodComboBox->addItem ("Bilinear", 1);
	connect (methodComboBox, SIGNAL(activated(int)), this, SLOT(setChosenMethod(int)));
    
    //default eh 0 - vizinho mais proximo
    chosenMethod = 0;
	
	//Cria o layout de width e height 
	QHBoxLayout *dimensionLayout_1 = new QHBoxLayout;
	dimensionLayout_1->addWidget (widthLabel);
	dimensionLayout_1->addWidget (imageWidth);
	
	QHBoxLayout *dimensionLayout_2 = new QHBoxLayout;
	dimensionLayout_2->addWidget (heightLabel);
	dimensionLayout_2->addWidget (imageHeight);
	
	QVBoxLayout *vLayout = new QVBoxLayout;
	vLayout->addLayout (dimensionLayout_1);
	vLayout->addLayout (dimensionLayout_2);
	
	QHBoxLayout *methodLayout = new QHBoxLayout;
	methodLayout->addWidget (methodComboBox);
	
	//Cria o group Box
	QGroupBox *dimensionBox = new QGroupBox (tr("Dimensoes da imagem"));
	dimensionBox->setLayout (vLayout);
	
	//cria o box com o combo box dos metodos
	QGroupBox *methodBox = new QGroupBox (tr("Metodo de interpolacao"));
	methodBox->setLayout (methodLayout);
	
	vLayout = new QVBoxLayout;
	vLayout->addWidget (dimensionBox);
	vLayout->addWidget (methodBox);
	
	//Cria o layout dos botoes
	QVBoxLayout *vButtonLayout = new QVBoxLayout;
	vButtonLayout->addWidget (okButton);
	vButtonLayout->addWidget (cancelButton);
	vButtonLayout->addStretch();
	vButtonLayout->addStretch();
	vButtonLayout->addStretch();
	
	//Cria o layout da janela
	QHBoxLayout *dialogLayout = new QHBoxLayout;
	dialogLayout->addLayout (vLayout);
	dialogLayout->addLayout (vButtonLayout);
	
	//Para a janela ter um tamanho fixo respeitando o tamanho do layout
	dialogLayout->setSizeConstraint(QLayout::SetFixedSize);

	dialog->setLayout (dialogLayout);
	dialog->exec();
}

//private slot
void MainWindow::binarImDialog() {
	QDialog *dialog = new QDialog(this);	
	dialog->setWindowTitle (tr("Binarizacao"));

	QLineEdit *limiarEdit = new QLineEdit (this);
	QLabel *limiarLabel = new QLabel (tr("Limiar (0..255): "));

	limiarLabel->setBuddy (limiarEdit);

	//cria validador de int
	QIntValidator *intValidator = new QIntValidator (0, 255, limiarEdit);

	limiarEdit->setValidator (intValidator);

	connect (limiarEdit, SIGNAL(textChanged(const QString&)), this, 
								SLOT(enableBinButton(const QString&)));

	//cria botoes ok e cancelar
	binOkButton = new QPushButton(tr("Ok"));
	binOkButton->setEnabled (false);
	QPushButton *cancelButton = new QPushButton(tr("Cancelar"));

	connect (binOkButton, SIGNAL(clicked()), this, SLOT(binarizeImage()));
	connect (binOkButton, SIGNAL(clicked()), dialog, SLOT(close()));
	connect (cancelButton, SIGNAL(clicked()), dialog, SLOT(close()));
	
	QHBoxLayout *hlay = new QHBoxLayout;
	hlay->addWidget (limiarLabel);
	hlay->addWidget (limiarEdit);
	
	QVBoxLayout *vlay = new QVBoxLayout;
	vlay->addWidget (binOkButton);
	vlay->addWidget (cancelButton);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addLayout (hlay);
	layout->addLayout (vlay);

	layout->setSizeConstraint (QLayout::SetFixedSize);

	dialog->setLayout (layout);
	dialog->exec();
}

//private slot
void MainWindow::enableBinButton (const QString& text) {
	if (!text.isEmpty()) {
		binOkButton->setEnabled (true);
		limiar = text.toInt();
	}
}

//private slot
void MainWindow::binarizeImage() {
	image = imageProcessor->binarizeImage (image, limiar);
	imageLabel->setPixmap (QPixmap::fromImage (*image)); 
}

//private slot
void MainWindow::setWidthValue (int value) {
	newWidth = value;
}

//private slot
void MainWindow::setHeightValue (int value) {
	newHeight = value;
}

//private slot
void MainWindow::setChosenMethod(int index) { 
   chosenMethod =  index;
}

//private slot
void MainWindow::restoreOriginalIm() {
	image = originalIm;
	imageLabel->setPixmap (QPixmap::fromImage (*image)); 
}

//private slot
//chama o metodo escolhido de imageProcessor para calcular nova imagem
void MainWindow::resizeImage(){
    if (chosenMethod == 0)
		image = imageProcessor->nearestNeighborMethod (image, newWidth, newHeight);
	imageLabel->setPixmap (QPixmap::fromImage (*image)); 
}

//private slot
void MainWindow::applySobelFilter() {
	image = imageProcessor->applySobelFilter (image);
	imageLabel->setPixmap (QPixmap::fromImage (*image)); 
}

bool MainWindow::loadImage (const QString& imageName) {
    image->load (imageName);

    if (image->isNull()) {
        QMessageBox::information (this, tr("Image View"), 
                tr("Nao foi possivel abrir arquivo: %1").arg(imageName));
		RGBtoGreyAction->setEnabled (false);
		imageSizeAction->setEnabled (false);
        return false;

    }
	if (originalIm->isNull())
		originalIm = image;

    //Setting the pixmap clears any previous content. 
    imageLabel->setPixmap (QPixmap::fromImage (*image));

	//Enabling the functionalities once we have a image
	RGBtoGreyAction->setEnabled (true);
	imageSizeAction->setEnabled (true);
	restoreOriginalImAction->setEnabled (true);
	binarImAction->setEnabled (true);
	sobelImAction->setEnabled (true);

    setWindowTitle (tr("Visualizador de Imagens - (%1)").arg(imageName));

    return true;
}
