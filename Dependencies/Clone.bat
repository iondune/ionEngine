
@ECHO off

CALL :Clone stb             https://github.com/nothings/stb.git          955dfe991b26f6fb1287ec0093f606843487b099
CALL :Clone tinyformat      https://github.com/c42f/tinyformat.git       fd72f9cf17e4b12cbca932049a17badc7af6718b
CALL :Clone glm             https://github.com/g-truc/glm.git            8f0d85460557dc5fbf4f44dc23a7708d065d7683
CALL :Clone imgui           https://github.com/ocornut/imgui.git         b329a36d2707a94806f85e6d3af3b10c242f6440
CALL :Clone Catch           https://github.com/philsquared/Catch.git     3bd20bf2cd05cd88e767ec1aeb856bf8032a04c7
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
