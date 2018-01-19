January 18, 2018 16:05:10 Library.fmp12 - gotoTimeLogMainWindow -1-
sharedLayoutScripts: gotoTimeLogMainWindow
#
#
#Ask user if they want to go the timer or
#the all apps menu.
Show Custom Dialog [ Message: "Open the Action Log (timer) or the All Apps menu?"; Default Button: “timer”, Commit: “Yes”; Button
2: “All”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Perform Script [ “allSolutionsMenu (new)” ]
Exit Script [ ]
End If
#
#
#Open using this url on iPad/iPhone.
If [ Get ( SystemPlatform ) = 3 ]
Open URL [ "fmp://%7e/ActionLog" ]
[ No dialog ]
Exit Script [ ]
End If
#
Set Field [ MemorySwitch::currentLibraryMainWIndow; Get ( WindowName ) ]
Set Field [ MemorySwitch::currentLibraryPath; Get ( FilePath ) ]
Select Window [ Name: "Tag" ]
Select Window [ Name: "Day" ]
Select Window [ Name: "Specific Action" ]
Select Window [ Name: "Timer" ]
If [ Get (LastError) = 112 ]
Set Variable [ $timer; Value:Get (LastError) ]
End If
Select Window [ Name: "HelpGiveThanks Solutions" ]
If [ Get (LastError) = 112 ]
Set Variable [ $app; Value:Get (LastError) ]
End If
If [ $timer + $app = 224 ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "help" ; "actionLog82" ) ]
[ No dialog ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "help" ; "actionLog" ) ]
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
