# Important

chishiki rebuild started. Instead of building a scalable high-efficiency renderer, the improvement of the debuggability are now regarded as the core goal of this project.

# chishiki
chishiki is a rendering engine combining traditional rendering methods (monte carlo ray tracing and so on) and some new methods such as deep shading. All rendering methods will be given with a mathemetical analysis, and it will help a lot in understanding the methods.
Scalability is the most important feature of chishiki. The author build this rendering engine for convenience in computer graphics research.

## Code Design Structure

The Design of Code Structure is mainly for scalability. Visit https://factorialncom.wordpress.com/2018/11/30/chishiki-code-design-structure/ for detail.

## Supporting

###  

### Shape

Sphere
Triangle Mesh

### Materials

#### BSDF
Diffuse
Mirror
Mircofacet
Dielectric

#### BSSRDF
Seperable BSSRDF

#### Medium
Homogeneous Medium

### Environment Map

Light probe

### Camera

Perspective
