#include "Image.h"
#include <Windows.h>

Image::Image(int screenWidth, int screenHeight, int stepX, int stepY, string imgPath) {
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->stepX = stepX;
	this->stepY = stepY;
	this->image = cv::imread("C:\\Users\\bartv\\Downloads\\og-image-3380954756.png");
	this->Point.x = 0;
	this->Point.y = 0;
	if (image.empty()) {
		cout << "Image File "
			<< "Not Found" << endl;
		return;
	}
	this->SetupImage();
}

void Image::SetupImage() {
	resize(this->image, this->image, Size(300, 300), INTER_LINEAR);
	cv::imshow("Image", image);
}

void Image::Next() {
	if (image.empty()) {
		cout << "Image File "
			<< "Not Found" << endl;
		return;
	}
	if (Point.x + this->image.cols >= (screenWidth - 5))
	{
		stepX *= -1;
	}
	if (Point.y + this->image.rows >= (screenHeight - 5))
	{
		stepY *= -1;
	}
	if (Point.x <= 0)
	{
		stepX = abs(stepX);
	}
	if (Point.y <= 0)
	{
		stepY = abs(stepY);
	}
	Point.x = Point.x + stepX;
	Point.y = Point.y + stepY;
	moveWindow("Image", this->Point.x, this->Point.y);

}

//HideConsole();
// Error Handling
//if (image.empty()) {
//	cout << "Image File "
//		<< "Not Found" << endl;

//	// wait for any key press
//	cin.get();
//	return -1;
//}
