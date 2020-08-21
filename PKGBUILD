# Maintainer: Courrier Guillaume <courrier.guillaume.123@gmail.com>
pkgname=pangolin
pkgver=0.1.1
pkgrel=1
epoch=0
pkgdesc="Simple C++ game engine."
arch=('x86_64')
url="https://github.com/CourrierGui/pangolin"
license=('MIT')
groups=()
depends=('freetype2' 'glm' 'glfw-x11' 'assimp')
makedepends=() # glm ?
checkdepends=('gtest')
optdepends=()
provides=()
conflicts=()
replaces=()
backup=()
options=('!buildflags')
install=
changelog=
source=()
noextract=()
md5sums=()
validpgpkeys=()

prepare() {
	git clone $url "$pkgname-$pkgver"
	mkdir -p "$pkgname-$pkgver"/build
}

build() {
	cd "$pkgname-$pkgver"
	cmake -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build
}

check() {
	cd "$pkgname-$pkgver"/build
	ctest -VV
}

package() {
	cd "$pkgname-$pkgver"
	cmake --install build --prefix "$pkgdir/"
}
