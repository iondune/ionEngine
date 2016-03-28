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

CloneGithubDependency 'stb'            'https://github.com/nothings/stb.git'         '955dfe991b26f6fb1287ec0093f606843487b099'
CloneGithubDependency 'tinyformat'     'https://github.com/c42f/tinyformat.git'      'fd72f9cf17e4b12cbca932049a17badc7af6718b'
CloneGithubDependency 'glm'            'https://github.com/g-truc/glm.git'           '8f0d85460557dc5fbf4f44dc23a7708d065d7683'
CloneGithubDependency 'imgui'          'https://github.com/ocornut/imgui.git'        'b329a36d2707a94806f85e6d3af3b10c242f6440'
CloneGithubDependency 'Catch'          'https://github.com/philsquared/Catch.git'    '3bd20bf2cd05cd88e767ec1aeb856bf8032a04c7'
CloneGithubDependency 'glad'           'https://github.com/iondune/glad.git'         '410adfead3468c13d40120a5259e687b8ef0616e'
CloneGithubDependency 'tinyobjloader'  'https://github.com/syoyo/tinyobjloader.git'  'ad9911ef1b124c628581c0f75adb3178f9d03c3c'
