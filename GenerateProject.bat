call premake\premake5.exe vs2019
call xcopy /E /Y "$(ProjectDir)External\*.dll" "$(OutDir)"
call mkdir "$(OutDir)assets"
call xcopy /E /Y "$(ProjectDir)assets" "$(OutDir)assets"
PAUSE