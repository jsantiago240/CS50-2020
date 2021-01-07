/* Javius Santiago
   Filter
   5/16/2020
*/

#include "helpers.h"
#include <math.h>

// If a given rgb value is higher than the maximum possible value it is capped.
int cap(int value)
{
    if (value > 255)
    {
        value = 255;
    }
    return value;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterates over each row
    for (int row = 0; row < height; row++)
    {
        // Iterates over each column
        for (int col = 0; col < width; col++)
        {
            // Gets the average of all the rgb values
            float average = round((image[row][col].rgbtRed + image[row][col].rgbtBlue + image[row][col].rgbtGreen) / 3.00);
            // Set all rgb values to the average of the three
            image[row][col].rgbtRed = average;
            image[row][col].rgbtBlue = average;
            image[row][col].rgbtGreen = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;

    // Iterates over each row
    for (int row = 0; row < height; row++)
    {
        // Iterates over each column
        for (int col = 0; col < width; col++)
        {
            // Creates sepia rgb values using sepia formula given
            sepiaRed = cap(round(0.393 * image[row][col].rgbtRed + .769 * image[row][col].rgbtGreen + .189 * image[row][col].rgbtBlue));
            sepiaGreen = cap(round(0.349 * image[row][col].rgbtRed + .686 * image[row][col].rgbtGreen + .168 * image[row][col].rgbtBlue));
            sepiaBlue = cap(round(0.272 * image[row][col].rgbtRed + .534 * image[row][col].rgbtGreen + .131 * image[row][col].rgbtBlue));

            // Set rgb values after sepia formula
            image[row][col].rgbtRed = sepiaRed;
            image[row][col].rgbtGreen = sepiaGreen;
            image[row][col].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // RGB Values of the current pixel being worked on in the double for loop
    RGBTRIPLE currentPixel;

    for (int row = 0; row < height; row++)
    {
        // Reflections are only done on the first half so the effect is not undone by the end of the loop
        for (int col = 0; col < width / 2; col++)
        {
            // Sets currentPixel to the current pixel being analyzed
            currentPixel = image[row][col];

            // The current pixel is set to the pixel on the same row, at the last column - the current iteration of the second loop
            image[row][col] = image[row][width - 1 - col];

            // The pixel whos value was given to the currentPixel is then assigned the current pixels value
            image[row][width - 1 - col] = currentPixel;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int avgRed;
    int avgGreen;
    int avgBlue;

    float total;

    // Create a temporary copy of the image to reference
    RGBTRIPLE imageCopy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }

    // Iterates over each row
    for (int row = 0; row < height; row++)
    {
        // Iterates over each column
        for (int col = 0; col < width; col++)
        {
            avgRed = 0;
            avgGreen = 0;
            avgBlue = 0;
            total = 0.00;

            // Iterates through each row of surrounding box
            for (int i = -1; i <= 1; i++)
            {
                // Iterates through each column of surrounding box
                for (int j = -1; j <= 1; j++)
                {
                    // If pixels are within bounds, it is added to the average
                    if (row + i != height && row + i > -1 &&
                        col + j != width && col + j > -1)
                    {
                        avgRed += imageCopy[row + i][col + j].rgbtRed;
                        avgGreen += imageCopy[row + i][col + j].rgbtGreen;
                        avgBlue += imageCopy[row + i][col + j].rgbtBlue;
                        // Total is updated to find the average
                        total++;
                    }
                }
            }
            image[row][col].rgbtRed = round(avgRed / total);
            image[row][col].rgbtGreen = round(avgGreen / total);
            image[row][col].rgbtBlue = round(avgBlue / total);
        }
    }
}
