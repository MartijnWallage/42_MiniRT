# 42_MiniRT
Authors: Thomas Höfting (thofting), Martijn Wallage (mwallage)

## Components

MiniRT, a project of the 42 Core Curriculum, is a ray tracer written in C and using <a href="https://github.com/codam-coding-college/MLX42">MLX42</a>, an openGL graphics library.

1.	Parsing
  The input to miniRT is a .rt file which describes a scene.
  A scene consists of a camera, spotlights (several for the bonus version), and various geometrical objects: planes, spheres and cylinders.
  In addition, we need a viewport which by convention is at a distance of 1 from the camera.
  We parse this into a struct, which mainly consists of vectors, colors (stored as ints), and some additional information.

3.	Raytracing

calculate surfaces

calculate rays on the basis of camera

calculate intersections of ray with surface

calculate rays from the spotlight

calculate shadows

calculate color of intersections based on lighting and shadows

calculate translations and rotations

3.	Image processing

For each ray write one pixel to an image.

Display the image to the screen.

Take care of resizing etc.
