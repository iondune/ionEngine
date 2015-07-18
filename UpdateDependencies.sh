#! /bin/bash

cd "${0%/*}"

mkdir -p 'Dependencies'
cd 'Dependencies/'

function CMakeBuild {
	cmake .
	make
	sudo make install
}

function HeaderOnly {
	name="$1"

	echo "$1: Header-only library, no build necessary"
}

function FetchDependency {
	name="$1"
	url="$2"
	buildstep="$3"

	echo "--------------------------------------------------------------------------------"
	if [ -d "$1" ] ; then
		cd "$1"

		echo -n "$1: "
		git remote update

		LOCAL=$(git rev-parse @)
		REMOTE=$(git rev-parse @{u})
		BASE=$(git merge-base @ @{u})

		if [ $LOCAL = $REMOTE ]; then
			echo "$1: Up-to-date"
		elif [ $LOCAL = $BASE ]; then
			echo "$1: Need to pull"
			git pull
			"$buildstep" "$1"
		else
			echo "$1: Diverged or outgoing changes - please resolve"
		fi

		cd ..
	else
		echo "$1: Does not exist - cloning"

		git clone "$2" "$1"
		cd "$1"
		"$buildstep" "$1"
		cd ..
	fi
}

# Install GLEW
if [ ! -d 'glew-1.12.0' ] ; then
	echo 'glew: Does not exist - installing'
	wget http://sourceforge.net/projects/glew/files/glew/1.12.0/glew-1.12.0.tgz
	tar -xzf glew-1.12.0.tgz
	cd glew-1.12.0
	make
	sudo make install
	cd ..
fi

FetchDependency 'stb' 'https://github.com/nothings/stb.git' 'HeaderOnly'
FetchDependency 'tinyformat' 'https://github.com/c42f/tinyformat.git' 'HeaderOnly'
FetchDependency 'glm' 'https://github.com/g-truc/glm.git' 'HeaderOnly'
FetchDependency 'glfw' 'https://github.com/glfw/glfw.git' 'CMakeBuild'
FetchDependency 'assimp' 'https://github.com/assimp/assimp.git' 'CMakeBuild'
FetchDependency 'imgui' 'https://github.com/ocornut/imgui.git' 'HeaderOnly'
