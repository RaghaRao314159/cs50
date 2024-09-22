#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE average = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed)/3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE a = image[i][j];
            RGBTRIPLE b = image[i][width - j - 1];
            image[i][j] = b;
            image[i][width - j - 1] = a;
        }
    }
    return;
}

void blur_average(int i, int j, int up, int down, int left, int right, int height, int width, RGBTRIPLE image[height][width],
                  RGBTRIPLE image2[height][width])
{
    float sum_red = 0;
    float sum_green = 0;
    float sum_blue = 0;

    for (int vert = i + up; vert <= i + down; vert++)
    {
        for (int horz = j + left; horz <= j + right; horz++)
        {
            sum_red += (float) image[vert][horz].rgbtRed;
            sum_green += (float) image[vert][horz].rgbtGreen;
            sum_blue += (float) image[vert][horz].rgbtBlue;
        }
    }
    float pixels = (right - left + 1) * (down - up + 1);
    int8_t red_av = round(sum_red / pixels);
    int8_t green_av = round(sum_green / pixels);
    int8_t blue_av = round(sum_blue / pixels);

    image2[i][j].rgbtRed = red_av;
    image2[i][j].rgbtGreen = green_av;
    image2[i][j].rgbtBlue = blue_av;
    return;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE red_average, green_average, blue_average;

            if (i == 0 && j == 0)
            {
                blur_average(i, j, 0, 1, 0, 1, height, width, image, image2);
            }
            else if (i == height-1 && j == width-1)
            {
                blur_average(i, j, -1, 0, -1, 0, height, width, image, image2);
            }
            else if (i == 0 && j == width-1)
            {
                blur_average(i, j, 0, 1, -1, 0, height, width, image, image2);
            }
            else if (i == height-1 && j == 0)
            {
                blur_average(i, j, -1, 0, 0, 1, height, width, image, image2);
            }
            else if (i == 0)
            {
                blur_average(i, j, 0, 1, -1, 1, height, width, image, image2);
            }
            else if (i == height-1)
            {
                blur_average(i, j, -1, 0, -1, 1, height, width, image, image2);
            }
            else if (j == 0)
            {
                blur_average(i, j, -1, 1, 0, 1, height, width, image, image2);
            }
            else if (j == width-1)
            {
                blur_average(i, j, -1, 1, -1, 0, height, width, image, image2);
            }
            else
            {
                blur_average(i, j, -1, 1, -1, 1, height, width, image, image2);
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image2[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image2[i][j].rgbtGreen;
            image[i][j].rgbtRed = image2[i][j].rgbtRed;
        }
    }

    return;
}

void sobel(int i, int j, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE image2[height][width])
{
    //2nd dim must be specified in 2d array initialisation
    float GX[][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    float gx_red = 0, gx_green = 0, gx_blue = 0;

    float GY[][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    float gy_red = 0, gy_green = 0, gy_blue = 0;

    for (int vert = -1; vert <= 1; vert++)
    {
        for (int horz = -1; horz <= 1; horz++)
        {
            if ((i + vert >= 0) && (i + vert < height) && (j + horz >= 0) && (j + horz < width))
            {
                gx_red += (GX[vert + 1][horz + 1]) * (float)(image[i + vert][j + horz].rgbtRed);
                gx_green += (GX[vert + 1][horz + 1]) * (float)(image[i + vert][j + horz].rgbtGreen);
                gx_blue += (GX[vert + 1][horz + 1]) * (float)(image[i + vert][j + horz].rgbtBlue);

                gy_red += (GY[vert + 1][horz + 1]) * (image[i + vert][j + horz].rgbtRed);
                gy_green += (GY[vert + 1][horz + 1]) * (image[i + vert][j + horz].rgbtGreen);
                gy_blue += (GY[vert + 1][horz + 1]) * (image[i + vert][j + horz].rgbtBlue);

            }
        }
    }
    image2[i][j].rgbtRed = (BYTE) round(fmin(pow(pow(gx_red, 2) + pow(gy_red, 2), 0.5), 255));
    image2[i][j].rgbtGreen = (BYTE) round(fmin(pow(pow(gx_green, 2) + pow(gy_green, 2), 0.5), 255));
    image2[i][j].rgbtBlue = (BYTE) round(fmin(pow(pow(gx_blue, 2) + pow(gy_blue, 2), 0.5), 255));

    return;
}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sobel(i, j, height, width, image, image2);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image2[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image2[i][j].rgbtGreen;
            image[i][j].rgbtRed = image2[i][j].rgbtRed;
        }
    }
    return;
}
