July 21, 2018 12:53:50 Library.fmp12 - gotoAllAppsMenuORActionLogApp -1-
sharedLayoutScripts: gotoAllAppsMenuORActionLogApp
#
#
#Ask user if they want to go the timer or
#the all apps menu.
Show Custom Dialog [ Message: "Open the Action Log (timer) or the all apps menu?"; Default Button: “timer”, Commit: “Yes”; Button
2: “all apps”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Perform Script [ “allAppsMenu (update)” ]
Exit Script [ ]
End If
#
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
End If
#
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
#There can be up to three windows open.
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
Open URL [ "fmp://%7e/ActionLog" ]
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
Select Window [ Name: "HelpGiveThanks Apps" ]
If [ Get (LastError) = 112 ]
Set Variable [ $notOpen; Value:1 + $notOpen ]
End If
End If
#
#If ActionLog is not open on the desktop
#computer, then open it.
If [ $notOpen = 5 ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "help" ; "actionlog" ) ]
[ No dialog ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "help" ; "actionLog" ) ]
[ No dialog ]
End If
#
#
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "This library file needs to be put into the HGT folder. "; Default Button: “OK”, Commit: “Yes” ]
End If
#
#
