/*      < 2026-2027 >
FCAI-CU > 2nd Level > OOP > Assignment 1 > Image Filters
Section : (15,16)
Team members :
20250666 Malak Mohamed  Filters: 1]Gray scale     5]Flip          9]Merge     13]Fix natural sunlight
20250693 Merna Hany     Filters: 2]Black & White  6]Rotate       10]Detect    14]Old TV Effect
20250721 Hoda Ahmad     Filters: 3]Inverting      7]Brightness   11]Crop      15]purple effect
20251051 Alaa Sayed     Filters: 4]Frame          8] Resize      12]Blur      16]Infrared photography
*/

#include "Image_Class.h"
#include <filesystem>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;

// 1] gray scale
void grayscale(Image& image) {
  for (int y = 0; y < image.height; ++y) {
    for (int x = 0; x < image.width; ++x) {
      unsigned char r = image.getPixel(x, y, 0);
      unsigned char g = image.getPixel(x, y, 1);
      unsigned char b = image.getPixel(x, y, 2);
      unsigned char gray = static_cast<unsigned char>(0.21 * r + 0.72 * g + 0.07 * b);
      image.setPixel(x, y, 0, gray);
      image.setPixel(x, y, 1, gray);
      image.setPixel(x, y, 2, gray);
    }
  }
}

// 2] Black & White
void Black_White(Image& image) {
  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      unsigned char r = image.getPixel(i, j, 0);
      unsigned char g = image.getPixel(i, j, 1);
      unsigned char b = image.getPixel(i, j, 2);
      int avg = (r + g + b) / 3;
      unsigned char newValue = (avg >= 128 ? 255 : 0);
      image.setPixel(i, j, 0, newValue);
      image.setPixel(i, j, 1, newValue);
      image.setPixel(i, j, 2, newValue);
    }
  }
}

// 3] Inverting
void invert(Image& image) {
  for (int r = 0; r < image.width; r++) {
    for (int c = 0; c < image.height; c++) {
      image(r, c, 0) = 255 - image(r, c, 0);
      image(r, c, 1) = 255 - image(r, c, 1);
      image(r, c, 2) = 255 - image(r, c, 2);
    }
  }
}

// 4] Frame
void frame(Image& image) {
  int m, s;
  cout << " 1]Thin  2]Thick \n ";
  cin >> m;
  s = (m == 1 ? 20 : 50);
  Image fr(image.width + 2 * s, image.height + 2 * s);
  for (int r = 0; r < fr.width; r++) {
    for (int c = 0; c < fr.height; c++) {
      for (int N = 0; N < 3; N++) {
        fr(r, c, N) = 0;
      }
    }
  }
  for (int x = 0; x < image.width; x++) {
    for (int y = 0; y < image.height; y++) {
      for (int N = 0; N < 3; N++) {
        fr(x + s, y + s, N) = image(x, y, N);
      }
    }
  }
  image = fr;
}

// 5.1] Horizontal Flip
void horizontal_flip(Image& image) {
  for (int y = 0; y < image.height; ++y) {
    for (int x = 0; x < image.width / 2; ++x) {
      unsigned char r1 = image.getPixel(x, y, 0);
      unsigned char g1 = image.getPixel(x, y, 1);
      unsigned char b1 = image.getPixel(x, y, 2);
      unsigned char r2 = image.getPixel(image.width - x - 1, y, 0);
      unsigned char g2 = image.getPixel(image.width - x - 1, y, 1);
      unsigned char b2 = image.getPixel(image.width - x - 1, y, 2);
      image.setPixel(x, y, 0, r2);
      image.setPixel(x, y, 1, g2);
      image.setPixel(x, y, 2, b2);
      image.setPixel(image.width - x - 1, y, 0, r1);
      image.setPixel(image.width - x - 1, y, 1, g1);
      image.setPixel(image.width - x - 1, y, 2, b1);
    }
  }
}

// 5.2] Vertical Flip
void vertical_flip(Image& image) {
  for (int y = 0; y < image.height / 2; ++y) {
    for (int x = 0; x < image.width; ++x) {
      unsigned char r1 = image.getPixel(x, y, 0);
      unsigned char g1 = image.getPixel(x, y, 1);
      unsigned char b1 = image.getPixel(x, y, 2);
      unsigned char r2 = image.getPixel(x, image.height - y - 1, 0);
      unsigned char g2 = image.getPixel(x, image.height - y - 1, 1);
      unsigned char b2 = image.getPixel(x, image.height - y - 1, 2);
      image.setPixel(x, y, 0, r2);
      image.setPixel(x, y, 1, g2);
      image.setPixel(x, y, 2, b2);
      image.setPixel(x, image.height - y - 1, 0, r1);
      image.setPixel(x, image.height - y - 1, 1, g1);
      image.setPixel(x, image.height - y - 1, 2, b1);
    }
  }
}

// 6] Rotation
void Rotate(Image& image) {
  int angle;
  cout << " Enter rotation angle [90-180-270]: ";
  cin >> angle;
  if (angle == 90) {
    Image rotated(image.height, image.width);
    for (int x = 0; x < image.width; ++x) {
      for (int y = 0; y < image.height; ++y) {
        for (int c = 0; c < 3; ++c) {
          rotated(y, image.width - 1 - x, c) = image(x, y, c);
        }
      }
    }
    image = rotated;
  } else if (angle == 180) {
    Image rotated(image.width, image.height);
    for (int x = 0; x < image.width; ++x) {
      for (int y = 0; y < image.height; ++y) {
        for (int c = 0; c < 3; ++c) {
          rotated(image.width - 1 - x, image.height - 1 - y, c) = image(x, y, c);
        }
      }
    }
    image = rotated;
  } else if (angle == 270) {
    Image rotated(image.height, image.width);
    for (int x = 0; x < image.width; ++x) {
      for (int y = 0; y < image.height; ++y) {
        for (int c = 0; c < 3; ++c) {
          rotated(image.height - 1 - y, x, c) = image(x, y, c);
        }
      }
    }
    image = rotated;
  } else {
    cout << "=>Invalid angle! \n ";
  }
}

// 7] Brightness
void brightness(Image& image) {
  int M;
  float v;
  cout << " 1] Increase Brightness   2]: Decrease Brightness\n ";
  cin >> M;
  cout << " Enter the percentage [0~300%]: ";
  cin >> v;
  v = v / 100 + 1;
  if (M == 2) v = 1 / v;
  for (int r = 0; r < image.width; r++) {
    for (int c = 0; c < image.height; c++) {
      for (int N = 0; N < 3; N++) {
        if (image(r, c, N) * v > 255) image(r, c, N) = 255;
        else image(r, c, N) *= v;
      }
    }
  }
}
 
// 8] Resize
void Resize(Image& image, int w, int h) {
  Image resized(w, h);
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      int X = x * image.width / w;
      int Y = y * image.height / h;
      for (int c = 0; c < 3; c++) {
        resized(x, y, c) = image(X, Y, c);
      }
    }
  }
  image = resized;
}
   
// 9] Merge
void merge(Image& image) {
    string photo2;
    cout << " Enter the second image name [with extension]: ";
    cin >> photo2;

    Image image2(photo2);

    int mergeWidth;
    int mergeHeight;

    if (image.width != image2.width ||
        image.height != image2.height) {

        int option;

        cout << "\nImages have different dimensions.\n";
        cout << "1. Resize both images and merge\n";
        cout << "2. Merge only the overlapping area\n";
        cout << "Choose an option: ";
        cin >> option;

        if (option == 1) {
            mergeWidth = max(image.width, image2.width);
            mergeHeight = max(image.height, image2.height);

            Image resized1(mergeWidth, mergeHeight);

            for (int x = 0; x < mergeWidth; x++) {
                for (int y = 0; y < mergeHeight; y++) {
                    int X = x * image.width / mergeWidth;
                    int Y = y * image.height / mergeHeight;

                    for (int c = 0; c < 3; c++) {
                        resized1(x, y, c) = image(X, Y, c);
                    }
                }
            }

            image = resized1;

            Image resized2(mergeWidth, mergeHeight);

            for (int x = 0; x < mergeWidth; x++) {
                for (int y = 0; y < mergeHeight; y++) {
                    int X = x * image2.width / mergeWidth;
                    int Y = y * image2.height / mergeHeight;

                    for (int c = 0; c < 3; c++) {
                        resized2(x, y, c) = image2(X, Y, c);
                    }
                }
            }

            image2 = resized2;
        }
        else if (option == 2) {
            mergeWidth = min(image.width, image2.width);
            mergeHeight = min(image.height, image2.height);
        }
        else {
            cout << "Invalid option!\n";
            return;
        }
    }
    else {
        mergeWidth = image.width;
        mergeHeight = image.height;
    }

    if (mergeWidth <= 0 || mergeHeight <= 0) {
        cout << "Invalid image dimensions.\n";
        return;
    }

    float alpha;

    cout << " Enter the alpha value [0.0 - 1.0]: ";
    cin >> alpha;

    if (alpha < 0.0f || alpha > 1.0f) {
        cout << "Error: Alpha value must be between 0.0 and 1.0.\n";
        return;
    }

    for (int x = 0; x < mergeWidth; x++) {
        for (int y = 0; y < mergeHeight; y++) {
            for (int c = 0; c < 3; c++) {
                image(x, y, c) =
                    (alpha * image(x, y, c)) +
                    ((1.0f - alpha) * image2(x, y, c));
            }
        }
    }

    cout << "Images merged successfully!\n";
} 


// 10] Detect Image Edges  
void detectEdges(Image& image) {
    Image result(image.width, image.height);

    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // Convert the image to grayscale
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);

            int gray = static_cast<int>(
                0.299 * r + 0.587 * g + 0.114 * b
            );

            image.setPixel(x, y, 0, gray);
            image.setPixel(x, y, 1, gray);
            image.setPixel(x, y, 2, gray);
        }
    }

    int threshold = 100;

    // Detect edges using horizontal and vertical gradients
    for (int y = 1; y < image.height - 1; y++) {
        for (int x = 1; x < image.width - 1; x++) {
            int sumX = 0;
            int sumY = 0;

            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    int val = image.getPixel(x + i, y + j, 0);

                    sumX += val * Gx[j + 1][i + 1];
                    sumY += val * Gy[j + 1][i + 1];
                }
            }

            int magnitude = static_cast<int>(
                sqrt(sumX * sumX + sumY * sumY)
            );

            int color = (magnitude > threshold) ? 0 : 255;

            result.setPixel(x, y, 0, color);
            result.setPixel(x, y, 1, color);
            result.setPixel(x, y, 2, color);
        }
    }

    // Set the top and bottom borders to white
    for (int x = 0; x < image.width; x++) {
        for (int c = 0; c < 3; c++) {
            result.setPixel(x, 0, c, 255);
            result.setPixel(x, image.height - 1, c, 255);
        }
    }

    // Set the left and right borders to white
    for (int y = 0; y < image.height; y++) {
        for (int c = 0; c < 3; c++) {
            result.setPixel(0, y, c, 255);
            result.setPixel(image.width - 1, y, c, 255);
        }
    }

    image = result;
}  

// 11] Crop
void crop(Image& image) {
  int x, y, w, h;
  cout << "=Detect starting point (x,y) [will be upper left corner]";
  cout << "\n (x) coordinate: ";
  cin >> x;
  cout << " (y) coordinate: ";
  cin >> y;
  cout << "=New dimensions: ";
  cout << "\n Width: ";
  cin >> w;
  cout << " Hight: ";
  cin >> h;
  Image cropped(w, h);
  for (int r = 0; r < w; r++) {
    for (int c = 0; c < h; c++) {
      for (int N = 0; N < 3; N++) {
        cropped(r, c, N) = image(r + x, c + y, N);
      }
    }
  }
  image = cropped;
}
// 13] Sunlight
void sunlight(Image& image) {
    for (int r = 0; r < image.width; r++) {
        for (int c = 0; c < image.height; c++) {
            image(r, c, 0) = min(255, static_cast<int>(image(r, c, 0) * 1.2));
            image(r, c, 1) = min(255, static_cast<int>(image(r, c, 1) * 1.2));
            image(r, c, 2) /= 1.2; 
        }
    }
}

// 14] TV Scanlines

void applyScanlineTVFilter(Image &image)
{
    Image result = image;

    for (int r = 1; r < image.height - 1; r++)
    {
        for (int c = 1; c < image.width - 1; c++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int sum = 0;

                for (int y = -1; y <= 1; y++)
                {
                    for (int x = -1; x <= 1; x++)
                    {
                        sum += image(c + x, r + y, channel);
                    }
                }

                result(c, r, channel) = sum / 9;
            }
        }
    }

    for (int r = 0; r < image.height; r++)
    {
        for (int c = 0; c < image.width; c++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int value = result(c, r, channel) * 1.3;

                if (value > 255)
                    value = 255;

                image(c, r, channel) = value;
            }
        }
    }

    for (int r = 0; r < image.height; r += 2)
    {
        for (int c = 0; c < image.width; c++)
        {
            image(c, r, 0) *= 0.15;
            image(c, r, 1) *= 0.15;
            image(c, r, 2) *= 0.15;
        }
    }
}

// 15] Purple
void purple(Image& image) {
    for (int r = 0; r < image.width; r++) {
        for (int c = 0; c < image.height; c++) {
            image(r, c, 1) /= 3;
            image(r, c, 2) = min(
                255, static_cast<int>(image(r, c, 2) * 1.3)
            );
        }
    }
}
 
// 17] Skew 
void skew(Image& image) {
    const double angle = 40.0;
    const double radians = angle * 3.14159265358979323846 / 180.0;
    const double skewFactor = tan(radians);

    int originalWidth = image.width;
    int originalHeight = image.height;

    int newWidth = originalWidth +
        static_cast<int>(ceil((originalHeight - 1) * skewFactor));

    Image result(newWidth, originalHeight);

    
    for (int y = 0; y < originalHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            for (int c = 0; c < 3; c++) {
                result.setPixel(x, y, c, 255);
            }
        }
    }

    
    for (int y = 0; y < originalHeight; y++) {
        for (int x = 0; x < originalWidth; x++) {
            int newX = static_cast<int>(
                round(x + y * skewFactor)
            );

            if (newX >= 0 && newX < newWidth) {
                for (int c = 0; c < 3; c++) {
                    result.setPixel(
                        newX, y, c,
                        image.getPixel(x, y, c)
                    );
                }
            }
        }
    }

    image = result;
} 

// 18] Oil Paint

void oilPaint(Image& image) {
    Image original = image;

    const int radius = 3;
    const int levels = 16;

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {

            int count[levels] = {};
            int redSum[levels] = {};
            int greenSum[levels] = {};
            int blueSum[levels] = {};

            // Examine the neighboring pixels
            for (int ny = max(0, y - radius);
                 ny <= min(image.height - 1, y + radius); ny++) {

                for (int nx = max(0, x - radius);
                     nx <= min(image.width - 1, x + radius); nx++) {

                    int red = original(nx, ny, 0);
                    int green = original(nx, ny, 1);
                    int blue = original(nx, ny, 2);

                    // Group the pixel by its average brightness
                    int brightness = (red + green + blue) / 3;
                    int bucket = brightness / 16;

                    count[bucket]++;
                    redSum[bucket] += red;
                    greenSum[bucket] += green;
                    blueSum[bucket] += blue;
                }
            }

            // Find the most common brightness group
            int bestBucket = 0;

            for (int i = 1; i < levels; i++) {
                if (count[i] > count[bestBucket]) {
                    bestBucket = i;
                }
            }

            // Replace the pixel with that group's average color
            if (count[bestBucket] > 0) {
                image(x, y, 0) =
                    redSum[bestBucket] / count[bestBucket];

                image(x, y, 1) =
                    greenSum[bestBucket] / count[bestBucket];

                image(x, y, 2) =
                    blueSum[bestBucket] / count[bestBucket];
            }
        }
    }
}


 

int main() {
    string photo;
    int choice;
    string answer;

    cout << "             >> Welcome to <PixelLab> Photo Editor! <<\n\n";
    cout << " Enter Image's Name [with extension]: ";
    getline(cin, photo);

    Image image(photo);
    Image tempimage; 
  string tempphoto = "tempphoto.jpg"; 

  cout << "\n                          ~< Filters List >~            \n\n";
  cout << "                    1] Gray scale       2] Black & White  \n";
  cout << "                    3] Invert colors    4] Frame          \n";
  cout << "                    5] Flip             6] Rotate         \n";
  cout << "                    7] Brightness       8] Resize         \n";
  cout << "                    9] Merge           10] detect Edges   \n";
  cout << "                   11] Crop            12] Blur           \n";
  cout << "                   13] sunlight        14] TV effect      \n";
  cout << "                   15] Purple          16] Infrared       \n";
  cout << "                   17] Skew            18] Oil paint      \n\n";
  do {
        cout << " chose Filter's number: ";
        cin >> choice;
        switch (choice) {
            case 1:
                grayscale(image);
                break;
            case 2:
                Black_White(image);
                break;
            case 3:
                invert(image);
                break;
            case 4:
                frame(image);
                break;
            case 5: 
                int M;
                cout << " 1] Horizontal flip   2] Vertical flip\n ";
                cin >> M;
                if (M == 1)
                  horizontal_flip(image);
                else if (M == 2)
                  vertical_flip(image);
                else
                  cout << "Invalid flip choice!\n";
                break;
            case 6:
                Rotate(image);
                break;
            case 7:
                brightness(image);
                break;
            case 8:
                int w, h;
                cout << " Original dimensions: [" << image.width << "x" << image.height << "]" << endl;
                cout << " New width : ";
                cin >> w;
                cout << " New height : ";
                cin >> h;
                Resize(image, w, h);
                break;
            case 9:
                merge(image); 
                break;
            case 10:
                detectEdges(image);
                break;
            case 11:
                crop(image);
                break;
            case 12:
                break;
            case 13:
                sunlight(image);
                break;
            case 14:
                ScanlineTV(image);
                break;
            case 15:
                purple(image);
                break;
            case 16:
            case 17:
                skew(image);
                break;

            case 18:
                oilPaint(image);
                break;

            default:
                cout << "=> Invalid choice!\n";
                break;
        }

        choice = 0;

        tempimage = image;
        tempimage.saveImage(tempphoto);
        system(tempphoto.c_str());

        cout << " Do you want to apply another filter?\n ";
        cin >> answer;
        remove("tempphoto.jpg");

    } while (answer[0] == 'y' || answer[0] == 'Y');

    remove("tempphoto.jpg");

    cout << " Do you want to save as a copy?\n ";
    cin >> answer;

    if (answer[0] == 'y' || answer[0] == 'Y') {
        string newphoto;
        cout << "\n Enter New Image Name [with wanted extension]: ";
        cin.ignore();
        getline(cin, newphoto);
        image.saveImage(newphoto);
    } else {
        image.saveImage(photo);
    }

    cout << "\n >> Image saved successfully! " << endl;
    cout << "\n                << Thank you for using our program! >>\n" << endl;

    return 0;
}  