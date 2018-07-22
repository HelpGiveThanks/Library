July 20, 2018 17:15:12 Library.fmp12 - help -1-
help: help
#
#
#BEGIN Help interface and column message
#
#If the help app is open figure out if it is
#focused on help for the interface the user
#is currently looking at.
If [ MemorySwitch::helpAppIsRunning ≠ "" ]
#
#If not focused on the help layout or column for
#the current interface then ask the user if they
#would like to go to help for this interface, or
#return the help for the interface currently showing.
If [ MemorySwitch::helpLayoutName ≠ $$helpLayoutName or MemorySwitch::helpLayoutColumnName ≠ $$helpColumnName ]
If [ $$helpLayoutName = "Test" ]
If [ $$helpColumnName = "B" ]
Show Custom Dialog [ Message: "Go to help for this interface (Test Templates" & ": Column — " & $
$helpColumnName & "), or return to the interface help being viewed?"; Default Button: “return”, Commit: “Yes”;
Button 2: “go”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
Else If [ $$helpColumnName = "C" ]
Show Custom Dialog [ Message: "Go to help for this interface (Test" & ": Column — " & $$helpColumnName & "),
or return to the interface help being viewed?"; Default Button: “return”, Commit: “Yes”; Button 2: “go”, Commit:
“No”; Button 3: “cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Go to help for this interface (Report" & ": Column — " & $$helpColumnName &
"), or return to the interface help being viewed?"; Default Button: “return”, Commit: “Yes”; Button 2: “go”,
Commit: “No”; Button 3: “cancel”, Commit: “No” ]
End If
Else
#
#If the $$gotoHelpObject variable is blank,
#meaning the user has already been asked if
#they want to go help for an interface that has
#to close to do so, ask if they want to go to help.
If [ $$gotoHelpObject = "" ]
Show Custom Dialog [ Message: "Go to help for this interface (" & $$helpLayoutName & ": Column — " & $
$helpColumnName & "), or return to the interface help being viewed?"; Default Button: “return”, Commit: “Yes”;
Button 2: “go”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
End If
End If
#
#
#
If [ Get (LastMessageChoice) = 2 or $$gotoHelpObject ≠ "" ]
Set Field [ MemorySwitch::helpLayoutName; $$helpLayoutName ]
Set Field [ MemorySwitch::helpLayoutColumnName; $$helpColumnName ]
Set Field [ MemorySwitch::helpLayoutObjectName; $$helpColumnName ]
Set Variable [ $messageChoice; Value:2 ]
End If
#
If [ Get (LastMessageChoice) = 3 ]
Exit Script [ ]
End If
#
#
#If focused on the help layout and column for
#the current interface then just go to it.
Else
If [ Get ( SystemPlatform ) ≠ 3 ]
Select Window [ Name: "Help" ]
Else
Open URL [ "fmp://%7e/Help" ]
[ No dialog ]
End If
Exit Script [ ]
End If
#
#If the help app is not open, then tell the user
#what interface and column they are going
#to be taken to when it is opened.
Else
Set Field [ MemorySwitch::helpLayoutName; $$helpLayoutName ]
Set Field [ MemorySwitch::helpLayoutColumnName; $$helpColumnName ]
Set Field [ MemorySwitch::helpLayoutObjectName; $$helpColumnName ]
If [ $$helpLayoutName = "Test" ]
If [ $$helpColumnName = "B" ]
Show Custom Dialog [ Message: "Now going to help for this interface (Test Templates" & ": Column — " & $
$helpColumnName & ")."; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
Else If [ $$helpColumnName = "C" ]
Show Custom Dialog [ Message: "Now going to help for this interface (Test" & ": Column — " & $$helpColumnName &
")."; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Now going to help for this interface (Report" & ": Column — " & $$helpColumnName
& ")."; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
End If
Else
Show Custom Dialog [ Message: "Now going to help for this interface (" & $$helpLayoutName & ": Column — " & $
$helpColumnName & ")."; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
End If
#
If [ Get (LastMessageChoice) = 2 ]
Exit Script [ ]
End If
End If
#
#
#END Help interface and column message
#
#
#
#
#
#BEGIN Find and record all open windows
#
#
#Get the name of the window that the user
#clicked the help button on.
Set Variable [ $windowHelpWasClickedOn; Value:Get (WindowName) ]
#
#Update the current app being used info.
Set Field [ MemorySwitch::backToSolution; "Library" ]
#
#
#Now figure out what other windows are open.
#There can be up to three windows open.
#LEARN
#Is this window open and not alread recorded?
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) ≠ 112 //window is missing = 112
and
$windowHelpWasClickedOn ≠ Get ( WindowName ) ]
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
$windowHelpWasClickedOn ≠ Get ( WindowName ) ]
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
$windowHelpWasClickedOn ≠ Get ( WindowName ) ]
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
$windowHelpWasClickedOn ≠ Get ( WindowName ) ]
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
$windowHelpWasClickedOn ≠ Get ( WindowName ) ]
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
$windowHelpWasClickedOn ≠ Get ( WindowName ) ]
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
$windowHelpWasClickedOn ≠ Get ( WindowName ) ]
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
$windowHelpWasClickedOn ≠ Get ( WindowName ) ]
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
$windowHelpWasClickedOn ≠ Get ( WindowName ) ]
#Is the second open window accounted for?
If [ $windowAlsoOpen2 = "" ]
Set Variable [ $windowAlsoOpen2; Value:Get (WindowName) ]
Else
Set Variable [ $windowAlsoOpen3; Value:Get (WindowName) ]
End If
End If
#
Set Field [ MemorySwitch::helpAppWindowName; $windowHelpWasClickedOn ]
Set Field [ MemorySwitch::helpAppWindowName[2]; $windowAlsoOpen2 ]
Set Field [ MemorySwitch::helpAppWindowName[3]; $windowAlsoOpen3 ]
#
#
#END Find and record all open windows
#
#
#
#
#Go to the help windows if the app is open.
If [ Get ( SystemPlatform ) ≠ 3 ]
Select Window [ Name: "Tutorial" ]
Select Window [ Name: "Menu" ]
Select Window [ Name: "Help" ]
Else
Open URL [ "fmp://%7e/Help" ]
[ No dialog ]
End If
#
#
#If open, then run the script that forces help
#to go the user's selected help location.
If [ Get (LastError) ≠ 112 //window is missing = 112 ]
If [ $messageChoice = 2 ]
Perform Script [ “TRIGGERED_SCRIPTByOtherApp” from file: “Help” ]
Else
Perform Script [ “fixForLearnLayoutBug” from file: “Help” ]
End If
#
Else
#
#If help is not open, then open it.
If [ Get ( SystemPlatform ) ≠ 3 ]
Open URL [ MemorySwitch::helpPath ]
[ No dialog ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "file://" ; "file:///Volumes/" ) ]
[ No dialog ]
Else
Open URL [ "fmp://%7e/Help" ]
End If
End If
#
#
