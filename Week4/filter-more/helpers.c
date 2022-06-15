#include "helpers.h"

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width]; // create new temp array for reflected picture
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
            image[i][j] = tmp_image[i][j]; // copy reflected image from temp array to the original image
        }
    }
    return;
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
            if (!(i - 1 < 0)) // if above line is exist
            {
                rgbtBlue += image[i - 1][j].rgbtBlue;
                rgbtGreen += image[i - 1][j].rgbtGreen;
                rgbtRed += image[i - 1][j].rgbtRed;
                z++;
                if (!(j - 1 < 0)) // if left pixel on line above is exist
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
            if (!(j - 1 < 0)) // if left pixel on current line is exist
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
                if (!(j - 1 < 0)) // if left pixel on line below is exist
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

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];
    int rgbtBlue, rgbtGreen, rgbtRed;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gx_rgbtBlue = 0;
            int Gx_rgbtGreen = 0;
            int Gx_rgbtRed = 0;
            int Gy_rgbtBlue = 0;
            int Gy_rgbtGreen = 0;
            int Gy_rgbtRed = 0;
            if (!(i - 1 < 0)) // if above line is exist
            {
                Gy_rgbtBlue -= image[i - 1][j].rgbtBlue * 2;
                Gy_rgbtGreen -= image[i - 1][j].rgbtGreen * 2;
                Gy_rgbtRed -= image[i - 1][j].rgbtRed * 2;
                if (!(j - 1 < 0)) // if left pixel on line above is exist
                {
                    Gy_rgbtBlue -= image[i - 1][j - 1].rgbtBlue;
                    Gy_rgbtGreen -= image[i - 1][j - 1].rgbtGreen;
                    Gy_rgbtRed -= image[i - 1][j - 1].rgbtRed;
                    Gx_rgbtBlue -= image[i - 1][j - 1].rgbtBlue;
                    Gx_rgbtGreen -= image[i - 1][j - 1].rgbtGreen;
                    Gx_rgbtRed -= image[i - 1][j - 1].rgbtRed;
                }
                if (j + 1 != width) // if right pixel on line above is exist
                {
                    Gy_rgbtBlue -= image[i - 1][j + 1].rgbtBlue;
                    Gy_rgbtGreen -= image[i - 1][j + 1].rgbtGreen;
                    Gy_rgbtRed -= image[i - 1][j + 1].rgbtRed;
                    Gx_rgbtBlue += image[i - 1][j + 1].rgbtBlue;
                    Gx_rgbtGreen += image[i - 1][j + 1].rgbtGreen;
                    Gx_rgbtRed += image[i - 1][j + 1].rgbtRed;
                }
            }
            if (!(j - 1 < 0)) // if left pixel on current line is exist
            {
                Gx_rgbtBlue -= image[i][j - 1].rgbtBlue * 2;
                Gx_rgbtGreen -= image[i][j - 1].rgbtGreen * 2;
                Gx_rgbtRed -= image[i][j - 1].rgbtRed * 2;
            }
            if (j + 1 != width) // if right pixel on current line is exist
            {
                Gx_rgbtBlue += image[i][j + 1].rgbtBlue * 2;
                Gx_rgbtGreen += image[i][j + 1].rgbtGreen * 2;
                Gx_rgbtRed += image[i][j + 1].rgbtRed * 2;
            }
            if (i + 1 != height) // if below line is exist
            {
                Gy_rgbtBlue += image[i + 1][j].rgbtBlue * 2;
                Gy_rgbtGreen += image[i + 1][j].rgbtGreen * 2;
                Gy_rgbtRed += image[i + 1][j].rgbtRed * 2;
                if (!(j - 1 < 0)) // if left pixel on line below is exist
                {
                    Gy_rgbtBlue += image[i + 1][j - 1].rgbtBlue;
                    Gy_rgbtGreen += image[i + 1][j - 1].rgbtGreen;
                    Gy_rgbtRed += image[i + 1][j - 1].rgbtRed;
                    Gx_rgbtBlue -= image[i + 1][j - 1].rgbtBlue;
                    Gx_rgbtGreen -= image[i + 1][j - 1].rgbtGreen;
                    Gx_rgbtRed -= image[i + 1][j - 1].rgbtRed;
                }
                if (j + 1 != width) // if right pixel on line below is exist
                {
                    Gy_rgbtBlue += image[i + 1][j + 1].rgbtBlue;
                    Gy_rgbtGreen += image[i + 1][j + 1].rgbtGreen;
                    Gy_rgbtRed += image[i + 1][j + 1].rgbtRed;
                    Gx_rgbtBlue += image[i + 1][j + 1].rgbtBlue;
                    Gx_rgbtGreen += image[i + 1][j + 1].rgbtGreen;
                    Gx_rgbtRed += image[i + 1][j + 1].rgbtRed;

                }
            }
            rgbtBlue = round(sqrt(pow(Gy_rgbtBlue, 2) + pow(Gx_rgbtBlue, 2)));
            rgbtGreen = round(sqrt(pow(Gy_rgbtGreen, 2) + pow(Gx_rgbtGreen, 2)));
            rgbtRed = round(sqrt(pow(Gy_rgbtRed, 2) + pow(Gx_rgbtRed, 2)));
            if (rgbtBlue > 255)
            {
                rgbtBlue = 255;
            }
            if (rgbtGreen > 255)
            {
                rgbtGreen = 255;
            }
            if (rgbtRed > 255)
            {
                rgbtRed = 255;
            }
            tmp_image[i][j].rgbtBlue = rgbtBlue;
            tmp_image[i][j].rgbtGreen = rgbtGreen;
            tmp_image[i][j].rgbtRed = rgbtRed;
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
