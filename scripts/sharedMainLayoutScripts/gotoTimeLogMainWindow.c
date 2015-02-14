sharedMainLayoutScripts: gotoTimeLogMainWindow
Set Field [ MemorySwitch::currentLibraryMainWIndow; Get ( WindowName ) ]
Set Field [ MemorySwitch::currentLibraryPath; Get ( FilePath ) ]
Select Window [ Name: "Tag" ]
Select Window [ Name: "Day" ]
Select Window [ Name: "Specific Action" ]
Select Window [ Name: "Timer" ]
If [ Get (LastError) = 112 ]
Set Variable [ $timer; Value:Get (LastError) ]
End If
Select Window [ Name: "HelpGiveThanks Apps" ]
If [ Get (LastError) = 112 ]
Set Variable [ $app; Value:Get (LastError) ]
End If
If [ $timer + $app = 224 ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "help" ; "actionLog82" ) ]
[ No dialog ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "help" ; "actionLog" ) ]
[ No dialog ]
End If
January 7, 平成26 18:08:01 Imagination Quality Management.fp7 - gotoTimeLogMainWindow -1-
