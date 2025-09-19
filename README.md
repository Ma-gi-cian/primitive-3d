# Primitive-3d

This is a repository for learning 3d graphics from an unorthodox method of not using any graphics api like opengl or stuff.

This repo is based on the course : [pikuma 3d computer graphics programming](https://pikuma.com/courses/learn-3d-computer-graphics-programming).

There are some changes from the course, like using cpp instead of c.

> Would highly recommend the course.


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