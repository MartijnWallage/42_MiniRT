# miniRT
Authors: Thomas Höfting (thofting), Martijn Wallage (mwallage)

## A ray tracer in C and openGL

MiniRT, a joint project of the <a href="https://42berlin.de/curriculum-42-berlin/">42 Core Curriculum</a>, is a ray tracer written in C. 

We got to choose between two openGL graphics libraries, one bad and one good.
After some deliberation, we chose the <a href="https://github.com/codam-coding-college/MLX42">good</a> one.

Compile by writing `make` in the terminal, or `make bonus` for the bonus version. Run `./miniRT scenes/<filename>.rt`

The camera, objects and lights can be moved and rotated using `+` and `-`, the arrow keys, `q`, `w`, `d`, and `a`,`s`,`d`. You'll get the hang of it when you play around with them. `c` selects the camera, `l` the next spotlight, `o` the next object. Objects can also be selected by clicking on them.

## Parsing

The input to miniRT is a .rt file which describes a scene.

A scene consists of a camera, ambient light, spotlights, and various geometrical objects: planes, spheres and cylinders. 

Each of these things, except the camera, have a colour; the lights have a brightness ratio; the camera, spotlights and objects have a position in space; the camera and objects have a direction. For the bonus, there is some additional information on the ratio between diffuse and specular light that each spotlight emits and each object reflects.

Colours we store as ints, because that is how the MLX42 graphic library stores them. Positions and directions we store as 3d vectors of floats. We found that the program runs smoothly with floats; doubles would produce a nicer picture, but at a high cost.

Not given in the input file, but needed for our model, is a <em>viewport</em>. A viewport is a rectangular plane in front of the camera; its height and width make up the resolution of the picture that we want to produce.

## Ray tracing

The viewport is a grid; each cell represents a pixel of the image that we want to produce. By convention, the viewport is at a distance of 1 from the camera. The idea of <a href="https://en.wikipedia.org/wiki/Ray_tracing_%2528graphics%2529">ray tracing</a> is that we shoot a ray from the camera, through the middle of the corresponding cell of the viewport, into the scene.
We then calculate the nearest point (if any) where the ray intersects with an object in the scene. All this is done with basic linear algebra.

<img src="https://upload.wikimedia.org/wikipedia/commons/8/83/Ray_trace_diagram.svg" alt="wikipedia image on raytracing" height="250px">

That is already enough information to make a simple picture: for each ray that intersects with an object, its colour (the colour of the corresponding pixel) will be the colour of the object mixed with the colour of the ambient lighting. The remaining pixels (those whose rays don't intersect with any object) are black.

Now consider the intersection between a camera ray and an object. In order to show the effect of the spotlights, we shoot another ray from each spotlight to that point and calculate how the light affects the colour of the object.

For the bonus version, this second calculation comprises both diffuse and specular lighting, using the <a href="https://en.wikipedia.org/wiki/Phong_reflection_model">Phong model</a>. We also implement anti-aliasing and, because anti-aliasing slowed the whole thing down so much, multi-threading.

## Helpful sources


<a href="https://www.scratchapixel.com/">Scratchapixel</a>

<a href="https://raytracing.github.io/">Ray Tracing in One Weekend</a>

Wikipedia:
<a href="https://en.wikipedia.org/wiki/Ray_tracing_%2528graphics%2529">Ray tracing</a>, <a href="https://en.wikipedia.org/wiki/Line-cylinder_intersection">Line-cylinder intersection</a>, <a href="https://en.wikipedia.org/wiki/Phong_reflection_model">Phong model</a>