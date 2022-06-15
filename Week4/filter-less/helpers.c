#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray = rint((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = rint(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = rint(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = rint(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];
    for (int i = 0; i < height; i++)
    {
        int x = width - 1;
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][x] = image[i][j];
            x--;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];
    RGBTRIPLE tmp_pixel;

/*
    for (int i = 0; i < height; i++)
    {
        int x = width - 1;
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][x] = image[i][j];
            x--;
        }
    }
*/
    int z, sum, rgbtBlue, rgbtGreen, rgbtRed;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            z = 1;
            rgbtBlue = image[i][j].rgbtBlue;
            rgbtGreen = image[i][j].rgbtGreen;
            rgbtRed = image[i][j].rgbtRed;
            if (!(i - 1 < 0))
            {
                rgbtBlue += image[i - 1][j].rgbtBlue;
                rgbtGreen += image[i - 1][j].rgbtGreen;
                rgbtRed += image[i - 1][j].rgbtRed;
                z++;
                if (!(j - 1 < 0))
                {
                    rgbtBlue += image[i - 1][j - 1].rgbtBlue;
                    rgbtGreen += image[i - 1][j - 1].rgbtGreen;
                    rgbtRed += image[i - 1][j - 1].rgbtRed;
                    z++;
                }
                if (j + 1 != width)
                {
                    rgbtBlue += image[i - 1][j + 1].rgbtBlue;
                    rgbtGreen += image[i - 1][j + 1].rgbtGreen;
                    rgbtRed += image[i - 1][j + 1].rgbtRed;
                    z++;
                }
            }
            if (!(j - 1 < 0))
            {
                rgbtBlue += image[i][j - 1].rgbtBlue;
                rgbtGreen += image[i][j - 1].rgbtGreen;
                rgbtRed += image[i][j - 1].rgbtRed;
                z++;
            }
            if (j + 1 != width)
            {
                rgbtBlue += image[i][j + 1].rgbtBlue;
                rgbtGreen += image[i][j + 1].rgbtGreen;
                rgbtRed += image[i][j + 1].rgbtRed;
                 z++;
            }
            if (i + 1 != height)
            {
                rgbtBlue += image[i + 1][j].rgbtBlue;
                rgbtGreen += image[i + 1][j].rgbtGreen;
                rgbtRed += image[i + 1][j].rgbtRed;
                z++;
                if (!(j - 1 < 0))
                {
                    rgbtBlue += image[i + 1][j - 1].rgbtBlue;
                    rgbtGreen += image[i + 1][j - 1].rgbtGreen;
                    rgbtRed += image[i + 1][j - 1].rgbtRed;
                    z++;
                }
                if (j + 1 != width)
                {
                    rgbtBlue += image[i + 1][j + 1].rgbtBlue;
                    rgbtGreen += image[i + 1][j + 1].rgbtGreen;
                    rgbtRed += image[i + 1][j + 1].rgbtRed;
                    z++;
                }
            }
            tmp_image[i][j].rgbtBlue = round(rgbtBlue/(float)z);
            tmp_image[i][j].rgbtGreen = round(rgbtGreen/(float)z);
            tmp_image[i][j].rgbtRed = round(rgbtRed/(float)z);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }
    return;
}
