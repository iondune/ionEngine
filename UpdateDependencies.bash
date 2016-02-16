#!/usr/bin/env bash

cd "${0%/*}"
mkdir -p 'Dependencies'
cd './Dependencies'

function CloneGithubDependency {
	repoName="$1"
	repoURL="$2"
	revision="$3"
	buildStep="$4"

	echo "Cloning Dependency '$repoName'"
	echo "================================================================================"

	rm -rf "./$repoName"
	git clone "$repoURL" "$repoName"
	cd "./$repoName"
	git reset --hard "$revision"

	if [ -z "$4" ] ; then
		echo "Peforming build step ''"
	fi
	cd ..

	echo
}

CloneGithubDependency 'stb'        'https://github.com/nothings/stb.git'      '955dfe991b26f6fb1287ec0093f606843487b099'
CloneGithubDependency 'tinyformat' 'https://github.com/c42f/tinyformat.git'   'fd72f9cf17e4b12cbca932049a17badc7af6718b'
CloneGithubDependency 'glm'        'https://github.com/g-truc/glm.git'        '8f0d85460557dc5fbf4f44dc23a7708d065d7683'
CloneGithubDependency 'imgui'      'https://github.com/ocornut/imgui.git'     'b329a36d2707a94806f85e6d3af3b10c242f6440'
CloneGithubDependency 'Catch'      'https://github.com/philsquared/Catch.git' '3bd20bf2cd05cd88e767ec1aeb856bf8032a04c7'
