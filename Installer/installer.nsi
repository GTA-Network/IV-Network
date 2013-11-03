; DO NOT TRY TO COMPILE THIS FILE (installer_template.nsi).
; ${VERSION} will be replaced by custom script, no macro definition needed

;======================================================
; Includes
!include nsDialogs.nsh
!include "MUI2.nsh"
!include LogicLib.nsh

;======================================================
; Configuration
!define NAME 'IVNetwork'
!define VERSION '1.0.0.DEV'

;======================================================
; Modern Interface Configuration
!define MUI_ICON .\icon.ico
!define MUI_INSTALLCOLORS "DDDDDD 333333"
!define MUI_INSTFILESPAGE_COLORS "DDDDDD 333333"
!define MUI_INSTFILESPAGE_PROGRESSBAR colored

;======================================================
; Installer Information
Name "${NAME} ${VERSION}"
OutFile "${NAME}-${VERSION}.exe"
SetCompressor /SOLID lzma
CRCCheck force
BrandingText /TRIMCENTER "${NAME} ${VERSION} Setup"
ShowInstDetails show
ShowUninstDetails show
RequestExecutionLevel admin

;======================================================
; Initialize Function
Var GTAIVDirectory

Function .onInit
	; Try to get the GTAIV directory from the registry
	ReadRegStr $GTAIVDirectory HKLM "Software\Rockstar Games\EFLC" "InstallFolder"

	; Did we find it?
	IfFileExists $GTAIVDirectory\EFLC.exe done

	; Try to get the GTAIV directory from the registry
	ReadRegStr $GTAIVDirectory HKCU "Software\IVNetwork" "GrandTheftAutoDirectory"

	; Did we find it?
	IfFileExists $GTAIVDirectory\EFLC.exe done

	; Show a dialog to find the GTAIV directory
	nsDialogs::SelectFolderDialog "Please select your Grand Theft Auto EFLC directory" ""
	Pop $GTAIVDirectory

	; Did we find it?
	IfFileExists $GTAIVDirectory\EFLC.exe done

	; GTAIV directory not found
	MessageBox MB_OK "Failed to find Grand Theft Auto EFLC directory. Grand Theft Auto EFLC must be installed in order to install IV:Network."
	Abort

done:
FunctionEnd

;======================================================
; Pages

; Get Install Directory Page
Page directory

DirText "Welcome to the installer for ${NAME} ${VERSION}.$\n$\nYou must have Grand Theft Auto EFLC installed in order to install ${NAME}." "Please select the directory to install IV:Net to."
InstallDir "$PROGRAMFILES\IVNetwork"

; Options Page

Var OptionsWindow
Var OptionsPageText
Var CreateStartMenuShortcutsCheckbox
Var CreateDesktopShortcutCheckbox
Var CreateStartMenuShortcuts
Var CreateDesktopShortcut

Page custom OptionsPage OptionsPageLeave

Function OptionsPage
	nsDialogs::Create 1018
	Pop $OptionsWindow

	${If} $OptionsWindow == error
		Abort
	${EndIf}

	${NSD_CreateLabel} 0 0 100% 20u "Please select the following installation options, then click Install to proceed with the installation."
	Pop $OptionsPageText

	${NSD_CreateCheckbox} 0 40u 100% 10u "&Create Start Menu Shortcut"
	Pop $CreateStartMenuShortcutsCheckbox

	${NSD_Check} $CreateStartMenuShortcutsCheckbox

	${NSD_CreateCheckbox} 0 55u 100% 10u "&Create Desktop Shortcut"
	Pop $CreateDesktopShortcutCheckbox

	nsDialogs::Show
FunctionEnd

Function OptionsPageLeave
	${NSD_GetState} $CreateStartMenuShortcutsCheckbox $CreateStartMenuShortcuts

	${NSD_GetState} $CreateDesktopShortcutCheckbox $CreateDesktopShortcut
FunctionEnd

;======================================================
; Installer

!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "English"

;======================================================
; Sections

Section "Install" SecDummy
	SetOverwrite on

	; Copy New Files
	
	SetOutPath "$INSTDIR"

	File ..\Files\LaunchIVNetwork.exe
	File ..\Files\IVNetwork.dll
	File ..\Files\bass.dll
	File ..\Files\IVNUpdater.exe
	File ..\Files\MahApps.Metro.dll
	File ..\Files\System.Windows.Interactivity.dll

	SetOutPath "$INSTDIR\multiplayer\datafiles"
	
	; CEGUI Stuff
	CreateDirectory "$INSTDIR\CEGUI"
	CreateDirectory "$INSTDIR\CEGUI\fonts"
	CreateDirectory "$INSTDIR\CEGUI\imagesets"
	CreateDirectory "$INSTDIR\CEGUI\layouts"
	CreateDirectory "$INSTDIR\CEGUI\looknfeel"
	CreateDirectory "$INSTDIR\CEGUI\schemes"
	CreateDirectory "$INSTDIR\CEGUI\xml_schemas"
	
	SetOutPath "$INSTDIR\CEGUI\fonts"
	
	File ..\Files\CEGUI\fonts\*

	SetOutPath "$INSTDIR\CEGUI\imagesets"

	File ..\Files\CEGUI\imagesets\Loading.png
	File ..\Files\CEGUI\imagesets\Background.png
	File ..\Files\CEGUI\imagesets\WindowsLook.png
	File ..\Files\CEGUI\imagesets\WindowsLook.imageset

	SetOutPath "$INSTDIR\CEGUI\layouts"

	SetOutPath "$INSTDIR\CEGUI\looknfeel"
	
	File ..\Files\CEGUI\looknfeel\WindowsLook.looknfeel

	SetOutPath "$INSTDIR\CEGUI\schemes"
	
	File ..\Files\CEGUI\schemes\WindowsLook.scheme
	File ..\Files\CEGUI\schemes\WindowsLookWidgets.scheme

	SetOutPath "$INSTDIR\CEGUI\xml_schemas"
	
	File ..\Files\CEGUI\xml_schemas\CEGUIConfig.xsd
	File ..\Files\CEGUI\xml_schemas\Falagard.xsd
	File ..\Files\CEGUI\xml_schemas\Font.xsd
	File ..\Files\CEGUI\xml_schemas\GUILayout.xsd
	File ..\Files\CEGUI\xml_schemas\GUIScheme.xsd
	File ..\Files\CEGUI\xml_schemas\Imageset.xsd
	
	; EpisodeManager Files
	
	CreateDirectory "$INSTDIR\IVN"
	CreateDirectory "$INSTDIR\IVN\common"
	CreateDirectory "$INSTDIR\IVN\common\data"
	CreateDirectory "$INSTDIR\IVN\loadingscreens"
	
	SetOutPath "$INSTDIR\IVN"
	File ..\Files\IVN\audio.xml
	File ..\Files\IVN\content.dat
	File ..\Files\IVN\ControlMap.dat
	File ..\Files\IVN\images.txt
	File ..\Files\IVN\radio.xml
	
	SetOutPath "$INSTDIR\IVN\common\data"
	File ..\Files\IVN\common\data\handling.dat
	File ..\Files\IVN\common\data\vehicles.ide
	
	SetOutPath "$INSTDIR"
	
	; Create Start Menu Folder

	CreateDirectory "$SMPROGRAMS\IVNetwork"
	
	; Create Documents Folder - For Later Usage
	CreateDirectory "$DOCUMENTS\IVNetwork"
	CreateDirectory "$DOCUMENTS\IVNetwork\Screenshots"

	; Create Start Menu Shortcuts If Requested

	${If} $CreateStartMenuShortcuts == ${BST_CHECKED}
		CreateShortCut "$SMPROGRAMS\IVNetwork\${NAME}.lnk" "$INSTDIR\IVNUpdater.exe"

		CreateShortCut "$SMPROGRAMS\IVNetwork\Uninstall ${NAME}.lnk" "$INSTDIR\Uninstall_${NAME}.exe"
	${EndIf}

	; Create Desktop Shortcut If Requested
	
	${If} $CreateDesktopShortcut == ${BST_CHECKED}
		CreateShortCut "$DESKTOP\${NAME}.lnk" "$INSTDIR\IVNUpdater.exe"
	${EndIf}

	; Create Uninstaller

	WriteUninstaller "$INSTDIR\Uninstall_${NAME}.exe"
	
SectionEnd

Section "Uninstall"
	; Delete Files

	Delete "$INSTDIR\LaunchIVNetwork.exe"
	Delete "$INSTDIR\IVNetwork.dll"
	Delete "$INSTDIR\IVNUpdater.exe"
	Delete "$INSTDIR\MahApps.Metro.dll"
	Delete "$INSTDIR\System.Windows.Interactivity.dll"
	
	; Remove CEGUI Folders
	RMDIR "$INSTDIR\CEGUI\fonts"
	RMDIR "$INSTDIR\CEGUI\imagesets"
	RMDIR "$INSTDIR\CEGUI\layouts"
	RMDIR "$INSTDIR\CEGUI\looknfeel"
	RMDIR "$INSTDIR\CEGUI\schemes"
	RMDIR "$INSTDIR\CEGUI\xml_schemas"
	RMDIR "$INSTDIR\CEGUI"

	; Remove EpisodeManager Folders
	
	CreateDirectory "$INSTDIR\IVN\loadingscreens"
	CreateDirectory "$INSTDIR\IVN\common\data"
	CreateDirectory "$INSTDIR\IVN\common"
	CreateDirectory "$INSTDIR\IVN"
	
	; Remove Program Files Folder

	RMDIR "$INSTDIR\"

	; Remove Start Menu Folder

	RMDIR "$SMPROGRAMS\IVNetwork"

	; Delete The Desktop Shortcut

	Delete "$DESKTOP\${NAME}.lnk"
	
	; Delete Installer

	Delete "$INSTDIR\Uninstall_${NAME}.exe"
SectionEnd
