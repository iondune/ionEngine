
@ECHO off

CALL :Clone stb             https://github.com/nothings/stb.git          b42009b3b9d4ca35bc703f5310eedc74f584be58
CALL :Clone tinyformat      https://github.com/c42f/tinyformat.git       705e3f4e1de922069bf715746d35bd2364b1f98f
CALL :Clone glm             https://github.com/g-truc/glm.git            bf71a834948186f4097caa076cd2663c69a10e1e
CALL :Clone imgui           https://github.com/ocornut/imgui.git         ffa863a3ba0c2c211a66940ef648156642553e5d
CALL :Clone doctest         https://github.com/onqtam/doctest.git        f0ab4e793fa863d4a5929ff263ddd3bebec8767e
CALL :Clone tinyobjloader   https://github.com/syoyo/tinyobjloader.git   51d13700d880d2d5fdaf5bd3547100bafcae7932
CALL :Clone simpleini       https://github.com/brofield/simpleini.git    7bca74f6535a37846162383e52071f380c99a43a
CALL :Clone dirent          https://github.com/tronkko/dirent.git        833b6928e860578b0237fb0a3c04277b9c0c2447

EXIT /B 0


:Clone
IF exist %1 RMDIR /S /Q %1
git clone %2
CD %1
git reset --hard %3
CD ..
EXIT /B 0
