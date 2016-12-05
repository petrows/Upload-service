;--------------------------------

!include "MUI.nsh"

!define UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\Upload-Client"

; The name of the installer
Name "Upload Client"

; The file to write
OutFile "upload-client-setup.exe"

; The default installation directory
InstallDir $PROGRAMFILES\upload-client

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

;--------------------------------

!define MUI_FINISHPAGE_RUN "$INSTDIR\upload-client.exe"
!define MUI_FINISHPAGE_RUN_TEXT "Start client"
!insertmacro MUI_PAGE_FINISH

;--------------------------------

;Languages
!insertmacro MUI_LANGUAGE "English"

; The stuff to install
Section "" ;No components page, name is not important

	; Set output path to the installation directory.
	SetOutPath $INSTDIR

	; Put file there
	File /r *

	; Write the installation path into the registry
	WriteRegStr HKLM "SOFTWARE\PetroWS\Upload-Client" "Install_Dir" "$INSTDIR"

	; Write the uninstall keys for Windows
	WriteRegStr HKLM "${UNINST_KEY}" "DisplayName" "Upload Client"
	WriteRegStr HKLM "${UNINST_KEY}" "DisplayIcon" "$INSTDIR\upload-client.exe"
	WriteRegStr HKLM "${UNINST_KEY}" "UninstallString" "$INSTDIR\uninstall.exe"
	WriteRegDWORD HKLM "${UNINST_KEY}" "NoModify" 1
	WriteRegDWORD HKLM "${UNINST_KEY}" "NoRepair" 1
	WriteUninstaller "uninstall.exe"
  
SectionEnd ; end the section

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

	CreateDirectory "$SMPROGRAMS\Upload Client"
	CreateShortcut "$SMPROGRAMS\Upload Client\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
	CreateShortcut "$SMPROGRAMS\Upload Client\Client.lnk" "$INSTDIR\upload-client.exe" "" "$INSTDIR\upload-client.exe" 0
	CreateShortcut "$DESKTOP\Upload.lnk" "$INSTDIR\upload-client.exe"

SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"

	; Remove registry keys
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Upload-Client"
	DeleteRegKey HKLM "SOFTWARE\PetroWS\Upload-Client"
	DeleteRegKey HKCU "SOFTWARE\PetroWS\Upload-Client"

	; Remove files and uninstaller
	Delete $INSTDIR\*

	; Remove directories used
	RMDir /r "$INSTDIR"

SectionEnd
