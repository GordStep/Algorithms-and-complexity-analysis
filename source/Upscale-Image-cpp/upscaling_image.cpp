#include <iostream>

#include "CImg.h"

using namespace std;
using namespace cimg_library;

struct Color {
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;

    Color(unsigned char R, unsigned char G, unsigned char B)
    {
        Red = R;
        Green = G;
        Blue = B;
    }
};

CImg<unsigned char> makeImage(int width, int height, int color)
{
    CImg<unsigned char> img(width, height, 1, 3, color);

    return img;
}

void setPixelRGB(
    CImg<unsigned char> &image, 
    unsigned int x, 
    unsigned int y, 
    Color pixel
);
void setPixelRGB(CImg<unsigned char> &image, unsigned int x, unsigned int y, unsigned char col[]);

Color getPixelRGB(
    CImg<unsigned char> &image, 
    unsigned int x, 
    unsigned int y
);

/*
def UpscalingImage2x(image):
    width = image.size[0] #Определяем ширину. 
    height = image.size[1] #Определяем высоту. 
    
    up_image = Image.new(mode="RGB", size=(width * 2, height * 2))
    draw = ImageDraw.Draw(up_image) #Создаем инструмент для рисования. 
    	
    orig_pix = image.load() #Выгружаем значения пикселей.
    
    for i in range(0, width):
        for j in range(0, height):
            pixel = orig_pix[i, j]
            
            for k in range(0, 2):
                for m in range(0, 2):
                    draw.point((2 * i + k, 2 * j + m), pixel)
                    
    return up_image
*/

CImg<unsigned char> upscalingImage2x(CImg<unsigned char> orig_img);

int main()
{

    CImg<unsigned char> orig_img("../data/test_img.bmp");

    CImg<unsigned char> up_image = upscalingImage2x(orig_img);

    orig_img.display();
    up_image.display();

	return 0;
}

void setPixelRGB(CImg<unsigned char> &image, unsigned int x, unsigned int y, Color color)
{
    image(x, y, 0) = color.Red; // Красный канал 
    image(x, y, 1) = color.Green; // Зеленый канал 
    image(x, y, 2) = color.Blue; // Синий канал 
}
void setPixelRGB(CImg<unsigned char> &image, unsigned int x, unsigned int y, unsigned char col[])
{
    image(x, y, 0) = col[0]; // Красный канал 
    image(x, y, 1) = col[1]; // Зеленый канал 
    image(x, y, 2) = col[2]; // Синий канал 
}

Color getPixelRGB(CImg<unsigned char> &image, unsigned int x, unsigned int y)
{
    // Получаем значения красного, зеленого и синего каналов для пикселя с координатами (x, y)

    unsigned char red = image(x, y, 0);
    unsigned char green = image(x, y, 1);
    unsigned char blue = image(x, y, 2);

    return Color(red, green, blue);
}

/*
def UpscalingImage2x(image):
    width = image.size[0] #Определяем ширину. 
    height = image.size[1] #Определяем высоту. 
    
    up_image = Image.new(mode="RGB", size=(width * 2, height * 2))
    draw = ImageDraw.Draw(up_image) #Создаем инструмент для рисования. 
    	
    orig_pix = image.load() #Выгружаем значения пикселей.
    
    for i in range(0, width):
        for j in range(0, height):
            pixel = orig_pix[i, j]
            
            for k in range(0, 2):
                for m in range(0, 2):
                    draw.point((2 * i + k, 2 * j + m), pixel)
                    
    return up_image
*/

CImg<unsigned char> upscalingImage2x(CImg<unsigned char> orig_img)
{
    int width = orig_img.width();
    int height = orig_img.height();

    CImg<unsigned char> up_image = makeImage(width * 2, height * 2, 0);

    for (int i = 0; i < 2 * width; i++)
    {
        for (int j = 0; j < 2 * height; j++)
        {
            Color orig_col = getPixelRGB(orig_img, i, j);
            setPixelRGB(up_image, i, j, orig_col);
            setPixelRGB(up_image, i + 1, j, orig_col);
            setPixelRGB(up_image, i, j + 1, orig_col);
            setPixelRGB(up_image, i + 1, j + 1, orig_col);
        }
    }

    return up_image;
}