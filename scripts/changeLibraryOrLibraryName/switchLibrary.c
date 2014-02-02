changeLibraryOrLibraryName: switchLibrary
#
#If on mobile device, stop the script.
If [ Filter ( Get ( ApplicationVersion ) ; "go" ) = "go" ]
Exit Script [ ]
End If
#
#If library selected is the one open then exit the script.
Set Variable [ $library; Value:tempSetup::ﬁlePathLibraryToSwitchTo ]
If [ $library = Get (FilePath) ]
Go to Field [ ]
Exit Script [ ]
End If
Go to Field [ ]
#
#If library path is blank (which should only happen if
#admin adds library manually with path), then delete
#this library name from the list.
If [ $library = "" ]
Select Window [ Name: "Setup"; Current ﬁle ]
#
Go to Layout [ “startMemorySwitch” (MemorySwitch) ]
Show All Records
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $library = MemorySwitch::path ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
If [ $library = MemorySwitch::path ]
Set Variable [ $name; Value:MemorySwitch::name ]
Delete Record/Request
[ No dialog ]
End If
Go to Layout [ “defaultSetup” (tempSetup) ]
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
Show Custom Dialog [ Message: $name & " cannot be found. It has been moved, deleted, or its name has been changed. Its name has been removed from the switch libraries list. Find and click on it to put it back on the list."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Open the selected library.
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; $library ; Substitute ( $library ; "ﬁle:/" ; "ﬁle://" ) ) ; " " ; "%20" ) ]
[ No dialog ]
#
#If the path stored for the selected library failed to open
#the library, then that library is no longer there or its
#name has been changed, so delete it from the
#library list.
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
Show Custom Dialog [ Message: $libraryName & " cannot be found. It has been moved, deleted, or its name has been changed. Its name has been removed from the switch libraries list. Find and click on it to put it back on the list."; Buttons: “OK” ]
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
February 1, 平成26 18:35:21 Imagination Quality Management.fp7 - switchLibrary -1-