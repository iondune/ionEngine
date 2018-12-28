
@ECHO off

CALL :Clone stb             https://github.com/nothings/stb.git          9d9f75eb682dd98b34de08bb5c489c6c561c9fa6
CALL :Clone tinyformat      https://github.com/c42f/tinyformat.git       3a33bbf65442432277eee079e83d3e8fac51730c
CALL :Clone glm             https://github.com/g-truc/glm.git            6fa203eeb7fbcbb6f620501fad40359c8a456049
CALL :Clone imgui           https://github.com/ocornut/imgui.git         00418d13e369bf53cc4b8f817eb10b8ce65f0904
CALL :Clone Catch           https://github.com/philsquared/Catch.git     19ab2117c5bac2f376f8da4a4b25e183137bcec0
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
