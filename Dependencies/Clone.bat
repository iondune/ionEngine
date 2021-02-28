
@ECHO off

CALL :Clone stb             https://github.com/nothings/stb.git          b42009b3b9d4ca35bc703f5310eedc74f584be58
CALL :Clone tinyformat      https://github.com/c42f/tinyformat.git       3a33bbf65442432277eee079e83d3e8fac51730c
CALL :Clone glm             https://github.com/g-truc/glm.git            6fa203eeb7fbcbb6f620501fad40359c8a456049
CALL :Clone imgui           https://github.com/ocornut/imgui.git         4b4be11fd2dabc7a72d749c22a5eeeb3647078bc
CALL :Clone doctest         https://github.com/onqtam/doctest.git        d5aa2bfb8f00b6260296a754af3a3a98d93f7b67
CALL :Clone glad            https://github.com/iondune/glad.git          11f33ab7625ada108f836a83cd8abc405bd870e9
CALL :Clone tinyobjloader   https://github.com/syoyo/tinyobjloader.git   51d13700d880d2d5fdaf5bd3547100bafcae7932
CALL :Clone simpleini       https://github.com/brofield/simpleini        2af65fcc504f8242752755e836709762ef7ce062

CALL :Clone dirent          https://github.com/tronkko/dirent.git        94ff8bdbb4e11eea5fba17b92edfcdc4b4ece769

EXIT /B 0


:Clone
IF exist %1 RMDIR /S /Q %1
git clone %2
CD %1
git reset --hard %3
CD ..
EXIT /B 0
