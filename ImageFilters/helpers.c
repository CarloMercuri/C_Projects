#include "helpers.h"
#include <math.h>


typedef struct
{
    int  rgbtBlue;
    int  rgbtGreen;
    int  rgbtRed;
} __attribute__((__packed__))
RGBTRINT;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avarage = 0;
    
    for (int row = 0; row < height; row++)
    {
        for (int px = 0; px < width; px++)
        {
            avarage = round(((float)image[row][px].rgbtBlue + (float)image[row][px].rgbtGreen + (float)image[row][px].rgbtRed) / 3);
            
            if (avarage > 255)
            {
                avarage = 255;
            }
            
            image[row][px].rgbtBlue = avarage;
            image[row][px].rgbtGreen = avarage;
            image[row][px].rgbtRed = avarage;
        }
    }

    return;
}



// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    int r = width - 1;
    int l = 0;
    
    for (int row = 0; row < height; row++)
    {
        r = width - 1;
        l = 0;
        
        while (r > l)
        {
            tmp.rgbtBlue = image[row][r].rgbtBlue;
            tmp.rgbtGreen = image[row][r].rgbtGreen;
            tmp.rgbtRed = image[row][r].rgbtRed;
            
            image[row][r].rgbtBlue = image[row][l].rgbtBlue;
            image[row][r].rgbtGreen = image[row][l].rgbtGreen;
            image[row][r].rgbtRed = image[row][l].rgbtRed;
            
            image[row][l].rgbtBlue = tmp.rgbtBlue;
            image[row][l].rgbtGreen = tmp.rgbtGreen;
            image[row][l].rgbtRed = tmp.rgbtRed;
            
            r--;
            l++;
        }
    }
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int count = 0;
    int aB = 0;
    int aG = 0;
    int aR = 0;
    
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }
    
    // Going through each pixel
    for (int row = 0; row < height; row++)
    {
        for (int px = 0; px < width; px++)
        {
            aB = 0;
            aG = 0;
            aR = 0;
            count = 0;
            
            // Then for each pixel, we run another for loop to check the pixels around it
            for (int y = -1; y <  2; y++)
            {
                for (int x = -1; x < 2; x++)
                {

                    if (px + x >= 0 && px + x < width && row + y >= 0 && row + y < height)
                    {
                        aB += original[row + y][px + x].rgbtBlue;
                        aG += original[row + y][px + x].rgbtGreen;
                        aR += original[row + y][px + x].rgbtRed;
                        count++;
                    }
 
                }
            }
            
            image[row][px].rgbtBlue = round(aB / (count * 1.0));
            image[row][px].rgbtGreen = round(aG / (count * 1.0));
            image[row][px].rgbtRed = round(aR / (count * 1.0));
        }
    }
    
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    
    RGBTRIPLE original[height][width];
    RGBTRINT xPass;
    RGBTRINT yPass;
    
    int b;
    int g;
    int r;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }
    
    // Only formatted it this way to please Style, otherwise they'd be on 3 lines to be more readable
    int gx[3][3] =  {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    // same                     
    int gy[3][3] =  {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};                  
                     
                     
    for (int row = 0; row < height; row++)
    {
        for (int px = 0; px < width; px++)
        {
            xPass.rgbtBlue = 0;
            xPass.rgbtGreen = 0;
            xPass.rgbtRed = 0;
            
            yPass.rgbtBlue = 0;
            yPass.rgbtGreen = 0;
            yPass.rgbtRed = 0;
            
            b = 0;
            g = 0;
            r = 0;

            // Then for each pixel, we run another for loop to check the pixels around it
            for (int y = -1; y <  2; y++)
            {
                for (int x = -1; x < 2; x++)
                {

                    if (px + x >= 0 && px + x < width && row + y >= 0 && row + y < height)
                    {
                        xPass.rgbtBlue += original[row + y][px + x].rgbtBlue * gx[y + 1][x + 1];
                        xPass.rgbtGreen += original[row + y][px + x].rgbtGreen * gx[y + 1][x + 1];
                        xPass.rgbtRed += original[row + y][px + x].rgbtRed * gx[y + 1][x + 1];
                        
                        yPass.rgbtBlue += original[row + y][px + x].rgbtBlue * gy[y + 1][x + 1];
                        yPass.rgbtGreen += original[row + y][px + x].rgbtGreen * gy[y + 1][x + 1];
                        yPass.rgbtRed += original[row + y][px + x].rgbtRed * gy[y + 1][x + 1];
                    }

                }
            }
            
            b = round(sqrt(pow(xPass.rgbtBlue, 2) + pow(yPass.rgbtBlue, 2)));
            

            if (b > 255)
            {
                b = 255;
            }
            
            image[row][px].rgbtBlue = b;

            g = round(sqrt(pow(xPass.rgbtGreen, 2) + pow(yPass.rgbtGreen, 2)));
            
            if (g > 255)
            {
                g = 255;
            }
            
            image[row][px].rgbtGreen = g;
            
            r = round(sqrt(pow(xPass.rgbtRed, 2) + pow(yPass.rgbtRed, 2)));
            
            if (r > 255)
            {
                r = 255;
            }
            
            image[row][px].rgbtRed = r;
        }
    }
    
    return;
}
