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

CloneGithubDependency 'stb'            'https://github.com/nothings/stb.git'         'c7110588a4d24c4bb5155c184fbb77dd90b3116e'
CloneGithubDependency 'tinyformat'     'https://github.com/c42f/tinyformat.git'      '3a33bbf65442432277eee079e83d3e8fac51730c'
CloneGithubDependency 'glm'            'https://github.com/g-truc/glm.git'           '5dcc56489e1b66dfd5bca751fa9b8dc68059e008'
CloneGithubDependency 'imgui'          'https://github.com/ocornut/imgui.git'        'df52f46b13891acf6298a6a783d7f024ccd9ab21'
CloneGithubDependency 'Catch'          'https://github.com/philsquared/Catch.git'    'a0ada2e935324db5c951571c52c9b07307ea422f'
CloneGithubDependency 'glad'           'https://github.com/iondune/glad.git'         '11f33ab7625ada108f836a83cd8abc405bd870e9'
CloneGithubDependency 'tinyobjloader'  'https://github.com/syoyo/tinyobjloader.git'  '51d13700d880d2d5fdaf5bd3547100bafcae7932'
CloneGithubDependency 'simpleini'      'https://github.com/iondune/simpleini.git'    'b04314f8dd525e8dccc28541d1ca601260064351'
