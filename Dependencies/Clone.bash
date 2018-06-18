#!/usr/bin/env bash

cd "${0%/*}"

function CloneGithubDependency {
	repoName="$1"
	repoURL="$2"
	revision="$3"

	echo "Cloning Dependency '$repoName'"
	echo "================================================================================"

	rm -rf "./$repoName"
	git clone "$repoURL" "$repoName"
	cd "./$repoName"
	git reset --hard "$revision"
	cd ..

	echo
}

CloneGithubDependency 'stb'            'https://github.com/nothings/stb.git'         '9d9f75eb682dd98b34de08bb5c489c6c561c9fa6'
CloneGithubDependency 'tinyformat'     'https://github.com/c42f/tinyformat.git'      '3a33bbf65442432277eee079e83d3e8fac51730c'
CloneGithubDependency 'glm'            'https://github.com/g-truc/glm.git'           '6fa203eeb7fbcbb6f620501fad40359c8a456049'
CloneGithubDependency 'imgui'          'https://github.com/ocornut/imgui.git'        '78b28d545f79c5c5ed3e0ebae4099e44bdc6c5a6'
CloneGithubDependency 'Catch'          'https://github.com/philsquared/Catch.git'    '19ab2117c5bac2f376f8da4a4b25e183137bcec0'
CloneGithubDependency 'glad'           'https://github.com/iondune/glad.git'         '11f33ab7625ada108f836a83cd8abc405bd870e9'
CloneGithubDependency 'tinyobjloader'  'https://github.com/syoyo/tinyobjloader.git'  '51d13700d880d2d5fdaf5bd3547100bafcae7932'
CloneGithubDependency 'simpleini'      'https://github.com/brofield/simpleini.git'   '2af65fcc504f8242752755e836709762ef7ce062'
