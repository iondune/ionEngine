
@ECHO off

CALL :Clone stb             https://github.com/nothings/stb.git          c9ead07188b342350530e92e14542222c3ad9abe
CALL :Clone tinyformat      https://github.com/c42f/tinyformat.git       3a33bbf65442432277eee079e83d3e8fac51730c
CALL :Clone glm             https://github.com/g-truc/glm.git            8f0d85460557dc5fbf4f44dc23a7708d065d7683
CALL :Clone imgui           https://github.com/ocornut/imgui.git         8291d7dc7c3d17425462e7aaf8593a4465405968
CALL :Clone Catch           https://github.com/philsquared/Catch.git     f666f5f0aef121c357a3705b0187e77920a3e0b5
CALL :Clone glad            https://github.com/iondune/glad.git          410adfead3468c13d40120a5259e687b8ef0616e
CALL :Clone tinyobjloader   https://github.com/syoyo/tinyobjloader.git   ad9911ef1b124c628581c0f75adb3178f9d03c3c
CALL :Clone dirent          https://github.com/tronkko/dirent.git        57535c8c159052a9871f58dc6fb43278d19102b3

EXIT /B 0


:Clone
IF exist %1 RMDIR /S /Q %1
git clone %2
CD %1
git reset --hard %3
CD ..
EXIT /B 0
