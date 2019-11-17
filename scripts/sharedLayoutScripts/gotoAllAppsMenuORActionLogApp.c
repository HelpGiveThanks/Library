October 30, 2019 13:57:47 Librar.fmp12 - -1-
gotoAllAppsMenuORActionLogApp
sharedLayoutScripts: gotoAllAppsMenuORActionLogApp
#
#
#Ask user if they want to go the timer or
#the all apps menu.
If [ Get (WindowName) ≠ "All Apps" ]
Show Custom Dialog [ Message: "Open the Action Generator or the all apps menu?"; Default Button: “Generator”, Commit:
“Yes”; Button 2: “all apps”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Perform Script [ “allAppsMenu” ]
Exit Script [ ]
End If
#
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
End If
End If
#
If [ Get (WindowName) = "All Apps" ]
Set Variable [ $$otherApps ]
Close Window [ Current Window ]
End If
#
#
#BEGIN Find and record all open windows
#
#
#Get the name of the window that the user
#clicked the app button on.
Set Variable [ $windowAppWasClickedOn; Value:Get (WindowName) ]
#
#
#Now figure out what other windows are open.
#
#Put this discovery process in order so that the
#main windows our found after the Tag Menus
#and Reference window, as only main windows
#have the app button that triggered this script.
#
#There can be up to three windows open.
#
#REFERENCE (NOTE: Change this window
#name to references when time permits.)
#Is this window open and not alread recorded?
Select Window [ Name: "Reference"; Current file ]
If [ Get (LastError) ≠ 112 //window is missing = 112
and
$windowAppWasClickedOn ≠ Get ( WindowName ) ]
#Is the second open window accounted for?
If [ $windowAlsoOpen2 = "" ]
Set Variable [ $windowAlsoOpen2; Value:Get (WindowName) ]
Else
Set Variable [ $windowAlsoOpen3; Value:Get (WindowName) ]
End If
End If
#TAG MENUS
#Is this window open and not alread recorded?
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) ≠ 112 //window is missing = 112
and
$windowAppWasClickedOn ≠ Get ( WindowName ) ]
#Is the second open window accounted for?
If [ $windowAlsoOpen2 = "" ]
Set Variable [ $windowAlsoOpen2; Value:Get (WindowName) ]
Else
Set Variable [ $windowAlsoOpen3; Value:Get (WindowName) ]
End If
End If
#LEARN
#Is this window open and not alread recorded?
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) ≠ 112 //window is missing = 112
and
$windowAppWasClickedOn ≠ Get ( WindowName ) ]
#Is the second open window accounted for?
If [ $windowAlsoOpen2 = "" ]
Set Variable [ $windowAlsoOpen2; Value:Get (WindowName) ]
Else
Set Variable [ $windowAlsoOpen3; Value:Get (WindowName) ]
End If
End If
#REFERENCES
#Is this window open and not alread recorded?
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) ≠ 112 //window is missing = 112
and
$windowAppWasClickedOn ≠ Get ( WindowName ) ]
#Is the second open window accounted for?
If [ $windowAlsoOpen2 = "" ]
Set Variable [ $windowAlsoOpen2; Value:Get (WindowName) ]
Else
Set Variable [ $windowAlsoOpen3; Value:Get (WindowName) ]
End If
End If
#REPORT
#Is this window open and not alread recorded?
Select Window [ Name: "Report"; Current file ]
If [ Get (LastError) ≠ 112 //window is missing = 112
and
$windowAppWasClickedOn ≠ Get ( WindowName ) ]
#Is the second open window accounted for?
If [ $windowAlsoOpen2 = "" ]
Set Variable [ $windowAlsoOpen2; Value:Get (WindowName) ]
Else
Set Variable [ $windowAlsoOpen3; Value:Get (WindowName) ]
End If
End If
#SETUP
#Is this window open and not alread recorded?
Select Window [ Name: "Setup"; Current file ]
If [ Get (LastError) ≠ 112 //window is missing = 112
and
$windowAppWasClickedOn ≠ Get ( WindowName ) ]
#Is the second open window accounted for?
If [ $windowAlsoOpen2 = "" ]
Set Variable [ $windowAlsoOpen2; Value:Get (WindowName) ]
Else
Set Variable [ $windowAlsoOpen3; Value:Get (WindowName) ]
End If
End If
#SHARE
#Is this window open and not alread recorded?
Select Window [ Name: "Share"; Current file ]
If [ Get (LastError) ≠ 112 //window is missing = 112
and
$windowAppWasClickedOn ≠ Get ( WindowName ) ]
#Is the second open window accounted for?
If [ $windowAlsoOpen2 = "" ]
Set Variable [ $windowAlsoOpen2; Value:Get (WindowName) ]
Else
Set Variable [ $windowAlsoOpen3; Value:Get (WindowName) ]
End If
End If
#TEST
#Is this window open and not alread recorded?
Select Window [ Name: "Test"; Current file ]
If [ Get (LastError) ≠ 112 //window is missing = 112
and
$windowAppWasClickedOn ≠ Get ( WindowName ) ]
#Is the second open window accounted for?
If [ $windowAlsoOpen2 = "" ]
Set Variable [ $windowAlsoOpen2; Value:Get (WindowName) ]
Else
Set Variable [ $windowAlsoOpen3; Value:Get (WindowName) ]
End If
End If
#TEST TEMPLATES
#Is this window open and not alread recorded?
Select Window [ Name: "Test Templates"; Current file ]
If [ Get (LastError) ≠ 112 //window is missing = 112
and
$windowAppWasClickedOn ≠ Get ( WindowName ) ]
#Is the second open window accounted for?
If [ $windowAlsoOpen2 = "" ]
Set Variable [ $windowAlsoOpen2; Value:Get (WindowName) ]
Else
Set Variable [ $windowAlsoOpen3; Value:Get (WindowName) ]
End If
End If
#
Set Field [ MemorySwitch::currentLibraryPath; Get ( FilePath ) ]
Set Field [ MemorySwitch::currentLibraryWIndows; $windowAppWasClickedOn ]
Set Field [ MemorySwitch::currentLibraryWIndows[2]; $windowAlsoOpen2 ]
Set Field [ MemorySwitch::currentLibraryWIndows[3]; $windowAlsoOpen3 ]
#
#
#END Find and record all open windows
#
#
#
#Open using this url on iPad/iPhone.
If [ Get ( SystemPlatform ) = 3 ]
Open URL [ "fmp://%7e/ActionGenerator" ]
[ No dialog ]
Exit Script [ ]
Else
Select Window [ Name: "Tag" ]
If [ Get (LastError) = 112 ]
Set Variable [ $notOpen; Value:1 ]
End If
Select Window [ Name: "Day" ]
If [ Get (LastError) = 112 ]
Set Variable [ $notOpen; Value:1 + $notOpen ]
End If
Select Window [ Name: "Timer" ]
If [ Get (LastError) = 112 ]
Set Variable [ $notOpen; Value:1 + $notOpen ]
End If
Select Window [ Name: "Specific Action" ]
If [ Get (LastError) = 112 ]
Set Variable [ $notOpen; Value:1 + $notOpen ]
End If
Select Window [ Name: "ActionGenerator" ]
If [ Get (LastError) = 112 ]
Set Variable [ $notOpen; Value:1 + $notOpen ]
End If
End If
#
#If ActionLog is not open on the desktop
#computer, then open it.
If [ $notOpen = 5 ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "help" ; "ActionGenerator" ) ]
[ No dialog ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "help" ; "ActionGenerator" ) ]
[ No dialog ]
End If
#
#This logic is the same for going to all apps in
#each HGT application. So if you change it,
#change it everywhere.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ActionGenerator's name has been changed or it is not in its required folder:
0penME_YourFilesAreHere."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "If the name is correct (ActionGenerator) and it is in the correct folder
(0penME_YourFilesAreHere), then check if the file types are either all .fmp12 or . HFG2 files."; Default Button: “OK”, Commit:
“Yes” ]
Show Custom Dialog [ Message: "Click the HelpGiveThanks Website button to find out how to get a new copy of the ActionLog if
needed."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "Open the folder — 0penME_YourFilesAreHere — so you can check on this app, or put it in this
folder?"; Default Button: “yes”, Commit: “Yes”; Button 2: “no”, Commit: “No” ]
If [ Get (LastMessageChoice) = 1 ]
Open URL [ Substitute (
Left ( MemorySwitch::helpPath ; Length ( MemorySwitch::helpPath ) -
Case ( Middle ( Right ( MemorySwitch::helpPath ; 6 ) ; 0 ; 1 ) = "." ; 11 ;
 Middle ( Right ( MemorySwitch::helpPath ; 5 ) ; 0 ; 1 ) = "." ; 10 ;
 Middle ( Right ( MemorySwitch::helpPath ; 4 ) ; 0 ; 1 ) = "." ; 9 ;
 Middle ( Right ( MemorySwitch::helpPath ; 3 ) ; 0 ; 1 ) = "." ; 8 ) )
 ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Left ( MemorySwitch::helpPath ; Length ( MemorySwitch::helpPath ) -
Case ( Middle ( Right ( MemorySwitch::helpPath ; 6 ) ; 0 ; 1 ) = "." ; 11 ;
 Middle ( Right ( MemorySwitch::helpPath ; 5 ) ; 0 ; 1 ) = "." ; 10 ;
 Middle ( Right ( MemorySwitch::helpPath ; 4 ) ; 0 ; 1 ) = "." ; 9 ;
 Middle ( Right ( MemorySwitch::helpPath ; 3 ) ; 0 ; 1 ) = "." ; 8 ) ) ]
[ No dialog ]
End If
#
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The folder name — 0penME_YourFilesAreHere — has been changed, or this folder
has been moved."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
End If
#
#
