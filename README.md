# Primitive-3d

This is a repository for learning 3d graphics from an unorthodox method of not using any graphics api like opengl or stuff.


## Draw Grid:

![Draw Grid Function](images/draw_grid_primitive_3d.png)

```cpp
void draw_grid(){
    for(int i = 0 ; i < window_height; i++) {
        for(int j = 0; j < window_width ; j++) {
            if ( j % 10 == 0 || i % 10 == 0) {
                color_buffer[window_width * j + i] = 0x00000000;
            }
        }
    }
}
```

Here we are manually manipulating the color_buffer to change the color of the pixels at that particular position.


## Draw Square / Rectangle

![Black Square in White Background](images/black_square_white_background.png)

```cpp
void drawSquare(int posx, int posy, int width, int height, uint32_t color){
    int beginx = std::max(0, posx);
    int beginy = std::max(0, posy); 

    int endx = std::min(widow_width, beginx + width);
    int endy = std::min(window_height, beginy + height);

    for(int y = beginy ; y < endy ; y++){
        for(int x = beginx; x < endx ; x++){
            color_buffer[(width * y) + x] = color;
        }
    }
}
```

## Draw a bitmap

![Lotus Bitmap from designed by macrovector / Freepik](images/lotus_bitmap.png)

## Points in 3d - like a 3d Square

![Points in 3d](images/points_in_3d.png)



## Acknowledgements:

- Pikuma 3d Computer graphics course : [https://github.com/pr0g/pikuma-3d-graphics](https://github.com/pr0g/pikuma-3d-graphics) - highly recommended
- Hoff._world video on [How to write a display driver from start to finish](https://www.youtube.com/watch?v=5cp2iPGWmUY)
- **Website for image to c conversion:** [https://notisrac.github.io/FileToCArray/](https://notisrac.github.io/FileToCArray/)
- The lotus bitmap was created from an image designed by **macrovector / Freepik**