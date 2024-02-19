# 42_MiniRT
Authors: Thomas Höfting (thofting), Martijn Wallage (mwallage)

## Components

MiniRT, a joint project of the 42 Core Curriculum, is a ray tracer written in C and, in our case, using <a href="https://github.com/codam-coding-college/MLX42">MLX42</a>, an openGL graphics library.

## Parsing

The input to miniRT is a .rt file which describes a scene.

A scene consists of a camera, a spotlight (or several, for the bonus version), and various geometrical objects: planes, spheres and cylinders. Each of these things have a position, a direction, a color, and, for the bonus, some information on how much ambient, diffuse and specular light it emits or reflects.

In addition, we need a viewport, a rectangular plane which by convention is at a distance of 1 from the camera. Its height and width make up the resolution of the picture that we want to produce.

We parse this into a struct, which mainly consists of vectors, colours (stored as ints, though perhaps vectors would have been better), and some additional information.

## Raytracing

The idea of ray tracing is that, for each pixel in the image, you shoot a ray from the camera through the corresponding point in the viewport into the scene.
You then calculate the nearest point (if any) where the ray intersects with an object in the scene. 

<img src="https://upload.wikimedia.org/wikipedia/commons/8/83/Ray_trace_diagram.svg" alt="wikipedia image on raytracing">

That is already enough information to make a basic picture: for each pixel whose ray intersects with an object, its colour will be the colour of the object mixed with the colour of the ambient lighting. The pixels whose rays don't intersect with any object will be black.

We then shoot another ray from the spotlight (or several rays from the several spotlights) to that point on the surface of the object, and calculate how the light affects the colour of the object.

For the bonus version, this second calculation comprises both diffuse and specular lighting. We also implemented anti-aliasing and, because anti-aliasing slowed the whole thing down so much, multi-threading.
