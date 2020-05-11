# Pangolin
Probably one of the worst game engines.

## Dependencies
This project depends on:
* [glm](https://github.com/g-truc/glm) (v0.9.9.8);
* [glfw](https://github.com/glfw/glfw) (v3.3.2);
* [assimp](https://github.com/assimp/assimp) (v4.1.0): cannot use more recent versions due to [this issue](https://github.com/assimp/assimp/issues/2754);
* [stb_image](https://github.com/nothings/stb): it only uses stb_image.h available [here](https://github.com/nothings/stb/blob/master/stb_image.h);
* [glad](https://glad.dav1d.de/): the exact version depends on the distribution;
* [googletest](https://github.com/google/googletest) (v1.10.0).

### Freetype installation

 Freetype2 is available [here](https://git.savannah.gnu.org/cgit/freetype/freetype2.git/).

```
cd pangolin/extern
git clone https://git.savannah.gnu.org/git/freetype/freetype2.git
cd freetype2
./autogen.sh
./configure
make
```
