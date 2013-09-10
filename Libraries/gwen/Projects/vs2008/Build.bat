call "%VS90COMNTOOLS%\vsvars32.bat"

devenv Gwen.sln /Build "Debug|Win32" > Debug.txt
devenv Gwen.sln /Build "Release|Win32" > Release.txt