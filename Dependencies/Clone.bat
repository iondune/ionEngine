
@ECHO off

CALL :Clone stb             https://github.com/nothings/stb.git          c7110588a4d24c4bb5155c184fbb77dd90b3116e
CALL :Clone tinyformat      https://github.com/c42f/tinyformat.git       3a33bbf65442432277eee079e83d3e8fac51730c
CALL :Clone glm             https://github.com/g-truc/glm.git            5dcc56489e1b66dfd5bca751fa9b8dc68059e008
CALL :Clone imgui           https://github.com/ocornut/imgui.git         df52f46b13891acf6298a6a783d7f024ccd9ab21
CALL :Clone Catch           https://github.com/philsquared/Catch.git     a0ada2e935324db5c951571c52c9b07307ea422f
CALL :Clone glad            https://github.com/iondune/glad.git          11f33ab7625ada108f836a83cd8abc405bd870e9
CALL :Clone tinyobjloader   https://github.com/syoyo/tinyobjloader.git   51d13700d880d2d5fdaf5bd3547100bafcae7932
CALL :Clone simpleini       https://github.com/brofield/simpleini        03e27b27901c8e12fef6daeddc18a9a3e217dea4

CALL :Clone dirent          https://github.com/tronkko/dirent.git        8b1db5092479a73d47eafd3de739b27e876e6bf3

EXIT /B 0


:Clone
IF exist %1 RMDIR /S /Q %1
git clone %2
CD %1
git reset --hard %3
CD ..
EXIT /B 0
