#include "helpers.h"
#include <math.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //make average gray colour from all colors of pixel
            int gray = rint((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the sepia for the each colour
            int sepiaRed = rint(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = rint(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = rint(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            // if sepia more than 255 for each colour the colour should be the 255
            sepiaRed = MIN(sepiaRed, 255);
            sepiaGreen = MIN(sepiaGreen, 255);
            sepiaBlue = MIN(sepiaBlue, 255);
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width]; // create new temp array for reflected picture
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][width - j - 1] = image[i][j];
        }
    }
    copy(height, width, image, tmp_image);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];
    int z, sum, rgbtBlue, rgbtGreen, rgbtRed;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            z = 1;
            rgbtBlue = image[i][j].rgbtBlue;
            rgbtGreen = image[i][j].rgbtGreen;
            rgbtRed = image[i][j].rgbtRed;
            if (i >= 1) // if above line is exist
            {
                rgbtBlue += image[i - 1][j].rgbtBlue;
                rgbtGreen += image[i - 1][j].rgbtGreen;
                rgbtRed += image[i - 1][j].rgbtRed;
                z++;
                if (j >= 1) // if left pixel on line above is exist
                {
                    rgbtBlue += image[i - 1][j - 1].rgbtBlue;
                    rgbtGreen += image[i - 1][j - 1].rgbtGreen;
                    rgbtRed += image[i - 1][j - 1].rgbtRed;
                    z++;
                }
                if (j + 1 != width) // if right pixel on line above is exist
                {
                    rgbtBlue += image[i - 1][j + 1].rgbtBlue;
                    rgbtGreen += image[i - 1][j + 1].rgbtGreen;
                    rgbtRed += image[i - 1][j + 1].rgbtRed;
                    z++;
                }
            }
            if (j >= 1) // if left pixel on current line is exist
            {
                rgbtBlue += image[i][j - 1].rgbtBlue;
                rgbtGreen += image[i][j - 1].rgbtGreen;
                rgbtRed += image[i][j - 1].rgbtRed;
                z++;
            }
            if (j + 1 != width) // if right pixel on current line is exist
            {
                rgbtBlue += image[i][j + 1].rgbtBlue;
                rgbtGreen += image[i][j + 1].rgbtGreen;
                rgbtRed += image[i][j + 1].rgbtRed;
                z++;
            }
            if (i + 1 != height) // if below line is exist
            {
                rgbtBlue += image[i + 1][j].rgbtBlue;
                rgbtGreen += image[i + 1][j].rgbtGreen;
                rgbtRed += image[i + 1][j].rgbtRed;
                z++;
                if (j >= 1) // if left pixel on line below is exist
                {
                    rgbtBlue += image[i + 1][j - 1].rgbtBlue;
                    rgbtGreen += image[i + 1][j - 1].rgbtGreen;
                    rgbtRed += image[i + 1][j - 1].rgbtRed;
                    z++;
                }
                if (j + 1 != width) // if right pixel on line below is exist
                {
                    rgbtBlue += image[i + 1][j + 1].rgbtBlue;
                    rgbtGreen += image[i + 1][j + 1].rgbtGreen;
                    rgbtRed += image[i + 1][j + 1].rgbtRed;
                    z++;
                }
            }
            tmp_image[i][j].rgbtBlue = round(rgbtBlue / (float)z);
            tmp_image[i][j].rgbtGreen = round(rgbtGreen / (float)z);
            tmp_image[i][j].rgbtRed = round(rgbtRed / (float)z);
        }
    }
    copy(height, width, image, tmp_image);
}

void copy(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE tmp_image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }
}
