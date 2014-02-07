changeLibraryOrLibraryName: changeLibrary
If [ Filter ( Get ( ApplicationVersion ) ; "go" ) = "go" ]
Exit Script [ ]
End If
Set Variable [ $library; Value:tempSetup::ﬁlePathLibraryToSwitchTo ]
If [ $library = Get (FilePath) ]
Go to Field [ ]
Exit Script [ ]
End If
Go to Field [ ]
#
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; $library ; Substitute ( $library ; "ﬁle:/" ; "ﬁle://" ) ) ; " " ; "%20" ) ]
[ No dialog ]
#
If [ Get (LastError) = 5 ]
#
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; $library ; Substitute ( $library ; "ﬁle:/" ; "ﬁle:///volumes/" ) ) ; " " ; "%20" ) ]
[ No dialog ]
#
If [ Get (LastError) = 5 ]
Select Window [ Name: "Setup"; Current ﬁle ]
#
Go to Layout [ “startMemorySwitch” (MemorySwitch) ]
Enter Find Mode [ ]
Set Field [ MemorySwitch::path; $library ]
Perform Find [ ]
#
If [ $library = MemorySwitch::path ]
Set Variable [ $libraryName; Value:MemorySwitch::name ]
Delete Record/Request
[ No dialog ]
End If
Go to Layout [ “defaultSetup” (tempSetup) ]
Show Custom Dialog [ Message: $libraryName & " cannot be found as it has been moved, deleted, or its name has been changed. The system has thus removed its name has from the switch libraries list. Find it and open it to put it back on the list."; Buttons: “OK” ]
#
#Reset pulldown menu to select the current ﬁle's
#name record, so that it will show up as selected when
#the user clicks on the pulldown list again.
Go to Layout [ “startMemorySwitch” (MemorySwitch) ]
Enter Find Mode [ ]
Set Field [ MemorySwitch::name; tempSetup::ﬁleName ]
Perform Find [ ]
Set Field [ TEMP::ﬁlePathLibraryToSwitchTo; MemorySwitch::path ]
Go to Layout [ “defaultSetup” (tempSetup) ]
Exit Script [ ]
End If
End If
#
#Reset pulldown menu to select the current ﬁle's
#name record, so that it will show up as selected when
#the user clicks on the pulldown list again.
Go to Layout [ “startMemorySwitch” (MemorySwitch) ]
Enter Find Mode [ ]
Set Field [ MemorySwitch::name; tempSetup::ﬁleName ]
Perform Find [ ]
Set Field [ TEMP::ﬁlePathLibraryToSwitchTo; MemorySwitch::path ]
Go to Layout [ “defaultSetup” (tempSetup) ]
Close Window [ Current Window ]
Close Window [ Name: "Tag Menus"; Current ﬁle ]
January 7, 平成26 12:09:47 Imagination Quality Management.fp7 - changeLibrary -1-
