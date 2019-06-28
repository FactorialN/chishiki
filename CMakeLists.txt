cmake_minimum_required (VERSION 3.1.0)
project(chishiki)

set(CMAKE_CXX_STANDARD 14)

include_directories(
  # chishiki include files
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package (Threads REQUIRED)

add_executable(chishiki

  # Header files

  include/computation/linear/linearhead.h
  include/computation/linear/homo.h
  include/computation/linear/lintype.h

  include/computation/geometry/geometryhead.h
  include/computation/geometry/ray.h
  include/computation/geometry/bbox.h
  include/computation/geometry/color.h
  include/computation/geometry/transform.h
  include/computation/geometry/intersection.h
  include/computation/geometry/triangle.h

  include/computation/sample/samplehead.h
  include/computation/sample/sampler.h
  include/computation/sample/weighted.h
  include/computation/sample/mathdistri.h

  include/computation/computation.h

  include/interface/camera/camerahead.h
  include/interface/camera/camerabase.h
  include/interface/camera/film.h
  include/interface/camera/perspective.h

  include/interface/analyse.h

  include/object/accel/accelhead.h
  include/object/accel/accel.h
  include/object/accel/kdaccel.h

  include/object/environmentmap/envmaphead.h
  include/object/environmentmap/envmapbase.h
  include/object/environmentmap/lightprobe.h

  include/object/material/materialhead.h
  include/object/material/diffuse.h
  include/object/material/bsdf.h
  include/object/material/dielectric.h
  include/object/material/microfacet.h
  include/object/material/mirror.h
  include/object/material/bssrdf.h
  include/object/material/seperable.h

  include/object/medium/mediumhead.h
  include/object/medium/mediumbase.h
  include/object/medium/homomedium.h

  include/object/shape/shapehead.h
  include/object/shape/shape.h
  include/object/shape/sphere.h
  include/object/shape/trianglemesh.h

  include/object/texture/texturehead.h

  include/object/scene.h

  include/rendering/integrator/integratorhead.h
  include/rendering/integrator/integratorbase.h
  include/rendering/integrator/normalint.h
  include/rendering/integrator/aoint.h
  include/rendering/integrator/rtint.h
  include/rendering/integrator/whittedint.h
  include/rendering/integrator/volint.h

  # Source code files

  src/main.cpp

  src/computation/linear/homo.cpp
  src/computation/linear/lintype.cpp

  src/computation/geometry/bbox.cpp
  src/computation/geometry/transform.cpp
  src/computation/geometry/triangle.cpp
  src/computation/geometry/color.cpp

  src/computation/sample/weighted.cpp
  src/computation/sample/mathdistri.cpp

  src/interface/camera/film.cpp
  src/interface/camera/perspective.cpp

  src/interface/analyse.cpp

  src/object/accel/kdaccel.cpp
  
  src/object/environmentmap/lightprobe.cpp

  src/object/material/diffuse.cpp
  src/object/material/dielectric.cpp
  src/object/material/microfacet.cpp
  src/object/material/mirror.cpp
  src/object/material/seperable.cpp

  src/object/medium/homomedium.cpp

  src/object/shape/shape.cpp
  src/object/shape/sphere.cpp
  src/object/shape/trianglemesh.cpp

  src/object/scene.cpp

  src/rendering/integrator/normalint.cpp
  src/rendering/integrator/aoint.cpp
  src/rendering/integrator/rtint.cpp
  src/rendering/integrator/whittedint.cpp
  src/rendering/integrator/volint.cpp
)

target_link_libraries (chishiki ${CMAKE_THREAD_LIBS_INIT})